uint32_t on_heap;

int foo ()
{
	uint32_t on_stack;

	// this can use on_heap and on_stack.
}


int bar ()
{
	// this can use on_heap
}

