! init_00.s for linking with thread 0,0 only

% include("build_init/parts/init_header.s")

% include("build_init/parts/init_allocate.s")

% include("build_init/parts/init_threads_setup.s")

% include("build_init/parts/init_page_table_mmu_wait.s")

% include("build_init/parts/init_threads_start.s")

% include("build_init/parts/init_footer.s")

