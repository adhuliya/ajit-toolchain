#!/usr/bin/env python3.6

# Generate asm code of all  possible bit patterns.  Some of them could
# be wrong but we generate them nevertheless in this version.
#
# This is a purely procedural style code; no OOP here.

# Added command line processing using the argparse() library. 22-May-2020, AMV

# Economising on  expansion lists.   As the instructions  are expanded
# the lists  containing the expansions  increase rapidly in  size.  We
# try  to reuse  the  lists.   Once an  instruction  pattern has  been
# expanded, we immediately  print it out, and reuse the  lists for the
# next instruction pattern.

import csv
import os
import pprint   as pp           # pretty printer
import sys
import pathlib  as pl
import argparse as ap

#####
# Information section
#####

def setup_globals():
    # Declare the globals
    global script_name
    global parser, args
    global top, curr_dir, tmpdir, indentstr
    global insnformatscsv, insnlistcsv, verbosity_level
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

    global out_bitlst_is_arg_num_at
    global out_bitlst_bf_name_at
    global out_bitlst_bf_val_type_at
    global out_bitlst_out_opc_lst_at
    global out_bitlst_reg_val_lst_at
    global out_bitlst_given_val_at

    global fin_expans         # The Master list of all expansions.
    global expanded_insns
    
    global insn_iterator
    global fmt_iterator
    global bit_fields_iterator

    global list_length_max
    global max_list_length_bits
    global asm_comment_str

    # Directory structure
    top = '/lindata/My-work/Professional/iitb/development'
    asmgentop = top + '/asmgen'
    asmgencode = asmgentop + '/code'
    asmgendata = asmgentop + '/data'
    asmgenccode = asmgencode + '/c'
    asmgenpycode = asmgencode + '/python'
    asmgenschemecode = asmgencode + '/scheme'

    tmpdir = '/tmp'               # Temporary work area. Check for existence

    # ### Input  file names.   The defaults  are actually  set by  the
    # ### argparse module!
    insnformatscsv = asmgendata + '/' + 'smf.csv'     ### 'sparc-manual-formats.csv'
    insnlistcsv = asmgendata + '/' + 'sie3.csv'        ### 'sparc-insn-expand.csv'
    # ### Input file names.   The defaults otherwise!
    ### insnformatscsv = asmgendata + '/' + 'sparc-manual-formats.csv'
    ### insnlistcsv = asmgendata + '/' + 'sparc-insn-expand.csv'

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
    insn_asm_mnemonic_at    = 14
    insn_asm_num_args_at    = 15
    insn_asm_arg_1_at       = 16
    insn_asm_arg_2_at       = 17
    insn_asm_arg_3_at       = 18
    insn_asm_arg_4_at       = 19
    insn_info_end_at        = 20
    insn_expanded_fields_at = 21

    # List fields offsets: FORMATS list
    fmt_name_at           = 0
    fmt_index_at          = 0            # alias for format name
    fmt_num_bit_fields_at = 1
    fmt_bit_field_list_at = 2

    # List fields offsets: BIT FIELDS list
    bit_field_name_at             = 0
    bit_field_end_at              = 1
    bit_field_start_at            = 2
    bit_field_length_at           = 3
    bit_field_val_str_at          = 4
    bit_field_val_type_at         = 5
    # The fields from  this one onwards are not a  part of information
    # stored on secondary memory.
    bit_field_mask_at             = 6
    bit_field_pattern_str_at      = 7
    bit_field_processing_state_at = 8
    bit_field_val_lst_at          = 9

    # Outputs: Each expansion of the patterns has the following fields.
    insn_source_at                = 1 # Index into  the  source
                                      # instructions  list   that  was
                                      # expanded to  this.  One source
                                      # insn can  yield more  than one
                                      # expansions.
    insn_32_bit_string_at         = 2 # Each bit of the 32 bit instruction

    insn_integer_code_at          = 3 #  8 hex digits representation -
                                      # the actual machine code!
    insn_asm_string_list_at       = 4 # ASM code
    insn_asm_comment_at           = 5 # Brief   explanation.
                                      # Particularly  for ranges,  and
                                      # manual page/section!

    out_bitlst_is_arg_num_at      = 0
    out_bitlst_bf_name_at         = 1
    out_bitlst_bf_val_type_at     = 2
    out_bitlst_out_opc_lst_at     = 3
    out_bitlst_reg_val_lst_at     = 4
    out_bitlst_given_val_at       = 5

    expanded_insn_opcode_at       = 0
    expanded_insn_asm_code_at     = 1
    expanded_insn_comment_at      = 2
    # This  is the  copy of  the expanded  bit lists  to fill  in more
    # comment details.
    expanded_insn_fmt_lists_at    = 3 

    fin_expans = []
    expanded_insns = []
    
    # Maximum length of generated lists.
    #
    # We  check if  the possible  length of  the list  to generate  is
    # larger than this.   If larger than we specify  the _range_.  For
    # example, the disp30 is a 30  bit field that will generate 2^{30}
    # possible values.   Not worth  its while  at all.   Hence replace
    # this by the range: 0 - 2^{30}.
    max_list_length_bits = 5
    list_length_max = 2 ^ max_list_length_bits
    
    indentstr="..."
    asm_comment_str = "#;|"

    script_name = pl.PurePosixPath(sys.argv[0]).name
    verbosity_level =  0        # By  default  we are very  quiet, and
                                # generate only the output asked!
    MAX_SPARC_REGS = 32
    call_depth = 0

#####
# I/O functions section
#####

# print("{p:{w}s}{m}: {f:82s} ...".format(c=call_depth, mi=maxindent, p=" ", w=(3*verbosity_level), m="Reading data file", f=df), end='')
# Read in data files
def read_data_file(df):
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if ((3*call_depth) > 12) else call_depth
    
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
    global insnformatscsv, insnlistcsv, verbosity_level
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if ((3*call_depth) > 12) else call_depth

    dmsg="Generate machine code bit patterns and their ASM syntax for all possible "
    dmsg=dmsg + "SPARC V8 instruction combinations."
    emsg="Use the SPARC V8 manual for any names needed, e.g. the instruction to expand. "
    emsg=emsg + "WARNING: Not all the details in the manual are implemented. "
    emsg=emsg + "Some output may be wrong."
    parser = ap.ArgumentParser(description=dmsg, epilog=emsg)
    parser.add_argument("-v", "--verbosity", action="count",
                        default=0, help="increase output verbosity")
    parser.add_argument("-f", "--formatsfile", action="store", nargs='?',
                        default=asmgendata + '/' + 'smf.csv',
                        help="Specify the CSV file with instruction formats")
    parser.add_argument("-i", "--insnsfile", action="store", nargs='?',
                        default=asmgendata + '/' + 'sparc-insn-expand.csv',
                        help="Specify the CSV file with instructions")
    parser.add_argument("-e", "--expandinsn", action="store", nargs='?',
                        default="ld",
                        help="[ToDo] Specify a specific instruction to expand")
    parser.add_argument("-c", "--category", action="store", nargs='?', choices=[1, 2, 3, 4, 5, 6],
                        default=1,
                        help="[ToDo] Specify a specific category of instructions to expand")
    args = parser.parse_args()
    # print (args)

    if args.formatsfile:
        ### Input file names
        insnformatscsv = "{v}".format(v=args.formatsfile)
        
    if args.insnsfile:
        insnlistcsv = args.insnsfile

    verbosity_level = args.verbosity

    if (call_depth < verbosity_level):
       print("{m:20s}: {f}".format(m="Verbosity level", f=verbosity_level))
        
    call_depth = call_depth - 1
    return

def check_and_create_if_necessary(the_dir):
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if ((3*call_depth) > 12) else call_depth
    
    if not os.path.exists(the_dir):
        os.mkdir(the_dir, mode=0o777)
    call_depth = call_depth - 1
    return os.path.exists(the_dir)

def system_setup():
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if ((3*call_depth) > 12) else call_depth

    curr_dir = os.getcwd()        # Current directory
    os.chdir(top)

    check_and_create_if_necessary(tmpdir)
    curr_dir = os.getcwd()
    if (call_depth < verbosity_level):
       print ("Curr dir: {d}".format (d=curr_dir))
    
    call_depth = call_depth - 1
    return

#####
# Processing functions section
#####

def get_mask_of_length (masklen):
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if ((3*call_depth) > 12) else call_depth
    
    val = 0
    i = 0
    while (i < masklen):
        set_bit = 0x1 << i
        val = val | set_bit
        i = i + 1
        
    call_depth = call_depth - 1
    return val

def make_lists_of_flat_bit_fields_in_formats (fl):
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if ((3*call_depth) > 12) else call_depth
    
    n = len (fl)
    result = []
    for i in range (n):
        result.append (reorganise_formats_list (fl[i], i))

    call_depth = call_depth - 1
    return result
    
def reorganise_formats_list (fl, hdr):
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if ((3*call_depth) > 12) else call_depth
    
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
            mask             = "MAXMASKVAL"
            pattern_str      = "PATTERN STR"
            processing_state = "BIT Field Processing State"
            value_list       = "List of Values"
        else:
            name             = sl[field_offset + bit_field_name_at]
            start            = int (sl[field_offset + bit_field_start_at])
            end              = int (sl[field_offset + bit_field_end_at])
            length           = end - start + 1
            value            = sl[field_offset + bit_field_val_str_at]
            value_type       = sl[field_offset + bit_field_val_type_at]
            mask             = get_mask_of_length (length)
            pattern_str      = ""
            processing_state = "raw" # Initialise to "raw". Update as we process bit field lists.
            value_list       = []
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
    return reformatted_list

def get_fmt_list_from_fmt_index (fmt_index, fl):
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if ((3*call_depth) > 12) else call_depth
    
    fmt_list = []
    fls = []
    num_parts = fmt_index.count ("|")

    srchstr = fmt_index
    i = 0
    while (i <= num_parts):
        parts = srchstr.partition ('|')
        fmtstr = parts[0]
        srchstr = parts[2]

        the_lst = get_format_given_str (fmtstr, fl)

        if (the_lst != []):
            fmt_list.append (the_lst)
        
        i = i + 1

    call_depth = call_depth - 1
    return fmt_list

def get_format_given_str (fmt_str, fl):
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if ((3*call_depth) > 12) else call_depth
    
    ans = []

    for i in range (len (fl)):
        if (fl[i][0] == fmt_str):
            ans = fl[i]
            break
        
    call_depth = call_depth - 1
    return ans

def replace_format_specs_by_lists (il, fl):
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if ((3*call_depth) > 12) else call_depth
    
    all_insns = len (il)
    all_fmts  = len (fl)
    fmt_fld   = insn_fmt_index_at

    for i in range (0, all_insns):
        il[i][fmt_fld] =  get_fmt_list_from_fmt_index (il[i][fmt_fld], fl)
    
    call_depth = call_depth - 1
    return il
    
def set_bit (bitno, toReset):
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if ((3*call_depth) > 12) else call_depth
    
    retval = 0
    if (bitno >= 0) and (bitno <= 31):
        retval = retval | (0x1 << bitno)

    call_depth = call_depth - 1
    return (retval if (toReset == False) else (0xFFFFFFFF - retval))

def make_bit_mask (end, start):
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if ((3*call_depth) > 12) else call_depth
    
    theval  = pow (2, (end - start) + 1) - 1
    maskval = theval << start
    minusmaskval = 0xFFFFFFFF - maskval
        
    call_depth = call_depth - 1
    return maskval

def do_given (bitfld, insn, is_arg_num):
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if ((3*call_depth) > 12) else call_depth
    
    # print ("=== ... ... ... ... {m:20s}: {l}".format(m="Doing GIVEN", l=bitfld))
    if (call_depth < verbosity_level):
       print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent),
                     m="Doing GIVEN", l=bitfld))
    out_lst = []
    out_opc_lst = []
    reg_val_lst = []

    bf_name     = bitfld [bit_field_name_at]
    bf_end      = bitfld [bit_field_end_at]
    bf_start    = bitfld [bit_field_start_at]
    bf_nbits    = bitfld [bit_field_length_at]
    bf_given    = bitfld [bit_field_val_str_at]
    bf_val_type = bitfld [bit_field_val_type_at]
    bf_mask     = make_bit_mask (bf_start, bf_end)
    
    useval = int (bf_given, 16)
    theval = useval
    useval = (useval << bf_end)

    out_opc_lst = [useval]
    out_lst = [is_arg_num, bf_name, bf_val_type, out_opc_lst, reg_val_lst, theval]
    # print ("=== ... ... ... ... {m:20s}: {l}".format(m="DONE Doing GIVEN", l=out_lst))
    if (call_depth < verbosity_level):
       print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent),
                     m="DONE Doing GIVEN", l=out_lst))
    
    call_depth = call_depth - 1
    return out_lst

def do_lookup (bitfld, insn, is_arg_num):
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if ((3*call_depth) > 12) else call_depth
    
    if (call_depth < verbosity_level):
       print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent),
                     m="Doing LOOKUP", l=bitfld))
    out_lst = []
    out_opc_lst = []
    reg_val_lst = []

    bf_name     = bitfld [bit_field_name_at]
    bf_end      = bitfld [bit_field_end_at]
    bf_start    = bitfld [bit_field_start_at]
    bf_nbits    = bitfld [bit_field_length_at]
    bf_given    = bitfld [bit_field_val_str_at]
    bf_val_type = bitfld [bit_field_val_type_at]
    bf_mask     = make_bit_mask (bf_start, bf_end)
    
    value_str_found = insn [insn_format_value_at]
    useval = int (value_str_found, 2)
    theval = useval
    useval = (useval << bf_end)

    out_opc_lst = [useval]
    out_lst = [is_arg_num, bf_name, bf_val_type, out_opc_lst, reg_val_lst, theval]
    if (call_depth < verbosity_level):
       print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent),
                     m="DONE Doing LOOKUP", l=out_lst))

    out_lst = [is_arg_num, bf_name, bf_val_type, out_opc_lst, reg_val_lst, theval]
    
    call_depth = call_depth - 1
    return out_lst

def do_generate (bitfld, insn, is_arg_num):
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if ((3*call_depth) > 12) else call_depth
    
    if (call_depth < verbosity_level):
       print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent),
                     m="Doing GENERATE", l=bitfld))
    out_lst = []
    out_opc_lst = []
    reg_val_lst = []

    bf_name     = bitfld [bit_field_name_at]
    bf_end      = bitfld [bit_field_end_at]
    bf_start    = bitfld [bit_field_start_at]
    bf_nbits    = bitfld [bit_field_length_at]
    bf_given    = bitfld [bit_field_val_str_at]
    bf_val_type = bitfld [bit_field_val_type_at]
    bf_mask     = make_bit_mask (bf_start, bf_end)

    theval = -1                 # Does not make sense here :-(.
    if (bf_nbits <= max_list_length_bits):
        num_vals = pow (2, bf_nbits)
        for i in range (num_vals):
            useval = i
            reg_val_lst.append (useval)

            useval = (useval << bf_end)
        
            out_opc_lst.append (useval)
    else:
        print ("ERROR: Range for bitfield \"{n}\" exceeds maximum.  Max #bits: {m}, Given #bits: {g}".
               format (n=bf_name, m=max_list_length_bits, g=bf_nbits))

    out_lst = [is_arg_num, bf_name, bf_val_type, out_opc_lst, reg_val_lst, theval]
    if (call_depth < verbosity_level):
       print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent),
                     m="DONE Doing GENERATE", l=out_lst))

    call_depth = call_depth - 1
    return out_lst

def do_range (bitfld, insn, is_arg_num):
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if ((3*call_depth) > 12) else call_depth
    
    if (call_depth < verbosity_level):
       print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent),
                     m="Doing RANGE", l=bitfld))
    out_lst = []
    out_opc_lst = []
    reg_val_lst = []

    bf_name     = bitfld [bit_field_name_at]
    bf_end      = bitfld [bit_field_end_at]
    bf_start    = bitfld [bit_field_start_at]
    bf_nbits    = bitfld [bit_field_length_at]
    bf_given    = bitfld [bit_field_val_str_at]
    bf_val_type = bitfld [bit_field_val_type_at]
    bf_mask     = make_bit_mask (bf_start, bf_end)

    min = 0
    max = pow (2, bf_nbits) # Careful: This could be a very large number, e.g. > 24 bits!

    # print ("=== ... ... ... ...    {m:20s}: {d}".format(m="Num bits", d= bf_nbits))
    # print ("=== ... ... ... ...    {m:20s}: {d:032b}".format(m="Bit mask", d= bf_mask))
    theval = -1                 # Does not make sense here
    useval = min
    useval = (useval << bf_end)
    # print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l:032b} ({d})".format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent), m="Field Min val", l=min, d=min))
    # print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l:032b} ({d})".format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent), m="Min val", l=useval, d= useval))
    
    out_opc_lst.append (useval)
    
    useval = max
    useval = (useval << bf_end) - 1
    # print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l:032b} ({d})".format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent), m="Field Max val", l=min, d=max))
    # print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l:032b} ({d})".format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent), m="Max val", l=useval, d= useval))
    
    out_opc_lst.append (useval)
    
    out_lst = [is_arg_num, bf_name, bf_val_type, out_opc_lst, reg_val_lst, theval]
    if (call_depth < verbosity_level):
       print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent),
                     m="DONE Doing RANGE", l=out_lst))

    call_depth = call_depth - 1
    return out_lst

def do_set (bitfld, insn, is_arg_num):
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if ((3*call_depth) > 12) else call_depth
    
    if (call_depth < verbosity_level):
       print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent),
                     m="Doing RANGE", l=bitfld))
    out_lst = []
    out_opc_lst = []
    reg_val_lst = []

    bf_name     = bitfld [bit_field_name_at]
    bf_end      = bitfld [bit_field_end_at]
    bf_start    = bitfld [bit_field_start_at]
    bf_nbits    = bitfld [bit_field_length_at]
    bf_given    = bitfld [bit_field_val_str_at]
    bf_val_type = bitfld [bit_field_val_type_at]
    bf_mask     = make_bit_mask (bf_start, bf_end)

    useval = int (bf_given, 16)
    theval = useval
    useval = (useval << bf_end)
    
    out_opc_lst.append (useval)
    
    out_lst = [is_arg_num, bf_name, bf_val_type, out_opc_lst, reg_val_lst, theval]
    if (call_depth < verbosity_level):
       print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent),
                     m="DONE Doing RANGE", l=out_lst))

    call_depth = call_depth - 1
    return out_lst

def is_which_arg (bitfld, insn):
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if ((3*call_depth) > 12) else call_depth
    
    argnum = -1
    
    bf_name  = bitfld [bit_field_name_at]
    num_args = insn [insn_asm_num_args_at]

    for i in range (int (num_args, 10)):
        if   (bf_name == insn [insn_asm_arg_1_at]):
            argnum = 1
        elif (bf_name == insn [insn_asm_arg_2_at]):
            argnum = 2
        elif (bf_name == insn [insn_asm_arg_3_at]):
            argnum = 3
        elif (bf_name == insn [insn_asm_arg_4_at]):
            argnum = 4
        else:
            argnum = -1
            
    call_depth = call_depth - 1
    return argnum

def get_reg_rname (regno):
    return "%r" + str (regno) if (0 <= regno <= MAX_SPARC_REGS) else ""

def get_reg_gname (regno):
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if ((3*call_depth) > 12) else call_depth
    
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
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if ((3*call_depth) > 12) else call_depth
    
    bitlst = []
    n = 0
    gen_bitvals_lst = []
    rng_pat_str_lst = []
    
    if (call_depth < verbosity_level):
       print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent),
                     m="Expanding BIT FLD", l=bitfld))
    
    bf_is_arg_num = is_which_arg (bitfld, insn) # -1 # write a function to get the argument number!
    bf_val_type = bitfld [bit_field_val_type_at]
    
    if (bf_val_type == "generate"):
       bitlst = do_generate (bitfld, insn, bf_is_arg_num)
    
    if (bf_val_type == "given"):
        bitlst = do_given (bitfld, insn, bf_is_arg_num)
    
    if (bf_val_type == "range"):
        bitlst = do_range (bitfld, insn, bf_is_arg_num)
    
    if (bf_val_type == "set"):
        bitlst = do_set (bitfld, insn, bf_is_arg_num)
    
    if (bf_val_type == "lookup"):
        bitlst = do_lookup (bitfld, insn, bf_is_arg_num)
    
    if (call_depth < verbosity_level):
       print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent),
                     m="Bit Field Expanded to", l=bitlst))

    if (call_depth < verbosity_level):
       print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent),
                     m="DONE Expanding Bit Field", l=bitfld))
    
    call_depth = call_depth - 1
    return bitlst

def expand_insn (insn):
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if ((3*call_depth) > 12) else call_depth
    
    if (call_depth < verbosity_level):
       print ("=== {c:02d}/{mi:02d} {p:{w}s}Expanding insn: {l}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent),
                     l=insn))
       print ("=== {c:02d}/{mi:02d} {p:{w}s}   {m:20s}: {n}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent),
                     m="INSN name", n=insn[insn_name_at]))
       print ("=== {c:02d}/{mi:02d} {p:{w}s}   {m:20s}: {l}".
              format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent),
                     m="Using format", l=insn [insn_fmt_index_at][0][0]))
            
    expanded_outlst = []
    fmt_iterator = iter (insn [insn_fmt_index_at])

    for fmt in fmt_iterator:
        if (call_depth < verbosity_level):
            print ("=== {c:02d}/{mi:02d} {p:{w}s}   {m:20s}: {n}".
                   format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent),
                          m="FMT name", n=fmt [fmt_name_at]))
            
        bit_fields_iterator = iter (fmt [fmt_bit_field_list_at])
        
        total_bits = 0
        theOpcode  = 0xFFFFFFFF # Set the fields with bitwise ANDs
        tmpintval  = 0
        num_bitflds = fmt [fmt_num_bit_fields_at]
        len_bitflds = len(fmt [fmt_bit_field_list_at])
        for bitfld in bit_fields_iterator:
            thlst = expand_bit_field (bitfld, insn)
            if (call_depth < verbosity_level):
                print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
                       format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent),
                              m="Appending bitfield", l=thlst))
            expanded_outlst.append (thlst)

        num_bitflds_processed = len (expanded_outlst)
        
    insn [insn_fmt_index_at] = expanded_outlst
    if (call_depth < verbosity_level):
        print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
               format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent),
                      m="Expanded insn", l=insn[insn_fmt_index_at]))

    do_final_expansion (insn)
    if (call_depth < verbosity_level):
        print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
               format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent),
                      m="DONE Expanding insn", l=insn))

    call_depth = call_depth - 1
    return insn

def get_opcode (l):
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if ((3*call_depth) > 12) else call_depth
    
    x = 0
    for i in l:
        x = x | i[0]

    call_depth = call_depth - 1
    return x

# INSN:
# [
#  'LDSB',                                       # insn_name_at            = 0
#  'op3',                                        # insn_format_type_at     = 1
#  '001001',                                     # insn_format_value_at    = 2
#  'i',                                          # insn_other_field_at     = 3
#  '000000',                                     # insn_other_value_at     = 4
#  'Load Signed Byte',                           # insn_op_desc_at         = 5
#  '90',                                         # insn_page_num_at        = 6
#  'B1',                                         # insn_chap_ref_at        = 7
#  'Load/Store',                                 # insn_category_at        = 8
#  '1',                                          # insn_category_ind_at    = 9 
#  [                                             # insn_fmt_index_at       = 10
#   [-1, 'op', 'given', [3221225472], []],       # 
#   [3,                                          # out_bitlst_is_arg_num_at      = 0
#    'rd',                                       # out_bitlst_bf_name_at         = 1
#    'generate',                                 # out_bitlst_bf_val_type_at     = 2
#    [0, 33554432, ..., 1006632960, 1040187392], # out_bitlst_out_opc_lst_at     = 3
#    [0, 1, ..., 30, 31]],                       # out_bitlst_reg_val_lst_at     = 4
#   [-1, 'op3', 'lookup', [33030144], []],       # 
#   [1,                                          # 
#    'rs1',                                      # 
#    'generate',                                 # 
#    [0, 16384, ..., 491520, 507904],            # 
#    [0, 1, ..., 30, 31]],                       # 
#   [-1, 'i', 'given', [0], []],                 # 
#   [-1, 'UNUSED', 'given', [0], []],            # 
#   [2,                                          # 
#    'rs2',                                      # 
#    'generate',                                 # 
#    [0, 1, ..., 30, 31],                        # 
#    [0, 1, ..., 30, 31]                         # 
#   ]                                            # 
#  ],                                            # 
#  'raw',                                        # insn_proc_stat_at       = 11
#  '0',                                          # insn_privilege_at       = 12
#  '',                                           # insn_notes_at           = 13
#  'ldsb',                                       # insn_asm_mnemonic_at    = 14
#  '3',                                          # insn_asm_num_args_at    = 15
#  'rs1',                                        # insn_asm_arg_1_at       = 16
#  'rs2',                                        # insn_asm_arg_2_at       = 17
#  'rd',                                         # insn_asm_arg_3_at       = 18
#  '',                                           # insn_asm_arg_4_at       = 19
#  'end'                                         # insn_info_end_at        = 20
# ]

def make_comment_str (insn, other):
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if ((3*call_depth) > 12) else call_depth
    
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
    maxindent = 4 if ((3*call_depth) > 12) else call_depth
    
    thestr = ""
    for l in r:
        if (l[1] == arg):
            thestr = l[2]
            break

    call_depth = call_depth - 1
    return thestr
        
def get_argnum_val (r, arg):
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if ((3*call_depth) > 12) else call_depth
    
    theval = -1
    for l in r:
        if (l[1] == arg):
            theval = l[3]
            break

    call_depth = call_depth - 1
    return theval
        
def build_list_of_opcodes (insn, l, il, res, rec):
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if ((3*call_depth) > 12) else call_depth
    
    reslst = []
    num_asm_args = insn [insn_asm_num_args_at]
    opsubcode = 0
    argnum = -1
    argstr = ""
    numvalofarg = -1
    otherstr = ""

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

    # if (len (l) == 0):
    if (l == []):
        # print ("(Rec: {r}) List is: {l}".format (r=rec, l=res))
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

        # Format of output list: [opcode, mnemonic, arg1, arg2, arg3, arg4, cmtstr, arg1val, arg2val, arg3val, arg4val]
        fin_expans.append ([theopc, insn [insn_asm_mnemonic_at], arg1, arg2, arg3, arg4, cmtstr, arg1val, arg2val, arg3val, arg4val])
        call_depth = call_depth - 1
        return res
    else:
        fst = l[0]
        rst = l[1:]
        numfst = len (fst)
        for i in range (numfst):
            reslst = res.copy()
            # Format of output list: [opsubcode, argnum, argstr, numvalofarg, otherstr]
            opsubcode = fst[i]
            if (il[rec][out_bitlst_given_val_at] != -1): # Record "static" information
                if ((il[rec][out_bitlst_bf_val_type_at] == "given")   or
                    (il[rec][out_bitlst_bf_val_type_at] == "lookup")  or
                    (il[rec][out_bitlst_bf_val_type_at] == "range")  or
                    (il[rec][out_bitlst_bf_val_type_at] == "UNUSED")):
                    otherstr = "{n} = {v}".format (n=il[rec][out_bitlst_bf_name_at], v=il[rec][out_bitlst_given_val_at])
                    
            argnum = il[rec][out_bitlst_is_arg_num_at]
            # print ("yyy Checking InfoLst[{r}]: {v}".format(r=rec, v=il[rec]))
            if (argnum != -1):  # We are some argument in the opcode pattern
                inargstr = il[rec][out_bitlst_bf_name_at]
                # print ("xxx InArgStr: {i} for rec {r}".format (i=inargstr, r=rec))
                # print ("xxx InfoLst[{r}]: {v}".format(r=rec, v=il[rec]))
                # print ("xxx InfoLst[{r}][out_bitlst_reg_val_lst_at]: {v}".format(r=rec, v=il[rec][out_bitlst_reg_val_lst_at]))
                # print ("xxx InfoLst:")
                # pp.pprint (il)
                if (inargstr == "rs1"): # Source register #1
                    numvalofarg = il[rec][out_bitlst_reg_val_lst_at][i]
                    argstr = get_reg_gname (numvalofarg)
                if (inargstr == "rs2"): # Source register #2
                    numvalofarg = il[rec][out_bitlst_reg_val_lst_at][i]
                    argstr = get_reg_gname (numvalofarg)
                if (inargstr == "rd"): # Destination register
                    numvalofarg = il[rec][out_bitlst_reg_val_lst_at][i]
                    argstr = get_reg_gname (numvalofarg)
                if (inargstr == "imm22"): # immediate value
                    numvalofarg = il[rec][out_bitlst_out_opc_lst_at][i]
                    argstr = "0x{v:08X}".format (v=numvalofarg)
                
            thisreslst = [fst[i], argnum, argstr, numvalofarg, otherstr]        
            # print ("xxx InfoLst[{r}][out_bitlst_reg_val_lst_at]: {v}".format(r=rec, v=il[rec][out_bitlst_reg_val_lst_at]))
            reslst.append (thisreslst)
            build_list_of_opcodes (insn, rst, il, reslst, (rec + 1))
            
# The final expander: This is where we need iterative list flattening.
def do_final_expansion (insn):
    global call_depth, maxindent
    global fin_expans
    global expanded_insns
    
    call_depth = call_depth + 1
    maxindent = 4 if ((3*call_depth) > 12) else call_depth
    
    bit_fields = insn [insn_fmt_index_at]
    num_bit_fields = len (bit_fields)

    if (call_depth < verbosity_level):
        print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {i}".
               format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent),
                      m="Final INSN Expansion", i=insn))
        # print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {i}".
        #        format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent),
        #               m="    ... Bit Fields at", i=out_bitlst_out_opc_lst_at))

    # Extract the expanded bit lists into a list of lists.
    oclst = []
    infolst = []

    for bf in bit_fields:
        infolst.append (bf)
        oclst.append (bf[out_bitlst_out_opc_lst_at])

    # if (call_depth < verbosity_level):
    #     print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {d}".
    #            format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent),
    #                   m="#OC Lists:", d=len(oclst)))
    #     print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
    #            format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent),
    #                   m="OC Lists:", l=oclst))
    #     print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {d}".
    #            format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent),
    #                   m="#Info Lists:", d=len(infolst)))
    #     print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}: {l}".
    #            format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent),
    #                   m="Info Lists:", l=infolst))
    build_list_of_opcodes (insn, oclst, infolst, [], 0)

    # ## fin_expans is set inside the function build_list_of_opcodes
    # print ("=== Opcode expansions list ...")
    # # # pp.pprint (fin_expans)
    # # neat_print (fin_expans)
    # print (fin_expans)
    # print ("=== #Opcode expansions list : {v}".format (v=len(fin_expans)))

    xx = final_expanded_insns (fin_expans)
    # print ("=== Final Opcode expansions list ...")
    # pp.pprint (xx)
    # # print (xx)
    # # print ("=== #Final opcode expansions list : {v}".format (v=len(xx)))
    # # All done.
    # print ("Done.")

    print_results (expanded_insns)
    fin_expans = []
    expanded_insns = []

    if (call_depth < verbosity_level):
        print ("=== {c:02d}/{mi:02d} {p:{w}s}{m:20s}".
               format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent),
                      m="DONE Final INSN Expansion"))

    call_depth = call_depth - 1
    return insn

def final_expanded_insns (fe):
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if ((3*call_depth) > 12) else call_depth
    
    # Format of output list:    [opcode, mnemonic, arg1, arg2, arg3, arg4, cmtstr, a1val, a2val, a3val, a4val]
    # Format of output offsets: [0       1         2     3     4     5     6,      7,     8,     9,     10]
    for the_i in fe:
        h = "0x{o:08X}".format (o=the_i[0])
        b = "0x{o:032b}".format (o=the_i[0])
        a = "{m} {a1}{a2}{a3}{a4}".format (
            m=the_i [1],         # the_i name
            a1=the_i [2]        if (the_i [2] != "") else "",   # arg 1, if any
            a2=", " + the_i [3] if (the_i [3] != "") else "",   # arg 2, if any
            a3=", " + the_i [4] if (the_i [4] != "") else "",   # arg 3, if any
            a4=", " + the_i [5] if (the_i [5] != "") else "",   # arg 4, if any
        )
        v = "{m} {a1}{a2}{a3}{a4}".format (
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

# This is the expander!

# We implement the format based approach found from page 44 onwards in
# the SPARC V8 manual.   This is pretty much the same  idea as the GNU
# Binutils  implementation  to  support  the  SPARC.   However  the  C
# implementation and this Python3 implementation look very different!

def expand_all_insns (il):
    global call_depth, maxindent
    call_depth = call_depth + 1
    maxindent = 4 if ((3*call_depth) > 12) else call_depth
    
    if (call_depth < verbosity_level):
       print ("=== {c:02d}/{mi:02d} {p:{w}s}Expander started".
              format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent)))
    insn_iterator = iter (il)
    out_insns_lst = []
    for insn in insn_iterator:
        if (insn [insn_name_at] != "Opcode"): # SKIP the headers list
            out_insns_lst = expand_insn (insn)
    
    if (call_depth < verbosity_level):
        print ("=== {c:02d}/{mi:02d} {p:{w}s}DONE Expander".
               format(c=call_depth, mi=maxindent, p=".", w=(3*maxindent)))
    
    call_depth = call_depth - 1
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
    # system_setup()
    parse_command_line ()

    # Read in the  data.
    fmtlst  = read_data_file (insnformatscsv)
    insnlst = read_data_file (insnlistcsv)
    # print ("=== INSNs list ...")
    ## pp.pprint (insnlst)
    # print (insnlst)

    fl = make_lists_of_flat_bit_fields_in_formats (fmtlst)
    ## pp.pprint (fmtlst)
    ## # print ("=== Format list after reorganising flat bit fields into lists ...")
    ## pp.pprint (fl)
    ## pp.pprint (insnlst)
    
    il = replace_format_specs_by_lists (insnlst, fl)
    ## # print ("=== INSN list after including format list ...")
    ## pp.pprint (il)

    new_il = expand_all_insns (il)
    # print ("=== INSN list after expanding ...")
    # print (new_il)

    # ## fin_expans is set inside the function build_list_of_opcodes
    # print ("=== Opcode expansions list ...")
    # # # pp.pprint (fin_expans)
    # # neat_print (fin_expans)
    # print (fin_expans)
    # print ("=== #Opcode expansions list : {v}".format (v=len(fin_expans)))

    # xx = final_expanded_insns (fin_expans)
    # # print ("=== Final Opcode expansions list ...")
    # # pp.pprint (xx)
    # # # print (xx)
    # # # print ("=== #Final opcode expansions list : {v}".format (v=len(xx)))
    # # # All done.
    # # print ("Done.")

    # print_results (expanded_insns)

    return

if __name__ == "__main__":
    main()
