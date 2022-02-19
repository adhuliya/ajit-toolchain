Test Examples
=================
# TODO: not updated for cortos2

* 001 to 049: Single Core, Single Thread
* 050 to 099: Multithreads, no collaboration
* 100 to 149: Multithreads, only with synchronization
* 150 to 199: Multithreads, only with queues
* 200 to 249: Multithreads, only with bget
* 250 to 299: Multithreads, with sync, queue, and bget


## What constitutes a project?
A project consists of the following necessary components,

* A set of C source files and header files. Currently, CoRTOS doesn't support
  sub-directories of source files.
* A `main()` function to enable the building,
  although for CoRTOS `main()` is not required.
* A `config.yaml` file to specify the necessary details of the project.
  A quick introduction to yaml file format can be found
  [here](https://www.youtube.com/watch?v=cdLNKUoMc6c).

  The details of the `config.yaml` file can be studied using the examples
  in this directory. Specifically the following config files are a good
  reference point,
  
   * [./example_001/config.yaml](example_001/config.yaml)
   * [./example_050/config.yaml](example_050/config.yaml)
   * [./example_100/config.yaml](example_100/config.yaml)
   * [./example_150/config.yaml](example_150/config.yaml)
   * [./example_200/config.yaml](example_200/config.yaml)
   * [./example_250/config.yaml](example_250/config.yaml)


## How to run the examples?
In each example_XXX project directory do the following,

    ./build.sh  # builds the project
    ./run.sh    # runs the project


## How a cortos project is built?

Once the user invokes `cortos build` command on the project,
the `cortos` program reads the configuration from `config.yaml` file.
Then a directory `cortos_build/` is created in the current directory
and is populated with all the necessary (and some dynamically generated)
files to build the project.
The user's `*.c` and `*.h` files are also
copied into the `cortos_build/` dir.


## What API does CoRTOS provide?
The API and its documentation can be read from `cortos.h` file.
This file can be found in `cortos_build/` directory once the `cortos build`
has been invoked.
This is a dynamically generated file hence to view it, one has to 
create a skeleton project with a `config.yaml` and a `.c` file to
be able to invoke the `cortos build` command.
Any one of the examples in this directory can also be used for this purpose.

Although the `cortos.h` is dynamically generated file, a sample output
is provided below for convenience. For the most up-to-date content
follow in the instructions given above.


    // NOTE:
    // All symbols for cortos' internal use are prefixed with `__`,
    // and can be mostly found in `__cortos.h` header file.
    
    #ifndef CORTOS_H
    #define CORTOS_H
    
    #include <stdint.h>
    
    
    ////////////////////////////////////////////////////////////////////////////////
    // BLOCK START: cortos_memory_layout
    ////////////////////////////////////////////////////////////////////////////////
    
    // First Address 0x0:
    // Few instruction to start the bootup initializtion.
    
    // Memory region reserved for cortos' misc internal use.
    #define RESERVED_MEM_START_ADDR 56
    #define RESERVED_MEM_END_ADDR 311
    
    // Details related to the user scratch space.
    #define SCRATCH_SPACE_START_ADDR 312
    #define SCRATCH_SPACE_END_ADDR 1335
    #define TOTAL_SCRATCH_SPACE_IN_BYTES 1024
    
    // Details of the cortos reserved lock vars (not available to the user)
    #define RES_LOCK_VARS_START_ADDR 1336
    #define RES_LOCK_VARS_END_ADDR 1463
    #define MAX_RES_LOCK_VARS 32
    
    // Details of the lock vars available to the user.
    #define LOCK_VARS_START_ADDR 1464
    #define LOCK_VARS_END_ADDR 1591
    #define MAX_LOCK_VARS 32
    
    // Details of the lock vars available to the user.
    #define Q_LOCK_VARS_START_ADDR 1592
    #define Q_LOCK_VARS_END_ADDR 1719
    #define MAX_Q_LOCK_VARS 32
    
    // Details of the queue header array (one queue header per queue).
    #define Q_HEADERS_START_ADDR 1720
    #define Q_HEADERS_END_ADDR 2231
    #define MAX_Q_HEADERS 32
    
    // Queues available to the user (all the queues sit here).
    #define QUEUE_START_ADDR 2232
    #define QUEUE_END_ADDR 34999
    #define MAX_QUEUES 32
    #define QUEUE_MSG_SIZE_IN_BYTES 32
    #define MAX_ELEMENTS_PER_QUEUE 32
    #define MAX_QUEUE_SIZE_IN_BYTES (MAX_ELEMENTS_PER_QUEUE * QUEUE_MSG_SIZE_IN_BYTES)
    
    // Total heap space available in bytes.
    #define HEAP_START_ADDR 35000
    #define HEAP_END_ADDR 137399
    #define TOTAL_HEAP_SIZE_IN_BYTES 102400
    
    // ALL INSTRUCTIONS start after 137399:
    // 1. Logic to start all the threads.
    // 2. All user program instructions sit here.
    
    // All program stacks sit here.
    #define PROG_0_STACK_START_ADDR 3153920
    #define PROG_0_STACK_SIZE 8192
    #define PROG_1_STACK_START_ADDR 3162112
    #define PROG_1_STACK_SIZE 8192
    
    ////////////////////////////////////////////////////////////////////////////////
    // BLOCK END  : cortos_memory_layout
    ////////////////////////////////////////////////////////////////////////////////
    
    ////////////////////////////////////////////////////////////////////////////////
    // BLOCK START: cortos_locking_declarations
    ////////////////////////////////////////////////////////////////////////////////
    
    // Usage Note:
    // cortos_lock_acquire_buzy(<index: an-integer-index>);
    //   CRITICAL_SECTION_CODE...
    // cortos_lock_release(<index: an-integer-index>);
    // ----or-------or--------
    // status = cortos_lock_acquire(<index: an-integer-index>);
    // if (status == 1) {
    //   CRITICAL_SECTION_CODE...
    //   cortos_lock_release(<index: an-integer-index>);
    // }
    
    // NOTE: Use the same index to synchronize two or more threads.
    
    int cortos_lock_acquire_buzy(int index);
    int cortos_lock_acquire(int index);
    void cortos_lock_release(int index);
    
    // Reserve an unused lock variable id from cortos.
    //   It returns the lock variable id of the lock reserved.
    //   If no lock is available it returns -1.
    // Once a lock is reserved it is held by the caller,
    // until it is freed.
    int cortos_reserveLockVar();
    
    // Free a lock variable for reuse by cortos.
    void cortos_freeLockVar(int lockId);
    
    ////////////////////////////////////////////////////////////////////////////////
    // BLOCK END  : cortos_locking_declarations
    ////////////////////////////////////////////////////////////////////////////////
    
    
    ////////////////////////////////////////////////////////////////////////////////
    // BLOCK START: cortos_message_queues_declarations
    ////////////////////////////////////////////////////////////////////////////////
    
    // A cortos' queue message.
    typedef union _CortosMessage32Bytes {
      char charArr[32];
      int intArr[8];
      float floatArr[8];
      double doubleArr[4];
    
      struct {
        int a_code;
        void *a_ptr; // pointer to a location
        int *a_size; // in bytes
        int a_intArr[5];
      };
    
      struct {
        int b_code;
        int b_intArr[7];
      };
    
      struct {
        int c_code;
        char c_charArr[28];
      };
    
      struct {
        int d_code;
        int d_val1;
        double d_d1;
        double d_d2;
        double d_d3;
      };
    
    } CortosMessage;
    
    
    /* Write a CortosMessage.
      - Returns zero if the queue is full.
      - Returns non-zero if the msg was added.
    */
    int cortos_writeMessage(int queueId, CortosMessage *msg);
    
    /* Read a CortosMessage.
      - Returns zero if the queue is empty.
      - Returns non-zero if the msg was put into the *msg location.
    */
    int cortos_readMessage(int queueId, CortosMessage *msg);
    
    // Reserve an unused queue from cortos.
    //   It returns the queue id of the queue reserved.
    //   If no queue is available it returns -1.
    // Once a queue is reserved it is held by the caller,
    // until it is freed.
    int cortos_reserveQueue();
    
    // Free a queue for reuse by cortos.
    void cortos_freeQueue(int queueId);
    
    ////////////////////////////////////////////////////////////////////////////////
    // BLOCK END  : cortos_message_queues_declarations
    ////////////////////////////////////////////////////////////////////////////////
    
    
    
    ////////////////////////////////////////////////////////////////////////////////
    // BLOCK START: cortos_bget_declarations
    ////////////////////////////////////////////////////////////////////////////////
    
    typedef long cortos_bufsize;
    
    // get/allocate a memory of `size` bytes
    // Note: Some internal space is wasted to make size align to 2^3 boundary.
    void *cortos_bget(cortos_bufsize size);
    
    // release/free an allocated memory chunk
    void cortos_brel(void *buf);
    
    ////////////////////////////////////////////////////////////////////////////////
    // BLOCK END  : cortos_bget_declarations
    ////////////////////////////////////////////////////////////////////////////////
    
    
    
    ////////////////////////////////////////////////////////////////////////////////
    // BLOCK START: cortos_debug_routines
    ////////////////////////////////////////////////////////////////////////////////
    
    // Exit after putting error_code into asr16.
    // Any non-zero code is considered error.
    // Any error code <= 255 is reserved for CoRTOS.
    // A user code may use 0 for successful exit,
    // or a value >=256 as an error exit code.
    // Cortos exit codes and their meaning:
    //      0       Successful Exit
    //      1       Error in init_00.s
    void cortos_exit(unsigned int error_code);
    
    // printf routine offered by Cortos
    // This needs the serial device to be enabled.
    // __cortos_enable_serial() enables the serial device and is
    // automatically called in init_00.s file.
    int cortos_printf(const char *fmt, ...);
    
    ////////////////////////////////////////////////////////////////////////////////
    // BLOCK END  : cortos_debug_routines
    ////////////////////////////////////////////////////////////////////////////////
    
    
    ////////////////////////////////////////////////////////////////////////////////
    // BLOCK START: cortos_logging_declarations
    ////////////////////////////////////////////////////////////////////////////////
    
    // The programmer can log messages in CoRTOS using logging macros.
    // These macros pass the arguments to printf function internally.
    // For example, to log a TRACE message
    //      CORTOS_TRACE("Current count: %d", count);
    // When the user disables all logging or some log levels,
    // all the macros of disabled log levels expand to a blank space,
    // which removes the logging message entirely.
    
    #define LOG_LEVEL_ALL       10
    #define LOG_LEVEL_TRACE     20
    #define LOG_LEVEL_DEBUG     30
    #define LOG_LEVEL_INFO      40
    #define LOG_LEVEL_ERROR     50
    #define LOG_LEVEL_CRITICAL  60
    #define LOG_LEVEL_NONE      100
    
    #define CORTOS_LOG_LEVEL 20
    #define CORTOS_LOG_LEVEL_NAME "TRACE"
    
    #define CORTOS_ALL(...)     /*blank*/
    
    #define CORTOS_TRACE(...) \
    __cortos_log_printf("TRACE", __FILE__, __func__, __LINE__, __VA_ARGS__);
    
    #define CORTOS_DEBUG(...) \
    __cortos_log_printf("DEBUG", __FILE__, __func__, __LINE__, __VA_ARGS__);
    
    #define CORTOS_INFO(...) \
    __cortos_log_printf("INFO", __FILE__, __func__, __LINE__, __VA_ARGS__);
    
    #define CORTOS_ERROR(...) \
    __cortos_log_printf("ERROR", __FILE__, __func__, __LINE__, __VA_ARGS__);
    
    #define CORTOS_CRITICAL(...) \
    __cortos_log_printf("CRITICAL", __FILE__, __func__, __LINE__, __VA_ARGS__);
    
    #define CORTOS_NONE(...) \
    __cortos_log_printf("NONE", __FILE__, __func__, __LINE__, __VA_ARGS__);
    
    
    ////////////////////////////////////////////////////////////////////////////////
    // BLOCK END  : cortos_logging_declarations
    ////////////////////////////////////////////////////////////////////////////////
    
    
    ////////////////////////////////////////////////////////////////////////////////
    // BLOCK START: cortos_utility_routines
    ////////////////////////////////////////////////////////////////////////////////
    
    // reads high and low clock counters to return
    // the value...   Returns the number of elapsed ticks
    // where one thick is 256 clock cycles.
    //   (Thus, if the clock is 100MHz, 1 tick is 2.56 micro-seconds).
    inline uint64_t cortos_get_clock_time();
    
    // sleep for specified number of clock cycles
    inline void cortos_sleep(uint32_t clock_cycles);
    
    ////////////////////////////////////////////////////////////////////////////////
    // BLOCK END  : cortos_utility_routines
    ////////////////////////////////////////////////////////////////////////////////
    
    
    
    ////////////////////////////////////////////////////////////////////////////////
    // BLOCK START: cortos_scratch_pad_area
    ////////////////////////////////////////////////////////////////////////////////
    
    // Here is a list of addresses to 4 byte locations that the
    // user can use for any miscellaneous reading, writing,
    // and sharing between the threads.
    
    #define SHARED_INT_ADDR_0 0x138  // Decimal: 312
    #define SHARED_INT_ADDR_1 0x13c  // Decimal: 316
    #define SHARED_INT_ADDR_2 0x140  // Decimal: 320
    #define SHARED_INT_ADDR_3 0x144  // Decimal: 324
    #define SHARED_INT_ADDR_4 0x148  // Decimal: 328
    #define SHARED_INT_ADDR_5 0x14c  // Decimal: 332
    #define SHARED_INT_ADDR_6 0x150  // Decimal: 336
    #define SHARED_INT_ADDR_7 0x154  // Decimal: 340
    #define SHARED_INT_ADDR_8 0x158  // Decimal: 344
    #define SHARED_INT_ADDR_9 0x15c  // Decimal: 348
    #define SHARED_INT_ADDR_10 0x160  // Decimal: 352
    #define SHARED_INT_ADDR_11 0x164  // Decimal: 356
    #define SHARED_INT_ADDR_12 0x168  // Decimal: 360
    #define SHARED_INT_ADDR_13 0x16c  // Decimal: 364
    #define SHARED_INT_ADDR_14 0x170  // Decimal: 368
    #define SHARED_INT_ADDR_15 0x174  // Decimal: 372
    #define SHARED_INT_ADDR_16 0x178  // Decimal: 376
    #define SHARED_INT_ADDR_17 0x17c  // Decimal: 380
    #define SHARED_INT_ADDR_18 0x180  // Decimal: 384
    #define SHARED_INT_ADDR_19 0x184  // Decimal: 388
    #define SHARED_INT_ADDR_20 0x188  // Decimal: 392
    #define SHARED_INT_ADDR_21 0x18c  // Decimal: 396
    #define SHARED_INT_ADDR_22 0x190  // Decimal: 400
    #define SHARED_INT_ADDR_23 0x194  // Decimal: 404
    #define SHARED_INT_ADDR_24 0x198  // Decimal: 408
    #define SHARED_INT_ADDR_25 0x19c  // Decimal: 412
    #define SHARED_INT_ADDR_26 0x1a0  // Decimal: 416
    #define SHARED_INT_ADDR_27 0x1a4  // Decimal: 420
    #define SHARED_INT_ADDR_28 0x1a8  // Decimal: 424
    #define SHARED_INT_ADDR_29 0x1ac  // Decimal: 428
    #define SHARED_INT_ADDR_30 0x1b0  // Decimal: 432
    #define SHARED_INT_ADDR_31 0x1b4  // Decimal: 436
    #define SHARED_INT_ADDR_32 0x1b8  // Decimal: 440
    #define SHARED_INT_ADDR_33 0x1bc  // Decimal: 444
    #define SHARED_INT_ADDR_34 0x1c0  // Decimal: 448
    #define SHARED_INT_ADDR_35 0x1c4  // Decimal: 452
    #define SHARED_INT_ADDR_36 0x1c8  // Decimal: 456
    #define SHARED_INT_ADDR_37 0x1cc  // Decimal: 460
    #define SHARED_INT_ADDR_38 0x1d0  // Decimal: 464
    #define SHARED_INT_ADDR_39 0x1d4  // Decimal: 468
    #define SHARED_INT_ADDR_40 0x1d8  // Decimal: 472
    #define SHARED_INT_ADDR_41 0x1dc  // Decimal: 476
    #define SHARED_INT_ADDR_42 0x1e0  // Decimal: 480
    #define SHARED_INT_ADDR_43 0x1e4  // Decimal: 484
    #define SHARED_INT_ADDR_44 0x1e8  // Decimal: 488
    #define SHARED_INT_ADDR_45 0x1ec  // Decimal: 492
    #define SHARED_INT_ADDR_46 0x1f0  // Decimal: 496
    #define SHARED_INT_ADDR_47 0x1f4  // Decimal: 500
    #define SHARED_INT_ADDR_48 0x1f8  // Decimal: 504
    #define SHARED_INT_ADDR_49 0x1fc  // Decimal: 508
    #define SHARED_INT_ADDR_50 0x200  // Decimal: 512
    #define SHARED_INT_ADDR_51 0x204  // Decimal: 516
    #define SHARED_INT_ADDR_52 0x208  // Decimal: 520
    #define SHARED_INT_ADDR_53 0x20c  // Decimal: 524
    #define SHARED_INT_ADDR_54 0x210  // Decimal: 528
    #define SHARED_INT_ADDR_55 0x214  // Decimal: 532
    #define SHARED_INT_ADDR_56 0x218  // Decimal: 536
    #define SHARED_INT_ADDR_57 0x21c  // Decimal: 540
    #define SHARED_INT_ADDR_58 0x220  // Decimal: 544
    #define SHARED_INT_ADDR_59 0x224  // Decimal: 548
    #define SHARED_INT_ADDR_60 0x228  // Decimal: 552
    #define SHARED_INT_ADDR_61 0x22c  // Decimal: 556
    #define SHARED_INT_ADDR_62 0x230  // Decimal: 560
    #define SHARED_INT_ADDR_63 0x234  // Decimal: 564
    #define SHARED_INT_ADDR_64 0x238  // Decimal: 568
    #define SHARED_INT_ADDR_65 0x23c  // Decimal: 572
    #define SHARED_INT_ADDR_66 0x240  // Decimal: 576
    #define SHARED_INT_ADDR_67 0x244  // Decimal: 580
    #define SHARED_INT_ADDR_68 0x248  // Decimal: 584
    #define SHARED_INT_ADDR_69 0x24c  // Decimal: 588
    #define SHARED_INT_ADDR_70 0x250  // Decimal: 592
    #define SHARED_INT_ADDR_71 0x254  // Decimal: 596
    #define SHARED_INT_ADDR_72 0x258  // Decimal: 600
    #define SHARED_INT_ADDR_73 0x25c  // Decimal: 604
    #define SHARED_INT_ADDR_74 0x260  // Decimal: 608
    #define SHARED_INT_ADDR_75 0x264  // Decimal: 612
    #define SHARED_INT_ADDR_76 0x268  // Decimal: 616
    #define SHARED_INT_ADDR_77 0x26c  // Decimal: 620
    #define SHARED_INT_ADDR_78 0x270  // Decimal: 624
    #define SHARED_INT_ADDR_79 0x274  // Decimal: 628
    #define SHARED_INT_ADDR_80 0x278  // Decimal: 632
    #define SHARED_INT_ADDR_81 0x27c  // Decimal: 636
    #define SHARED_INT_ADDR_82 0x280  // Decimal: 640
    #define SHARED_INT_ADDR_83 0x284  // Decimal: 644
    #define SHARED_INT_ADDR_84 0x288  // Decimal: 648
    #define SHARED_INT_ADDR_85 0x28c  // Decimal: 652
    #define SHARED_INT_ADDR_86 0x290  // Decimal: 656
    #define SHARED_INT_ADDR_87 0x294  // Decimal: 660
    #define SHARED_INT_ADDR_88 0x298  // Decimal: 664
    #define SHARED_INT_ADDR_89 0x29c  // Decimal: 668
    #define SHARED_INT_ADDR_90 0x2a0  // Decimal: 672
    #define SHARED_INT_ADDR_91 0x2a4  // Decimal: 676
    #define SHARED_INT_ADDR_92 0x2a8  // Decimal: 680
    #define SHARED_INT_ADDR_93 0x2ac  // Decimal: 684
    #define SHARED_INT_ADDR_94 0x2b0  // Decimal: 688
    #define SHARED_INT_ADDR_95 0x2b4  // Decimal: 692
    #define SHARED_INT_ADDR_96 0x2b8  // Decimal: 696
    #define SHARED_INT_ADDR_97 0x2bc  // Decimal: 700
    #define SHARED_INT_ADDR_98 0x2c0  // Decimal: 704
    #define SHARED_INT_ADDR_99 0x2c4  // Decimal: 708
    #define SHARED_INT_ADDR_100 0x2c8  // Decimal: 712
    #define SHARED_INT_ADDR_101 0x2cc  // Decimal: 716
    #define SHARED_INT_ADDR_102 0x2d0  // Decimal: 720
    #define SHARED_INT_ADDR_103 0x2d4  // Decimal: 724
    #define SHARED_INT_ADDR_104 0x2d8  // Decimal: 728
    #define SHARED_INT_ADDR_105 0x2dc  // Decimal: 732
    #define SHARED_INT_ADDR_106 0x2e0  // Decimal: 736
    #define SHARED_INT_ADDR_107 0x2e4  // Decimal: 740
    #define SHARED_INT_ADDR_108 0x2e8  // Decimal: 744
    #define SHARED_INT_ADDR_109 0x2ec  // Decimal: 748
    #define SHARED_INT_ADDR_110 0x2f0  // Decimal: 752
    #define SHARED_INT_ADDR_111 0x2f4  // Decimal: 756
    #define SHARED_INT_ADDR_112 0x2f8  // Decimal: 760
    #define SHARED_INT_ADDR_113 0x2fc  // Decimal: 764
    #define SHARED_INT_ADDR_114 0x300  // Decimal: 768
    #define SHARED_INT_ADDR_115 0x304  // Decimal: 772
    #define SHARED_INT_ADDR_116 0x308  // Decimal: 776
    #define SHARED_INT_ADDR_117 0x30c  // Decimal: 780
    #define SHARED_INT_ADDR_118 0x310  // Decimal: 784
    #define SHARED_INT_ADDR_119 0x314  // Decimal: 788
    #define SHARED_INT_ADDR_120 0x318  // Decimal: 792
    #define SHARED_INT_ADDR_121 0x31c  // Decimal: 796
    #define SHARED_INT_ADDR_122 0x320  // Decimal: 800
    #define SHARED_INT_ADDR_123 0x324  // Decimal: 804
    #define SHARED_INT_ADDR_124 0x328  // Decimal: 808
    #define SHARED_INT_ADDR_125 0x32c  // Decimal: 812
    #define SHARED_INT_ADDR_126 0x330  // Decimal: 816
    #define SHARED_INT_ADDR_127 0x334  // Decimal: 820
    #define SHARED_INT_ADDR_128 0x338  // Decimal: 824
    #define SHARED_INT_ADDR_129 0x33c  // Decimal: 828
    #define SHARED_INT_ADDR_130 0x340  // Decimal: 832
    #define SHARED_INT_ADDR_131 0x344  // Decimal: 836
    #define SHARED_INT_ADDR_132 0x348  // Decimal: 840
    #define SHARED_INT_ADDR_133 0x34c  // Decimal: 844
    #define SHARED_INT_ADDR_134 0x350  // Decimal: 848
    #define SHARED_INT_ADDR_135 0x354  // Decimal: 852
    #define SHARED_INT_ADDR_136 0x358  // Decimal: 856
    #define SHARED_INT_ADDR_137 0x35c  // Decimal: 860
    #define SHARED_INT_ADDR_138 0x360  // Decimal: 864
    #define SHARED_INT_ADDR_139 0x364  // Decimal: 868
    #define SHARED_INT_ADDR_140 0x368  // Decimal: 872
    #define SHARED_INT_ADDR_141 0x36c  // Decimal: 876
    #define SHARED_INT_ADDR_142 0x370  // Decimal: 880
    #define SHARED_INT_ADDR_143 0x374  // Decimal: 884
    #define SHARED_INT_ADDR_144 0x378  // Decimal: 888
    #define SHARED_INT_ADDR_145 0x37c  // Decimal: 892
    #define SHARED_INT_ADDR_146 0x380  // Decimal: 896
    #define SHARED_INT_ADDR_147 0x384  // Decimal: 900
    #define SHARED_INT_ADDR_148 0x388  // Decimal: 904
    #define SHARED_INT_ADDR_149 0x38c  // Decimal: 908
    #define SHARED_INT_ADDR_150 0x390  // Decimal: 912
    #define SHARED_INT_ADDR_151 0x394  // Decimal: 916
    #define SHARED_INT_ADDR_152 0x398  // Decimal: 920
    #define SHARED_INT_ADDR_153 0x39c  // Decimal: 924
    #define SHARED_INT_ADDR_154 0x3a0  // Decimal: 928
    #define SHARED_INT_ADDR_155 0x3a4  // Decimal: 932
    #define SHARED_INT_ADDR_156 0x3a8  // Decimal: 936
    #define SHARED_INT_ADDR_157 0x3ac  // Decimal: 940
    #define SHARED_INT_ADDR_158 0x3b0  // Decimal: 944
    #define SHARED_INT_ADDR_159 0x3b4  // Decimal: 948
    #define SHARED_INT_ADDR_160 0x3b8  // Decimal: 952
    #define SHARED_INT_ADDR_161 0x3bc  // Decimal: 956
    #define SHARED_INT_ADDR_162 0x3c0  // Decimal: 960
    #define SHARED_INT_ADDR_163 0x3c4  // Decimal: 964
    #define SHARED_INT_ADDR_164 0x3c8  // Decimal: 968
    #define SHARED_INT_ADDR_165 0x3cc  // Decimal: 972
    #define SHARED_INT_ADDR_166 0x3d0  // Decimal: 976
    #define SHARED_INT_ADDR_167 0x3d4  // Decimal: 980
    #define SHARED_INT_ADDR_168 0x3d8  // Decimal: 984
    #define SHARED_INT_ADDR_169 0x3dc  // Decimal: 988
    #define SHARED_INT_ADDR_170 0x3e0  // Decimal: 992
    #define SHARED_INT_ADDR_171 0x3e4  // Decimal: 996
    #define SHARED_INT_ADDR_172 0x3e8  // Decimal: 1000
    #define SHARED_INT_ADDR_173 0x3ec  // Decimal: 1004
    #define SHARED_INT_ADDR_174 0x3f0  // Decimal: 1008
    #define SHARED_INT_ADDR_175 0x3f4  // Decimal: 1012
    #define SHARED_INT_ADDR_176 0x3f8  // Decimal: 1016
    #define SHARED_INT_ADDR_177 0x3fc  // Decimal: 1020
    #define SHARED_INT_ADDR_178 0x400  // Decimal: 1024
    #define SHARED_INT_ADDR_179 0x404  // Decimal: 1028
    #define SHARED_INT_ADDR_180 0x408  // Decimal: 1032
    #define SHARED_INT_ADDR_181 0x40c  // Decimal: 1036
    #define SHARED_INT_ADDR_182 0x410  // Decimal: 1040
    #define SHARED_INT_ADDR_183 0x414  // Decimal: 1044
    #define SHARED_INT_ADDR_184 0x418  // Decimal: 1048
    #define SHARED_INT_ADDR_185 0x41c  // Decimal: 1052
    #define SHARED_INT_ADDR_186 0x420  // Decimal: 1056
    #define SHARED_INT_ADDR_187 0x424  // Decimal: 1060
    #define SHARED_INT_ADDR_188 0x428  // Decimal: 1064
    #define SHARED_INT_ADDR_189 0x42c  // Decimal: 1068
    #define SHARED_INT_ADDR_190 0x430  // Decimal: 1072
    #define SHARED_INT_ADDR_191 0x434  // Decimal: 1076
    #define SHARED_INT_ADDR_192 0x438  // Decimal: 1080
    #define SHARED_INT_ADDR_193 0x43c  // Decimal: 1084
    #define SHARED_INT_ADDR_194 0x440  // Decimal: 1088
    #define SHARED_INT_ADDR_195 0x444  // Decimal: 1092
    #define SHARED_INT_ADDR_196 0x448  // Decimal: 1096
    #define SHARED_INT_ADDR_197 0x44c  // Decimal: 1100
    #define SHARED_INT_ADDR_198 0x450  // Decimal: 1104
    #define SHARED_INT_ADDR_199 0x454  // Decimal: 1108
    #define SHARED_INT_ADDR_200 0x458  // Decimal: 1112
    #define SHARED_INT_ADDR_201 0x45c  // Decimal: 1116
    #define SHARED_INT_ADDR_202 0x460  // Decimal: 1120
    #define SHARED_INT_ADDR_203 0x464  // Decimal: 1124
    #define SHARED_INT_ADDR_204 0x468  // Decimal: 1128
    #define SHARED_INT_ADDR_205 0x46c  // Decimal: 1132
    #define SHARED_INT_ADDR_206 0x470  // Decimal: 1136
    #define SHARED_INT_ADDR_207 0x474  // Decimal: 1140
    #define SHARED_INT_ADDR_208 0x478  // Decimal: 1144
    #define SHARED_INT_ADDR_209 0x47c  // Decimal: 1148
    #define SHARED_INT_ADDR_210 0x480  // Decimal: 1152
    #define SHARED_INT_ADDR_211 0x484  // Decimal: 1156
    #define SHARED_INT_ADDR_212 0x488  // Decimal: 1160
    #define SHARED_INT_ADDR_213 0x48c  // Decimal: 1164
    #define SHARED_INT_ADDR_214 0x490  // Decimal: 1168
    #define SHARED_INT_ADDR_215 0x494  // Decimal: 1172
    #define SHARED_INT_ADDR_216 0x498  // Decimal: 1176
    #define SHARED_INT_ADDR_217 0x49c  // Decimal: 1180
    #define SHARED_INT_ADDR_218 0x4a0  // Decimal: 1184
    #define SHARED_INT_ADDR_219 0x4a4  // Decimal: 1188
    #define SHARED_INT_ADDR_220 0x4a8  // Decimal: 1192
    #define SHARED_INT_ADDR_221 0x4ac  // Decimal: 1196
    #define SHARED_INT_ADDR_222 0x4b0  // Decimal: 1200
    #define SHARED_INT_ADDR_223 0x4b4  // Decimal: 1204
    #define SHARED_INT_ADDR_224 0x4b8  // Decimal: 1208
    #define SHARED_INT_ADDR_225 0x4bc  // Decimal: 1212
    #define SHARED_INT_ADDR_226 0x4c0  // Decimal: 1216
    #define SHARED_INT_ADDR_227 0x4c4  // Decimal: 1220
    #define SHARED_INT_ADDR_228 0x4c8  // Decimal: 1224
    #define SHARED_INT_ADDR_229 0x4cc  // Decimal: 1228
    #define SHARED_INT_ADDR_230 0x4d0  // Decimal: 1232
    #define SHARED_INT_ADDR_231 0x4d4  // Decimal: 1236
    #define SHARED_INT_ADDR_232 0x4d8  // Decimal: 1240
    #define SHARED_INT_ADDR_233 0x4dc  // Decimal: 1244
    #define SHARED_INT_ADDR_234 0x4e0  // Decimal: 1248
    #define SHARED_INT_ADDR_235 0x4e4  // Decimal: 1252
    #define SHARED_INT_ADDR_236 0x4e8  // Decimal: 1256
    #define SHARED_INT_ADDR_237 0x4ec  // Decimal: 1260
    #define SHARED_INT_ADDR_238 0x4f0  // Decimal: 1264
    #define SHARED_INT_ADDR_239 0x4f4  // Decimal: 1268
    #define SHARED_INT_ADDR_240 0x4f8  // Decimal: 1272
    #define SHARED_INT_ADDR_241 0x4fc  // Decimal: 1276
    #define SHARED_INT_ADDR_242 0x500  // Decimal: 1280
    #define SHARED_INT_ADDR_243 0x504  // Decimal: 1284
    #define SHARED_INT_ADDR_244 0x508  // Decimal: 1288
    #define SHARED_INT_ADDR_245 0x50c  // Decimal: 1292
    #define SHARED_INT_ADDR_246 0x510  // Decimal: 1296
    #define SHARED_INT_ADDR_247 0x514  // Decimal: 1300
    #define SHARED_INT_ADDR_248 0x518  // Decimal: 1304
    #define SHARED_INT_ADDR_249 0x51c  // Decimal: 1308
    #define SHARED_INT_ADDR_250 0x520  // Decimal: 1312
    #define SHARED_INT_ADDR_251 0x524  // Decimal: 1316
    #define SHARED_INT_ADDR_252 0x528  // Decimal: 1320
    #define SHARED_INT_ADDR_253 0x52c  // Decimal: 1324
    #define SHARED_INT_ADDR_254 0x530  // Decimal: 1328
    #define SHARED_INT_ADDR_255 0x534  // Decimal: 1332
    
    ////////////////////////////////////////////////////////////////////////////////
    // BLOCK END  : cortos_scratch_pad_area
    ////////////////////////////////////////////////////////////////////////////////
    
    
    
    #endif
