r mode
w rst 1
w ipc 0x40000000
w inpc 0x40000004
m dcache_store_hit.mmap.remapped 0x40000000
w rst 0
r mode
