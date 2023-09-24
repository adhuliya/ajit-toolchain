r mode
w rst 1
w ipc 0x40000000
r ipc
w inpc 0x40000004
r inpc
m coremark.mmap 0x40000000
w rst 0
r mode
