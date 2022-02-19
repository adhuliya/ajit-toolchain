athreadManager blas_atm;

int main_00 ()
{
	initAthreadManager(&blas_atm);

	// will ask for which test is to be run
	//
	// a  dot-product 1024 point dot-product
	// b  matrix-vector-product 1024x1024 matrix, 1024 point vector.
	// c  daxpy
	// d  ....
	

	// run the selected test
	// prepare the test..
	// populate the matrices, populate the vectors etc...
	generateTestData (....);
	// timer before
	blas_dotProduct(N,A,B);
	// timer after
}


int main_01 ()
{
	runLoop ();
}


