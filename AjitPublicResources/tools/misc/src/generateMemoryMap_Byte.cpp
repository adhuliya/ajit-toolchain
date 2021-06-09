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
		map<uint32_t,uint8_t> memoryMap;

		
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

				memoryMap[addr] = getSlice32(word[0],31,24);
				memoryMap[addr+1] = getSlice32(word[0],23,16);
				memoryMap[addr+2] = getSlice32(word[0],15,8);
				memoryMap[addr+3] = getSlice32(word[0],7,0);

				memoryMap[addr+4] = getSlice32(word[1],31,24);
				memoryMap[addr+5] = getSlice32(word[1],23,16);
				memoryMap[addr+6] = getSlice32(word[1],15,8);
				memoryMap[addr+7] = getSlice32(word[1],7,0);

				memoryMap[addr+8] = getSlice32(word[2],31,24);
				memoryMap[addr+9] = getSlice32(word[2],23,16);
				memoryMap[addr+10] = getSlice32(word[2],15,8);
				memoryMap[addr+11] = getSlice32(word[2],7,0);

				memoryMap[addr+12] = getSlice32(word[3],31,24);
				memoryMap[addr+13] = getSlice32(word[3],23,16);
				memoryMap[addr+14] = getSlice32(word[3],15,8);
				memoryMap[addr+15] = getSlice32(word[3],7,0);

			}
		}
		infile.close();

		int j;

		//for(j = 0; j < memoryMap.size(); j++)
			//printf("%x\n",memoryMap[j]);

		for(map<uint32_t,uint8_t>::const_iterator it = memoryMap.begin();it != memoryMap.end(); ++it)
		{
    			//cout << it->first << " " << it->second << "\n";
			fprintf(stdout,"%x\t%x\n",it->first,it->second);
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
		string file_name = argv[1];
		initializeMemory(file_name);
	}

	return 0;
}
