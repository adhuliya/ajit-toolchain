makeLinkerScript.py -t 0x40000000 -d 0x40001000 -o LinkerScript.lnk
compileToSparcUclibc.py -N add2 -s add2.s  -L LinkerScript.lnk  -W ./
