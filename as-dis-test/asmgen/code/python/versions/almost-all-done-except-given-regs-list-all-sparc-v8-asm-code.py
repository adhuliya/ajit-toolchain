#!/usr/bin/env python3

# Generate asm code of all  possible bit patterns.  Some of them could
# be wrong but we generate them nevertheless in this version.
#
# This is a purely procedural style code;  no OOP or FP here; not even
# comprehensions!
# 06-May-2020, AMV

# Added command line processing using the argparse() library.
# 22-May-2020, AMV

# Economising on  expansion lists.   As the instructions  are expanded
# the lists  containing the expansions  increase rapidly in  size.  We
# try  to reuse  the  lists.   Once an  instruction  pattern has  been
# expanded, we immediately  print it out, and reuse the  lists for the
# next instruction pattern.  (See "do_final_expansion ()")
#
# Command line  support to expand  (a) a  given instruction, or  (b) a
# category of instructions.
#
# Both above added:
# 23-May-2020, AMV

# Documented  the important  functions.   Suggestion:  Read them  from
# main() onwards.
# 24-May-2020, AMV

# Done with all the registers only instructions.
# 31-May-2020, AMV

# Done with floating point and coprocessor registers.
# 03-Jun-2020, AMV

# Done with arguments with constants.
# 05-Jun-2020, AMV

# Done with branch instructions (including floating point and coprocessor)
# 06-Jun-2020, AMV

# Done with ASI instructions
# 06-Jun-2020, AMV

import csv
import os
# import pprint   as pp           # pretty printer
import pprint
import sys
import pathlib  as pl
import argparse as ap

#####
# Information section
#####

def setup_globals():
    '''
    Declare and  initialise global  variables.  These  must be  set as
    early as possible.
    '''
    # Declare the globals
    global script_name
    global parser, args
    global top, curr_dir, tmpdir, indentstr
    global insnformatscsv, insnlistcsv, verbosity_level
    global doinsncategory, insntoexpand, doinsnexpand, insncategory
    global asmgendata
    global fmtlst, insnlst
    global MAX_SPARC_REGS
    global call_depth, maxindent

    # List offsets: INSN list
    global insn_name_at
    global insn_format_type_at
    global insn_format_value_at
    global insn_other_field_at
    global insn_other_value_at
    global insn_op_desc_at
    global insn_page_num_at
    global insn_chap_ref_at
    global insn_category_at
    global insn_category_ind_at
    global insn_fmt_index_at
    global insn_proc_stat_at
    global insn_privilege_at
    global insn_notes_at
    global insn_reg_arg_type_at
    global insn_asm_mnemonic_at
    global insn_asm_num_args_at
    global insn_asm_arg_1_at
    global insn_asm_arg_2_at
    global insn_asm_arg_3_at
    global insn_asm_arg_4_at
    global insn_info_end_at
    global insn_expanded_fields_at # Added during calculations

    # List offsets: FORMATS list
    global fmt_name_at
    global fmt_index_at            # alias for format name
    global fmt_num_bit_fields_at
    global fmt_bit_field_list_at

    # List offsets: BIT FIELDS list
    global bit_field_name_at
    global bit_field_end_at
    global bit_field_start_at
    global bit_field_length_at
    global bit_field_val_str_at
    global bit_field_val_type_at
    # The fields from  this one onwards are not a  part of information
    # stored on secondary memory.
    global bit_field_mask_at
    global bit_field_pattern_str_at
    global bit_field_processing_state_at
    global bit_field_val_lst_at

    # Outputs: Each expansion of the patterns has the following fields.
    global insn_source_at
    global insn_32_bit_string_at
    global insn_integer_code_at
    global insn_asm_string_list_at
    global insn_asm_comment_at

    global arg_detail_argnum_at
    global arg_detail_bitfield_name_at
    global arg_detail_asm_name_at
    global arg_detail_arg_type_at
    global arg_detail_asm_arg_str_at
    global arg_detail_argval_lst_at
    global arg_detail_reglsttouse_at
    
    global out_bitlst_is_arg_num_at
    global out_bitlst_bf_name_at
    global out_bitlst_bf_val_type_at
    global out_bitlst_out_opc_lst_at
    global out_bitlst_reg_val_lst_at
    global out_bitlst_given_val_at
    global out_bitlst_asm_name_at
    global out_bitlst_arg_type_at
    global out_bitlst_asm_arg_str_at
    global out_bitlst_argval_lst_at
    # global out_bitlst_arglst_at

    global fin_expans         # The Master list of all expansions.
    global expanded_insns     # The final list of all expansions.

    global sparc_regs, sparc_fpregs, sparc_as_regs, sparc_coproc_regs # Lists of SPARC V8 registers
    global insn_iterator
    global fmt_iterator
    global bit_fields_iterator

    global list_length_max
    global max_list_length_bits
    global asm_comment_str
    global pp

    # Initialisations
    # Directory structure
    top = '/lindata/My-work/Professional/iitb/development'
    asmgentop = top + '/asmgen'
    asmgencode = asmgentop + '/code'
    asmgendata = asmgentop + '/data'
    asmgenccode = asmgencode + '/c'
    asmgenpycode = asmgencode + '/python'
    asmgenschemecode = asmgencode + '/scheme'

    tmpdir = '/tmp'               # Temporary work area. Check for existence

    # ### Input  file names.   The defaults  are actually  set in  the
    # ### argparse module as in the next two lines of this comment.
    # ### insnformatscsv = asmgendata + '/' + 'sparc-manual-formats.csv'
    # ### insnlistcsv = asmgendata + '/' + 'sparc-insn-expand.csv'
    insnformatscsv = asmgendata + '/' + 'smf.csv'     ### 'sparc-manual-formats.csv'
    insnlistcsv = asmgendata + '/' + 'sie3.csv'        ### 'sparc-insn-expand.csv'

    # Lists
    fmtlst  = []                # Formats      read in from insnformatscsv are here
    insnlst = []                # Instructions read in from insnlistcsv    are here

    # List fields offsets: INSN list
    insn_name_at            = 0
    insn_format_type_at     = 1
    insn_format_value_at    = 2
    insn_other_field_at     = 3
    insn_other_value_at     = 4
    insn_op_desc_at         = 5
    insn_page_num_at        = 6
    insn_chap_ref_at        = 7
    insn_category_at        = 8
    insn_category_ind_at    = 9 
    insn_fmt_index_at       = 10
    insn_proc_stat_at       = 11
    insn_privilege_at       = 12
    insn_notes_at           = 13
    insn_reg_arg_type_at    = 14
    insn_asm_mnemonic_at    = 15
    insn_asm_num_args_at    = 16
    insn_asm_arg_1_at       = 17
    insn_asm_arg_2_at       = 18
    insn_asm_arg_3_at       = 19
    insn_asm_arg_4_at       = 20
    insn_info_end_at        = 21
    insn_expanded_fields_at = 22

    # List fields offsets: FORMATS list
    fmt_name_at           = 0
    fmt_index_at          = 0            # alias for format name
    fmt_num_bit_fields_at = 1
    fmt_bit_field_list_at = 2

    # List fields offsets: BIT FIELDS list
    bit_field_name_at           = 0
    bit_field_end_at            = 1
    bit_field_start_at          = 2
    bit_field_length_at         = 3
    bit_field_val_str_at        = 4
    bit_field_val_type_at       = 5

    # List field offsets: Argument details list (analyse_args())
    arg_detail_argnum_at        = 0 # Copied to expanded bit list output below
    arg_detail_bitfield_name_at = 1 # Copied
    arg_detail_asm_name_at      = 2 # To be added to expanded bit list
    arg_detail_arg_type_at      = 3 # To be added to expanded bit list
    arg_detail_asm_arg_str_at   = 4 # To be added to expanded bit list
    arg_detail_argval_lst_at    = 5 # To be added to expanded bit list
    arg_detail_reglsttouse_at   = 6 # Copied
    
    # Offsets of an expanded bit lists at output
    out_bitlst_is_arg_num_at    = 0 # Copy from arg_detail_argnum_at
    out_bitlst_bf_name_at       = 1 # Copy from arg_detail_bitfield_name_at
    out_bitlst_bf_val_type_at   = 2
    out_bitlst_out_opc_lst_at   = 3
    out_bitlst_reg_val_lst_at   = 4 # Copy from arg_detail_reglsttouse_at
    out_bitlst_given_val_at     = 5
    out_bitlst_asm_name_at      = 6 # Added from argument details list
    out_bitlst_arg_type_at      = 7 # Added from argument details list
    out_bitlst_asm_arg_str_at   = 8 # Added from argument details list
    out_bitlst_argval_lst_at    = 9 # Added from argument details list

    out_bitlst_arglst_at        = 6

    MAX_SPARC_REGS = 32
    
    sparc_regs                    = list (range (MAX_SPARC_REGS))
    sparc_fpregs                  = list (range (MAX_SPARC_REGS))
    sparc_as_regs                 = list (range (MAX_SPARC_REGS))
    sparc_coproc_regs             = list (range (MAX_SPARC_REGS))
    fin_expans = []
    expanded_insns = []
    
    # Maximum length of generated lists.
    #
    # We  check if  the possible  length of  the list  to generate  is
    # larger than this.   If larger than we specify  the _range_.  For
    # example, the disp30 is a 30  bit field that will generate 2^{30}
    # possible values.   Not worth  its while  at all.   Hence replace
    # this by two extremities of the range: [0, 2^{30}].
    max_list_length_bits = 5
    list_length_max = 2 ^ max_list_length_bits

    asm_comment_str = "#;|"

    script_name = pl.PurePosixPath(sys.argv[0]).name
    verbosity_level =  0        # By  default  we are very  quiet, and
                                # generate only the output asked!
    call_depth = 0
    doinsncategory = False      # Should we expand an insn category? No
    doinsnexpand = False        # Should we expand an insn? No
    insncategory = 2            # default insn category to expand
    insntoexpand = "ADD"        # default insn to expand

    pp = pprint.PrettyPrinter (indent=3, compact=True)

#####
# I/O functions section
#####

def read_data_file(df):
    '''
    Read in data files.
    '''
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if (verbosity_level > 4) else verbosity_level
    
    if (verbosity_level >= 1):
        print("{m}: {f:82s} ...".format(m="Reading data file", f=df), end='')
    rv = []
    with open(df, 'r') as f1:
        raw_data = csv.reader(f1, delimiter=',')
        rv = list(raw_data)
    f1.closed
    if (verbosity_level >= 1):
        print("Done.")
    call_depth = call_depth - 1
    return rv

#####
# System and setup functions section
#####

def parse_command_line ():
    '''
    Parse the  command line  options and set  variables accordingly.
    We use the argparse module here.
    '''
    global insnformatscsv, insnlistcsv, verbosity_level
    global call_depth, maxindent
    global doinsncategory, insntoexpand, doinsnexpand, insncategory
    call_depth = call_depth + 1
    maxindent = 4 if (verbosity_level > 4) else verbosity_level

    dmsg="Generate machine code bit patterns and their ASM syntax for all possible "
    dmsg=dmsg + "SPARC V8 instruction combinations."
    emsg="Use the SPARC V8 manual for any names needed, e.g. the instruction to expand. "
    emsg=emsg + "WARNING: Not all the details in the manual are implemented. "
    emsg=emsg + "Some output may be wrong."
    parser = ap.ArgumentParser(description=dmsg, epilog=emsg)
    parser.add_argument("-v", "--verbosity", action="count",
                        default=0, help="increase output verbosity")
    parser.add_argument("-f", "--formatsfile", action="store", nargs='?',
                        default=asmgendata + '/' + 'sparc-manual-formats.csv',
                        help="Specify the CSV file with instruction formats")
    parser.add_argument("-i", "--insnsfile",   action="store", nargs='?',
                        default=asmgendata + '/' + 'sparc-insn-expand.csv',
                        help="Specify the CSV file with instructions")
    parser.add_argument("-e", "--expandinsn",  action="store", nargs='?',
                        help="[ToDo] Specify a specific instruction to expand")
    parser.add_argument("-c", "--category",    action="store", nargs='?',
                        type=int, choices=[1, 2, 3, 4, 5, 6],
                        help="[ToDo] Specify a specific category of instructions to expand")
    args = parser.parse_args()

    if args.formatsfile:
        ### Input file names
        insnformatscsv = "{v}".format(v=args.formatsfile)
        
    if args.insnsfile:
        insnlistcsv = args.insnsfile

    if args.expandinsn:
        doinsnexpand = True
        insntoexpand = "{v}".format (v=args.expandinsn.upper())
    else:
        doinsnexpand = False
        insntoexpand = ""

    if args.category:
        doinsncategory = True
        insncategory = "{v}".format (v=args.category)
    else:
        doinsncategory = False
        insncategory = ""

    verbosity_level = args.verbosity

    if (verbosity_level >= 1):
       print("{m:30s}: {f}".format(m="ARGS IS", f=args))
       print("{m:30s}: {f}".format(m="INSNs CSV file", f=insnlistcsv))
       print("{m:30s}: {f}".format(m="INSN formats CSV file", f=insnformatscsv))
       print("{m:30s}: {f}".format(m="Verbosity level", f=verbosity_level))
       print("{m:30s}: {f}".format(m="Expand insns from category", f=doinsncategory))
       print("{m:30s}: {f}".format(m="Insn category to expand", f=insncategory))
       print("{m:30s}: {f}".format(m="Expand a given insn", f=doinsnexpand))
       print("{m:30s}: {f}".format(m="Insn to expand", f=insntoexpand))
        
    call_depth = call_depth - 1
    return

def check_and_create_if_necessary(the_dir):
    '''
    Check if a directory exists, and create it if it does not.
    '''
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if (verbosity_level > 4) else verbosity_level
    
    if not os.path.exists(the_dir):
        os.mkdir(the_dir, mode=0o777)
    call_depth = call_depth - 1
    return os.path.exists(the_dir)

def system_setup():
    '''
    Set some global parameters.
    '''
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if (verbosity_level > 4) else verbosity_level

    curr_dir = os.getcwd()        # Current directory
    os.chdir(top)

    check_and_create_if_necessary(tmpdir)
    curr_dir = os.getcwd()
    if (verbosity_level > 0):
       print ("{m:30s}: {d}".format (m="Current directory",d=curr_dir))
    
    call_depth = call_depth - 1
    return

#####
# Processing functions section
#####

def get_mask_of_length (masklen):
    '''
    Generate a (bit) mask of 1s of the given length.
    '''
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if (verbosity_level > 4) else verbosity_level
    
    val = 0
    i = 0
    while (i < masklen):
        set_bit = 0x1 << i
        val = val | set_bit
        i = i + 1
        
    call_depth = call_depth - 1
    return val

def make_lists_of_flat_bit_fields_in_formats (fl):
    '''
    The input  data is a  list for each  format line read  in.  Each
    format line has a sequence of bit field formats.  Thus the input
    of a format on a line is received as a _flat_ list of bitfields.
    We want  to reorganise  each of  these flat  bit field  lists as
    separate individual  lists.  Each  individual bit field  list is
    then a part of the list for each format.

    This  function calls  the  reorganising function  for each  list
    (i.e. line) of the input.
    
    Each reorganised list is collected  into the "result" list.  The
    "result" list is the list of a given format into a list of lists
    of bit fields.  It is returned to the caller.

    Input: List of lists of flat formats data
    Output: List of lists of lists of bit fields data.
    '''
    
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if (verbosity_level > 4) else verbosity_level
    
    # if (verbosity_level > 0):   # detail level: 1
    #    print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
    #           format(c=call_depth, mi=maxindent, p=".", w=(3*1),
    #                  m="Reorganising formats database",
    #                  l=fl if (verbosity_level > 3) else "// Low verbosity. Skipping display"))
       
    n = len (fl)
    result = []
    for i in range (n):
        result.append (reorganise_formats_list (fl[i], i))
    # for i in range (1, n):      # Skip the header row
    #     result.append (reorganise_formats_list (fl[i], i))

    call_depth = call_depth - 1
    # if (verbosity_level > 0):   # detail level: 1
    #    print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}.".
    #           format(c=call_depth, mi=maxindent, p=".", w=(3*1),
    #                  m="DONE Reorganising formats database"))
       
    return result
    
def reorganise_formats_list (fl, hdr):
    '''
    The actual reorganising work horse that organises each bit field
    into a list of its own.

    Each row of flat formatted data  has some generic data common to
    all  instruction (aka  insn) formats.   The bit  fields data  is
    however specific  to each format.   Each bit field has  the same
    parameters of  information.  However the specific  data for each
    parameter for  a given bits field  and the number of  bit fields
    differ for  each format.   Further, the  first row  is a  row of
    headers that is useful when we view the formats data as a table.
    For our purposes though we skip this row.

    Input : fl  - A row of format specifications,
            hdr - The row number; header rows are row 0.
    Output: A reorganised list of list of bit fields lists.
    '''
    
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if (verbosity_level > 4) else verbosity_level
    
    # if (verbosity_level > 0):   # detail level: 2
    #    print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s} #{n}: {l}".
    #           format(c=call_depth, mi=maxindent, p=".", w=(3*2),
    #                  m="Reorganising formats list", n=hdr, 
    #                  l=fl if (verbosity_level > 3) else "// Low verbosity. Skipping display"))
       
    num_fields = len (fl)
    total_bits = 0

    num_bit_fields = bit_field_val_type_at - bit_field_name_at + 1
    sl = fl[fmt_bit_field_list_at:]
    num_bit_fields_lists = (int) (len (sl) / num_bit_fields)
    
    bit_fields = []
    reformatted_list = []

    reformatted_list.append (fl[fmt_name_at])
    reformatted_list.append (fl[fmt_num_bit_fields_at])

    total_bits = 0
    for i in range (0, num_bit_fields_lists): 
        field_offset = (i * num_bit_fields)

        if (hdr == 0):          # First row has labels (strings) instead of any numbers
            name             = sl[field_offset + bit_field_name_at]
            start            = sl[field_offset + bit_field_start_at]
            end              = sl[field_offset + bit_field_end_at]
            length           = "DIFF"
            value            = sl[field_offset + bit_field_val_str_at]
            value_type       = sl[field_offset + bit_field_val_type_at]
        else:
            name             = sl[field_offset + bit_field_name_at]
            start            = int (sl[field_offset + bit_field_start_at])
            end              = int (sl[field_offset + bit_field_end_at])
            length           = end - start + 1
            value            = sl[field_offset + bit_field_val_str_at]
            value_type       = sl[field_offset + bit_field_val_type_at]
            total_bits       = total_bits + length
            
        bit_fields.append ([name, start, end, length, value, value_type])
        
        i = i + 1

    if ((total_bits != 32) and (hdr != 0)):
        print ("ERROR: Format entry {d} has incorrect total bits.  The format is:".format(d=hdr))
        print (fl)
        
    reformatted_list.append (bit_fields)
    if (hdr == 0):
        reformatted_list.append ("Formats List Processing State")
    else:
        reformatted_list.append ("bit fields combined")
    
    call_depth = call_depth - 1
    # if (verbosity_level > 0):   # detail level: 2
    #    print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s} #{n}".
    #           format(c=call_depth, mi=maxindent, p=".", w=(3*2),
    #                  m="DONE Reorganising formats list", n=hdr))
       
    return reformatted_list

def get_fmt_list_from_fmt_index (fmt_index, fl):
    '''
    Insns refer to  format lists using a string we  call the "format
    index" (fmt_index).  This function retrieves the format index of
    the given insn from the list of formats.

    Input: fmt_index - format index to search
           fl - list of formats to search from

    Output: Return the list if found, else empty list.
    '''
    
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if (verbosity_level > 4) else verbosity_level
    
    if (verbosity_level > 0):   # detail level: 2
       print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s} #{n}: {l}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*2),
                     m="Getting formats list named", n=fmt_index,
                     l=fl if (verbosity_level > 3) else "// Low verbosity. Skipping display"))
       
    fmt_list = []
    fls = []
    num_parts = fmt_index.count ("|")

    srchstr = fmt_index
    i = 0
    while (i <= num_parts):
        # Our earlier version  used to associate more  than one format
        # with a  given insn.  The  formats were separated by  the "|"
        # character.  Our current version  of the formats database now
        # associates a  single format with  a given insn.  An  insn is
        # duplicated  if the  SPARC  V8 manual  allows  more than  one
        # formats  for that  insn.  So  we no  longer need  the string
        # partitioning  code.   Nevertheless,  its presence  does  not
        # cause problems since no field value has the "|" character in
        # it.
        parts = srchstr.partition ('|')
        fmtstr = parts[0]
        srchstr = parts[2]

        the_lst = get_format_given_str (fmtstr, fl)

        if (the_lst != []):
            fmt_list.append (the_lst)
        
        i = i + 1

    call_depth = call_depth - 1
    if (verbosity_level > 0):   # detail level: 2
       print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s} #{n}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*2),
                     m="DONE Getting formats list named", n=fmt_index))
       
    return fmt_list

def get_format_given_str (fmt_str, fl):
    '''
    The actual work horse for the function above.

    Input: fmt_str - format string to search
           fl - list of formats to search from

    Output: Return the list if found, else empty list.
    '''
    
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if (verbosity_level > 4) else verbosity_level
    
    if (verbosity_level > 0):   # detail level: 3
       print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s} \"{n}\": {l}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*3),
                     m="Searching formats list named", n=fmt_str,
                     l="Ignoring headers row"
                     if (fmt_str == "Format Index")
                     else (fl if (verbosity_level > 3)
                              else "// Low verbosity. Skipping display")))
       
    ans = []

    for i in range (len (fl)):
        if (fl[i][0] == fmt_str):
            ans = fl[i]
            break
        
    call_depth = call_depth - 1
    if (verbosity_level > 0):   # detail level: 3
       print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s} \"{n}\": {l}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*3),
                     m="Searching formats list named", n=fmt_str,
                     l="Ignored headers row" if (fmt_str == "Format Index") else ("Found" if (ans != []) else "Not found")))
       
    return ans

def replace_format_specs_by_lists (il, fl):
    '''
    This function replaces  the format specification for  an insn by
    the corresponding  list from the formats  database.  The formats
    database must  be reorganised so  that the bit fields  are lists
    and the format list is thus a list of lists.

    Input:  il - list of insns
            fl - list of (reorganised) formats
    Output: il - list of insns with format specification replaced by
                 the (reorganised) list.
    '''
    
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if (verbosity_level > 4) else verbosity_level
    
    if (verbosity_level > 0):   # detail level: 1
       print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*1),
                     m="Replacing formats specs by lists",
                     l=fl if (verbosity_level > 3) else "// Low verbosity. Skipping display"))
       # theil = pp.pformat (il)
       # print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
       #        format(c=call_depth, mi=maxindent, p=".", w=(3*1),
       #               m="Using insns list ...",
       #               l=theil if (verbosity_level > 3) else "// Low verbosity. Skipping display"))
       
    all_insns = len (il)
    all_fmts  = len (fl)
    fmt_fld   = insn_fmt_index_at

    for i in range (0, all_insns):
        il[i][fmt_fld] =  get_fmt_list_from_fmt_index (il[i][fmt_fld], fl)
    
    call_depth = call_depth - 1
    if (verbosity_level > 0):   # detail level: 1
       # theil = pp.pformat (il)
       # print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
       #        format(c=call_depth, mi=maxindent, p=".", w=(3*1),
       #               m="Insns list is now ...",
       #               l=theil if (verbosity_level > 3) else "// Low verbosity. Skipping display"))
       print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*1),
                     m="DONE Replacing formats specs by lists"))
       
    return il
    
def set_bit (bitno, toReset):
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if (verbosity_level > 4) else verbosity_level
    
    retval = 0
    if (bitno >= 0) and (bitno <= 31):
        retval = retval | (0x1 << bitno)

    call_depth = call_depth - 1
    return (retval if (toReset == False) else (0xFFFFFFFF - retval))

def make_bit_mask (end, start):
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if (verbosity_level > 4) else verbosity_level
    
    theval  = pow (2, (end - start) + 1) - 1
    maskval = theval << start
    minusmaskval = 0xFFFFFFFF - maskval
        
    call_depth = call_depth - 1
    return maskval

def do_given (bitfld, insn, arglst):
    '''
    The  values to  be  used for  some bitfields  are  given in  the
    manual.  Our  insn and formats  databases record such  values as
    given.  This function generates the  bit pattern using the given
    values that is to be used in the final opcode.
    
    We also  record if  a given  bitfield is an  argument to  an ASM
    instruction in our database.  We capture this information in our
    output.  At this point the  capture only propagates the argument
    number.  Later  functions will use  this value to  generate some
    more information.
    
    Input:  bitfld - the particular bit field to expand using GIVEN
            insn   - the instruction that has the given value
            arglst - Arguments list updated by analyse_args().
    Output: A list with the following fields -
            is_arg_num  - the ASM arugment number, else -1
            bf_name     - name of the bit field
            bf_val_type - "given" in this case
            out_opc_lst - List of values to be used in final opcode
            reg_val_lst - List of registers, if describes registers
            theval      - The given value, else -1 for other types
            asmname     - ASM name of the argument represented by this bitfield
            argtype     - Type of argument: r/f/c/a/g
            asmargstr   - ASM instance string of the argument
            argvallst   - List of values: same as out_opc_lst

    All the do_... functions below follow the format above.
    '''
    
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if (verbosity_level > 4) else verbosity_level
    
    if (verbosity_level > 0):   # detail level: 4
       print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*4),
                     m="Doing GIVEN", l=bitfld))

    out_lst = []
    # out_opc_lst = []
    # reg_val_lst = []

    bf_name     = bitfld [bit_field_name_at]
    bf_end      = bitfld [bit_field_end_at]
    bf_start    = bitfld [bit_field_start_at]
    bf_nbits    = bitfld [bit_field_length_at]
    bf_given    = bitfld [bit_field_val_str_at]
    bf_val_type = bitfld [bit_field_val_type_at]
    bf_mask     = make_bit_mask (bf_start, bf_end)

    # is_arg_num  = arglst[0]
    
    useval = int (bf_given, 16)
    theval = useval
    useval = (useval << bf_end)

    # out_opc_lst = [useval]
    # out_lst = [is_arg_num, bf_name, bf_val_type, out_opc_lst, reg_val_lst, theval, arglst]
    out_lst = [theval, [useval]]
    
    call_depth = call_depth - 1
    if (verbosity_level > 0):   # detail level: 4
       print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*4),
                     m="DONE Doing GIVEN"))
    return out_lst

def get_cond_val (insn):
    thecondval = ""
    iname = insn [insn_name_at]

    if ((iname == "TA")     or (iname == "BA")):
        thecondval="1000"
    elif ((iname == "TN")   or (iname == "BN")):
        thecondval="0000"
    elif ((iname == "TNE")  or (iname == "BNE")):
        thecondval="1001"
    elif ((iname == "TE")   or (iname == "BE")):
        thecondval="0001"
    elif ((iname == "TG")   or (iname == "BG")):
        thecondval="1010"
    elif ((iname == "TLE")  or (iname == "BLE")):
        thecondval="0010"
    elif ((iname == "TGE")  or (iname == "BGE")):
        thecondval="1011"
    elif ((iname == "TL")   or (iname == "BL")):
        thecondval="0011"
    elif ((iname == "TGU")  or (iname == "BGU")):
        thecondval="1100"
    elif ((iname == "TLEU") or (iname == "BLEU")):
        thecondval="0100"
    elif ((iname == "TCC")  or (iname == "BCC")):
        thecondval="1101"
    elif ((iname == "TCS")  or (iname == "BCS")):
        thecondval="0101"
    elif ((iname == "TPOS") or (iname == "BPOS")):
        thecondval="1110"
    elif ((iname == "TNEG") or (iname == "BNEG")):
        thecondval="0110"
    elif ((iname == "TVC")  or (iname == "BVC")):
        thecondval="1111"
    elif ((iname == "TVS")  or (iname == "BVS")):
        thecondval="0111"
    elif (iname == "FBA"):
        thecondval="1000"
    elif (iname == "FBN"):
        thecondval="0000"
    elif (iname == "FBU"):
        thecondval="0111"
    elif (iname == "FBG"):
        thecondval="0110"
    elif (iname == "FBUG"):
        thecondval="0101"
    elif (iname == "FBL"):
        thecondval="0100"
    elif (iname == "FBUL"):
        thecondval="0011"
    elif (iname == "FBLG"):
        thecondval="0010"
    elif (iname == "FBNE"):
        thecondval="0001"
    elif (iname == "FBE"):
        thecondval="1001"
    elif (iname == "FBUE"):
        thecondval="1010"
    elif (iname == "FBGE"):
        thecondval="1011"
    elif (iname == "FBUGE"):
        thecondval="1100"
    elif (iname == "FBLE"):
        thecondval="1101"
    elif (iname == "FBULE"):
        thecondval="1110"
    elif (iname == "FBO"):
        thecondval="1111"
    elif (iname == "CBA"):
        thecondval="1000"
    elif (iname == "CBN"):
        thecondval="0000"
    elif (iname == "CB3"):
        thecondval="0111"
    elif (iname == "CB2"):
        thecondval="0110"
    elif (iname == "CB23"):
        thecondval="0101"
    elif (iname == "CB1"):
        thecondval="0100"
    elif (iname == "CB13"):
        thecondval="0011"
    elif (iname == "CB12"):
        thecondval="0010"
    elif (iname == "CB123"):
        thecondval="0001"
    elif (iname == "CB0"):
        thecondval="1001"
    elif (iname == "CB03"):
        thecondval="1010"
    elif (iname == "CB02"):
        thecondval="1011"
    elif (iname == "CB023"):
        thecondval="1100"
    elif (iname == "CB01"):
        thecondval="1101"
    elif (iname == "CB013"):
        thecondval="1110"
    elif (iname == "CB012"):
        thecondval="1111"
    else:
        thecondval = ""

    return thecondval

def do_lookup (bitfld, insn, arglst):
    '''
    Some bitfields are  part of the _format_ type.   SPARC has three
    format types, and the insns are  defined by the values for these
    type  fields.   These values  are  defined  in the  manual,  and
    recorded in the insn and  formats databases we have created from
    the manual.

    This function does a lookup in  the insns database for the value
    to  be  used  for  such  bitfields.   This  is  similar  to  the
    "do_given()" functionality  above.  In  that case, the  value to
    use  is given  in the  bitfield itself  which is  a part  of the
    formats database.  In this case the value to use is in the insns
    database.
    '''
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if (verbosity_level > 4) else verbosity_level
    
    if (verbosity_level > 0):   # detail level: 4
       print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*4),
                     m="Doing LOOKUP", l=bitfld))
       
    out_lst = []
    # out_opc_lst = []
    # reg_val_lst = []

    bf_name     = bitfld [bit_field_name_at]
    bf_end      = bitfld [bit_field_end_at]
    bf_start    = bitfld [bit_field_start_at]
    bf_nbits    = bitfld [bit_field_length_at]
    bf_given    = bitfld [bit_field_val_str_at]
    bf_val_type = bitfld [bit_field_val_type_at]
    bf_mask     = make_bit_mask (bf_start, bf_end)
    
    # is_arg_num  = arglst[0]

    if (bf_name == "cond"):
        value_str_found = get_cond_val (insn)
    else:
        value_str_found = insn [insn_format_value_at]

    # print ("GGG Bit Field name lookup(): {v}".format (v=bf_name))
    # print ("GGG ValStr in lookup(): {v}".format (v=value_str_found))

    useval = int (value_str_found, 2)
    # print ("GGG ValStr in lookup(): {v}".format (v=useval))
    # sys.exit (0)
    theval = useval
    useval = (useval << bf_end)

    # out_opc_lst = [useval]
    # out_lst = [is_arg_num, bf_name, bf_val_type, out_opc_lst, reg_val_lst, theval, arglst]
    out_lst = [theval, [useval]]
    
    call_depth = call_depth - 1
    if (verbosity_level > 0):   # detail level: 4
       print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*4),
                     m="DONE Doing LOOKUP"))
       
    return out_lst

def do_generate (bitfld, insn, arglst):
    '''
    Bitfields, like  those describing registers,  can take a  set of
    values from a minimum to a maximum.  This function generates all
    the values  for the opcode  part that this bitfield  deals with.
    Thus  it not  only generates  the  integer value  but also  left
    shifts it as needed to align with exactly the part of the opcode
    this bitfield describes.
    
    This  generation can  be large  if we  allow generation  for any
    range of values.   For example the "call" instruction  uses a 30
    bit argument.  Generating all the values from 0 to (2^30 - 1) is
    not useful at  all.  We arbitrarily constrain  the generation by
    restricting to a maximum  of "max_list_length_bits" defined as a
    global variable at  the start of this script.   Fields, like the
    30 bit  argument to  the "call"  insn, are  handled by  the next
    function that  only generates  two values:  the minimum  and the
    maximum.
    
    Input and output are as in the "do_given()" function.
    '''
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if (verbosity_level > 4) else verbosity_level
    
    if (verbosity_level > 0):   # detail level: 4
       print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*4),
                     m="Doing GENERATE", l=bitfld))
       
    out_lst = []
    out_opc_lst = []
    # reg_val_lst = []

    bf_name     = bitfld [bit_field_name_at]
    bf_end      = bitfld [bit_field_end_at]
    bf_start    = bitfld [bit_field_start_at]
    bf_nbits    = bitfld [bit_field_length_at]
    bf_given    = bitfld [bit_field_val_str_at]
    bf_val_type = bitfld [bit_field_val_type_at]
    bf_mask     = make_bit_mask (bf_start, bf_end)

    # is_arg_num  = arglst[0]
    
    theval = -1                 # Does not make sense here :-(.
    if (bf_nbits <= max_list_length_bits):
        num_vals = pow (2, bf_nbits)
        for i in range (num_vals):
            # useval = i
            # reg_val_lst.append (useval)
            # useval = (useval << bf_end)
            
            useval = (i << bf_end)
        
            out_opc_lst.append (useval)
    else:
        print ("ERROR: Range for bitfield \"{n}\" exceeds maximum.  Max #bits: {m}, Given #bits: {g}".
               format (n=bf_name, m=max_list_length_bits, g=bf_nbits))

    # out_lst = [is_arg_num, bf_name, bf_val_type, out_opc_lst, reg_val_lst, theval, arglst]
    out_lst = [theval, out_opc_lst.copy()]
    
    call_depth = call_depth - 1
    if (verbosity_level > 0):   # detail level: 4
       print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*4),
                     m="DONE Doing GENERATE"))
       
    return out_lst

def do_range (bitfld, insn, arglst):
    '''
    Similar to  the "do_generate()" function, but  only generate the
    minimum and maximum values of the range.
    '''
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if (verbosity_level > 4) else verbosity_level
    
    if (verbosity_level > 0):   # detail level: 4
       print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*4),
                     m="Doing RANGE", l=bitfld))
       
    out_lst = []
    out_opc_lst = []
    # reg_val_lst = []

    bf_name     = bitfld [bit_field_name_at]
    bf_end      = bitfld [bit_field_end_at]
    bf_start    = bitfld [bit_field_start_at]
    bf_nbits    = bitfld [bit_field_length_at]
    bf_given    = bitfld [bit_field_val_str_at]
    bf_val_type = bitfld [bit_field_val_type_at]
    bf_mask     = make_bit_mask (bf_start, bf_end)

    # is_arg_num  = arglst[0]
    
    min = 0
    max = pow (2, bf_nbits) # Careful: This could be a very large number, e.g. > 24 bits!

    theval = -1                 # Does not make sense here
    useval = min
    useval = (useval << bf_end)
    
    out_opc_lst.append (useval)
    # out_lst.append (useval)
    
    useval = max
    useval = (useval << bf_end) - 1
    
    out_opc_lst.append (useval)
    # out_lst.append (useval)
    
    out_lst = [theval, out_opc_lst]

    call_depth = call_depth - 1
    if (verbosity_level > 0):   # detail level: 4
       print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*4),
                     m="DONE Doing RANGE"))
       
    return out_lst

def do_set (bitfld, insn, arglst):
    '''
    The values  for some bit fields  are given, and are  relevant to
    the  instruction for  which they  are being  defined.  At  other
    times some  bit fields may  not be relevant to  the instruction.
    In such cases, the manual either prescribes a value or describes
    them as  "don't care"  bits.  We  say that  such bit  fields are
    "set" to the given value.  In  case these are "don't care" bits,
    we arbitrarily _set_ them to 0.
    '''
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if (verbosity_level > 4) else verbosity_level
    
    if (verbosity_level > 0):   # detail level: 4
       print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*4),
                     m="Doing SET", l=bitfld))
       
    out_lst = []
    # out_opc_lst = []
    # reg_val_lst = []

    bf_name     = bitfld [bit_field_name_at]
    bf_end      = bitfld [bit_field_end_at]
    bf_start    = bitfld [bit_field_start_at]
    bf_nbits    = bitfld [bit_field_length_at]
    bf_given    = bitfld [bit_field_val_str_at]
    bf_val_type = bitfld [bit_field_val_type_at]

    useval = int (bf_given, 16)
    theval = useval
    useval = (useval << bf_end)
    
    # out_opc_lst.append (useval)
    
    # out_lst = [out_opc_lst]
    out_lst = [theval, [useval]]

    call_depth = call_depth - 1
    if (verbosity_level > 0):   # detail level: 4
       print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*4),
                     m="DONE Doing SET"))
       
    return out_lst

# def do_given (bitfld, insn, arglst):
#     '''
#     The  values to  be  used for  some bitfields  are  given in  the
#     manual.  Our  insn and formats  databases record such  values as
#     given.  This function generates the  bit pattern using the given
#     values that is to be used in the final opcode.
    
#     We also  record if  a given  bitfield is an  argument to  an ASM
#     instruction in our database.  We capture this information in our
#     output.  At this point the  capture only propagates the argument
#     number.  Later  functions will use  this value to  generate some
#     more information.
    
#     Input:  bitfld - the particular bit field to expand using GIVEN
#             insn   - the instruction that has the given value
#             is_arg_num - the ASM argument number, else -1.
#     Output: A list with the following fields -
#             is_arg_num  - the ASM arugment number, else -1
#             bf_name     - name of the bit field
#             bf_val_type - "given" in this case
#             out_opc_lst - List of values to be used in final opcode
#             reg_val_lst - List of registers, if describes registers
#             theval      - The given value, else -1 for other types
#             asmname     - ASM name of the argument represented by this bitfield
#             argtype     - Type of argument: r/f/c/a/g
#             asmargstr   - ASM instance string of the argument
#             argvallst   - List of values: same as out_opc_lst

#     All the do_... functions below follow the format above.
#     '''
    
#     global call_depth, maxindent
#     call_depth = call_depth + 1
#     maxindent = 4 if (verbosity_level > 4) else verbosity_level
    
#     if (verbosity_level > 0):   # detail level: 4
#        print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
#               format(c=call_depth, mi=maxindent, p=".", w=(3*4),
#                      m="Doing GIVEN", l=bitfld))

#     out_lst = []
#     out_opc_lst = []
#     reg_val_lst = []

#     bf_name     = bitfld [bit_field_name_at]
#     bf_end      = bitfld [bit_field_end_at]
#     bf_start    = bitfld [bit_field_start_at]
#     bf_nbits    = bitfld [bit_field_length_at]
#     bf_given    = bitfld [bit_field_val_str_at]
#     bf_val_type = bitfld [bit_field_val_type_at]
#     bf_mask     = make_bit_mask (bf_start, bf_end)

#     is_arg_num  = arglst[0]
    
#     useval = int (bf_given, 16)
#     theval = useval
#     useval = (useval << bf_end)

#     out_opc_lst = [useval]
#     out_lst = [is_arg_num, bf_name, bf_val_type, out_opc_lst, reg_val_lst, theval, arglst]
    
#     call_depth = call_depth - 1
#     if (verbosity_level > 0):   # detail level: 4
#        print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}".
#               format(c=call_depth, mi=maxindent, p=".", w=(3*4),
#                      m="DONE Doing GIVEN"))
#     return out_lst

# def do_lookup (bitfld, insn, arglst):
#     '''
#     Some bitfields are  part of the _format_ type.   SPARC has three
#     format types, and the insns are  defined by the values for these
#     type  fields.   These values  are  defined  in the  manual,  and
#     recorded in the insn and  formats databases we have created from
#     the manual.

#     This function does a lookup in  the insns database for the value
#     to  be  used  for  such  bitfields.   This  is  similar  to  the
#     "do_given()" functionality  above.  In  that case, the  value to
#     use  is given  in the  bitfield itself  which is  a part  of the
#     formats database.  In this case the value to use is in the insns
#     database.
#     '''
#     global call_depth, maxindent
#     call_depth = call_depth + 1
#     maxindent = 4 if (verbosity_level > 4) else verbosity_level
    
#     if (verbosity_level > 0):   # detail level: 4
#        print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
#               format(c=call_depth, mi=maxindent, p=".", w=(3*4),
#                      m="Doing LOOKUP", l=bitfld))
       
#     out_lst = []
#     out_opc_lst = []
#     reg_val_lst = []

#     bf_name     = bitfld [bit_field_name_at]
#     bf_end      = bitfld [bit_field_end_at]
#     bf_start    = bitfld [bit_field_start_at]
#     bf_nbits    = bitfld [bit_field_length_at]
#     bf_given    = bitfld [bit_field_val_str_at]
#     bf_val_type = bitfld [bit_field_val_type_at]
#     bf_mask     = make_bit_mask (bf_start, bf_end)
    
#     is_arg_num  = arglst[0]
    
#     value_str_found = insn [insn_format_value_at]
#     useval = int (value_str_found, 2)
#     theval = useval
#     useval = (useval << bf_end)

#     out_opc_lst = [useval]
#     out_lst = [is_arg_num, bf_name, bf_val_type, out_opc_lst, reg_val_lst, theval, arglst]
    
#     call_depth = call_depth - 1
#     if (verbosity_level > 0):   # detail level: 4
#        print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}".
#               format(c=call_depth, mi=maxindent, p=".", w=(3*4),
#                      m="DONE Doing LOOKUP"))
       
#     return out_lst

# def do_generate (bitfld, insn, arglst):
#     '''
#     Bitfields, like  those describing registers,  can take a  set of
#     values from a minimum to a maximum.  This function generates all
#     the values  for the opcode  part that this bitfield  deals with.
#     Thus  it not  only generates  the  integer value  but also  left
#     shifts it as needed to align with exactly the part of the opcode
#     this bitfield describes.
    
#     This  generation can  be large  if we  allow generation  for any
#     range of values.   For example the "call" instruction  uses a 30
#     bit argument.  Generating all the values from 0 to (2^30 - 1) is
#     not useful at  all.  We arbitrarily constrain  the generation by
#     restricting to a maximum  of "max_list_length_bits" defined as a
#     global variable at  the start of this script.   Fields, like the
#     30 bit  argument to  the "call"  insn, are  handled by  the next
#     function that  only generates  two values:  the minimum  and the
#     maximum.
    
#     Input and output are as in the "do_given()" function.
#     '''
#     global call_depth, maxindent
#     call_depth = call_depth + 1
#     maxindent = 4 if (verbosity_level > 4) else verbosity_level
    
#     if (verbosity_level > 0):   # detail level: 4
#        print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
#               format(c=call_depth, mi=maxindent, p=".", w=(3*4),
#                      m="Doing GENERATE", l=bitfld))
       
#     out_lst = []
#     out_opc_lst = []
#     reg_val_lst = []

#     bf_name     = bitfld [bit_field_name_at]
#     bf_end      = bitfld [bit_field_end_at]
#     bf_start    = bitfld [bit_field_start_at]
#     bf_nbits    = bitfld [bit_field_length_at]
#     bf_given    = bitfld [bit_field_val_str_at]
#     bf_val_type = bitfld [bit_field_val_type_at]
#     bf_mask     = make_bit_mask (bf_start, bf_end)

#     is_arg_num  = arglst[0]
    
#     theval = -1                 # Does not make sense here :-(.
#     if (bf_nbits <= max_list_length_bits):
#         num_vals = pow (2, bf_nbits)
#         for i in range (num_vals):
#             useval = i
#             reg_val_lst.append (useval)

#             useval = (useval << bf_end)
        
#             out_opc_lst.append (useval)
#     else:
#         print ("ERROR: Range for bitfield \"{n}\" exceeds maximum.  Max #bits: {m}, Given #bits: {g}".
#                format (n=bf_name, m=max_list_length_bits, g=bf_nbits))

#     out_lst = [is_arg_num, bf_name, bf_val_type, out_opc_lst, reg_val_lst, theval, arglst]
    
#     call_depth = call_depth - 1
#     if (verbosity_level > 0):   # detail level: 4
#        print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}".
#               format(c=call_depth, mi=maxindent, p=".", w=(3*4),
#                      m="DONE Doing GENERATE"))
       
#     return out_lst

# def do_range (bitfld, insn, arglst):
#     '''
#     Similar to  the "do_generate()" function, but  only generate the
#     minimum and maximum values of the range.
#     '''
#     global call_depth, maxindent
#     call_depth = call_depth + 1
#     maxindent = 4 if (verbosity_level > 4) else verbosity_level
    
#     if (verbosity_level > 0):   # detail level: 4
#        print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
#               format(c=call_depth, mi=maxindent, p=".", w=(3*4),
#                      m="Doing RANGE", l=bitfld))
       
#     out_lst = []
#     out_opc_lst = []
#     reg_val_lst = []

#     bf_name     = bitfld [bit_field_name_at]
#     bf_end      = bitfld [bit_field_end_at]
#     bf_start    = bitfld [bit_field_start_at]
#     bf_nbits    = bitfld [bit_field_length_at]
#     bf_given    = bitfld [bit_field_val_str_at]
#     bf_val_type = bitfld [bit_field_val_type_at]
#     bf_mask     = make_bit_mask (bf_start, bf_end)

#     is_arg_num  = arglst[0]
    
#     min = 0
#     max = pow (2, bf_nbits) # Careful: This could be a very large number, e.g. > 24 bits!

#     theval = -1                 # Does not make sense here
#     useval = min
#     useval = (useval << bf_end)
    
#     out_opc_lst.append (useval)
    
#     useval = max
#     useval = (useval << bf_end) - 1
    
#     out_opc_lst.append (useval)
    
#     out_lst = [is_arg_num, bf_name, bf_val_type, out_opc_lst, reg_val_lst, theval, arglst]

#     call_depth = call_depth - 1
#     if (verbosity_level > 0):   # detail level: 4
#        print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}".
#               format(c=call_depth, mi=maxindent, p=".", w=(3*4),
#                      m="DONE Doing RANGE"))
       
#     return out_lst

# def do_set (bitfld, insn, arglst):
#     '''
#     The values  for some bit fields  are given, and are  relevant to
#     the  instruction for  which they  are being  defined.  At  other
#     times some  bit fields may  not be relevant to  the instruction.
#     In such cases, the manual either prescribes a value or describes
#     them as  "don't care"  bits.  We  say that  such bit  fields are
#     "set" to the given value.  In  case these are "don't care" bits,
#     we arbitrarily _set_ them to 0.
#     '''
#     global call_depth, maxindent
#     call_depth = call_depth + 1
#     maxindent = 4 if (verbosity_level > 4) else verbosity_level
    
#     if (verbosity_level > 0):   # detail level: 4
#        print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
#               format(c=call_depth, mi=maxindent, p=".", w=(3*4),
#                      m="Doing SET", l=bitfld))
       
#     out_lst = []
#     out_opc_lst = []
#     reg_val_lst = []

#     bf_name     = bitfld [bit_field_name_at]
#     bf_end      = bitfld [bit_field_end_at]
#     bf_start    = bitfld [bit_field_start_at]
#     bf_nbits    = bitfld [bit_field_length_at]
#     bf_given    = bitfld [bit_field_val_str_at]
#     bf_val_type = bitfld [bit_field_val_type_at]
#     bf_mask     = make_bit_mask (bf_start, bf_end)

#     is_arg_num  = arglst[0]
    
#     useval = int (bf_given, 16)
#     theval = useval
#     useval = (useval << bf_end)
    
#     out_opc_lst.append (useval)
    
#     out_lst = [is_arg_num, bf_name, bf_val_type, out_opc_lst, reg_val_lst, theval, arglst]

#     call_depth = call_depth - 1
#     if (verbosity_level > 0):   # detail level: 4
#        print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}".
#               format(c=call_depth, mi=maxindent, p=".", w=(3*4),
#                      m="DONE Doing SET"))
       
#     return out_lst

def get_regs_list_for_given_type (arg_type):
    thereglst = []

    print ("zzz {m:30s}: {v}".format (m="Searching reglist for type", v=arg_type))
    # global sparc_regs, sparc_fpregs, sparc_as_regs, sparc_coproc_regs # Lists of SPARC V8 registers
    if   (arg_type == "r"):
        thereglst = sparc_regs
    elif (arg_type == "f"):
        thereglst = sparc_fpregs
    elif (arg_type == "c"):
        thereglst = sparc_coproc_regs
    elif (arg_type == "a"):
        thereglst = sparc_as_regs
    else:
        thereglst = []
        
    print ("zzz {m:30s}: {v}".format (m="Reglist for type is", v=thereglst))
    return thereglst

def analyse_args (bitfld, insn):

    # Return the list of ASM  argument values this bitfield describes.
    # The format of the result list is:
    #
    # [
    #   argnum,                 # 0: Argument number; -1 if unknown or irrelevant
    #   bf_name,                # 1: Name of the bit field either from manual or us
    #   argname,                # 2: Name of the ASM form of the argument 
    #   argtype,                # 3: Type of argument: register etc.
    #   asmargstr,              # 4: Argument string to use in the ASM expansion
    #   argvallst,              # 5: List of values of the argument, if any
    #   reglsttouse             # 6: List of register numbers to use, if any
    # ]

    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if (verbosity_level > 4) else verbosity_level
    
    argnum = -1                 # The   local  variables,  argstr  and
                                # argval, following  this have invalid
                                # data if this variable is -1.
    argstr = ""
    argval = 0
    # global sparc_regs, sparc_fpregs, sparc_as_regs, sparc_coproc_regs # Lists of SPARC V8 registers
    reglst = sparc_regs         # Default registers to use

    thelst = []
    
    bf_name  = bitfld [bit_field_name_at]

    if ((bf_name == "op3")    or   # Don't bother checking for arguments
                                   # if the  bit field  itself is  not an
                                   # argument!
        (bf_name == "op2")    or
        (bf_name == "i")      or
        (bf_name == "a")      or
        (bf_name == "cond")   or
        (bf_name == "op")     or
        (bf_name == "UNUSED") or
        (bf_name == "RES")    or
        (bf_name == "NONAME")):
        # print ("yyy {m:30s}: {v}".format (m="SKIP isArgAnalysis for Bitfield", v=bf_name))
        thelst = [argnum, bf_name, argstr, "", argstr, [], []]
        return thelst
    
    num_args = insn [insn_asm_num_args_at]
    asm_arg1 = insn [insn_asm_arg_1_at]
    asm_arg2 = insn [insn_asm_arg_2_at]
    asm_arg3 = insn [insn_asm_arg_3_at]
    asm_arg4 = insn [insn_asm_arg_4_at]

    arg_type = insn [insn_reg_arg_type_at]

    # print ("yyy {m:30s}: {v}".format (m="Bit fields list name", v=bf_name))
    # print ("yyy {m:30s}: {v}".format (m="#Args", v=num_args))

    # msg = "ASM Args type code "
    # print ("yyy {m:30s}: {v}".format (m=msg, v=arg_type))
    # msg = "ASM Arg {d} is ".format (d=1)
    # print ("yyy {m:30s}: {v}".format (m=msg, v=asm_arg1))
    # msg = "ASM Arg {d} is ".format (d=2)
    # print ("yyy {m:30s}: {v}".format (m=msg, v=asm_arg2))
    # msg = "ASM Arg {d} is ".format (d=3)
    # print ("yyy {m:30s}: {v}".format (m=msg, v=asm_arg3))
    # msg = "ASM Arg {d} is ".format (d=4)
    # print ("yyy {m:30s}: {v}".format (m=msg, v=asm_arg4))
    # msg = "ASM Arg {d} is ".format (d=-1)
    # print ("yyy {m:30s}: {v}".format (m=msg, v="UNKNOWN"))

    theargs = [asm_arg1, asm_arg2, asm_arg3, asm_arg4]

    print ("yyy Attempting match using exact match with ASM arg names ...")
    print ("yyy {m:30s}: {v}".format (m="Number of arguments", v=num_args))
    argnum = -1
    for i in range (int (num_args, 10)):
        if   (bf_name == theargs[i]):
            argnum = (i + 1)
            argstr = theargs[i]
            argval = []
            typecode = arg_type [i]
            reglst = get_regs_list_for_given_type (typecode)
            # [argnum, bf_name, argname, argtype, argstr, argvallst, reglsttouse]
            thelst = [argnum, bf_name, argstr, arg_type[argnum - 1], argstr, [], reglst]
            break

    print ("yyy {m:30s}: {v}".format (m="ArgNum Matched by field name", v=argnum))
    print ("yyy {m:30s}: {v}".format (m="ArgNum Matched by ASM arg name", v=thelst))

    if (argnum == -1):    
        print ("yyy Attempting match using \"=\" match with ASM patterns ...")
        print ("yyy {m:30s}: {v}".format (m="Number of arguments", v=num_args))
        for i in range (int (num_args, 10)):
            msg="Checking arg {d} ... ".format (d=i)
            print ("yyy    {m:30s}: {v}".format (m=msg, v=theargs[i]), end="")
            if ("=" in theargs[i]):
                argsplits=theargs[i].split(sep="=")
                print (" ... FOUND. argspilts is: {a}".format (a=argsplits))
                print ("yyy {m:30s}: {v}".format (m="ArgNum Matched by =", v=argnum))
                if (bf_name == argsplits[0]):
                    argnum = (i + 1)
                    argstr = theargs[i]
                    argval = []
                    typecode = arg_type [i]
                    reglst = get_regs_list_for_given_type (typecode)
                    # [argnum, bf_name, argname, argtype, argstr, argvallst, reglsttouse]
                    thelst = [argnum, bf_name, argstr, arg_type[argnum - 1], argsplits[1], [], reglst]
                    break
            else:
                print (" ... NOT FOUND.")
            
        print ("yyy {m:30s}: {v}".format (m="ArgNum Matched by =", v=thelst))
    
    if (argnum == -1):    
        print ("yyy Attempting match for constants with ASM patterns ...")
        print ("yyy {m:30s}: {v}".format (m="Number of arguments", v=num_args))
        for i in range (int (num_args, 10)):
            msg="Checking arg {d} ... ".format (d=i)
            print ("yyy    {m:30s}: {v}".format (m=msg, v=theargs[i]), end="")
            if (("imm7"    in theargs[i]) or # immediate value
                ("simm13"  in theargs[i]) or # immediate value
                ("imm22"   in theargs[i]) or # immediate value
                ("disp22"  in theargs[i]) or # immediate value
                ("const22" in theargs[i]) or # immediate value
                ("disp30"  in theargs[i]) or # immediate value
                False):
                argnum = (i + 1)
                argstr = theargs[i]
                argval = []
                typecode = arg_type [i]
                reglst = get_regs_list_for_given_type (typecode)
                # [argnum, bf_name, argname, argtype, argstr, argvallst, reglsttouse]
                thelst = [argnum, bf_name, argstr, arg_type[argnum - 1], argstr, [], reglst]
                break
            else:
                print (" ... NOT FOUND.")
            
        print ("yyy {m:30s}: {v}".format (m="ArgNum Matched for constants", v=thelst))
    
    print ("yyy ===")

    # if ((inargstr.find ("rs1")     != -1) or # Source register #1
    #     (inargstr.find ("rs2")     != -1) or # Source register #2
    #     (inargstr.find ("rd")      != -1) or # Destination register
    #     False):
    #     print ("Hello")
                
    # print ("yyy {m:30s}: {v}".format (m="ArgNum Matched by field name", v=argnum))

    call_depth = call_depth - 1
    # return argnum
    return thelst

def get_reg_rname (regno):
    return "%r" + str (regno) if (0 <= regno <= MAX_SPARC_REGS) else ""

def get_freg_name (regno):
    return "%f" + str (regno) if (0 <= regno <= MAX_SPARC_REGS) else ""

def get_coproc_reg_name (regno):
    return "%c" + str (regno) if (0 <= regno <= MAX_SPARC_REGS) else ""

def get_as_reg_name (regno):
    return "%asr_r" + str (regno) if (0 <= regno <= MAX_SPARC_REGS) else ""

def get_reg_name (regno, regtype):
    prefix = ""
    reglist = []
    
    if (regtype == "f"):
        prefix="%f"
        reglist = sparc_fpregs
    elif (regtype == "c"):
        prefix="%c"
        reglist = sparc_coproc_regs
    elif (regtype == "a"):
        prefix="%asr_r"
        reglist = sparc_as_regs
    else:
        prefix="%r"
        reglist = sparc_regs

    return prefix + str (regno) if (0 <= regno <= MAX_SPARC_REGS) else ""

def get_reg_gname (regno):
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if (verbosity_level > 4) else verbosity_level
    
    the_gname = ""
    
    if (0 <= regno <= 7):
        the_gname = "%g" + str (regno)      # Global
    if (8 <= regno <= 15):
        the_gname = "%o" + str (regno - 8)  # Out
    if (16 <= regno <= 23):
        the_gname = "%l" + str (regno - 16) # Local
    if (24 <= regno <= 31):
        the_gname = "%i" + str (regno - 24) # In

    call_depth = call_depth - 1
    return the_gname

def expand_bit_field (bitfld, insn):
    '''
    Bitfields  represent parts  of the  opcode that  must either  be
    given, or  be generated (again:  either over the whole  range or
    only the minimum and maximum), or be looked up, or be set.  This
    is  the driver  function that  studies the  given bit  field and
    calls the corresponding bit field expander.
    
    Input:  bitfld - the bit field of the insn to expand
            insn   - the insn
    Output: A list with expansion and other information.
            (See the output documentation of "do_given()" above)
    '''
    
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if (verbosity_level > 4) else verbosity_level
    
    if (verbosity_level > 0):   # detail level: 3
       print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*3),
                     m="Expanding bit field", l=bitfld))
       
    # print ("aaa {m:30s}: {v}".format (m="Bit field", v=bitfld))
    # print ("aaa {m:30s}: {v}".format (m="INSN to process", v=insn))
    # # print ("aaa {m:30s}:".format (m="FE"))
    # # pp.pprint (insn)
    bitlst = []
    retlst = []
    n = 0
    # gen_bitvals_lst = []
    # rng_pat_str_lst = []
    args_lst = []

    args_lst = analyse_args (bitfld, insn)
    if (verbosity_level > 0):   # Detail level 3
       # print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
       #        format(c=call_depth, mi=maxindent, p=".", w=(3*3),
       #               m="Analysed ARGS are", l=args_lst))
       print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}:".
              format(c=call_depth, mi=maxindent, p=".", w=(3*3),
                     m="Analysed ARGS are"))
       pp.pprint (args_lst)
    
    bf_val_type = bitfld [bit_field_val_type_at]
    
    if (bf_val_type == "generate"):
       retlst = do_generate (bitfld, insn, args_lst)
    
    if (bf_val_type == "given"):
        retlst = do_given (bitfld, insn, args_lst)
    
    if (bf_val_type == "range"):
        retlst = do_range (bitfld, insn, args_lst)
    
    if (bf_val_type == "set"):
        retlst = do_set (bitfld, insn, args_lst)
    
    if (bf_val_type == "lookup"):
        retlst = do_lookup (bitfld, insn, args_lst)

    print ("ccc Args analysed: {a}".format (a=args_lst))
    print ("ccc Bit field expanded to: {b}".format (b=retlst))

    bitlst = [ args_lst [arg_detail_argnum_at],
               args_lst [arg_detail_bitfield_name_at],
               bf_val_type,
               retlst [1],
               args_lst [arg_detail_reglsttouse_at],
               retlst [0],
               args_lst [arg_detail_asm_name_at],
               args_lst [arg_detail_arg_type_at],
               args_lst [arg_detail_asm_arg_str_at],
               args_lst [arg_detail_argval_lst_at]
    ]
    
    if (verbosity_level > 0):   # Detail level 3
       print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*3),
                     m="Bit Field Expanded to", l=bitlst))

    call_depth = call_depth - 1
    if (verbosity_level > 0):   # detail level: 3
       print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*3),
                     m="DONE Expanding bit field"))
       
    return bitlst

def expand_insn (insn):
    '''
    Given an insn as a list of various pieces of information, expand
    it.  In particular, we iterate over the format list that has all
    the bitfields of this insn.   For each bitfield iterated over we
    call the bit fields expander.
    
    Once  all  the bitfields  are  expanded,  we first  replace  the
    original formats specifications list field in the insn with this
    expanded list.  We then  call the "do_final_expansion() function
    to generate the final opcode.
    
    Although these functions return  the insn, the actual expansions
    are in  separate global lists.   The returned value is  not very
    useful.  Not very good programming, eh! :-(.
    '''

    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if (verbosity_level > 4) else verbosity_level
    
    if (verbosity_level > 0):   # Detail level: 2
       # print ("=== {c:02d}/{mi:02d} {p:{w}s}Expanding insn: {l}".
       #        format(c=call_depth, mi=maxindent, p=".", w=(3*2),
       #               l=insn))
       print ("=== {c:02d}/{mi:02d} {p:{w}s}Expanding insn:".
              format(c=call_depth, mi=maxindent, p=".", w=(3*2)))
       pp.pprint (insn)
       print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {n}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*2),
                     m="INSN name", n=insn[insn_name_at]))
       # print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
       #        format(c=call_depth, mi=maxindent, p=".", w=(3*2),
       #               m="Using format", l=insn [insn_fmt_index_at][0][0]))
            
    expanded_outlst = []
    fmt_iterator = iter (insn [insn_fmt_index_at])

    for fmt in fmt_iterator:
        if (verbosity_level > 0): # Detail level 2
            print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {n}".
                   format(c=call_depth, mi=maxindent, p=".", w=(3*2),
                          m="FMT name", n=fmt [fmt_name_at]))
            
        bit_fields_iterator = iter (fmt [fmt_bit_field_list_at])
        
        total_bits = 0
        theOpcode  = 0xFFFFFFFF # Set the fields with bitwise ANDs
        tmpintval  = 0
        num_bitflds = fmt [fmt_num_bit_fields_at]
        len_bitflds = len(fmt [fmt_bit_field_list_at])
        for bitfld in bit_fields_iterator:
            thlst = expand_bit_field (bitfld, insn)
            # Now set up the full bit field ...
            # Output: A list with the following fields -
            #         is_arg_num  - the ASM arugment number, else -1
            #         bf_name     - name of the bit field
            #         bf_val_type - "given" in this case
            #         out_opc_lst - List of values to be used in final opcode
            #         reg_val_lst - List of registers, if describes registers
            #         theval      - The given value, else -1 for other types
            #         asmname     - ASM name of the argument represented by this bitfield
            #         argtype     - Type of argument: r/f/c/a/g
            #         asmargstr   - ASM instance string of the argument
            #         argvallst   - List of values: same as out_opc_lst
            # out_lst = [is_arg_num, bf_name, bf_val_type, out_opc_lst, reg_val_lst, theval, arglst]
            if (verbosity_level > 0): # Detail level 2
                print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
                       format(c=call_depth, mi=maxindent, p=".", w=(3*2),
                              m="Appending bitfield", l=thlst))
            expanded_outlst.append (thlst)

        num_bitflds_processed = len (expanded_outlst)
        
    insn [insn_fmt_index_at] = expanded_outlst
    if (verbosity_level > 0):   # Detail level 2
        # print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
        #        format(c=call_depth, mi=maxindent, p=".", w=(3*2),
        #               m="Expanded insn", l=insn[insn_fmt_index_at]))
        print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}:".
               format(c=call_depth, mi=maxindent, p=".", w=(3*2), m="Expanded insn"))
        pp.pprint (insn[insn_fmt_index_at])

    # print ("\n\nALERT: We SKIP - do_final_expansion (insn) with insn as:\n")
    # pp.pprint (insn)

    do_final_expansion (insn)

    if (verbosity_level > 0):
        print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
               format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent),
                      m="DONE Expanding insn", l=insn))

    call_depth = call_depth - 1
    return insn

def get_opcode (l):
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if (verbosity_level > 4) else verbosity_level
    
    x = 0
    for i in l:
        x = x | i[0]

    call_depth = call_depth - 1
    return x

def make_comment_str (insn, other):
    '''
    Apart  from generating  the numerical  opcode, we  also generate
    some descriptive  information of  the instruction that  has just
    been expanded.   In particular we  generate the ASM form  of the
    instruction,  a  brief  description  of  the  operation  of  the
    instruction,  the  values of  some  key  fields like  the  "op?"
    fields, and a reference to the  section and page in the SPARC V8
    manual for this instruction.

    Each  is   separated  by  the  "asm_comment_str"   string.   The
    asm_comment_str is typically one or more of characters in "|#;".
    This allows  generating a  particularly tabular form  of output.
    This can  be easily picked up  into a spreadsheet software  as a
    "CSV" file.  In our case  though the separating character is not
    comma, but  one or  more of  the characters  in asm_comment_str.
    Fortunately  most spreadsheet  software allows  us to  use other
    characters as field separators.
    '''
    
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if (verbosity_level > 4) else verbosity_level
    
    thecomment = ""

    asm_str = "{theinsn} {a1}{a2}{a3}{a4}".format (
            theinsn=insn [insn_name_at],         # insn name
            a1=insn [insn_asm_arg_1_at]        if (insn [insn_asm_arg_1_at] != "") else "",   # arg 1, if any
            a2=", " + insn [insn_asm_arg_2_at] if (insn [insn_asm_arg_2_at] != "") else "",   # arg 2, if any
            a3=", " + insn [insn_asm_arg_3_at] if (insn [insn_asm_arg_3_at] != "") else "",   # arg 3, if any
            a4=", " + insn [insn_asm_arg_4_at] if (insn [insn_asm_arg_4_at] != "") else "",   # arg 4, if any
    )

    keyfields = "{op}{opval}{op1}{op1val}".format (
        op=insn[insn_format_type_at] if (insn[insn_format_type_at] != "") else "",
        opval=" = " + insn[insn_format_value_at] if (insn[insn_format_value_at] != "") else "",
        op1=", " + insn[insn_other_field_at] if (insn[insn_other_field_at] != "") else "",
        op1val=" = " + insn[insn_other_value_at] if (insn[insn_other_field_at] != "") else ""
        )
    
    opdesc = "{opdesc} {o}".format (
        opdesc=insn [insn_op_desc_at],
        o=other
    )
    manref = "{ref1} {cref} {pag1} {pref} {ref2}".format (
        ref1="See Section",
        cref=insn [insn_chap_ref_at],
        pag1="on page",
        pref=insn [insn_page_num_at],
        ref2="of the Sparc V8 manual."
    )
    thecomment =  "{sc} {asm} {sc1} {opd} {sc2} {kf} {sc3} {mr}".format (
        sc="#",
        asm=asm_str,
        sc1=asm_comment_str,
        opd=opdesc,
        sc2=asm_comment_str,
        kf=keyfields,
        sc3=asm_comment_str,
        mr=manref,
    )
    
    call_depth = call_depth - 1
    return thecomment

def get_argnum_str (r, arg):
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if (verbosity_level > 4) else verbosity_level
    
    thestr = ""
    # print ("bbb get_argnum_val(): arg is {a}, r is {r}".format (a=arg, r=r))
    for l in r:
        # print ("bbb l in r is {l}".format (l=l))
        if (l[1] == arg):
            thestr = l[2]
            # print ("bbb    Value is: {l}".format (l=thestr))
            break

    call_depth = call_depth - 1
    return thestr
        
def get_argnum_val (r, arg):
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if (verbosity_level > 4) else verbosity_level
    
    theval = -1
    print ("bbb get_argnum_val(): arg is {a}, r is {r}".format (a=arg, r=r))
    for l in r:
        print ("bbb l in r is {l}".format (l=l))
        if (l[1] == arg):
            theval = l[5]
            print ("bbb    Value is: {l}".format (l=theval))
            break

    call_depth = call_depth - 1
    return theval

def get_numeric_value (strval, numval):
    if ((strval.find ("imm7")    != -1) or # immediate value
        (strval.find ("simm13")  != -1) or # immediate value
        (strval.find ("imm22")   != -1) or # immediate value
        (strval.find ("disp22")  != -1) or # immediate value
        (strval.find ("const22") != -1) or # immediate value
        (strval.find ("disp30")  != -1) or # immediate value
        False):
        argstr = "0x{v:08X}".format (v=numval)
    else:
        argstr = ""

    return argstr

def get_specific_reg_names (inargstr, regvalofarg):
    theregs = ""
    
    return theregs

def build_list_of_opcodes (insn, l, bf, res, rec):
    '''
    The expander workhorse.  This function  takes a list of bitfield
    lists.   The   number  of   bitfields  is  different   for  each
    instruction, though.   Each bitfield list  has a list  of values
    that it  contributes into the final  opcode.  We need to  take a
    value from  the first list and  combine it with the  values from
    the  rest of  the  lists.   This recursive  pattern  is used  to
    generate all the combinations that can be possibly generated for
    this insn.

    This  function not  only generates  the opcode,  but also  other
    information.  For example, our  insn database records the syntax
    pattern  of the  ASM form  of the  instruction.  For  example we
    record if the  instruction uses the "rs1"  source register.  Our
    opcode generation process generates  an opcode for each possible
    register  _value_.   As  additional  information,  we  take  the
    register value and generate  the register _string_.  This allows
    us to emit the specific ASM form of the opcode generated.

    Note that  the base case  is where  we _return_ the  result list
    "res" and the recursive case is  where we do the recursive call.
    In the recursive  call, the "res" list  assembles the components
    from each bitfield and is an argument.

    Format of output list:
      opcode   - The _numeric_ opcode.  This is printed twice.
      mnemonic - The ASM mnemonic string
      arg1     - The string form of the argument 1, if any
      arg2     - The string form of the argument 2, if any
      arg3     - The string form of the argument 3, if any
      arg4     - The string form of the argument 4, if any
      cmtstr   - A brief comment about the instruction operation. We
                 include important bit field  values, e.g. the value
                 of  the "op3"  field or  the given  value (see  the
                 description in "do_given()")  etc. We also indicate
                 the  reference section  and  page in  the SPARC  V8
                 manual for this ASM instruction.
      arg1val  - The value form of the argument 1, if any
      arg2val  - The value form of the argument 2, if any
      arg3val  - The value form of the argument 3, if any
      arg4val  - The value form of the argument 4, if any
    '''

    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent  = 4 if (verbosity_level > 4) else verbosity_level
    
    reslst       = []
    num_asm_args = insn [insn_asm_num_args_at]
    opsubcode    = 0
    argnum       = -1
    argstr       = ""
    numvalofarg  = -1
    regvalofarg  = -1
    otherstr     = ""

    theopc  = 0
    arg1    = ""
    arg2    = ""
    arg3    = ""
    arg4    = ""
    arg1val = -1
    arg2val = -1
    arg3val = -1
    arg4val = -1
    cmtstr  = ""

    if (l == []):
        pres = pp.pformat (res)
        print ("aaa RES is: {r}".format (r=pres))
        theopc  = get_opcode (res)
        arg1    = get_argnum_str (res, 1)
        arg2    = get_argnum_str (res, 2)
        arg3    = get_argnum_str (res, 3)
        arg4    = get_argnum_str (res, 4)
        arg1val = get_argnum_val (res, 1)
        arg2val = get_argnum_val (res, 2)
        arg3val = get_argnum_val (res, 3)
        arg4val = get_argnum_val (res, 4)
        cmtstr  = make_comment_str (insn, otherstr)
        theopcstr = "{l:032b}".format(l=theopc)
        print ("aaa    theopc is: {r}".format (r=theopc))
        print ("aaa    arg1   is: {r}".format (r=arg1))
        print ("aaa    arg2   is: {r}".format (r=arg2))
        print ("aaa    arg3   is: {r}".format (r=arg3))
        print ("aaa    arg4   is: {r}".format (r=arg4))
        print ("aaa    a1val  is: {r}".format (r=arg1val))
        print ("aaa    a2val  is: {r}".format (r=arg2val))
        print ("aaa    a3val  is: {r}".format (r=arg3val))
        print ("aaa    a4val  is: {r}".format (r=arg4val))

        # Format of output list: [opcode, mnemonic, arg1, arg2, arg3, arg4, cmtstr, arg1val, arg2val, arg3val, arg4val]
        fin_expans.append ([theopc, insn [insn_asm_mnemonic_at], arg1, arg2, arg3, arg4, cmtstr, arg1val, arg2val, arg3val, arg4val])
        call_depth = call_depth - 1
        return res
    else:
        fst = l[0]
        rst = l[1:]
        numfst = len (fst)
        bftouse = bf[rec]

        for i in range (numfst):
            reslst = res.copy()
            # Format of output list: [opsubcode, argnum, argstr, numvalofarg, otherstr]
            opsubcode = fst[i]
            if (bftouse[out_bitlst_given_val_at] != -1): # Record "static" information
                if ((bftouse[out_bitlst_bf_val_type_at] == "given")   or
                    (bftouse[out_bitlst_bf_val_type_at] == "lookup")  or
                    (bftouse[out_bitlst_bf_val_type_at] == "range")   or
                    (bftouse[out_bitlst_bf_val_type_at] == "UNUSED")):
                    otherstr = "{n} = {v}".format (n=bftouse[out_bitlst_bf_name_at],
                                                   v=bftouse[out_bitlst_given_val_at])
                    
            argnum = bftouse[out_bitlst_is_arg_num_at]

            if (argnum != -1):  # We are some argument in the opcode pattern

                # inargtype can be one of [rfncg]
                inargtype   = insn [insn_reg_arg_type_at][argnum - 1]
                inargstr    = bftouse[out_bitlst_bf_name_at].casefold()
                # numvalofarg = bftouse[out_bitlst_out_opc_lst_at][i]
                numvalofarg = bftouse[out_bitlst_out_opc_lst_at][i]

                # regvalofarg = bftouse[out_bitlst_reg_val_lst_at][i] if (bftouse [out_bitlst_arg_type_at] == "r") else -1
                if ((bftouse [out_bitlst_arg_type_at] == "r") or
                    (bftouse [out_bitlst_arg_type_at] == "f") or
                    (bftouse [out_bitlst_arg_type_at] == "c") or
                    (bftouse [out_bitlst_arg_type_at] == "a") or
                    False):
                    regvalofarg = bftouse[out_bitlst_reg_val_lst_at][i]
                else:
                    regvalofarg = -1

                    
                print ("xxx {m:30s}: {v}".format (m="INSN Using Bit Field",  v=bftouse))
                print ("xxx {m:30s}: {v}".format (m="INSN Reg Arg Type Str", v=insn [insn_reg_arg_type_at]))
                print ("xxx {m:30s}: {v}".format (m="INSN Arg Num",          v=argnum))
                print ("xxx {m:30s}: {v}".format (m="INSN Arg Type",         v=inargtype))
                print ("xxx {m:30s}: {v}".format (m="INSN Arg Str",          v=inargstr))
                print ("xxx {m:30s}: {v}".format (m="INSN Reg OpC Lst",      v=bftouse[out_bitlst_out_opc_lst_at]))
                print ("xxx {m:30s}: {v}".format (m="INSN Reg Arg Lst",      v=bftouse[out_bitlst_reg_val_lst_at]))
                print ("xxx {m:30s}: {v}".format (m="INSN Reg Num Val",      v=numvalofarg))
                print ("xxx {m:30s}: {v}".format (m="INSN Reg Reg Val",      v=regvalofarg))
    
                if (inargtype == "f"):
                    argstr = get_reg_name (regvalofarg, "f")
                elif (inargtype == "c"):
                    argstr = get_reg_name (regvalofarg, "c")
                elif (inargtype == "a"):
                    argstr = get_reg_name (regvalofarg, "a")
                elif (inargtype == "g"):
                    argstr = get_specific_reg_names (inargstr, regvalofarg)
                elif (inargtype == "n"):
                    argstr = get_numeric_value (inargstr, regvalofarg)
                else:
                    argstr = get_reg_gname (regvalofarg)
                    
                # print ("xxx {m:30s}: {v}".format (m="INSN ArgStr Found",     v=argstr))
                # print ("xxx {m:30s}: {v}".format (m="INSN ArgStr Found",
                #                                   v=argstr if (argstr != "") else "NULL"))
                
                # # Generate strings for detailed commenting
                # if ((inargstr.find ("rs1")     != -1) or # Source register #1
                #     (inargstr.find ("rs2")     != -1) or # Source register #2
                #     (inargstr.find ("rd")      != -1) or # Destination register
                #     False):
                #     if (inargtype == "f"):
                #         argstr = get_reg_name (numvalofarg, "f")
                #     elif (inargtype == "c"):
                #         argstr = get_reg_name (numvalofarg, "c")
                #     elif (inargtype == "a"):
                #         argstr = get_reg_name (numvalofarg, "a")
                #     # elif (inargtype == "g"):
                #     #     argstr = get_specific_reg_names (inargstr, numvalofarg)
                #     elif (inargtype == "n"):
                #         argstr = get_numeric_value (inargstr, numvalofarg)
                #     else:
                #         argstr = get_reg_gname (numvalofarg)

                # # Generate strings for detailed commenting
                # if ((inargstr.find ("rs1")     != -1) or # Source register #1
                #     (inargstr.find ("rs2")     != -1) or # Source register #2
                #     (inargstr.find ("rd")      != -1) or # Destination register
                #     False):
                #     numvalofarg = bftouse[out_bitlst_out_opc_lst_at][i]
                #     argstr = get_reg_gname (numvalofarg)
                    
                if ((inargstr.find ("imm7")    != -1) or # immediate value
                    (inargstr.find ("simm13")  != -1) or # immediate value
                    (inargstr.find ("imm22")   != -1) or # immediate value
                    (inargstr.find ("disp22")  != -1) or # immediate value
                    (inargstr.find ("const22") != -1) or # immediate value
                    (inargstr.find ("disp30")  != -1) or # immediate value
                    (inargstr.find ("asi")     != -1) or # immediate value
                    False):
                    numvalofarg = bftouse[out_bitlst_out_opc_lst_at][i]
                    argstr = "0x{v:08X}".format (v=numvalofarg)

                
                # if (inargstr.find ("rs1") != -1): # Source register #1
                #     numvalofarg = bftouse[out_bitlst_reg_val_lst_at][i]
                #     argstr = get_reg_gname (numvalofarg)
                # if (inargstr.find ("rs2") != -1): # Source register #2
                #     numvalofarg = bftouse[out_bitlst_reg_val_lst_at][i]
                #     argstr = get_reg_gname (numvalofarg)
                # if (inargstr.find ("rd") != -1): # Destination register
                #     numvalofarg = bftouse[out_bitlst_reg_val_lst_at][i]
                #     argstr = get_reg_gname (numvalofarg)
                # if (inargstr.find ("imm22") != -1): # immediate value
                #     numvalofarg = bftouse[out_bitlst_out_opc_lst_at][i]
                #     argstr = "0x{v:08X}".format (v=numvalofarg)
                # if (inargstr.find ("imm7") != -1): # immediate value
                #     numvalofarg = bftouse[out_bitlst_out_opc_lst_at][i]
                #     argstr = "0x{v:08X}".format (v=numvalofarg)
                # # if (inargstr.find ("sign_ext (simm13)") != -1): # immediate value
                # #     numvalofarg = bftouse[out_bitlst_out_opc_lst_at][i]
                # #     argstr = "0x{v:08X}".format (v=numvalofarg)
                # if (inargstr.find ("simm13") != -1): # immediate value
                #     numvalofarg = bftouse[out_bitlst_out_opc_lst_at][i]
                #     argstr = "0x{v:08X}".format (v=numvalofarg)
                # if (inargstr.find ("disp22") != -1): # immediate value
                #     numvalofarg = bftouse[out_bitlst_out_opc_lst_at][i]
                #     argstr = "0x{v:08X}".format (v=numvalofarg)
                # if (inargstr.find ("const22") != -1): # immediate value
                #     numvalofarg = bftouse[out_bitlst_out_opc_lst_at][i]
                #     argstr = "0x{v:08X}".format (v=numvalofarg)
                    
                # Generate specific register names as strings for detailed commenting
                if ((inargstr.find ("%psr") != -1) or # Processor State Register
                    (inargstr.find ("%wim") != -1) or # Window Invalid Mask
                    (inargstr.find ("%tbr") != -1) or # Trap Base Register
                    (inargstr.find ("%fsr") != -1) or # Floating point State Register
                    (inargstr.find ("%fq")  != -1) or # Floating deferred trap Queue
                    (inargstr.find ("%csr") != -1) or # Coprocessor State Register
                    (inargstr.find ("%cq")  != -1) or # Coprocessor deferred trap Queue
                    (inargstr.find ("%y")   != -1) or # Y (Multiply/Divide) Register
                    False):
                    numvalofarg = bftouse[out_bitlst_out_opc_lst_at][i]
                    argstr = "0x{v:08X}".format (v=numvalofarg)

            # thisreslst = [fst[i], argnum, argstr, numvalofarg, otherstr]        
            thisreslst = [fst[i], argnum, argstr, numvalofarg, otherstr, regvalofarg]        

            reslst.append (thisreslst)
            build_list_of_opcodes (insn, rst, bf, reslst, (rec + 1))
            
def do_final_expansion (insn):
    '''
    The  final  expander:
    
    This is where we need  (iterative or recursive) depth first list
    flattening.

    Our insn  has been fully  populated with all the  information to
    generate the  final opcode and other  information.  However each
    exists as a separate part in each bitfield list within the insn.
    This is a  driver function that runs over all  the bitfield list
    of the  given insn.  It  then calls the  list builder to  do the
    actual work.

    The results of  the list builder are then  formatted for display
    and printed on the output  device.  Doing the output here allows
    us to reuse some lists and hence economise on the memory.
    '''

    global call_depth, maxindent
    global fin_expans
    global expanded_insns
    
    call_depth = call_depth + 1
    maxindent = 4 if (verbosity_level > 4) else verbosity_level
    
    bit_fields = insn [insn_fmt_index_at]
    num_bit_fields = len (bit_fields)

    if (verbosity_level > 0):
        # print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {i}".
        #        format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent),
        #               m="Final INSN Expansion", i=insn))
        print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}:".
               format(c=call_depth,
                      mi=maxindent,
                      p=".",
                      w=(3*maxindent),
                      m="Final INSN Expansion"))
        pp.pprint (insn)

    # Extract the expanded bit lists into a list of lists.
    oclst = []

    for bf in bit_fields:
        oclst.append (bf[out_bitlst_out_opc_lst_at])

    fe = build_list_of_opcodes (insn, oclst, bit_fields, [], 0)

    print ("\n\nALERT: We stop before - final_expanded_insns (fin_expans) with fin_expans as:\n")
    pp.pprint (fin_expans)
    # sys.exit (0)
    xx = final_expanded_insns (fin_expans) # Note: xx is assigned but not used.
    print_results (expanded_insns)

    fin_expans.clear ()
    expanded_insns.clear ()

    if (verbosity_level > 0):
        print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}".
               format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent),
                      m="DONE Final INSN Expansion"))

    call_depth = call_depth - 1
    return insn

def final_expanded_insns (fe):
    '''
    Assemble each opcode and details for printing out.
    '''
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if (verbosity_level > 4) else verbosity_level
    
    # Format of output list:    [opcode, mnemonic, arg1, arg2, arg3, arg4, cmtstr, a1val, a2val, a3val, a4val]
    # Format of output offsets: [0       1         2     3     4     5     6,      7,     8,     9,     10]
    for the_i in fe:
        h = "0x{o:08X}".format (o=the_i[0])  # Opcode printed as 8 digit hexadecimal string
        b = "0x{o:032b}".format (o=the_i[0]) # Opcode printed as a 32 bit binary string
        a = "{m} {a1}{a2}{a3}{a4}".format (  # The ASM version of the instruction with arguments.
            m=the_i [1],         # the_i name
            a1=the_i [2]        if (the_i [2] != "") else "",   # arg 1, if any
            a2=", " + the_i [3] if (the_i [3] != "") else "",   # arg 2, if any
            a3=", " + the_i [4] if (the_i [4] != "") else "",   # arg 3, if any
            a4=", " + the_i [5] if (the_i [5] != "") else "",   # arg 4, if any
        )
        v = "{m} {a1}{a2}{a3}{a4}".format ( # Description of the instruction
            m=asm_comment_str,
            a1=("arg1 = "   + str(the_i [7]))  if (the_i [7]  != -1) else "",   # arg 1, if any
            a2=(", arg2 = " + str(the_i [8]))  if (the_i [8]  != -1) else "",   # arg 2, if any
            a3=(", arg3 = " + str(the_i [9]))  if (the_i [9]  != -1) else "",   # arg 3, if any
            a4=(", arg4 = " + str(the_i [10])) if (the_i [10] != -1) else "",   # arg 4, if any
        )
        c = "{s1} {c}".format (s1=asm_comment_str, c=the_i[6])
        output = "{h} | {b} | {a} {v} {c}".format (h=h, b=b, a=a, v=v, c=c)
        expanded_insns.append (output)

    call_depth = call_depth - 1
    return expanded_insns

def expand_all_insns (il):
    '''This is the expander!
    
    We  implement  the format  based  approach  found from  page  44
    onwards in  the SPARC V8 manual.   This is pretty much  the same
    idea as  the GNU Binutils  implementation to support  the SPARC.
    However  the C  implementation and  this Python3  implementation
    look very different!

    This function is  a simple driver that iterates over  each insn in
    the  database  of  instructions  and calls  the  expander  for  an
    individual insn.  There are two main filters here: (a) filter that
    selects only  the insn  given, and (b)  filter that  selects insns
    belonging to the  category.  Both the filters may be  given on the
    command line.  If no filter is given, then we generate for all the
    insns in the database.
    '''
    
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if (verbosity_level > 4) else verbosity_level
    
    if (verbosity_level > 0):   # Detail level: 1
       print ("=== {c:02d}/{mi:02d} {p:{w}s}Expander started".
              format(c=call_depth, mi=maxindent, p=".", w=(3*1)))
       
    insn_iterator = iter (il)
    out_insns_lst = []
    
    for insn in insn_iterator:
        if (insn [insn_name_at] != "Opcode"): # SKIP the headers list
            if (doinsncategory == True):
                if (insn [insn_category_ind_at] == insncategory):
                    out_insns_lst = expand_insn (insn)
            elif (doinsnexpand == True):
                  if (insn [insn_name_at] == insntoexpand):
                      out_insns_lst = expand_insn (insn)
            else:
                out_insns_lst = expand_insn (insn)
                
    call_depth = call_depth - 1
    if (verbosity_level > 0):   # Detail level: 1
        print ("=== {c:02d}/{mi:02d} {p:{w}s}DONE Expander".
               format(c=call_depth, mi=maxindent, p=".", w=(3*1)))
    
    return out_insns_lst

def neat_print (l):
    numperline = 5
    numentries = len (l)
    numlines   = numentries // numperline
    remainent  = numentries % numperline
    
    for i in range (numlines):
        for j in range (numperline):
            enttoprn = (i * numperline) + j

def print_results (ei):
    for i in ei:
        print (i)
            
# "Main" program.  We are now using the __main__
def main ():
    setup_globals()
    parse_command_line ()

    # Read in the  data.
    fmtlst  = read_data_file (insnformatscsv)
    insnlst = read_data_file (insnlistcsv)

    fl = make_lists_of_flat_bit_fields_in_formats (fmtlst)
    il = replace_format_specs_by_lists (insnlst, fl)
    new_il = expand_all_insns (il)

    return

if __name__ == "__main__":
    main()
