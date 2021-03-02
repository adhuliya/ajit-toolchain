//Ajit_nodeops.h

#ifndef AJIT_NODEOPS_H
#define AJIT_NODEOPS_H



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





//int no_nextnode(int n)
//	  return sibling of node n.
//	  if 0 is passed as argument, return offset of root node.
//	  if node has no sibling, return 0
//	  return -1 to indicate error condition
int no_nextnode(int n);


//int no_child(int n)
//return first child of node n.
//if node has no child, return 0
//return -1 to indicate error condition
int no_child(int n);



//const char * no_nextprop(int n, const char* pname)
//
//return the name of the property that follows
//property with name "pname" for node n.
//if pname==0 or pname=='\0', return name of
//first property for node n

char * no_nextprop(int n, char* pname);

//if node n has a property "pname"
//copy its value into "val" and returns length of property in Bytes
//else return -1
int no_getprop(int n, const char * pname, char * val);

//if node n has a property <pname>,
//return length of the property's value in bytes.
//else return -1
int no_proplen(int n, const char* pname);



int no_setprop(int node, const char* name, char* value, int size);



/* Routines for traversing the prom device tree. */
struct Ajit_linux_nodeops {
	int (*no_nextnode)(int node);
	int (*no_child)(int node);
	int (*no_proplen)(int node, const char *name);
	int (*no_getprop)(int node, const char *name, char *val);
	int (*no_setprop)(int node, const char *name, char *val, int len);
	char * (*no_nextprop)(int node, char *name);
};




//struct linux_nodeops* get_Ajit_nodeops() :
//return pointer to a set of nodeop functions
//written for Ajit using flattened device tree routines,
//which will replace the default nodeop routines 
//present in the romvec
struct linux_nodeops* get_Ajit_nodeops(void);

//store the address of the device_tree_blob passed
//by the bootloader
void set_fdt_blob_addr(void* addr);

int blob_totalsize(void * blob);

#endif
