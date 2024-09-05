makeLinkerScript.py -t 0x0 -d 0x1000 -o LinkerScript.lnk
compileToSparcUclibc.py -N add2 -s add2.s  -L LinkerScript.lnk  -W ./
