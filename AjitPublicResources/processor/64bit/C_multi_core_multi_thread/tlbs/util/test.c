#include <stdlib.h>
#include <stdio.h>
#include <tlbs.h>

#define MAXVAL 64
int main(int argc, char* argv[])
{
	

	fprintf(stderr,"Usage: %s [nseeds]\n", argv[0]);
	int nseeds = 1;

	if(argc > 1)
		nseeds = atoi(argv[1]);

	fprintf(stderr,"nseeds = %d\n", nseeds);

	int err  = 0;
	uint8_t I,J;
			
	setAssociativeMemory* m = findOrAllocateSetAssociativeMemory(0,8,8,6,3); 

	int seed;
	for(seed = 0; seed < nseeds; seed++)
	{
		// write into all slots.
		fprintf(stderr,"Info: write into all slots (seed=%d)\n", seed);
		for(I = 0; I < MAXVAL; I++)
		{
			uint8_t lv = 0;
			uint64_t ld  = 0;
			if(I&0x1)
				writeIntoSetAssociativeMemory(m, I+seed, I, I&0x7);
			else
			{
				setAssociativeMemoryCModel(
						0,8,8,6,3, 
						1, // ignore collisions.
						0, 0, 1, 	     // clear, erase, write
						I, I+seed, I & 0x7,  // write data, tag, set-id
						0, 0, 0,	     // lookup-flag, tag, set-id
						&lv, &ld);
				if(lv)
				{
					fprintf(stderr,"Error: received lookup_valid while writing (I=%d)\n", I);
					err = 1;
				}
			}
		}

		// lookup all slots.
		fprintf(stderr,"Info: lookup all slots (seed=%d)\n", seed);
		for(I = 0; I < MAXVAL; I++)
		{
			uint8_t lv = 0;
			uint64_t ld  = 0;
			if(I&0x1)
				lv = lookupSetAssociativeMemory(m, I+seed, I&0x7, &ld);
			else
				setAssociativeMemoryCModel(
						0,8,8,6,3,     // configuration
						0, // do not ignore collisions
						0, 0, 0, 	// clear, erase, write
						0, 0, 0, 	// write-data, tag, set-id
						1, I+seed, I & 0x7,  // lookup-flag, tag, set-id
						&lv, &ld);

			if(!lv)
			{
				fprintf(stderr,"Error: received lookup_invalid while looking up (I=%d)\n", I);
				err = 1;
			}
			if(ld != I)
			{
				fprintf(stderr,"Error: incorrect lookup_data 0x%x (exp: 0x%x)  (I=%d)\n", 
						(uint32_t) ld, I, I);
				err = 1;
			}
		}

		// erase all 
		fprintf(stderr,"Info: erase all slots (seed=%d)\n", seed);
		for(I = 0; I < MAXVAL; I++)
		{
			uint8_t lv = 0;
			uint64_t ld  = 0;
			setAssociativeMemoryCModel(
					0,8,8,6,3, 	// config
					1,  // ignore collisions
					0, 1, 0, // clear erase write
					0, (I+seed),  I&0x7,  // write-data, tag, set-id
					0, 0, 0, 	// lookup flag, tag, set-id
					&lv, &ld);
			if(lv)
			{
				fprintf(stderr,"Error: received valid lookup while erasing (I=%d)\n", I);
				err = 1;
			}
		}

		// lookup all slots.
		fprintf(stderr,"Info: post erase lookup all slots (seed=%d)\n", seed);
		for(I = 0; I < MAXVAL; I++)
		{
			uint8_t lv = 0;
			uint64_t ld  = 0;
			setAssociativeMemoryCModel(
					0,8,8,6,3,     // configuration
					1, // ignore collisions
					0, 0, 0, 	// clear, erase, write
					0, 0, 0, 	// write-data, tag, set-id
					1, I+seed, I & 0x7,  // lookup-flag, tag, set-id
					&lv, &ld);
			if(lv)
			{
				fprintf(stderr,"Error: post erase received lookup valid while looking up (I=%d)\n", 
						I);
				err = 1;
			}
		}

	}

	if(err) fprintf(stderr,"FAILURE\n"); else fprintf(stderr,"SUCCESS\n"); return(err); }

