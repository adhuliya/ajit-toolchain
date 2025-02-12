// swizzler.c
//
// Model for the swizzler for shuffling memory addresses for use in hardware security
//
// AUTHOR : Manan Garg

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "swizzler.h"
#include "memory.h"

uint64_t Cth, memory_size, L;
int mp, set_size, no_sets, queue_size;

// function to calculate the index corresponding to minimum element of an array (temp)
// used for updating the LC pointer to point to the element with the least life (lc)
int64_t argmin(uint64_t* temp, int number_of_elements) {
    int min_index = 0;
    for (int i = 1; i < number_of_elements; i++) {
        if (temp[i] < temp[min_index]) {
            min_index = i;
        }
    }
    return min_index;
}

// function to initialise the swizzler record
//    Reads three numbers from file file_name
//          Cth
//          memory_size
//          rng seed.
void initSwizzler(SwizzlerRecord* sr, char* initialize_file_name) {
	
	// steps to extract the value of Cth and memory_size out of the given file
	FILE *file;
	file = fopen(initialize_file_name, "r");
	if (file == NULL){
		printf("Error, could not find initialize file");
		fclose(file);
		return;
	}
	
	if(fscanf(file, "%lu", &Cth) != 1){
		printf("Error, could not read Cth\n");
		fclose(file);
		return;
	}	
	if(fscanf(file, "%lu", &memory_size) != 1){
		printf("Error, could not read memory size\n");
		fclose(file);
		return;
	}
	if(fscanf(file, "%d", &no_sets) != 1){
		printf("Error, could not read no_sets\n");
		fclose(file);
		return;
	}
	if(fscanf(file, "%d", &set_size) != 1){
		printf("Error, could not read set_size\n");
		fclose(file);
		return;
	}
	if(fscanf(file, "%d", &queue_size) != 1){
		printf("Error, could not read queue_size\n");
		fclose(file);
		return;
	}
	if(fscanf(file, "%d", &(sr->swizzler_seed)) != 1){
		printf("Error, could not read swizzler seed\n ");
		fclose(file);
		return;
	}
	if(fscanf(file, "%lu", &L) != 1){
		printf("Error, could not read L\n ");
		fclose(file);
		return;
	}
	mp = no_sets*set_size;
	fclose(file);
	
	sr->a = (uint64_t*)malloc((2*queue_size) * sizeof(uint64_t));
	sr->M = (uint64_t*)malloc(mp * sizeof(uint64_t));
	sr->lc = (uint64_t*)malloc(mp * sizeof(uint64_t));
	sr->C = (uint64_t*)malloc(mp * sizeof(uint64_t));
	sr->LC = (uint64_t*)malloc(no_sets * sizeof(uint64_t));
	
    for (int i = 0; i < queue_size; i++) {
    	// initialise 'a' (FIFO queue) to contain all 0's
        __a(sr,i,0) = 0;
        __a(sr,i,1) = 0; 
    }
    
    // front and rear pointers of queue will be properly initialised in the function
    // queue_in 
    sr->front_a = queue_size;
    sr->rear_a = queue_size;
    
    // initialise M (Temporary memory), lc (life counter), C (repetetion counter),
    // LC (pointer to the element with least life per set) to zero
    for (int i = 0; i < no_sets; i++) {
        for (int j = 0; j < set_size; j++) {
            __M(sr,i,j) = 0;
        }
    }
    for (int i = 0; i < mp; i++) {
        sr->lc[i] = 0;
    }
    for (int i = 0; i < mp; i++) {
        sr->C[i] = 0;
    }
    for (int i = 0; i < no_sets; i++) {
        sr->LC[i] = 0;
    }
}

void setRNGSeed (SwizzlerRecord* sr)
{
	srand (sr->swizzler_seed);
}

// Function to add a pair of elements (num1, num2) to the queue ('a') and storing the
// removed pair of elements (if queue is full) in (old_num1, old_num2)
void queue_in(SwizzlerRecord* sr, int* front, int* rear, uint64_t num1, uint64_t num2, uint64_t* old_num1, uint64_t* old_num2) {
    *old_num1 = 0;
    *old_num2 = 0;
    // Checking if the circular queue is full 
    if ((*rear + 1) % queue_size == *front) {
        // Queue is full, so we remove the element at the front of the queue
        *old_num1 = __a(sr,*front,0);  // Return the pair at the front
        *old_num2 = __a(sr,*front,1);
        *front = (*front + 1) % queue_size;  // Move the front pointer forward 
    }
    
    if (*front == queue_size) {
    // initialise both front and rear pointers to 0 if queue is empty
        *front = 0;
        *rear = 0;  
    } else {
    // If queue is not empty then Increment rear and wrap around if necessary
        *rear = (*rear + 1) % queue_size;
    }
    
    // Insert the pair of values at the rear of the queue
    __a(sr,*rear,0) = num1;  // Insert the first element in the pair at the rear
    __a(sr,*rear,1) = num2;  // Insert the second element in the pair at the rear
}

// Main function for checking if address is repeated frequently, shuffling the address
// mapping if necessary and doing reads and writes to the memory
void processAddress (SwizzlerRecord* sr, 
			uint8_t   read_write_bar,
			uint64_t  address, 
			uint64_t* dword_h, 
			uint64_t* dword_l)
{
	// Code for updating addr_new which is initiased to the root address
	uint64_t addr_new = address;
	int Q_in = 0; // Integer to keep track of index of queue where address is stored
	
	//printf("%lu \n", address);
	
	// 2 for loops to search both the first and second column vectors if address
	// is there in queue and storing the mapping of address 
	// (present in the other coloumn) in addr_new
	for (; Q_in < queue_size; Q_in ++){
		if (__a(sr,Q_in,0) == address){
			addr_new = __a(sr,Q_in,1);
			//printf("remapped to %lu \n", addr_new);
			break;
		}
	}
	Q_in = 0;
	for (; Q_in < queue_size; Q_in ++){
		if (__a(sr,Q_in,1) == address){
			addr_new = __a(sr,Q_in,0);
			//printf("remapped to %lu \n", addr_new);
			break;
		}
	}
	
	// Doing the required read or write of the supplied data dword_h and dword_l
	// by using the addr_new found out above
	if(read_write_bar == 1){
		*dword_h = getDoubleWordInMemory ((uint32_t) (addr_new));
		*dword_l = getDoubleWordInMemory ((uint32_t) (addr_new + 8));
		
	}else{
		setDoubleWordInMemory ((uint32_t)(addr_new), *dword_h, 0xff);
		setDoubleWordInMemory ((uint32_t)(addr_new + 8), *dword_l, 0xff);
		
	}
	
	// Address 0 will cause problems in the following code hence the 
	// swizzler doesnt shuffle address 0 with any other address
	if (address == 0){return;}
	
	uint64_t Ms = mp; // role of Ms defined below
	
	// identifies the set number of each address by simple modulo operation.
	// Address is divided by 16 since only quad word writing and reading 
	// is supported so address will always be a multiple of 16
	uint64_t broad_set = (addr_new/16) % no_sets;
	
	//printf("set number is %lu and its LC is %lu with new address / 16 as %lu \n", broad_set, sr->LC[broad_set], addr_new/16);
	
	// Ms points to the index of the memory where the new_address and stored
	// address match. If they dont match in entire M, then it stays at mp
	for (int j = 0; j < set_size; j++){
		if(__M(sr,broad_set,j) == addr_new){
			Ms = broad_set*set_size + j;
			break;
		}
	}
	
	// temporary array to just store the life's of all addresses in the 
	// relevant broad set in which the new_addr lies
	uint64_t temp[set_size];
	
	// temporarorily stores the value of Least Life pointer of the 
	// relevant broad set in which addr lies
	uint64_t temp2 = sr-> LC[broad_set];
	
	// addr_update holds the root addr if it's mapped address (addr_new))
	// is repeated too often, else just holds 0
	uint64_t addr_update = 0;
	
	
	if (Ms == (uint64_t)mp)
	// Operations to do if the new_address wasnt found anywhere in the memory
	{
		//printf("new address !\n");
		
		// Store the new address inplace of address with least life
		__M(sr,broad_set,temp2) = addr_new;
		
		// Make the corresponding counter as 1. NOTE C expects an index
		// corresponding to the full temp Memory (i.e. mp) but temp2 is an
		// index corresponding to element within a single set
		sr->C[broad_set*set_size + temp2] = 1;
		
		// Loop to Initialise the life of that stored addr as L and decrement
		// the life of rest of the addresses given the life is not 0 or 1 (
		// explained below) noting indexing for temp2 as above and for lc as
		// elements within the temporary memory which stores all the elements
		for (int j = 0; j < mp; j++){
			if ((uint64_t)j == (broad_set*set_size + temp2)){
				sr->lc[j] = L;
			}
			else if (sr->lc[j] != 1 && sr->lc[j] != 0){
		// Note: this ensures that a memory location which never had an addr
		// stored in it has always less life (0) than a location whose address
		// life has expired(1) thus giving priority to locations which never
		// had addr's
				sr->lc[j] --;
			}
		}
		
		// loop to evaluate temp as defined above keeping in mind lc also
		// expects a global index (corresponding to mp) whereas temp expects
		// an index corresponding to set_size
		for (int i = 0; i < set_size; i++) {
    			temp[i] = sr->lc[broad_set * set_size + i];
		}
		
		// Recompute the LC as minimum of all life counters (lc's)
		sr->LC[broad_set] = argmin(temp, set_size);
	} else
	// if the same addr_new has been found in location Ms
	{
		//printf("same addr found C: %lu\n", sr->C[Ms]);
		//printf("addr is %lu \n", addr_new);
		
		if (sr->C[Ms] != Cth)
		// if the counter of that location has not reached threshold value
		{
			//printf("thr not reached \n");
			
			// Incrmement the counter
			sr->C[Ms] ++ ;
			
			// loop to Initialise the life back to L of that location and
			// decrement life of all others given they are not 0 or 1
			for (int j = 0; j < mp; j++){
				if ((uint64_t)j == Ms){
					sr->lc[j] = L;
				}
				else if (sr->lc[j] != 1 && sr->lc[j] != 0){
					sr->lc[j] --;
				}
			}
			
			if ((Ms - broad_set*set_size) == sr->LC[broad_set])
			// If LC itself was initialised back to L then recompute LC 
			// as minimum of all life counters (lc's)
			{
				// loop to reevaluate temp
				for (int i = 0; i < set_size; i++) {
    					temp[i] = sr->lc[broad_set * set_size + i];
					}
				// Recompute the LC as minimum of all life counters
				sr->LC[broad_set] = argmin(temp, set_size);
				}
		} else 
		// If counter of that location has reached its threshold then 
		// remove that address from memory and give it for remapping
		{ 
		//printf("threshold reached : %lu\n", sr->C[Ms]);
		
		// Make the repetiton and life counter as 0 signifying empty location
		// and point LC of that set to that location
		sr->C[Ms] = 0;
		sr->lc[Ms] = 0;
		sr->LC[broad_set] = Ms - broad_set*set_size;
		
		// Erase the contents of that memory location and give
		// the root address to addr_update for shuffling
		__M(sr,broad_set,(Ms - broad_set*set_size)) = 0;
		addr_update = address;
		}
	}
	
	if(addr_update != 0) 
	//This logic updates the mappings (i.e. pairs of elements in queue 'a')
	{
		//printf("shuffling memory.... \n");
		
		// generates a random number seed and makes a random address which
		// is always a multiple of 16 and strictly inbetween 0 and memory size
		uint64_t rand_address = ((rand() % ((memory_size - 1) / 16)) + 1) * 16;
		
		// To rectify the case if rand_address is equal to root address
		// by adding or subtracting 16 from rand_address ensuring the above
		// constraints
		if(rand_address == addr_update){
			if((rand_address + 16) < memory_size){
				rand_address = rand_address + 16 ;
			}else{rand_address = rand_address - 16;}
		}
		
		//printf("rand_address is %lu \n", rand_address);
		
		// Q_in1 and Q_in2 stores the index of root address and 
		// rand_address if they are already present in the queue
		int Q_in1 = 0;
		int Q_in2 = 0;
		
		// Use of case defined below, addr_c and addr_d will store the
		// respective old mappings of root address and rand_address 
		// if they are already present in the queue
		int Case = 0;
		uint64_t addr_c, addr_d = 0;
		
		// Logic to find Q_in1 and Q_in2 by parsing each coloumn vector of the
		// queue and searching first for root address and then for rand_address
		for (; Q_in1 < queue_size; Q_in1 ++){
			if (__a(sr,Q_in1,0) == address){
				break;
			}
		}
		if (Q_in1 == queue_size){
			Q_in1 = 0;
			for (; Q_in1 < queue_size; Q_in1 ++){
				if (__a(sr,Q_in1,1) == address){
					break;
				}
			}
		}
		for (; Q_in2 < queue_size; Q_in2 ++){
			if (__a(sr,Q_in2,0) == rand_address){
				break;
			}
		}
		if (Q_in2 == queue_size){
			Q_in2 = 0;
			for (; Q_in2 < queue_size; Q_in2 ++){
				if (__a(sr,Q_in2,1) == rand_address){
					break;
				}
			}
		}
		
		// Logic to update the addr_c, addr_d and the queue for 4 cases
		// depending on wether root address / rand_address found in queue or
		// not. This case is stored in the variable Case defined above
		if (Q_in1 != queue_size){
			if(Q_in2 != queue_size)
			// If both root and rand address are found, store mapping 
			// of root address in addr_c, mapping of rand_address in addr_d
			// Modify the queue as follows :-
		// Initial state: (root, c) (rand, d) | Final: (root, rand) (0, 0)
			{
				Case = 1;
				if(__a(sr,Q_in1,0) == address){
					addr_c = __a(sr,Q_in1,1);
					__a(sr,Q_in1,1) = rand_address;
				}else if(__a(sr,Q_in1,1) == address){
					addr_c = __a(sr,Q_in1,0);
					__a(sr,Q_in1,0) = rand_address;
				}else{printf("bug1");
				}
				if(__a(sr,Q_in2,0) == rand_address){
					addr_d = __a(sr,Q_in2,1);
					__a(sr,Q_in2,1) = 0;
					__a(sr,Q_in2,0) = 0;
				}else if(__a(sr,Q_in2,1) == rand_address){
					addr_d = __a(sr,Q_in2,0);
					__a(sr,Q_in2,1) = 0;
					__a(sr,Q_in2,0) = 0;
				}else{printf("bug2");
				}
			}else
			// If only root address is found, store mapping 
			// of root address in addr_c
			// Modify the queue as follows :-
		// Initial state: (root, c) | Final: (root, rand)
			{
				Case = 2;
				if(__a(sr,Q_in1,0) == address){
					addr_c = __a(sr,Q_in1,1);
					//printf("block 2 %lu %lu and addr c is %lu and addr is %lu \n", sr->a[Q_in1][1], sr->a[Q_in1][0], addr_c, address);
					__a(sr,Q_in1,1) = rand_address;
				}else if(__a(sr,Q_in1,1) == address){
					addr_c = __a(sr,Q_in1,0);
					//printf("block 2 %lu %lu and addr c is %lu and addr is %lu \n", sr->a[Q_in1][1], sr->a[Q_in1][0], addr_c, address);
					__a(sr,Q_in1,0) = rand_address;
				}else{printf("bug3");}
			}
		}else if(Q_in2 != queue_size)
		// If only rand address is found, store mapping 
			// of root address in addr_d
			// Modify the queue as follows :-
		// Initial state: (rand, d) | Final: (rand, root)
		{
			Case = 3;
			if(__a(sr,Q_in2,0) == rand_address){
				addr_d = __a(sr,Q_in2,1);
				__a(sr,Q_in2,1) = address;
			}else if(__a(sr,Q_in2,1) == rand_address){
				addr_d = __a(sr,Q_in2,0);
				__a(sr,Q_in2,0) = address;
			}else{printf("bug4");}
		}else
		// If neither root address nor rand_address is found, invoke the 
		// queue in function to add (root, rand) to the queue with addr_c
		// and addr_d to store the removed pair from the queue
		{
			Case = 4;
			uint64_t t1, t2 = 0;
			queue_in(sr, &sr->front_a, &sr->rear_a, address, rand_address, &t1, &t2);
			addr_c = t1;
			addr_d = t2;
		}
		uint64_t data1h, data1l, data2h, data2l, data3h, data3l, data4h, data4l = 0;
		//printf("Case is %d \n", Case);
		
		// Logic to remap the addresses as defined above in the actual memory
		// First, all the data from the location is read into temporary 
		// variables data*h and data*l and then written back to modified memory
		// locations
		switch (Case) {
        case 1:
        	//printf("addr_c is %lu and add_d is %lu \n",addr_c, addr_d);
        	data1h = getDoubleWordInMemory ((uint32_t)(address));
			data1l = getDoubleWordInMemory ((uint32_t)(address + 8));
			data2h = getDoubleWordInMemory ((uint32_t)(rand_address));
			data2l = getDoubleWordInMemory ((uint32_t)(rand_address + 8));
			data3h = getDoubleWordInMemory ((uint32_t)(addr_c));
			data3l = getDoubleWordInMemory ((uint32_t)(addr_c + 8));
			data4h = getDoubleWordInMemory ((uint32_t)(addr_d));
			data4l = getDoubleWordInMemory ((uint32_t)(addr_d + 8));
			
			setDoubleWordInMemory ((uint32_t)(address), data4h, 0xff);
			setDoubleWordInMemory ((uint32_t)(address + 8), data4l, 0xff);
			setDoubleWordInMemory ((uint32_t)(rand_address), data3h, 0xff);
			setDoubleWordInMemory ((uint32_t)(rand_address + 8),data3l, 0xff);
			setDoubleWordInMemory ((uint32_t)(addr_c), data1h, 0xff);
			setDoubleWordInMemory ((uint32_t)(addr_c + 8), data1l, 0xff);
			setDoubleWordInMemory ((uint32_t)(addr_d), data2h, 0xff);
			setDoubleWordInMemory ((uint32_t)(addr_d + 8), data2l, 0xff);
            break;
        case 2:
        	//printf("addr_c is %lu \n",addr_c);
        	data1h = getDoubleWordInMemory ((uint32_t)(address));
			data1l = getDoubleWordInMemory ((uint32_t)(address + 8));
			data2h = getDoubleWordInMemory ((uint32_t)(rand_address));
			data2l = getDoubleWordInMemory ((uint32_t)(rand_address + 8));
			data3h = getDoubleWordInMemory ((uint32_t)(addr_c));
			data3l = getDoubleWordInMemory ((uint32_t)(addr_c + 8));
			
			setDoubleWordInMemory ((uint32_t)(address), data2h, 0xff);
			setDoubleWordInMemory ((uint32_t)(address + 8), data2l, 0xff);
			setDoubleWordInMemory ((uint32_t)(rand_address), data3h, 0xff);
			setDoubleWordInMemory ((uint32_t)(rand_address + 8),data3l, 0xff);
			setDoubleWordInMemory ((uint32_t)(addr_c), data1h, 0xff);
			setDoubleWordInMemory ((uint32_t)(addr_c + 8), data1l, 0xff);
            break;
        case 3:
        	//printf("addr_d is %lu \n",addr_d);
        	data1h = getDoubleWordInMemory ((uint32_t)(address));
			data1l = getDoubleWordInMemory ((uint32_t)(address + 8));
			data2h = getDoubleWordInMemory ((uint32_t)(rand_address));
			data2l = getDoubleWordInMemory ((uint32_t)(rand_address + 8));
			data4h = getDoubleWordInMemory ((uint32_t)(addr_d));
			data4l = getDoubleWordInMemory ((uint32_t)(addr_d + 8));
			
			setDoubleWordInMemory ((uint32_t)(address), data4h, 0xff);
			setDoubleWordInMemory ((uint32_t)(address + 8), data4l, 0xff);
			setDoubleWordInMemory ((uint32_t)(rand_address), data1h, 0xff);
			setDoubleWordInMemory ((uint32_t)(rand_address + 8),data1l, 0xff);
			setDoubleWordInMemory ((uint32_t)(addr_d), data2h, 0xff);
			setDoubleWordInMemory ((uint32_t)(addr_d + 8), data2l, 0xff);
            break;
        case 4:
        	//printf("addr_c is %lu and add_d is %lu \n",addr_c, addr_d);
        	data1h = getDoubleWordInMemory ((uint32_t)(address));
			data1l = getDoubleWordInMemory ((uint32_t)(address + 8));
			data2h = getDoubleWordInMemory ((uint32_t)(rand_address));
			data2l = getDoubleWordInMemory ((uint32_t)(rand_address + 8));
			
			setDoubleWordInMemory ((uint32_t)(address), data2h, 0xff);
			setDoubleWordInMemory ((uint32_t)(address + 8), data2l, 0xff);
			setDoubleWordInMemory ((uint32_t)(rand_address), data1h, 0xff);
			setDoubleWordInMemory ((uint32_t)(rand_address + 8),data1l, 0xff);
			if(addr_c != 0 && addr_d != 0){
				data3h = getDoubleWordInMemory ((uint32_t)(addr_c));
				data3l = getDoubleWordInMemory ((uint32_t)(addr_c + 8));
				data4h = getDoubleWordInMemory ((uint32_t)(addr_d));
				data4l = getDoubleWordInMemory ((uint32_t)(addr_d + 8));

				setDoubleWordInMemory ((uint32_t)(addr_c), data4h, 0xff);
				setDoubleWordInMemory ((uint32_t)(addr_c + 8), data4l, 0xff);
				setDoubleWordInMemory ((uint32_t)(addr_d), data3h, 0xff);
				setDoubleWordInMemory ((uint32_t)(addr_d + 8), data3l, 0xff);
			}
			break;
	default:
			printf("bug5\n");
			break;
		}
		
		return;
	}
	return;

}

void freeSwizzler (SwizzlerRecord* sr){
	free(sr->M);  // Free the allocated memory
	sr->M = NULL;
	free(sr->LC);  // Free the allocated memory
	sr->LC = NULL;
	free(sr->lc);  // Free the allocated memory
	sr->lc = NULL;
	free(sr->C);  // Free the allocated memory
	sr->C = NULL;
}
