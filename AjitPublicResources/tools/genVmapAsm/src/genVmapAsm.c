#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int GID  = 0;
uint32_t memory_needed_for_page_tables = 0;

FILE* in_file = NULL;
FILE* out_file = NULL;

#define L1MASK (0xffffffff >> 8)
#define L2MASK (L1MASK >> 6)
#define L3MASK (L2MASK >> 6)

#define PTM_SIZE (16*1024)
uint32_t page_table_memory[PTM_SIZE];
void initPageTableMemory()
{
	uint32_t I;
	for(I=0; I < PTM_SIZE; I++)
	{
		page_table_memory[I] = 0xffffffff;
	}
}

void dumpPageTableMemory()
{
	fprintf(stderr,"Info: dumping page-table-memory\n");
	uint32_t I;
	for(I=0; I < PTM_SIZE; I++)
	{
		uint32_t pdte = page_table_memory[I];
		if(pdte != 0xffffffff)
			fprintf(stderr,"[0x%x] = 0x%x \n",(I << 2), page_table_memory[I]);
		
	}
	fprintf(stderr,"Info: finished dumping page-table-memory\n");
}


void setInPageTableMemory(uint32_t addr, uint32_t value)
{
	uint32_t aindex = (addr >> 2);
	if(aindex < PTM_SIZE)
	{
		if(page_table_memory[aindex] == 0xffffffff)
			page_table_memory[aindex] = value;
		else
		{
			fprintf(stderr,"Error: page table memory overwritten at addr=0x%x\n", addr);
		}
	}
	else
		fprintf(stderr,"Error: page table memory overflow at addr=0x%x\n", addr);

}



//
// Generate assembly code, allocating page-tables on the stack.
//
//
uint32_t page_offset (uint32_t vaddr)
{
	uint32_t ret_val = vaddr & 0xfff;
	return(ret_val);
}

uint32_t page_table_index (uint32_t level, uint8_t context, uint32_t vaddr)
{
	uint32_t ret_val  = context;
	if(level == 1)
	//
	// 16MB page, 
	// 256 entries at level 1
	//
	{
		// index is given by top 8 bits [31:24]
		ret_val = (vaddr >> 24);
	}
	else if (level == 2)
	//
	// 256 KB page.
	// 64 entries at level 2
	//
	{
		// index given by bits [23:18]
		ret_val = (vaddr >> 18) & 0x3f;
	}
	else if (level == 3)
	//
	// 4KB page.
	// 64 entries at level 3
	//
	{
		// index given by bits [17:12]
		ret_val = (vaddr >> 12) & 0x3f;
	}
	return(ret_val);
}



typedef struct PDTE__ PDTE;
struct PDTE__ {
	uint8_t  context;
	uint8_t  level;				// level of the PDTE
	uint8_t  is_ptd;			// =1 for ptd.
	uint8_t  index; 			// index into the page-table at level.
	uint32_t ppnr;				// ppn or table-ptr.
	uint32_t p_addr;			// address of this PDTE in physical memory.
	uint32_t cacheable;
	uint32_t acc;
	PDTE*    child;
	PDTE*    sibling;
	PDTE*    pred_sibling;
	int id;
};


PDTE*  root_context;


PDTE* context_table_pointer;
PDTE* make_pdte (uint8_t l, uint8_t context, uint8_t is_ptd, uint32_t vaddr, uint32_t ppnr, uint32_t cacheable, uint32_t acc)
{
	PDTE* ret_pdte = (PDTE*) malloc(sizeof(PDTE));
	ret_pdte->context = context;
	ret_pdte->level = l;
	ret_pdte->index = page_table_index (l, context, vaddr);
	ret_pdte->is_ptd = is_ptd;
	ret_pdte->ppnr = ppnr;
	ret_pdte->child = NULL;
	ret_pdte->sibling = NULL;
	ret_pdte->pred_sibling = NULL;
	ret_pdte->p_addr = 0;
	ret_pdte->cacheable = cacheable;
	ret_pdte->acc = acc;
	ret_pdte->id = GID; 
	GID++;

	fprintf(stderr,"Info: new pdte: id=%d, context=%d, level=%d, index=0x%x, is_ptd=%d, ppnr=0x%x, cacheable=0x%x, acc=0x%x\n", 
				ret_pdte->id, ret_pdte->context, ret_pdte->level, 
				ret_pdte->index, ret_pdte->is_ptd, ret_pdte->ppnr, ret_pdte->cacheable, ret_pdte->acc);
	return(ret_pdte);
}

void append_sibling(PDTE* p, PDTE* c) 
{
	if (p != NULL) 
	{
		while (p->sibling != NULL)
		{
			p = p->sibling;
		}
		p->sibling = c;
		c->pred_sibling = p;

		assert (p->level == c->level);
		fprintf(stderr,"Info: added sibling: %d (level %d) to %d (level %d) \n", 
			c->id, c->level, p->id, p->level);
	}
}

void append_child(PDTE* p, PDTE* c) 
{
	if (p != NULL) 
	{
		if(p->child == NULL)
		{
			p->child = c;
			fprintf(stderr,"Info: added child:  %d (level=%d)-> %d (level=%d)\n", c->id, c->level, p->id, p->level);
		}
		else
		{
			append_sibling (p->child, c);
		}

	}
}



//
// starting from start-root, find/make a suitable parent for new_pte.
//
PDTE*  find_or_make_parent_ptd(PDTE* start_root, uint8_t context, uint32_t vaddr, PDTE* new_pte)
{
	PDTE* ret_val = NULL;
	PDTE* s_root = start_root;

	uint8_t search_level = s_root->level;

	while (s_root != NULL)
	//
	//
	//
	{
		if(s_root->index == page_table_index (search_level, context, vaddr))
		{
			if(s_root->level == (new_pte->level - 1))
			{
				// found a match at current level.
				ret_val = s_root;
				break;
			}
			else if (s_root->child != NULL)
			{
				ret_val = find_or_make_parent_ptd (s_root->child, context, vaddr, new_pte);
			}
			else 
			{
				PDTE* c = make_pdte (s_root->level + 1, context, 1, vaddr, new_pte->ppnr, new_pte->cacheable, new_pte->acc);
				append_child(s_root, c);

				ret_val = find_or_make_parent_ptd (c, context, vaddr, new_pte);
				break;
			}
	
		}
		
		s_root = s_root->sibling;
	}

	
	// not found..  add a sibling to start-root.
	if(ret_val == NULL)
	{
		if(search_level < new_pte->level)
		{
			s_root = make_pdte (search_level, context, 1, vaddr, new_pte->ppnr, new_pte->cacheable, new_pte->acc); 
			append_sibling (start_root, s_root);
			ret_val = find_or_make_parent_ptd (s_root, context, vaddr, new_pte);
		}
		else
		{
			ret_val = new_pte;
			append_sibling (start_root, new_pte);
		}
	}
	return(ret_val);
}


void insert_pte_into_tree (PDTE** root_context, uint8_t context, uint32_t vaddr,  PDTE* new_pte)
{
	if(*root_context == NULL)
	{
		//
		// new_pte is at level 0..
		// 
		if(new_pte->level == 0)
		{
			*root_context = new_pte;
		}
		else
		{
			*root_context = make_pdte (0, context, 1, vaddr, new_pte->ppnr, new_pte->cacheable, new_pte->acc);

			PDTE* new_root = find_or_make_parent_ptd (*root_context, context, vaddr, new_pte);
			if(new_root->is_ptd)
				append_child (new_root, new_pte);
		}
	}
	else
	{
		PDTE* new_root = find_or_make_parent_ptd (*root_context, context, vaddr, new_pte);
		if(new_root->is_ptd)
			append_child (new_root, new_pte);
	}
}


void dump_pdte (char* tab, PDTE* pdte)
{
	if(pdte == NULL)
		return;

	if(pdte->is_ptd)
	{
		fprintf(stderr, "%s PTD: context=%d, index=%d, level=%d, child_p_addr=0x%x, p_addr=0x%x\n",
				tab, pdte->context, pdte->index, pdte->level, pdte->child->p_addr, pdte->p_addr);
	}
	else
	{
		fprintf(stderr, "%s PTE: context=%d, index=%d, level=%d,  ppnr=0x%x, p_addr=0x%x, cacheable=0x%x, acc=0x%x\n",
				tab, pdte->context, pdte->index, pdte->level, pdte->ppnr, pdte->p_addr, pdte->cacheable, pdte->acc);
	}

	char tab_buffer [1024];
	sprintf(tab_buffer,"%s  ", tab);
	dump_pdte (tab_buffer, pdte->child);
	dump_pdte (tab, pdte->sibling);
}


void dump_vmap ()
{
	dump_pdte ("", root_context);
}


uint32_t align_page_table (uint32_t A, uint32_t level)
{
	uint32_t C = ((level > 1) ? 64 : 256);
	uint32_t R = (A % C);

	if (R != 0)
	{
		A = (A + C) - R;
	}
	return(A);
}

//
// bottom up
//
uint32_t alloc_pdte (uint32_t SP, PDTE* p)
{

	if(p == NULL)
		return (SP);


	PDTE* sib;
	for(sib = p; sib != NULL; sib = sib->sibling)
	{
		// allocate under each sibling..
		SP = alloc_pdte (SP, sib->child);
	}

	// align as per level..
	SP = align_page_table (SP, p->level);

	if(p->pred_sibling == NULL)
		fprintf(stderr,"Level-%d page-table starting at offset 0x%x\n", p->level, (SP << 2));

	for(sib = p; sib != NULL; sib = sib->sibling)
	{
		sib->p_addr = (SP  << 2) | (sib->index << 2);
	}

	if(p->pred_sibling == NULL)
	{
		if ((p->level == 0) || (p->level == 1))
		{
			SP += 256;
		}
		else
		{
			SP += 64;
		}

	}

	return (SP);
}


void alloc_vmap ()
{
	memory_needed_for_page_tables = (alloc_pdte (0, root_context) << 2);
	fprintf(stderr,"Info: table memory used=0x%x\n", memory_needed_for_page_tables);
}

		
uint32_t make_pte_32 (uint32_t level,  uint32_t ppnr, uint32_t cacheable, uint32_t acc)
{
	uint32_t pte = (ppnr >> 12) << 8;

	// C = cacheable, ACC = acc, ET = 2.
	pte = pte | (cacheable << 7) | (acc << 2) | 2;

	return(pte);
}

//
// p_addr is aligned and will appear on bits of 35-6 
// of physical address..
//
uint32_t make_ptd_32 (uint32_t level,  uint32_t p_addr)
{

	if ((level == 0)  || (level == 1))
	{
		if ((p_addr & 0xff)  != 0)
		{
			fprintf(stderr,"Error: addr 0x%x of page-table at level %d is not aligned correctly\n",  p_addr, level);
		}
	}
	else
	{
		if ((p_addr & 0x3f)  != 0)
		{
			fprintf(stderr,"Error: addr 0x%x of page-table at level %d is not aligned correctly\n",  p_addr, level);
		}
	}

	uint32_t ptd = (p_addr >> 4) | 1;
	return(ptd);
}

void dump_asm (PDTE* root)
{

	if(root == NULL) return;

	fprintf(stderr,"Info:dump_asm: entering id=%d\n",root->id);

	if(root->is_ptd)
	{
		fprintf(out_file, "   !PTD: context=%d, index=%d, level=%d, child_p_addr=0x%x, p_addr=0x%x\n",
			root->context, root->index, root->level, root->child->p_addr, root->p_addr);
	}
	else
	{
		fprintf(out_file, "   !PTE: context=%d, index=%d, level=%d,  ppnr=0x%x, p_addr=0x%x, cacheable=0x%x, acc=0x%x\n",
			root->context, root->index, root->level, root->ppnr, root->p_addr, root->cacheable, root->acc);
	}

	if(!root->is_ptd)
	{
		// make pte and write it at the physical address.
		uint32_t pte = make_pte_32 (root->level, root->ppnr, root->cacheable, root->acc);
		setInPageTableMemory(root->p_addr, pte);

		fprintf(out_file, "   ! *(PAGE_TABLE_BASE + 0x%x) = 0x%x (pte)\n", root->p_addr, pte);
		fprintf(out_file,"   set 0x%x, %s\n", pte, "%g2");
		fprintf(out_file,"   set 0x%x, %s\n", root->p_addr, "%g5");
		fprintf(out_file,"   add %s, %s, %s\n", "%g5", "%g1", "%g3");
		fprintf(out_file,"   st %s, [%s]\n", "%g2", "%g3");
	}
	else if (root->child != NULL)
	{ // root is ptd..  it points to a lower-level page-table


		uint32_t child_table_base = (root->child->p_addr - (root->child->index << 2));

		uint32_t ptd = make_ptd_32 (root->level, child_table_base);
		setInPageTableMemory(root->p_addr, ptd);

		fprintf(out_file, "   ! *(PAGE_TABLE_BASE + 0x%x) = ptd(PAGE_TABLE_BASE + 0x%x)\n", root->p_addr, child_table_base);
		fprintf(out_file, "   ! make PTD from 0x%x\n", root->child->p_addr);
		fprintf(out_file, "   set 0x%x, %s\n", child_table_base, "%g4");
		fprintf(out_file, "   add %s, %s, %s\n",  "%g1", "%g4", "%g4");
		fprintf(out_file, "   srl %s, 0x4, %s\n", "%g4", "%g4");
		fprintf(out_file, "   or  %s, 0x1, %s\n", "%g4", "%g4");
		fprintf(out_file, "   ! g4 contains PTD \n");
		fprintf(out_file, "   set 0x%x, %s\n", root->p_addr, "%g5");
		fprintf(out_file, "   add %s, %s, %s\n", "%g5", "%g1", "%g3");
		fprintf(out_file, "   st %s, [%s]\n", "%g4", "%g3");
		fprintf(out_file, "   ! g4 stored into [g3] \n");

#ifdef DDEBUG
		if(root->child)
			fprintf(stderr,"Info:dump_asm: continue from %d to child id=%d\n", 
				root->id, root->child->id);
#endif
		dump_asm(root->child);
	}

	PDTE* s = root->sibling;
	if(s != NULL)
	{

#ifdef DDEBUG
		fprintf(stderr,"Info:dump_asm: continue from %d to sibling id=%d\n", root->id, s->id);
#endif
		dump_asm (s);
	}

#ifdef DDEBUG
	fprintf(stderr,"Info:dump_asm: leaving id=%d\n",root->id);
#endif

}

//
// generate assembly code to map virtual pages to physical pages.
//
int main(int argc, char* argv[])
{
	int err = 0;

	initPageTableMemory();
	uint32_t context, vpage_addr, ppage_addr, level, cacheable, acc;

	if(argc < 3) 
	{
		fprintf(stderr,"Usage: %s <in-file> <out-file>\n", argv[0]);
		fprintf(stderr," input vmap file should contain lines with the following fields\n");
		fprintf(stderr,"   context  virtual-page-address  physical-page-address page-level [cacheable?] [acc] \n");
		fprintf(stderr,"        (default cacheable=1, acc=3).\n");
		return(1);
	}

	in_file = fopen(argv[1],"r");
	if(in_file == NULL)
	{
		fprintf(stderr,"Error: could not open infile %s\n", argv[1]);
	}

	out_file = fopen(argv[2],"w");
	if(out_file == NULL)
	{
		fprintf(stderr,"Error: could not open outfile %s\n", argv[2]);
	}

	root_context = NULL;
	PDTE* new_pte = NULL;

	char data_line[1024];
  	while(fgets(data_line,1023,in_file) != NULL)
	{
		// comments in vmap file start with !
		if(data_line[0] == '!') continue;

		// default: page is cacheable with acc=3 (read/write/execute)
		cacheable = 1; acc = 3; 

		char* tbuf = strtok(data_line, " \t");
		if (tbuf == NULL) break;
		sscanf (tbuf, "0x%x", &context);

		tbuf = strtok(NULL, " \t");
		if (tbuf == NULL) break;
		sscanf (tbuf, "0x%x", &vpage_addr);
		
		tbuf = strtok(NULL, " \t");
		if (tbuf == NULL) break;
		sscanf (tbuf, "0x%x", &ppage_addr);

		tbuf = strtok(NULL, " \t");
		if (tbuf == NULL) break;
		sscanf (tbuf, "0x%x", &level);

		tbuf = strtok(NULL, " \t");
		if(tbuf != NULL)
		{
			sscanf (tbuf, "0x%x", &cacheable);
			tbuf = strtok(NULL, " \t");
			if(tbuf != NULL)
				sscanf (tbuf, "0x%x", &acc);
		}

		fprintf(stderr,"Info: context=0x%x, vaddr=0x%x, paddr=0x%x, level=0x%x, cacheable=0x%x, acc=0x%x\n",
				context, vpage_addr, ppage_addr, level, cacheable, acc);

		if ((level == 1) && ((L1MASK & vpage_addr) != 0))
		{
			err = 1;
			fprintf(stderr,"Error: level 1 page is not aligned to 16MB boundary (base-addr = 0x%x\n", vpage_addr);
		}
		if ((level == 2) && ((L2MASK & vpage_addr) != 0))
		{
			err = 1;
			fprintf(stderr,"Error: level 2 page is not aligned to 16MB boundary (base-addr = 0x%x\n", vpage_addr);
		}
		if ((level == 3) && ((L3MASK & vpage_addr) != 0))
		{
			err = 1;
			fprintf(stderr,"Error: level 3 page is not aligned to 16MB boundary (base-addr = 0x%x\n", vpage_addr);
		}
		
		new_pte = make_pdte (level, context, 0, vpage_addr, ppage_addr, cacheable, acc);
		insert_pte_into_tree (&(root_context), context, vpage_addr, new_pte);
	}

	alloc_vmap ();
	dump_vmap ();

	fprintf (out_file,".section .text.pagetablesetup\n");
	fprintf (out_file,".global page_table_setup\n");
	fprintf (out_file,"page_table_setup:\n");
	fprintf (out_file,"   set PAGE_TABLE_BASE, %s\n", "%g1");
	dump_asm (root_context);

	fprintf (out_file, "   retl;\n");
	fprintf (out_file, "   nop;\n");
	fprintf (out_file, "! done: page_table_setup\n"); 

	// set the context table pointer.
	fprintf (out_file, "! start: set context-table-pointer = PAGE_TABLE_BASE + 0x%x\n", root_context->p_addr);
	fprintf (out_file, ".global set_context_table_pointer\n");
	fprintf (out_file,"set_context_table_pointer:\n");
	fprintf (out_file,"   set PAGE_TABLE_BASE, %s\n", "%g1");

	fprintf (out_file, "   set 0x%x, %s\n", root_context->p_addr, "%g5");
	fprintf (out_file, "   add %s, %s, %s\n", "%g5", "%g1", "%g2");
	fprintf (out_file, "   srl  %s, 0x4, %s\n", "%g2", "%g2");
	fprintf (out_file, "   or  %s, 0x1, %s\n", "%g2", "%g2");
	
	fprintf (out_file, "   set 0x100, %s\n", "%g3");
	fprintf (out_file, "   sta %s, [%s] 0x4\n", "%g2", "%g3");

	fprintf (out_file, "   retl;\n");
	fprintf (out_file, "   nop;\n");
	fprintf (out_file, "! done: set  context-table-pointer\n");

	fprintf(out_file,".align 1024\n");
	fprintf(out_file,"PAGE_TABLE_BASE: .skip %d\n", memory_needed_for_page_tables);

	dumpPageTableMemory();

	fclose(in_file);
	fclose(out_file);

	if(err)
	{
		fprintf(stderr,"Error: there were errors, look at the log.\n");
	}
	return(err);
}

