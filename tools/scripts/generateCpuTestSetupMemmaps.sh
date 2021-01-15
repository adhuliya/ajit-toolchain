#!/bin/bash
convertMemmapToIntBitVectorForm < $1 > cpu_test_setup_memmap_icache.txt
convertMemmapToIntBitVectorForm < $1 > cpu_test_setup_memmap_dcache.txt
