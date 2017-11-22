#ifndef __ISGRIGEN__
#define __ISGRIGEN__

// Usefull includes
#include <stdio.h>
#include <stdlib.h>
#include <isdc.h>
#include "dal3gen.h"

// Usefull defines
#define I_ASIC_PER_LINE  32  // Number of ASICs horizontally per line                          
#define J_ASIC_PER_LINE   2  // Number of ASICs vertically per line  
#define Quot(X, Y) ((X)-(X)%(Y))/(Y)

// Function declarations
int YZtoModN(int,  // detector coordinate
             int); // detector coordinate                

void lDecToBin(long,    // a long value                                      
               char *); // a pointer to a string to contain the binary value            

int DeltaOBT(OBTime,     // First OBTime                
             OBTime,     // Second OBTime               
             double *,   // Time difference in second   
             const int); // input status                

#endif
