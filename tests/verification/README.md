 
 
 The usage of the validation script to run the tests is given below. 
 
 It takes a .vprj file, which should be present in the directory, as its input.
 
 
 -----------------------------------------------------------------------------------------------------------
 USAGE:
        validation_outer_env_v3.py [MODEL] [OPTIONS] [-t TIMEOUT_IN_SECONDS] [-j JOBS_TO_RUN_IN_PARALLEL]  PATHS...
 -----------------------------------------------------------------------------------------------------------
 MODEL:
      -A : Aa executable
      -C : C  executable
      -F : FPGA  executable
 ------------------------
 OPTIONS:
      -l : Generate a log of register writes
            The files are generated in trace_files/ folder
            with extension .C_trace for C model and .Aa_trace for Aa model
 
      -s : Run in single-stepping mode
            Relevant only for Aa/VHDL/FPGA model.

      -T : Generate a detailed trace of activity for each instruction 
           The trace file is generated in trace_files/ folder
            with extension .long_trace
           (CAUTION : A trace file can get very large)
 ------------------------
 CLEANUP:
      validation_outer_env_v3.py -c PATHS...
           cleans up the compiled/ log/ and trace_files/ 
           folders recursively from PATH
 -----------------------------------------------------------------------------------------------------------
