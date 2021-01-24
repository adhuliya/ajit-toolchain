//Ajit_nodeops.c

#include "Ajit_nodeops.h"



//============================================================================
//
//Implementation of nodeops using fdt :
//
//============================================================================
//Nodeops satisfying romvec interface.
//
//The information is stored in a flattened device tree format
//and Nodeops use fdt routines internally to traverse the fdt 
//and get the required info.
//
//
//NOTE: 
//	In an fdt structure, the root node has id(offset) 0.
//	However, in romvec's nodeops, a node id of value 0 is used
//	to indicate an error condition. Hence nodeops functions such as
//	no_nextnode or no_child should not return 0 as a id of a valid node.
//	Hence we cannot use the real root node of the fdt.
//
//	Hence, we impose an artificial restriction on the structure of the fdt:
//	The real root node of the fdt (with offset 0) should have a  
//	single child node (with id not equal to 0) which we shall use as the
//	root node for our Nodeops.
//
//	fdt_root(id 0)
//	      |
//	root(id != 0)
//	   |
//	   child nodes ....
//
//Thus the device tree (in dts format) must be written like so:
//  \{  <--------dummy root
//       real_root {
//                   prop 1 = "foo"...
//
//                   first_child {
//                   	....
//                   	};
//                   ....
//                  };
//
//   };
//============================================================================

#include "libfdt.h"

//extern int dt_blob_start; //start of the external fdt blob linked to this code
//const void * fdt_blob = &dt_blob_start;//address of start of blob


void * fdt_blob; //address of start of blob, passed by bootloader


//store the address of the device_tree_blob passed
//by the bootloader
void set_fdt_blob_addr(void* addr)
{
	fdt_blob = addr;
}


//int no_nextnode(int n)
//	  return sibling of node n.
//	  if 0 is passed as argument, return offset of root node.
//	  if node has no sibling, return 0
//	  return -1 to indicate error condition
int no_nextnode(int n)
{
	int next_node = 0;
	int current_node=0;
	int depth = 1;

	if(n<0)
	{
		return -1; //error, not a valid node
	}
	if (n==0)
	{
		//get root node
		 next_node = fdt_next_node(fdt_blob, 0, &depth);
		 if(next_node >0)
			 return next_node; //valid offset for the root node
		 else
			 return -1; //root node not found!
	}
	else 
	{
		//try to locate the sibling
		current_node=n;

		while(1)
		{
			//get next node in the fdt
			//the next node (if one is found) might be a
			//child node, sibling node, or an ancestral node
			next_node = fdt_next_node(fdt_blob, current_node, &depth);
			if(next_node <= 0)
			{
				return 0; //no sibling
			}
			if(next_node>0 && depth>1)
			{
				//found a child node.
				//continue looking for next node
				current_node = next_node;
			}
			else if(next_node >0 && depth<1)
			{
				//found an ancestral node.
				//current node has no sibling.
				return 0;
			}
			else if(next_node >0 && depth==1)
			{
				//found a sibling !
				return next_node;
			}
		};
		return 0;
	};
};




//int no_child(int n)
//return first child of node n.
//if node has no child, return 0
//return -1 to indicate error condition
int no_child(int n)
{
	const int DEPTH =1;
	int next_node = 0;
	int current_node=0;
	int depth = DEPTH;

	if(n<0)
	{
		return -1; //error, not a valid node
	}
	else 
	{
		//try to locate the child node
		current_node=n;

		//get next node in the fdt
		//the next node (if one is found) might be a
		//child node, sibling node, or an ancestral node
		next_node = fdt_next_node(fdt_blob, current_node, &depth);
		if(next_node <= (DEPTH-1))
		{
			return 0; //no next node exists
		}
		if(next_node>0 && depth>DEPTH)
		{
			//found a child node.
			//return its value
			return next_node;
		}
		else if(next_node >0 && depth<=DEPTH)
		{
			//found a sibling/ancestral node.
			//this node has no children
			return 0;
		}
	};
	return 0;
};



//const char * no_nextprop(int n, const char* pname)
//
//return the name of the property that follows
//property with name "pname" for node n.
//if pname==0 or pname=='\0', return name of
//first property for node n
char * Ajit_name_string="name";
char   Ajit_name_buffer[500];

char * no_nextprop(int n, char* pname)
{
	int prop;
	const struct fdt_property *data;
	char* name = Ajit_name_buffer;


	if(n<0) 
	{
		return NULL;
	}
	else
	{
		//n is a valid node
		if(pname==NULL || pname=='\0') 
		{
			//if pname is 0 or NULL,
			//return the name of the first property.
			//"name" is supposed to be the first property 
			//in romvec nodeops
			return Ajit_name_string;
		}
		else if(strcmp(pname,"name")==0) 		
		{
			//return the first property of the node:
			//get the offset of first property
			prop = fdt_first_property_offset(fdt_blob, n);
			if(prop <0)
				return NULL; //no property found
			else
			{
				data = fdt_get_property_by_offset(fdt_blob, prop, NULL);
				if (data)
				{
					strcpy(name,fdt_string(fdt_blob, fdt32_to_cpu(data->nameoff)));
					//return fdt_string(fdt_blob, fdt32_to_cpu(data->nameoff));
					return name;
				}
				else
					return NULL;
			}
		}
		else
		{
			//try to locate a property "pname",
			//and return the property next to this one.

			prop = fdt_first_property_offset(fdt_blob, n);
			if(prop<0) return NULL;

			while(prop>=0)
			{
				//get name of the property
				data = fdt_get_property_by_offset(fdt_blob, prop, NULL);
				if(!data) return NULL;
				if (strcmp(pname,fdt_string(fdt_blob, fdt32_to_cpu(data->nameoff)))==0) break; //found name
				else
				{
					prop = fdt_next_property_offset(fdt_blob, prop); //get property next to pname
					if(prop<0) return NULL;
				}
			}
			
			prop = fdt_next_property_offset(fdt_blob, prop); 
			if(prop<0) return NULL;
			data = fdt_get_property_by_offset(fdt_blob, prop, NULL);
			if(!data) return NULL;
			return (char*)fdt_string(fdt_blob, fdt32_to_cpu(data->nameoff));
			//return name;
		}
	};
};

//if node n has a property "pname"
//copy its value into "val" and return size of the property value in Bytes
//else return -1
int no_getprop(int n, const char * pname, char * val)
{
	const char* prop_value=NULL;
	int length;

	if((n<0) || pname==NULL || pname=='\0' || val==NULL) 
	{
		// if n or name are not valid..return -1...error
		return -1;
	}
	
	//ok. input arguments are valid.
	//find value of the property with name "pname"
	if(strcmp(pname,"name")==0)
	{
		//copy name of this node into val and return success
		strcpy(val,fdt_get_name(fdt_blob, n, &length));
		return (length+1);
	}
	else
	{

		prop_value= fdt_getprop(fdt_blob, n, pname, &length);
		if(prop_value && length>0)
		{
			memcpy(val,prop_value,length);
			return length;
		}
		else
			return -1;
	}
};

//if node n has a property <pname>,
//return length of the property's value in bytes.
//else return -1
int no_proplen(int n, const char* pname)
{
	
	const char* prop_value=NULL;
	int length=0;

	if((n<=0) || pname==NULL || pname=='\0') 
	{
		// if n or name are not valid..return -1...error
		return -1;
	}
	
	//ok. input arguments are valid.
	//find value of the property with name "pname"
	if(strcmp(pname,"name")==0)
	{
		prop_value=fdt_get_name(fdt_blob, n, &length);
		return (length+1);
	}
	else
	{
 
		prop_value= fdt_getprop(fdt_blob, n, pname, &length);
		if(prop_value)
			return length;
		else
			return -1;
	};
};



int no_setprop(int node, const char* name, char* value, int size)
{
	//not implemented!
	//return error
	return -1;
};


/* Routines for traversing the prom device tree. */
/*
struct Ajit_linux_nodeops {
	int (*no_nextnode)(int node);
	int (*no_child)(int node);
	int (*no_proplen)(int node, const char *name);
	int (*no_getprop)(int node, const char *name, char *val);
	int (*no_setprop)(int node, const char *name, char *val, int len);
	char * (*no_nextprop)(int node, char *name);
};
*/


struct Ajit_linux_nodeops Ajit_nodeops = {
	no_nextnode,
	no_child,
	no_proplen,
	no_getprop,
	no_setprop,
	no_nextprop };




//struct linux_nodeops* get_Ajit_nodeops() :
//return pointer to a set of nodeop functions
//written for Ajit using flattened device tree routines,
//which will replace the defualt nodeop routines 
//present in the romvec
struct linux_nodeops* get_Ajit_nodeops(void)
{
	return (struct linux_nodeops*)&Ajit_nodeops;
};

int blob_totalsize(void * blob)
{
	return fdt_totalsize(blob);
}
