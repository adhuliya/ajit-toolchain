#!/usr/bin/env bash

set -eE

BASE_MARSHAL=e5243630ddb091eeda27678d2d124806cfe35dc6

temporary_root=
failure=
trap 'failure="line $LINENO: $BASH_COMMAND"' ERR
trap 'status=$?; rm -rf -- "${temporary_root:-}"; if ((status)); then printf "Exited %d; last failure: %s\n" "$status" "$failure" >&2; else printf "Exited successfully.\n"; fi' EXIT

script_dir=$(CDPATH= cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)
script_path="$script_dir/${BASH_SOURCE[0]##*/}"
ajit_tools_root=$(git -C "$script_dir/.." rev-parse --show-toplevel)

base_marshal=$BASE_MARSHAL
new_marshal=$(git -C "$ajit_tools_root" rev-parse refs/heads/marshal)

if [[ $base_marshal == "$new_marshal" ]]; then
    printf 'Already synchronized with marshal %s\n' "$new_marshal"
fi

destination_roots=(
    ajit-processor/AjitPublicResources
    ajit-processor/ahir_release
    ajit-processor/application_development
    docs
    os
    testing/tests
    testing/training
    testing/validation_ladder
)

temporary_root=$(mktemp -d)

generated_excludes=(
    ':(exclude,glob)**/bin/**'
    ':(exclude,glob)**/lib/*.a'
    ':(exclude,glob)**/lib/**/*.a'
    ':(exclude,glob)**/obj_assembly/**'
    ':(exclude,glob)**/.sconsign.dblite'
    ':(exclude,glob)**/cortos_build/**'
    ':(exclude,glob)**/*.log'
    ':(exclude,glob)**/*.elf'
    ':(exclude,glob)**/*.hex'
    ':(exclude,glob)**/*.mmap'
    ':(exclude,glob)**/*.mmap.remapped'
    ':(exclude,glob)**/*.objdump'
    ':(exclude,glob)**/*.vars'
    ':(exclude,glob)**/*.wtrace.*'
    ':(exclude,glob)**/*~'
)

compatibility_excludes=(
    ':(exclude)build.sh'
    ':(exclude)processor/64bit/C_multi_core_multi_thread/SConscript'
    ':(exclude)processor/64bit/C_multi_core_multi_thread/SConstruct'
    ':(exclude)processor/64bit/C_multi_core_multi_thread/common/src/Ancillary.c'
    ':(exclude)processor/64bit/C_multi_core_multi_thread/cpu/SConscript'
    ':(exclude)processor/64bit/C_multi_core_multi_thread/cpu/SConstruct'
    ':(exclude)processor/64bit/C_multi_core_multi_thread/half_precision_float/SConscript'
    ':(exclude)processor/64bit/C_multi_core_multi_thread/half_precision_float/SConstruct'
    ':(exclude)processor/64bit/C_multi_core_multi_thread/half_precision_float/aa2clib/SConscript'
    ':(exclude)processor/64bit/C_multi_core_multi_thread/half_precision_float/aa2clib/SConstruct'
    ':(exclude,glob)processor/64bit/C_multi_core_multi_thread/half_precision_float/**/*pthread*'
    ':(exclude)processor/64bit/C_multi_core_multi_thread/testbench/SConscript'
    ':(exclude)processor/64bit/C_multi_core_multi_thread/testbench/SConstruct'
    ':(exclude)processor/C_reference_model/SConscript'
    ':(exclude)processor/C_reference_model/SConstruct'
    ':(exclude)processor/C_reference_model/cache/src/DummyDcache.c'
    ':(exclude)processor/C_reference_model/cache/src/DummyIcache.c'
    ':(exclude)processor/C_reference_model/common/src/Ancillary.c'
    ':(exclude)processor/C_reference_model/cpu/SConscript'
    ':(exclude)processor/C_reference_model/debugger/gpb/src/GDBtoAJITbridge.c'
    ':(exclude)processor/TestEnvironments/core_environment/aggregator/include/spi.h'
    ':(exclude)processor/TestEnvironments/core_environment/aggregator/src/aggregator.c'
    ':(exclude)processor/TestEnvironments/core_environment/bootmem/SConscript'
    ':(exclude)processor/TestEnvironments/core_environment/char_client_server/src/char_client_server.c'
    ':(exclude)tools/ajit_debug_monitor/SConscript'
    ':(exclude)tools/ajit_debug_monitor/SConstruct'
    ':(exclude)tools/ajit_debug_monitor_mt/SConscript'
    ':(exclude)tools/ajit_debug_monitor_mt/SConstruct'
    ':(exclude)tools/antlr3Cruntime/SConscript'
    ':(exclude)tools/antlr3Cruntime/SConstruct'
)

patch_counter=0

apply_tree() {
    local source_directory=$1
    local destination_directory=$2
    shift 2

    ((patch_counter += 1))
    local patch_file="$temporary_root/$patch_counter.patch"

    # marshal is read-only: this command only creates a patch from commit trees.
    git -C "$ajit_tools_root" diff \
        --binary \
        --full-index \
        --no-renames \
        "$base_marshal:$source_directory" \
        "$new_marshal:$source_directory" \
        -- \
        . \
        "${generated_excludes[@]}" \
        "$@" \
        > "$patch_file"

    if [[ ! -s $patch_file ]]; then
        return
    fi

    printf 'apply %s -> %s\n' "$source_directory" "$destination_directory"

    # All index and worktree updates explicitly target ajit_tools.
    git -C "$ajit_tools_root" apply \
        --3way \
        --index \
        --directory="$destination_directory" \
        "$patch_file"
}

apply_tree \
    AjitPublicResources \
    ajit-processor/AjitPublicResources \
    "${compatibility_excludes[@]}"

apply_tree \
    ahir_release \
    ajit-processor/ahir_release \
    ':(exclude)include/pthreadUtils.h'

apply_tree \
    application_development \
    ajit-processor/application_development

apply_tree docs docs
apply_tree os os
apply_tree tests testing/tests
apply_tree training testing/training
apply_tree validation_ladder testing/validation_ladder

# git apply --3way uses the index. Return successful results to the same
# unstaged working-tree form produced by the earlier synchronizer.
git -C "$ajit_tools_root" reset -q HEAD -- "${destination_roots[@]}"

updated_script="$temporary_root/sync-marshal-content.sh"
sed "s/^BASE_MARSHAL=.*/BASE_MARSHAL=$new_marshal/" \
    "$script_path" > "$updated_script"
chmod 755 "$updated_script"
mv -- "$updated_script" "$script_path"

printf 'Synchronized to marshal %s\n' "$new_marshal"
