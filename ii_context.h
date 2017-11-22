#ifndef __SHADOW_BUILD_H__
#define __SHADOW_BUILD_H__

#define COMPONENT_NAME           "ii_context"
#define COMPONENT_VERSION        "0.1"

// ISDC includes:
#include "isdc.h"
#include "dal3gen.h"
#include "dal3aux.h"
#include "dal3hk.h"
#include "dal3ibis.h"

// Program includes
#include "ii_context_types.h"
#include "HK3stuff/HK3stuff.h"
#include "IsgriGen/IsgriGen.h"
#include "Tree/tree_mgr.h"

// Functions list in ii_shadow_build_read.cpp

int GetPars(dal_element   **newGRP,          // DOL to the SCW group
            dal_element   **idxREVcontext,   // DOL to the index of REVOLUTION contexts
            dal_element   **idxHK3maps,      // DOL to the index of HK3 noisy maps
            int *revolution,
             unsigned char *detailedOutput   // Detailed Output
	    );           
	    

int ChkFilesExist(dal_element   *NewGRP,         // DOL to the SWG
		  OBTime        *StartTime,      // Start time of the SCW (OBT)
 		  OBTime        *EndTime,        // End time of the SCW (OBT)
                  dal_element   *idxREVcontext,  // DOL to the index of the REV Contexts                                  
                  dal_element   **REVcontext,    // Output: DOL to the REV Context to be used
                  unsigned char detailedOutput); //output


int GetREVcontext(dal_element   *REVcontext,       // DOL to the REV context
		  int           Revol,             // Revolution number of the SCW
                  OBTime        OBTend,            // End Time of the SCW		                  
		  dal_double    **LowThreshMap,    // Output: Map of Low Thresholds (keV)
		  dal_int       **ONpixelsREVmap,  // Output: Map of Pixels Status for this REV
		  unsigned char detailedOutput);

int GetHK3status(dal_element   *idxNoisy,        // DOL to the HK3 noisy maps
		 OBTime        SCWstart,         // SCW Starting time
		 OBTime        SCWend,           // SCW Finishing tine
		 dal_int       **ONpixelsHK3map, // Output: Map[y][z] of percent of Time ON
                 unsigned char detailedOutput);

int GetHKdata(dal_element   *NewGRP, 
              dal_element   *DTtable,
              char          *InGTIName,
              OBTime        **GTIstart, 
              OBTime        **GTIstop, 
              int           *NumIntervals,
              OBTime        **GTIstartPerMCE,
              OBTime        **GTIstopPerMCE,
              int           *NumGTIperMCE,
              int           *NumGTIXtra,
              dal_float     ***DeadTimes,
              OBTime        **OBTdeadTimes, 
              long          *NumDeadTimes,
              OBTime        StartTime, 
              OBTime        EndTime,
              unsigned char detailedOutput);

int MkOutputFiles(dal_element   *OSMindex,
                  dal_element   **DOLs,
                  int           NumImaBin,
                  int           NumTime,
                  char          *TemplateName,
                  int           status);

int WriteAttributes(dal_element           *Element,
                    const unsigned long   code,
                    const T_OSM_ATTRIBUTE values,
                    int                   InStatus);

int UpdateIndex(dal_element   *OSMindex,
                dal_element   **DOLs,
                int           NumImaBin,
                unsigned char detailedOutput,
                int           status);

void Abort(dal_element *NewGRP,
           const char  *msg,
           int         status);

// Functions list in ii_shadow_build_image.cpp

int SpecNoisyPixels(dal_byte      *IsgrY,           // Table of Y coordinate of events
		    dal_byte      *IsgrZ,           // Table of Z coordinate of events 
		    dal_double    *IsgrE,           // Table of Energy of events
		    long          NumEvents,        // Number of ISGRI events			  
		    OBTime        SCWstart,         // SCW start
		    OBTime        SCWend,           // SCW end
		    OBTime        *GTIstart,        // Good time intervals, starting times               
		    OBTime        *GTIstop,         // Good time intervals, finishing times              
		    int           NumGTI,           // Number of good time intervals                     
		    OBTime        **GTIstartPerMCE, // Good time intervals per module, starting times    
		    OBTime        **GTIstopPerMCE,  // Good time intervals per module, stopping times    
		    int           *NumGTIperMCE,    // Number of good time intervals  per module 
		    dal_float     **DeadTimes,      // DeadTimes for each module, over the SCW
		    OBTime        *OBTdeadTimes,    // ISGRI DeadTimes dates over the SCW
		    long          NumDeadTimes,     // Number ISGRI DeadTimes over the SCW
		    dal_int       **ONpixelsREVmap, // Map of Pixels Status for this REV (REV context)
		    dal_int       **ONpixelsHK3map, // Map of Pixels Status for this SCW (HK3 data)
		    dal_int       **SelectFlagMap,  // Map of Noisy Pixels, as detected by SELECT_FLAG method
		    dal_double    **LowThreshMap,   // Map of Low Thresholds (keV)
		    int           revol_scw,        // Revolution number
		    int           LTMode,        // Revolution number
		    dal_double    **SpecNoisyMap,   // Output: Remaining Noisy pixels map
		    int           *NumSpecNoisy,    // Output: Number of found noisy pixels
		    unsigned char detailedOutput);  // Detailed output

int ComputeTimeEffMap(OBTime        OBTstart,         // Time Bin starting time
		      OBTime        OBTend,           // Time Bin finishing time 
		      OBTime        *GTIstart,        // Good time intervals, starting times               
		      OBTime        *GTIstop,         // Good time intervals, finishing times              
		      int           NumGTI,           // Number of good time intervals                     
		      OBTime        **GTIstartPerMCE, // Good time intervals per module, starting times    
		      OBTime        **GTIstopPerMCE,  // Good time intervals per module, stopping times    
		      int           *NumGTIperMCE,    // Number of good time intervals  per module  
		      dal_float     **DeadTimes,      // DeadTimes for each module, over the SCW
		      OBTime        *OBTdeadTimes,    // ISGRI DeadTimes dates over the SCW
		      long          NumDeadTimes,     // Number ISGRI DeadTimes over the SCW
		      dal_int       **ONpixelsREVmap, // Map of Pixels Status for this REV (REV context)
		      dal_int       **ONpixelsHK3map, // Map of Pixels Status for this SCW (HK3 data)
		      dal_int       **SelectFlagMap,  // Map of Noisy Pixels, as detected by SELECT_FLAG method
		      dal_double    **TimeEffMap,     // Output: ISGRI Time Efficiency map
		      dal_double    *MeanTimeEff,     // Output: ISGRI Average Time Efficiency
		      dal_double    *OnTime,          // Output: ISGRI ONTIME (sec)
		      dal_double    *DeadC,           // Output: ISGRI DeadTime Correction factor (%)
		      unsigned char detailedOutput);  // Detailed output

int MkImage(dal_byte      *IsgriY,        // Detector coordinate on Y                                 
            dal_byte      *IsgriZ,        // Detector coordinate on Z                                 
            dal_double    *IsgriEnergy,   // Phase height amplitude raw / corrected or deposed energy 
            long          NumRow,         // Number of events                                         
            dal_float     **EnergyBounds, // Energy/channel intervals                                 
            int           NumImaBin,      // Number of energy intervals
            dal_double    ***IsgriSHD,    // Output: resultant image 
	    long          *NumEvents);    // Output: Number of events in these Ebands
 
int MkeffImage(dal_double    **TimeEffMap,    // Pixels Time Efficiency map                                        
	       dal_double    **LowThresImage, // Low Threshold map (keV)
	       dal_double    **SpecNoisyMap,  // Map of Noisy Pixels, as detected by spectral method
	       dal_float     **EnergyBounds,  // Energy/channel intervals                                    
	       int           NumImaBin,       // Number of energy bands                                      
	       int           revol_scw,       // Revolution number
	       int           LTMode,       // Revolution number
	       dal_double    ***IsgriEffSHD,  // Output: Image efficiency map, one per energy band                   
	       dal_double    *MeanEff);       // Output: Means of the efficiency maps to be calculated

int WriteImage(dal_element   *NewGRP,        // Pointer to the Science window                           
	       dal_element   **image,        // Pointer to the object in which image is written         
	       dal_element   **efficiency,   // Pointer to the object in which efficiencies are written 
	       dal_double    ***IsgriSHD,    // Image matrix                                            
	       dal_double    ***IsgriEffSHD, // Efficiency matrix                                       
	       OBTime        StartTime,      // Start time of science window                            
	       OBTime        EndTime,        // End Time of science window                              
	       OBTime        t0,             // Lower boundary of time interval                         
	       OBTime        t1,             // Upper boundary of time interval                         
	       dal_float     **EnergyBounds, // energy/channel intervals                                
	       int           NumImaBin,      // number of energy intervals                              
	       char          *BndTyp,        // band type                                               
	       char          *ChTyp,         // channel type                                            
	       double        OnTime,         // Effective time computed with global GTIs  
	       double        DeadC,          // Dead Time Correction factor                    
	       double        MeanTimeEff);   // Mean of the Time Efficiency map of the current Time Bin

void SetImageMCEtoZero(double **Image, 
		       int    MCEid);

double LTfunction(double Energy,
		  double LTkeV,
		  int revol_scw,
          int LTMode);

double ARF(double Energy);


int ReadProTable(dal_element *pTabPtr,
		 double      *my_tStart,
		 double      *C11_90,
		 double      *C20_27,
		 double	     *C40_50, 
		 double	     *C50_70, 
		 double	     *Csup130, 
		 double	     *Csup39, 
		 double	     *C20_550, 
		 double	     *Cions);


int EnerDriftCorr(dal_double  **LowThreshMap,
                  int revol_scw
		  );

int ibis_energyIsgrHkCal(dal_element *workGRP,
                         OBTime       obtStart,
                         OBTime       obtEnd,
                         double      *meanT,
                         double       meanBias[8],
                         int          chatter,
                         int          status);

#endif

