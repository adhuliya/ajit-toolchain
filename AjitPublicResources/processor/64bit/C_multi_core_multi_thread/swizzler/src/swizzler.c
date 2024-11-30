#include "swizzler2.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// function to calculate the index corresponding to minimum element of an array
int64_t argmin(uint64_t* temp, int num_elements) {
    int min_index = 0;
    for (int i = 1; i < num_elements; i++) {
        if (temp[i] < temp[min_index]) {
            min_index = i;
        }
    }
    return min_index;
}

// function to initialise the record
void initSwizzler(SwizzlerRecord* sr) {
    for (int i = 0; i < queue_size; i++) {
        sr->a[i][0] = 0; // initially a contains 0's
        sr->a[i][1] = 0;
    }
    sr->front_a = queue_size;
    sr->rear_a = queue_size;
    
    for (int i = 0; i < no_sets; i++) {
        for (int j = 0; j < set_size; j++) {
            sr->M[i][j] = 0;
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

// insertion into the queue.
void queue_in(uint64_t (*queue)[2], 
			int* front,  
			int* rear, 
			uint64_t num1,  // new entry is num1, num2
			uint64_t num2, 
			uint64_t* old_num1,  // data overwritten by num1, num2
			uint64_t* old_num2) 
{
    *old_num1 = 0;
    *old_num2 = 0;
    // Check if the queue is full
    if ((*rear + 1) % queue_size == *front) {
        // Queue is full, so we remove the element at the front
        *old_num1 = queue[*front][0];  // Return the pair at the front
        *old_num2 = queue[*front][1];
        *front = (*front + 1) % queue_size;  // Move the front pointer forward (circular)
    }
    
    // Handle the first insertion case (queue is empty)
    if (*front == queue_size) {
        *front = 0;
        *rear = 0;  // Set both front and rear to 0 when first element is added
    } else {
        *rear = (*rear + 1) % queue_size;  // Increment rear and wrap around if necessary
    }
    
    // Insert the pair of values at the rear of the queue
    queue[*rear][0] = num1;  // Insert the first element in the pair at the rear
    queue[*rear][1] = num2;  // Insert the second element in the pair at the rear
}

//
// What does this do?
//
int processAddress (SwizzlerRecord* sr, 
			uint8_t   read_write_bar,
			uint64_t  address, 
			uint64_t* dword_h, 
			uint64_t* dword_l)
{
	// returns immedatialy if address 0 is given
	if (address == 0){
		*newly_mapped_address = 0;
		return 0;
	}
	// Code for updating addr_new
	*newly_mapped_address = address;
	uint64_t addr_new = address;
	int Q_in = 0;
	for (; Q_in < queue_size; Q_in ++){
		if (sr->a[Q_in][0] == address){
			*newly_mapped_address = sr->a[Q_in][1];
			addr_new = sr->a[Q_in][1];
			break;
		}
	}
	Q_in = 0;
	for (; Q_in < queue_size; Q_in ++){
		if (sr->a[Q_in][1] == address){
			*newly_mapped_address = sr->a[Q_in][0];
			addr_new = sr->a[Q_in][0];
			break;
		}
	}
	
	uint64_t Ms = mp; // role of Ms defined below
	uint64_t broad_set = addr_new % no_sets; // identifies the set number of each address by simple modulo operation
	
	// Ms points to the index of the memory where the new_address and stored address match. If they dont match in entire M, then it stays at mp
	for (int j = 0; j < set_size; j++){
		if(sr->M[broad_set][j] == addr_new){
			Ms = broad_set*set_size + j;
			break;
		}
	}
	
	uint64_t temp[set_size]; // temporary array to just store the least counts of the relevant broad set in which addr lies
	uint64_t temp2 = sr-> LC[broad_set]; // temporarorily stores value of Least count of the relevant broad set in which addr lies
	uint64_t addr_update = 0; // addr_update holds addr_new if it is repeated too often, else just holds 0
	
	
	if (Ms == mp){// things to do if the new_address wasnt found anywhere in the memory
		sr->M[broad_set][temp2] = addr_new; // Store the new address inplace of address with least life
		sr->C[broad_set*set_size + temp2] = 1; // Make the corresponding counter as 1
		//Loop to Initialise the life of that stored addr as L and decrement the life of rest of the addresses given they are not 0 or 1
		for (int j = 0; j < mp; j++){
			if (j == (broad_set*set_size + temp2)){
				sr->lc[j] = L;
			}
			else if (sr->lc[j] != 1 && sr->lc[j] != 0){// Note: this ensures that a memeory location which never had an addr stored in it has always less life (0) than a location whose address life has expired(1) thus giving priority to locations which never had addr's
				sr->lc[j] --;
			}
		}
		// loop to evaluate temp as defined above
		for (int i = 0; i < set_size; i++) {
    		temp[i] = sr->lc[broad_set * set_size + i];
		}
		sr->LC[broad_set] = argmin(temp, set_size); // Recompute the LC as minimum of all life counters (lc's)
	} else { // # the following statements execute if the same addr_new has been found in location Ms
		//printf("C: %lu\n", sr->C[Ms]);
		if (sr->C[Ms] != Cth){ //  if the counter of that location has not reached threshold value then do the following
			sr->C[Ms] ++; // Incrmement the counter
			// loop to Initialise the life back to L of that location and decrement life of all others given they are not 0 or 1
			for (int j = 0; j < mp; j++){
				if (j == Ms){
					sr->lc[j] = L;
				}
				else if (sr->lc[j] != 1 && sr->lc[j] != 0){
					sr->lc[j] --;
				}
			}
			
			if ((Ms - broad_set*set_size) == sr->LC[broad_set]){ //If LC itself was initialised back to L then recompute LC as minimum of all life counters (lc's)
			// loop to reevaluate temp
				for (int i = 0; i < set_size; i++) {
    				temp[i] = sr->lc[broad_set * set_size + i];
					}
				sr->LC[broad_set] = argmin(temp, set_size); // Recompute the LC as minimum of all life counters (lc's)
				}
		} else { // If counter of that location has reached its threshold then do the following to effecively remove that address from memory and give it for remapping
		//printf("threshold: %lu\n", sr->C[Ms]); //TODO
		sr->C[Ms] = 0; // Make the counter as 0
		sr->lc[Ms] = 0; // Make the life counter 0 signifying empty location
		sr->LC[broad_set] = Ms - broad_set*set_size; // Since lc is zero, LC will point to it
		sr->M[broad_set][Ms - broad_set*set_size] = 0; // Erase the contents of that memory
		addr_update = address; // As discussed above give addr_update the value of that address for remapping

		}
	}
	
	if(addr_update != 0){ //This logic updates the mappings ( ie the b cloumn in a -> b )
		srand(clock()); // To generate a random number seed
		uint64_t rand_address = rand() % (memory_size-1) + 1;
		uint64_t Q_in1 = 0;
		uint64_t Q_in2 = 0;
		for (; Q_in1 < queue_size; Q_in1 ++){
			if (sr->a[Q_in1][0] == address){
				break;
			}
		}
		if (Q_in1 == queue_size){
			Q_in1 = 0;
			for (; Q_in1 < queue_size; Q_in1 ++){
				if (sr->a[Q_in1][1] == address){
					break;
				}
			}
		}
		for (; Q_in2 < queue_size; Q_in2 ++){
			if (sr->a[Q_in2][0] == rand_address){
				break;
			}
		}
		if (Q_in2 == queue_size){
			Q_in2 = 0;
			for (; Q_in2 < queue_size; Q_in2 ++){
				if (sr->a[Q_in2][1] == rand_address){
					break;
				}
			}
		}
		if (Q_in1 != queue_size){
			if(Q_in2 != queue_size){
				if(sr->a[Q_in1][0] == address){
					*revert_p = sr->a[Q_in1][1];
					sr->a[Q_in1][1] = rand_address;
				}else if(sr->a[Q_in1][1] == address){
					*revert_p = sr->a[Q_in1][0];
					sr->a[Q_in1][0] = rand_address;
				}else{printf("bug");
				}
				if(sr->a[Q_in2][0] == rand_address){
					*revert_s = sr->a[Q_in2][1];
					*s = rand_address;
					sr->a[Q_in2][1] = 0;
					sr->a[Q_in2][0] = 0;
				}else if(sr->a[Q_in1][1] == rand_address){
					*revert_s = sr->a[Q_in2][0];
					*s = rand_address;
					sr->a[Q_in2][1] = 0;
					sr->a[Q_in2][0] = 0;
				}else{printf("bug");
				}
			}else{
				if(sr->a[Q_in1][0] == address){
					*revert_p = sr->a[Q_in1][1];
					sr->a[Q_in1][1] = rand_address;
				}else if(sr->a[Q_in1][1] == address){
					*revert_p = sr->a[Q_in1][0];
					sr->a[Q_in1][0] = rand_address;
				}else{printf("bug");}
			}
		}else if(Q_in2 != queue_size){
			if(sr->a[Q_in2][0] == rand_address){
				*revert_s = sr->a[Q_in2][1];
				*s = rand_address;
				sr->a[Q_in2][1] = address;
			}else if(sr->a[Q_in2][1] == rand_address){
				*revert_s = sr->a[Q_in2][0];
				*s = rand_address;
				sr->a[Q_in2][0] = address;
			}else{printf("bug");}
		}else{
		uint64_t t1, t2 = 0;
		queue_in(sr->a, &sr->front_a, &sr->rear_a, address, rand_address, &t1, &t2);
		*revert_p = t1;
		*revert_s = t2;
		} 
		*newly_mapped_address = rand_address;
		return 1;
	}
	return 0;
	
}
