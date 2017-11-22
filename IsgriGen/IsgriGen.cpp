#include "IsgriGen.h"


//////////////////////////////////////////////////////////////////////////
// Determine the ISGRI module number starting from the pixel coordinates.
//////////////////////////////////////////////////////////////////////////

int YZtoModN(int IsgrY, // detector coordinate
             int IsgrZ) // detector coordinate
{
 int IsgrModN;

 if((IsgrY<0) || (IsgrY>128)) return(-1);
 if((IsgrZ<0) || (IsgrZ>128)) return(-1);

 if(IsgrY>63) IsgrModN=3-div(IsgrZ, 32).quot;
 else         IsgrModN=7-div(IsgrZ, 32).quot;
 
 return(IsgrModN);
}


/////////////////////////////////////////////////////////////////////
// Write an integer value into a string in its binary representation. 
/////////////////////////////////////////////////////////////////////

void lDecToBin(long a,   // a long value       
               char *ch) // a pointer to a string to contain the binary value
{
 int  i, m=8*sizeof(long);
 long c=1l;

 ch[m]='\0';
 ch[0]='0';
 for(i=1; i<m; i++) {
    ch[m-i]=c&a ? '1' : '0';
    c=c<<1;
 }
}


/////////////////////////////////////////////////////////////////
// Compute the difference between two On Board Times in seconds.                                                  
/////////////////////////////////////////////////////////////////

int DeltaOBT(OBTime    a,        // First OBTime             
             OBTime    b,        // Second OBTime             
             double    *Time,    // Time difference in second 
             const int InStatus) // input status              
{
  int    Status=ISDC_OK;
  OBTime d=0, s=1, quot, rem;
  
  if(InStatus!=ISDC_OK) return(InStatus);
  
  if(a>=b);
  if((Status=DAL3GENelapsedOBT(a, b, &d, InStatus))!=ISDC_OK) return(Status);
  else {
    if((Status=DAL3GENelapsedOBT(b, a, &d, InStatus))!=ISDC_OK) return(Status);
    s=-1;
  }
  rem=d%DAL3_OBT_SECOND;
  quot=(d-rem)/DAL3_OBT_SECOND;
  
  // SPR 4189: remove constant IEEE_MAX_DOUBLE (too big)
  //  if(quot<=IEEE_MAX_DOUBLE) {
  //    *Time=(double)(quot*s)+(double)(rem*s)*DAL3_OBT_UNIT;
  //    return(Status);
  //  }
  //  else return(-1);
  
  *Time= (double)(quot*s) + (double)(rem*s)*DAL3_OBT_UNIT;
  return Status;
}
