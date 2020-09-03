#include <stdint.h>
#include "Opcodes.h"
#include "FpExceptions.h"
#include "Ancillary.h"

uint8_t isNaN32(float op)
{
	uint32_t NaN_single = 0x7F800000;
	uint32_t op_int  = _BITCAST_(uint32_t, op);
	op_int = op_int & NaN_single;
	if(op_int == NaN_single) 
		return 1;
	return 0;
}

uint8_t isNaN64(double op)
{
	uint64_t NaN_double = 0x7FF0000000000000;
	uint64_t op_int  = _BITCAST_(uint64_t, op);
	op_int = op_int & NaN_double;
	if(op_int == NaN_double) 
		return 1;
	return 0;
}

/* Chekking operand is a sNaN
 * Added by Ashfaque Ahammed
 *
 * A signalling NaN (NANS) is represented by any bit pattern between 7F800001 and 7FBFFFFF or between FF800001 and FFBFFFFF
 * and double precision between 7FF0000000000001 and 7FF7FFFFFFFFFFFF or between FFF0000000000001 and FFF7FFFFFFFFFFFF
 *
 * A quiet NaN (NANQ) is represented by any bit pattern between 7FC00000 and 7FFFFFFF or between FFC00000 and FFFFFFFF
 * and double precison between 7FF8000000000000 and 7FFFFFFFFFFFFFFF or between FFF8000000000000 and FFFFFFFFFFFFFFFF
 *
 */
uint8_t isSNaN32(float op)
{
	uint32_t sNaN_single1_min = 0x7F800001;
	uint32_t sNaN_single1_max = 0x7FBFFFFF;
	uint32_t sNaN_single2_min = 0xFF800001;
	uint32_t sNaN_single2_max = 0xFFBFFFFF;
	uint32_t op_int  = _BITCAST_(uint32_t, op);
	if((op_int >= sNaN_single1_min && op_int <= sNaN_single1_max) || (op_int >= sNaN_single2_min && op_int <= sNaN_single2_max))
		return 1;
	return 0;
}
uint8_t isSNaN64(double op)
{
	uint64_t sNaN_double1_min = 0x7FF0000000000001;
	uint64_t sNaN_dobule1_max = 0x7FF7FFFFFFFFFFFF;
	uint64_t sNaN_double2_min = 0xFFF0000000000001;
	uint64_t sNaN_double2_max = 0xFFF7FFFFFFFFFFFF;
	uint64_t op_int  = _BITCAST_(uint64_t, op);
	if((op_int >= sNaN_double1_min && op_int <= sNaN_dobule1_max) || (op_int >= sNaN_double2_min && op_int <= sNaN_double2_max)) 
		return 1;
	return 0;
}
uint8_t isQNaN32(float op)
{
	return(isNaN32(op) && !isSNaN32(op));
}

uint8_t isQNaN64(double op)
{
	return(isNaN64(op) && !isSNaN64(op));
}
uint8_t isPosZero32(float op)
{
	uint32_t tv = *((uint32_t*) &op);
	return (tv == 0);
}
uint8_t isPosZero64(double op)
{
	uint64_t tv = *((uint64_t*) &op);
	return (tv == 0);
}
uint8_t isNegZero32(float op)
{
	uint32_t tv = *((uint32_t*) &op);
	uint32_t tv_sign = (tv >> 31);
	return (tv_sign && ((tv << 1) == 0));
}

uint8_t isNeg32(float op)
{
	uint32_t tv = *((uint32_t*) &op);
	uint32_t tv_sign = (tv >> 31);
	return(tv_sign);
}

uint8_t isNegZero64(double op)
{
	uint64_t tv = *((uint64_t*) &op);
	uint64_t tv_sign = (tv >> 63);
	uint64_t tvval = (tv << 1);
	return (tv_sign && (tvval == 0));
}

uint8_t isNeg64(double op)
{
	uint64_t tv = *((uint64_t*) &op);
	uint64_t tv_sign = (tv >> 63);
	return(tv_sign);
}

uint8_t isPosInf32(float op)
{
	uint32_t tv = *((uint32_t*) &op);
	uint32_t mantissa = (tv & 0x7fffff);
	uint32_t exponent = (tv >> 23) & 0xff;
	uint32_t sign_flag = (tv >> 31);

	return(!sign_flag && (exponent == 0xff) & (mantissa == 0));
}

uint8_t isPosInf64(double op)
{
	uint64_t tv = *((uint64_t*) &op);
	uint64_t mantissa_mask = 0;
	mantissa_mask = ((~mantissa_mask) >> 12);
	uint64_t mantissa = (tv & mantissa_mask);
	uint64_t exponent = (tv >> 52) & 0x7ff;
	uint64_t sign_flag = (tv >> 63);

	return(!sign_flag && (exponent == 0x7ff) & (mantissa == 0));
}

uint8_t isNegInf32(float op)
{
	uint32_t tv = *((uint32_t*) &op);
	uint32_t mantissa = (tv & 0x7fffff);
	uint32_t exponent = (tv >> 23) & 0xff;
	uint32_t sign_flag = (tv >> 31);

	return(sign_flag && (exponent == 0xff) & (mantissa == 0));
}


uint8_t isNegInf64(double op)
{
	uint64_t tv = *((uint64_t*) &op);
	uint64_t mantissa_mask = 0;
	mantissa_mask = ((~mantissa_mask) >> 12);
	uint64_t mantissa = (tv & mantissa_mask);
	uint64_t exponent = (tv >> 52) & 0x7ff;
	uint64_t sign_flag = (tv >> 63);

	return(sign_flag && (exponent == 0x7ff) & (mantissa == 0));
}

uint8_t isPosDenormal32(float op)
{
	uint32_t tv = *((uint32_t*) &op);
	uint32_t mantissa = (tv & 0x7fffff);
	uint32_t exponent = (tv >> 23) & 0xff;
	uint32_t sign_flag = (tv >> 31);

	return(!sign_flag && (exponent == 0) && (mantissa != 0));
}

uint8_t isPosDenormal64(double op)
{
	uint64_t tv = *((uint64_t*) &op);
	uint64_t mantissa_mask = 0;
	mantissa_mask = ((~mantissa_mask) >> 12);
	uint64_t mantissa = (tv & mantissa_mask);
	uint64_t exponent = (tv >> 52) & 0x7ff;
	uint64_t sign_flag = (tv >> 63);

	return(!sign_flag && (exponent == 0) & (mantissa != 0));
}

uint8_t isNegDenormal32(float op)
{
	uint32_t tv = *((uint32_t*) &op);
	uint32_t mantissa = (tv & 0x7fffff);
	uint32_t exponent = (tv >> 23) & 0xff;
	uint32_t sign_flag = (tv >> 31);

	return(sign_flag && (exponent == 0) && (mantissa != 0));

}

uint8_t isNegDenormal64(double op)
{
	uint64_t tv = *((uint64_t*) &op);
	uint64_t mantissa_mask = 0;
	mantissa_mask = ((~mantissa_mask) >> 12);
	uint64_t mantissa = (tv & mantissa_mask);
	uint64_t exponent = (tv >> 52) & 0x7ff;
	uint64_t sign_flag = (tv >> 63);

	return(sign_flag && (exponent == 0) & (mantissa != 0));
}

uint8_t isFpInvalidOp(Opcode op, float f1_s, float f2_s, double f1_d, double f2_d)
{
	uint8_t ret_val = 0;

	uint8_t is_pos_zero_f1_s = isPosZero32(f1_s);
	uint8_t is_pos_zero_f2_s = isPosZero32(f2_s);
	uint8_t is_pos_zero_f1_d = isPosZero64(f1_d);
	uint8_t is_pos_zero_f2_d = isPosZero64(f2_d);

	uint8_t is_neg_zero_f1_s = isNegZero32(f1_s);
	uint8_t is_neg_zero_f2_s = isNegZero32(f2_s);
	uint8_t is_neg_zero_f1_d = isNegZero64(f1_d);
	uint8_t is_neg_zero_f2_d = isNegZero64(f2_d);

	uint8_t is_pos_inf_f1_s = isPosInf32(f1_s);
	uint8_t is_pos_inf_f2_s = isPosInf32(f2_s);
	uint8_t is_pos_inf_f1_d = isPosInf64(f1_d);
	uint8_t is_pos_inf_f2_d = isPosInf64(f2_d);

	uint8_t is_neg_inf_f1_s = isNegInf32(f1_s);
	uint8_t is_neg_inf_f2_s = isNegInf32(f2_s);
	uint8_t is_neg_inf_f1_d = isNegInf64(f1_d);
	uint8_t is_neg_inf_f2_d = isNegInf64(f2_d);

	uint8_t is_qnan_f1_s = isQNaN32(f1_s);
	uint8_t is_qnan_f2_s = isQNaN32(f2_s);
	uint8_t is_qnan_f1_d = isQNaN64(f1_d);
	uint8_t is_qnan_f2_d = isQNaN64(f2_d);

	uint8_t is_snan_f1_s = isSNaN32(f1_s);
	uint8_t is_snan_f2_s = isSNaN32(f2_s);
	uint8_t is_snan_f1_d = isSNaN64(f1_d);
	uint8_t is_snan_f2_d = isSNaN64(f2_d);

	uint8_t is_neg_f1_s = isNeg32(f1_s);
	uint8_t is_neg_f1_d = isNeg64(f1_d);



	// IEEE-754 Exception
	switch (op)
	{
		case _FMULs_:
			// zero X infinity
			ret_val = ((is_pos_zero_f1_s || is_neg_zero_f1_s) && (is_pos_inf_f2_s || is_neg_inf_f2_s)) ||
					((is_pos_zero_f2_s || is_neg_zero_f2_s) && (is_pos_inf_f1_s || is_neg_inf_f1_s));
			ret_val = ret_val || is_snan_f1_s || is_snan_f2_s;
			break;
		case _FADDs_:
			// infinity - infinity
			// -infinity + infinity
			ret_val = ((is_pos_inf_f1_s & is_neg_inf_f2_s) || (is_neg_inf_f1_s & is_pos_inf_f2_s));
			ret_val = ret_val || is_snan_f1_s || is_snan_f2_s;
			break;
		case _FSUBs_:
			// infinity - infinity
			// -infinity - (-infinity)
			ret_val = ((is_pos_inf_f1_s & is_pos_inf_f2_s) || (is_neg_inf_f1_s & is_neg_inf_f2_s));
			ret_val = ret_val || is_snan_f1_s || is_snan_f2_s;
			break;
		case _FDIVs_:
			// 0/0
			// infinity/infinity
			ret_val = ((is_pos_zero_f1_s || is_neg_zero_f1_s) && (is_pos_zero_f2_s || is_neg_zero_f2_s)) ||
					((is_pos_inf_f2_s || is_neg_inf_f2_s) && (is_pos_inf_f1_s || is_neg_inf_f1_s));
			ret_val = ret_val || is_snan_f1_s || is_snan_f2_s;
			break;
		case _FSQRTs_:
			// sqrt (negative) 
			ret_val = (is_snan_f1_s || (is_neg_f1_s && !(is_pos_zero_f1_s || is_neg_zero_f1_s)));
			break;
		case _FCMPs_:
			// at least one snan.
			ret_val = (is_snan_f1_s || is_snan_f2_s);
			break;
		case _FCMPEs_:
			// at least one snan or qnan.
			ret_val = (is_qnan_f1_s || is_qnan_f2_s || is_snan_f1_s || is_snan_f2_s);
			break;
		case _FsTOi_:
			ret_val = (is_qnan_f1_s || is_snan_f1_s);
			break;
		case _FMULd_:
			// zero X infinity
			ret_val = ((is_pos_zero_f1_d || is_neg_zero_f1_d) && (is_pos_inf_f2_d || is_neg_inf_f2_d)) ||
					((is_pos_zero_f2_d || is_neg_zero_f2_d) && (is_pos_inf_f1_d || is_neg_inf_f1_d));
			ret_val = ret_val || is_snan_f1_d || is_snan_f2_d;
			break;
		case _FADDd_:
			// infinity - infinity
			// -infinity + infinity
			ret_val = ((is_pos_inf_f1_d & is_neg_inf_f2_d) || (is_neg_inf_f1_d & is_pos_inf_f2_d));
			ret_val = ret_val || is_snan_f1_d || is_snan_f2_d;
			break;
		case _FSUBd_:
			// infinity - infinity
			// -infinity - (-infinity)
			ret_val = is_snan_f1_d || is_snan_f2_d;
			ret_val = ret_val || ((is_pos_inf_f1_d & is_pos_inf_f2_d) || (is_neg_inf_f1_d & is_neg_inf_f2_d));
			break;
		case _FDIVd_:
			// 0/0
			// infinity/infinity
			ret_val = is_snan_f1_d || is_snan_f2_d ||
					((is_pos_zero_f1_d || is_neg_zero_f1_d) && (is_pos_zero_f2_d || is_neg_zero_f2_d)) ||
					((is_pos_inf_f2_d || is_neg_inf_f2_d) && (is_pos_inf_f1_d || is_neg_inf_f1_d));
			break;
		case _FSQRTd_:
			// sqrt (negative)
			ret_val = ((is_neg_f1_d & !(is_pos_zero_f1_d || is_neg_zero_f1_d)) || is_snan_f1_d);
			break;
		case _FCMPd_:
			// at least one snan.
			ret_val = (is_snan_f1_d || is_snan_f2_d);
			break;
		case _FCMPEd_:
			// at least one snan or qnan.
			ret_val = (is_qnan_f1_d || is_qnan_f2_d || is_snan_f1_d || is_snan_f2_d);
			break;
		case _FdTOi_:
			ret_val = (is_qnan_f1_d || is_snan_f1_d);
			break;
		case _FdTOs_:
			ret_val = is_snan_f1_d;
			break;
		case _FsTOd_:
			ret_val = is_snan_f1_s;
			break;
		default:
			break;
	}
	return(ret_val);
} 

uint8_t isNvmSet(uint32_t fsr)
{
	uint8_t ret_val = (fsr >> 27) & 0x1;
	return(ret_val);
}

/* Chekking operand is a sNaN
 * Added by Ashfaque Ahammed
 *
 * A signalling NaN (NANS) is represented by any bit pattern between 7F800001 and 7FBFFFFF or between FF800001 and FFBFFFFF
 * and double precision between 7FF0000000000001 and 7FF7FFFFFFFFFFFF or between FFF0000000000001 and FFF7FFFFFFFFFFFF
 *
 * A quiet NaN (NANQ) is represented by any bit pattern between 7FC00000 and 7FFFFFFF or between FFC00000 and FFFFFFFF
 * and double precison between 7FF8000000000000 and 7FFFFFFFFFFFFFFF or between FFF8000000000000 and FFFFFFFFFFFFFFFF
 *
 */
uint8_t check_sNaN32(float op)
{
	uint32_t sNaN_single1_min = 0x7F800001;
	uint32_t sNaN_single1_max = 0x7FBFFFFF;
	uint32_t sNaN_single2_min = 0xFF800001;
	uint32_t sNaN_single2_max = 0xFFBFFFFF;
	uint32_t op_int  = _BITCAST_(uint32_t, op);
	if((op_int >= sNaN_single1_min && op_int <= sNaN_single1_max) || (op_int >= sNaN_single2_min && op_int <= sNaN_single2_max))
		return 1;
	return 0;
}

uint8_t check_sNaN64(double op)
{
	uint64_t sNaN_double1_min = 0x7FF0000000000001;
	uint64_t sNaN_dobule1_max = 0x7FF7FFFFFFFFFFFF;
	uint64_t sNaN_double2_min = 0xFFF0000000000001;
	uint64_t sNaN_double2_max = 0xFFF7FFFFFFFFFFFF;
	uint64_t op_int  = _BITCAST_(uint64_t, op);
	if((op_int >= sNaN_double1_min && op_int <= sNaN_dobule1_max) || (op_int >= sNaN_double2_min && op_int <= sNaN_double2_max)) 
		return 1;
	return 0;
}

/***************************************************************/

