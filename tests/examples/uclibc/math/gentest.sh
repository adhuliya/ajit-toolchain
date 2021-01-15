#!/usr/bin/env bash
# Author: Anshuman Dhuliya (anshumandhuliya@gmail.com)

# This script takes a model folder as a model test and
# replicates all its files in all the other folders
# perserving `main.c` and `main.results` file in
# each folder.

_CWD="`pwd`";
_MODEL="$_CWD/../../misc/sin-model-test";
_TMP_DIR="`mktemp -d $_CWD/tmpdir.XXXX`";

for x in `ls`; do
  if [[ -d "$x" ]]; then
    cd "$x";

    mkdir -p $_TMP_DIR;   # CREATE: TMP_DIRECTORY_1
    mv ./{main.c,main.results} $_TMP_DIR;

    rm -r *;
    cp $_MODEL/* .;

    mv $_TMP_DIR/{main.c,main.results} .;
    rm -rf $_TMP_DIR;     # DELETE: TMP_DIRECTORY_1

    cd "$_CWD";
    echo "Done: $x";
  fi
done


echo -e "\nNo errors above? Then all is probably good.";


