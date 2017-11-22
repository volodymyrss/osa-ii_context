#ifndef __SHADOW_BUILD_TYPES__
#define __SHADOW_BUILD_TYPES__

// ================================ Personal defines ================================
#define FWHM0                4.80
#define FWHM1                0.0017
/* constant parameters for the energy correction*/
#define OFF_SCALE0          -1.997
#define G_SCALE0             1.0184
#define G_SCALE1             0.0000089
#define PAR1_GAIN_corrPH1    2.047
#define PAR2_GAIN_corrPH1   -0.00061
#define PAR1_OFFSET_corrPH1 -5.655
#define ZERO       1e-10
#define Pi         3.14159265
#define NUM_PHA    2048 // maximum number of phase height channels 
//#define FAULTY_REV_CTXT  272l // SPR 4262, commented with SCREW 1793
#define TIME_EFF_THRESH  0.01 
          
// ============================= Error ranges and codes ============================= 
#define I_ISGR_RANGE                          (I_ERROR_CODE_START-20000)
#define I_ISGR_SCW_ERR                        (I_ISGR_RANGE-1000)
#define I_ISGR_OSM_ERR                        (I_ISGR_SCW_ERR-200)
#define ERR_ISGR_OSM_UNUSED                   (I_ISGR_OSM_ERR-1)    // Unused error                               
#define ERR_ISGR_OSM_TABLE_EMPTY              (I_ISGR_OSM_ERR-2)    // Data table is empty                        
#define ERR_ISGR_OSM_NROWS_NVALUES            (I_ISGR_OSM_ERR-3)    // Number of rows != number of values         
#define ERR_ISGR_OSM_DEREFERENCE              (I_ISGR_OSM_ERR-4)    // Dereferencing error                        
#define ERR_ISGR_OSM_FILE_NOTFOUND            (I_ISGR_OSM_ERR-5)    // Data i/o file not found => continue        
#define ERR_ISGR_OSM_FILE_NECESSARY_NOTFOUND  (I_ISGR_OSM_ERR-6)    // Data necessary i/o file not found => abort 
#define ERR_ISGR_OSM_OUTPUT_FILE_CREATION     (I_ISGR_OSM_ERR-7)    // Output file creation error => abort        
#define ERR_ISGR_OSM_OUTPUT_INDEX_CREATION    (I_ISGR_OSM_ERR-8)    // Index file creation error => abort         
#define ERR_ISGR_OSM_MEMORY_ALLOC             (I_ISGR_OSM_ERR-9)    // Memmory allocation error                   
#define ERR_ISGR_OSM_SHD_INDX                 (I_ISGR_OSM_ERR-10)   // Shadowgram index does not exist            
#define ERR_ISGR_OSM_EFFI_SHD_INDX            (I_ISGR_OSM_ERR-11)   // Shadowgram efficiency index does not exist 
#define ERR_ISGR_OSM_DSP_INDX                 (I_ISGR_OSM_ERR-12)   // Spectral index does not exist              
#define ERR_ISGR_OSM_LCR_INDX                 (I_ISGR_OSM_ERR-13)   // Light curve index does not exist           
#define ERR_ISGR_OSM_WRITE_STATITICS          (I_ISGR_OSM_ERR-14)   // Impossible to write statistics             
#define ERR_ISGR_OSM_WRITE_SHADOWGRAM         (I_ISGR_OSM_ERR-15)   // Impossible to write image                  
#define ERR_ISGR_OSM_WRITE_EFFICIENCY_SHD     (I_ISGR_OSM_ERR-16)   // Impossible to write image efficiency       
#define ERR_ISGR_OSM_WRITE_SPECTRA            (I_ISGR_OSM_ERR-17)   // Impossible to write spectra                
#define ERR_ISGR_OSM_WRITE_EFFICIENCY_DSP     (I_ISGR_OSM_ERR-18)   // Impossible to write spectra efficiency     
#define ERR_ISGR_OSM_WRITE_LIGHTCURVES        (I_ISGR_OSM_ERR-19)   // Impossible to write lightcurve             
#define ERR_ISGR_OSM_WRITE_EFFICIENCY_LCR     (I_ISGR_OSM_ERR-20)   // Impossible to write lightcurve efficiency  
#define ERR_ISGR_OSM_DATA_INCONSISTENCY       (I_ISGR_OSM_ERR-21)   // Some data inconsistency                    

// ============================= Error ranges and codes ============================= 
// (more general and are used in other programs, usually standard support functions) 
#define I_PERSO_ERR                           (I_ISGR_OSM_ERR-25)
#define I_PERSO_ERR_ALLOCATION                (I_PERSO_ERR-1)  
#define I_PERSO_ERR_NOTOKEN                   (I_PERSO_ERR-2)  
#define I_PERSO_ERR_POSITION                  (I_PERSO_ERR-3)  
#define I_PERSO_ERR_DEREFERENCE               (I_PERSO_ERR-4)           // dereferencing error                 
#define I_PERSO_ERR_REBINNING                 (I_PERSO_ERR-5)           // rebinning was unseccessfull

// ================================= Template names ================================= 
#define ISGR_SHD_IDX_TPL      "ISGR-DETE-SHD-IDX"    // Detector image index                            
#define ISGR_SHD_EFFI_IDX_TPL "ISGR-EFFI-SHD-IDX"    // Efficency image index                           
#define ISGR_SHD_TPL          "ISGR-DETE-SHD"        // Detector image shadowgram                       
#define ISGR_SHD_EFFI_TPL     "ISGR-EFFI-SHD"        // Efficency image shadowgram                      
#define ISGR_EVTS_RAW_TPL     "ISGR-EVTS-RAW"        // ISGRI event by event                            
#define ISGR_EVTS_PRW_TPL     "ISGR-EVTS-PRW"        // ISGRI packet data event by event                
#define ISGR_EVTS_SRW_TPL     "ISGR-EVTS-SRW"        // ISGRI secondary packet data event by event      
#define ISGR_DEAD_STA         "ISGR-DEAD-SCP"        // Dead times                                      
#define ISGR_EVTS_PRP_TPL     "ISGR-EVTS-PRP"        // Prepares ISGRI science data                     
#define ISGR_NMAP_STA_TPL     "ISGR-NMAP-STA"        // ISGRI switch list pixel from HK                 
#define ISGR_NEVT_STA_TPL     "ISGR-NEVT-STA"        // ISGRI switch list pixel from science            
#define ISGR_EVTS_COR_TPL     "ISGR-EVTS-COR"        // Corrected ISGRI science event data              
#define ISGR_GNRL_GTI_IDX     "ISGR-GNRL-GTI-IDX"    // Index of Good Time Interval definition          
#define ISGR_GNRL_GTI_TPL     "ISGR-GNRL-GTI"        // Good Time Interval definition                   
#define ISGR_NOIS_CRW_IDX_TPL "ISGR-NOIS-CRW-IDX"    // Index of pixel status for ISGRI (dynamic)       
#define ISGR_NOIS_CRW_TPL     "ISGR-NOIS-CRW"        // Pixel status for ISGRI (dynamic)                
#define ISGR_LTHR_STA_IDX_TPL "ISGR-LTHR-STA-IDX"    // Index of pixel low threshold for ISGRI (static) 
#define ISGR_LTHR_STA_TPL     "ISGR-LTHR-STA"        // Pixel lowthreshold for ISGRI (static)           
#define ISGR_PXLP_CFG         "ISGR-PXLP-CFG"        // context PIXEL configuration                     
#define ISGR_ASIP_CFG         "ISGR-ASIP-CFG"        // context ASIC  configuration                      
#define ISGR_NOIS_CPR_IDX     "ISGR-NOIS-CPR-IDX"
#define ISGR_NOIS_CPR         "ISGR-NOIS-CPR"
#define ISGR_CTXT_GRP_IDX     "ISGR-CTXT-GRP-IDX"
#define ISGR_CTXT_GRP         "ISGR-CTXT-GRP"
#define GROUP                 "GROUPING"
#define IBIS_GNRL_GTI_IDX     "IBIS-GNRL-GTI-IDX"
#define IBIS_GNRL_GTI         "IBIS-GNRL-GTI"
#define DS_IREM_CAL           "IBIS-IREM-CAL"
#define DS_ISGR_HK            "IBIS-DPE.-CNV"
#define KEY_DEF_TEMP        -8.0    /* default when HK1 missing */
#define KEY_DEF_BIAS      -120.0    /* default when HK1 missing */
#define DS_ISGR_SWIT      "IBIS-SWIT-CAL"
#define KEY_MIN_TEMP       -50.5    /* to disregard RAW 0 */
#define KEY_RMS_TEMP         1.2    /* disregard MDU Temp */
#define KEY_MCE_BIAS "I0E_MCDTE_MBIAS"
#define KEY_MAX_BIAS       155.0    /* to disregard RAW 0 */
#define KEY_MCE_TEMP "I0E_MTEMP2_MMDU"
#define SEC_DELTA_MIN       25      /* minimal time range to search HK1 */


// =========================================== Attributes appearing in the output headers ==================================== 
//            Name of attibute |    Format      |           Descrition                | DETE-SHD | EFFI-SHD | LCR | DSP | STAT 
// =========================================================================================================================== 
#define OBTSTART  "OBTSTART"   // OBT_format : OBT of the start of the Science Window | Yes      | Yes      | Yes | Yes | Yes  
#define OBTEND    "OBTEND"     // OBT_format : OBT of the end of the Science Window   | Yes      | Yes      | Yes | Yes | Yes  
#define TSTART    "TSTART"     // Real       : Start time of the observation          | Yes      | Yes      | Yes | Yes | No   
#define TSTOP     "TSTOP"      // Real       : End time of the observation            | Yes      | Yes      | Yes | Yes | No   
#define TFIRST    "TFIRST"     // Real       : Start time of the observation          | Yes      | Yes      | Yes | Yes | No   
#define TLAST     "TLAST"      // Real       : End time of the observation            | Yes      | Yes      | Yes | Yes | No   
#define TELAPSE   "TELAPSE"    // Real       : Total observation elapse time          | Yes      | Yes      | Yes | Yes | No   
#define CHANTYPE  "CHANTYPE"   // String     : PHA, PI or ENERGY                      | Yes      | Yes      | Yes | Yes | No   
#define CHANMIN   "CHANMIN"    // Integer    : Lower bound of band in channels        | Yes      | Yes      | Yes | No  | No   
#define CHANMAX   "CHANMAX"    // Integer    : Upper bound of band in channels        | Yes      | Yes      | Yes | No  | No   
#define E_MIN     "E_MIN"      // Real       : Lower bound of band in keV             | Yes      | Yes      | Yes | No  | No   
#define E_MAX     "E_MAX"      // Real       : Upper bound of band in keV             | Yes      | Yes      | Yes | No  | No   
#define BANDTYPE  "BANDTYPE"   // String     : ENERGY or CHANNEL                      | Yes      | Yes      | Yes | Yes | No   
#define OBT_ACQ   "OBT_ACQ"    // OBT_format : OBT acquisition time                   | NO       | No       | Yes | Yes | No   
#define BINTIME   "BINTIME"    // Integer    : Binning time                           | NO       | No       | Yes | NO  | No   
#define NUMRANGE  "NUMRANGE"   // Integer    : Number of energy ranges                | NO       | No       | Yes | NO  | No   
#define INT_TIME  "INT_TIME"   // Integer    : Integration time                       | NO       | No       | No  | YES | No   
#define ERTFIRST  "ERTFIRST"   // String     : Earth received time of the first packet| YES      | YES      | YES | YES | YES  
#define ERTLAST   "ERTLAST"    // String     : Earth received time of the last packet | YES      | YES      | YES | YES | YES  
#define REVOL     "REVOL"      // Integer    : Revolution number                      | YES      | YES      | YES | YES | YES  
#define SWID      "SWID"       // String     : Science Window identifier              | YES      | YES      | YES | YES | YES  
#define SWTYPE    "SW_TYPE"    // String     : Type of the Science Window             | YES      | YES      | YES | YES | YES  
#define SWBOUND   "SWBOUND"    // String     : Reason for Science Window ending       | YES      | YES      | YES | YES | YES  
#define BCPPID    "BCPPID"     // String     : Broadcast packet pointing ID at start  | YES      | YES      | YES | YES | YES  
#define PREVSWID  "PREVSWID"   // Stirng     : Id previous Science Window             | YES      | YES      | YES | YES | YES  
#define OUTPUTLEV "ISDCLEVL"   // String     : ISDC Level constant                    | YES      | YES      | YES | YES | YES  
#define ONTIME    "ONTIME"
#define LIVETIME  "LIVETIME"
#define EXPOSURE  "EXPOSURE"
#define DEADC     "DEADC"
#define RISE_MIN  "RISE_MIN"   // Raw Rise time
#define RISE_MAX  "RISE_MAX"   // Raw Rise time



#define MEMLOC    "MEMBER_LOCATION"

// =========================================== Access codes to these Attributes ==================================== 
#define OBTSTART_NUM    0x00000001 
#define OBTEND_NUM      0x00000002
#define TSTART_NUM      0x00000004
#define TSTOP_NUM       0x00000008
#define TELAPSE_NUM     0x00000010
#define CHANTYPE_NUM    0x00000020
#define CHANMIN_NUM     0x00000040
#define CHANMAX_NUM     0x00000080
#define E_MIN_NUM       0x00000100
#define E_MAX_NUM       0x00000200
#define BANDTYPE_NUM    0x00000400
#define OBT_ACQ_NUM     0x00000800
#define BINTIME_NUM     0x00001000
#define NUMRANGE_NUM    0x00002000
#define INT_TIME_NUM    0x00004000
#define ERTFIRST_NUM    0x00008000
#define ERTLAST_NUM     0x00010000
#define REVOL_NUM       0x00020000
#define SWID_NUM        0x00040000
#define SWTYPE_NUM      0x00080000
#define SWBOUND_NUM     0x00100000
#define BCPPID_NUM      0x00200000
#define PREVSWID_NUM    0x00400000
#define OUTPUT_NUM      0x00800000
#define TFIRST_NUM      0x01000000
#define TLAST_NUM       0x02000000
#define ONTIME_NUM      0x04000000
#define LIVETIME_NUM    0x08000000
#define EXPOSURE_NUM    0x10000000
#define DEADC_NUM       0x20000000
#define RISE_MIN_NUM    0x40000000
#define RISE_MAX_NUM    0x80000000

// ======================================= Attributes Structure ====================================
#define T_OSM_ATTRIBUTE  struct t_osm_attribute

T_OSM_ATTRIBUTE { 
  OBTime obtstart;                            // - OBT of start of the Science Window in OBT format  
  OBTime obtstop;                             // - OBT of end of the Science Window in OBT format    
  double tstart;                              // - OBT of the start of the Science Window in days    
  double tstop;                               // - OBT of the end of the Science Window in days      
  double tfirst;                              // - Time of the first data element in days            
  double tlast;                               // - Time of the last data element in days             
  double telapse;                             // - Time interval (in seconds) obtained as difference 
                                              // between the start and stop times of an observation. 
                                              // Any gaps due to Earth occultation, or high          
                                              // background counts and/or other anomalies,            
                                              // are included.                                       
  char   chantype[DAL_MAX_ATTRIBUTE_SIZE];    // - Channel type PHA | PI                             
  int    chanmin;                             // - Lowest channel of the energy range                
  int    chanmax;                             // - Highest channel of the energy range               
  double e_min;                               // - Lower bound of the energy range in keV            
  double e_max;                               // - Upper bound of the energy range in keV            
  char   bandtype[DAL_MAX_ATTRIBUTE_SIZE];    // - Type of energy band ENERGY | CHANNEL              
  OBTime obt_acq;
  int    bintime;
  int    numrange;
  int    int_time;
  char   ertfirst[DAL_MAX_ATTRIBUTE_SIZE];  
  char   ertlast[DAL_MAX_ATTRIBUTE_SIZE];     
  int    revol;     
  char   swid[DAL_MAX_ATTRIBUTE_SIZE];     
  char   sw_type[DAL_MAX_ATTRIBUTE_SIZE];   
  char   swbound[DAL_MAX_ATTRIBUTE_SIZE];   
  char   bcppid[DAL_MAX_ATTRIBUTE_SIZE];    
  char   prevswid[DAL_MAX_ATTRIBUTE_SIZE]; 
  char   outputlevel[DAL_MAX_ATTRIBUTE_SIZE];
  double ontime;                              // - total "good" time (in seconds) on 'source'.          
                                              // If a 'Good Time Interval' (GTI) table is provided,    
                                              // ONTIME should be calculated as the sum of those       
                                              // intervals. Corrections for instrumental 'dead time'   
                                              // effects are NOT included.                             
  double livetime;                            // - total time (in seconds) on source, corrected for    
                                              // the 'total' instrumental dead time effect. The ratio  
                                              // LIVETIME/ONTIME therefore gives the dead time         
                                              // correction value (which hence lies in the range       
                                              // 0.0-1.0).                                             
  double exposure;                            // - total time (in seconds) on source, corrected for    
                                              // any relevant quantity used to calculate the           
                                              // corrected count rate. The value can include            
                                              // correction which are not directly related with time    
                                              // (e.g. collimation efficiency or vignetting). This     
                                              //  keyword is a mean value when appropriate.            
  double deadc;                               // - total correction factor for any dead time           
                                              // effect (i.e. LIVETIME/ONTIME), and lies in the range  
                                              // 0.0-1.0. Thus the multiplication of this value by     
                                              // the ONTIME value gives the 'effective' integration    
                                              // time or LIVETIME (TIMEDEL in the case of a light      
                                              // curve). Since the total dead time of a given dataset  
                                              // can be the result of a multitude of instrumental/     
                                              // processing effects (especially related to the         
                                              // particular experiment, and/or processing by an        
                                              // onboard computer, and/or spacecraft operations), it   
                                              // is recommended that as well as including the total    
                                              // correction factor in the DEADC keyword,               
                                              // instrument-specific keywords are used to keep a       
                                              // record of the original value for the individual       
                                              // correction factors.                                   
  int rise_min;
  int rise_max;
  
};

#endif
