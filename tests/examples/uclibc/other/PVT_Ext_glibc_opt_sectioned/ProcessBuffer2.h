#ifndef datastructure
#define datastructure
#include <stdint.h>
#endif
//#define NAVSATNO 8	//orig
#define NAVSATNO 6	//z_gcc

///Data Structure to Save Subframe -1 Data of 7 Satellites

//z: Size =76bytes, Number= 7;
struct NavicSubFrame1
{
	double	af0;  	// Clock bias
	double	af1; 	// Clock drift
	double	af2; 	// Clock drift rate
	double	Toc;	// Time of clock
	double	Tgd; 	// Total group delay
	double	MD;	// Mean Motion Difference
	double	IODEC;  // Issue of Data Ephemeris & Clock
	double	Cuc; 	// Cosine Harmonic Correction Term Amplitude to Argument of Latitude
	double	Cus; 	// Sine Harmonic Correction Term Amp to the Argument of Latitude
	double	Cic; 	// Cosine Harmonic Correction Term Amp to the Angle of Inclination
	double	Cis; 	// Sine Harmonic Correction Term Amplitude to the Angle of Inclination
	double	Crc; 	// Cosine Harmonic Correction Term Amplitude to the Orbit Radius
	double	Crs ;	// Sine Harmonic Correction Term Amplitude to the Orbit Radius
	double	IDOT;	// Rate of Inclination angle
	int	Sflag;	// status of the s Band signals
	int	L5flag; // status of the L5 Band signals
	// New
	int	Autonav; // Auto Nav
	int	Alert;	// Alert Flag
	int	URA;    // user range accuracy
	int	WN;     // Week Number
	int	TOWC1;  // Time of week count
}NavSubFrame1Data[NAVSATNO],temp_frame1;

///Data Structure to Save Subframe -2 Data of 7 Satellites

//z: Size = 44bytes, Number=7
struct NavicSubFrame2
{
	double	Mo;	        // Mean Anomaly
	double	Toe; 		// Time of ephemeris
	double	e;  		// Eccentricity
	double	A;  		// Square root of Semi major axis
	double	Omega;	    	// Long of Ascending Node
	double	w;   		// Argument of perigee
	double	OmegaDot;	// Rate of RAAN
	double	Io;    		// Inclination
	int	TOWC2;	    	// Time of week count
	// New
	int	Alert;		// Alert Flag
	int	AutoNav; 	// Auto Navigation

}NavSubFrame2Data[NAVSATNO],temp_frame2 ;

//z: Size = 28bytes, Number =7;
struct NavicSubFrame3Frame4
{
	//uint8_t 	PRNID, MSGID,Alert34,Autonav34;	//orig
	uint32_t 	PRNID, MSGID,Alert34,Autonav34;	//z_gcc
	int 		TOWC34;
	int 		countutc;
	int16_t 	WN;

}NavSubFrame3_4Data[NAVSATNO],temp_frame3_4 ;

//z: Size = 60bytes, Number = 2;
struct NavMsgTypNine_TwentySix
{
	double	A0utc;  	// Bias coefficient of IRNSS time scale relative to UTC time scale
	double	A1utc; 		// Drift coefficient of IRNSS time scale relative to UTC time scale
	double	A2utc; 		// Drift rate correction coefficient of IRNSS time scale relative to UTC time scale
	double	delTls; 	// Current or past leap second count
	double	Toutc; 		// Time data reference time of week
	double	WNoutc;		// Time data reference week number
	double	WNlsf; 		// Leap second reference week number
	double	DN; 		// Leap second reference day number
	double	delTlsf; 	// Current or future leap second count

	// IRNSS time can be related to GPS using the IRNSS time offsets with respect to following GPS parameters

	double	A0; 		// Bias coefficient of IRNSS time scale relative to GPS time scale
	double	A1; 		// Drift coefficient of IRNSS time scale relative to GPS time scale
	double	A2;		// Drift rate correction coefficient of IRNSS time scale relative of GPS time scale
	double	Tot;		// Time data reference time of week
	double	WNot; 		// Time data reference week number
	//uint8_t	GNSSID;     	// GNSS ID for GPS is 0		//orig
	uint32_t	GNSSID;     	// GNSS ID for GPS is 0		//z_gcc
}NavUTCCorr,temp_UTCCorr;

//z: Size = 32bytes, Number = 2;
struct NavMsgTypEleven
{
	//4 Alpha Coefficients (αn; n=0,1,2,3)
	double	alpha0;
	double	alpha1;
	double	alpha2;
	double	alpha3;
	//4 Beta Coefficients (βn; n=0,1,2,3)
	double	beta0;
	double	beta1;
	double	beta2;
	double	beta3;
}NavIonoCorrction,temp_Iono_Corr;


// Observables Data structure

//z: Size = 72bytes, Number = 2;
struct	NavObservedData
{

	double	ObsPseudorange[NAVSATNO];	// Observed Pseudorange Values
	double	ObsDoppler[NAVSATNO];		// Observed Doppler Values
	double	ObsCNR[NAVSATNO];		// Observed CNR values


}NavObsDat, temp_NavObsDat;


//z: Size = 60bytes, Number = 7;
struct NavProcessedData
{
	// Towc Parameters
	double	TOWC, CorTOWC[NAVSATNO];
	double	CorrPseudorange[NAVSATNO];
	double	Corr1Pseudorange[NAVSATNO];
	int	UTCAbsFlg;
	// Towc Parameters

	// Indian Standard Time
	int	IST_Day, IST_DayofYr, IST_Mon, IST_Yr;
	int	IST_Hrs, IST_Mins, IST_Sec;
	// Valid Navigation Satellite  Data Available
	int	Valid_NavICSat_Count;		//z: No. of satellite with valid data available 
	int	Nav_Valid_Buf_Id[NAVSATNO];
	//Satellite Coordinates Data
	double	SatPositionECEF[NAVSATNO][3];	//z: changed size
	double	SatPosAzEl_Deg[NAVSATNO][2];
	// Satellite Velocity Data
	double	SatVelocity[NAVSATNO][3];
	// Ionospheric and Tropospheric Correction
	double	SatIonosphericCorr[NAVSATNO];
	double	SatTroposphericCorr[NAVSATNO];
	// User Position
	double	UserPos_XYZ[3];
	double	UserPosition_Long;
	double	UserPosition_Lat;
	double	UserPosition_Ht;
	char	RX_Lat_Dir;
	char	Rx_Lon_Dir;

	// User Dilution of Precision
	double	GDOP, PDOP, HDOP, VDOP, TDOP;

	// User - Satellite Geometric Distance
	double	UserSatRange[NAVSATNO];
	// User - Satellite Geometric Distance
	double	Geo_UserSat_Range[NAVSATNO];
	double	UserSatPseudoRange[NAVSATNO];

	// User Velocity
	double	UserVelocity[3];

	double   UTC_Day;
	double   UTC_DayofYr;
	double   UTC_Mon;
	double   UTC_Yr;

	double	UTC_Hrs;
	double   UTC_Mins;
	double   UTC_Sec;

	// Newly added
	double   geoid;
	int     ThreeDFix;
	char    SigStatus;
	int     No_of_sentences_data;
	int     sentence_no;
	int     Sat_PRN_no;
	int     SNR;
	int     Speed_knots;
	int     Track_angle;

}NavprocData,NavprocData1[NAVSATNO];

//z: Size = 150bytes, Number = 1;
struct Temp
{
	int TOW;
	int NavCorrectedTOWC;
	double delTime;
}temp;

//////////////////
//z: Size = 124bytes, Number = 1;
struct NavNMEAData
{
	/// GPGGA Sentence
	int	UTC_Hr;     		//UTC  Time
	int	UTC_Min;   		//UTC  Time
	int	UTC_Sec;    		//UTC  Time
	double 	Rx_Lat;                 //Latitude
	char	RX_Lat_Dir;             //N Or S
	double	Rx_Lon;                 //Longitude
	char	Rx_Lon_Dir;             //E Or W
	int	Rx_QC_Id;    		///Not getting               //GPS Quality indicator (0= No fix, 1=GPS fix)
	int	No_Sat_Used;            //Number Of Satellites Used
	double   HDOP;
	double   Altitude;       	///Not getting
	double   Ht_of_geoid;    	///Not getting
	//(empty field) time in seconds since last DGPS update;
	//(empty field) DGPS station ID number;

	/// GPGSA Sentence
	char    Auto_selection_of_2D_or_3D_fix;     ///Not getting
	int     ThreeD_fix_values;                  ///Not getting
	int     PRNs_of_satellites_used_for_fix;    ///Not getting
	double   PDOP;
	double   VDOP;

	/// GPGSV Sentence
	int     Number_of_sentences_for_full_data;  	///Not getting
	int     sentence_1_of_2;                    	///Not getting
	//int     Number_of_satellites_in_view;       ///Not getting
	int     Satellite_PRN_number1,Satellite_PRN_number2;
	double   Elevation_degrees;
	double   Azimuth_degrees;
	int     SNR;                               	///Not getting

	/// GPRMC Sentence
	char    Data_Status;                        	///Not getting    //A=active or V=void /Navigation Receiver warning
	double   Speed_over_the_ground_in_knots;     	///Not getting
	double   Track_angle_in_degrees_True;        	///Not getting
	int     day;            			//Date
	int     month;          			//Date
	int     year;           			//Date
	double   Magnetic_Variation;                 	///Not getting
	// double	Rx_Ht_AMSL;                 //Antenna Height AMSL

}NavNMEAdata;
