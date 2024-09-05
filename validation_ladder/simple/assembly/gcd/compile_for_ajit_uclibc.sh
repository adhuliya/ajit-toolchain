TEXTBASE=0x0
DATABASE=0x4000
#1.  make a linker script
makeLinkerScript.py -t $TEXTBASE -d $DATABASE -o customLinkerScript.lnk
#2. compile the application
compileToSparcUclibc.py -N gcd -s gcd.s -L customLinkerScript.lnk
