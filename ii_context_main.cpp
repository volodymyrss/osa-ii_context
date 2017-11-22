
#include "ii_context.h"

int main(int argc, char *argv[]) {
    int status = ISDC_OK, // ISDC_OK means no without mishaps                              
            RILstatus = ISDC_OK,
            HowMany = 5, // Max EFF maps to write at once: for memory considerations      
            NumImaBin = 1, // number of energy channels                                   
            NoisyDetFlag = 0, // Spectral Noisy Pixels Detection Flag
            LTMode = 0; // Spectral Noisy Pixels Detection Flag
    unsigned char
    detailedOutput = 1; // Detailed output Yes = 1 No = 0 = default                     
    char
    UserRowFilter[DAL_FILE_NAME_STRING] = "", // User-defined ROW filter on ISGRI events
            InGTIName[DAL_FILE_NAME_STRING] = "",
            outputLevel[PIL_LINESIZE] = "";
    dal_byte
    MinRiseTime = 0,
            MaxRiseTime = 0x7F;

    dal_float
            **EnergyBounds = NULL; // Energy bounds                               
    dal_double
    SCWduration, // Size of SCW
            TimeLen; // Size of time bins
    dal_element
            *idxREVcontext = NULL, // DOL to the index of ISGRI REVOLUTION Contexts
            *idxHK3maps = NULL, // DOL to the index of ISGRI HK3 noisy Maps
            *NewGRP = NULL, // DOL to the SWG
            *REVcontext;


    int chatter = 4;

    int revolution;

    //hk1 variables
    dal_element *isgrHK1_Ptr = NULL;
    double meanT, meanBias[8]; /* mean of the 8 mce temperatures */
    dal_dataType DALtype_hk1;
    double tstart_grp;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    //                              Initialize the common library stuff
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    if ((status = CommonInit(COMPONENT_NAME, COMPONENT_VERSION, argc, argv)) != ISDC_SINGLE_MODE) {
        RILstatus = RILlogMessage(NULL, Log_1, "CommonInit status = %d", status);
        RILstatus = RILlogMessage(NULL, Log_1, "number of command line arguments = %d", argc);
        RILstatus = RILlogMessage(NULL, Log_1, "program name : %s", argv[0]);
        RILstatus = RILlogMessage(NULL, Error_2, "Program aborted : could not initialize.");
        CommonExit(status);
    }

    RILstatus = RILlogMessage(NULL, Log_1, "---------- Retrieve program PARAMETERS ----------");
    status = GetPars(&NewGRP, &idxREVcontext, &idxHK3maps, &revolution, &detailedOutput);
    if (status != ISDC_OK) Abort(NewGRP, "Program aborted with status %d : could not retrieve parameters.", status);


    double RevolStart, RevolEnd;
    OBTime *RevolOBT;
    double RevolIJD[2] = {RevolStart, RevolEnd};
    int tmp_revol;
    status = DAL3AUXgetRevolutionBounds(revolution, DAL3AUX_INPUT_REVOL_NUM, &tmp_revol, &RevolStart, &RevolEnd, status);

    status = DAL3AUXconvertIJD2OBT(NewGRP,
                                    TCOR_ANY,
                                    2,
                                    RevolIJD,
                                    RevolOBT,
                                    status);

    status = ChkFilesExist(NewGRP, &(RevolOBT[0]), &(RevolOBT[1]),
                            idxREVcontext, &REVcontext,
                            detailedOutput);



    dal_element
            *DTtable = NULL, // DOL to Table containing the dead time values 
            *idxRAWshad = NULL, // DOL to Index for RAW images                                          
            *idxEFFshad = NULL; // DOL to Index for EFF images            

    // Check files and retrieve SCW start/end
    

    status = ISDC_OK;


    ///////////////////////////////////////////////////////////////////////////////////////////////////
    //                      Read the REVOLUTION CONTEXT and the HK3 status                                             
    ///////////////////////////////////////////////////////////////////////////////////////////////////

    RILstatus = RILlogMessage(NULL, Log_1, "-------- Get REVOL Context and HK3 status --------");

    // Retrieve Pixel Revolution Status
    //
    dal_double **LowThreshMap = NULL;
    if ((LowThreshMap = (dal_double **) calloc(ISGRI_SIZE, sizeof (dal_double *))) == NULL)
        Abort(NewGRP, "Error in allocating memory for LowThreshold image  map.", status);
    for (int i = 0; i < ISGRI_SIZE; i++)
        if ((LowThreshMap[i] = (dal_double *) calloc(ISGRI_SIZE, sizeof (dal_double))) == NULL)
            Abort(NewGRP, "Error in allocating memory for LowThreshold image map : i = %d.", i);


    dal_int **ONpixelsREVmap = NULL;
    if ((ONpixelsREVmap = (dal_int**) calloc(ISGRI_SIZE, sizeof (dal_int*))) == NULL)
        Abort(NewGRP, "Error in allocating memory for pixels on / off map.", status);
    for (int i = 0; i < ISGRI_SIZE; i++)
        if ((ONpixelsREVmap[i] = (dal_int*) calloc(ISGRI_SIZE, sizeof (dal_int))) == NULL)
            Abort(NewGRP, "Error in allocating memory for  pixels on / off map.", status);
    if ((status = GetREVcontext(idxREVcontext, revolution, RevolEnd,
            LowThreshMap, ONpixelsREVmap, detailedOutput)) != ISDC_OK) {
        RILstatus = RILlogMessage(NULL, Error_1, "Retrieving Revolution Context failed, status %d.", status);
        CommonExit(status);
    }

    FILE *f = fopen("lowthreshmap_uncorr.txt", "w"); // horrible
    for (int y = 0; y < ISGRI_SIZE; y++)
        for (int z = 0; z < ISGRI_SIZE; z++) {
            fprintf(f, "%i %i %.5lg\n", y, z, LowThreshMap[y][z]);
        }
    fclose(f);



    // Retrieve Pixel HK3 Status
    dal_int **ONpixelsHK3map = NULL;
    if ((ONpixelsHK3map = (dal_int**) calloc(ISGRI_SIZE, sizeof (dal_int*))) == NULL)
        Abort(NewGRP, "Error in allocating memory for ONpixelsHK3 map[].", ERR_ISGR_OSM_MEMORY_ALLOC);
    for (int y = 0; y < ISGRI_SIZE; y++)
        if ((ONpixelsHK3map[y] = (dal_int*) calloc(ISGRI_SIZE, sizeof (dal_int))) == NULL)
            Abort(NewGRP, "Error in allocating memory for ONpixelsHK3 map[][]", ERR_ISGR_OSM_MEMORY_ALLOC);
    if ((status = GetHK3status(idxHK3maps, RevolStart, RevolEnd, ONpixelsHK3map, detailedOutput)) != ISDC_OK) {
        RILstatus = RILlogMessage(NULL, Error_1, "Error while retrieving HK3 pixels live time, status= %d.", status);
        CommonExit(status);
    }


    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                           COMMON  EXIT
    /////////////////////////////////////////////////////////////////////////////////////////////////////

    Abort(NewGRP, "Program terminated normally", status);
}
