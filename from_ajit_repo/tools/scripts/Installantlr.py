#! /usr/bin/python
import sys
import os
import subprocess

#cd to directory in which this script resides
working_dir  = os.environ['AJIT_PROJECT_HOME']+"/processor/C/debugger/doval/antlr3Cruntime/"
os.chdir(working_dir)


#install antlr C runtime
print "Installing antlr3C runtime............"
#untar the antlr runtime tarball
command = "tar -xzvf libantlr3c-3.4.tar.gz"
subprocess.call(command.split())
os.chdir("./libantlr3c-3.4")
build_dir = working_dir+"build"
command= "./configure --prefix="+build_dir+" --exec-prefix="+build_dir+" "

#check if this system is 64 bit
is_64bits = sys.maxsize > 2**32
if (is_64bits) :
	command= command+" --enable-64bit "

subprocess.call(command.split())
subprocess.call("make")
command="make install"
status = subprocess.call(command.split())

#done
if(status==0):
	print "======================"
	print "finished installation"
	print "======================"
	alias_path = working_dir+"/antlrworks-1.4.3.jar"
	s = "alias antlrwors='java -jar "+alias_path+"'"
	print s
	print "#-------------------------"
else :
	
	print "======================"
	print"installation FAILED"
	print "======================"
	
print "\n\n"
