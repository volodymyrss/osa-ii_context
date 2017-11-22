#ifndef __TREE_MGR__
#define __TREE_MGR__

// Data types used by the tree programs. These are based on the standard data types.        
enum TreeKeyTypes {TREE_BYTE, TREE_CHAR, TREE_UCHAR, TREE_SHORT, TREE_USHORT, TREE_INT, TREE_UINT, 
                   TREE_LONG, TREE_ULONG, TREE_LLONG, TREE_ULLONG, TREE_FLOAT, 
                   TREE_DOUBLE, TREE_STRING};

// The tree functions work for the most part 
// recursively. It is fundamental that the   
// calling functions respect the arguments   
// otherwise unprdictable errors will occur. 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long BinarySearch(const void *, // value searched for                       
                  const void *, // array containing the table to search in  
                  const long,   // starting index                           
                  const long,   // ending index                             
                  long *,       // index of wher the value resides          
                  const short); // type of data 
 
short getkeysize(const short); // data type                                            

short TreeCmp(const void  *,   // pointer to value for comparison 
              const void  *,   // pointer to value for comparison 
              const short);    // type of data                                                  

#endif
