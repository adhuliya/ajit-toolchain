#!/bin/bash

# ---- MODIFY THESE PATHS AS NEEDED ----
SRC_DIR="../src"         # Directory containing .c source files
HEADER_DIR="../include"  # Directory containing header files
PROGRAM_PATH="crypto_program.c"  # Unified encryption/decryption program
TEST_KEYS_PATH="test_keys.txt"   # Default key file (optional)

# ---- OUTPUT EXECUTABLE NAME ----
CRYPTO_EXEC="crypto_program"

# ---- CHECK ARGUMENTS ----
if [ "$1" == "-h" ]; then
if [ "$1" == "-h" ]; then
    echo "--------------------------------------------------------------------------------------------------"
    echo "            MMAP Encryption & Decryption tool using AES in CTR mode with Hashing"
    echo "--------------------------------------------------------------------------------------------------"
    echo "Usage:"
    echo "  ./run_DE.sh -e <input_file> <output_file> <key_file>"
    echo "      - Encrypts <input_file> using <key_file> and saves to <output_file>."
    echo ""
    echo "  ./run_DE.sh -d <input_file> <output_file> <key_file>"
    echo "      - Decrypts <input_file> using <key_file> and saves to <output_file>."
    echo ""
    echo "Examples:"
    echo "  To encrypt a file:"
    echo "    ./run_DE.sh -e example_input.mmap encrypted_output.mmap example_keys.txt"
    echo ""
    echo "  To decrypt a file:"
    echo "    ./run_DE.sh -d encrypted_output.mmap decrypted_output.mmap example_keys.txt"
    echo ""
    echo "  For help:"
    echo "    ./run_DE.sh -h"
    echo ""
    echo "Key File Format Example:"
    echo "  The key file should contain two 64-bit hexadecimal values (128-bit AES key)"
    echo "  & a 32 bit hash."
    echo "  Example (example_key.txt):"
    echo "    0x0f1571c947d9e859 0x0cb7add6af7f6798 0x00000000"
    echo ""
    echo "Memory-Mapped File Format Example:"
    echo "  The mmap file should contain addresses followed by byte values."
    echo "  Example (example_input.mmap):"
    echo "    0x40000000 90"
    echo "    0x40000001 10"
    echo "    0x40000002 21"
    echo "    0x40000003 00"
    echo "------------------------------------------------------------"
    exit 0
fi
fi


# ---- VALIDATE OTHER ARGUMENTS ----
if [ "$#" -ne 4 ]; then
    echo "[ERROR] Invalid number of arguments."
    echo "Run './run_DE.sh -h' for usage instructions."
    exit 1
fi

MODE=$1          # Mode: -e or -d
INPUT_FILE=$2    # Input file (plaintext or encrypted)
OUTPUT_FILE=$3   # Output file (encrypted or decrypted)
KEY_FILE=$4      # AES key file

# ---- COMPILING THE PROGRAM ----
echo "[INFO] Compiling Program..."
gcc -o $CRYPTO_EXEC "$PROGRAM_PATH" "$SRC_DIR/aes_block.c" "$SRC_DIR/aes_utils.c" -I"$HEADER_DIR" -Wall
if [ $? -ne 0 ]; then
    echo "[ERROR] Compilation failed!"
    exit 1
fi

# ---- RUNNING ENCRYPTION OR DECRYPTION ----
if [ "$MODE" == "-e" ]; then
    echo "[INFO] Performing Encryption..."
    ./$CRYPTO_EXEC -e "$INPUT_FILE" "$OUTPUT_FILE" "$KEY_FILE"
    if [ $? -ne 0 ]; then
        echo "[ERROR] Encryption failed!"
        exit 1
    fi
    echo "[SUCCESS] Encryption Completed!"
    echo "[INFO] Encrypted output saved to: $OUTPUT_FILE"

elif [ "$MODE" == "-d" ]; then
    echo "[INFO] Performing Decryption..."
    ./$CRYPTO_EXEC -d "$INPUT_FILE" "$OUTPUT_FILE" "$KEY_FILE"
    if [ $? -ne 0 ]; then
        echo "[ERROR] Decryption failed!"
        exit 1
    fi
    echo "[SUCCESS] Decryption Completed!"
    echo "[INFO] Decrypted output saved to: $OUTPUT_FILE"

else
    echo "[ERROR] Invalid mode flag '$MODE'. Use -e for encryption, -d for decryption, or -h for help."
    exit 1
fi

