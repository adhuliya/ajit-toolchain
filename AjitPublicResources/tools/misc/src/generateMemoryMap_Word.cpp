#include <iostream>
#include<sstream>
#include<fstream> 
#include <stdint.h>
#include <map>
#include <stdio.h>
#include <malloc.h>

using namespace std;

uint32_t getSlice32(uint32_t reg, uint8_t h, uint8_t l)
{
        reg = reg << (31 - h);
        reg = reg >> (31 - h + l);
        return reg;
}


bool initializeMemory(string hex_dump_file)
{
	ifstream infile;
	infile.open(hex_dump_file.c_str(), ifstream::in);

	if(!infile.is_open())
	{
		cerr<<"\nERROR: Could not open file for initializing memory";
		cerr<<"\nExiting Simulation";
		return false;
	}
	else
	{
		unsigned int count=0;	//total number of words stored in memory
		
		//values parsed line by line
		string line;
		uint32_t addr=0;
		uint32_t word[4];	
		map<uint32_t,uint32_t> memoryMap;

		
		while(infile.good())
		{
			getline(infile,line);
			if(!(line=="" || line ==" "))
			{
				stringstream ss;
				ss<<line;
				ss>>hex>>addr;
				for(int i=0;i<=3;i++)
					ss>>hex>>word[i];

				memoryMap[addr] = word[0];
				memoryMap[addr+4] = word[1];
				memoryMap[addr+8] = word[2];
				memoryMap[addr+12] = word[3];
			}
		}
		infile.close();

		int j;


		for(map<uint32_t,uint32_t>::const_iterator it = memoryMap.begin();it != memoryMap.end(); ++it)
		{
			fprintf(stdout, "%x\t%x\n",it->first,it->second);
		}
	}
}

int main(int argc, char **argv)
{
        if (!(argc == 2))
        {
                fprintf(stderr,"Provide hex-map file as input\n");
                fprintf(stderr,"Eg: ./testbench_sw main_memorymap.hex\n");
        }
	else
	{

        	string mmapfile = argv[1];

		initializeMemory(mmapfile);
	}

	return 0;
}
