#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<tgmath.h>
#include<unistd.h>
#include<stdint.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include "ProcessBuffer2.h"
#include "ExtractData.h"
//#include "math_func.h"
#ifdef AJIT
#include "fpop.h"
#include "core_portme.h"
#endif

#ifdef AJIT
#include "ajit_access_routines.h"
int __enable_serial()
{
	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE);
	return(0);
}
#define PRINTF ee_printf
#else
#define PRINTF printf
#endif

double zftemp;	//z_ajit
int ztemp;	//z_ajit

#define pi 3.141592653589
//#define pi 3.14159265
#define ee 1/298.257223563  ///Used to calculate longitude
#define re 6378137          ///Used to calculate latitude
#define C 299792458
#define gm 9.784
#define Rd 287.054
#define K1 77.604
#define K2 382.000
#define g  9.80665
////////////////////////////////

//z: not used
/*	//z_debug
#define GEODESY_REFERENCE_ELLIPSE_WGS84_A                                (6378137.0)
#define GEODESY_REFERENCE_ELLIPSE_WGS84_F_INV                            (298.257223563)
#define GEODESY_REFERENCE_ELLIPSE_WGS84_B                                (6356752.31424518)
#define GEODESY_REFERENCE_ELLIPSE_WGS84_E2                               (0.00669437999014132)
*/

//#define HALFPI    (1.5707963267948966192313216916398)    //!< PI/2.0
#define HALFPI   1.570796325// (1.5707963267948966192313216916398)    //!< PI/2.0

#define NAVSATNO 6

/*	//z_debug
double Latitude,Longitude,Height,rx_clock_bias;
unsigned char checksum;
char str1[10];
char comma[2];
char GIGGAFrame[80];
char GIGSAFrame[60];
char GIGGLLFrame[60];
char GIGSVFrame[60];
char GIRMCFrame[70];
*/
//extern double Raw_PR_Delay[12][8];	//z: time,satellite_number	//z_debug

///PVT Computation

void    NavFindUTCTime(int );			
void    NavComputeSatPos(int,int,int,double);
void    NavComputeUserPosFourSat();
void    NavComputeUserPosSixSat();

void    CompTranspose(int m, int n, double mat1[m][n], double b[n][m]);
void    MatMultiplication(int m,int n,int p, int q,double mat2[][n],double mat3[][q],double prod[][q]);
double   FindDeterminant (int x,double f[4][4]);
void    FindCoFactor(int f,double num[f][f],double fac[f][f] );
void    FindMatrixInverse(int k, double mat4[][k],double inv[][k]);
void    NavComputeDOP(int kk,double mat[][4]);


void    NavComputeSatAzEl(int);
double   NavComputeTroposphericDelay(int count);
void    NavComputeIonosphericDelay( int Count , int32_t TOW);
void    NavComputeSatVelocity(int ,int );
void    NavIC_Compute_Sat_Rx_Range(int SatNo);
void    NavIC_TOWC_Correction(int NavSatNo,int tc,double deltr);
void    NavIC_Cor_ObsPRange(int);
void    ProcessNavIC_PVTData_Main(int PR_Num,int TOWC);
void    NavIC_Init_Processed_Data( );
void    NavIC_Cor1_ObsPRange(int NavSatNo,int TOW,double Raw_PR_Delay);
void    NavComputeUserVelocitySixSat();
void    NavComputeUserVelocityFourSat();
void    Print_Process_Data();
//////////////////////////////////////////////////

/*------------------------------------
//z: temp
void 	NavGIGGAMesage();
void 	NavGIGSAMesage();
void 	NavGIGLLMessage();
void 	NavGIGSVMesage();
void 	NavGIRMCMessage();
------------------------------------*/
unsigned char calc_checksum(const char *s);

//z_debug
//z: Data for 6 satellites for 8sec, Raw_PR_Delay[sec][sat_no]
//z: time,satellite_number
double Raw_PR_Delay[8][6]={{120081493,120919233,125691986,122421616,126287652,128693501},\
{120083407,120919125,125695600,122422710,126287857,128693536},\
{120085339,120919030,125699229,122423819,126288072,128693585},\
{120087263,120918922,125702846,122424917,126288277,128693619},\
{120089202,120918823,125706473,122426028,126288490,128693663},\
{120091137,120918715,125710093,122427134,126288696,128693699},\
{120093092,120918622,125713727,122428256,126288916,128693747},\
{120095032,120918507,125717343,122429361,126289117,128693776}};

void main()
{
	int PR_Num,TOW;
	uint64_t t0;

	#ifdef AJIT
	__enable_serial();
	#endif	

	#ifdef AJIT
	t0 = __ajit_get_clock_time();
	PRINTF("t0=%d, %d\n", t0, t0);
	#endif

	//Step I  : Initialise Processed data
	NavIC_Init_Processed_Data();

	#ifdef AJIT
	t0 = __ajit_get_clock_time();
	PRINTF("t1=%d, %d\n", t0, t0);
	#endif
	
	//PRINTF("NavIC_init over\n");

	//Step II  : Read and Extract Data of all 6 satellites
	
	//z : Temp. read 4 subframe(1 frame) from 1 satellite
	TOW=ReadandExtractData();

	#ifdef AJIT
	t0 = __ajit_get_clock_time();
	PRINTF("t2=%d, %d\n", t0, t0);
	#endif

	//PRINTF("Read_and_Extract data over\n");

	//Step III : Call Process PVTMain
	PR_Num = 0;
	//z: temp
	//for(PR_Num=0; PR_Num < 6; PR_Num++)	//z: PR_Num (pseudo range sec time)
	//{
		ProcessNavIC_PVTData_Main(PR_Num,TOW);
		//PRINTF("Process Navic PVT\n");
		TOW++;
	//}

	#ifdef AJIT
	t0 = __ajit_get_clock_time();
	PRINTF("t3=%d, %d\n", t0, t0);
	#endif

	//Step IV  : Print Processed Data
	//z: temp	
	Print_Process_Data();

	#ifdef AJIT
	t0 = __ajit_get_clock_time();
	PRINTF("t4=%d, %d\n", t0, t0);
	#endif

}

//******************************************************************//
// Main Routine: To compute PVT Value from NavIC Data
//******************************************************************//
/*
This routine will find out the availability of the Navigation data required
to compute the PVT solutions

Input: Navigation Data Buffers
Output: No of Valid PVT Data Buffers and the corresponding channel or Satellite Number
		Numbers. The Valid Buffer Ids  will be saved in the int Nav_Valid_Buf_Id[ ];
		int Valid_NavICSat_Count
*/
// Note that this routine will be executed every time the PVT solution is tobe computed..
//******************************************************************//


int Verify_NavIC_PVT_Data(int PR_Num)
{

	//z: Stack Req. = 17*4 = 68bytes 

	int NavFlag,NoSat =0;
	int SatNoVal_1[NAVSATNO],SatNoVal_2[NAVSATNO];
	int i,j,k;
	//int RFlg[NAVSATNO];	//z_ajit

	//----- Step 1 :Initialize the data Structure  and the Navigation Flag to 0

	NavFlag=1;
	for (i=0; i< NAVSATNO ; i++)
		SatNoVal_1[i] = -1;


  	//----- Step 2: Check the First and second subframe data  Buffers

    	for (i=0; i< NAVSATNO; i++){
		NavFlag=1;  // Newly Added
		if (NavSubFrame1Data [i].af0 == -500.0) NavFlag=0;	// Clock bias
		if (NavSubFrame1Data [i].af1== -500.0) NavFlag=0;	// Clock drift
		if (NavSubFrame1Data [i].af2== -500.0) NavFlag=0;	// Clock drift rate
		if (NavSubFrame1Data [i].Toc== -500.0) NavFlag=0;	// Time of clock
		if (NavSubFrame1Data [i].Tgd== -500.0) NavFlag=0;	// Total group delay
		if (NavSubFrame1Data [i].MD== -500.0) NavFlag=0;	// Mean Motion Difference
		if (NavSubFrame1Data [i].IODEC== -500.0) NavFlag=0;	// Issue of Data Ephemeris & Clock
		if (NavSubFrame1Data [i].Cuc== -500.0) NavFlag=0;	// Cosine Harmonic Correction Term
		if (NavSubFrame1Data [i].Cus== -500.0) NavFlag=0;	// Sine Harmonic Correction Term
		if (NavSubFrame1Data [i].Cic== -500.0) NavFlag=0;	// Cosine Harmonic Correction Term
		if (NavSubFrame1Data [i].Cis== -500.0) NavFlag=0;	// Sine Harmonic Correction Term
		if (NavSubFrame1Data [i].Crc== -500.0) NavFlag=0;	// Cosine Harmonic Correction Term
		if (NavSubFrame1Data [i].Crs== -500.0) NavFlag=0;	// Sine Harmonic Correction Term
		if (NavSubFrame1Data [i].IDOT== -500.0) NavFlag=0;	// Rate of Inclination angle
		if (NavSubFrame1Data [i].Sflag== 1) NavFlag=0;		// status of the s signals
		if (NavSubFrame1Data [i].L5flag== 1) NavFlag=0;		// status of  L5  signals
		if (NavSubFrame1Data [i].URA== -500.0) NavFlag=0;	// user range accuracy
		if (NavSubFrame1Data [i].WN== -500.0) NavFlag=0;  	// Week Number
		if (NavSubFrame2Data [i].Mo== -500.0) NavFlag=0;   	// Mean Anomaly
		if (NavSubFrame2Data [i].Toe== -500.0) NavFlag=0;  	// Time of ephemeris
		if (NavSubFrame2Data [i].e== -500.0) NavFlag=0;    	// Eccentricity
		if (NavSubFrame2Data [i].A== -500.0) NavFlag=0;   	// Square root of Semi major axis
		if (NavSubFrame2Data [i].Omega== -500.0) NavFlag=0;   	// Long of Ascending Node
		if (NavSubFrame2Data [i].w == -500.0) NavFlag=0;   	// Argument of perigee
		if (NavSubFrame2Data [i].OmegaDot== -500.0) NavFlag=0;  // Rate of RAAN
		if (NavSubFrame2Data [i].Io== -500.0) NavFlag=0;    	// Inclination


		if (NavFlag == 1){
			SatNoVal_1[i] = i; //dbtfl Here it is assumed that 1st satellite data is saved in the 0th place;
			NoSat++;
			NavFlag=1;        // Initialize the Navigation Flag again to 0 //z: confirm ??
		} // if


	} // for Loop

        // step -3 To check whether the Pseudo range Values for the Corresponding satellites are available
        k=0;
        for (i=0; i< NoSat; i++){
		j = SatNoVal_1[i];
		if(j==-1)continue; // Newly Added
		NavObsDat.ObsPseudorange[j]=Raw_PR_Delay[PR_Num][j];	//sec(pseudorange time sec),sat_no
		if(NavObsDat.ObsPseudorange[j] != -500){ // Observed Pseudorange Values
			SatNoVal_2[k] = j; // Valid satellite numbers which have both Ephemeris and Pseudorange data
			k++;
        	}// if

        }//for
        NoSat = k;
        // Step -4 Copying the Valid satellite numbers for computation of PVT
        NavprocData.Valid_NavICSat_Count = k;
        for (i=0; i< NoSat; i++){
                NavprocData.Nav_Valid_Buf_Id[i] = SatNoVal_2[i];



		// step -5 To check whether the data required to Compute UTC is AVAILABLE
		NavFlag=0; 	// Init the Flag
		if(NavUTCCorr.A0utc == -500.0) NavFlag=1;
		if(NavUTCCorr.A1utc == -500.0) NavFlag=1;
		if(NavUTCCorr.A2utc == -500.0) NavFlag=1;
		if(NavUTCCorr.delTls == -500.0) NavFlag=1; 	// Current or past leap second count
		if(NavUTCCorr.Toutc == -500.0) NavFlag=1; 	// Time data reference time of week
		if(NavUTCCorr.WNoutc == -500.0) NavFlag=1;	// Time data reference week number
		if(NavUTCCorr.WNlsf == -500.0) NavFlag=1; 	// Leap second reference week number
		if(NavUTCCorr.DN == -500.0) NavFlag=1; 	    	// Leap second reference day number
		if(NavUTCCorr.delTlsf == -500.0) NavFlag=1; 	// Current or future leap second count

		// IRNSS time can be related to GPS using the IRNSS time offsets with respect to following GPS parameters

		if(NavUTCCorr.A0 == -500.0) NavFlag=1;
		if(NavUTCCorr.A1 == -500.0) NavFlag=1;
		if(NavUTCCorr.A2 == -500.0) NavFlag=1;
		if(NavUTCCorr.Tot == -500.0) NavFlag=1;		// Time data reference time of week
		if(NavUTCCorr.WNot == -500.0) NavFlag=1; 	// Time data reference week number

		if(NavFlag==1) NavprocData.UTCAbsFlg= 1;


        }

        return NoSat;
}// End of the Subroutine


//******************************************************************//
// Main Routine: To compute PVT Value from NavIC Data
//******************************************************************//

void ProcessNavIC_PVTData_Main(int PR_Num,int TOWC)
{
	//z: Stack Req. = 3*4 + 2*4 = 20bytes (including args. to be passed to function) 
	
	//z: Repetition of work, cant we reduce this function confirm ??
	
        int i,Sat_No;
	
	//z: temp
	int UP_Flg=0;

	//uint64_t t1;

	/*
	#ifdef AJIT
	t1 = __ajit_get_clock_time();
	PRINTF("pt0=%d, %d\n", t1, t1);
	#endif
	*/

        //----- Step 2 : To Verify the availability of the Navigational Data
        NavprocData.Valid_NavICSat_Count=Verify_NavIC_PVT_Data(PR_Num);

        //----- Step 1 : To copy Pseudorange values

	i=0;	//z: temp
	//PRINTF("Valid_NavICSat_count = %d\n",NavprocData.Valid_NavICSat_Count);
        for (i=0; i< NavprocData.Valid_NavICSat_Count; i++)	//z: for 6 satellites valid data is available
        {
		
        	NavObsDat.ObsPseudorange[i] = Raw_PR_Delay[PR_Num][i];	//z: time(sec), satellite_number

        			

        }

	/*
	#ifdef AJIT
	t1 = __ajit_get_clock_time();
	PRINTF("pt1=%d, %d\n", t1, t1);
	#endif
	*/

        //----- Step 3 : To compute the Corrected ToWC
	
	i=0;	//z: temp
        for (i=0; i< NavprocData.Valid_NavICSat_Count; i++)
        {
		// The Satellite Number is saved in the  Nav_Valid_Buf_Id[i] variable
		Sat_No = NavprocData.Nav_Valid_Buf_Id[i];
		NavIC_TOWC_Correction(Sat_No,TOWC,NavObsDat.ObsPseudorange[Sat_No]);

        } // end for

	/*
	#ifdef AJIT
	t1 = __ajit_get_clock_time();
	PRINTF("pt2=%d, %d\n", t1, t1);
	#endif
	*/

         //----- Step 4 : To Correct the Pseudorange

	i=0;	//z: temp
        for (i=0; i< NavprocData.Valid_NavICSat_Count; i++)
        {
		// The Satellite Number is saved in the  Nav_Valid_Buf_Id[i] variable
		 Sat_No = NavprocData.Nav_Valid_Buf_Id[i];
		 NavIC_Cor1_ObsPRange(Sat_No, TOWC, NavObsDat.ObsPseudorange[Sat_No]);
        } // end f

	/*
	#ifdef AJIT
	t1 = __ajit_get_clock_time();
	PRINTF("pt3=%d, %d\n", t1, t1);
	#endif
	*/

        //----- Step 5: Init PVT Result data

        // NavIC_Init_Processed_Data();


        //----- Step 6 : Compute UTC Time ( if the data is available)

        NavFindUTCTime(TOWC);

	/*
	#ifdef AJIT
	t1 = __ajit_get_clock_time();
	PRINTF("pt4=%d, %d\n", t1, t1);
	#endif
	*/

        //----- Step 7 : Check number of satellites Available Minimum 4 Satellites Required

        if (NavprocData.Valid_NavICSat_Count <=3)
        	//return-1; // No more processing	//orig
		return;		//z_gcc

        //----- Step 8 : Compute the Satellite Position
	i=0;	//z: temp
        for (i=0; i< NavprocData.Valid_NavICSat_Count; i++)
        {
		// The Satellite Number is saved in the  Nav_Valid_Buf_Id[i] variable
		Sat_No = NavprocData.Nav_Valid_Buf_Id[i];
		// Note that Raw_PR_Delay[Sat_No] I made one Dimenional array and added a count(i) .
		NavComputeSatPos(i,Sat_No, TOWC,NavObsDat.ObsPseudorange[Sat_No]);

        } // end for

	/*
	#ifdef AJIT
	t1 = __ajit_get_clock_time();
	PRINTF("pt5=%d, %d\n", t1, t1);
	#endif
	*/

        if ( UP_Flg ==1){ // First Time

		//----- Step 9 : Compute User Position

		if (NavprocData.Valid_NavICSat_Count >=6){
			NavComputeUserPosSixSat();

			/*
			#ifdef AJIT
			t1 = __ajit_get_clock_time();
			PRINTF("pt6=%d, %d\n", t1, t1);
			#endif
			*/
	
		}else if (NavprocData.Valid_NavICSat_Count >=4){
			NavComputeUserPosFourSat();

			/*
			#ifdef AJIT
			t1 = __ajit_get_clock_time();
			PRINTF("pt7=%d, %d\n", t1, t1);
			#endif
			*/
		}

		//----- Step 10 : Compute Satellite Position (Azimuth and Elevation)

		i=0;	//z: temp
		for ( i=0; i< NavprocData.Valid_NavICSat_Count;i++){
			Sat_No = NavprocData.Nav_Valid_Buf_Id[i];
			NavComputeSatAzEl(Sat_No);
		}

		/*
		#ifdef AJIT
		t1 = __ajit_get_clock_time();
		PRINTF("pt8=%d, %d\n", t1, t1);
		#endif
		*/

		//----- Step 11 : Compute Ionospheric Delays for all the Satellites

		i=0;	//z: temp
		for (i=0; i< NavprocData.Valid_NavICSat_Count;i++)
		{
			Sat_No = NavprocData.Nav_Valid_Buf_Id[i];
			NavComputeIonosphericDelay(Sat_No ,NavprocData.CorTOWC[Sat_No]); 	        // Corrected TOWC may be used here
		}

		/*
		#ifdef AJIT
		t1 = __ajit_get_clock_time();
		PRINTF("pt9=%d, %d\n", t1, t1);
		#endif
		*/

		//----- Step 12 : Compute Tropospheric  Delays for all the Satellites
		i=0;	//z: temp
		for (i=0; i< NavprocData.Valid_NavICSat_Count;i++)
		{
			Sat_No = NavprocData.Nav_Valid_Buf_Id[i];
			NavComputeTroposphericDelay(Sat_No);
		}

		/*
		#ifdef AJIT
		t1 = __ajit_get_clock_time();
		PRINTF("pt10=%d, %d\n", t1, t1);
		#endif
		*/

		 //----- Step 13 : Apply Tropospheric & Ionospheric Corrections to Psuedorange values
		
		i=0;	//z: temp
		for (i=0; i< NavprocData.Valid_NavICSat_Count;i++)
		{
			Sat_No = NavprocData.Nav_Valid_Buf_Id[i];
			NavIC_Cor_ObsPRange(Sat_No);
		}


		/*
		#ifdef AJIT
		t1 = __ajit_get_clock_time();
		PRINTF("pt11=%d, %d\n", t1, t1);
		#endif
		*/

		                        // Check the exact routine
        } // If UP_Flg ==1


        // If not for the First Time

        //----- Step 14 : Compute User Position for 6 or 4 Satellites + DOP for first time
	if (NavprocData.Valid_NavICSat_Count >=6){
		NavComputeUserPosSixSat();

		/*
		#ifdef AJIT
		t1 = __ajit_get_clock_time();
		PRINTF("pt12=%d, %d\n", t1, t1);
		#endif
		*/

	}else if (NavprocData.Valid_NavICSat_Count >=4){
		NavComputeUserPosFourSat();

		/*
		#ifdef AJIT
		t1 = __ajit_get_clock_time();
		PRINTF("pt13=%d, %d\n", t1, t1);
		#endif
		*/

	}

       //----- Step 15 : Compute Satellite Position (Azimuth and Elevation)
	i=0;	//z: temp
        for(i=0; i< NavprocData.Valid_NavICSat_Count;i++){
                Sat_No = NavprocData.Nav_Valid_Buf_Id[i];
                NavComputeSatAzEl(Sat_No);
        }

	/*
	#ifdef AJIT
	t1 = __ajit_get_clock_time();
	PRINTF("pt14=%d, %d\n", t1, t1);
	#endif
	*/

        //----- Step 16 : Compute Ionospheric Delays for all the Satellites
	i=0;	//z: temp
        for(i=0; i< NavprocData.Valid_NavICSat_Count;i++)
        {
		Sat_No = NavprocData.Nav_Valid_Buf_Id[i];
		NavComputeIonosphericDelay(Sat_No,NavprocData.CorTOWC[i]); 	  // Corrected TOWC may be used here
        }
	
	/*
	#ifdef AJIT
	t1 = __ajit_get_clock_time();
	PRINTF("pt15=%d, %d\n", t1, t1);
	#endif
	*/

        //----- Step 17 : Compute Tropospheric  Delays for all the Satellites
	i=0;	//z: temp
        for(i=0; i< NavprocData.Valid_NavICSat_Count;i++)
        {
		Sat_No = NavprocData.Nav_Valid_Buf_Id[i];
		NavComputeTroposphericDelay(Sat_No); 	                             // Check the exact routine
        }
	
	/*
	#ifdef AJIT
	t1 = __ajit_get_clock_time();
	PRINTF("pt16=%d, %d\n", t1, t1);
	#endif
	*/

	i=0;	//z: temp
      	for (i=0; i< NavprocData.Valid_NavICSat_Count;i++)
        {
               Sat_No = NavprocData.Nav_Valid_Buf_Id[i];
               NavIC_Cor_ObsPRange(Sat_No);
        }

	/*
	#ifdef AJIT
	t1 = __ajit_get_clock_time();
	PRINTF("pt17=%d, %d\n", t1, t1);
	#endif
	*/


        //----- Step 18 : Compute the Satellite Velocity
	i=0;	//z: temp
        for(i=0; i< NavprocData.Valid_NavICSat_Count;i++)
        {
		Sat_No = NavprocData.Nav_Valid_Buf_Id[i];
		NavComputeSatVelocity(TOWC ,Sat_No);
        }

	/*
	#ifdef AJIT
	t1 = __ajit_get_clock_time();
	PRINTF("pt18=%d, %d\n", t1, t1);
	#endif
	*/

        //----- Step 19 : Compute the User Velocity

         if (NavprocData.Valid_NavICSat_Count >=6){ 
		NavComputeUserVelocitySixSat();
		/*
		#ifdef AJIT
		t1 = __ajit_get_clock_time();
		PRINTF("pt19=%d, %d\n", t1, t1);
		#endif
		*/

	}else if (NavprocData.Valid_NavICSat_Count >=4){
		NavComputeUserVelocityFourSat();
		/*
		#ifdef AJIT
		t1 = __ajit_get_clock_time();
		PRINTF("pt20=%d, %d\n", t1, t1);
		#endif
		*/
	}
        //----- Step 20 : Compute Geometric and Pseudorange of each satellite
	i=0;	//z: temp
        for(i=0; i< NavprocData.Valid_NavICSat_Count;i++)
                NavIC_Compute_Sat_Rx_Range(i);

	/*
	#ifdef AJIT
	t1 = __ajit_get_clock_time();
	PRINTF("pt21=%d, %d\n", t1, t1);
	#endif
	*/
	
	//z:temp

	//----- Step 21 : NMEA Data formulation
	//NavGIGGAMesage();
	//NavGIGSAMesage();
	//NavGIGLLMessage();
	//NavGIGSVMesage();
	//NavGIRMCMessage();


        return ;

} // End of the Subroutine



void NavIC_Init_Processed_Data( )
{
        int i;

	//z: NavprocData : datastructure defined in processorbuffer.h	

        for (i=0; i< NAVSATNO; i++){

		NavprocData.CorTOWC[i] =-500.0;           // TOWC
		NavObsDat.ObsPseudorange[i] = -500.0;	  // Observed Pseudorange Values
		NavprocData.CorrPseudorange[i]=-500.0;    // Corrected Observed Pseudorange Values used in computation of User Position

        }// for

        // UTC Time
        NavprocData.UTCAbsFlg =0;
        NavprocData.UTC_Day= -500.0;
        NavprocData.UTC_DayofYr= -500.0;
        NavprocData.UTC_Mon= -500.0;
        NavprocData.UTC_Yr = -500.0;
        NavprocData.UTC_Hrs= -500.0;
        NavprocData.UTC_Mins= -500.0;
        NavprocData.UTC_Sec= -500.0;

        // Indian Standard Time
        NavprocData.IST_Day= -500.0;
        NavprocData.IST_DayofYr= -500.0;
        NavprocData.IST_Mon= -500.0;
        NavprocData.IST_Yr= -500.0;
        NavprocData.IST_Hrs= -500.0;
        NavprocData.IST_Mins= -500.0;
        NavprocData.IST_Sec= -500.0;


        // Valid Nav Data Availability
         NavprocData.Valid_NavICSat_Count=-500;

        for (i=0; i< NAVSATNO; i++)
		NavprocData.Nav_Valid_Buf_Id[i] =-50;

        // Init Satellite Coordinates Data
        for (i=0; i< NAVSATNO; i++){
                NavprocData.SatPositionECEF[i][0] = -500.0;
                NavprocData.SatPositionECEF[i][1] = -500.0;
                NavprocData.SatPositionECEF[i][2] = -500.0;
        }

        for (i=0; i< NAVSATNO; i++){
                NavprocData.SatPosAzEl_Deg[i][0] = -500.0;
                NavprocData.SatPosAzEl_Deg[i][1] = -500.0;
        }

        for (i=0; i< NAVSATNO; i++){
                NavprocData.SatVelocity[i][0] = -500.0;
                NavprocData.SatVelocity[i][1] = -500.0;
                NavprocData.SatVelocity[i][2] = -500.0;
        }

        for (i=0; i< NAVSATNO; i++){
                NavprocData.SatIonosphericCorr[i] = -500.0;
                NavprocData.SatTroposphericCorr[i] = -500.0;
        }

        // User Position related Data Make Correction here
        NavprocData.UserPos_XYZ[0] = -500.0;
        NavprocData.UserPos_XYZ[1] = -500.0;
        NavprocData.UserPos_XYZ[2] = -500.0;

        for (i=0; i< NAVSATNO; i++)
        	NavprocData.UserSatRange[i] = -500.0;

        NavprocData.UserPosition_Long= -500.0;
        NavprocData.UserPosition_Lat= -500.0;
        NavprocData.UserPosition_Ht= -500.0;


        NavprocData.RX_Lat_Dir = 'N';
        NavprocData.Rx_Lon_Dir = 'E';

        NavprocData.UserVelocity[0] = -500.0;
        NavprocData.UserVelocity[1] = -500.0;
        NavprocData.UserVelocity[2] = -500.0;


        NavprocData.GDOP = -500.0;
        NavprocData.PDOP = -500.0;
        NavprocData.HDOP = -500.0;
        NavprocData.VDOP = -500.0;
        NavprocData.TDOP = -500.0;

        // User - Satellite Geometric Distance
        for (i=0; i< NAVSATNO; i++){
		NavprocData.Geo_UserSat_Range[i] = -500.0;
		NavprocData.UserSatPseudoRange[i]= -500.0;
        }

        // User Velocity
        NavprocData.UserVelocity[0] = -500.0;
        NavprocData.UserVelocity[1] = -500.0;
        NavprocData.UserVelocity[2] = -500.0;

        return;

} // End of the Subroutine


//******************************************************************//

// This routine computes the range between Satellite and the  Receiver
// This value is corrected with Ionospheric and Tropospheric Correction

//******************************************************************//


void NavIC_Compute_Sat_Rx_Range(int SatNo) // I/P Values Checked..
{
	//z: Stack Req. = 8*4 = 32bytes

	double	satX,satY,satZ,userX,userY,userZ, r;
	int	DatErFlg=0;
	// Check the Correctness of the Values before copying…
	// Satellite Position in ECEF Coordinate System

   	double val,ans;			//z_ajit
   	int addr_val, addr_ans;		//z_ajit

	if(NavprocData.SatPositionECEF[SatNo][0] == -500.0) DatErFlg= 1;
	if(NavprocData.SatPositionECEF[SatNo][1] == -500.0) DatErFlg= 1;
	if(NavprocData.SatPositionECEF[SatNo][2] == -500.0) DatErFlg= 1;

	// Receiver Position in ECEF Format
	if(NavprocData.UserPos_XYZ [0] == -500.0) DatErFlg= 1;
	if(NavprocData.UserPos_XYZ [1] == -500.0) DatErFlg= 1;
	if(NavprocData.UserPos_XYZ [2] == -500.0) DatErFlg= 1;

	if (DatErFlg== 1){
		NavprocData.UserSatPseudoRange[SatNo] = -500.0;
		NavprocData.Geo_UserSat_Range[SatNo] = -500.0;
		return;
	}//  if

        // Copying the Satellite & Rx  Position values in the Local Variables
        // Satellite Position in ECEF Coordinate System
        satX= NavprocData.SatPositionECEF[SatNo][0];
        satY= NavprocData.SatPositionECEF[SatNo][1];
        satZ= NavprocData.SatPositionECEF[SatNo][2];

        // Receiver  Position in  ECEF Format
        userX=NavprocData.UserPos_XYZ[0];
        userY=NavprocData.UserPos_XYZ[1];
        userZ=NavprocData.UserPos_XYZ[2];

        // Step -1 Compute the Geometrical Distance between Receiver and satellite Position
        //r=pow((pow(satX-userX,2),pow(satY-userY,2),pow(satZ-userZ,2)),0.5);

	#ifdef AJIT
	val = (pow(satX-userX,2) + pow(satY-userY,2) + pow(satZ-userZ,2));
	addr_val = (uint32_t) &val;	//memory address location 
	addr_ans = (uint32_t) &ans;
	sqrt_ajit_asm_double(addr_val, addr_ans);
	r = ans;
	#else
	r=sqrt(pow(satX-userX,2) + pow(satY-userY,2) + pow(satZ-userZ,2) );
	#endif


        NavprocData.Geo_UserSat_Range[SatNo] = r;

        // Step 2: Tropospheric and Ionospheric Correction
        if (NavprocData.SatIonosphericCorr[SatNo] != -500.0)
        	r = r + NavprocData.SatIonosphericCorr[SatNo];

        if(NavprocData.SatTroposphericCorr[SatNo] != -500.0)
        	r = r + NavprocData.SatTroposphericCorr[SatNo];

        //  if the Correction values are not available then Geometric distance  is saved
        NavprocData.UserSatPseudoRange[SatNo] =r;
        return;
}// End of the subroutine


//****************************************************************************//
// This routine corrects the TOWC value used in the computation of PVT
//****************************************************************************//


void NavIC_TOWC_Correction(int NavSatNo,int TOW,double Raw_PR_Delay)
{

	//z: Stack Req. =  17*4 bytes = 68bytes

	double	mu=3.986005*pow(10,14);
	//double	OmegaEDot= 7.2921151467*pow(10,-5);		//z_ajit
	double	F=-4.442807633*pow(10,-10);
	double	tk,tc,deltr,delt;
	double 	a,no,n,Mk,Ek;
	//double   t;	//z_ajit
	//double   Vk,sinVk,cosVk,Phik,duk,drk,dik,uk,rk,ik;	//z_ajit
	//double	Xko,Yko,Omegak,Xk,Yk,Zk;	//z_ajit
	double   Ekold,diff;

   	double val,ans;			//z_ajit
   	int addr_val, addr_ans;		//z_ajit

	Raw_PR_Delay=(Raw_PR_Delay)*pow(10,-9);

        //Step 1 tc = NavIC System Time (Seconds) @ Time of Message Transmission
        //Comment: Not sure why the Time delay corresponding to Pseudo Range is subtracted from the TOWC.
        //The reason could be that the CurrentTOWC value represents the Receive Time and to convert it to Satellite
        // Emission Timethe Pseudo Range Time Delay is subtracted from the   TOWC value
        ///
        tc=TOW-Raw_PR_Delay;



	//Step 2 Compute Delta Time (Tk) from Ephemeris Reference Epoch	[ Toe = Time of ephemeris (seconds)]
	tk=tc-NavSubFrame2Data[NavSatNo].Toe;
	if(tk>=302400)		tk=tk-604800;
	else if(tk<=-302400)	tk=tk+604800;

	//Step 3 Compute Semi -major Axis  of the Satellite Orbit
	a=pow(NavSubFrame2Data[NavSatNo].A,2);

	//Step 4  Computed mean motion (rad/sec)
	//no=pow(mu/a,0.5)/a;
	#ifdef AJIT
	val = mu/a;
	addr_val = (uint32_t) &val;	//memory address location 
	addr_ans = (uint32_t) &ans;
	sqrt_ajit_asm_double(addr_val, addr_ans);
	no = ans/a;
	#else
	no = sqrt(mu/a)/a;
	#endif

	//Step 6 Compute Corrected Mean Motion
	n= no+NavSubFrame1Data[NavSatNo].MD;

	//Step 7 Compute Mean Anomaly
	Mk=NavSubFrame2Data[NavSatNo].Mo+ (n*tk);

	//Step 8 Compute Eccentric anomaly (Ek) by iteration from following Kepler’s equation
	Ek=Mk;
	do
	{
		Ekold=Ek;
		Ek=Mk+NavSubFrame2Data[NavSatNo].e*sin(Ek);
		diff=Ek-Ekold;
	}
	while(fabs(diff)>0.00000001);
	deltr=F*NavSubFrame2Data[NavSatNo].e*a*sin(Ek);

	//Step 8 Applying Correction to TOWC  using  the Clock Coefficients transmitted as part of Subframe 1
	delt=NavSubFrame1Data[NavSatNo].af0+NavSubFrame1Data[NavSatNo].af1*(tc-NavSubFrame1Data[NavSatNo].Toc)+NavSubFrame1Data[NavSatNo].af2*pow((tc-NavSubFrame1Data[NavSatNo].Toc),2)+deltr-(NavSubFrame1Data[NavSatNo].Tgd );
	NavprocData.CorTOWC[NavSatNo] =tc-delt;


	//   Applying these Correction to  Pseudo Range Delays...
	//   Comment :  The Step 8 : This step can be  executed outside this routine for simplicity &
	//   Better understanding. of the PVT Steps. Applying the Clock Correction to Pseudo range
	//   Delay needs justification.


	return ;
} // End of the subroutine


//****************************************************************************//
// This routine corrects the Observed Pseudo-range values used in the computation
// of PVT
//****************************************************************************//
void NavIC_Cor1_ObsPRange(int NavSatNo,int TOW,double Raw_PR_Delay)
{

	//z: Stack Req. = 17*4 = 68bytes 

        double	mu=3.986005*pow(10,14);
        //double	OmegaEDot= 7.2921151467*pow(10,-5);	//z_ajit
        double	F=-4.442807633*pow(10,-10);
        double	tk,tc,deltr,delt;
        double 	a,no,n,Mk,Ek;
	//double   Vk,sinVk,cosVk,Phik,duk,drk,dik,uk,rk,ik,Xko;	//z_ajit
        //double	Xko,Yko,Omegak,Xk,Yk,Zk;	//z_ajit
	double   Ekold,diff;

   	double val,ans;			//z_ajit
   	int addr_val, addr_ans;		//z_ajit

        Raw_PR_Delay=(Raw_PR_Delay)*pow(10,-9);
        /*
        //Step 1 tc = NavIC System Time (Seconds) @ Time of Message Transmission
        //Comment: Not sure why the Time delay corresponding to Pseudo Range is subtracted from the TOWC.
        //The reason could be that the CurrentTOWC value represents the Receive Time and to convert it to Satellite
        // Emission Time the Pseudo Range Time Delay is subtracted from the   TOWC value
        ///
        */
        tc=TOW-Raw_PR_Delay;

	//Step 2 Compute Delta Time (Tk) from Ephemeris Reference Epoch	[ Toe = Time of ephemeris (seconds)]
	tk=tc-NavSubFrame2Data[NavSatNo].Toe;
	if(tk>=302400)		tk=tk-604800;
	else if(tk<=-302400)	tk=tk+604800;

	//Step 3 Compute Semi -major Axis  of the Satellite Orbit
	a=pow(NavSubFrame2Data[NavSatNo].A,2);

	//Step 4  Computed mean motion (rad/sec)
	//no=pow(mu/a,0.5)/a;
	#ifdef AJIT
	val = mu/a;
	addr_val = (uint32_t) &val;	//memory address location 
	addr_ans = (uint32_t) &ans;
	sqrt_ajit_asm_double(addr_val, addr_ans);
	no = ans/a;
	#else
	no = sqrt(mu/a)/a;
	#endif

	//Step 6 Compute Corrected Mean Motion
	n= no+NavSubFrame1Data[NavSatNo].MD;

	//Step 7 Compute Mean Anomaly
	Mk=NavSubFrame2Data[NavSatNo].Mo + (n*tk);

	//Step 8 Compute Eccentric anomaly (Ek) by iteration from following Kepler’s equation
	Ek=Mk;
	do
	{
		Ekold=Ek;
		Ek=Mk+NavSubFrame2Data[NavSatNo].e*sin(Ek);
		diff=Ek-Ekold;
	}
	while(fabs(diff)>0.00000001);

        deltr=F*NavSubFrame2Data[NavSatNo].e*a*sin(Ek);

        //Step 8 Applying Correction to TOWC  using  the Clock Coefficients transmitted as part of Subframe 1
        delt=NavSubFrame1Data[NavSatNo].af0+NavSubFrame1Data[NavSatNo].af1*(tc-NavSubFrame1Data[NavSatNo].Toc)+NavSubFrame1Data[NavSatNo].af2*pow((tc-NavSubFrame1Data[NavSatNo].Toc),2)+deltr-(NavSubFrame1Data[NavSatNo].Tgd );
        //t=tc-delt;

        //  Applying these Correction to  Pseudo Range Delays...
        //  Comment :  The Step 8 : This step can be  executed outside this routine for simplicity &
        //  Better understanding. of the PVT Steps. Applying the Clock Correction to Pseudo range
        //  Delay needs justification.

        Raw_PR_Delay=Raw_PR_Delay+delt;
        NavprocData.Corr1Pseudorange[NavSatNo]=Raw_PR_Delay;

        //Step 9  Computation of  Eccentricity

}

void NavIC_Cor_ObsPRange(int NavSatNo)
{

	double r;

	// for (i=0; i<= NavprocData.Valid_NavICSat_Count;i++){
	r =NavprocData.Corr1Pseudorange[NavSatNo];

	// Step 1: Tropospheric and Ionospheric Correction

	if(NavprocData.SatIonosphericCorr[NavSatNo] != -500.0)
		r = r + NavprocData.SatIonosphericCorr[NavSatNo];
	if(NavprocData.SatTroposphericCorr[NavSatNo] != -500.0)
		r = r + NavprocData.SatTroposphericCorr[NavSatNo];
    	NavprocData.CorrPseudorange[NavSatNo] = r;

    //} // for Loop
    	return ;
} // End of the subroutine




//******************************************************************//
// To compute NavIC Satellite Position at given ToWC
// Input Parameter :
// (1) TOWC : Corrected for the Satellite Parameters
// (2)  Channel No Containing the valid Navigation Data
// Output Parameter
// Satellite Position ( X, Y, Z) in ECEF  Coordinates System
//******************************************************************//

/* Note : There is no need to pass the  Pseudo Range Delay & TOWC value to
this routine However, it will deleted in the next revision
*/
void NavComputeSatPos(int Count,int NavSatNo,int TOW,double Raw_PR_Delay) //OK
{
	//z: Stack Req. = 31*4 = 124bytes + (32bytes++ for atan2)

        double	mu=3.986005*pow(10,14);
        double	OmegaEDot= 7.2921151467*pow(10,-5);
        //double	F=-4.442807633*pow(10,-10);		//z_ajit
        double	tk,tc;
	//double   deltr,delt;		//z_ajit
        double	a,no,n,Mk,Ek,Vk,sinVk,cosVk,Phik,duk,drk,dik,uk,rk,ik,Xko;
        double	Yko,Omegak,Xk,Yk,Zk,Ekold,diff;

   	double val,ans;			//z_ajit
   	int addr_val, addr_ans;		//z_ajit

	//z: temp
	//PRINTF("Raw_PR_Delay=%f, TOWC=%d\n", Raw_PR_Delay, TOW);
	//PRINTF("NavSubFrame2Data[NavSatNo].Toe=%f\n", NavSubFrame2Data[NavSatNo].Toe);
	//PRINTF("NavSubFrame2Data[NavSatNo].A=%f\n", NavSubFrame2Data[NavSatNo].A);


        Raw_PR_Delay=(Raw_PR_Delay)*pow(10,-9);


        /*
        //Step 1 tc = NavIC System Time (Seconds) @ Time of Message Transmission
        //Comment: Not sure why the Time delay corresponding to Pseudo Range is subtracted from the TOWC.
        //The reason could be that the CurrentTOWC value represents the Receive Time and to convert it to Satellite
        // Emission Time the Pseudo Range Time Delay is subtracted from the   TOWC value
        ///
        */
        tc=TOW-Raw_PR_Delay;

	//Step 2 Compute Delta Time (Tk) from Ephemeris Reference Epoch	[ Toe = Time of ephemeris (seconds)]
	tk=tc-NavSubFrame2Data[NavSatNo].Toe;
	if(tk>=302400)		tk=tk-604800;
	else if(tk<=-302400)	tk=tk+604800;

	//Step 3 Compute Semi -major Axis  of the Satellite Orbit
	a=pow(NavSubFrame2Data[NavSatNo].A,2);

	//Step 4  Computed mean motion (rad/sec)
	//no=pow(mu/a,0.5)/a;
	#ifdef AJIT
	val = mu/a;
	addr_val = (uint32_t) &val;	//memory address location 
	addr_ans = (uint32_t) &ans;
	sqrt_ajit_asm_double(addr_val, addr_ans);
	no = ans/a;
	#else
	no = sqrt(mu/a)/a;
	#endif

	//Step 6 Compute Corrected Mean Motion
	n= no+NavSubFrame1Data[NavSatNo].MD;

	//Step 7 Compute Mean Anomaly
	Mk=NavSubFrame2Data[NavSatNo].Mo + (n*tk);

	//Step 8 Compute Eccentric anomaly (Ek) by iteration from following Kepler’s equation
	Ek=Mk;
	do
	{
		Ekold=Ek;
		Ek=Mk+NavSubFrame2Data[NavSatNo].e*sin(Ek);
		diff=Ek-Ekold;
	}while(fabs(diff)>0.00000001);


	//deltr=F*NavSubFrame2Data[NavSatNo].e*a*sin(Ek);

	//Step 8 Applying Correction to TOWC  using  the Clock Coefficients transmitted as part of Subframe 1
	//delt=NavSubFrame1Data[NavSatNo].af0+NavSubFrame1Data[NavSatNo].af1*(tc-NavSubFrame1Data[NavSatNo].Toc)+NavSubFrame1Data[NavSatNo].af2*pow((tc-NavSubFrame1Data[NavSatNo].Toc),2)+deltr-(NavSubFrame1Data[NavSatNo].Tgd );
	//t=tc-delt;

	//  Applying these Correction to  Pseudo Range Delays...
	//  Comment :  The Step 8 : This step can be  executed outside this routine for simplicity &
	//  Better understanding. of the PVT Steps. Applying the Clock Correction to Pseudo range
	//  Delay needs justification.

	//  Raw_PR_Delay=Raw_PR_Delay+delt;

        //Step 9  Computation of  Eccentricity
        //sinVk= ((pow(1-pow(NavSubFrame2Data[NavSatNo].e,2),0.5))* sin(Ek))/(1-NavSubFrame2Data[NavSatNo].e*cos(Ek));
	#ifdef AJIT
	val = (1-pow(NavSubFrame2Data[NavSatNo].e,2));
 	addr_val = (uint32_t) &val;	//memory address location 
  	addr_ans = (uint32_t) &ans;
  	sqrt_ajit_asm_double(addr_val, addr_ans);
	sinVk= ((ans)* sin(Ek))/(1-NavSubFrame2Data[NavSatNo].e*cos(Ek));
	#else
	sinVk= ((sqrt(1-pow(NavSubFrame2Data[NavSatNo].e,2)))* sin(Ek))/(1-NavSubFrame2Data[NavSatNo].e*cos(Ek));
	#endif

        cosVk=(cos(Ek)-NavSubFrame2Data[NavSatNo].e)/(1-NavSubFrame2Data[NavSatNo].e*cos(Ek));

        //Step 10 Compute True Anomaly
	//z: SR : 32bytes++ (Stack Req.)
        Vk=atan2(sinVk,cosVk);

        //Step 11 Compute Argument Of Latitude
        Phik= Vk+NavSubFrame2Data[NavSatNo].w;

        //Step 12 Compute Second Harmonic Perturbations (δUk, δRk&δIk)
        duk= NavSubFrame1Data[NavSatNo].Cus* sin(2*Phik) + NavSubFrame1Data[NavSatNo].Cuc* cos(2*Phik);
        drk= NavSubFrame1Data[NavSatNo].Crs* sin(2*Phik) + NavSubFrame1Data[NavSatNo].Crc* cos(2*Phik);
        dik= NavSubFrame1Data[NavSatNo].Cis* sin(2*Phik) + NavSubFrame1Data[NavSatNo].Cic* cos(2*Phik);

        //Step 13 Calculate Corrected Argument Of Latitude (uk)
        uk=Phik+duk;

        //Step 14 Compute Corrected Radius (rk)
        rk=a*(1-NavSubFrame2Data[NavSatNo].e*cos(Ek))+drk;

        //Step 15 Corrected Inclination (ik)
        ik=NavSubFrame2Data[NavSatNo].Io+dik+NavSubFrame1Data[NavSatNo].IDOT*(NavprocData.CorTOWC[NavSatNo]-NavSubFrame2Data[NavSatNo].Toe);

        //Step 16  ComputePosition in orbital plane
        Xko= rk* cos(uk);
        Yko= rk* sin(uk);

        //Step 17 (Ωk) Corrected Longitude of Ascending Node(Ω) Rate of RAAN (radian/sec)
        Omegak=NavSubFrame2Data[NavSatNo].Omega+NavSubFrame2Data[NavSatNo].OmegaDot*(NavprocData.CorTOWC[NavSatNo]-NavSubFrame2Data[NavSatNo].Toe)- OmegaEDot*NavprocData.CorTOWC[NavSatNo];

        //Step 18 Compute Final Earth-Fixed Coordinates (ECEF) Of Satellite
        Xk= Xko*cos(Omegak)- Yko* cos(ik)*sin(Omegak);
        Yk= Xko*sin(Omegak)+ Yko* cos(ik)*cos(Omegak);
        Zk= Yko*sin(ik);

        // Note that this is OK for Valid satellite Number
        NavprocData.SatPositionECEF[NavSatNo][0] = Xk;
        NavprocData.SatPositionECEF[NavSatNo][1] = Yk;
        NavprocData.SatPositionECEF[NavSatNo][2] = Zk;
	// NavprocData.SatPositionECEF[Count][3]= NavprocData.Corr1Pseudorange[NavSatNo];//Raw_PR_Delay;

	//z: temp
	//NavprocData.SatPositionECEF[NavSatNo][3]= 87.7;

	//z: temp
	//PRINTF("SatPos[i][0] : %f,SatPos[i][1] : %f,SatPos[i][2] : %f\n",Xk,Yk,Zk);

}// End of the Subroutine


void NavComputeUserPosFourSat()
{

	//z : Stack Req. = 148*4 = 592bytes

        int	j,Sat_No;
        double	PRn[6];
        double	xn=0,yn=0,zn=0,Tbn=0;
        double gu[3],delPR[6][1],alpha[6][4],alphaT[4][6],alphasq[4][4],alphasqinv[4][4],alphamat[4][6]; 	//z_debug
	double dl[4][1] = {{0},{0},{0},{0}};	//z_debug -o 3
        double	erro;
        double	xuser,yuser,zuser,rsp,Lc,Lsp,Ltemp,L,erro1,Lflp,alt;
        double	Lcden;
        uint8_t	k1,loop;
	double bias;

   	double val,ans;		//z_ajit
   	int addr_val, addr_ans;	//z_ajit
	
	//z_debug : Array initialization

	/*
	double gu[3] = {0,0,0};
	double dl[4][1] = {{0},{0},{0},{0}};	//z_debug -o 3
	double delPR[6][1] = {{0},{0},{0},{0},{0},{0}};
	double alpha[6][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
	double alphaT[4][6] = {{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0}};
	double alphasq[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
	double alphasqinv[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
	double alphamat[4][6] = {{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0}};
	*/
	loop=0;
	do
	{

		//  Step 1 Initializing the User Coordinates
		gu[0]=xn;
		gu[1]=yn;
		gu[2]=zn;

		//   Step 2 Computing the Geometric Distance between Satellite  and Receiver Position
		//   SQRT[( Xj - Xo)2 + (Yj - Yo)2 + (Zj- Zo)2 ]+ TBN * C [ TBN : Clock Bias Term]
		//for(j=0;j<6;j++)
		//  for(j=0; j< NavprocData.Valid_NavICSat_Count;j++)
		//  {
		//   Sat_No = NavprocData.Nav_Valid_Buf_Id[i];
		//  PRn[j]=(pow(gu[0]-NavprocData.SatPositionECEF[j][0],2))+(pow(gu[1]-NavprocData.SatPositionECEF[j][1],2))+(pow(gu[2]-NavprocData.SatPositionECEF[j][2],2));
		//   PRn[j]=pow(PRn[j],0.5)+Tbn*C;

		//   } // For Loop
		//

		 //for(j=0;j<6;j++)
		for(j=0; j< 4;j++)
		{

			Sat_No = NavprocData.Nav_Valid_Buf_Id[j];

			PRn[j]=(pow(gu[0]-NavprocData.SatPositionECEF[Sat_No][0],2))+(pow(gu[1]-NavprocData.SatPositionECEF[Sat_No][1],2))+(pow(gu[2]-NavprocData.SatPositionECEF[Sat_No][2],2));
			//PRn[j]=pow(PRn[j],0.5)+Tbn*C;
	 		#ifdef AJIT
			val = PRn[j];
	 		addr_val = (uint32_t) &val;	//memory address location 
	  		addr_ans = (uint32_t) &ans;
	  		sqrt_ajit_asm_double(addr_val, addr_ans);
			PRn[j]=ans+Tbn*C;
			#else
		   	PRn[j]=sqrt(PRn[j])+Tbn*C;
			#endif

		}

		// Step 3 :  Formulation of the Matrix [6][4] to Compute the User Position
		//	[Matrix[j] [0]  = (Xo -Xj) /( PRn[j] -TBN * C);
		//	[Matrix[j] [1]  = (Yo- Yj) /( PRn[j] --TBN * C)
		//	[Matrix[j] [2]  = ( Zo - Zj) /( PRn[j] -TBN * C)
		//	[Matrix[j] [3]  =  C
		for(j=0; j< 4;j++)
		{
			Sat_No = NavprocData.Nav_Valid_Buf_Id[j];
			for(k1=0;k1<3;k1++)
			{
				alpha[j][k1]=(gu[k1]-NavprocData.SatPositionECEF[Sat_No][k1])/(PRn[j]-Tbn*C);
			}
		} // For Loop
		for(j=0;j<4;j++)
			alpha[j][3]=C;

		//  Step 4  Defining [Matrix [6]  = PsudoRange[j] = ( Zo - Zj) /( PRn[j] -TBN * C)
		for(j=0; j< 4;j++)
		{
			Sat_No = NavprocData.Nav_Valid_Buf_Id[j];
			delPR[j][0]=(NavprocData.Corr1Pseudorange[Sat_No]*C)-PRn[j];
		}

		// Step 5 Solving the Matrix to estimate  Receiver Position
		// Matrix Transpose
		//CompTranspose(4,4,alpha, alphaT);			//z_debug
		CompTranspose(6,4,alpha, alphaT);

		// Matrix Multiplication
		//MatMultiplication(4,4,4,4,alphaT,alpha,alphasq);	//z_debug
		MatMultiplication(4,6,4,4,alphaT,alpha,alphasq);	

		// Matrix Inverse
		FindMatrixInverse(4,alphasq,alphasqinv);

		// Matrix Multiplication
		//MatMultiplication(4,4,4,4,alphasqinv,alphaT,alphamat);	//z_dldebug
		MatMultiplication(4,4,4,6,alphasqinv,alphaT,alphamat);	

		//MatMultiplication(4,4,4,1,alphamat,delPR,dl);		//z_debug
		MatMultiplication(4,6,4,1,alphamat,delPR,dl);		

		// Step 6 Computing the error
		erro=(pow(dl[0][0],2)) +( pow(dl[1][0],2) )+( pow(dl[2][0],2));
		//erro=pow(erro,0.5);
 		#ifdef AJIT
		val = erro;
 		addr_val = (uint32_t) &val;	//memory address location 
  		addr_ans = (uint32_t) &ans;
  		sqrt_ajit_asm_double(addr_val, addr_ans);
		erro = ans;
		#else
		erro=sqrt(erro);
		#endif

		if(erro>20){
			xn=xn+dl[0][0];
			yn=yn+dl[1][0];
			zn=zn+dl[2][0];
			Tbn=Tbn+dl[3][0];
			loop++;
		}
		else
			break;
      
	} while(loop<10);

        //Step 7  Satellite Position in ECEF Cartesian Coordinates System
        xuser= xn;
        yuser=yn;
        zuser=zn;
        bias=Tbn;
	zftemp = bias;	//z_ajit	

        // Step 8 Converting the Satellite Coordinates in ECEF to Spherical Coordinate System
        // 8.1 Computation of the distance from the centre of the earth to the Receiver Position
        rsp=(pow(xuser,2)) +( pow(yuser,2) )+( pow(zuser,2));
        //rsp=pow(rsp,0.5);
	#ifdef AJIT
	val = rsp;
	addr_val = (uint32_t) &val;	//memory address location 
	addr_ans = (uint32_t) &ans;
	sqrt_ajit_asm_double(addr_val, addr_ans);
	rsp = ans;
	#else
	rsp=sqrt(rsp);
	#endif

        // Step 8.2 Computation of Geocentric Latitude..[Lc].
        Lcden=(pow(xuser,2)) +( pow(yuser,2) );
        //Lcden=pow(Lcden,0.5);
	#ifdef AJIT
	val = Lcden;
	addr_val = (uint32_t) &val;	//memory address location 
	addr_ans = (uint32_t) &ans;
	sqrt_ajit_asm_double(addr_val, addr_ans);
	Lcden = ans;
	#else
	Lcden=sqrt(Lcden);
	#endif

        // Lc=  TAN INERVESE ( (Zuser / SQRT (X2user + Y2user)))
        Lc= atan2(zuser,Lcden);

	//Step8.3 Computation of  Geodetic  Longitude[L
	Lsp=atan2(yuser,xuser)*180/pi;

	// Step 8.4 Computation of Geodetic Latitude by Iterative Process...[Lflp]
	Ltemp=Lc;
	erro1=1;
	while(erro1>0.000001)
	{
		L= Lc+ ee*sin(2*Ltemp);
		erro1=fabs(Ltemp-L);
		Ltemp=L;
	}
	Lflp=L*(180/pi);

        // Step 8.5 Computation of Altitude of the Receiver using the corrected Earth radius value

        alt = rsp - re *(1-ee*pow(sin(L),2));

        // Saving User Position in Cartesian Coordinate  System
        NavprocData.UserPos_XYZ[0]=xuser;
        NavprocData.UserPos_XYZ[1]=yuser;
        NavprocData.UserPos_XYZ[2]=zuser;

        // Saving User Position in Spherical Coordinate System
        NavprocData.UserPosition_Long =Lsp;
        NavprocData.UserPosition_Lat =Lflp;
        NavprocData.UserPosition_Ht= alt;
        NavComputeDOP(4,alphasqinv);
}//*End of Subroutine*

void NavComputeUserPosSixSat()
{
	//z: Stack Req. = 148*4 =  592bytes

        int	j,Sat_No;
        double	PRn[6];
        double	xn=0,yn=0,zn=0,Tbn=0;
        double gu[3],delPR[6][1],alpha[6][4],alphaT[4][6],alphasq[4][4],alphasqinv[4][4],alphamat[4][6];	//z_debug
	double dl[4][1] = {{0},{0},{0},{0}};
        double	erro;
        double	xuser,yuser,zuser,bias,rsp,Lc,Lsp,Ltemp,L,erro1,Lflp,alt;
        double	Lcden;
        uint8_t	k1,loop;

   	double val,ans;			//z_ajit
   	int addr_val, addr_ans;		//z_ajit

	//z_debug : Array initialization
	/*
	double gu[3] = {0,0,0};
	double dl[4][1] = {{0},{0},{0},{0}};
	double delPR[6][1] = {{0},{0},{0},{0},{0},{0}};
	double alpha[6][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
	double alphaT[4][6] = {{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0}};
	double alphasq[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
	double alphasqinv[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
	double alphamat[4][6] = {{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0}};
	*/

	loop=0;

	do
	{

		//  Step 1 Initializing the User Coordinates
		gu[0]=xn;
		gu[1]=yn;
		gu[2]=zn;

		//   Step 2 Computing the Geometric Distance between Satellite  and Receiver Position
		//   SQRT[( Xj - Xo)2 + (Yj - Yo)2 + (Zj- Zo)2 ]+ TBN * C [ TBN : Clock Bias Term]
		//for(j=0;j<6;j++)
	      /*  for(j=0; j< NavprocData.Valid_NavICSat_Count;j++)
		{
		Sat_No = NavprocData.Nav_Valid_Buf_Id[i];
		PRn[j]=(pow(gu[0]-NavprocData.SatPositionECEF[j][0],2))+(pow(gu[1]-NavprocData.SatPositionECEF[j][1],2))+(pow(gu[2]-NavprocData.SatPositionECEF[j][2],2));
		PRn[j]=pow(PRn[j],0.5)+Tbn*C;

		} // For Loop*/

         	//for(j=0;j<6;j++)

		j=0;	//z: temp
		for(j=0; j< NavprocData.Valid_NavICSat_Count;j++)
		{
			Sat_No = NavprocData.Nav_Valid_Buf_Id[j];
			PRn[j]=(pow(gu[0]-NavprocData.SatPositionECEF[Sat_No][0],2))+(pow(gu[1]-NavprocData.SatPositionECEF[Sat_No][1],2))+(pow(gu[2]-NavprocData.SatPositionECEF[Sat_No][2],2));
			//PRn[j]=pow(PRn[j],0.5)+Tbn*C;
	 		#ifdef AJIT
			val = PRn[j];
	 		addr_val = (uint32_t) &val;	//memory address location 
	  		addr_ans = (uint32_t) &ans;
	  		sqrt_ajit_asm_double(addr_val, addr_ans);
			PRn[j]=ans+Tbn*C;
			#else
		   	PRn[j]=sqrt(PRn[j])+Tbn*C;
			#endif

		}

		// Step 3 :  Formulation of the Matrix [6][4] to Compute the User Position
		//	[Matrix[j] [0]  = (Xo -Xj) /( PRn[j] -TBN * C);
		//	[Matrix[j] [1]  = (Yo- Yj) /( PRn[j] --TBN * C)
		//	[Matrix[j] [2]  = ( Zo - Zj) /( PRn[j] -TBN * C)
		//	[Matrix[j] [3]  =  C

		j=0;	//z: temp
		for(j=0; j< NavprocData.Valid_NavICSat_Count;j++)
		{
			Sat_No = NavprocData.Nav_Valid_Buf_Id[j];
			for(k1=0;k1<3;k1++)
			{
				alpha[j][k1]=(gu[k1]-NavprocData.SatPositionECEF[Sat_No][k1])/(PRn[j]-Tbn*C);
			}
		} // For Loop

		for(j=0;j<6;j++)
			alpha[j][3]=C;

		//  Step 4  Defining [Matrix [6]  = PsudoRange[j] = ( Zo - Zj) /( PRn[j] -TBN * C)
		
		j=0;	//z: temp
		for(j=0; j< NavprocData.Valid_NavICSat_Count;j++)
		{
			Sat_No = NavprocData.Nav_Valid_Buf_Id[j];
			delPR[j][0]=(NavprocData.Corr1Pseudorange[Sat_No]*C)-PRn[j];
		}

		// Step 5 Solving the Matrix to estimate  Receiver Position
		// Matrix Transpose
		CompTranspose(6,4,alpha, alphaT);

		// Matrix Multiplication
		MatMultiplication(4,6,6,4,alphaT,alpha,alphasq);	//z_debug checked

		// Matrix Inverse
		FindMatrixInverse(4,alphasq,alphasqinv);

		// Matrix Multiplication
		MatMultiplication(4,4,4,6,alphasqinv,alphaT,alphamat);	//z_debug checked
		MatMultiplication(4,6,6,1,alphamat,delPR,dl);		//z_debug checked

		// Step 6 Computing the error
		erro=(pow(dl[0][0],2)) +( pow(dl[1][0],2) )+( pow(dl[2][0],2));
		//erro=pow(erro,0.5);
 		#ifdef AJIT
		val = erro;
 		addr_val = (uint32_t) &val;	//memory address location 
  		addr_ans = (uint32_t) &ans;
  		sqrt_ajit_asm_double(addr_val, addr_ans);
		erro = ans;
		#else
		erro=sqrt(erro);
		#endif

		if(erro>20){
			xn=xn+dl[0][0];
			yn=yn+dl[1][0];
			zn=zn+dl[2][0];
			Tbn=Tbn+dl[3][0];
			loop++;
		}
		else
			break;
	
	} while(loop<10);

	//Step 7  Satellite Position in ECEF Cartesian Coordinates System
	xuser= xn;
	yuser=yn;
	zuser=zn;
	bias=Tbn;
	zftemp = bias;

	// Step 8 Converting the Satellite Coordinates in ECEF to Spherical Coordinate System
	// 8.1 Computation of the distance from the centre of the earth to the Receiver Position
	rsp=(pow(xuser,2)) +( pow(yuser,2) )+( pow(zuser,2));
	//rsp=pow(rsp,0.5);
	#ifdef AJIT
	val = rsp;
	addr_val = (uint32_t) &val;	//memory address location 
	addr_ans = (uint32_t) &ans;
	sqrt_ajit_asm_double(addr_val, addr_ans);
	rsp = ans;
	#else
	rsp=sqrt(rsp);
	#endif

	// Step 8.2 Computation of Geocentric Latitude..[Lc].
	Lcden=(pow(xuser,2)) +( pow(yuser,2) );
	//Lcden=pow(Lcden,0.5);
	#ifdef AJIT
	val = Lcden;
	addr_val = (uint32_t) &val;	//memory address location 
	addr_ans = (uint32_t) &ans;
	sqrt_ajit_asm_double(addr_val, addr_ans);
	Lcden = ans;
	#else
	Lcden=sqrt(Lcden);
	#endif

	// Lc=  TAN INERVESE ( (Zuser / SQRT (X2user + Y2user)))
	Lc= atan2(zuser,Lcden);

	//Step8.3 Computation of  Geodetic  Longitude[L
	Lsp=atan2(yuser,xuser)*180/pi;

	// Step 8.4 Computation of Geodetic Latitude by Iterative Process...[Lflp]
	Ltemp=Lc;
	erro1=1;
	while(erro1>0.000001)
	{
		L= Lc+ ee*sin(2*Ltemp);
		erro1=fabs(Ltemp-L);
		Ltemp=L;
	}
	Lflp=L*(180/pi);

        // Step 8.5 Computation of Altitude of the Receiver using the corrected Earth radius value

        alt = rsp - re *(1-ee*pow(sin(L),2));

        // Saving User Position in Cartesian Coordinate  System
        NavprocData.UserPos_XYZ[0]=xuser;
        NavprocData.UserPos_XYZ[1]=yuser;
        NavprocData.UserPos_XYZ[2]=zuser;

        // Saving User Position in Spherical Coordinate System
        NavprocData.UserPosition_Long =Lsp;
        NavprocData.UserPosition_Lat =Lflp;
        NavprocData.UserPosition_Ht= alt;
        NavComputeDOP(4,alphasqinv);
}//*End of Subroutine*

//! Function to find transpose of matrix

void CompTranspose(int m, int n, double mat1[m][n], double b[n][m])
{
    int i1, j1;

	for (i1 = 0;i1 < m; i1++)
	{
		for (j1 = 0;j1 < n; j1++)
		{
			b[j1][i1] = mat1[i1][j1];
		}
	}
}

//! Function for matrix multiplication

void MatMultiplication(int m,int n,int p, int q,double mat2[][n],double mat3[][q],double prod[][q])
{
   int c, d, k;
	double sum = 0;

	if (n != p)
		PRINTF("\nMatrices with entered orders can't be multiplied with each other.\n");
	else
	{
		sum=0;
		for (c = 0; c < m; c++)
		{
			for (d = 0; d < q; d++)
			{
				for (k = 0; k < p; k++)
				{
					sum = sum + mat2[c][k]*mat3[k][d];
				}
				prod[c][d] = sum;
				sum = 0;
			}
		}
	}

}

//! Function to find determinant of matrix
double FindDeterminant(int x,double f[4][4])
{

	//z: Stack Req. = 42*4 = 168bytes

	double c[20],d=0,b[4][4];
	int j,p,q,t,pr;
	if(x==2)
	{
		d=0;
		d=(f[0][0]*f[1][1])-(f[0][1]*f[1][0]);
		return(d);
	}
	else
	{
		for(j=0;j<x;j++)
		{
			int r=0,s=0;
			for(p=0;p<x;p++)
			{
				for(q=0;q<x;q++)
				{
					if(p!=0&&q!=j)
					{
						b[r][s]=f[p][q];
						s++;
						if(s>x-2)
						{
							r++;
							s=0;
						}
					}
				}
			}
			for(t=0,pr=1;t<=(1+j);t++)
				pr=(-1)*pr;
			c[j]=pr*FindDeterminant(x-1,b);
		}
		for(j=0,d=0;j<x;j++)
			d=d+(f[0][j]*c[j]);

		return(d);
	}
}

 //! Function to find cofactor of matrix
void FindCoFactor(int f,double num[f][f],double fac[f][f] )	
{
	//z: Stack Req. = 22*4 = 88bytes

	double b[4][4];
	int p, q, m, n, i1, j1;
	for (q = 0;q < f; q++)
	{
		for (p = 0;p < f; p++)
		{
			m = 0;
			n = 0;
			for (i1 = 0;i1 < f; i1++)
			{
				for (j1 = 0;j1 < f; j1++)
				{
					if (i1 != q && j1 != p)
					{
						b[m][n] = num[i1][j1];
						if (n < (f - 2))
							n++;
						else
						{
							n = 0;
							m++;
						}
					}
				}
			}
			fac[q][p] = pow(-1, q + p) * FindDeterminant(f - 1,b);
		}
	}

}

//! Function to find inverse of matrix

void FindMatrixInverse(int k, double mat4[][k],double inv[][k])	//z_debug
{
	//z: Stack Req. = 35*4 = 150bytes 
	int i1,j1;
	double dd;
	double co[4][4],trans[4][4];

	dd = FindDeterminant(k,mat4);
	if (dd == 0)
		PRINTF("\nInverse of Entered Matrix is not possible\n");
	else
		FindCoFactor(k,mat4,co);

	CompTranspose(k,k,co,trans);

	for (i1 = 0;i1 < k; i1++)
	{
		for (j1 = 0;j1 < k; j1++)
		{
			inv[i1][j1] = trans[i1][j1] / dd;
		}
	}
}



//******************************************************************//
// Function to compute Dilution of Precision
//******************************************************************//

void NavComputeDOP(int kk,double mat[][4])	//z_debug
{

	//z: Stack Req. = 11*4 = 44bytes

	double 	GDOP=0,PDOP=0,VDOP=0,TDOP=0,HDOP=0;
	int	ii,jj;

   	double val,ans;			//z_ajit
   	int addr_val, addr_ans;		//z_ajit

	// Step 1 Computation of GDOP
	for(ii=0;ii<kk;ii++)
	{
		for(jj=0;jj<kk;jj++)
		{
			if(ii==jj)
			{
				GDOP=GDOP+mat[ii][jj];
			}
		}
	}
	//GDOP=pow(GDOP,0.5);
	#ifdef AJIT
	val = GDOP;
	addr_val = (uint32_t) &val;	//memory address location 
	addr_ans = (uint32_t) &ans;
	sqrt_ajit_asm_double(addr_val, addr_ans);
	GDOP = ans;
	#else
	GDOP=sqrt(GDOP);
	#endif


	// Step 2 Computation of PDOP Position (3D) Dilution Of Precision
	for(ii=0;ii<kk-1;ii++)
	{
		for(jj=0;jj<kk-1;jj++)
		{
			if(ii==jj)
			{
				PDOP=PDOP+mat[ii][jj];
			}
		}
	}
	//PDOP=pow(PDOP,0.5);
	#ifdef AJIT
	val = PDOP;
	addr_val = (uint32_t) &val;	//memory address location 
	addr_ans = (uint32_t) &ans;
	sqrt_ajit_asm_double(addr_val, addr_ans);
	PDOP = ans;
	#else
	PDOP=sqrt(PDOP);
	#endif

	//Step 3 HDOP = Horizontal Dilution Of Precision

	for(ii=0;ii<kk-2;ii++)
	{
		for(jj=0;jj<kk-2;jj++)
		{
			if(ii==jj)
			{
				HDOP=HDOP+mat[ii][jj];
			}
		}
	}
	//HDOP=pow(HDOP,0.5);
	#ifdef AJIT
	val = HDOP;
	addr_val = (uint32_t) &val;	//memory address location 
	addr_ans = (uint32_t) &ans;
	sqrt_ajit_asm_double(addr_val, addr_ans);
	HDOP = ans;
	#else
	HDOP=sqrt(HDOP);
	#endif

	//Step 4 VDOP = Vertical Dilution Of Precision
	VDOP=mat[kk-2][kk-2];
	//VDOP=pow(VDOP,0.5);
	#ifdef AJIT
	val = VDOP;
	addr_val = (uint32_t) &val;	//memory address location 
	addr_ans = (uint32_t) &ans;
	sqrt_ajit_asm_double(addr_val, addr_ans);
	VDOP = ans;
	#else
	VDOP=sqrt(VDOP);
	#endif

	//Step 5 TDOP = Time Dilution Of Precision
	TDOP=mat[kk-1][kk-1];
	//TDOP=pow(TDOP,0.5);
	#ifdef AJIT
	val = TDOP;
	addr_val = (uint32_t) &val;	//memory address location 
	addr_ans = (uint32_t) &ans;
	sqrt_ajit_asm_double(addr_val, addr_ans);
	TDOP = ans;
	#else
	TDOP=sqrt(TDOP);
	#endif

	// Saving DOP data in the Processed buffer

	NavprocData.GDOP = GDOP;
	NavprocData.PDOP = PDOP;
	NavprocData.HDOP = HDOP;
	NavprocData.VDOP = VDOP;
	NavprocData.TDOP = TDOP;
	return;

}//End of Subroutine


//******************************************************************//
// This routine computes Satellite Azimuth & Elevation Coordinates
//******************************************************************//


void NavComputeSatAzEl(int NavSatNo) // Input Data Ver ification done
{
	//z: Stack Req. = 22*4 = 88bytes
        double	satX,satY,satZ,userX,userY,userZ;
        double	r,dx,dy,dz;
        double	S,E,Z,El,Az,R,Lat,Lon;
        int	DatErFlg=0;

   	double val,ans;			//z_ajit
   	int addr_val, addr_ans;		//z_ajit

        // Check the Correctness of the Values before copying…
        // Satellite Position in ECEF Coordinate System

         if(NavprocData.SatPositionECEF[NavSatNo][0] == -500.0) DatErFlg= 1;
         if(NavprocData.SatPositionECEF[NavSatNo][1] == -500.0) DatErFlg= 1;
         if(NavprocData.SatPositionECEF[NavSatNo][2] == -500.0) DatErFlg= 1;

        // Receiver Position in ECEF Format

         if(NavprocData.UserPos_XYZ[0] == -500.0) DatErFlg= 1;
         if(NavprocData.UserPos_XYZ[1] == -500.0) DatErFlg= 1;
         if(NavprocData.UserPos_XYZ[2] == -500.0) DatErFlg= 1;
         if(NavprocData.UserPosition_Long== -500.0) DatErFlg= 1;
         if(NavprocData.UserPosition_Lat== -500.0) DatErFlg= 1;

         if (DatErFlg== 1){

		NavprocData.SatPosAzEl_Deg[NavSatNo][0] = -500.0;
		NavprocData.SatPosAzEl_Deg[NavSatNo][1] = -500.0;
		return;
	}//  if


        // Satellite Position in ECEF Coordinate System
        satX= NavprocData.SatPositionECEF[NavSatNo][0];
        satY= NavprocData.SatPositionECEF[NavSatNo][1];
        satZ= NavprocData.SatPositionECEF[NavSatNo][2];



        // Receiver  Position in  ECEF Format
        userX=NavprocData.UserPos_XYZ[0];
        userY=NavprocData.UserPos_XYZ[1];
        userZ=NavprocData.UserPos_XYZ[2];

        //  Step -1 Compute the Geometrical Distance between Receiver and satellite Position

        //r=pow((pow(satX-userX,2),pow(satY-userY,2),pow(satZ-userZ,2)),0.5);
	#ifdef AJIT
	val = (pow(satX-userX,2) + pow(satY-userY,2) + pow(satZ-userZ,2));
	addr_val = (uint32_t) &val;	//memory address location 
	addr_ans = (uint32_t) &ans;
	sqrt_ajit_asm_double(addr_val, addr_ans);
	r = ans;
	#else
	r=sqrt(pow(satX-userX,2) + pow(satY-userY,2) + pow(satZ-userZ,2) );
	#endif
	zftemp = r;

        // Step 2 : Compute dx , dy and dz
        dx=(satX-userX);
        dy=(satY-userY);
        dz=(satZ-userZ);

        /*Note: Step 3 & 4 have already been done in the Satellite position computation routine
        It is not still not clear why these Steps are repeated
        Check the Lat and Long values computed here with the original and then delete comment
        these Steps
        */

        Lon = NavprocData.UserPosition_Long * (pi/180); // degrees to radian conversion
        Lat = NavprocData.UserPosition_Lat* (pi/180); // degrees to radian conversion

        // why direction is not considered while computing Latitude and Longitude

        // Step 5 :  Computation of  Azimuth and Elevation Angles

	S= sin(Lat)*cos(Lon)*dx+ sin(Lat)*sin(Lon)*dy-cos(Lat)*dz;
	E=-1*sin(Lon)*dx+cos(Lon)*dy;
	Z=cos(Lat)*cos(Lon)*dx+cos(Lat)*sin(Lon)*dy+sin(Lat)*dz;

	//R=pow((pow(S,2)+pow(E,2)+pow(Z,2)),0.5);
	#ifdef AJIT
	val = (pow(S,2)+pow(E,2)+pow(Z,2));
	addr_val = (uint32_t) &val;	//memory address location 
	addr_ans = (uint32_t) &ans;
	sqrt_ajit_asm_double(addr_val, addr_ans);
	R = ans;
	#else
	R = sqrt(pow(S,2)+pow(E,2)+pow(Z,2));
	#endif

	//El=asin(Z/R)*180/pi;
	double cos_val;
	#ifdef AJIT
	val = 1-pow((Z/R),2);
	addr_val = (uint32_t) &val;	//memory address location 
	addr_ans = (uint32_t) &ans;
	sqrt_ajit_asm_double(addr_val, addr_ans);
	cos_val = ans;
	#else
	cos_val = sqrt(1-pow((Z/R),2));	
	#endif
	El = atan2((Z/R), cos_val);
	El = El*180/pi;	

	Az=atan2(E,-1*S)*180/pi;

	if(Az<0)
		Az= 360+Az;
	else  if(Az>360)
		Az=Az-360;

        // Saving the Satellite Az and El Coordinates in Processed Data Buffer
        NavprocData.SatPosAzEl_Deg[NavSatNo][0] = Az;
        NavprocData.SatPosAzEl_Deg[NavSatNo][1] =El;



        return ;

}//End of Subroutine




double NavComputeTroposphericDelay(int NavSatNo )
{
	//z: Stack Req. = 26*4 = 104bytes

        double Lat,Sat_EL,Rx_Ht;
        Lat = NavprocData.UserPosition_Lat,
        Sat_EL = NavprocData.SatPosAzEl_Deg[NavSatNo][1];
        Rx_Ht=NavprocData.UserPosition_Ht;

        // Tropospheric error Computation Steps
        //(A) Computation of  Tr z0,D :Dry Tropospheric Delay
        //To compute the  Dry Tropospheric Delay [at Zenith] Atmospheric Pressure at the Antenna Height is computed using Table 5.1
        double 	Prso[] = {1013.5, 1017.25, 1015.75, 1011.75, 1013.00};
        //double 	SeasonPrso [ ] = {0.0, -3.75, -2.25, -1.75, -0.50};		//z_ajit
        double	PrsSlope[] = {0.25,	-0.1,-0.266666667,0.083333333};
        double	Lato [ ] = {15.0, 30.0, 45.0, 60.0, 75.0};
        double   DelPo,Po;
        double   Const;
        int     DayofYear,Dmin;

	double val, ans;			//z_ajit
	int addr_val,addr_ans;		//z_ajit

        DayofYear=NavprocData.UTC_DayofYr;
        Dmin=28;

        //Step 1 Computation of Po  and  P
        if (Lat <= 15) {Po = 1013.5; DelPo = 0.0;}
        if (Lat >= 75){ Po = 1011.75; DelPo = -0.5;}

        if ( Lat > 15  && Lat <= 30) {
		Po =  Prso [0] +PrsSlope [0] *(Lat - Lato[0]);
		DelPo =  (-0.25) *(Lat - Lato[0]);
        }
        if (  Lat > 30  && Lat <= 45){
		Po =  Prso [1] +PrsSlope [1] *(Lat - Lato[1]);
		DelPo =  -3.75 +(0.1) *(Lat - Lato[1]);
        }
        if (  Lat > 45  && Lat <= 60){
		Po =  Prso [2] +PrsSlope [2] *(Lat - Lato[2]);
		DelPo =  -2.25 +(0.033) *(Lat - Lato[2]);
        }
        if (  Lat > 60  && Lat <= 75) {
		Po =  Prso [3] +PrsSlope [3] *(Lat - Lato[3]) ;
		DelPo=  -1.75 +(0.083) *(Lat - Lato[3]);
        }

        //Step 2 Computation of  Corrected P0  for the Latitude
        //For the receiver latitude and given day the corrected P0  is computed using the relation given in the above paragraph. Dmin = 28  for Northern Latitudes

        Const =  2 * pi * ( DayofYear - Dmin)/365.25;  ///check formula
        double  Cor_Po =  Po - DelPo * cos ( Const);

        //Step 3: Computation of   Dry Tropospheric Delay
        double Tr_z0_Dry =  (K1 * Rd * Cor_Po  * pow(10,-6)) / gm;

        //Where
        // k1 = 77:604K/mbar; 	Rd = 287:054 J/(kg K); 	gm = 9:784 m/s2

        //(B) Computation of  Tr z0,W :Wet  Tropospheric Delay
        // Step 1 Computation  of  To and  DelTo

	double 	To [ ] = {299.65, 294.15, 283.15, 272.15, 263.65};
	//double 	SeasonTo [ ] = {0.0, 7.0, 11.00, 15.00, 14.50};		//z_ajit
	double	ToSlope[] = {-0.366666667,-0.733333333,-0.733333333,-0.566666667};
	double   to,DelTo,Cor_To;


        if (Lat <= 15) {to = 299.65; DelTo = 0.0;}
        if (Lat  >= 75){to = 263.65; DelTo = 14.5;}

        if ( Lat > 15  && Lat <= 30) {
		to =  To [0] +ToSlope [0] *(Lat - Lato[0]);
		DelTo =  (0.46) *(Lat - Lato[0]);
        }
        if (  Lat > 30  && Lat <= 45){
		to =  To [1] +ToSlope [1] *(Lat - Lato[1]);
		DelTo =  7.0  +(0.266) *(Lat - Lato[1]);
        }
        if (  Lat > 45  && Lat <= 60){
		to=  To [2] +ToSlope [2] *(Lat - Lato[2]);
		DelTo = 11.0 +(0.266) *(Lat - Lato[2]);
        }
        if (  Lat > 60  && Lat <= 75) {
		to =  To [3] +ToSlope [3] *(Lat - Lato[3]) ;
		DelTo =  15.00 -(0.033) *(Lat - Lato[3]);
        }

        //Step 2 Computation of  Corrected P0  for the Latitude
        //For the receiver latitude and given day the corrected To  is computed using the relation given in the above paragraph. Dmin = 28  for Northern Latitudes

        Const=  2 * pi * ( DayofYear - Dmin)/365.25;
        Cor_To =  to - DelTo * cos ( Const);

        //Step 3 Computation  of  Eo and  DelEo
        double 	Eo [ ] = {26.31, 21.79, 11.66, 6.78, 4.11};
        //double 	SeasonEo [ ] = {0.0, 8.85, 7.24, 5.36, 3.39};	//z_ajit
        double	EoSlope[] = {-0.301333333,-0.675333333,-0.325333333,-0.178};
        double   Cor_E0,eo,DelEo;


        if (Lat <= 15) { eo = 26.31; DelEo = 0.0;}
        if (Lat >= 75) { eo = 4.11; DelEo  = 3.39;}

        if ( Lat > 15  && Lat <= 30) {
		eo =  Eo[0] +EoSlope[0] *(Lat - Lato[0]);
		DelEo =  -0.25 *(Lat - Lato[0]);
        }
        if (  Lat > 30  && Lat <= 45){
		eo =  Eo [1] +EoSlope [1] *(Lat - Lato[1]);
		DelEo =  -3.75  +(0.1) *(Lat - Lato[1]);
        }
        if (  Lat > 45  && Lat <= 60){
		eo =  Eo [2] +EoSlope [2] *(Lat - Lato[2]);
		DelEo = -2.25 +(0.033) *(Lat - Lato[2]);
        }
        if (  Lat > 60  && Lat <= 75) {
		eo =  Eo [3] +EoSlope [3] *(Lat - Lato[3]) ;
		DelEo =  -1.75 +(0.0833) *(Lat - Lato[3]);
        }

        //Step 4 Computation of  Corrected E0  for the Latitude
        //For the receiver latitude and given day the corrected To  is computed using the relation given in the above paragraph. Dmin = 28  for Northern Latitudes

        Const = 2 * pi * ( DayofYear - Dmin)/365.25;
        Cor_E0 =  eo - DelEo * cos ( Const);

        //Step 5 Computation  of  Bo and  DelBo
        double 	Bo [ ] = {6.3, 6.05, 5.58, 5.39, 4.53};
        //double 	SeasonBo [ ] = {0.0, 0.25, 0.32, 0.81, 0.62};	//z_ajit
        double	BoSlope[] = {-0.016666667,-0.031333333,-0.012666667,-0.057333333};
        double   DelBo,bo,Cor_Bo;
     	//double	 Lato [ ] = {15.0, 30.0, 45.0, 60.0, 75.0};

        if (Lat <= 15) { bo = 6.3; DelBo = 0.0;}
        if (Lat  >= 75){ bo = 4.53; DelBo  = 0.62;}

        if ( Lat > 15  && Lat <= 30) {
		bo =  Bo [0] +BoSlope [0] *(Lat - Lato[0]);
		DelBo =  -0.0166 *(Lat - Lato[0]);
        }
        if (  Lat > 30  && Lat <= 45){
		bo =  Bo[1] + BoSlope[1] *(Lat - Lato[1]);
		DelBo =  0.25+(0.000466) *(Lat - Lato[1]);
        }

        if (  Lat > 45  && Lat <= 60){
		bo =  Bo [2] +BoSlope [2] *(Lat - Lato[2]);
		DelBo = 0.32 +(0.03266) *(Lat - Lato[2]);
        }
        if (  Lat > 60  && Lat <= 75) {
		bo =  Bo [3] +BoSlope [3] *(Lat - Lato[3]) ;
		DelBo =  0.81 -(0.01266) *(Lat - Lato[3]);
        }

        //Step 6 Computation of  Corrected Bo  for the Latitude
        //For the receiver latitude and given day the corrected To  is computed using the relation given in the above paragraph. Dmin = 28  for Northern Latitudes

        Const = 2 * pi * ( DayofYear - Dmin)/365.25;
        Cor_Bo =  (bo - DelBo) * 10 -6 *cos (Const);
        //Step7 Computation  of  Lo and  DelLo
        double 	Lo [ ] = {2.77, 3.15, 257, 1.81, 155};
        //double 	SeasonLo [ ] = {0.0, 0.33, 0.46, 0.74, 0.3};	//z_ajit
        double	LoSlope[] = {0.025333333,16.92333333,-17.01266667,10.21266667};
        double   lo,DelLo,Cor_Lo;

	if (Lat <= 15) { lo = 2.77; DelLo = 0.0;}
	if (Lat  >= 75){ lo = 1.55; DelLo  = 0.3;}

	if ( Lat > 15  && Lat <= 30) {
		lo =  Lo [0] +LoSlope [0] *(Lat - Lato[0]);
		DelLo =  0.022*(Lat - Lato[0]);
	}
	if (  Lat > 30  && Lat <= 45){
		lo =  Lo [1] +LoSlope [1] *(Lat - Lato[1]);
		DelLo =  0.33 +((0.00866) *(Lat - Lato[1]));
	}

	if (  Lat > 45  && Lat <= 60){
		lo =  Lo [2] +LoSlope [2] *(Lat - Lato[2]);
		DelLo = 0.46 +((0.01866) *(Lat - Lato[2]));
	}
	if (  Lat > 60  && Lat <= 75) {
		lo =  Lo [3] +LoSlope [3] *(Lat - Lato[3]) ;
		DelLo =  0.74 - ((0.02933) *(Lat - Lato[3]));
	}

        //Step 8 Computation of  Corrected Lo  for the Latitude
        //For the receiver latitude and given day the corrected To  is computed using the relation given in the above paragraph. Dmin = 28  for Northern Latitudes

        Const=  2 * pi * ( DayofYear - Dmin)/365.25;
        Cor_Lo =  (lo - DelLo)  * cos (Const);

        //Step 9 Computation Wet Tropospheric Delay

        double Tr_z0_Wet =  (K2 * Rd *  pow(10,-6)  * Cor_E0) / (( Cor_Lo + 1) * gm  - (Cor_Bo * Rd * Cor_To));

        //Where
        //k1 = 77:604K/mbar; 	Rd = 287:054 J/(kg K); 	gm = 9:784 m/s2


        //Step 10 : To Compute the Dry  Tropospheric Delays at Receiver Height
        //To compute Temperature at the Receiver Height using the equation
        //        T =  To  -  H

       /* Where
        T  : Temperature at the Receiver Antenna Height  [ T1]
        To : Temperature at the Sea Level  [ Cor_To]
        H :  AMSL Height of the Receiver in Km [ RxHt]
          : Temperature Lapse Rate [Cor_Bo]*/

        double T1 = Cor_To - Cor_Bo  * Rx_Ht;

        double P1 =  (1 - ((Cor_Bo * Rx_Ht)/T1));
        double P2 =   g / (Rd * Cor_Bo);
        //Tr z,D = pow (P1, P2) *  Tr z0,D
	//z: P2 value confirm ??
        Tr_z0_Dry = pow (P1, P2) *  Tr_z0_Dry;

        //Step 11 : To Compute the Wet  Tropospheric Delays at Receiver Height
        T1 = Cor_To - Cor_Bo  * Rx_Ht;

        P1 =  (1 - ((Cor_Bo * Rx_Ht)/T1));
        P2 =   (g  *( Cor_Lo+1)) / (Rd * Cor_Bo);
	//z: P2 value confirm ??
        Tr_z0_Wet = pow (P1, P2) *  Tr_z0_Wet;

        //k1 = 77:604K/mbar,k2 = 382 000K2/mbar, Rd = 287:054 J/(kg K),
        //gm = 9:784 m/s2 and g =9:80665 m/s2

        //Step 12 : To Compute the  Dry & Wet  Tropospheric Delays with mapping function
        //The Total Delay ( Dry + Wet ) is multiplied by the Mapping Function given below
        //M(E)=  1.001⁄√(0.002001+ 〖Sin〗^2 (E))
        //Where E : Satellite Elevation Angel wrt Receiver

        //double Map_fun = 1.001 / ( sqrt ( 0.002001 + sin (Sat_EL ) * sin (Sat_EL )));
	
	double Map_fun;

	#ifdef AJIT
	val = (0.002001 + sin (Sat_EL ) * sin (Sat_EL )) ;
 	addr_val = (uint32_t) &val;	//memory address location 
  	addr_ans = (uint32_t) &ans;
  	sqrt_ajit_asm_double(addr_val, addr_ans);
	Map_fun = 1.001/ans;
	#else
	Map_fun = 1.001 / ( sqrt ( 0.002001 + sin (Sat_EL ) * sin (Sat_EL )));

	#endif

        //  double Map_fun = 1.001 / ( sqrt( 0.002001 + sin ( Lat) * sin ( Lat)));

        double TotalDelay = (Tr_z0_Dry +Tr_z0_Wet) * Map_fun;

        NavprocData.SatTroposphericCorr[NavSatNo]=TotalDelay;


        return  TotalDelay;

}




/*
******************************************************************
Input Parameters :
	(1) Rx Longitude and Latitude ; ( Degress)
	(2) Satellite  Co-ordinates ( Az, El)

Output:
	Ionospheric Delay in meters
******************************************************************
*/
void NavComputeIonosphericDelay( int NavSatNo , int32_t TOW) // // Input Data Ver ification done
{
	//z: Stack Req. = 24*4 = 96bytes
        double	F;
        double	PER=0,AMP=0;

        int	i,Iono_Flg =0;
        double	x,psi,t,Latm,LatI,LongI;
        double	Tiono;

        double	alpha[4],beta[4];
        double	Sat_AZ, Sat_EL, User_Long, User_Lat;

        // Step 1:  Verify the Satellite and User Coordinates
        // Before computing the Ionospheric Delays check the Input Values are Valid ?

        if (NavprocData.UserPosition_Long == -500.0)Iono_Flg =1;
        if (NavprocData.UserPosition_Lat== -500.0)Iono_Flg =1;
        if (NavprocData.SatPosAzEl_Deg[NavSatNo][0] == -500.0)Iono_Flg =1;
        if (NavprocData.SatPosAzEl_Deg[NavSatNo][1] == -500.0)Iono_Flg =1;

        //  Step 2 : Copy Alpha and Beta Values are to be read from the Navigation Data Buffer
        //  Check the Alpha and Beta Values read from the Navigation data are correct

        if (NavIonoCorrction.alpha0== -500.0)Iono_Flg =1;
        if (NavIonoCorrction.alpha1== -500.0)Iono_Flg =1;
        if (NavIonoCorrction.alpha2== -500.0)Iono_Flg =1;
        if (NavIonoCorrction.alpha3== -500.0)Iono_Flg =1;

        if (NavIonoCorrction.beta0== -500.0)Iono_Flg =1;
        if (NavIonoCorrction.beta1== -500.0)Iono_Flg =1;
        if (NavIonoCorrction.beta2== -500.0)Iono_Flg =1;
        if (NavIonoCorrction.beta3== -500.0)Iono_Flg =1;

        if (Iono_Flg == 1){
        	NavprocData.SatIonosphericCorr[NavSatNo] = -500.0;
        	return ;
        }


        // Step 2:  Copying the Satellite and User Coordinates
        User_Long = NavprocData.UserPosition_Long;
        User_Lat = NavprocData.UserPosition_Lat;

        Sat_AZ = NavprocData.SatPosAzEl_Deg[NavSatNo][0];
        Sat_EL = NavprocData.SatPosAzEl_Deg[NavSatNo][1];

        // Copy the Alpha and Beta Values read from the Navigation data

        alpha[0]= NavIonoCorrction.alpha0;
        alpha[1]= NavIonoCorrction.alpha1;
        alpha[2]= NavIonoCorrction.alpha2;
        alpha[3]= NavIonoCorrction.alpha3;



        beta[0]= NavIonoCorrction.beta0;
        beta[1]= NavIonoCorrction.beta1;
        beta[2]= NavIonoCorrction.beta2;
        beta[3]= NavIonoCorrction.beta3;


        // Step 3 Converting Azimuth and Elevation Angles from Degrees to Radians
        Sat_AZ = Sat_AZ*(pi/180.0);
        //Sat_EL=SAT_EL * PI /180.0;

        Sat_EL=Sat_EL * 1 /180.0;

        // Note : Only Azimuth and Elevation angles are to  be converted Radians.
        // The  Latitude and Longitude Angles will remain in Degrees

        //  Step -3 Compute the Angle (SI)
        // Earth's Central Angle between the User Position And The Earth Projection of Ionospheric Intersection Point
        psi=(0.0137/(Sat_EL+0.11))-0.022;

        // Step 4  Compute the Angle Latl
        // Geodetic Latitude of the Earth Projection of the Ionospheric Intersection Point (semi-circles)
        LatI= (User_Lat /180.0) + psi*cos(Sat_AZ);
        // Note : Receiver  Latitude Value is multiplied by 1/180 to convert Degrees to Semicircle

        if(LatI>0.416)	LatI=0.416;
        else  if(LatI<(-0.416))LatI=-0.416;

        // Step 5 :Geodetic Longitude of the Earth Projection of the Ionospheric Intersection Point (semi-circles)
        LongI= (User_Long) / 180.0 + psi * sin(Sat_AZ)/cos(LatI * pi); // Multi by PI : Semicircles to rads.

        // Step 6 Geomagnetic Latitude of the Earth Projection of the Ionospheric Intersection Point using //equation

        Latm= LatI + 0.064*cos((LongI-1.617)*pi);


        // Step 7 :local time, t, at the IPP is calculated using the IRNSS system time in seconds
        t=43200 * LongI + TOW;

        // Step 8 :ComputeSeconds of the Day
        t=fmod(t,86400);
        if(t>86400)t=t-86400;
        else  if(t<0)t=t+86400;

        // Step 9 : Compute Period of the Model using four beta coefficents
        //for(i=0;i<4;i++)	PER= PER + beta[i] * pow(Latm,i);

        PER  = beta[0] + beta[1] * Latm + beta[2] * pow(Latm,2) + beta[3]*pow(Latm,3);

        if(PER< 72000)	PER=72000;

        // Step 10 Compute the Slant Angle Factor

        F=1.0 +16.0*pow(0.53-Sat_EL,3);

        // Compute the Argument X

        x=2*pi*(t-50400)/PER;

        // Step 11 Compute Vertical Delay using the four coefficients Alpha provided by Navigation Message

        for(i=0;i<4;i++)
                AMP=AMP+alpha[i]*pow(Latm,i);

        AMP = alpha[0] + alpha [1] * Latm + alpha [2] * pow(Latm,2) + alpha [3]*pow(Latm,3);

        if(AMP<0)AMP=0;

        // Step 12 Compute the Ionospheric Delay correction
        if(fabs(x)<1.57)
		Tiono= F* (5*pow(10,-9) + AMP*((1-pow(x,2)/2) + (pow(x,4)/24.0)) );
        else
		Tiono = F*5*pow(10,-9);

        NavprocData.SatIonosphericCorr[NavSatNo] = Tiono * C;


        //return 1;	//orig
	return;		//z_gcc


}// End of the subroutine

//******************************************************************//
//!***************NavCompSatVel() Start*************
//******************************************************************//
void NavComputeSatVelocity(int TOW ,int NavSatNo)
{

	//z: Stack req. = 41*4 = 164bytes
        double	deltimes;
        double	mu=3.986005*pow(10,14);
        double	OmegaEDot= 7.2921151467*pow(10,-5);
        //double	F=-4.442807633*pow(10,-10);		//z_ajit
        double	tk,tc;//,t,tc,deltr,delt;
        double 	a,no,n,Mk,Ek,Vk,sinVk,cosVk,Phik,duk,drk,dik,uk,rk,ik,Xko,Yko,Omegak,Ekold,diff;
        double 	Mkdot,Ekdot,ikdot, Xkodot,Ykodot,rkdot,Vkdot,ukdot,Omegakdot,Vx,Vy,Vz;

   	double val,ans;			//z_ajit
   	int addr_val, addr_ans;		//z_ajit

        deltimes =  NavprocData.Corr1Pseudorange[NavSatNo];//*pow(10,-9);//NavprocData.SatPositionECEF[NavSatNo][3];


        tc=TOW-deltimes;

	//Step 1 tk = Compute Delta Time from Ephemeris Reference Epoch
	tk=tc-NavSubFrame2Data[NavSatNo].Toe;
	if(tk>=302400)
		tk=tk-604800;
	else if(tk<=-302400)
		tk=tk+604800;

        //Step 2 a = Compute Semi -major Axis  of the Satellite Orbit
        a=pow(NavSubFrame2Data[NavSatNo].A,2);

	//Step 3 no = Computed Mean Motion
	//no=pow(mu/a,0.5)/a;
	#ifdef AJIT
	val = mu/a ;
 	addr_val = (uint32_t) &val;	//memory address location 
  	addr_ans = (uint32_t) &ans;
  	sqrt_ajit_asm_double(addr_val, addr_ans);
	no=ans/a;
	#else
	no=sqrt(mu/a)/a;
	#endif

	//Step 4 n = Compute Corrected Mean Motion
	n= no+NavSubFrame1Data[NavSatNo].MD;

	//Step 5 Mk = Compute Mean Anomaly
	Mk=NavSubFrame2Data[NavSatNo].Mo+ (n*tk);
	Mkdot = n;

	//Step 6 Ek = Compute Eccentric anomaly
	Ek=Mk;

	do
	{
		Ekold=Ek;
		Ek=Mk+NavSubFrame2Data[NavSatNo].e*sin(Ek);
		diff=Ek-Ekold;
	}
	while(fabs(diff)>0.00000001);
	Ekdot = Mkdot/ (1- NavSubFrame2Data[NavSatNo].e* cos(Ek));



	//deltr=F*NavSubFrame2Data[NavSatNo].e*a*sin(Ek);

	//delt=NavSubFrame1Data[NavSatNo].af0+NavSubFrame1Data[NavSatNo].af1*(tc-NavSubFrame1Data[NavSatNo].Toc)+NavSubFrame1Data[NavSatNo].af2*pow((tc-NavSubFrame1Data[NavSatNo].Toc),2)+deltr - (NavSubFrame1Data[NavSatNo].Tgd );

	//t=tc-delt;

	//  deltimes=deltimes+delt;


	//sinVk= ((pow(1-pow(NavSubFrame2Data[NavSatNo].e,2),0.5))* sin(Ek))/(1-NavSubFrame2Data[NavSatNo].e*cos(Ek));
	#ifdef AJIT
	val = (1-pow(NavSubFrame2Data[NavSatNo].e,2));
 	addr_val = (uint32_t) &val;	//memory address location 
  	addr_ans = (uint32_t) &ans;
  	sqrt_ajit_asm_double(addr_val, addr_ans);
	sinVk= ((ans)* sin(Ek))/(1-NavSubFrame2Data[NavSatNo].e*cos(Ek));
	#else
	sinVk= ((sqrt(1-pow(NavSubFrame2Data[NavSatNo].e,2)))* sin(Ek))/(1-NavSubFrame2Data[NavSatNo].e*cos(Ek));
	#endif

	cosVk=(cos(Ek)-NavSubFrame2Data[NavSatNo].e)/(1-NavSubFrame2Data[NavSatNo].e*cos(Ek));

	//Step 7 Vk = Compute True Anomaly
	Vk=atan2(sinVk,cosVk);
	Vkdot = sin(Ek)*Ekdot*(1+ NavSubFrame2Data[NavSatNo].e*cos(Vk))/(sin(Vk)* ( 1- NavSubFrame2Data[NavSatNo].e* cos(Ek)));

	//Step 8 Compute Argument Of Latitude
	Phik= Vk+NavSubFrame2Data[NavSatNo].w;

	//Step 9 Compute Second Harmonic Perturbations
	duk= NavSubFrame1Data[NavSatNo].Cus* sin(2*Phik) + NavSubFrame1Data[NavSatNo].Cuc* cos(2*Phik);
	drk= NavSubFrame1Data[NavSatNo].Crs* sin(2*Phik) + NavSubFrame1Data[NavSatNo].Crc* cos(2*Phik);
	dik= NavSubFrame1Data[NavSatNo].Cis* sin(2*Phik) + NavSubFrame1Data[NavSatNo].Cic* cos(2*Phik);

	//Step 10 Calculate Corrected Argument Of Latitude (uk), Corrected Radius(rk), Corrected Inclination (ik) & Corrected Longitude of Ascending Node (Ωk)
	uk=Phik+duk;
	rk=a*(1-NavSubFrame2Data[NavSatNo].e*cos(Ek))+drk;
	ik=NavSubFrame2Data[NavSatNo].Io+dik+NavSubFrame1Data[NavSatNo].IDOT*( NavprocData.CorTOWC[NavSatNo]-NavSubFrame2Data[NavSatNo].Toe);

	rkdot = a*NavSubFrame2Data[NavSatNo].e*sin(Ek) * n/ (1- NavSubFrame2Data[NavSatNo].e* cos(Ek)) - 2* (NavSubFrame1Data[NavSatNo].Crc* sin(2*uk) - NavSubFrame1Data[NavSatNo].Crs* cos(2*uk)) * Vkdot ;
	ukdot = Vkdot - 2* (NavSubFrame1Data[NavSatNo].Cuc* sin(2*uk) - NavSubFrame1Data[NavSatNo].Cus* cos(2*uk)) * Vkdot;
	ikdot = NavSubFrame1Data[NavSatNo].IDOT - 2* (NavSubFrame1Data[NavSatNo].Cic* sin(2*uk) - NavSubFrame1Data[NavSatNo].Cis* cos(2*uk)) * Vkdot;

	//Step 11 Position in orbital plane
	Xko= rk* cos(uk);
	Yko= rk* sin(uk);

	Xkodot= rkdot* cos(uk) - rk * sin(uk)* ukdot;
	Ykodot= rkdot* sin(uk) + rk * cos(uk)* ukdot;

        Omegakdot = NavSubFrame2Data[NavSatNo].OmegaDot - OmegaEDot;
        Omegak=NavSubFrame2Data[NavSatNo].Omega+NavSubFrame2Data[NavSatNo].OmegaDot*( NavprocData.CorTOWC[NavSatNo]-NavSubFrame2Data[NavSatNo].Toe)- OmegaEDot* NavprocData.CorTOWC[NavSatNo];

         //Step 12 Satellite Velocity values are obtained by taking the derivatives
        Vx=(Xkodot - Yko* cos(ik) *Omegakdot) * cos(Omegak) - (Xko *Omegakdot + Ykodot* cos(ik) - Yko* sin(ik) *ikdot ) * sin(Omegak);
        Vy= ( Xkodot - Yko* cos(ik) *Omegakdot) * sin(Omegak) + (Xko *Omegakdot + Ykodot* cos(ik) - Yko* sin(ik) *ikdot ) * cos(Omegak);
        Vz= Ykodot* sin(ik) + Yko* cos(ik) *ikdot;

        NavprocData.SatVelocity[NavSatNo][0]=Vx;
        NavprocData.SatVelocity[NavSatNo][1]=Vy;
        NavprocData.SatVelocity[NavSatNo][2]=Vz;


}// End of the Subroutine

//******************************************************************//
//  To compute UTC from the Towc data
//******************************************************************//


void NavFindUTCTime(int t) // Input Data Verified…
{
	//z : Stack Req. = 21*4+1 = 85bytes 

	int      i,Sat_No;
	double    Tutc,delTutc,W;
	uint8_t	 CurHr,CurMin,CurSec;
	uint16_t mday[13]={0,31,59,90,120,151,181,212,243,273,304,334,365};
	int	 nday,nod,CurYr,CurMonth, CurDay,noyr,lastyr,remday,WN1;

	WN1=-500;	//z_debug for -o 3
	CurMonth =0;

	delTutc = 0.0;	//z_ajit
	Tutc = 0.0;	//z_ajit : to allocate value
			//enter any if statement confirm behaviour ?? affects  UTC_Hrs, UTC_Mins, UTC_Sec

	CurHr=0; CurMin=0; CurSec=0;	//z_debug for -o3 run on fpga

	// Step – 0 To check availability of the correct UTC Correction Data
	if (NavprocData.UTCAbsFlg == 1) // UTC data not available
		//return 1;	//orig
		return;


	// Step -1 Copying Week Number

	i =0;	//z: temp
	for(i=0; i<NavprocData.Valid_NavICSat_Count;i++){
		Sat_No = NavprocData.Nav_Valid_Buf_Id[i];

		if (NavSubFrame1Data[Sat_No].WN != -500.0){
			WN1= NavSubFrame1Data[Sat_No].WN;
			break;	
		}

	}// For
	if ( WN1 == -500.0) return ; // No Valid Week Number


	/* The effectivity time of leap second event indicated by the WNLSF  [Leap second reference week number]
	and  DN  [Leap second reference day number] is not in the past (relative to the user's present time)
	*/
	//z: Experimentally on gcc seen, program doesn't go in any of the 3 if's 
	if((WN1 >= NavUTCCorr.WNlsf)&&((NavUTCCorr.DN + 3/4 > t/86400)||(NavUTCCorr.DN+5/4 < t/86400)))
	{
		// ΔTUTC =ΔTLSF +A0utc+A1utc (TE -Toutc+604800(WN - WNoutc))+A2utc(TE-Toutc+ 604800(WN - WNoutc))2 seconds
		delTutc= NavUTCCorr.delTls+NavUTCCorr.A0utc+NavUTCCorr.A1utc*(t-NavUTCCorr.Toutc+604800*(WN1- NavUTCCorr.WNoutc))+NavUTCCorr.A2utc*pow((t-NavUTCCorr.Toutc+604800*(WN1-NavUTCCorr.WNoutc)),2);
		Tutc=fmod((t-delTutc),86400);

	}

	/* The current time falls within  time span of six hours prior to the effectivity time of leap second event to six hours after the effectivity time
	*/
	else   if(( NavUTCCorr.DN+3/4 < t/86400) &&(t/86400 < NavUTCCorr.DN+5/4))
	{
		W=fmod((t-delTutc-43200),86400)+43200;
		Tutc=fmod(W,(86400+NavUTCCorr.delTlsf-NavUTCCorr.delTls));

	}
	/* The effectivity time of the leap second event, as indicated by the WNLSF and DN values, is in the "past" (relative to Rx's current time),
	*/
	else  if((NavUTCCorr.WNlsf< WN1)&&((NavUTCCorr.DN+3/4 > t/86400)||(NavUTCCorr.DN+5/4 < t/86400)))
	{
		delTutc= NavUTCCorr.delTlsf+NavUTCCorr.A0utc+NavUTCCorr.A1utc*(t-NavUTCCorr.Toutc+604800*(WN1-NavUTCCorr.WNoutc))+NavUTCCorr.A2utc*pow((t-NavUTCCorr.Toutc+604800*(WN1-NavUTCCorr.WNoutc)),2);
		Tutc=fmod((t-delTutc),86400);

	}

	// Computing the Current Hour

	CurHr = Tutc/3600;

	// Compute Current Hours : Balance  Hours / Divided by 60;
	CurMin = fmod(Tutc,3600)/60;

	// Compute Current Second by finding Balance Seconds
	CurSec  = fmod(Tutc,60);;


	uint8_t z;

	// The IRNSS System Time start epoch shall be 00:00 UT on Sunday August 22nd 1999

	// Step 2-1 Converting into  Total Week No to Total Number of Days

	nod=WN1*7;

	// Step 2-2 Removing Extra Days of  the Leap Years [ndays = Total No of Days -  Leap Year days]
	nday=nod-nod/(365*4);

	// Step 2-3 No of Years from the no of days
	noyr=nday/365;

	// Step 2-4 Computing Current Year from Year 1999
	CurYr=1999 + noyr;

	// Step 2-5 Compute No of days till Last Year to compute
	lastyr = 132 +(noyr-1-(nod/(365*4)))*365 + (nod/(365*4))*366;

	//Step 2-6 Remaining Days in the Current Year for computation of the Month of the Year
	remday=nod-lastyr;

	// Step 2-7 Computing the Current Month
	for(z=0;z<12;z++){
		if((mday[z]<=remday)&&(mday[z+1]>remday)){
			CurMonth =z+1;
			break;
		}
	}// For

        //Step 2-8 Computing the Current Day

        CurDay=remday-mday[z]+(t/86400);

        //Step 2-9 Copying the Date and Time in the Processed Data Buffer

        NavprocData.UTC_Day = CurDay;
        NavprocData.UTC_DayofYr = remday;
        NavprocData.UTC_Mon = CurMonth;
        NavprocData.UTC_Yr = CurYr;

        NavprocData.UTC_Hrs = CurHr;
        NavprocData.UTC_Mins =CurMin,
        NavprocData.UTC_Sec = CurSec;
        return;

}//End of Subroutine

// NEMA
/*------------------------------------------------
//z: temp
void NavGIGGAMesage() // Completed & Checked
{
	
	int i;
	comma[0]=',';
	comma[1]='\0';

	//sprintf(GIGGAFrame,"%s","$GIGGA,");	//z_ajit
	
	GIGGAFrame[0] = '$';	//z_ajit
	GIGGAFrame[1] = 'G';
	GIGGAFrame[2] = 'I';
	GIGGAFrame[3] = 'G';
	GIGGAFrame[4] = 'G';
	GIGGAFrame[5] = 'A';
	GIGGAFrame[6] = ',';
	GIGGAFrame[7] = '\0';


	// 1 UTC Time
	if(NavprocData.UTC_Hrs==-500 || NavprocData.UTC_Mins==-500 || NavprocData.UTC_Sec==-500)
	{
		//strcat(GIGGAFrame,comma);	//z_ajit
		
		i=0;
		while(GIGGAFrame[i] != '\0'){	//z_ajit
			i++;
		}
		GIGGAFrame[i] = comma[0]; i++;
		GIGGAFrame[i] = comma[1]; 			

	}else {
		sprintf(str1,"%02.f%02.f%02.f",NavprocData.UTC_Hrs,NavprocData.UTC_Mins,NavprocData.UTC_Sec );
		strcat(GIGGAFrame,str1);
	}

	// 2 Latitude in Degrees

	str1[0]='\0';
	if(NavprocData.UserPosition_Lat==-500){
		strcat(GIGGAFrame,comma);
		strcat(GIGGAFrame,comma);
	}else {
		sprintf(str1,"%8.3f,%c,",(NavprocData.UserPosition_Lat *100.0),NavprocData.RX_Lat_Dir);
		strcat(GIGGAFrame,str1);
	}

	//3 Longitude in Degrees
	str1[0]='\0';
	if(NavprocData.UserPosition_Long==-500){
		strcat(GIGGAFrame,comma);
		strcat(GIGGAFrame,comma);
	}else {
		sprintf(str1,"%9.3f,%c,",(NavprocData.UserPosition_Long*100.), NavprocData.Rx_Lon_Dir);
		strcat(GIGGAFrame,str1);
	}

	// Fix quality      //Not Available

	
	// Fix Quality: 0 = invalid
        // 1 = GPS fix (SPS)
        // 2 = DGPS fix
        // 3 = PPS fix
	//	 4 = Real Time Kinematic
	//	 5 = double RTK
        // 6 = estimated (dead reckoning) (2.3 feature)
	//	 7 = Manual input mode
	//	 8 = Simulation mode
	//	 In the current Implmentation Fix Quality value is 1 Default is 0
	

	str1[0]='\0';
	if(NavNMEAdata.Rx_QC_Id==-500)
		strcat(GIGGAFrame,comma);
	else{
		sprintf(str1,"%d,",NavNMEAdata.Rx_QC_Id);
		strcat(GIGGAFrame,str1);
	}

	//5 Number of satellites being tracked
	str1[0]='\0';
	if(NavprocData.Valid_NavICSat_Count==-500)
		strcat(GIGGAFrame,comma);
	else {
		sprintf(str1,"%01d,",NavprocData.Valid_NavICSat_Count);
		strcat(GIGGAFrame,str1);
	}

	//6 HDOP
	str1[0]='\0';
	if(NavprocData.HDOP==-500)
		strcat(GIGGAFrame,comma);
	else {
		sprintf(str1,"%1.1f,",NavprocData.HDOP);
		strcat(GIGGAFrame,str1);
	}

	// 7  Altitude, Meters, above mean sea level
	str1[0]='\0';
	if(NavprocData.UserPosition_Ht==-500)
		strcat(GIGGAFrame,comma);
	else {
		sprintf(str1,"%.1f,",NavprocData.UserPosition_Ht);
		strcat(GIGGAFrame,str1);
	}

	// Height of Geoid (Mean Sea Level) above WGS84 ellipsoid   //NOT GETTING
	str1[0]='\0';
	if(NavprocData.geoid==-500)
		strcat(GIGGAFrame,comma);
	else {
		sprintf(str1,"%2.2f,",NavprocData.geoid);
		strcat(GIGGAFrame,str1);
	}

	// 9 Time in seconds since last DGPS update [Not Applicable ]
	str1[0]='\0';
	strcat(GIGGAFrame,comma);


	// 10 DGPS station ID number [Not Applicable ]
	str1[0]='\0';
	strcat(GIGGAFrame,comma);

	//11 Checksum
	checksum=calc_checksum(GIGGAFrame);
	sprintf(str1,"*%02X",checksum);
	strcat(GIGGAFrame,str1);

	return;

}// End of the subroutine

-------------------------------------------------------*/


// This function generates GSA message which contain the list of the
// active satellites along with DOP values

	// http://www.gpsinformation.org/dale/nmea.htm#GSA

/*----------------------------------------------------
//z: temp
void NavGIGSAMesage()  // Completed &Checked
{

	int i,Sat_No;

	comma[0]=',';
	comma[1]='\0';


	// Mode ; Automatic or Manual Selection of the Satellite 'A'
	// Position Fix 2D or 3D. It is three 3D Hence 3 1: No Fix
	// This value needs to be read from the processed data.

	//int ThreeDFix =3 ; // Initialised to 1: No fix 2: 2D Fix 3 : 3D Fix	//z_ajit

	sprintf(GIGSAFrame, "GIGSA,A,%1d,", NavprocData.ThreeDFix);

	// Inserting PRN Id..[ Maximum for 12 Satellites]

	str1[0]='\0';
	for (i=0; i<NavprocData.Valid_NavICSat_Count;i++){
		Sat_No = NavprocData.Nav_Valid_Buf_Id[i]+1;
		// 0 is prefixed because the satellite numbres are less than 10
		sprintf(str1,"0%d,", Sat_No);
		strcat(GIGSAFrame,str1);
	}
	// Add Commas for remaining Satellites
	for (i= NavprocData.Valid_NavICSat_Count; i< 12; i++)
		strcat(GIGSAFrame,comma);

	// PDOP
	str1[0]='\0';
	if(NavprocData.PDOP==-500)
		strcat(GIGSAFrame,comma);
	else {
		sprintf(str1,"%.1f,",NavprocData.PDOP);
		strcat(GIGSAFrame,str1);
	}

	// HDOP
	str1[0]='\0';
	if(NavprocData.HDOP==-500)
		strcat(GIGSAFrame,comma);
	else {
		sprintf(str1,"%.1f,",NavprocData.HDOP);
		strcat(GIGSAFrame,str1);
	}

	// VDOP
	str1[0]='\0';
	if(NavprocData.VDOP==-500)
		strcat(GIGSAFrame,comma);
	else {
		sprintf(str1,"%.1f",NavprocData.VDOP);
		strcat(GIGSAFrame,str1);
	}

	//Checksum
	str1[0]='\0';
	checksum=calc_checksum(GIGSAFrame);
	sprintf(str1,"*%02X",checksum);
	strcat(GIGSAFrame,str1);

	return;

}// End of the Subroutine
---------------------------------------------------*/


/*--------------------------------------------------
//z: temp
void NavGIGLLMessage() // Completed & checked
{

	comma[0]=',';
	comma[1]='\0';

	// 1 UTC Time
	sprintf(GIGGLLFrame,"%s","$GIGLL,");


	// 1 Latitude in Degrees
	str1[0]='\0';
	if(NavprocData.UserPosition_Lat==-500)
	{
		strcat(GIGGLLFrame,comma);
		strcat(GIGGLLFrame,comma);
	}else {
		sprintf(str1,"%7.2f,%c,",(NavprocData.UserPosition_Lat*100.0),NavprocData.RX_Lat_Dir);
		strcat(GIGGLLFrame,str1);
	}

	//2 Longitude in Degrees
	str1[0]='\0';
	if(NavprocData.UserPosition_Long==-500){
		strcat(GIGGLLFrame,comma);
		strcat(GIGGLLFrame,comma);
	}else {
		sprintf(str1,"%8.2f,%c,",(NavprocData.UserPosition_Long *100.0), NavprocData.Rx_Lon_Dir);
		strcat(GIGGLLFrame,str1);
	}

	// 3 UTC Time
	str1[0]='\0';
	if(NavprocData.UTC_Hrs==-500 || NavprocData.UTC_Mins==-500 || NavprocData.UTC_Sec==-500)
	{
		strcat(GIGGLLFrame,comma);
	}else {
		sprintf(str1,"%02.f%02.f%02.f",NavprocData.UTC_Hrs,NavprocData.UTC_Mins,NavprocData.UTC_Sec );
		strcat(GIGGLLFrame,str1);
	}

	//The next letter just lets us know if the signal is Active (A) or Void (V).
	//An ‘A’ indicates NavIC  a signal is being received and things are working properly.
	//‘V’ means NavIC Signal is absent.

	str1[0]='\0';
	sprintf(str1,"%c",NavprocData.SigStatus); // Variable to be added to the Processed data structure
	strcat(GIGGLLFrame,str1);

	return;
}// End of the subroutine
--------------------------------------------------*/

/*-------------------------------------------------
//z: temp
void NavGIGSVMesage() // Not Checked
{
	

	//NavprocData.No_of_sentences_data=-500;
	double Az=NavprocData.SatPosAzEl_Deg[0][0];
	double El=NavprocData.SatPosAzEl_Deg[0][1];

	comma[0]=',';
	comma[1]='\0';

	sprintf(GIGSVFrame,"%s","$GIGSV,");

	// Number of sentences for full data    //NOT GETTING
	str1[0]='\0';
	if(NavprocData.No_of_sentences_data==-500)
		strcat(GIGSVFrame,comma);
	else {sprintf(str1,"%d,",NavprocData.No_of_sentences_data); strcat(GIGSVFrame,str1);}

	// sentence 1 of 2          //NOT GETTING
	str1[0]='\0';
	if(NavprocData.sentence_no==-500)
		strcat(GIGSVFrame,comma);
	else {sprintf(str1,"%d,",NavprocData.sentence_no); strcat(GIGSVFrame,str1);}

	// Number of satellites in view
	str1[0]='\0';
	if(NavprocData.Valid_NavICSat_Count==-500)
		strcat(GIGSVFrame,comma);
	else {sprintf(str1,"%d,",NavprocData.Valid_NavICSat_Count); strcat(GIGSVFrame,str1);}

	// Satellite PRN number         //NOT GETTING
	str1[0]='\0';
	if(NavprocData.Sat_PRN_no==-500)
		strcat(GIGSVFrame,comma);
	else {sprintf(str1,"%d,",NavprocData.Sat_PRN_no); strcat(GIGSVFrame,str1);}

	// Azimuth
	str1[0]='\0';
	if(Az==-500)
		strcat(GIGSVFrame,comma);
	else {sprintf(str1,"%.f,",Az); strcat(GIGSVFrame,str1);}

	// Elevation
	str1[0]='\0';
	if(El==-500)
		strcat(GIGSVFrame,comma);
	else {sprintf(str1,"%.f,",El); strcat(GIGSVFrame,str1);}

	// SNR - higher is better       //NOT GETTING
	str1[0]='\0';
	if(NavprocData.SNR==-500)
		strcat(GIGSVFrame,comma);
	else {sprintf(str1,"%d,",NavprocData.SNR); strcat(GIGSVFrame,str1);}
	//Checksum
	checksum=calc_checksum(GIGSVFrame);
	sprintf(str1,"*%02X",checksum);
	strcat(GIGSVFrame,str1);


}
--------------------------------------------*/

// This function generates essential NavIC pvt (position, velocity, time) data.
// It is called RMC

/*--------------------------------------------
//z: temp
void NavGIRMCMessage() // Checked + Require Additional Data
{

	unsigned char checksum;


	comma[0]=',';
	comma[1]='\0';

	sprintf(GIRMCFrame,"%s","$GIRMC,");

	// 1 UTC Time
	if(NavprocData.UTC_Hrs==-500 || NavprocData.UTC_Mins==-500 || NavprocData.UTC_Sec==-500)
	{
		strcat(GIRMCFrame,comma);

	}else {
		sprintf(str1,"%02.f%02.f%02.f",NavprocData.UTC_Hrs,NavprocData.UTC_Mins,NavprocData.UTC_Sec );
		strcat(GIRMCFrame,str1);
	}

	// Signal Status

	str1[0]='\0';
	sprintf(str1,"%c",NavprocData.SigStatus); // Variable to be added to the Processed data structure
	strcat(GIRMCFrame,str1);

	// Latitude
	str1[0]='\0';
	if(NavprocData.UserPosition_Lat==-500)
		strcat(GIRMCFrame,comma);
	else {
		sprintf(str1,"%8.3f,%c,",(NavprocData.UserPosition_Lat *100.0),NavprocData.RX_Lat_Dir);
		strcat(GIRMCFrame,str1);
	}

	// Longitude
	str1[0]='\0';
	if(NavprocData.UserPosition_Long==-500)
		strcat(GIRMCFrame,comma);
	else {
		sprintf(str1,"%2.4f,%c,",(NavprocData.UserPosition_Long *100.0),NavprocData.Rx_Lon_Dir);
		strcat(GIRMCFrame,str1);
	}

	// Speed over the ground in knots    //New Variable
	str1[0]='\0';
	if(NavprocData.Speed_knots==-500)
		strcat(GIRMCFrame,comma);
	else {
		sprintf(str1,"%d,",NavprocData.Speed_knots);
		strcat(GIRMCFrame,str1);
	}

	// Track angle in degrees True      //New Variable

	str1[0]='\0';
	if(NavprocData.Track_angle==-500)
	strcat(GIRMCFrame,comma);
	else {
		sprintf(str1,"%d,",NavprocData.Track_angle);
		strcat(GIRMCFrame,str1);
	}

	// UTC Day
	str1[0]='\0';
	if(NavprocData.UTC_Day==-500 ||NavprocData.UTC_Mon==-500 ||NavprocData.UTC_Yr==-500)
		strcat(GIRMCFrame,comma);
	else {
		sprintf(str1,"%02.f%02.f%02.f",NavprocData.UTC_Day,NavprocData.UTC_Mon, NavprocData.UTC_Yr );
		strcat(GIRMCFrame,str1);
	}

	// Magnetic Variations [To be added]
	strcat(GIRMCFrame,comma);

	//Checksum
	checksum=calc_checksum(GIRMCFrame);
	sprintf(str1,"*%02X",checksum);
	strcat(GIRMCFrame,str1);

}
------------------------------------------*/

unsigned char calc_checksum(const char *s)
{
	unsigned char result;
	result = 0;
	s++; // Skip dollar sign
	while ((*s != '*') && (*s != '\0'))
		result ^= *s++;
	return result;
}

void NavComputeUserVelocitySixSat()
{
	//z: Stack Req. = 48 *4 = 192bytes

	double fr[6];
	//int ii,jj,sv,svu;		//z_ajit
	//int32_t dumyval[10];		//z_ajit
	double fL5 = 1176450000.0;
	//char mytext3[200];		//z_ajit
	double PRn[6];
	double alpha[6][4];	//z_debug
	int i,j;
	//int c;	//z_ajit

	//z_debug
	//double alpha[6][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};

   	double val,ans;			//z_ajit
   	int addr_val, addr_ans;		//z_ajit

	double dopf[6];
	dopf[0]=-187566; ///doubtful-187566
	dopf[1]= 10169;
	dopf[2]=-354778;
	dopf[3]=-107718;
	dopf[4]=-20269;
	dopf[5]=-3903; ///doubtful


	for(j=0;j<6;j++)
	{
		PRn[j]=(pow(NavprocData.UserPos_XYZ[0]-NavprocData.SatPositionECEF[j][0],2))+(pow(NavprocData.UserPos_XYZ[1]-NavprocData.SatPositionECEF[j][1],2))+(pow(NavprocData.UserPos_XYZ[2]-NavprocData.SatPositionECEF[j][2],2));
		//PRn[j]=pow(PRn[j],0.5) ;
		#ifdef AJIT
		val = PRn[j];
		addr_val = (uint32_t) &val;	//memory address location 
		addr_ans = (uint32_t) &ans;
		sqrt_ajit_asm_double(addr_val, addr_ans);
		PRn[j] = ans;
		#else
		PRn[j] = sqrt(PRn[j]);
		#endif

	}

	for(i=0;i<6;i++)
	{
		for(j=0;j<3;j++)
		{
			alpha[i][j]= (NavprocData.UserPos_XYZ[j] -NavprocData.SatPositionECEF[i][j] ) / (PRn[i]);

		}

	}

	for(j=0;j<6;j++)
		alpha[j][3]=C;

	double rr[6][1];
	for(i=0;i<6;i++)
	{
		fr[i]=fL5+(dopf[i]/1000);
		rr[i][0]= C*(1-(fr[i]/fL5));
	}

	double vnew[6][1],rhodot[6][1],Vuser[6][1];
	//double alphainv[4][4];		//z_ajit
	double alphaT[4][6],alphasq[4][4],alphasqinv[4][4],alphamat[4][6];	//z_debug

	//z_debug : Array initialization
	/*
	double alphaT[4][6] = {{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0}};
	double alphasq[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
	double alphasqinv[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
	double alphamat[4][6] = {{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0}};
	*/

	double I1[3][1],I2[3][1],I3[3][1],I4[3][1],I5[3][1],I6[3][1];

	double V1[1][3],V2[1][3],V3[1][3],V4[1][3],V5[1][3],V6[1][3];

	for(i=0;i<3;i++)
	{
		V1[0][i]=NavprocData.SatVelocity[0][i];
		V2[0][i]=NavprocData.SatVelocity[1][i];
		V3[0][i]=NavprocData.SatVelocity[2][i];
		V4[0][i]=NavprocData.SatVelocity[3][i];
		V5[0][i]=NavprocData.SatVelocity[4][i];
		V6[0][i]=NavprocData.SatVelocity[5][i];
	}

	double v1[1][1],v2[1][1],v3[1][1],v4[1][1],v5[1][1],v6[1][1];

	for(i=0;i<3;i++)
	{
	I1[i][0]=-1 * alpha[0][i];
	I2[i][0]=-1 * alpha[1][i];
	I3[i][0]=-1 * alpha[2][i];
	I4[i][0]=-1 * alpha[3][i];
	I5[i][0]=-1 * alpha[4][i];
	I6[i][0]=-1 * alpha[5][i];
	}

	MatMultiplication1331(1,3,3,1,V1,I1,v1);	//z_debug checked all right
	MatMultiplication1331(1,3,3,1,V2,I2,v2);
	MatMultiplication1331(1,3,3,1,V3,I3,v3);
	MatMultiplication1331(1,3,3,1,V4,I4,v4);
	MatMultiplication1331(1,3,3,1,V5,I5,v6);
	MatMultiplication1331(1,3,3,1,V6,I6,v6);

	vnew[0][0] = v1[0][0];
	vnew[1][0] = v2[0][0];
	vnew[2][0] = v3[0][0];
	vnew[3][0] = v4[0][0];
	vnew[4][0] = v5[0][0];
	vnew[5][0] = v6[0][0];

	for(i=0;i<6;i++)
	{
	rhodot[i][0]=rr[i][0]-vnew[i][0];

	}

	CompTranspose64(6,4,alpha, alphaT);
	MatMultiplication46x4(4,6,6,4,alphaT,alpha,alphasq);	//z_debug checked
	FindMatrixInverse(4,alphasq,alphasqinv);
	MatMultiplication4446(4,4,4,6,alphasqinv,alphaT,alphamat);	//z_debug checked
	MatMultiplication46x1(4,6,6,1,alphamat,rhodot,Vuser);	//z_debug checked

	//inverse(4,alpha,alphainv);
	//mult(4,4,4,1,alphainv,rhodot,Vuser);

}

void NavComputeUserVelocityFourSat()
{

	//z: Stack Req. = 48 *4 = 192bytes

	double fr[6];
	//int ii,jj,sv,svu;		//z_ajit
	//int32_t dumyval[10];		//z_ajit
	double fL5 = 1176450000.0;
	//char mytext3[200];		//z_ajit
	double PRn[6];
	double alpha[6][4];	//z_debug
	int i,j,k;
	//int c;	//z_ajit

	//z_debug
	//double alpha[6][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};

	double val,ans;			//z_ajit
	int addr_val, addr_ans;		//z_ajit

	double dopf[6];
	dopf[0]=-187566; ///doubtful-187566
	dopf[1]= 10169;
	dopf[2]=-354778;
	dopf[3]=-107718;
	dopf[4]=-20269;
	dopf[5]=-3903; ///doubtful

	for (i=0; i< 4; i++){
		// The Satellite Number is saved in the  Nav_Valid_Buf_Id[i] variable
		j = NavprocData.Nav_Valid_Buf_Id[i];
		//for(j=0;j<4;j++)
		//{
		PRINTF("\n J= %d",j);
		PRn[j]=(pow(NavprocData.UserPos_XYZ[0]-NavprocData.SatPositionECEF[j][0],2))+(pow(NavprocData.UserPos_XYZ[1]-NavprocData.SatPositionECEF[j][1],2))+(pow(NavprocData.UserPos_XYZ[2]-NavprocData.SatPositionECEF[j][2],2));
		//PRn[j]=pow(PRn[j],0.5) ;
		#ifdef AJIT
		val = PRn[j];
		addr_val = (uint32_t) &val;	//memory address location 
		addr_ans = (uint32_t) &ans;
		sqrt_ajit_asm_double(addr_val, addr_ans);
		PRn[j] = ans;
		#else
		PRn[j] = sqrt(PRn[j]);
		#endif

	}

	for (k=0; k< 4; k++)//for(i=0;i<4;i++)
	{  
		i = NavprocData.Nav_Valid_Buf_Id[k];
		for(j=0;j<3;j++)
		{
			alpha[i][j]= (NavprocData.UserPos_XYZ[j] -NavprocData.SatPositionECEF[i][j] ) / (PRn[i]);

		}

	}

	for (i=0; i< 4; i++)//for(j=0;j<4;j++)
	{
		j = NavprocData.Nav_Valid_Buf_Id[i];
		alpha[j][3]=C;
	}


	double rr[6][1];
	for(i=0;i<4;i++)
	{
		fr[i]=fL5+(dopf[i]/1000);
		rr[i][0]= C*(1-(fr[i]/fL5));
	}

	double vnew[6][1],rhodot[6][1],Vuser[6][1];
	//double alphainv[4][4];		//z_ajit
	double alphaT[4][6],alphasq[4][4],alphasqinv[4][4],alphamat[4][6];	//z_debug

	//z_debug : Array initialization
	/*
	double alphaT[4][6] = {{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0}};
	double alphasq[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
	double alphasqinv[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
	double alphamat[4][6] = {{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0}};
	*/

	double I1[3][1],I2[3][1],I3[3][1],I4[3][1],I5[3][1],I6[3][1];

	double V1[1][3],V2[1][3],V3[1][3],V4[1][3],V5[1][3],V6[1][3];

	for(i=0;i<3;i++)
	{
		V1[0][i]=NavprocData.SatVelocity[0][i];
		V2[0][i]=NavprocData.SatVelocity[1][i];
		V3[0][i]=NavprocData.SatVelocity[2][i];
		V4[0][i]=NavprocData.SatVelocity[3][i];
		V5[0][i]=NavprocData.SatVelocity[4][i];
		V6[0][i]=NavprocData.SatVelocity[5][i];
	}

	double v1[1][1],v2[1][1],v3[1][1],v4[1][1],v5[1][1],v6[1][1];

	for(i=0;i<3;i++)
	{
		I1[i][0]=-1 * alpha[0][i];
		I2[i][0]=-1 * alpha[1][i];
		I3[i][0]=-1 * alpha[2][i];
		I4[i][0]=-1 * alpha[3][i];
		I5[i][0]=-1 * alpha[4][i];
		I6[i][0]=-1 * alpha[5][i];
	}

	MatMultiplication1331(1,3,3,1,V1,I1,v1);	//z_debug checked
	MatMultiplication1331(1,3,3,1,V2,I2,v2);
	MatMultiplication1331(1,3,3,1,V3,I3,v3);
	MatMultiplication1331(1,3,3,1,V4,I4,v4);
	MatMultiplication1331(1,3,3,1,V5,I5,v6);
	MatMultiplication1331(1,3,3,1,V6,I6,v6);

	vnew[0][0] = v1[0][0];
	vnew[1][0] = v2[0][0];
	vnew[2][0] = v3[0][0];
	vnew[3][0] = v4[0][0];
	vnew[4][0] = v5[0][0];
	vnew[5][0] = v6[0][0];

	for(i=0;i<4;i++)
	{
		rhodot[i][0]=rr[i][0]-vnew[i][0];

	}

	//CompTranspose(4,4,alpha, alphaT);			//z_debug
	CompTranspose64(6,4,alpha, alphaT);	
	//MatMultiplication(4,4,4,4,alphaT,alpha,alphasq);	//z_debug
	MatMultiplication46x4(4,6,4,4,alphaT,alpha,alphasq);

	FindMatrixInverse(4,alphasq,alphasqinv);
	
	//MatMultiplication(4,4,4,4,alphasqinv,alphaT,alphamat);	//z_debug
	MatMultiplication4446(4,4,4,6,alphasqinv,alphaT,alphamat);

	//MatMultiplication(4,4,4,1,alphamat,rhodot,Vuser);		//z_debug
	MatMultiplication46x1(4,6,4,1,alphamat,rhodot,Vuser);		

	//inverse(4,alpha,alphainv);
	//mult(4,4,4,1,alphainv,rhodot,Vuser);



}

//!***************Print_Process_Data() Start*************
//******************************************************************//
void Print_Process_Data()
{
	int s,c,l,sv,Sat_No;
	PRINTF("================Satellite Position====================\n");
	for(s=0;s<NavprocData.Valid_NavICSat_Count;s++)		//z: Valid_NavICSat_Count : no. of satellites whose valid data is available  
	{
		Sat_No = NavprocData.Nav_Valid_Buf_Id[s];
		for(c=0;c<3;c++)
		{
			PRINTF("\nSatPos[%d][%d]=%0.10f\n",s,c,NavprocData.SatPositionECEF[Sat_No][c]);
		}
		PRINTF("\n");
	}
	PRINTF("\n\n================User Position====================\n");
	for(s=0;s<3;s++)
	{
		PRINTF("\nUserpos[%d]=%0.10f\n",s,NavprocData.UserPos_XYZ[s]);
	}
	PRINTF("\n\nUserPosition_Lat= %0.10f\n",NavprocData.UserPosition_Lat);
	PRINTF("\nUserPosition_Long= %0.10f\n",NavprocData.UserPosition_Long);
	PRINTF("\nUserPosition_Ht= %0.10f\n",NavprocData.UserPosition_Ht);

	PRINTF("\n\n================SatAzEl Cooridinates====================\n\n");

	for(l=0;l<NavprocData.Valid_NavICSat_Count;l++)
	{
		Sat_No = NavprocData.Nav_Valid_Buf_Id[l];
		PRINTF("SatPosAz[%d][0]=%0.10f\t\n",l,NavprocData.SatPosAzEl_Deg[Sat_No][0]);
		PRINTF("SatPosEl[%d][1]=%0.10f\n",l,NavprocData.SatPosAzEl_Deg[Sat_No][1]);
	}
	PRINTF("\n\n================Satellite Velocity====================\n");	

	for(s=0;s<NavprocData.Valid_NavICSat_Count;s++)
	{
		Sat_No = NavprocData.Nav_Valid_Buf_Id[s];
		for(sv=0;sv<3;sv++)
		{
		    PRINTF("SatVel[%d][%d]=%0.10f\t\n",s,sv,NavprocData.SatVelocity[Sat_No][sv]);
		}
		PRINTF("\n");
	}
	PRINTF("\n\n======================DOP================================\n");
	PRINTF("\nGDOP=%0.10f\n",NavprocData.GDOP);
	PRINTF("\tPDOP=%0.10f\n",NavprocData.PDOP);
	PRINTF("\tHDOP=%0.10f\n",NavprocData.HDOP);
	PRINTF("\tVDOP=%0.10f\n",NavprocData.VDOP);
	PRINTF("\tTDOP=%0.10f\n",NavprocData.TDOP);

	PRINTF("\n\n======================Ionospheric Delay================================\n");
	PRINTF("\nSatIonosphericCorr=%0.10f\n",NavprocData.SatIonosphericCorr[NavprocData.Valid_NavICSat_Count]);

	PRINTF("\n\n======================FINDUTC================================\n");
	PRINTF("\nCurDay = %0.10f\tCurMonth = %0.10f\tUTC_Yr = %0.10f\n",NavprocData.UTC_Day,NavprocData.UTC_Mon,NavprocData.UTC_Yr);
	PRINTF("\nUTC_Hrs = %0.10f\tUTC_Mins = %0.10f\tUTC_Sec = %0.10f\tremday = %0.10f\n",NavprocData.UTC_Hrs,NavprocData.UTC_Mins,NavprocData.UTC_Sec,NavprocData.UTC_DayofYr);

	/*----------------------------
	//z: temp
	PRINTF("\n\n%s\n",GIGGAFrame);
	PRINTF("\n%s\n",GIGSAFrame);
	PRINTF("\n%s\n",GIGSVFrame);
	PRINTF("\n%s\n",GIRMCFrame);
	---------------------------------*/
}//End of Subroutine

