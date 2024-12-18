#!/bin/bash

# Paths to source files and header files
SRC_FILES=(
    "../src/aes_block.c"
    "../src/aes_utils.c"
    "Main.c"
)

HEADER_DIRS=(
    "../include"
)

# Output executable name
OUTPUT="program"

# Build include flags for header directories
INCLUDE_FLAGS=""
for dir in "${HEADER_DIRS[@]}"; do
    INCLUDE_FLAGS+="-I${dir} "
done

# Compile the program
echo "Compiling..."
gcc ${INCLUDE_FLAGS} "${SRC_FILES[@]}" -o ${OUTPUT}

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful! Running the program..."
    ./${OUTPUT}
else
    echo "Compilation failed!"
    exit 1
fi

