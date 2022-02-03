extern athreadManager blas_atm;
blasThreadData blas_thread_state[MAX_NUMBER_OF_THREADS];

double blas_dotProduct (int N, double* A, double* B)
{
	// break into K dot-products.
	//   e.g. K = N/1024.
	
	for(I = 0; I < K; I++)
	{
		// initialize K data structures.

		// create thread with argument being the data structure pointer
		// and function being blas_dotProductInner
	}

	runMasterLoop (K);

	// assemble the result from the K threads..
	double ret_val = 0.0;
	for(I = 0;  I < K; I++)
	{
		ret_val += *((double*) blas_thread_state[K].arg_8);
	}
	return(ret_val);
}


void runLoop ()
{
	while(1)
	{
		// select and run thread....
		

		athreadReturn (selected_thread);
	}
}

void runMasterLoop (K)
{
	while(1)
	{
		// select and run thread....
		athreadReturn (selected_thread);
		if(all_threads_have_finished(K))
			break;
	}
	return;
}


