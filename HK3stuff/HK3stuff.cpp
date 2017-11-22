#include "HK3stuff.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                   Compute PixelLive map on a given Time Interval, by handling HK3 data                
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

int getPixelLive(dal_element *idxNoisy,    // DOL to the HK3 noisy maps
		 OBTime      OBTstart,     // Starting time
		 OBTime      OBTend,       // Finishing tine
		 dal_double  **PixelLive,  // Output: Map[y][z] of percent of Time ON
                 dal_int     *NumMaps,     // Output: Number of HK3 maps per module
                 int         chatter,      // verbosity level, min 0 to max 3
		 int         status)
{
  //  You can improve the code to do more checking
  //  // init
  //  prevSOP = 65535;
  //  prevMap[][] set to first HK3 map
  //  firstMap =true
  
  //  for(k=0; k<NoisyLength; k++) {
  //    set map from block[k]
  //    if ((PERIOD_ON == 65535) && (prevSOP  == 65535)) {
  //      // because changes can occur in first map after NPHS switch off
  //      check that map equal prevMap (change prevMap accordingly)
  //     }
  //    }
  //    else {
  //      if (ON_RANGE == 255) {
  //        if (prevMap[y][z] == off) check that pixel is still off
  //      }
  //      else {
  //        if (prevMap[y][z] == off) check that pixel ON coherent with ON_RANGE
  //      }
  //      prevMap=map;
  //    }
  //    prevSOP=PERIOD_ON;
  //  } // end of loop

  int RILstatus= ISDC_OK;

  // =============================================================================================
  //                                           First checks
  // =============================================================================================

  if(status!=ISDC_OK) return status;

  // Init outputs to default value = status ON
  for(int y=0;y<ISGRI_SIZE;y++)
    for(int z=0;z<ISGRI_SIZE;z++) 
      PixelLive[y][z]= 1.;
  for (int mce=0; mce<IBIS_NUM_BLOCK; mce++) 
    NumMaps[mce]= 0;

  // Check Input Interval duration 
  double DeltaT=0.;
  if((status=DeltaOBT(OBTend, OBTstart, &DeltaT, status))!=ISDC_OK)
    {
      RILstatus= RILlogMessage(NULL, Error_1, "OBTime difference fatal error for input interval [ %lld, %lld ]", 
			       OBTstart,OBTend);
      return status;
    }
  if(DeltaT<1e-9)
    {
      RILstatus= RILlogMessage(NULL, Error_1, "Bad input interval [ %lld, %lld ] (has Length<0)!", 
			       OBTstart,OBTend);
      return status;
    }


  // =============================================================================================
  //                      Get the size of the relevant HK3 Noisy data
  // =============================================================================================
  
  if(!idxNoisy) 
    {
      RILstatus= RILlogMessage(NULL, Warning_2, "There is no HK3 Noisy Map index!");
      RILstatus= RILlogMessage(NULL, Warning_2, "Estimating pixels'status now only relies on SELECT_FLAG tags.");
      RILstatus= RILlogMessage(NULL, Warning_2, "Arbitrary Pixel ON time ratio is fixed at 1.");
      return ISDC_OK;
    }
  
  long NoisyLength= 0;
  if((status= DAL3IBISgetSizeNoisyMaps(idxNoisy, OBTstart, OBTend, &NoisyLength, status))!=ISDC_OK) 
    { 
      // NOTE: Failure can occur if ( NOISE-CPR_OBTLast<OBTstart && OBTend<NOISE-CPR_OBTFirst ) 
      RILstatus= RILlogMessage(NULL, Warning_2, "Error in obtaining number of HK3 Noisy Maps (status= %d)!", status);
      RILstatus= RILlogMessage(NULL, Warning_2, "(Check HK3 times of prev/current/next Time Interval)"); 
      RILstatus= RILlogMessage(NULL, Warning_2, "Estimating pixels'status now only relies on SELECT_FLAG tags.");
      RILstatus= RILlogMessage(NULL, Warning_2, "Arbitrary Pixel ON time ratio is fixed at 1.");
      RILstatus= RILlogMessage(NULL, Warning_2, "Reverting to ISDC_OK."); 
      return ISDC_OK;
    }
  if(chatter>1) 
    RILstatus= RILlogMessage(NULL, Log_1, "There were %ld HK3 maps in [ %llu, %llu ]", 
			     NoisyLength, OBTstart, OBTend);
  if(!NoisyLength)
    {
      RILstatus= RILlogMessage(NULL, Warning_2, "Found no HK3 map during interval [ %llu, %llu ].", OBTstart, OBTend);
      RILstatus= RILlogMessage(NULL, Warning_2, "Estimating pixels'status now only relies on SELECT_FLAG tags.");
      RILstatus= RILlogMessage(NULL, Warning_2, "Arbitrary Pixel ON time ratio is fixed at 1.");
      return ISDC_OK;
    }
  
  
  // =============================================================================================
  //                              Allocate the required arrays 
  // =============================================================================================
 
  OBTime     
    *blockTime= NULL;
  DAL3_Byte
    *mceId=   NULL,
    *onRange= NULL,
    (*block)[IBIS_IBLOCK_LENGTH]= NULL;
  DAL3_Word     
    *periodOn= NULL;

  DAL3_Byte **onOffMap= NULL;
  if((onOffMap= (DAL3_Byte**)calloc(ISGRI_SIZE, sizeof(DAL3_Byte*)))==NULL) 
    {
      RILstatus= RILlogMessage(NULL, Error_2, "Error in memory allocation : onOffMap.");
      return ERR_ISGR_OSM_MEMORY_ALLOC;
    }
  for(int y=0;y<ISGRI_SIZE;y++) 
    onOffMap[y]= NULL;

  // =============================================================================================
  //                          Get the Noisy (switch) Maps and HK3 data
  // =============================================================================================

  do 
    {
      // Allocate HK3 stuff
      if((status= DAL3IBISallocateNoisyMaps(&blockTime, &mceId, &periodOn, &onRange, &block, 
					    NoisyLength, status))!=ISDC_OK) 
	{
	  RILstatus= RILlogMessage(NULL, Error_2, "Memory allocation for Noisy Maps: status= %d.", status);
	  break;
	}
      for(int y=0;y<ISGRI_SIZE;y++) 
	{
	  if((onOffMap[y]= (DAL3_Byte*)calloc(ISGRI_SIZE, sizeof(DAL3_Byte)))==NULL) 
	    {
	      RILstatus= RILlogMessage(NULL, Error_2, "Error in memory allocation : onOffMap[].");
	      status= ERR_ISGR_OSM_MEMORY_ALLOC;
	      break;
	    }
	}
      if(status!=ISDC_OK) break;

      // Fill HK3 stuff
      if((status= DAL3IBISgetNoisyMaps(idxNoisy, OBTstart, OBTend, blockTime, mceId, periodOn, onRange,
				       block, &NoisyLength, status))!=ISDC_OK) 
	{ 
	  RILstatus= RILlogMessage(NULL, Error_1,   "Error in getting HK3 Noisy Maps (status %d).", status);
	  RILstatus= RILlogMessage(NULL, Warning_2, "Estimating pixels'status now only relies on SELECT_FLAG tags.");
	  RILstatus= RILlogMessage(NULL, Warning_2, "Arbitrary Pixel ON time ratio is fixed at 1.");
	  RILstatus= RILlogMessage(NULL, Warning_1, "Reverting to ISDC_OK.");
	  status= ISDC_OK;
	  break;
	}  

      // Init Output to 0 before summing
      for(int y=0;y<ISGRI_SIZE;y++)
	for(int z=0;z<ISGRI_SIZE;z++) 
	  PixelLive[y][z]= 0.;

      // Compute Pixel Live map out of noisy maps
      int 
	StartY,
	StartZ;
      bool
	FoundMap= FALSE;
      long
	FirstMap=0, 
	LastMap=0;
      for(long k=0; k<NoisyLength; k++)
	{
	  //  SPR 3270: care for corrupted data
	  if(mceId[k]>=IBIS_NUM_BLOCK) 
	    {
	      RILstatus= RILlogMessage(NULL, Error_1, "Impossible mceId data value : out of range [0,7].");
	      status= ERR_ISGR_OSM_DATA_INCONSISTENCY;
	      break;
	    }
	  StartY= (mceId[k]<4) ? 64 : 0;
	  StartZ= (3-mceId[k]%4)*32;
	  
	  // Select Maps relevant with Input Time Interval
	  if( (blockTime[k]>=OBTstart) && (blockTime[k]<=OBTend) )
	    {
	      // Locate first and last map
	      if(FoundMap)
		{
		  if(blockTime[k]<blockTime[FirstMap]) 
		    FirstMap= k;
		}
	      else
		{
		  FirstMap= k;
		  FoundMap= TRUE;
		}
	      if(blockTime[k]>blockTime[LastMap]) 
		LastMap= k;
	      // Retrieve HK3 OnOff map
	      status= PixelOnOffMap(block[k], onOffMap, mceId[k], status);
	      if(status != ISDC_OK) break;
	      // Sum status for relevant mce
	      for(int y=StartY;y<StartY+64;y++)
		for(int z=StartZ;z<StartZ+32;z++)
		  PixelLive[y][z]+= (double)onOffMap[y][z];
	      NumMaps[mceId[k]]++;

	    } // If Map is time-relevant

	} // Loop on Maps
 
      if(status!=ISDC_OK) break;
      
      // Output info on the first and last map
      if(FoundMap)
	{
	  if(chatter>2) 
	    {
	      RILstatus= RILlogMessage(NULL, Log_0, "First map (rank=%ld, mce=%d, period=%05d, range=%02d) is at OBT %llu.",
				       FirstMap, (int)mceId[FirstMap], (int)periodOn[FirstMap], (int)onRange[FirstMap], 
				       blockTime[FirstMap]);
	      RILstatus= RILlogMessage(NULL, Log_0, "Last  map (rank=%ld, mce=%d, period=%05d, range=%02d) is at OBT %llu",
				       LastMap, (int)mceId[LastMap], (int)periodOn[LastMap], (int)onRange[LastMap], 
				       blockTime[LastMap]);
	    }
	}
      else
	RILstatus= RILlogMessage(NULL, Warning_1, "There is no HK3 Noisy Map for this interval!");
      
      // Normalize map
      for(int mce=0; mce<IBIS_NUM_BLOCK; mce++) 
	{
	  // Determine module's ISGRI coordinates
	  StartY= (mce<4) ? 64 : 0;
	  StartZ= (3-mce%4)*32;
	  // If no HK3 for this module
	  if(!NumMaps[mce]) 
	    {
	      RILstatus= RILlogMessage(NULL, Warning_1, "There is no HK3 Noisy Map for module %d", mce);
	      RILstatus= RILlogMessage(NULL, Warning_1, "Arbitrary Pixel ON time ratio fixed at 1 for this module.");	      
	      for(int y=StartY;y<StartY+64;y++)
		for(int z=StartZ;z<StartZ+32;z++)
		  PixelLive[y][z]= 1.;
	    }
	  // Normalize map
	  else 
	    {
	      for(int y=StartY;y<StartY+64;y++)
		for(int z=StartZ;z<StartZ+32;z++)
		  PixelLive[y][z]/= (double)NumMaps[mce];
	      if(chatter>2) 
		RILstatus= RILlogMessage(NULL, Log_0, "MCE%d: Number of HK3 Noisy Maps= %ld", mce, NumMaps[mce]);
	    }
	}      
    } 
  while(0);


  // =============================================================================================
  //                                        Free memory and exit
  // =============================================================================================

  if((status= DAL3IBISfreeNoisyMaps(blockTime, mceId, periodOn, onRange, block, status))!=ISDC_OK)
    {
      RILstatus= RILlogMessage(NULL, Error_2, "Memory de-allocation error for Noisy Maps: status= %d.", status);
      return status;
    }
  if(onOffMap) 
    {
      for(int y=0;y<ISGRI_SIZE;y++) 
	if(onOffMap[y]) free(onOffMap[y]);
      free(onOffMap);
    }
  return status;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//             Decoding the bytes making up the ISGRI context tables proceding module by module
//                      [ see document  SIG-ISGRI-FMo-1071-99 for complete details.]
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

int PixelOnOffMap(DAL3_Byte *b,              // the data vector, must be 256 bytes long
                  DAL3_Byte **pixelOnOffMap, // the image [y][z]  to contain on/off pixel status
                  DAL3_Byte ModuleId,        // the module Identification 0 to 7
                  int       status)          // current status
{
  if(status!=ISDC_OK) return status;

  DAL3_Byte 
    ASICId, PixelId,
    Y, Z,
    OnOff;
  int
    NASIC= I_ASIC_PER_LINE*J_ASIC_PER_LINE;

 // Number of lines per module is equal to number of moodules in ISGRI
 for (DAL3_Byte LineId=0; LineId<IBIS_NUM_BLOCK; LineId++) 
   for (int ByteAddress=0; ByteAddress<IBIS_IBLOCK_LENGTH; ByteAddress++) 
     {
       PixelId= ByteAddress%4;
       ASICId=  (NASIC-1)-Quot(ByteAddress, 4);
       status=  GetXY(ModuleId, LineId, ASICId, PixelId, &Y, &Z);
       OnOff=   (b[ByteAddress]&(1<<LineId))!=0 ? 1 : 0;
       pixelOnOffMap[Y][Z]= OnOff;
     }

 return status;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Consult the document SIG-ISGRI-FMo-1071-99 for the details of this computation. See page 15 in particular.
//                 NOTE: this program is implemented for contigously alloted memory for a, A, m, 
//                                and M dynamic arrays are still supported.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

int GetXY(DAL3_Byte ModuleId, // Module identification number
          DAL3_Byte LineId,   // line identification number
	  DAL3_Byte ASICId,   // ASIC identification number
          DAL3_Byte PixelId,  // pixel identification number
	  DAL3_Byte *Y,       // pixel detector coordinate
          DAL3_Byte *Z)       // pixel detector coordinate 
{
  DAL3_Byte
    YconvRight[4][4]= { {0, 1, 3, 2}, {1, 0, 2, 3}, {0, 1, 3, 2}, {1, 0, 2, 3} },
    ZconvRight[4][4]= { {0, 2, 3, 1}, {0, 2, 3, 1}, {1, 3, 2, 0}, {1, 3, 2, 0} };

  if(ModuleId<=3) 
    {
      *Y= 64+Quot(ASICId, 4)*4;
      *Z= (3-ModuleId)*32+(7-LineId)*4;
    }
  else
    {
       // Setup the matrices if necessary. To permute a columns send in the line.
      for(int i=0; i<4; i++) permute(YconvRight[i], 1, sizeof(DAL3_Byte), 0, 2);
      for(int i=0; i<4; i++) permute(YconvRight[i], 1, sizeof(DAL3_Byte), 1, 3);
      for(int i=0; i<4; i++) permute(ZconvRight[i], 1, sizeof(DAL3_Byte), 0, 2);
      for(int i=0; i<4; i++) permute(ZconvRight[i], 1, sizeof(DAL3_Byte), 1, 3);

      *Y= Quot((63-ASICId), 4)*4;
      *Z= (7-ModuleId)*32+LineId*4;
    }
  *Y+= YconvRight[PixelId][ASICId%4];
  *Z+= ZconvRight[PixelId][ASICId%4];
  
  return ISDC_OK;
}


// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //  Consult the document SIG-ISGRI-FMo-1071-99 for the details of this computation. See page 15 in particular.
// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// int InvGetXY(DAL3_Byte Y,          // pixel detector coordinate    
//              DAL3_Byte Z,          // pixel detector coordinate    
//              DAL3_Byte *ModuleId,  // Module identification number 
//              DAL3_Byte *LineId,    // line identification number   
//              DAL3_Byte *ASICId,    // ASIC identification number   
//              DAL3_Byte *PixelId)   // pixel identification number  
// {
//  DAL3_Byte 
//    Column,
//    y, z,
//    a[4][4]= { {0, 0, 1, 1}, {0, 0, 1, 1}, {3, 3, 2, 2}, {3, 3, 2, 2} },
//    p[4][4]= { {0, 2, 1, 3}, {1, 3, 0, 2}, {2, 0, 3, 1}, {3, 1, 2, 0} };


//  if(Y>=64) 
//    {
//      *ModuleId= 3-Quot(Z, 32); 
//      y= Y-64;
//      z= Z-32*(3-*ModuleId);
//      *LineId= 7-Quot(z, 4);
//      Column= Quot(y, 4);
//      y-= 4*Column;
//      z-= 4*(7-*LineId);
//      *ASICId= 4*Column+a[y][z];
//      *PixelId= p[y][z];
//    }
//  else 
//    {
//      int i;
//      // Setup the matrices if necessary. To permute a columns send in the line.  
//      for(i=0; i<4; i++) permute(a[i], 1, sizeof(DAL3_Byte), 0, 2);
//      for(i=0; i<4; i++) permute(a[i], 1, sizeof(DAL3_Byte), 1, 3);
//      // to permute a lines send in the columns 
//      permute_line(a[0], a[2], 4*sizeof(DAL3_Byte));
//      permute_line(a[1], a[3], 4*sizeof(DAL3_Byte));

//      *ModuleId= 7-Quot(Z, 32);
//      y= Y;
//      z= Z-32*(7-*ModuleId);
//      *LineId= Quot(z, 4);
//      Column= 16-Quot(y, 4);
//      y-= 4*(16-Column);
//      z-= 4*(*LineId);
//      *ASICId= 4*(Column-1)+a[y][z];
//      *PixelId= p[y][z];
//    }

//  return ISDC_OK;
// }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Permute elements of given size
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void permute(void   *v,
             long   n,
             size_t s,
             long   i,
             long   j)
{
  if(n<1) return;
  
  void *p= (void *)calloc(1, s);
  memcpy((char *)p, (char *)v+i*s, s);
  memcpy((char *)v+i*s, (char *)v+j*s, s); 
  memcpy((char *)v+j*s,(char *) p, s);
  
  if(p) free(p);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                     Permute lines of given size
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void permute_line(void   *v, // pointer to line
		  void   *w, // pointer to line
                  size_t s)
{
  if(s<sizeof(char)) return;

  void *p= (void *)calloc(1, s);
  memcpy(p, v, s);
  memcpy(v, w, s); 
  memcpy(w, p, s);
  
  if(p) free(p);
}
