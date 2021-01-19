#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "half_precision_float.h"

int main(int argc, char* argv[])
{

	if(argc < 2)
	{
		fprintf(stderr,"Usage: %s <exp-width> \n", argv[0]);
		return(1);
	}

	int exp_width = atoi(argv[1]);
	fprintf(stderr,"Exp-width=%d\n", exp_width);

	float step = 0.1;

	int I, J;
	float xmin = - step* 50;
	float ymin = - step* 50;

	float two = 2.0;
	half htwo;
	initHalf(&htwo, exp_width,0);
	floatToHalf(two, &htwo);

	float onebytwo = 0.5;
	half honebytwo;
	initHalf(&honebytwo, exp_width,0);
	floatToHalf(onebytwo, &honebytwo);

	float bigpowx = 1.0;
	half  hbigpowx;
	initHalf (&hbigpowx, exp_width,0);
	floatToHalf(bigpowx, &hbigpowx);

	float smallpowx = 1.0;
	half  hsmallpowx;
	initHalf (&hsmallpowx, exp_width,0);
	floatToHalf(smallpowx, &hsmallpowx);

	

	half hx;
	initHalf(&hx, exp_width, 0);

	half hy;
	initHalf(&hy, exp_width, 0);

	half hsum, hdiff, hprod;
	initHalf(&hsum, exp_width, 0);
	initHalf(&hdiff, exp_width, 0);
	initHalf(&hprod, exp_width, 0);

	for(I=0; I < 100; I++)
	{
		mulHalf(&hbigpowx, &htwo, &hbigpowx);
		fprintf(stdout,"(2.0**%d) = %e\n", I+1, halfToFloat(&hbigpowx));

		mulHalf(&hsmallpowx, &honebytwo, &hsmallpowx);
		fprintf(stdout,"(0.5**%d) = %e\n", I+1, halfToFloat(&hsmallpowx));

		float x = xmin + I*step;
		floatToHalf(x,&hx);
		fprintf(stdout,"(float) (half) %f = %f\n", x, halfToFloat(&hx));
		for(J = 0; J < 100; J++)
		{
			float y = ymin + J*step;
			floatToHalf(y,&hy);

			addHalf(&hx,&hy,&hsum);
			subHalf(&hx,&hy,&hdiff);
			mulHalf(&hx,&hy,&hprod);

			fprintf(stdout,"%f + %f = %f (error=%f)\n",
					halfToFloat(&hx), halfToFloat(&hy), halfToFloat(&hsum),
					(x + y) - halfToFloat(&hsum));
			fprintf(stdout,"%f - %f = %f (error=%f)\n",
					halfToFloat(&hx), halfToFloat(&hy), halfToFloat(&hdiff),
					(x - y) - halfToFloat(&hdiff));
			fprintf(stdout,"%f * %f = %f (error=%f)\n",
					halfToFloat(&hx), halfToFloat(&hy), halfToFloat(&hprod),
					(x * y) - halfToFloat(&hprod));
		}
	}

	return(0);
}

