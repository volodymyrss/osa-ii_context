#ifndef __HK3STUFF_H__
#define __HK3STUFF_H__

// ISDC includes:
#include "isdc.h"
#include "dal3gen.h"
#include "dal3hk.h"
#include "dal3ibis.h"

// Program includes
#include "../IsgriGen/IsgriGen.h"                          
#include "../ii_context_types.h"

// Function Declarations
int getPixelLive(dal_element *idxNoisy,    // DOL to the HK3 noisy maps
		 OBTime      OBTstart,     // Starting time
		 OBTime      OBTend,       // Finishing tine
		 dal_double  **PixelLive,  // Output: Map[y][z] of percent of Time ON
                 dal_int     *NumMaps,     // Output: Number of HK3 maps per module
                 int         chatter,      // verbosity level, min 0 to max 3
		 int         status);

int PixelOnOffMap(DAL3_Byte *b,              // the data vector, must be 256 bytes long
                  DAL3_Byte **pixelOnOffMap, // the image [y][z]  to contain on/off pixel status
                  DAL3_Byte ModuleId,        // the module Identification 0 to 7
                  int       status);         // current status

int GetXY(DAL3_Byte ModuleId, // Module identification number
          DAL3_Byte LineId,   // line identification number
	  DAL3_Byte ASICId,   // ASIC identification number
          DAL3_Byte PixelId,  // pixel identification number
	  DAL3_Byte *Y,       // pixel detector coordinate
          DAL3_Byte *Z);      // pixel detector coordinate

void permute(void   *v,
             long   n,
             size_t s,
             long   i,
             long   j);

void permute_line(void   *v, // pointer to line
		  void   *w, // pointer to line
                  size_t s);

#endif
