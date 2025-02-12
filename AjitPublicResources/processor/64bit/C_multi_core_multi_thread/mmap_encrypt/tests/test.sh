../bin/mmap_encrypt -e coremark.mmap coremark.encrypted.mmap test_keys.txt
../bin/mmap_encrypt -d coremark.encrypted.mmap coremark.decrypted.mmap test_keys.txt
../bin/fc  coremark.mmap coremark.decrypted.mmap 
