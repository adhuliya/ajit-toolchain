
% setdefault("os", "cortos")

% include("init/init_header.s")

% include("init/init_threads_setup.s")

% include("init/init_page_table_mmu_wait.s")

% include("init/init_threads_start.s")

% include("init/init_init_routines.s")

% include("init/init_footer.s")

