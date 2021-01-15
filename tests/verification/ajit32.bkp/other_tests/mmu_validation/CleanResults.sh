#script for cleaning *ALL* results created by validation_outer script.

find . -name "src_file_list*" -type f -delete
find . -name "validation.console*" -type f -delete
find . -name "validation.job*" -type f -delete
find . -name "log" -type d -exec rm -r "{}" \;
find . -name "trace_files" -type d -exec rm -r "{}" \;
find . -name "compiled" -type d -exec rm -r "{}" \;
