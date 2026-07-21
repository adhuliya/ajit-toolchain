#!/usr/bin/env bash

set -euo pipefail

usage() {
    cat <<'EOF'
Usage: sync-marshal-content.sh [--dry-run] MARSHAL_WORKTREE [AJIT_TOOLS_WORKTREE]

Copy the reviewed, Git-tracked marshal directories into an ajit_tools branch
worktree. The destination defaults to the repository containing this script.

This deliberately excludes ahir_release, pthread compatibility files,
Ajit's hello/print test changes, generated outputs, and untracked files.
EOF
}

dry_run=false
if [[ ${1:-} == --dry-run ]]; then
    dry_run=true
    shift
fi

if (($# < 1 || $# > 2)); then
    usage >&2
    exit 2
fi

marshal_root=$(git -C "$1" rev-parse --show-toplevel 2>/dev/null) || {
    printf 'error: not a Git worktree: %s\n' "$1" >&2
    exit 1
}

script_dir=$(CDPATH= cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)
destination_arg=${2:-"$script_dir/.."}
ajit_tools_root=$(git -C "$destination_arg" rev-parse --show-toplevel 2>/dev/null) || {
    printf 'error: not a Git worktree: %s\n' "$destination_arg" >&2
    exit 1
}

marshal_branch=$(git -C "$marshal_root" branch --show-current)
destination_branch=$(git -C "$ajit_tools_root" branch --show-current)

if [[ $marshal_branch != marshal ]]; then
    printf 'error: source must have marshal checked out (found %s)\n' \
        "$marshal_branch" >&2
    exit 1
fi

if [[ $destination_branch != ajit_tools ]]; then
    printf 'error: destination must have ajit_tools checked out (found %s)\n' \
        "$destination_branch" >&2
    exit 1
fi

if [[ $marshal_root == "$ajit_tools_root" ]]; then
    printf 'error: source and destination must be different worktrees\n' >&2
    exit 1
fi

# Each entry is SOURCE_DIRECTORY|DESTINATION_DIRECTORY.
# Keep this list narrow: these boundaries were reviewed against the two branch
# tips and do not include Ajit's pthread or other host-compatibility changes.
sync_paths=(
    'AjitPublicResources/processor/64bit/C_multi_core_multi_thread/common/include|ajit-processor/AjitPublicResources/processor/64bit/C_multi_core_multi_thread/common/include'
    'AjitPublicResources/processor/64bit/C_multi_core_multi_thread/devices|ajit-processor/AjitPublicResources/processor/64bit/C_multi_core_multi_thread/devices'
    'AjitPublicResources/tools/ajit_access_routines|ajit-processor/AjitPublicResources/tools/ajit_access_routines'
    'AjitPublicResources/tools/scripts|ajit-processor/AjitPublicResources/tools/scripts'
    'os|os'
    'validation_ladder/basic_tests/dot_product/BIGMEM|testing/validation_ladder/basic_tests/dot_product/BIGMEM'
    'validation_ladder/benchmarks/coremark/opt|testing/validation_ladder/benchmarks/coremark/opt'
    'validation_ladder/benchmarks/nnet|testing/validation_ladder/benchmarks/nnet'
    'validation_ladder/cortos2_tests/mutexes|testing/validation_ladder/cortos2_tests/mutexes'
)

copy_tracked_directory() {
    local source_directory=$1
    local destination_directory=$2
    local source_path relative_path destination_path
    local copied=0

    if ! git -C "$marshal_root" diff --quiet HEAD -- "$source_directory"; then
        printf 'error: source has tracked changes under %s\n' \
            "$source_directory" >&2
        return 1
    fi

    while IFS= read -r -d '' source_path; do
        relative_path=${source_path#"$source_directory"/}
        destination_path="$ajit_tools_root/$destination_directory/$relative_path"
        printf 'copy %s -> %s\n' "$source_path" \
            "$destination_directory/$relative_path"

        if ! $dry_run; then
            mkdir -p -- "$(dirname -- "$destination_path")"
            cp -a -- "$marshal_root/$source_path" "$destination_path"
        fi
        ((copied += 1))
    done < <(git -C "$marshal_root" ls-files -z -- "$source_directory")

    if ((copied == 0)); then
        printf 'error: no tracked files found under %s\n' \
            "$source_directory" >&2
        return 1
    fi
}

for mapping in "${sync_paths[@]}"; do
    copy_tracked_directory "${mapping%%|*}" "${mapping#*|}"
done

if $dry_run; then
    printf 'Dry run complete; no files changed.\n'
else
    printf 'Synchronization complete. Review with: git -C %q status --short\n' \
        "$ajit_tools_root"
fi
