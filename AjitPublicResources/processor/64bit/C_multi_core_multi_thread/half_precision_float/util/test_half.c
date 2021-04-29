#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "half_precision_float.h"
#include "fpunit_exec_exec_aa_c_model.h"

int main(int argc, char* argv[])
{

	float step = 0.1;

	int I, J;
	float xmin = - step* 50;
	float ymin = - step* 50;

	float two = 2.0;
	half htwo  = floatToHalf(two);

	float onebytwo = 0.5;
	half honebytwo = floatToHalf(onebytwo);

	float bigpowx = 1.0;
	half  hbigpowx =  floatToHalf(bigpowx);

	float smallpowx = 1.0;
	half  hsmallpowx = floatToHalf(smallpowx);

	

	half hx;
	half hy;
	half hsum = 0;
	half hdiff;
	half hprod = 1;

		
	float max_error = 0;
	for(I=0; I < 100; I++)
	{
		hbigpowx = mulHalf(hbigpowx, htwo);
		fprintf(stdout,"(2.0**%d) = %e\n", I+1, halfToFloat(hbigpowx));

		hsmallpowx = mulHalf(hsmallpowx, honebytwo);
		fprintf(stdout,"(0.5**%d) = %e\n", I+1, halfToFloat(hsmallpowx));

		float x = xmin + I*step;
		hx = floatToHalf(x);
		fprintf(stdout,"(float) (half) %f = %f\n", x, halfToFloat(hx));


		for(J = 0; J < 100; J++)
		{
			float y = ymin + J*step;
			hy = floatToHalf(y);

			hsum  = addHalf(hx,hy);
			hdiff = subHalf(hx,hy);
			hprod = mulHalf(hx,hy);

			float esum = (x + y) - halfToFloat(hsum);
			fprintf(stdout,"%f + %f = %f (error=%f)\n",
					halfToFloat(hx), halfToFloat(hy), halfToFloat(hsum),esum);
		
			max_error = ((fabs(esum) > max_error) ? fabs(esum) : max_error);	
					
			float ediff = (x - y) - halfToFloat(hdiff);
			fprintf(stdout,"%f - %f = %f (error=%f)\n",
					halfToFloat(hx), halfToFloat(hy), halfToFloat(hdiff), ediff);
			max_error = ((fabs(ediff) > max_error) ? fabs(ediff) : max_error);	
					
			float emul = (x * y) - halfToFloat(hprod);
			fprintf(stdout,"%f * %f = %f (error=%f)\n",
					halfToFloat(hx), halfToFloat(hy), halfToFloat(hprod), emul);
			max_error = ((fabs(emul) > max_error) ? fabs(emul) : max_error);	
		}
	}

	fprintf(stderr,"MAX ERROR = %f\n", max_error);
	return(0);
}

