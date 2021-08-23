Notes
-------------

### Components
0. Read user configuration - yaml file -- DONE
1. Linking
   1. Linker Script
      * To compile each program into a separate text/data region.
   1. Linking (of setup_page_tables.s and init.s etc.)
      * Only with the first program which will run on thread (0,0).
2. Co-operative scheduler that will schedule processes on a thread.    
   * The scheduler starts the first process.
   * The processes call the scheduler at appropriate places,
     and the scheduler schedules the next process in the queue.
   * If a process ends, it returns to the scheduler which may
      * Stop the process forever.
      * Or restart the process.
2. Malloc library (bget: <https://www.fourmilab.ch/bget/>)
   * Defines an API to access the malloc logic.
   * Allocates a location for a locking variable.
   * Allocates a chunk of memory from which the allocations are made.
3. Message Queues
   * defines an API to use the queue.
   * allocates an array of locking variables (each for one queue).
   * allocates the space for each queue.
4. Lock/Release (Synchronization) procedures
   * allocates an array of locking variables
6. How to find the size of text and data sections?
   <https://medium.com/analytics-vidhya/exploring-elf-files-using-pyelftools-93bb7665cce3>
   use the `size` command :)
8. Read cortos documentation.


## Stage 1
Objective: To be able to run N programs on N threads without any communication.

## Stage 2
Objective: To be able to run N programs on N threads with a shared lock.

## Stage 2.5
Objective: To be able to run N programs on N threads with M shared locks.

## Stage 3
Objective: To be able to run N programs on N threads with a fixed shared queue.  

## Stage 3.5
Objective: To be able to run N programs on N threads with a variable shared queue.

## Stage 4
Objective: To be able to run N programs on N threads with M shared queues.

## Stage 5
Objective: To be able to run N programs on N threads with M shared queues,
           and with malloc functionality (bget?).

## Stage 6
Objective: To be able to run N programs on X threads with M shared queues.
           (will use co-operative scheduler, where the main function of processes
           return to the scheduler.)

## Stage 6.5
Objective: To be able to run N programs on X threads with M shared queues.
           (will use co-operative scheduler, where processes yield to the
            scheduler at specific program points)


Update:
Reached Stage 6 (by skipping stage 3.5)
Stage 6.5 is for a later stage. For now stage 6 suffices for our work.


Memory Layout Notes
-------------------------
Contents:
* programs (text, data), and their stack
* synchronization variables
* space for queues
* malloc area
* sync, queue library programs link with each user program.
* malloc service runs along with one of the user program.


    0x00000000  part of init.s starts here      (addr: 0)
    0x00000000  allocation space..............  (addr: pre-computed)
    0x00000000   data: reserved (~256 bytes)    (addr: pre-computed)
    0x00000000   data: sync variables           (addr: pre-computed)
    0x00000000   data: queue                    (addr: pre-computed)
    0x00000000  rest of the init.s is here      (addr: pre-computed)
    0x00000000  programs (text, data)           (addr: pre-computed)
    0x00000000    program: 0 (text, data)       (addr: pre-computed)
    0x00000000    program: 1 (text, data)       (addr: pre-computed)
    0x00000000    program: 2 (text, data)       (addr: pre-computed)
    0x00000000      data: malloc area (data)    (addr: locally-known)
    0x00000000  stack area                      (addr: pre-computed)
    0x00000000    stack: program0               (addr: pre-computed)
    0x00000000    stack: program1               (addr: pre-computed)
    0x00000000    stack: program2               (addr: pre-computed)
    0x00000000  unused area                     (addr: pre-computed)

There can be some unused gaps in the memory image due to memory alignment etc.

Queries:
1. Are memory locations zero by default? (Anyway don't assume it to be.)
2. What if one of the thread halts?
   If programs are lesser than the no. of threads
   then should the 'empty' threads loop?
3. `call main` works but `call 0x2` doesn't work. (PC + (4 * 0x2))
   Hence, need to hack the binary output as follows:
   
          call here_label    ! generates 0x40000002 (which is then modified)
          nop
        here_label:
4. Get size of elf text sections and data sections.
   



Using bottle templating system
---------------------------------
* <https://bottlepy.org/docs/dev/tutorial.html#tutorial-templates>
* <https://bottlepy.org/docs/dev/stpl.html>

