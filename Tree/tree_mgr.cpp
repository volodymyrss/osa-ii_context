#include "tree_mgr.h"
  
                          
////////////////////////////////////////////////////////////////////                
// Binary search for a value. The array (table) in which the search is effected  
// MUST be well ordered. This may depend on lexigraphical precedence although    
// for numerical values this should not cause problems. This function works      
// recursively, any incorrect argument may cause the calling program to crash.   
//////////////////////////////////////////////////////////////////// 

long BinarySearch(const void  *Mot,   // value searched for                      
                  const void  *Word,  // array containing the table to search in 
                  const long  upper,  // starting index                          
                  const long  lower,  // ending index                            
                  long        *where, // index of where the value resides        
                  const short type)   // type of data               
{
 long   li=0;
 int    i=0;
 short  size;
 void   *q;

 if((size=getkeysize(type))<=0) return(-1);

 if(upper>lower) { 
   *where=lower;
   return(-1);
 }
 // Get midpoint 
 li=ldiv(upper+lower-(upper+lower)%2, 2).quot;
 // Compare keys 
 q=(char *)Word+li*size;
 if(TreeCmp((void *)q, (void *)Mot, type)<0) {
   i=-1;
   i=BinarySearch(Mot, Word, li+1, lower, where, type);
 }
 else if(TreeCmp((void *)q, (void *)Mot, type)>0) {
   i=1;
   i=BinarySearch(Mot, Word, upper, li-1, where, type);
 }
 else {
   i=0;
   *where=li;
 }
 return(i);
}

 
//////////////////////////////////////////////////////////////////// 
// Compute the size of the data from its data type  
// defined in TreeKeyTypes.                         
//////////////////////////////////////////////////////////////////// 

short getkeysize(const short type)  // data type 
{
  switch(type) {
    case TREE_BYTE   :   return(sizeof(unsigned char));
    case TREE_CHAR   :   return(sizeof(char));
    case TREE_UCHAR  :   return(sizeof(unsigned char));
    case TREE_SHORT  :   return(sizeof(short));
    case TREE_USHORT :   return(sizeof(unsigned short));
    case TREE_INT    :   return(sizeof(int));
    case TREE_UINT   :   return(sizeof(unsigned int));
    case TREE_LONG   :   return(sizeof(long));
    case TREE_ULONG  :   return(sizeof(unsigned long));
    case TREE_LLONG  :   return(sizeof(long long));
    case TREE_ULLONG :   return(sizeof(unsigned long long));
    case TREE_FLOAT  :   return(sizeof(float));
    case TREE_DOUBLE :   return(sizeof(double));
    default          :   return(-1);
  }
 printf("error \n");
 exit(0);
}
  
 
////////////////////////////////////////////////////////////////////                
// This is a function to compare 2 values of the same type. It     
// returns respectively -1, 0, or 1 if the values are less, equal  
// or greater than. If different type data is sent, the result     
// will not correspond to anything.
////////////////////////////////////////////////////////////////////                

short TreeCmp(const void  *p,   // pointer to value for comparison 
              const void  *q,   // pointer to value for comparison 
              const short type) // type of data                                 
{ 
 switch(type) {
   case TREE_BYTE : 
     if((*(unsigned char *)p)<(*(unsigned char *)q)) return(-1);
     if((*(unsigned char *)p)>(*(unsigned char *)q)) return( 1);
     break;
   case TREE_CHAR :  
     if((*(char *)p)<(*(char *)q)) return(-1);
     if((*(char *)p)>(*(char *)q)) return( 1);
     break;
   case TREE_UCHAR : 
     if((*(unsigned char *)p)<(*(unsigned char *)q)) return(-1);
     if((*(unsigned char *)p)>(*(unsigned char *)q)) return( 1);
     break;
   case TREE_SHORT : 
     if((*(short *)p)<(*(short *)q)) return(-1);
     if((*(short *)p)>(*(short *)q)) return( 1);
     break;
   case TREE_USHORT : 
     if((*(unsigned short *)p)<(*(unsigned short *)q)) return(-1);
     if((*(unsigned short *)p)>(*(unsigned short *)q)) return( 1);
     break;
   case TREE_INT : 
     if((*(int *)p)<(*(int *)q)) return(-1);
     if((*(int *)p)>(*(int *)q)) return( 1); 
     break;
   case TREE_UINT : 
     if((*(unsigned int *)p)<(*(unsigned int *)q)) return(-1);
     if((*(unsigned int *)p)>(*(unsigned int *)q)) return( 1);
     break;
   case TREE_LONG :
     if((*(long *)p)<(*(long *)q)) return(-1);
     if((*(long *)p)>(*(long *)q)) return( 1);               
     break;
   case TREE_ULONG :  
     if((*(unsigned long *)p)<(*(unsigned long *)q)) return(-1);
     if((*(unsigned long *)p)>(*(unsigned long *)q)) return( 1);
     break;
   case TREE_LLONG :  
     if((*(long long *)p)<(*(long long *)q)) return(-1);
     if((*(long long *)p)>(*(long long *)q)) return( 1);
     break;
   case TREE_ULLONG : 
     if((*(unsigned long long *)p)<(*(unsigned long long *)q)) return(-1);
     if((*(unsigned long long *)p)>(*(unsigned long long *)q)) return( 1);
     break;
   case TREE_FLOAT :  
     if((*(float *)p)<(*(float *)q)) return(-1);
     if((*(float *)p)>(*(float *)q)) return( 1); 
     break;
   case TREE_DOUBLE : 
     if((*(double *)p)<(*(double *)q)) return(-1);
     if((*(double *)p)>(*(double *)q)) return( 1);
     break;
   case TREE_STRING : 
   return(strcmp((const char*)p, (const char*)q));
   break;
 }
 return(0);
}
