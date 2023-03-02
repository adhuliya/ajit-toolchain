#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "tlbs.h"

setAssociativeMemory* mem_list = NULL;



void generateName(setAssociativeMemory* ms, char* nbuf)
{
	if(ms != NULL)
	{
		sprintf(nbuf,"m_%d_%d_%d_%d_%d",
				ms->model_id, ms->tag_width, ms->data_width,
				ms->log_mem_size, ms->log_set_size);
	}
}


int twoPower(int x)
{
	if(x < 0)
		return 0;
	else if (x == 0)
		return(1);
	else if (x == 1)
		return(2);
	else
	{
		int y = x/2;
		int r = x - (2*y);
		int w = twoPower(y);
		w = w*w;
		if(r == 1)
			return(w*2);
		else
			return(w);
	}
}


setAssociativeMemory* findOrAllocateSetAssociativeMemory(uint8_t model_id,
		uint8_t tag_width, uint8_t data_width,
		uint8_t log_mem_size, uint8_t log_set_size)
{
	setAssociativeMemory* rval = NULL;
	setAssociativeMemory* ml;
	for(ml = mem_list; ml != NULL; ml = ml->next)
	{
		if( (ml->model_id == model_id) &&
				(ml->tag_width == tag_width) &&
				(ml->data_width == data_width) &&
				(ml->log_mem_size == log_mem_size) &&
				(ml->log_set_size == log_set_size))
		{

			rval = ml;
			break;
		}
	}
	if(rval == NULL)
	{
		rval = (setAssociativeMemory*) malloc(sizeof(setAssociativeMemory));

		rval->model_id = model_id;
		rval->tag_width = tag_width;
		rval->data_width = data_width;

		int mem_size = twoPower(log_mem_size);
		rval->log_mem_size = log_mem_size;
		rval->mem_size  = mem_size;

		int set_size = twoPower(log_set_size);
		rval->log_set_size = log_set_size;
		rval->set_size = set_size;

		rval->log_number_of_sets = (log_mem_size - log_set_size);

		// number of sets-1
		rval->set_index_mask = (mem_size/set_size)-1;


		rval->valids = (uint8_t*) malloc(mem_size*sizeof(uint8_t));
		rval->tags   = (uint64_t*) malloc(mem_size*sizeof(uint64_t));
		rval->data   = (uint64_t*) malloc(mem_size*sizeof(uint64_t));

		int I;
		for(I = 0; I < mem_size; I++)
		{
			rval->valids[I] = 0;
			rval->tags[I] = 0;
			rval->data[I] = 0;
		}

		int nsets = twoPower(log_mem_size  - log_set_size);

		rval->last_modified_index_per_set = (uint16_t*) malloc (nsets*sizeof(uint16_t));
		for(I = 0; I < nsets; I++)
		{
			rval->last_modified_index_per_set[I] = rval->set_size-1; 
		}

		pthread_mutex_init (&(rval->pm), NULL);

		rval->next = mem_list;
		mem_list = rval;
	}
	return(rval);
}

int searchForTag(setAssociativeMemory* m, int set_id, uint64_t tag)
{
	int b = (set_id*m->set_size);
	int I;
	int ret_val = -1;
	for(I = 0; I < m->set_size; I++)
	{
		int ti = b + I;

		assert(ti < m->mem_size);

		if(m->valids[ti] && (m->tags[ti] == tag))
		{
			ret_val = ti;
			break;
		}
	}
	return(ret_val);
}

// return lookup valid, data in lookup_data..
int lookupSetAssociativeMemory(setAssociativeMemory* m, uint64_t lookup_tag, uint16_t lookup_set_id,
		uint64_t* lookup_data)
{
	uint8_t lv = 0;
	operateOnSetAssociativeMemory(m, 0,
			0,0,0,
			0,0,0,
			1,lookup_tag, lookup_set_id,
			&lv, lookup_data);
	return(lv);
}

void writeIntoSetAssociativeMemory(setAssociativeMemory* m, uint64_t write_tag, uint64_t write_data, 
		uint16_t write_set_id)
{
	uint8_t lv;
	uint64_t ld;
	operateOnSetAssociativeMemory(m,0,
			0,0,1,
			write_data,write_tag,write_set_id,
			0,0,0,
			&lv, &ld);
}
void eraseFromSetAssociativeMemory(setAssociativeMemory* m, uint64_t write_tag, uint16_t write_set_id)
{
	uint8_t lv;
	uint64_t ld;
	operateOnSetAssociativeMemory(m,0,
			0,1,0,
			0,write_tag,write_set_id,
			0,0,0,
			&lv, &ld);
}

void clearSetAssociativeMemory(setAssociativeMemory* m)
{
	uint8_t lv;
	uint64_t ld;
	operateOnSetAssociativeMemory(m,0,
			1,0,0,
			0,0,0,
			0,0,0,
			&lv, &ld);
}


void operateOnSetAssociativeMemory(setAssociativeMemory* m, 
		uint8_t ignore_collisions,
		uint8_t clear_flag,
		uint8_t erase_flag, 
		uint8_t write_flag,
		uint64_t write_data,uint64_t write_tag, 
		uint16_t write_set_id,
		uint8_t lookup_flag, uint64_t lookup_tag, uint16_t lookup_set_id, 
		uint8_t* lookup_valid, uint64_t* lookup_data)
{

	pthread_mutex_lock (&(m->pm));

	if(lookup_valid != NULL)
		*lookup_valid = 0;
	if(lookup_data != NULL)
		*lookup_data = 0;

	int collision = (!ignore_collisions && write_flag && !erase_flag && !erase_flag && 
			(lookup_set_id == write_set_id) && (lookup_tag == write_tag));

	if(clear_flag)
	{
		int I;
		for(I = 0; I < m->mem_size; I++)
			m->valids[I] = 0;
	}

	if (lookup_flag) 
	{
		if(collision)
		{
			if(lookup_valid != NULL)
				*lookup_valid = 1;
			if(lookup_data != NULL)
				*lookup_data  = write_data;
			fprintf(stderr,"Info: lookup/write collision in set %d, tag=0x%x, data=0x%llx\n",
					lookup_set_id, lookup_tag, write_data);
		}
		else
		{
			int li = searchForTag(m, lookup_set_id, lookup_tag);
			if(li >= 0 )
			{
				assert(li < m->mem_size);

				if(lookup_valid != NULL)
					*lookup_valid = 1;
				if(lookup_data != NULL)
					*lookup_data = m->data[li];

#ifdef TLBS_DEBUG
				char nbuf[256];
				generateName(m, nbuf);
				fprintf(stderr,"Info: successful lookup in set %d, li=%d, tag=0x%x, data=0x%x\n",
						lookup_set_id, li, lookup_tag, *lookup_data);
#endif
			}
		}
	}

	if(write_flag || erase_flag)
	{
		int wi = searchForTag(m, write_set_id, write_tag);
		if(wi >= 0)
		{
			assert(wi < m->mem_size);

			if(erase_flag)
			{
				m->valids[wi] = 0;
			}
			else
			{
				m->valids[wi] = 1;
				m->data[wi] = write_data;
				m->tags[wi] = write_tag;

#ifdef TLBS_DEBUG
				char nbuf[256];
				generateName(m, nbuf);
				fprintf(stderr,"Info: wrote in set %d, wi=%d, tag=0x%x, data=0x%x\n",
						write_set_id, wi, write_tag, write_data);
#endif
			}
		}
		else if (!erase_flag)
		{
			int ni = (m->last_modified_index_per_set[write_set_id] + 1) % m->set_size;
			int wi = (write_set_id * m->set_size) + ni;

			assert(wi < m->mem_size);

			m->valids[wi] = 1;
			m->data[wi]   = write_data;
			m->tags[wi]   = write_tag;
			m->last_modified_index_per_set[write_set_id] = ni;

#ifdef TLBS_DEBUG
			char nbuf[256];
			generateName(m, nbuf);
			fprintf(stderr,"Info: wrote in set %d, wi=%d, tag=0x%x, data=0x%x\n",
					write_set_id, wi, write_tag, write_data);
#endif
		}
	}

	pthread_mutex_unlock (&(m->pm));
	return;
}


void setAssociativeMemoryCModel (
		uint8_t model_id,
		uint8_t twidth, uint8_t data_width, uint8_t log_mem_size, uint8_t log_set_size, 
		uint8_t ignore_collisions,
		uint8_t clear_flag, uint8_t erase_flag,  uint8_t write_flag,
		uint64_t write_data, uint64_t write_tag, uint16_t write_set_id,
		uint8_t lookup_flag, uint64_t lookup_tag, uint16_t lookup_set_id,
		uint8_t* lookup_valid, uint64_t* lookup_data)
{
	setAssociativeMemory* m = findOrAllocateSetAssociativeMemory(model_id,
			twidth, data_width, log_mem_size,
			log_set_size);

	operateOnSetAssociativeMemory(m,ignore_collisions, 
			clear_flag, erase_flag, write_flag,
			write_data, write_tag, write_set_id,
			lookup_flag, lookup_tag, lookup_set_id, 
			lookup_valid, lookup_data);
}

void fullyAssociativeMemoryCModel (
		uint8_t model_id, uint8_t twidth, uint8_t data_width, uint8_t log_mem_size, 
		uint8_t ignore_collisions, 
		uint8_t clear_flag, uint8_t erase_flag, uint8_t write_flag,
		uint64_t write_data, uint64_t write_tag, 
		uint8_t lookup_flag, uint64_t lookup_tag, 
		uint8_t* lookup_valid, uint64_t* lookup_data)
{
	setAssociativeMemoryCModel (model_id, 
			twidth, data_width, log_mem_size, log_mem_size, 
			ignore_collisions,
			clear_flag, erase_flag, write_flag,
			write_data, write_tag, 0,
			lookup_flag, lookup_tag, 0,
			lookup_valid, lookup_data);	
}




