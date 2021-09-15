int rsum (int N)
{
	int rval = 0;
	if (N > 0)
		rval = 1 + rsum(N-1);
	return(rval);
}

