
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<tgmath.h>
#include<unistd.h>
#include<stdint.h>
#include "ProcessBuffer2.h"
#include "math_func.h"

#ifdef AJIT
#include "fpop.h"
#endif

#define BUFFERSIZE 1024

#define	s33 xx__pow_opt(2,-33,0)
#define	s19 xx__pow_opt(2,-19,0)
#define	s41 xx__pow_opt(2,-41,0)

#define	s31 xx__pow_opt(2,-31,0)
#define	s43 xx__pow_opt(2,-43,0)
#define	s4  xx__pow_opt(2,-4,0)
#define	s28 xx__pow_opt(2,-28,0)
#define	s55 xx__pow_opt(2,-55,0)

#define	s24 xx__pow_opt(2,-24,0)	
#define	s30 xx__pow_opt(2,-30,0)
#define	s27 xx__pow_opt(2,-27,0)
#define	sp11 xx__pow_opt(2,11,0)
#define	sp14 xx__pow_opt(2,14,0)
#define	sp16 xx__pow_opt(2,16,0)

#define	s35 xx__pow_opt(2,-35,0)
#define	s51 xx__pow_opt(2,-51,0)
#define	s68 xx__pow_opt(2,-68,0)

#define pi 3.141592653589
#define ee 1/298.257223563
#define re 6378137
#define C 299792458
#define ht 350
#define gamma 4.4870291115
#define NAVSATNO 6

///---Process 1 Data Structure---///
///--Raw Frame1 and Frame 2 L5 Data---///

struct navRawFrame
{
	char frame1[601];
	char frame2[601];
	char frame3[601];
	char frame4[601];
};

struct preambleMatchedFound
{
	int32_t buff;
	uint8_t pre;
	uint8_t pos;
	uint8_t ct;
	uint8_t ll;
	uint8_t ct2;
	int32_t deltime;
	int32_t dopf[6];
	uint8_t satnum;
};

///---Processed Frame1 and Frame 2 L5 Data---///
struct navProcessFrame
{
	int frame1[40];
	int frame2[40];
	int frame3[40];
	int frame4[40];
};

struct navProcessbitData
{
	uint8_t bit[300];
};



void NavExtractDataFrameOne(int IDecodedIP[37]);
void NavExtractDataFrameTwo(int IDecodedIP[37]);
void NavExtractDataFrameThreeFour(int IDecodedIP[37],int NavSatNo);
void NavExtractMsgNine(int IDecodedIP[37]);
void NavExtractMsgEleven(int IDecodedIP[37]);
void NavExtractMsgTwentySix(int IDecodedIP[37]);


void VerifyCopyFrameOneData(int NavSatNo);
void VerifyCopyFrameTwoData(int NavSatNo);
void VerifyCopyFrameThreeFourData(int NavSatNo);
int ReadandExtractData();




uint8_t NavIdentifyFrameID(int IDecodedIP[37]);
void NavExtractDataFrameMain(int IDecodedIP [37], int NavSatNo);		//z_gcc
void VerifyCopyFrameMessageTwentySix(int IDecodedIP [37], int NavSatNo);	//z_gcc


void VerifyCopyMesssgeNine();						//z_gcc
void VerifyCopyMessageEleven();						//z_gcc


/*
	This is the main routine to extract the decoded data from the stage -1 of the Process-1///
	1	The one-bit Health Flags: L5 flag and S flag indicate the health of NAV data on L5
		and S signals. If the Health Flag is SET then do not update data.
	2	If the Alert Flag. The Alert flag is SET then do not  update data
	3	If URA >= 4 then do not update data.
	4	IODEC

*/

// This is one of the important Parameters. The value of to this parameter will
// be assigned by the routine which will call the data extraction routine
// This variable is used to check if L5 or S Band Flag is Set before copying
// the data in the PVT data buffer.

int	DataBufFrqBand = 0; // L5 = 0 S = 1;

int IntNavframeData01[37]={139,15,210,131,125,98,73,59,252,180,0,69,182,191,0,11,15,1,255,207,217,122,219,192,1,0,27,85,147,247,247,241,209,187,114,76,0};
int IntNavframeData02[37]={139,15,211,11,179,166,86,236,91,104,4,133,1,127,43,170,153,239,50,195,68,198,14,137,3,99,255,90,209,79,249,125,114,1,166,136,0};
int IntNavframeData03[37]={139,15,211,144,117,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,11,222,240,92,0};
int IntNavframeData04[37]={139,15,212,24,125,244,72,204,84,96,83,254,44,0,67,43,170,195,50,151,182,15,209,219,92,245,137,137,127,160,128,0,10,49,84,192,0};

int IntNavframeData11[37]={139,15,210,131,125,155,124,180,2,16,2,133,229,255,64,8,2,172,248,3,143,126,206,64,38,0,21,16,222,209,107,243,83,160,58,200,0};
int IntNavframeData12[37]={139,15,211,10,170,193,231,104,94,92,4,47,13,67,43,172,166,54,188,165,190,48,1,55,47,27,255,166,64,40,62,101,146,183,169,76,0};
int IntNavframeData13[37]={139,15,211,144,5,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,12,55,190,120,0};
int IntNavframeData14[37]={139,15,212,24,5,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,15,169,22,28,16};

int IntNavframeData21[37]={139,15,210,131,125,15,193,192,1,172,0,5,182,191,64,11,65,1,255,207,241,185,220,255,229,128,1,99,226,0,95,230,225,41,48,60,0};
int IntNavframeData22[37]={139,15,211,8,91,48,161,152,91,104,4,48,239,255,43,174,126,215,51,43,77,146,8,33,170,19,255,76,33,79,235,50,35,36,181,252,16};
int IntNavframeData23[37]={139,15,211,144,80,25,116,29,161,45,7,232,71,66,63,255,255,254,128,52,5,160,29,3,232,35,64,154,6,208,32,0,18,31,8,84,16};
int IntNavframeData24[37]={139,15,212,24,177,81,129,219,252,249,210,41,252,159,43,95,246,252,66,253,130,232,112,81,250,8,204,45,254,4,0,0,18,101,202,116,0};

int IntNavframeData31[37]={139,15,210,131,125,116,54,112,6,8,0,69,229,255,192,13,127,172,248,15,194,27,168,191,234,128,17,73,199,241,80,2,128,149,224,56,0};
int IntNavframeData32[37]={139,15,211,10,145,14,197,200,94,92,3,165,193,155,43,166,51,129,51,181,217,137,245,12,31,219,255,52,81,66,180,154,34,66,89,224,0};
int IntNavframeData33[37]={139,15,211,144,80,25,116,29,161,45,7,232,71,66,63,255,255,254,128,52,5,160,29,3,232,35,64,154,6,208,32,0,20,6,59,184,0};
int IntNavframeData34[37]={139,15,212,24,177,81,129,219,252,249,210,41,252,159,43,95,246,252,66,253,130,232,112,81,250,8,204,45,254,4,0,0,20,124,249,152,0};

int IntNavframeData41[37]={139,15,210,131,125,1,62,215,247,8,0,5,182,191,0,4,176,1,255,194,122,59,208,0,28,255,198,61,90,142,95,251,176,152,235,28,16};
int IntNavframeData42[37]={139,15,211,11,187,212,246,80,91,104,4,54,68,215,43,174,68,94,225,232,61,166,22,225,180,219,255,224,48,53,118,60,2,167,229,116,0};
int IntNavframeData43[37]={139,15,211,144,80,24,52,129,132,60,36,97,55,10,56,86,194,230,153,180,211,166,236,26,224,231,7,182,65,178,48,0,24,66,89,8,0};
int IntNavframeData44[37]={139,15,212,24,80,24,112,149,133,44,43,105,115,76,56,46,193,125,140,236,107,99,171,32,225,31,9,120,77,210,112,0,25,120,63,224,0};

int IntNavframeData51[37]={139,15,210,131,125,78,204,84,9,148,0,5,182,191,64,8,76,1,255,194,248,123,98,64,7,0,47,67,72,174,127,245,82,231,248,240,0};
int IntNavframeData52[37]={139,15,211,8,24,185,86,180,91,104,0,128,74,23,43,171,13,98,229,81,220,74,203,1,85,47,255,160,96,54,81,200,98,56,175,32,0};
int IntNavframeData53[37]={139,15,211,144,80,25,116,29,161,45,7,232,71,66,63,255,255,254,128,52,5,160,29,3,232,35,64,154,6,208,32,0,30,45,111,140,16};
int IntNavframeData54[37]={139,15,212,24,177,81,129,219,252,249,210,41,252,159,43,95,246,252,66,253,130,232,112,81,250,8,204,45,254,4,0,0,30,87,173,172,0};

int ReadandExtractData()	//z_ajit
{

	int TOWC=0;

	// Read all the frames from file
	// First 4sub-frames for 6 satellites from sat0-sat5
	
	//z : temp
	//Read only 4 frame (4 subframe) from 1 satellite with 1 pseudorange (1sec)

	NavExtractDataFrameMain(IntNavframeData01,0);
	NavExtractDataFrameMain(IntNavframeData02,0);
	NavExtractDataFrameMain(IntNavframeData03,0);
	NavExtractDataFrameMain(IntNavframeData04,0);

	NavExtractDataFrameMain(IntNavframeData11,1);
	NavExtractDataFrameMain(IntNavframeData12,1);
	NavExtractDataFrameMain(IntNavframeData13,1);
	NavExtractDataFrameMain(IntNavframeData14,1);

	NavExtractDataFrameMain(IntNavframeData21,2);
	NavExtractDataFrameMain(IntNavframeData22,2);
	NavExtractDataFrameMain(IntNavframeData23,2);
	NavExtractDataFrameMain(IntNavframeData24,2);

	NavExtractDataFrameMain(IntNavframeData31,3);
	NavExtractDataFrameMain(IntNavframeData32,3);
	NavExtractDataFrameMain(IntNavframeData33,3);
	NavExtractDataFrameMain(IntNavframeData34,3);

	NavExtractDataFrameMain(IntNavframeData41,4);
	NavExtractDataFrameMain(IntNavframeData42,4);
	NavExtractDataFrameMain(IntNavframeData43,4);
	NavExtractDataFrameMain(IntNavframeData44,4);

	NavExtractDataFrameMain(IntNavframeData51,5);
	NavExtractDataFrameMain(IntNavframeData52,5);
	NavExtractDataFrameMain(IntNavframeData53,5);
	NavExtractDataFrameMain(IntNavframeData54,5);

	TOWC=97260;


	
	return TOWC;

}

void NavExtractDataFrameMain(int IDecodedIP[37], int NavSatNo)
{
	//z: Stack Req. = 37*4 +2 (Including arg. passed too)	
	//		= 150bytes
			
	uint8_t subFrameID=0;

	subFrameID=NavIdentifyFrameID(IDecodedIP);

	switch(subFrameID)
	{
		case 0: NavExtractDataFrameOne(IDecodedIP);
			VerifyCopyFrameOneData(NavSatNo);
			break;

		case 1: NavExtractDataFrameTwo(IDecodedIP);
			VerifyCopyFrameTwoData(NavSatNo);
			break;

		case 2: NavExtractDataFrameThreeFour(IDecodedIP,NavSatNo);
			break;

		case 3: NavExtractDataFrameThreeFour(IDecodedIP,NavSatNo);
			break;

		default: break;
	}
	return;
}

uint8_t NavIdentifyFrameID(int decoded[37])
{
	uint8_t sfID=0;
	sfID = (unsigned)((decoded[3]&0b00011000)>>3);
	return sfID;
}// End of the subroutine

//z: InitNav.. not called

//This routine initializes Frame 1 PVT  Buffer
void InitNavFrameOneParameters(int NavSatNo)
{
	NavSubFrame1Data[NavSatNo].WN =-500;
	NavSubFrame1Data[NavSatNo].af0=-500;
	NavSubFrame1Data[NavSatNo].af1=-500;
	NavSubFrame1Data[NavSatNo].af2=-500;
	NavSubFrame1Data[NavSatNo].URA=-500;
	NavSubFrame1Data[NavSatNo].Toc=-500;
	NavSubFrame1Data[NavSatNo].Tgd=-500;
	NavSubFrame1Data[NavSatNo].MD=-500;
	NavSubFrame1Data[NavSatNo].IODEC=-500;
	NavSubFrame1Data[NavSatNo].Cuc=-500;
	NavSubFrame1Data[NavSatNo].Cus=-500;
	NavSubFrame1Data[NavSatNo].Cic=-500;
	NavSubFrame1Data[NavSatNo].Cis=-500;
	NavSubFrame1Data[NavSatNo].Crc=-500;
	NavSubFrame1Data[NavSatNo].Crs=-500;
	NavSubFrame1Data[NavSatNo].IDOT=-500;
	NavSubFrame1Data[NavSatNo].TOWC1=-500;
	return;

}// End of the subroutine

void InitNavFrameTwoParameters(int NavSatNo)
{

	NavSubFrame2Data[NavSatNo].TOWC2=-500;
	NavSubFrame2Data[NavSatNo].Mo=-500;
	NavSubFrame2Data[NavSatNo].Toe=-500;
	NavSubFrame2Data[NavSatNo].e=-500;
	NavSubFrame2Data[NavSatNo].A=-500;
	NavSubFrame2Data[NavSatNo].Omega=-500;
	NavSubFrame2Data[NavSatNo].w=-500;
	NavSubFrame2Data[NavSatNo].OmegaDot=-500;
	NavSubFrame2Data[NavSatNo].Io=-500;
	return;

}

void InitNavFrameThreeAndFourParameters(int NavSatNo)
{
	NavSubFrame3_4Data[NavSatNo].PRNID=-500;
	NavSubFrame3_4Data[NavSatNo].MSGID=-500;
	NavSubFrame3_4Data[NavSatNo].Alert34=-500;
	NavSubFrame3_4Data[NavSatNo].Autonav34=-500;
	NavSubFrame3_4Data[NavSatNo].TOWC34=-500;
	NavSubFrame3_4Data[NavSatNo].countutc=-500;
	NavSubFrame3_4Data[NavSatNo].WN=-500;
	return ;

} // End of the subroutine

void InitNavMessageNineParameters ()
{

	///Initialization of bit corresponding Navigation Message Type Nine & TwentySix
	NavUTCCorr.A0utc=-500;
	NavUTCCorr.A1utc=-500;
	NavUTCCorr.A2utc=-500;
	NavUTCCorr.delTls=-500;
	NavUTCCorr.Toutc=-500;
	NavUTCCorr.WNoutc=-500;
	NavUTCCorr.WNlsf=-500;
	NavUTCCorr.DN=-500;
	NavUTCCorr.delTlsf=-500;
	NavUTCCorr.A0=-500;
	NavUTCCorr.A1=-500;
	NavUTCCorr.A2=-500;
	NavUTCCorr.Tot=-500;
	NavUTCCorr.WNot=-500;
	NavUTCCorr.GNSSID=-500;
} // End of the subroutine


void InitNavMessageElevenParameters ()
{
	///Initialization of bit corresponding NavMsgTypEleven
	NavIonoCorrction.alpha0=-500;
	NavIonoCorrction.alpha1=-500;
	NavIonoCorrction.alpha2=-500;
	NavIonoCorrction.alpha3=-500;
	NavIonoCorrction.beta0=-500;
	NavIonoCorrction.beta1=-500;
	NavIonoCorrction.beta2=-500;
	NavIonoCorrction.beta3=-500;
	return;

}  // End of the subroutine



// This subroutine will check the availability of the minimum data to compute only Receiver Position
void NavExtractDataFrameOne(int IDecodedIP [37])
{
	uint8_t i4,temp4;

	//uint8_t Alert1,Autonav1;

	temp_frame1.WN=0,temp_frame1.af0=0,temp_frame1.af1=0,temp_frame1.af2=0;
	temp_frame1.URA=0,temp_frame1.Toc=0,temp_frame1.Tgd=0,temp_frame1.MD=0;
	temp_frame1.IODEC=0,temp_frame1.Cuc=0,temp_frame1.Cus=0,temp_frame1.Cic=0;
	temp_frame1.Cis=0,temp_frame1.Crc=0,temp_frame1.Crs=0,temp_frame1.IDOT=0;
	temp_frame1.TOWC1=0;

	temp_frame1.Alert =0; temp_frame1.URA =0; temp_frame1.Sflag =0;	temp_frame1.L5flag =0;

	//Extracting  IDOT : Rate of Inclination angle

	IDecodedIP[32]=IDecodedIP[32]/(2^4);
	for(i4=0;i4<14;i4++)
	{
		if(i4<4)
		{
			//temp4=IDecodedIP[32]%2;             //z_debug	//z_debug
			temp4=IDecodedIP[32] & 0x1;
			temp_frame1.IDOT=temp4*xx__pow_opt(2,i4,0)+temp_frame1.IDOT;
			IDecodedIP[32]=IDecodedIP[32]/2;
		}

		else if((i4>=4)&&(i4<12))
		{
			//temp4=IDecodedIP[31]%2;             //z_debug
			temp4=IDecodedIP[31] & 0x1;
			temp_frame1.IDOT=temp4*xx__pow_opt(2,i4,0)+temp_frame1.IDOT;
			IDecodedIP[31]=IDecodedIP[31]/2;
		}

		else if(i4==12)
		{
			//temp4=IDecodedIP[30]%2;             //z_debug
			temp4=IDecodedIP[30] & 0x1;
			temp_frame1.IDOT=temp4*xx__pow_opt(2,i4,0)+temp_frame1.IDOT;
			IDecodedIP[30]=IDecodedIP[30]/2;
		}

		else if(i4==13)
		{
			//temp4=IDecodedIP[30]%2;             //z_debug
			temp4=IDecodedIP[30] & 0x1;
			temp_frame1.IDOT=temp4*xx__pow_opt(2,i4,0)*-1+temp_frame1.IDOT;
			IDecodedIP[30]=IDecodedIP[30]/2;
		}
	}

	temp_frame1.IDOT=temp_frame1.IDOT*s43*pi;

	// Extracting  IDOT :	Rate of Inclination angle

	for(i4=0;i4<15;i4++)
	{
		if(i4<6)
		{
			//temp4=IDecodedIP[30]%2;             //z_debug
			temp4=IDecodedIP[30] & 0x1;
			temp_frame1.Crs=temp4*xx__pow_opt(2,i4,0)+temp_frame1.Crs;
			IDecodedIP[30]=IDecodedIP[30]/2;
		}

		else if((i4>=6)&&(i4<14))
		{
			//temp4=IDecodedIP[29]%2;             //z_debug
			temp4=IDecodedIP[29] & 0x1;
			temp_frame1.Crs=temp4*xx__pow_opt(2,i4,0)+temp_frame1.Crs;
			IDecodedIP[29]=IDecodedIP[29]/2;
		}

		else if(i4==14)
		{
			//temp4=IDecodedIP[28]%2;
			temp4=IDecodedIP[28] & 0x1;
			temp_frame1.Crs=temp4*xx__pow_opt(2,i4,0)*-1+temp_frame1.Crs;
			IDecodedIP[28]=IDecodedIP[28]/2;
		}
	}
	temp_frame1.Crs=temp_frame1.Crs*s4;

	// Extracting   Crc : Cosine Harmonic Correction Term Amplitude to the Orbit Radius

	for(i4=0;i4<15;i4++)
	{
		if(i4<7)
		{
			//temp4=IDecodedIP[28]%2;
			temp4=IDecodedIP[28] & 0x1;
			temp_frame1.Crc=temp4*xx__pow_opt(2,i4,0)+temp_frame1.Crc;
			IDecodedIP[28]=IDecodedIP[28]/2;
		}

		else if((i4>=7)&&(i4<14))
		{
			//temp4=IDecodedIP[27]%2;
			temp4=IDecodedIP[27] & 0x1;
			temp_frame1.Crc=temp4*xx__pow_opt(2,i4,0)+temp_frame1.Crc;
			IDecodedIP[27]=IDecodedIP[27]/2;
		}

		else if(i4==14)
		{
			//temp4=IDecodedIP[27]%2;
			temp4=IDecodedIP[27] & 0x1;
			temp_frame1.Crc=temp4*xx__pow_opt(2,i4,0)*-1+temp_frame1.Crc;
			IDecodedIP[27]=IDecodedIP[27]/2;
		}
	}
	temp_frame1.Crc=temp_frame1.Crc*s4;

	// Extracting  Cis : Sine Harmonic Correction Term Amplitude to the Angle of Inclination

	for(i4=0;i4<15;i4++)
	{
		if(i4<8)
		{
			//temp4=IDecodedIP[26]%2;
			temp4=IDecodedIP[26] & 0x1;
			temp_frame1.Cis=temp4*xx__pow_opt(2,i4,0)+temp_frame1.Cis;
			IDecodedIP[26]=IDecodedIP[26]/2;
		}

		else if((i4>=8)&&(i4<14))
		{
			//temp4=IDecodedIP[25]%2;
			temp4=IDecodedIP[25] & 0x1;
			temp_frame1.Cis=temp4*xx__pow_opt(2,i4,0)+temp_frame1.Cis;
			IDecodedIP[25]=IDecodedIP[25]/2;
		}

		else if(i4==14)
		{
			//temp4=IDecodedIP[25]%2;
			temp4=IDecodedIP[25] & 0x1;
			temp_frame1.Cis=temp4*xx__pow_opt(2,i4,0)*-1+temp_frame1.Cis;
			IDecodedIP[25]=IDecodedIP[25]/2;
		}
	}
	temp_frame1.Cis=temp_frame1.Cis*s28;

	// Extracting  Cic :Cosine Harmonic Correction TermAmp to the Angle of Inclination

	for(i4=0;i4<15;i4++)
	{
		if(i4<1)
		{
			//temp4=IDecodedIP[25]%2;
			temp4=IDecodedIP[25] & 0x1;
			temp_frame1.Cic=temp4*xx__pow_opt(2,i4,0)+temp_frame1.Cic;
			IDecodedIP[25]=IDecodedIP[25]/2;
		}

		else if((i4>=1)&&(i4<9))
		{
			//temp4=IDecodedIP[24]%2;
			temp4=IDecodedIP[24] & 0x1;
			temp_frame1.Cic=temp4*xx__pow_opt(2,i4,0)+temp_frame1.Cic;
			IDecodedIP[24]=IDecodedIP[24]/2;
		}

		else if((i4>=9)&&(i4<14))
		{
			//temp4=IDecodedIP[23]%2;
			temp4=IDecodedIP[23] & 0x1;
			temp_frame1.Cic=temp4*xx__pow_opt(2,i4,0)+temp_frame1.Cic;
			IDecodedIP[23]=IDecodedIP[23]/2;
		}

		else if(i4==14)
		{
			//temp4=IDecodedIP[23]%2;
			temp4=IDecodedIP[23] & 0x1;
			temp_frame1.Cic=temp4*xx__pow_opt(2,i4,0)*-1+temp_frame1.Cic;
			IDecodedIP[23]=IDecodedIP[23]/2;
		}
	}
	temp_frame1.Cic=temp_frame1.Cic*s28;

	// Extracting   	Cus :	Sine Harmonic Correction Term Ampto the Argument of Latitude

	for(i4=0;i4<15;i4++)
	{
		if(i4<=1)
		{
			//temp4=IDecodedIP[23]%2;
			temp4=IDecodedIP[23] & 0x1;
			temp_frame1.Cus=temp4*xx__pow_opt(2,i4,0)+temp_frame1.Cus;
			IDecodedIP[23]=IDecodedIP[23]/2;
		}

		else if((i4>1)&&(i4<10))
		{
			//temp4=IDecodedIP[22]%2;
			temp4=IDecodedIP[22] & 0x1;
			temp_frame1.Cus=temp4*xx__pow_opt(2,i4,0)+temp_frame1.Cus;
			IDecodedIP[22]=IDecodedIP[22]/2;
		}

		else if((i4>=10)&&(i4<14))
		{
			//temp4=IDecodedIP[21]%2;
			temp4=IDecodedIP[21] & 0x1;			
			temp_frame1.Cus=temp4*xx__pow_opt(2,i4,0)+temp_frame1.Cus;
			IDecodedIP[21]=IDecodedIP[21]/2;
		}

		else if(i4==14)
		{
			//temp4=IDecodedIP[21]%2;
			temp4=IDecodedIP[21] & 0x1;
			temp_frame1.Cus=temp4*xx__pow_opt(2,i4,0)*-1+temp_frame1.Cus;
			IDecodedIP[21]=IDecodedIP[21]/2;
		}
	}
	temp_frame1.Cus=temp_frame1.Cus*s28;

	// Extracting  Cuc :	Cosine Harmonic Correction Term Amplitude to Argument of Latitude

	for(i4=0;i4<15;i4++)
	{
		if(i4<3)
		{
			//temp4=IDecodedIP[21]%2;
			temp4=IDecodedIP[21] & 0x1;
			temp_frame1.Cuc=temp4*xx__pow_opt(2,i4,0)+temp_frame1.Cuc;
			IDecodedIP[21]=IDecodedIP[21]/2;
		}

		else if((i4>=3)&&(i4<11))
		{
			//temp4=IDecodedIP[20]%2;
			temp4=IDecodedIP[20] & 0x1;

			temp_frame1.Cuc=temp4*xx__pow_opt(2,i4,0)+temp_frame1.Cuc;
			IDecodedIP[20]=IDecodedIP[20]/2;
		}

		else if((i4>=11)&&(i4<14))
		{
			//temp4=IDecodedIP[19]%2;
			temp4=IDecodedIP[19] & 0x1;
			temp_frame1.Cuc=temp4*xx__pow_opt(2,i4,0)+temp_frame1.Cuc;
			IDecodedIP[19]=IDecodedIP[19]/2;
		}

		else if(i4==14)
		{
			//temp4=IDecodedIP[19]%2;
			temp4=IDecodedIP[19] & 0x1;
			temp_frame1.Cuc=temp4*xx__pow_opt(2,i4,0)*-1+temp_frame1.Cuc;
			IDecodedIP[19]=IDecodedIP[19]/2;
		}
	}

	temp_frame1.Cuc=temp_frame1.Cuc*s28;

	// Extracting S & L5 Band Status Flag

	for(i4=0;i4<2;i4++)
	{
		if(i4<1)
		{
			temp4=IDecodedIP[19]& 0x1;             //z_debug
			temp_frame1.Sflag=temp4;
			IDecodedIP[19]=IDecodedIP[19]/2;
		}

		else if(i4==1)
		{
			temp4=IDecodedIP[19]& 0x1;             //z_debug
			temp_frame1.L5flag=temp4;
			IDecodedIP[19]=IDecodedIP[19]/2;
		}
	}
	// Extracting IODEC : Issue of Data Ephemeris & Clock

	for(i4=0;i4<8;i4++)
	{

		temp4=IDecodedIP[17]& 0x1;             //z_debug
		temp_frame1.IODEC=temp4*xx__pow_opt(2,i4,0)+temp_frame1.IODEC;
		IDecodedIP[17]=IDecodedIP[17]/2;
	}

	// Extracting MD :Mean Motion Difference

	for(i4=0;i4<22;i4++)
	{
		if(i4<8)
		{
			temp4=IDecodedIP[16]& 0x1;             //z_debug
			temp_frame1.MD=temp4*xx__pow_opt(2,i4,0)+temp_frame1.MD;
			IDecodedIP[16]=IDecodedIP[16]/2;
		}

		else if((i4>=8)&&(i4<16))
		{
			temp4=IDecodedIP[15]& 0x1;             //z_debug
			temp_frame1.MD=temp4*xx__pow_opt(2,i4,0)+temp_frame1.MD;
			IDecodedIP[15]=IDecodedIP[15]/2;
		}

		else if((i4>=16)&&(i4<21))
		{
			temp4=IDecodedIP[14]& 0x1;             //z_debug
			temp_frame1.MD=temp4*xx__pow_opt(2,i4,0)+temp_frame1.MD;
			IDecodedIP[14]=IDecodedIP[14]/2;
		}

		else if(i4==21)
		{
			temp4=IDecodedIP[14]& 0x1;             //z_debug
			temp_frame1.MD=temp4*xx__pow_opt(2,i4,0)*-1+temp_frame1.MD;
			IDecodedIP[14]=IDecodedIP[14]/2;
		}
	}
	temp_frame1.MD=temp_frame1.MD*s41*pi;

	// Extracting Tgd: Total group delay
	for(i4=0;i4<8;i4++)
	{
		if(i4<2)
		{
			temp4=IDecodedIP[14]& 0x1;             //z_debug
			temp_frame1.Tgd=temp4*xx__pow_opt(2,i4,0)+temp_frame1.Tgd;
			IDecodedIP[14]=IDecodedIP[14]/2;
		}

		else if((i4>=2)&&(i4<7))
		{
			temp4=IDecodedIP[13]& 0x1;             //z_debug
			temp_frame1.Tgd=temp4*xx__pow_opt(2,i4,0)+temp_frame1.Tgd;
			IDecodedIP[13]=IDecodedIP[13]/2;
		}

		else if(i4==7)
		{
			temp4=IDecodedIP[13]& 0x1;             //z_debug
			temp_frame1.Tgd=temp4*xx__pow_opt(2,i4,0)*-1+temp_frame1.Tgd;
			IDecodedIP[13]=IDecodedIP[13]/2;
		}
	}
	temp_frame1.Tgd=temp_frame1.Tgd*s31;

	// Extracting Toc : Time of clock

	for(i4=0;i4<16;i4++)
	{
		if(i4<2)
		{
			temp4=IDecodedIP[13]& 0x1;             //z_debug
			temp_frame1.Toc=temp4*xx__pow_opt(2,i4,0)+temp_frame1.Toc;
			IDecodedIP[13]=IDecodedIP[13]/2;
		}

		else if((i4>=2)&&(i4<10))
		{
			temp4=IDecodedIP[12]& 0x1;             //z_debug
			temp_frame1.Toc=temp4*xx__pow_opt(2,i4,0)+temp_frame1.Toc;
			IDecodedIP[12]=IDecodedIP[12]/2;
		}

		else if(i4>=10)
		{
			temp4=IDecodedIP[11]& 0x1;             //z_debug
			temp_frame1.Toc=temp4*xx__pow_opt(2,i4,0)+temp_frame1.Toc;
			IDecodedIP[11]=IDecodedIP[11]/2;
		}
	}

	temp_frame1.Toc=temp_frame1.Toc*16;

	// Extracting URA :  User Range Accuracy

	for(i4=0;i4<4;i4++)
	{
		if(i4<2)
		{
			temp4=IDecodedIP[11]& 0x1;             //z_debug
			temp_frame1.URA=temp4*xx__pow_opt(2,i4,0)+temp_frame1.URA;
			IDecodedIP[11]=IDecodedIP[11]/2;
		}

		else if(i4>=2)
		{
			temp4=IDecodedIP[10]& 0x1;             //z_debug
			temp_frame1.URA=temp4*xx__pow_opt(2,i4,0)+temp_frame1.URA;
			IDecodedIP[10]=IDecodedIP[10]/2;
		}
	}

	// Extracting 	af2 :	Clock drift rate

	for(i4=0;i4<8;i4++)
	{
		if(i4<6)
		{
			temp4=IDecodedIP[10]& 0x1;             //z_debug
			temp_frame1.af2=temp4*xx__pow_opt(2,i4,0)+temp_frame1.af2;
			IDecodedIP[10]=IDecodedIP[10]/2;
		}

		else if(i4==6)
		{
			temp4=IDecodedIP[9]& 0x1;             //z_debug
			temp_frame1.af2=temp4*xx__pow_opt(2,i4,0)+temp_frame1.af2;
			IDecodedIP[9]=IDecodedIP[9]/2;
		}

		else if(i4==7)
		{
			temp4=IDecodedIP[9]& 0x1;             //z_debug
			temp_frame1.af2=temp4*xx__pow_opt(2,i4,0)*-1+temp_frame1.af2;
			IDecodedIP[9]=IDecodedIP[9]/2;
		}
	}
	temp_frame1.af2=temp_frame1.af2*s55;

	// Extracting  	af1 :Clock drift
	for(i4=0;i4<16;i4++)
	{
		if(i4<6)
		{
			temp4=IDecodedIP[9]& 0x1;             //z_debug
			temp_frame1.af1=temp4*xx__pow_opt(2,i4,0)+temp_frame1.af1;
			IDecodedIP[9]=IDecodedIP[9]/2;
		}

		if((i4>=6)&&(i4<14))
		{
			temp4=IDecodedIP[8]& 0x1;             //z_debug
			temp_frame1.af1=temp4*xx__pow_opt(2,i4,0)+temp_frame1.af1;
			IDecodedIP[8]=IDecodedIP[8]/2;
		}

		else if(i4==14)
		{
			temp4=IDecodedIP[7]& 0x1;             //z_debug
			temp_frame1.af1=temp4*xx__pow_opt(2,i4,0)+temp_frame1.af1;
			IDecodedIP[7]=IDecodedIP[7]/2;
		}

		else if(i4==15)
		{
			temp4=IDecodedIP[7]& 0x1;             //z_debug
			temp_frame1.af1=temp4*xx__pow_opt(2,i4,0)*-1+temp_frame1.af1;
			IDecodedIP[7]=IDecodedIP[7]/2;
		}
	}
	temp_frame1.af1=temp_frame1.af1*s43;

	// Extracting  	af0 :	Clock bias

	for(i4=0;i4<22;i4++)
	{
		if(i4<6)
		{
			temp4=IDecodedIP[7]& 0x1;             //z_debug
			temp_frame1.af0=temp4*xx__pow_opt(2,i4,0)+temp_frame1.af0;
			IDecodedIP[7]=IDecodedIP[7]/2;
		}

		if((i4>=6)&&(i4<14))
		{
			temp4=IDecodedIP[6]& 0x1;             //z_debug
			temp_frame1.af0=temp4*xx__pow_opt(2,i4,0)+temp_frame1.af0;
			IDecodedIP[6]=IDecodedIP[6]/2;
		}
		else if((i4>=14)&&(i4<21))
		{
			temp4=IDecodedIP[5]& 0x1;             //z_debug
			temp_frame1.af0=temp4*xx__pow_opt(2,i4,0)+temp_frame1.af0;
			IDecodedIP[5]=IDecodedIP[5]/2;
		}

		else if(i4==21)
		{
			temp4=IDecodedIP[5]& 0x1;             //z_debug
			temp_frame1.af0=temp4*xx__pow_opt(2,i4,0)*-1+temp_frame1.af0;
			IDecodedIP[5]=IDecodedIP[5]/2;
		}
	}
	temp_frame1.af0=temp_frame1.af0*s31;

	// Extracting  	WN   Week Number

	for(i4=0;i4<10;i4++)
	{
		if(i4<8)
		{
			temp4=IDecodedIP[4]& 0x1;             //z_debug
			temp_frame1.WN=temp4*xx__pow_opt(2,i4,0)+temp_frame1.WN;
			IDecodedIP[4]=IDecodedIP[4]/2;
		}

		else if(i4>=8)
		{
			temp4=IDecodedIP[3]& 0x1;             //z_debug
			temp_frame1.WN=temp4*xx__pow_opt(2,i4,0)+temp_frame1.WN;
			IDecodedIP[3]=IDecodedIP[3]/2;
		}
	}

	// Extracting  Autonav,  and Alert

	for(i4=0;i4<6;i4++)
	{
		if(i4<3)
			IDecodedIP[3]=IDecodedIP[3]/2;


		else if(i4==3)
		{
		temp_frame1.Autonav=IDecodedIP[3]& 0x1;             //z_debug
		IDecodedIP[3]=IDecodedIP[3]/2;
		}

		else if(i4==4)
		{
		temp_frame1.Alert=IDecodedIP[3]& 0x1;             //z_debug
		IDecodedIP[3]=IDecodedIP[3]/2;
		}
	}

	// Extracting  	TOWC
	for(i4=0;i4<17;i4++)
	{
		if(i4<1)
		{
		temp4=IDecodedIP[3]& 0x1;             //z_debug
		temp_frame1.TOWC1=temp4*xx__pow_opt(2,i4,0)+temp_frame1.TOWC1;
		IDecodedIP[3]=IDecodedIP[3]/2;
		}

		else if((i4>=1)&&(i4<9))
		{
		temp4=IDecodedIP[2]& 0x1;             //z_debug
		temp_frame1.TOWC1=temp4*xx__pow_opt(2,i4,0)+temp_frame1.TOWC1;
		IDecodedIP[2]=IDecodedIP[2]/2;
		}

		else if(i4>=9)
		{
		temp4=IDecodedIP[1]& 0x1;             //z_debug
		temp_frame1.TOWC1=temp4*xx__pow_opt(2,i4,0)+temp_frame1.TOWC1;
		IDecodedIP[1]=IDecodedIP[1]/2;
		}
	}

} // End of the Subroutine



void NavExtractDataFrameTwo(int IDecodedIP [37])
{
	uint8_t i4,temp4;

	//uint8_t Alert2,Autonav2;


	temp_frame2.TOWC2=0;
	temp_frame2.Mo=0,temp_frame2.Toe=0,temp_frame2.e=0,temp_frame2.A=0;
	temp_frame2.Omega=0,temp_frame2.w=0,temp_frame2.OmegaDot=0,temp_frame2.Io=0;

	temp_frame2.Alert =0;

	// Extracting Io : Inclination

	IDecodedIP[32]=IDecodedIP[32]/(2^4);

	for(i4=0;i4<32;i4++)
	{
		if(i4<4)
		{
			temp4=IDecodedIP[32]& 0x1;             //z_debug
			temp_frame2.Io=temp4*xx__pow_opt(2,i4,0)+temp_frame2.Io;
			IDecodedIP[32]=IDecodedIP[32]/2;
		}

		else if((i4>=4)&&(i4<12))
		{
			temp4=IDecodedIP[31]& 0x1;             //z_debug
			temp_frame2.Io=temp4*xx__pow_opt(2,i4,0)+temp_frame2.Io;
			IDecodedIP[31]=IDecodedIP[31]/2;
		}

		else if((i4>=12)&&(i4<20))
		{
			temp4=IDecodedIP[30]& 0x1;             //z_debug
			temp_frame2.Io=temp4*xx__pow_opt(2,i4,0)+temp_frame2.Io;
			IDecodedIP[30]=IDecodedIP[30]/2;
		}

		else if((i4>=20)&&(i4<28))
		{
			temp4=IDecodedIP[29]& 0x1;             //z_debug
			temp_frame2.Io=temp4*xx__pow_opt(2,i4,0)+temp_frame2.Io;
			IDecodedIP[29]=IDecodedIP[29]/2;
		}

		else if((i4>=28)&&(i4<31))
		{
			temp4=IDecodedIP[28]& 0x1;             //z_debug
			temp_frame2.Io=temp4*xx__pow_opt(2,i4,0)+temp_frame2.Io;
			IDecodedIP[28]=IDecodedIP[28]/2;
		}

		else if(i4==31)
		{
			temp4=IDecodedIP[28]& 0x1;             //z_debug
			temp_frame2.Io=temp4*xx__pow_opt(2,i4,0)*-1+temp_frame2.Io;
			IDecodedIP[28]=IDecodedIP[28]/2;
		}
	}
	temp_frame2.Io=temp_frame2.Io*s31*pi;

	// Extracting   OmegaDot :	Rate of RAAN

	for(i4=0;i4<22;i4++)
	{
		if(i4<4)
		{
			temp4=IDecodedIP[28]& 0x1;             //z_debug
			temp_frame2.OmegaDot=temp4*xx__pow_opt(2,i4,0)+temp_frame2.OmegaDot;
			IDecodedIP[28]=IDecodedIP[28]/2;
		}

		else if((i4>=4)&&(i4<12))
		{
			temp4=IDecodedIP[27]& 0x1;             //z_debug
			temp_frame2.OmegaDot=temp4*xx__pow_opt(2,i4,0)+temp_frame2.OmegaDot;
			IDecodedIP[27]=IDecodedIP[27]/2;
		}

		else if((i4>=12)&&(i4<20))
		{
			temp4=IDecodedIP[26]& 0x1;             //z_debug
			temp_frame2.OmegaDot=temp4*xx__pow_opt(2,i4,0)+temp_frame2.OmegaDot;
			IDecodedIP[26]=IDecodedIP[26]/2;
		}

		else if(i4==20)
		{
			temp4=IDecodedIP[25]& 0x1;             //z_debug
			temp_frame2.OmegaDot=temp4*xx__pow_opt(2,i4,0)+temp_frame2.OmegaDot;
			IDecodedIP[25]=IDecodedIP[25]/2;
		}

		else if(i4==21)
		{
			temp4=IDecodedIP[25]& 0x1;             //z_debug
			temp_frame2.OmegaDot=temp4*xx__pow_opt(2,i4,0)*-1+temp_frame2.OmegaDot;
			IDecodedIP[25]=IDecodedIP[25]/2;
		}
	}

	temp_frame2.OmegaDot=temp_frame2.OmegaDot*s41*pi;

	// Extracting   w : Argument of perigee

	for(i4=0;i4<32;i4++)
	{
		if(i4<6)
		{
			temp4=IDecodedIP[25]& 0x1;             //z_debug
			temp_frame2.w=temp4*xx__pow_opt(2,i4,0)+temp_frame2.w;
			IDecodedIP[25]=IDecodedIP[25]/2;
		}

		else if((i4>=6)&&(i4<14))
		{
			temp4=IDecodedIP[24]& 0x1;             //z_debug
			temp_frame2.w=temp4*xx__pow_opt(2,i4,0)+temp_frame2.w;
			IDecodedIP[24]=IDecodedIP[24]/2;
		}

		else if((i4>=14)&&(i4<22))
		{
			temp4=IDecodedIP[23]& 0x1;             //z_debug
			temp_frame2.w=temp4*xx__pow_opt(2,i4,0)+temp_frame2.w;
			IDecodedIP[23]=IDecodedIP[23]/2;
		}

		else if((i4>=22)&&(i4<30))
		{
			temp4=IDecodedIP[22]& 0x1;             //z_debug
			temp_frame2.w=temp4*xx__pow_opt(2,i4,0)+temp_frame2.w;
			IDecodedIP[22]=IDecodedIP[22]/2;
		}

		else if(i4==30)
		{
			temp4=IDecodedIP[21]& 0x1;             //z_debug
			temp_frame2.w=temp4*xx__pow_opt(2,i4,0)+temp_frame2.w;
			IDecodedIP[21]=IDecodedIP[21]/2;
		}

		else if(i4==31)
		{
			temp4=IDecodedIP[21]& 0x1;             //z_debug
			temp_frame2.w=temp4*xx__pow_opt(2,i4,0)*-1+temp_frame2.w;
			IDecodedIP[21]=IDecodedIP[21]/2;
		}
	}
	temp_frame2.w=temp_frame2.w*s31*pi;

    	// Extracting   Omega :Longitude of Ascending Node

	for(i4=0;i4<32;i4++)
	{
		if(i4<6)
		{
			temp4=IDecodedIP[21]& 0x1;             //z_debug
			temp_frame2.Omega=temp4*xx__pow_opt(2,i4,0)+temp_frame2.Omega;
			IDecodedIP[21]=IDecodedIP[21]/2;
		}

		else if((i4>=6)&&(i4<14))
		{
			temp4=IDecodedIP[20]& 0x1;             //z_debug
			temp_frame2.Omega=temp4*xx__pow_opt(2,i4,0)+temp_frame2.Omega;
			IDecodedIP[20]=IDecodedIP[20]/2;
		}

		else if((i4>=14)&&(i4<22))
		{
			temp4=IDecodedIP[19]& 0x1;             //z_debug
			temp_frame2.Omega=temp4*xx__pow_opt(2,i4,0)+temp_frame2.Omega;
			IDecodedIP[19]=IDecodedIP[19]/2;
		}

		else if((i4>=22)&&(i4<30))
		{
			temp4=IDecodedIP[18]& 0x1;             //z_debug
			temp_frame2.Omega=temp4*xx__pow_opt(2,i4,0)+temp_frame2.Omega;
			IDecodedIP[18]=IDecodedIP[18]/2;
		}

		else if(i4==30)
		{
			temp4=IDecodedIP[17]& 0x1;             //z_debug
			temp_frame2.Omega=temp4*xx__pow_opt(2,i4,0)+temp_frame2.Omega;
			IDecodedIP[17]=IDecodedIP[17]/2;
		}

		else if(i4==31)
		{
			temp4=IDecodedIP[17]& 0x1;             //z_debug
			temp_frame2.Omega=temp4*xx__pow_opt(2,i4,0)*-1+temp_frame2.Omega;
			IDecodedIP[17]=IDecodedIP[17]/2;
		}
	}

	temp_frame2.Omega=temp_frame2.Omega*s31*pi;

	// Extracting   A:Square root of Semi major axis

	for(i4=0;i4<32;i4++)
	{
		if(i4<6)
		{
			temp4=IDecodedIP[17]& 0x1;             //z_debug
			temp_frame2.A=temp4*xx__pow_opt(2,i4,0)+temp_frame2.A;
			IDecodedIP[17]=IDecodedIP[17]/2;
		}

		else if((i4>=6)&&(i4<14))
		{
			temp4=IDecodedIP[16]& 0x1;             //z_debug
			temp_frame2.A=temp4*xx__pow_opt(2,i4,0)+temp_frame2.A;
			IDecodedIP[16]=IDecodedIP[16]/2;
		}

		else if((i4>=14)&&(i4<22))
		{
			temp4=IDecodedIP[15]& 0x1;             //z_debug
			temp_frame2.A=temp4*xx__pow_opt(2,i4,0)+temp_frame2.A;
			IDecodedIP[15]=IDecodedIP[15]/2;
		}

		else if((i4>=22)&&(i4<30))
		{
			temp4=IDecodedIP[14]& 0x1;             //z_debug
			temp_frame2.A=temp4*xx__pow_opt(2,i4,0)+temp_frame2.A;
			IDecodedIP[14]=IDecodedIP[14]/2;
		}

		else if(i4>=30)
		{
			temp4=IDecodedIP[13]& 0x1;             //z_debug
			temp_frame2.A=temp4*xx__pow_opt(2,i4,0)+temp_frame2.A;
			IDecodedIP[13]=IDecodedIP[13]/2;
		}
	}
	temp_frame2.A=temp_frame2.A*s19;

	// Extracting e :  Eccentricity
	for(i4=0;i4<32;i4++)
	{
		if(i4<6)
		{
			temp4=IDecodedIP[13]& 0x1;             //z_debug
			temp_frame2.e=temp4*xx__pow_opt(2,i4,0)+temp_frame2.e;
			IDecodedIP[13]=IDecodedIP[13]/2;
		}

		else if((i4>=6)&&(i4<14))
		{
			temp4=IDecodedIP[12]& 0x1;             //z_debug
			temp_frame2.e=temp4*xx__pow_opt(2,i4,0)+temp_frame2.e;
			IDecodedIP[12]=IDecodedIP[12]/2;
		}

		else if((i4>=14)&&(i4<22))
		{
			temp4=IDecodedIP[11]& 0x1;             //z_debug
			temp_frame2.e=temp4*xx__pow_opt(2,i4,0)+temp_frame2.e;
			IDecodedIP[11]=IDecodedIP[11]/2;
		}

		else if((i4>=22)&&(i4<30))
		{
			temp4=IDecodedIP[10]& 0x1;             //z_debug
			temp_frame2.e=temp4*xx__pow_opt(2,i4,0)+temp_frame2.e;
			IDecodedIP[10]=IDecodedIP[10]/2;
		}

		else if(i4>=30)
		{
			temp4=IDecodedIP[9]& 0x1;             //z_debug
			temp_frame2.e=temp4*xx__pow_opt(2,i4,0)+temp_frame2.e;
			IDecodedIP[9]=IDecodedIP[9]/2;
		}
	}
	temp_frame2.e=temp_frame2.e*s33;

	// Extracting 	Toe	: Time of ephemeris
	for(i4=0;i4<16;i4++)
	{
		if(i4<6)
		{
			temp4=IDecodedIP[9]& 0x1;             //z_debug
			temp_frame2.Toe=temp4*xx__pow_opt(2,i4,0)+temp_frame2.Toe;
			IDecodedIP[9]=IDecodedIP[9]/2;
		}

		else if((i4>=6)&&(i4<14))
		{
			temp4=IDecodedIP[8]& 0x1;             //z_debug
			temp_frame2.Toe=temp4*xx__pow_opt(2,i4,0)+temp_frame2.Toe;
			IDecodedIP[8]=IDecodedIP[8]/2;
		}

		else if(i4>=14)
		{
			temp4=IDecodedIP[7]& 0x1;             //z_debug
			temp_frame2.Toe=temp4*xx__pow_opt(2,i4,0)+temp_frame2.Toe;
			IDecodedIP[7]=IDecodedIP[7]/2;
		}
	}
	temp_frame2.Toe=temp_frame2.Toe*16;

	// Extracting  	Mo : Mean Anomaly

	for(i4=0;i4<32;i4++)
	{
		if(i4<6)
		{
			temp4=IDecodedIP[7]& 0x1;             //z_debug
			temp_frame2.Mo=temp4*xx__pow_opt(2,i4,0)+temp_frame2.Mo;
			IDecodedIP[7]=IDecodedIP[7]/2;
		}

		else if((i4>=6)&&(i4<14))
		{
			temp4=IDecodedIP[6]& 0x1;             //z_debug
			temp_frame2.Mo=temp4*xx__pow_opt(2,i4,0)+temp_frame2.Mo;
			IDecodedIP[6]=IDecodedIP[6]/2;
		}

		else if((i4>=14)&&(i4<22))
		{
			temp4=IDecodedIP[5]& 0x1;             //z_debug
			temp_frame2.Mo=temp4*xx__pow_opt(2,i4,0)+temp_frame2.Mo;
			IDecodedIP[5]=IDecodedIP[5]/2;
		}

		else if((i4>=22)&&(i4<30))
		{
			temp4=IDecodedIP[4]& 0x1;             //z_debug
			temp_frame2.Mo=temp4*xx__pow_opt(2,i4,0)+temp_frame2.Mo;
			IDecodedIP[4]=IDecodedIP[4]/2;
		}

		else if(i4==30)
		{
			temp4=IDecodedIP[3]& 0x1;             //z_debug
			temp_frame2.Mo=temp4*xx__pow_opt(2,i4,0)+temp_frame2.Mo;
			IDecodedIP[3]=IDecodedIP[3]/2;
		}

		else if(i4==31)
		{
			temp4=IDecodedIP[3]& 0x1;             //z_debug
			temp_frame2.Mo=temp4*xx__pow_opt(2,i4,0)*-1+temp_frame2.Mo;
			IDecodedIP[3]=IDecodedIP[3]/2;
		}
	}
	temp_frame2.Mo=temp_frame2.Mo*s31*pi;

	// Extracting   Autonav Alert  Value

	for(i4=0;i4<6;i4++)
	{
		if(i4<3)
			IDecodedIP[3]=IDecodedIP[3]/2;

		else if(i4==3)
		{
		//Autonav2=IDecodedIP[3]%2;
		temp_frame2.AutoNav = IDecodedIP[3]& 0x1;             //z_debug
		IDecodedIP[3]=IDecodedIP[3]/2;
		}

		else if(i4==4)
		{
		//Alert2=IDecodedIP[3]& 0x1;             //z_debug
		temp_frame2.Alert =IDecodedIP[3]& 0x1;             //z_debug
		IDecodedIP[3]=IDecodedIP[3]/2;
		}
	}

	// Extracting  TOWC
	for(i4=0;i4<17;i4++)
	{
		if(i4==0)
		{
		temp4=IDecodedIP[3]& 0x1;             //z_debug
		temp_frame2.TOWC2=(temp4*xx__pow_opt(2,i4,0))+temp_frame2.TOWC2;
		IDecodedIP[3]=IDecodedIP[3]/2;
		}

		else if((i4>0)&&(i4<9))
		{
		temp4=IDecodedIP[2]& 0x1;             //z_debug
		temp_frame2.TOWC2=(temp4*xx__pow_opt(2,i4,0))+temp_frame2.TOWC2;
		IDecodedIP[2]=IDecodedIP[2]/2;
		}

		else if(i4>=9)
		{
		temp4=IDecodedIP[1]& 0x1;             //z_debug
		temp_frame2.TOWC2=(temp4*xx__pow_opt(2,i4,0))+temp_frame2.TOWC2;
		IDecodedIP[1]=IDecodedIP[1]/2;
		}
	}

 } // End of the Subroutine


void NavExtractDataFrameThreeFour(int IDecodedIP[37],int NavSatNo)
{

	uint8_t i4,temp4;
	uint8_t temp34;

	temp_frame3_4.PRNID=0,temp_frame3_4.MSGID=0;
	temp_frame3_4.TOWC34=0;temp_frame3_4.Alert34=0,temp_frame3_4.Autonav34=0;

	// Each message in the Sub-frame 3 and 4 has a 6 bit PRN identifier that uniquely
	// identifies the spacecraft transmitting the corresponding message..

	// Extracting  PRN identifier

	IDecodedIP[32]= IDecodedIP[32]/4;

	for(i4=0;i4<6;i4++) // Extracting  PRN identifier for Transmitting spacecraft
	{
		temp4=IDecodedIP[32]& 0x1;             //z_debug
		temp_frame3_4.PRNID=temp4*xx__pow_opt(2,i4,0)+temp_frame3_4.PRNID;
		IDecodedIP[32]=IDecodedIP[32]/2;
	}
	// Extracting Message ID.

	temp34=IDecodedIP[4]/16;

	for(i4=0;i4<6;i4++) // Extracting Message ID.
	{
		if(i4<4)
		{
			temp4=temp34& 0x1;             //z_debug
			temp_frame3_4.MSGID=temp4*xx__pow_opt(2,i4,0)+temp_frame3_4.MSGID;
			temp34=temp34/2;
		}

		else if(i4>=4)
		{
			temp4=IDecodedIP[3]& 0x1;             //z_debug
			temp_frame3_4.MSGID=temp4*xx__pow_opt(2,i4,0)+temp_frame3_4.MSGID;
			IDecodedIP[3]=IDecodedIP[3]/2;
		}
	}


	//Extraction of Autonav and ,Alert Code
	for(i4=0;i4<6;i4++)
	{
		if(i4<3)
			IDecodedIP[3]=IDecodedIP[3]/2;

		else if(i4==3)
		{
			temp_frame3_4.Autonav34=IDecodedIP[3]& 0x1;             //z_debug
			IDecodedIP[3]=IDecodedIP[3]/2;
		}

		else if(i4==4)
		{
			temp_frame3_4.Alert34=IDecodedIP[3]& 0x1;             //z_debug
			IDecodedIP[3]=IDecodedIP[3]/2;
		}
	}// for

    // Extraction of  TOWC

	for(i4=0;i4<17;i4++)
	{
		if(i4<1)
		{
			temp4=IDecodedIP[3]& 0x1;             //z_debug
			temp_frame3_4.TOWC34=temp4*xx__pow_opt(2,i4,0)+temp_frame3_4.TOWC34;
			IDecodedIP[3]=IDecodedIP[3]/2;
		}

		else if((i4>=1)&&(i4<9))
		{
			temp4=IDecodedIP[2]& 0x1;             //z_debug
			temp_frame3_4.TOWC34=temp4*xx__pow_opt(2,i4,0)+temp_frame3_4.TOWC34;
			IDecodedIP[2]=IDecodedIP[2]/2;
		}

		else if(i4>=9)
		{
			temp4=IDecodedIP[1]& 0x1;             //z_debug
			temp_frame3_4.TOWC34=temp4*xx__pow_opt(2,i4,0)+temp_frame3_4.TOWC34;
			IDecodedIP[1]=IDecodedIP[1]/2;
		}
	}

		// Check if the Alert Flag is set

		if (temp_frame3_4.Alert34 == 1)
		 return ; // Do not Copy the data and extract further data..

		// Else Copy the Extracted data in the PVT I/P data Buffers

		VerifyCopyFrameThreeFourData(NavSatNo);

   	switch(temp_frame3_4.MSGID)
	{
		case 9:
			NavExtractMsgNine(IDecodedIP);
			VerifyCopyMesssgeNine();
			break;

		case 11:
			NavExtractMsgEleven(IDecodedIP);
			VerifyCopyMessageEleven();
			break;

		case 26:
			NavExtractMsgTwentySix(IDecodedIP);
			//VerifyCopyFrameMessageTwentySix();			//orig
			VerifyCopyFrameMessageTwentySix(IDecodedIP, NavSatNo);	//z_gcc
			break;
	}
	return;

}// End of the Subroutine


void NavExtractMsgNine(int IDecodedIP [37])

{
	uint8_t i4,temp4;

	// Initialization Of The Parameters To Be Extracted

	temp_UTCCorr.A0utc=0,temp_UTCCorr.A1utc=0,temp_UTCCorr.A2utc=0,temp_UTCCorr.delTls=0;
	temp_UTCCorr.Toutc=0,temp_UTCCorr.WNoutc=0,temp_UTCCorr.WNlsf=0,temp_UTCCorr.DN=0;
	temp_UTCCorr.delTlsf=0,temp_UTCCorr.A0=0,temp_UTCCorr.A1=0,temp_UTCCorr.A2=0;
	temp_UTCCorr.Tot=0,temp_UTCCorr.WNot=0,temp_UTCCorr.GNSSID=0;

	// Extraction of  Satellite Number

	IDecodedIP[24]= IDecodedIP[24]/(2^7);

	for(i4=0;i4<3;i4++)
	{
		if(i4<1)
		{
			temp4=IDecodedIP[24]& 0x1;             //z_debug
			temp_UTCCorr.GNSSID=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.GNSSID;
			IDecodedIP[24]=IDecodedIP[24]/2;
		}
		else if(i4>=1)
		{
			temp4=IDecodedIP[23]& 0x1;             //z_debug
			temp_UTCCorr.GNSSID=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.GNSSID;
			IDecodedIP[23]=IDecodedIP[23]/2;
		}
	}
	// Extraction of  OmegaNot  time data reference week number
	for(i4=0;i4<10;i4++)
	{
		if(i4<6)
		{
			temp4=IDecodedIP[23]& 0x1;             //z_debug
			temp_UTCCorr.WNot=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.WNot;
			IDecodedIP[23]=IDecodedIP[23]/2;
		}
		else if(i4>=6)
		{
			temp4=IDecodedIP[22]& 0x1;             //z_debug
			temp_UTCCorr.WNot=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.WNot;
			IDecodedIP[23]=IDecodedIP[22]/2;
		}
	}
	// Extraction of  Tot : Time data reference time of week
	for(i4=0;i4<16;i4++)
	{
		if(i4<4)
		{
			temp4=IDecodedIP[22]& 0x1;             //z_debug
			temp_UTCCorr.Tot=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.Tot;
			IDecodedIP[22]=IDecodedIP[22]/2;
		}
		else if((i4>=4)&&(i4<12))
		{
			temp4=IDecodedIP[21]& 0x1;             //z_debug
			temp_UTCCorr.Tot=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.Tot;
			IDecodedIP[21]=IDecodedIP[21]/2;
		}
		else if(i4>=12)
		{
			temp4=IDecodedIP[20]& 0x1;             //z_debug
			temp_UTCCorr.Tot=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.Tot;
			IDecodedIP[20]=IDecodedIP[20]/2;
		}
	}
	temp_UTCCorr.Tot=temp_UTCCorr.Tot*16;

	// Extraction of  A2; Drift rate correction coefficient of IRNSS time scale
	//relative of GPS time scale

	for(i4=0;i4<7;i4++)
	{
		if(i4<4)
		{
			temp4=IDecodedIP[20]& 0x1;             //z_debug
			temp_UTCCorr.A2=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.A2;
			IDecodedIP[20]=IDecodedIP[20]/2;
		}
		else if((i4>=4)&&(i4<6))
		{
			temp4=IDecodedIP[19]& 0x1;             //z_debug
			temp_UTCCorr.A2=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.A2;
			IDecodedIP[19]=IDecodedIP[19]/2;
		}
		else if(i4==6)
		{
			temp4=IDecodedIP[19]& 0x1;             //z_debug
			temp_UTCCorr.A2=temp4*xx__pow_opt(2,i4,0)*-1+temp_UTCCorr.A2;
			IDecodedIP[19]=IDecodedIP[19]/2;
		}
	}
	temp_UTCCorr.A2=temp_UTCCorr.A2*s68;

	// Extraction of  A1; Drift coefficient of IRNSS time scale relative to GPS time scale
	for(i4=0;i4<13;i4++)
	{
		if(i4<5)
		{
			temp4=IDecodedIP[19]& 0x1;             //z_debug
			temp_UTCCorr.A1=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.A1;
			IDecodedIP[19]=IDecodedIP[19]/2;
		}
		else if((i4>=5)&&(i4<12))
		{
			temp4=IDecodedIP[18]& 0x1;             //z_debug
			temp_UTCCorr.A1=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.A1;
			IDecodedIP[18]=IDecodedIP[18]/2;
		}
		else if(i4==12)
		{
			temp4=IDecodedIP[18]& 0x1;             //z_debug
			temp_UTCCorr.A1=temp4*xx__pow_opt(2,i4,0)*-1+temp_UTCCorr.A1;
			IDecodedIP[18]=IDecodedIP[18]/2;
		}
	}
	temp_UTCCorr.A1=temp_UTCCorr.A1*s51;

	// Extraction of  A0; Bias coefficient of IRNSS time scale relative to GPS time scale
	for(i4=0;i4<16;i4++)
	{
		if(i4<8)
		{
			temp4=IDecodedIP[17]& 0x1;             //z_debug
			temp_UTCCorr.A0=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.A0;
			IDecodedIP[17]=IDecodedIP[17]/2;
		}
		else if((i4>=8)&&(i4<15))
		{
			temp4=IDecodedIP[16]& 0x1;             //z_debug
			temp_UTCCorr.A0=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.A0;
			IDecodedIP[16]=IDecodedIP[16]/2;
		}
		else if(i4==15)
		{
			temp4=IDecodedIP[16]& 0x1;             //z_debug
			temp_UTCCorr.A0=temp4*xx__pow_opt(2,i4,0)*-1+temp_UTCCorr.A0;
			IDecodedIP[16]=IDecodedIP[16]/2;
		}
	}
	temp_UTCCorr.A0=temp_UTCCorr.A0*s35;

	// Extraction of  delTlsf; Current or future leap second count
	for(i4=0;i4<8;i4++)
	{
		if(i4<7)
		{
			temp4=IDecodedIP[15]& 0x1;             //z_debug
			temp_UTCCorr.delTlsf=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.delTlsf;
			IDecodedIP[15]=IDecodedIP[15]/2;
		}
		else if(i4==7)
		{
			temp4=IDecodedIP[15]& 0x1;             //z_debug
			temp_UTCCorr.delTlsf=temp4*xx__pow_opt(2,i4,0)*-1+temp_UTCCorr.delTlsf;
			IDecodedIP[15]=IDecodedIP[15]/2;
		}
	}

	// Extraction of  DN; Leap second reference day number
	for(i4=0;i4<4;i4++)
	{
		temp4=IDecodedIP[14]& 0x1;             //z_debug
		temp_UTCCorr.DN=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.DN;
		IDecodedIP[14]=IDecodedIP[14]/2;
	}

	// Extraction of  WNlsf; Leap second reference week number
	for(i4=0;i4<10;i4++)
	{
		if(i4<4)
		{
			temp4=IDecodedIP[14]& 0x1;             //z_debug
			temp_UTCCorr.WNlsf=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.WNlsf;
			IDecodedIP[14]=IDecodedIP[14]/2;
		}
		else if(i4>=4)
		{
			temp4=IDecodedIP[13]& 0x1;             //z_debug
			temp_UTCCorr.WNlsf=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.WNlsf;
			IDecodedIP[13]=IDecodedIP[13]/2;
		}
	}

	// Extraction of  WNoutc,  Time data reference week number
	for(i4=0;i4<10;i4++)
	{
		if(i4<2)
		{
			temp4=IDecodedIP[13]& 0x1;             //z_debug
			temp_UTCCorr.WNoutc=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.WNoutc;
			IDecodedIP[13]=IDecodedIP[13]/2;
		}
		else if(i4>=2)
		{
			temp4=IDecodedIP[12]& 0x1;             //z_debug
			temp_UTCCorr.WNoutc=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.WNoutc;
			IDecodedIP[12]=IDecodedIP[12]/2;
		}
	}
	// Extraction of  Toutc; // Time data reference time of week
	for(i4=0;i4<16;i4++)
	{
		if(i4<8)
		{
			temp4=IDecodedIP[11]& 0x1;             //z_debug
			temp_UTCCorr.Toutc=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.Toutc;
			IDecodedIP[11]=IDecodedIP[11]/2;
		}
		else if(i4>=8)
		{
			temp4=IDecodedIP[10]& 0x1;             //z_debug
			temp_UTCCorr.Toutc=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.Toutc;
			IDecodedIP[10]=IDecodedIP[10]/2;
		}
	}
	temp_UTCCorr.Toutc=temp_UTCCorr.Toutc*16;

	// Extraction of  delTls, // Current or past leap second count
	for(i4=0;i4<8;i4++)
	{
		if(i4<7)
		{
			temp4=IDecodedIP[9]& 0x1;             //z_debug
			temp_UTCCorr.delTls=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.delTls;
			IDecodedIP[9]=IDecodedIP[9]/2;
		}
		else if(i4==7)
		{
			temp4=IDecodedIP[9]& 0x1;             //z_debug
			temp_UTCCorr.delTls=temp4*xx__pow_opt(2,i4,0)*-1+temp_UTCCorr.delTls;
			IDecodedIP[9]=IDecodedIP[9]/2;
		}
	}
	// Extraction of  A2utc// Drift rate correction coefficient of IRNSS time
	// scale relative to UTC time scale

	for(i4=0;i4<7;i4++)
	{
		if(i4<6)
		{
			temp4=IDecodedIP[8]& 0x1;             //z_debug
			temp_UTCCorr.A2utc=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.A2utc;
			IDecodedIP[8]=IDecodedIP[8]/2;
		}
		if(i4==6)
		{
			temp4=IDecodedIP[8]& 0x1;             //z_debug
			temp_UTCCorr.A2utc=temp4*xx__pow_opt(2,i4,0)*-1+temp_UTCCorr.A2utc;
			IDecodedIP[8]=IDecodedIP[8]/2;
		}
	}
	temp_UTCCorr.A2utc=temp_UTCCorr.A2utc*s68;

	// Extraction of A1utc // Drift coefficient of IRNSS time scale relative to UTC time scale
	for(i4=0;i4<13;i4++)
	{
		if(i4<1)
		{
			temp4=IDecodedIP[8]& 0x1;             //z_debug
			temp_UTCCorr.A1utc=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.A1utc;
			IDecodedIP[8]=IDecodedIP[8]/2;
		}
		else if((i4>=1)&&(i4<9))
		{
			temp4=IDecodedIP[7]& 0x1;             //z_debug
			temp_UTCCorr.A1utc=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.A1utc;
			IDecodedIP[7]=IDecodedIP[7]/2;
		}
		else if((i4>=9)&&(i4<12))
		{
			temp4=IDecodedIP[6]& 0x1;             //z_debug
			temp_UTCCorr.A1utc=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.A1utc;
			IDecodedIP[6]=IDecodedIP[6]/2;
		}
		else if(i4==12)
		{
			temp4=IDecodedIP[6]& 0x1;             //z_debug
			temp_UTCCorr.A1utc=temp4*xx__pow_opt(2,i4,0)*-1+temp_UTCCorr.A1utc;
			IDecodedIP[6]=IDecodedIP[6]/2;
		}
	}
	temp_UTCCorr.A1utc=temp_UTCCorr.A1utc*s51;

	// Extraction of A0utc// Bias coefficient of IRNSS time scale relative to UTC time scale
	for(i4=0;i4<16;i4++)
	{
		if(i4<4)
		{
			temp4=IDecodedIP[6]& 0x1;             //z_debug
			temp_UTCCorr.A0utc=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.A0utc;
			IDecodedIP[6]=IDecodedIP[6]/2;
		}
		else if((i4>=4)&&(i4<12))
		{
			temp4=IDecodedIP[5]& 0x1;             //z_debug
			temp_UTCCorr.A0utc=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.A0utc;
			IDecodedIP[5]=IDecodedIP[5]/2;
		}
		else if((i4>=12)&&(i4<15))
		{
			temp4=IDecodedIP[4]& 0x1;             //z_debug
			temp_UTCCorr.A0utc=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.A0utc;
			IDecodedIP[4]=IDecodedIP[4]/2;
		}
		else if(i4==15)
		{
			temp4=IDecodedIP[4]& 0x1;             //z_debug
			temp_UTCCorr.A0utc=temp4*xx__pow_opt(2,i4,0)*-1+temp_UTCCorr.A0utc;
			IDecodedIP[4]=IDecodedIP[4]/2;
		}
	}

} // End of the subroutine

//void NavExtractMsgEleven(int IDecodedIP [])	//z_debug
void NavExtractMsgEleven(int IDecodedIP [37])

{
    uint8_t i4,temp4;

    // Extraction of  Ionospheric Correction Beta 3

	IDecodedIP[29]=IDecodedIP[29]/4;
	for(i4=0;i4<8;i4++)
	{
		if(i4<6)
		{
			temp4=IDecodedIP[29]& 0x1;             //z_debug
			temp_Iono_Corr.beta3=temp4*xx__pow_opt(2,i4,0)+temp_Iono_Corr.beta3;
			IDecodedIP[29]=IDecodedIP[29]/2;
		}
		else if(i4==6)
		{
			temp4=IDecodedIP[28]& 0x1;             //z_debug
			temp_Iono_Corr.beta3=temp4*xx__pow_opt(2,i4,0)+temp_Iono_Corr.beta3;
			IDecodedIP[28]=IDecodedIP[28]/2;
		}
		else if(i4==7)
		{
			temp4=IDecodedIP[28]& 0x1;             //z_debug
			temp_Iono_Corr.beta3=temp4*xx__pow_opt(2,i4,0)*-1+temp_Iono_Corr.beta3;
			IDecodedIP[28]=IDecodedIP[28]/2;
		}
	}
	temp_Iono_Corr.beta3=temp_Iono_Corr.beta3*sp16;

	// Extraction of  Ionospheric Correction Beta 2

	for(i4=0;i4<8;i4++)
	{
		if(i4<6)
		{
			temp4=IDecodedIP[28]& 0x1;             //z_debug
			temp_Iono_Corr.beta2=temp4*xx__pow_opt(2,i4,0)+temp_Iono_Corr.beta2;
			IDecodedIP[28]=IDecodedIP[28]/2;
		}
		else if(i4==6)
		{
			temp4=IDecodedIP[27]& 0x1;             //z_debug
			temp_Iono_Corr.beta2=temp4*xx__pow_opt(2,i4,0)+temp_Iono_Corr.beta2;
			IDecodedIP[27]=IDecodedIP[27]/2;
		}
		else if(i4==7)
		{
			temp4=IDecodedIP[27]& 0x1;             //z_debug
			temp_Iono_Corr.beta2=temp4*xx__pow_opt(2,i4,0)*-1+temp_Iono_Corr.beta2;
			IDecodedIP[27]=IDecodedIP[27]/2;
		}
	}
	temp_Iono_Corr.beta2=temp_Iono_Corr.beta2*sp16;

	// Extraction of Ionospheric Correction Beta 1

	for(i4=0;i4<8;i4++)
	{
		if(i4<6)
		{
			temp4=IDecodedIP[27]& 0x1;             //z_debug
			temp_Iono_Corr.beta1=temp4*xx__pow_opt(2,i4,0)+temp_Iono_Corr.beta1;
			IDecodedIP[27]=IDecodedIP[27]/2;
		}
		else if(i4==6)
		{
			temp4=IDecodedIP[26]& 0x1;             //z_debug
			temp_Iono_Corr.beta1=temp4*xx__pow_opt(2,i4,0)+temp_Iono_Corr.beta1;
			IDecodedIP[26]=IDecodedIP[26]/2;
		}
		else if(i4==7)
		{
			temp4=IDecodedIP[26]& 0x1;             //z_debug
			temp_Iono_Corr.beta1=temp4*xx__pow_opt(2,i4,0)*-1+temp_Iono_Corr.beta1;
			IDecodedIP[26]=IDecodedIP[26]/2;
		}
	}
	temp_Iono_Corr.beta1=temp_Iono_Corr.beta1*sp14;

	// Extraction of Ionospheric Correction Beta 0

	for(i4=0;i4<8;i4++)
	{
		if(i4<6)
		{
			temp4=IDecodedIP[26]& 0x1;             //z_debug
			temp_Iono_Corr.beta0=temp4*xx__pow_opt(2,i4,0)+temp_Iono_Corr.beta0;
			IDecodedIP[26]=IDecodedIP[26]/2;
		}
		else if(i4==6)
		{
			temp4=IDecodedIP[25]& 0x1;             //z_debug
			temp_Iono_Corr.beta0=temp4*xx__pow_opt(2,i4,0)+temp_Iono_Corr.beta0;
			IDecodedIP[25]=IDecodedIP[25]/2;
		}
		else if(i4==7)
		{
			temp4=IDecodedIP[25]& 0x1;             //z_debug
			temp_Iono_Corr.beta0=temp4*xx__pow_opt(2,i4,0)*-1+temp_Iono_Corr.beta0;
			IDecodedIP[25]=IDecodedIP[25]/2;
		}
	}
	temp_Iono_Corr.beta0=temp_Iono_Corr.beta0*sp11;

	// Extraction of  Ionospheric Correction Alpha 3

	for(i4=0;i4<8;i4++)
	{
		if(i4<6){
			temp4=IDecodedIP[25]& 0x1;             //z_debug
			temp_Iono_Corr.alpha3=temp4*xx__pow_opt(2,i4,0)+temp_Iono_Corr.alpha3;
			IDecodedIP[25]=IDecodedIP[25]/2;
		}
		else if(i4==6){
			temp4=IDecodedIP[24]& 0x1;             //z_debug
			temp_Iono_Corr.alpha3=temp4*xx__pow_opt(2,i4,0)+temp_Iono_Corr.alpha3;
			IDecodedIP[24]=IDecodedIP[24]/2;
		}
		else if(i4==7){
			temp4=IDecodedIP[24]& 0x1;             //z_debug
			temp_Iono_Corr.alpha3=temp4*xx__pow_opt(2,i4,0)*-1+temp_Iono_Corr.alpha3;
			IDecodedIP[24]=IDecodedIP[24]/2;
		}
	}
	temp_Iono_Corr.alpha3=temp_Iono_Corr.alpha3*s24;

	// Extraction of Ionospheric Correction Alpha 2

	for(i4=0;i4<8;i4++){
		if(i4<6){
			temp4=IDecodedIP[24]& 0x1;             //z_debug
			temp_Iono_Corr.alpha2=temp4*xx__pow_opt(2,i4,0)+temp_Iono_Corr.alpha2;
			IDecodedIP[24]=IDecodedIP[24]/2;
		}
		else if(i4==6){
			temp4=IDecodedIP[23]& 0x1;             //z_debug
			temp_Iono_Corr.alpha2=temp4*xx__pow_opt(2,i4,0)+temp_Iono_Corr.alpha2;
			IDecodedIP[23]=IDecodedIP[23]/2;
		}
		else if(i4==7){
			temp4=IDecodedIP[23]& 0x1;             //z_debug
			temp_Iono_Corr.alpha2=temp4*xx__pow_opt(2,i4,0)*-1+temp_Iono_Corr.alpha2;
			IDecodedIP[23]=IDecodedIP[23]/2;
		}
	}
	temp_Iono_Corr.alpha2=temp_Iono_Corr.alpha2*s24;

	// Extraction of  Ionospheric Correction Alpha 1

	for(i4=0;i4<8;i4++){
		if(i4<6){
			temp4=IDecodedIP[23]& 0x1;             //z_debug
			temp_Iono_Corr.alpha1=temp4*xx__pow_opt(2,i4,0)+temp_Iono_Corr.alpha1;
			IDecodedIP[23]=IDecodedIP[23]/2;
		}
		else if(i4==6){
			temp4=IDecodedIP[22]& 0x1;             //z_debug
			temp_Iono_Corr.alpha1=temp4*xx__pow_opt(2,i4,0)+temp_Iono_Corr.alpha1;
			IDecodedIP[22]=IDecodedIP[22]/2;
		}
		else if(i4==7){
			temp4=IDecodedIP[22]& 0x1;             //z_debug
			temp_Iono_Corr.alpha1=temp4*xx__pow_opt(2,i4,0)*-1+temp_Iono_Corr.alpha1;
			IDecodedIP[22]=IDecodedIP[22]/2;
		}
	}
	temp_Iono_Corr.alpha1=temp_Iono_Corr.alpha1*s27;

	// Extraction of Ionospheric Correction Alpha 0

	for(i4=0;i4<8;i4++)
	{
		if(i4<6)
		{
			temp4=IDecodedIP[22]& 0x1;             //z_debug
			temp_Iono_Corr.alpha0=temp4*xx__pow_opt(2,i4,0)+temp_Iono_Corr.alpha0;
			IDecodedIP[22]=IDecodedIP[22]/2;
		}
		else if(i4==6)
		{
			temp4=IDecodedIP[21]& 0x1;             //z_debug
			temp_Iono_Corr.alpha0=temp4*xx__pow_opt(2,i4,0)+temp_Iono_Corr.alpha0;
			IDecodedIP[21]=IDecodedIP[21]/2;
		}
		else if(i4==7)
		{
			temp4=IDecodedIP[21]& 0x1;             //z_debug
			temp_Iono_Corr.alpha0=temp4*xx__pow_opt(2,i4,0)*-1+temp_Iono_Corr.alpha0;
			IDecodedIP[21]=IDecodedIP[21]/2;
		}
	}

}

//This routine extracts data from the Message Type 26. This Message provides the
//IRNSS time offset with respect to UTC, UTC (NPLI) and other GNSS like GPS, GALILEO
//and GLONASS etc The same set of data is also available in the meage type 9. Howver
// this data is required for computing the UTC time hence which ever message type comes
//first it will fill the UTC data structures

void NavExtractMsgTwentySix(int IDecodedIP[])
{

	uint8_t i4,temp4;

	temp_UTCCorr.A1utc=0,temp_UTCCorr.A2utc=0,temp_UTCCorr.delTls=0;
	temp_UTCCorr.Toutc=0,temp_UTCCorr.WNoutc=0,temp_UTCCorr.WNlsf=0;
	temp_UTCCorr.DN=0,temp_UTCCorr.delTlsf=0,temp_UTCCorr.A0=0;
	temp_UTCCorr.A1=0,temp_UTCCorr.A2=0,temp_UTCCorr.Tot=0;
	temp_UTCCorr.WNot=0,temp_UTCCorr.GNSSID=0;


	//start Extracting the Message Type 26 Data
	IDecodedIP[24]= IDecodedIP[24]/(2^7);

	//GNSSID; // GNSS ID for GPS is 0

	for(i4=0;i4<3;i4++){
		if(i4<1){
			temp4=IDecodedIP[24]& 0x1;             //z_debug
			temp_UTCCorr.GNSSID=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.GNSSID;
			IDecodedIP[24]=IDecodedIP[24]/2;
		}

		else if(i4>=1){
			temp4=IDecodedIP[23]& 0x1;             //z_debug
			temp_UTCCorr.GNSSID=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.GNSSID;
			IDecodedIP[23]=IDecodedIP[23]/2;
		}
	}

  	// Extraction of WNot; // Time data reference week number

	for(i4=0;i4<10;i4++){
		if(i4<6)	{
			temp4=IDecodedIP[23]& 0x1;             //z_debug
			temp_UTCCorr.WNot=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.WNot;
			IDecodedIP[23]=IDecodedIP[23]/2;
		}

		else if(i4>=6){
			temp4=IDecodedIP[22]& 0x1;             //z_debug
			temp_UTCCorr.WNot=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.WNot;
			IDecodedIP[23]=IDecodedIP[22]/2;
		}
	}
	// Extraction of Tot // Time data reference time of week

	for(i4=0;i4<16;i4++)
	{
		if(i4<4)
		{
			temp4=IDecodedIP[22]& 0x1;             //z_debug
			temp_UTCCorr.Tot=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.Tot;
			IDecodedIP[22]=IDecodedIP[22]/2;
		}

		else if((i4>=4)&&(i4<12))
		{
			temp4=IDecodedIP[21]& 0x1;             //z_debug
			temp_UTCCorr.Tot=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.Tot;
			IDecodedIP[21]=IDecodedIP[21]/2;
		}

		else if(i4>=12)
		{
			temp4=IDecodedIP[20]& 0x1;             //z_debug
			temp_UTCCorr.Tot=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.Tot;
			IDecodedIP[20]=IDecodedIP[20]/2;
		}
	}

	temp_UTCCorr.Tot=temp_UTCCorr.Tot*16;

	// Extraction of A2; // Drift rate correction coefficient of IRNSS
	//time scale relative of GPS time scale

	for(i4=0;i4<7;i4++)
	{
		if(i4<4)
		{
			temp4=IDecodedIP[20]& 0x1;             //z_debug
			temp_UTCCorr.A2=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.A2;
			IDecodedIP[20]=IDecodedIP[20]/2;
		}

		else if((i4>=4)&&(i4<6))
		{
			temp4=IDecodedIP[19]& 0x1;             //z_debug
			temp_UTCCorr.A2=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.A2;
			IDecodedIP[19]=IDecodedIP[19]/2;
		}

		else if(i4==6)
		{
			temp4=IDecodedIP[19]& 0x1;             //z_debug
			temp_UTCCorr.A2=temp4*xx__pow_opt(2,i4,0)*-1+temp_UTCCorr.A2;
			IDecodedIP[19]=IDecodedIP[19]/2;
		}
	}
	temp_UTCCorr.A2=temp_UTCCorr.A2*s68;

	// Extraction of A1 :Drift coefficient of IRNSS time scale relative to GPS time scale

	for(i4=0;i4<13;i4++)
	{
		if(i4<5)
		{
			temp4=IDecodedIP[19]& 0x1;             //z_debug
			temp_UTCCorr.A1=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.A1;
			IDecodedIP[19]=IDecodedIP[19]/2;
		}

		else if((i4>=5)&&(i4<12))
		{
			temp4=IDecodedIP[18]& 0x1;             //z_debug
			temp_UTCCorr.A1=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.A1;
			IDecodedIP[18]=IDecodedIP[18]/2;
		}

		else if(i4==12)
		{
			temp4=IDecodedIP[18]& 0x1;             //z_debug
			temp_UTCCorr.A1=temp4*xx__pow_opt(2,i4,0)*-1+temp_UTCCorr.A1;
			IDecodedIP[18]=IDecodedIP[18]/2;
		}
	}
	temp_UTCCorr.A1=temp_UTCCorr.A1*s51;

	// Extraction of A0 :Bias coefficient of IRNSS time scale relative to GPS time scale

	for(i4=0;i4<16;i4++)
	{
		if(i4<8)
		{
			temp4=IDecodedIP[17]& 0x1;             //z_debug
			temp_UTCCorr.A0=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.A0;
			IDecodedIP[17]=IDecodedIP[17]/2;
		}

		else if((i4>=8)&&(i4<15))
		{
			temp4=IDecodedIP[16]& 0x1;             //z_debug
			temp_UTCCorr.A0=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.A0;
			IDecodedIP[16]=IDecodedIP[16]/2;
		}

		else if(i4==15)
		{
			temp4=IDecodedIP[16]& 0x1;             //z_debug
			temp_UTCCorr.A0=temp4*xx__pow_opt(2,i4,0)*-1+temp_UTCCorr.A0;
			IDecodedIP[16]=IDecodedIP[16]/2;
		}
	}
	temp_UTCCorr.A0=temp_UTCCorr.A0*s35;

	// Extraction of delTlsf : Current or future leap second count

	for(i4=0;i4<8;i4++)
	{

		if(i4<7)
		{
			temp4=IDecodedIP[15]& 0x1;             //z_debug
			temp_UTCCorr.delTlsf=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.delTlsf;
			IDecodedIP[15]=IDecodedIP[15]/2;
		}

		else if(i4==7)
		{
			temp4=IDecodedIP[15]& 0x1;             //z_debug
			temp_UTCCorr.delTlsf=temp4*xx__pow_opt(2,i4,0)*-1+temp_UTCCorr.delTlsf;
			IDecodedIP[15]=IDecodedIP[15]/2;
		}
	}

	// Extraction of DN; : Leap second reference day number
	for(i4=0;i4<4;i4++)
	{
		temp4=IDecodedIP[14]& 0x1;             //z_debug
		temp_UTCCorr.DN=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.DN;
		IDecodedIP[14]=IDecodedIP[14]/2;
	}

	// Extraction of WNlsf :Leap second reference week number

	for(i4=0;i4<10;i4++)
	{
		if(i4<4)
		{
			temp4=IDecodedIP[14]& 0x1;             //z_debug
			temp_UTCCorr.WNlsf=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.WNlsf;
			IDecodedIP[14]=IDecodedIP[14]/2;
		}

		else if(i4>=4)
		{
			temp4=IDecodedIP[13]& 0x1;             //z_debug
			temp_UTCCorr.WNlsf=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.WNlsf;
			IDecodedIP[13]=IDecodedIP[13]/2;
		}
	}
	// Extraction of WNoutc : Time data reference week number

	for(i4=0;i4<10;i4++)
	{
		if(i4<2)
		{
			temp4=IDecodedIP[13]& 0x1;             //z_debug
			temp_UTCCorr.WNoutc=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.WNoutc;
			IDecodedIP[13]=IDecodedIP[13]/2;
		}

		else if(i4>=2)
		{
			temp4=IDecodedIP[12]& 0x1;             //z_debug
			temp_UTCCorr.WNoutc=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.WNoutc;
			IDecodedIP[12]=IDecodedIP[12]/2;
		}
	}
	// Extraction of Toutc : Time data reference time of week

	for(i4=0;i4<16;i4++)
	{
		if(i4<8)
		{
			temp4=IDecodedIP[11]& 0x1;             //z_debug
			temp_UTCCorr.Toutc=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.Toutc;
			IDecodedIP[11]=IDecodedIP[11]/2;
		}

		else if(i4>=8)
		{
			temp4=IDecodedIP[10]& 0x1;             //z_debug
			temp_UTCCorr.Toutc=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.Toutc;
			IDecodedIP[10]=IDecodedIP[10]/2;
		}
	}
	temp_UTCCorr.Toutc=temp_UTCCorr.Toutc*16;

	// Extraction of delTls : Current or past leap second count

	for(i4=0;i4<8;i4++)
	{

		if(i4<7)
		{
			temp4=IDecodedIP[9]& 0x1;             //z_debug
			temp_UTCCorr.delTls=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.delTls;
			IDecodedIP[9]=IDecodedIP[9]/2;
		}

		else if(i4==7)
		{
			temp4=IDecodedIP[9]& 0x1;             //z_debug
			temp_UTCCorr.delTls=temp4*xx__pow_opt(2,i4,0)*-1+temp_UTCCorr.delTls;
			IDecodedIP[9]=IDecodedIP[9]/2;
		}
	}

	// Extraction of A2utc : Drift rate correction coefficient of IRNSS time
	//scale relative to UTC time scale

	for(i4=0;i4<7;i4++)
	{

		if(i4<6)
		{
			temp4=IDecodedIP[8]& 0x1;             //z_debug
			temp_UTCCorr.A2utc=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.A2utc;
			IDecodedIP[8]=IDecodedIP[8]/2;
		}

		if(i4==6)
		{
			temp4=IDecodedIP[8]& 0x1;             //z_debug
			temp_UTCCorr.A2utc=temp4*xx__pow_opt(2,i4,0)*-1+temp_UTCCorr.A2utc;
			IDecodedIP[8]=IDecodedIP[8]/2;
		}
	}
	temp_UTCCorr.A2utc=temp_UTCCorr.A2utc*s68;

	// Extraction of 1utc :Drift coefficient of IRNSS time scale relative to UTC time scale

	for(i4=0;i4<13;i4++)
	{
		if(i4<1)
		{
			temp4=IDecodedIP[8]& 0x1;             //z_debug
			temp_UTCCorr.A1utc=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.A1utc;
			IDecodedIP[8]=IDecodedIP[8]/2;
		}

		else if((i4>=1)&&(i4<9))
		{
			temp4=IDecodedIP[7]& 0x1;             //z_debug
			temp_UTCCorr.A1utc=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.A1utc;
			IDecodedIP[7]=IDecodedIP[7]/2;
		}


		else if((i4>=9)&&(i4<12))
		{
			temp4=IDecodedIP[6]& 0x1;             //z_debug
			temp_UTCCorr.A1utc=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.A1utc;
			IDecodedIP[6]=IDecodedIP[6]/2;
		}

		else if(i4==12)
		{
			temp4=IDecodedIP[6]& 0x1;             //z_debug
			temp_UTCCorr.A1utc=temp4*xx__pow_opt(2,i4,0)*-1+temp_UTCCorr.A1utc;
			IDecodedIP[6]=IDecodedIP[6]/2;
		}

	}

	temp_UTCCorr.A1utc=temp_UTCCorr.A1utc*s51;

	// Extraction of A0utc// Bias coefficient of IRNSS time scale relative to UTC time scale

	for(i4=0;i4<16;i4++)
	{
		if(i4<4)
		{
			temp4=IDecodedIP[6]& 0x1;             //z_debug
			temp_UTCCorr.A0utc=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.A0utc;
			IDecodedIP[6]=IDecodedIP[6]/2;
		}

		else if((i4>=4)&&(i4<12))
		{
			temp4=IDecodedIP[5]& 0x1;             //z_debug
			temp_UTCCorr.A0utc=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.A0utc;
			IDecodedIP[5]=IDecodedIP[5]/2;
		}

		else if((i4>=12)&&(i4<15))
		{
			temp4=IDecodedIP[4]& 0x1;             //z_debug
			temp_UTCCorr.A0utc=temp4*xx__pow_opt(2,i4,0)+temp_UTCCorr.A0utc;
			IDecodedIP[4]=IDecodedIP[4]/2;
		}

		else if(i4==15)
		{
			temp4=IDecodedIP[4]& 0x1;             //z_debug
			temp_UTCCorr.A0utc=temp4*xx__pow_opt(2,i4,0)*-1+temp_UTCCorr.A0utc;
			IDecodedIP[4]=IDecodedIP[4]/2;
		}
	}
	return;

} // End of the subroutine

void VerifyCopyFrameOneData(int NavSatNo)
{
	// Check if the Alert Flag is set
	if (temp_frame1.Alert == 1)
		return ; // Do not Copy the data

	// Check the URA value  > 4
	if ( temp_frame1.URA > 14)
	{
		NavSubFrame1Data[NavSatNo].URA = -500.0; // Newly Added
		return ; // Do not Copy the data
	}

	 // Check the Current  S and L5 band Flags

	 if ( DataBufFrqBand == 1 && temp_frame1.Sflag == 1) // S Flag Status is Set
		return ; // Do not Copy the data

	 if ( DataBufFrqBand == 0 && temp_frame1.L5flag == 1) // L5 Flag Status is Set
	 	return ; // Do not Copy the data

	 // Check whether current Ephemeris Data is Latest one

	NavSubFrame1Data[NavSatNo].WN	=temp_frame1.WN;
	NavSubFrame1Data[NavSatNo].af0	=temp_frame1.af0;
	NavSubFrame1Data[NavSatNo].af1	=temp_frame1.af1;
	NavSubFrame1Data[NavSatNo].af2	=temp_frame1.af2;
	NavSubFrame1Data[NavSatNo].URA	=temp_frame1.URA;
	NavSubFrame1Data[NavSatNo].Toc	=temp_frame1.Toc;
	NavSubFrame1Data[NavSatNo].Tgd	=temp_frame1.Tgd;
	NavSubFrame1Data[NavSatNo].MD	=temp_frame1.MD;
	NavSubFrame1Data[NavSatNo].IODEC=temp_frame1.IODEC;
	NavSubFrame1Data[NavSatNo].Cuc	=temp_frame1.Cuc;
	NavSubFrame1Data[NavSatNo].Cus	=temp_frame1.Cus;
	NavSubFrame1Data[NavSatNo].Cic	=temp_frame1.Cic;
	NavSubFrame1Data[NavSatNo].Cis	=temp_frame1.Cis;
	NavSubFrame1Data[NavSatNo].Crc	=temp_frame1.Crc;
	NavSubFrame1Data[NavSatNo].Crs	=temp_frame1.Crs;
	NavSubFrame1Data[NavSatNo].IDOT=temp_frame1.IDOT;
	NavSubFrame1Data[NavSatNo].TOWC1=temp_frame1.TOWC1;
	NavSubFrame1Data[NavSatNo].Sflag = temp_frame1.Sflag;
	NavSubFrame1Data[NavSatNo].L5flag = temp_frame1.L5flag;

	return;
}

void VerifyCopyFrameTwoData(int NavSatNo)
{

	// Check if the Alert Flag is set
	if (temp_frame2.Alert == 1)
		return ; // Do not Copy the data

	// Doubt : Whether the  L5 Flag  extracted in Frame 1 is applicable for Frame 2 Data
	temp.TOW = temp_frame2.TOWC2;
	NavSubFrame2Data[NavSatNo].Mo=temp_frame2.Mo;
	NavSubFrame2Data[NavSatNo].Toe=temp_frame2.Toe;
	NavSubFrame2Data[NavSatNo].e=temp_frame2.e;
	NavSubFrame2Data[NavSatNo].A=temp_frame2.A;
	NavSubFrame2Data[NavSatNo].Omega=temp_frame2.Omega;
	NavSubFrame2Data[NavSatNo].w=temp_frame2.w;
	NavSubFrame2Data[NavSatNo].OmegaDot=temp_frame2.OmegaDot;
	NavSubFrame2Data[NavSatNo].Io=temp_frame2.Io;
	NavSubFrame2Data[NavSatNo].TOWC2=temp_frame2.TOWC2;

	return;
}

void VerifyCopyFrameThreeFourData(int NavSatNo)
{
	NavSubFrame3_4Data[NavSatNo].PRNID=temp_frame3_4.PRNID;
	NavSubFrame3_4Data[NavSatNo].MSGID=temp_frame3_4.MSGID;
	NavSubFrame3_4Data[NavSatNo].TOWC34=temp_frame3_4.TOWC34;
	NavSubFrame3_4Data[NavSatNo].Alert34=temp_frame3_4.Alert34;
	NavSubFrame3_4Data[NavSatNo].Autonav34=temp_frame3_4.Autonav34;
	NavSubFrame3_4Data[NavSatNo].countutc=temp_frame3_4.countutc;
	return;
}// End of the Subroutine

void VerifyCopyMesssgeNine()
{

	temp_UTCCorr.A0utc=temp_UTCCorr.A0utc*s35;

	NavUTCCorr.A0utc=temp_UTCCorr.A0utc;
	NavUTCCorr.A1utc=temp_UTCCorr.A1utc;
	NavUTCCorr.A2utc=temp_UTCCorr.A2utc;
	NavUTCCorr.delTls=temp_UTCCorr.delTls;
	NavUTCCorr.Toutc=temp_UTCCorr.Toutc;
	NavUTCCorr.WNoutc=temp_UTCCorr.WNoutc;
	NavUTCCorr.WNlsf=temp_UTCCorr.WNlsf;
	NavUTCCorr.DN=temp_UTCCorr.DN;
	NavUTCCorr.delTlsf=temp_UTCCorr.delTlsf;

	NavUTCCorr.A0=temp_UTCCorr.A0;
	NavUTCCorr.A1=temp_UTCCorr.A1;
	NavUTCCorr.A2=temp_UTCCorr.A2;
	NavUTCCorr.Tot=temp_UTCCorr.Tot;
	NavUTCCorr.WNot=temp_UTCCorr.WNot;
	NavUTCCorr.GNSSID=temp_UTCCorr.GNSSID;
	return;
}// End of the subroutine

void VerifyCopyMessageEleven()
{
	temp_Iono_Corr.alpha0=temp_Iono_Corr.alpha0*s30;

	//Transferring the extracted data in the main data structure
	NavIonoCorrction.alpha0=temp_Iono_Corr.alpha0;
	NavIonoCorrction.alpha1=temp_Iono_Corr.alpha1;
	NavIonoCorrction.alpha2=temp_Iono_Corr.alpha2;
	NavIonoCorrction.alpha3=temp_Iono_Corr.alpha3;
	NavIonoCorrction.beta0=temp_Iono_Corr.beta0;
	NavIonoCorrction.beta1=temp_Iono_Corr.beta1;
	NavIonoCorrction.beta2=temp_Iono_Corr.beta2;
	NavIonoCorrction.beta3=temp_Iono_Corr.beta3;
	return ;
}// End of the subroutine


void VerifyCopyFrameMessageTwentySix(int IDecodedIP [37], int NavSatNo)
{
	temp_UTCCorr.A0utc=temp_UTCCorr.A0utc*s35;
	NavUTCCorr.A0utc=temp_UTCCorr.A0utc;
	NavUTCCorr.A1utc=temp_UTCCorr.A1utc;
	NavUTCCorr.A2utc=temp_UTCCorr.A2utc;
	NavUTCCorr.delTls=temp_UTCCorr.delTls;
	NavUTCCorr.Toutc=temp_UTCCorr.Toutc;
	NavUTCCorr.WNoutc=temp_UTCCorr.WNoutc;
	NavUTCCorr.WNlsf=temp_UTCCorr.WNlsf;
	NavUTCCorr.DN=temp_UTCCorr.DN;
	NavUTCCorr.delTlsf=temp_UTCCorr.delTlsf;
	NavUTCCorr.A0=temp_UTCCorr.A0;
	NavUTCCorr.A1=temp_UTCCorr.A1;
	NavUTCCorr.A2=temp_UTCCorr.A2;
	NavUTCCorr.Tot=temp_UTCCorr.Tot;
	NavUTCCorr.WNot=temp_UTCCorr.WNot;
	NavUTCCorr.GNSSID=temp_UTCCorr.GNSSID;
	return ;

}// End of the Subroutine

