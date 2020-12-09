#!/usr/bin/env python3.6

# Generate asm code of all  possible bit patterns.  Some of them could
# be wrong but we generate them nevertheless in this version.

import csv
import csv
import os
import pprint as pp                  # pretty printer

#####
# Information section
#####

def setup_globals():
    # Declare the globals
    global top, curr_dir, tmpdir, indentstr
    global insnformatscsv, insnlistcsv
    global fmtlst, insnlst
    global insn_str_template
    global MAX_SPARC_REGS

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
    global bit_field_mask_at      # These onwards are not a part of information stored on secondary memory.
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

    ### Input file names
    insnformatscsv = asmgendata + '/' + 'smf.csv'     ### 'sparc-manual-formats.csv'
    insnlistcsv = asmgendata + '/' + 'sie2.csv'        ### 'sparc-insn-expand.csv'
    ### insnlistcsv = asmgendata + '/' + 'sparc-insn-expand.csv'

    # 32 bit string to fill; using "x" to ease debugging
    insn_str_template = ['x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x']

    # Lists
    fmtlst  = []
    insnlst = []

    # Some global constants
    # List offsets: INSN list
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

    # List offsets: FORMATS list
    fmt_name_at           = 0
    fmt_index_at          = 0            # alias for format name
    fmt_num_bit_fields_at = 1
    fmt_bit_field_list_at = 2

    # List offsets: BIT FIELDS list
    bit_field_name_at             = 0
    bit_field_end_at              = 1
    bit_field_start_at            = 2
    bit_field_length_at           = 3
    bit_field_val_str_at          = 4
    bit_field_val_type_at         = 5
    bit_field_mask_at             = 6 # These onwards are not a part of information stored on secondary memory.
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
    expanded_insn_fmt_lists_at    = 3 # This is the copy of the expanded bit lists to fill in more comment details.
    # expanded_insn_opcode_at       = 0
    # expanded_insn_opcode_at       = 0

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

    MAX_SPARC_REGS = 32
    
#####
# I/O functions section
#####

# Read in data files
def read_data_file(df):
    # print("Reading data file {f:82s} ...".format(f=df), end='')
    rv = []
    with open(df, 'r') as f1:
        raw_data = csv.reader(f1, delimiter=',')
        rv = list(raw_data)
    f1.closed
    # print("Done.")
    return rv

#####
# System and setup functions section
#####

def check_and_create_if_necessary(the_dir):
    if not os.path.exists(the_dir):
        os.mkdir(the_dir, mode=0o777)
    return os.path.exists(the_dir)

def system_setup():

    curr_dir = os.getcwd()        # Current directory
    os.chdir(top)

    check_and_create_if_necessary(tmpdir)
    curr_dir = os.getcwd()

#####
# Processing functions section
#####

def get_mask_of_length (masklen):
    val = 0
    i = 0
    while (i < masklen):
        set_bit = 0x1 << i
        val = val | set_bit
        i = i + 1
        
    return val

def make_lists_of_flat_bit_fields_in_formats (fl):
    n = len (fl)
    result = []
    for i in range (n):
        result.append (reorganise_formats_list (fl[i], i))

    return result
    
def reorganise_formats_list (fl, hdr):
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
    
    return reformatted_list

def get_fmt_list_from_fmt_index (fmt_index, fl):
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

    return fmt_list

def get_format_given_str (fmt_str, fl):
    ans = []

    for i in range (len (fl)):
        if (fl[i][0] == fmt_str):
            ans = fl[i]
            break
        
    return ans

def replace_format_specs_by_lists (il, fl):
    all_insns = len (il)
    all_fmts  = len (fl)
    fmt_fld   = insn_fmt_index_at

    for i in range (0, all_insns):
        il[i][fmt_fld] =  get_fmt_list_from_fmt_index (il[i][fmt_fld], fl)
    
    return il
    
def set_bit (bitno, toReset):
    retval = 0
    if (bitno >= 0) and (bitno <= 31):
        retval = retval | (0x1 << bitno)

    return (retval if (toReset == False) else (0xFFFFFFFF - retval))

def make_bit_mask (end, start):
    theval  = pow (2, (end - start) + 1) - 1
    maskval = theval << start
    minusmaskval = 0xFFFFFFFF - maskval
        
    return maskval

def do_given (bitfld, insn, is_arg_num):
    print ("=== ... ... ... ... {m:20s}: {l}".format(m="Doing GIVEN", l=bitfld))
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
    print ("=== ... ... ... ... {m:20s}: {l}".format(m="DONE Doing GIVEN", l=out_lst))
    
    return out_lst

def do_lookup (bitfld, insn, is_arg_num):
    print ("=== ... ... ... ... {m:20s}: {l}".format(m="Doing LOOKUP", l=bitfld))
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
    print ("=== ... ... ... ... ... {m:20s}: {l:032b} ({d})".format(m="LOOKUP val", l=theval, d=theval))
    print ("=== ... ... ... ... ... {m:20s}: {l:032b} ({d})".format(m="LOOKUP useval", l=useval, d=useval))

    out_opc_lst = [useval]
    out_lst = [is_arg_num, bf_name, bf_val_type, out_opc_lst, reg_val_lst, theval]
    print ("=== ... ... ... ... {m:20s}: {l}".format(m="DONE Doing LOOKUP", l=out_lst))

    out_lst = [is_arg_num, bf_name, bf_val_type, out_opc_lst, reg_val_lst, theval]
    return out_lst

def do_generate (bitfld, insn, is_arg_num):
    print ("=== ... ... ... ... {m:20s}: {l}".format(m="Doing GENERATE", l=bitfld))
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
        print ("=== ... ... ... ... ... {m:16s}: {l} values".format(m="Generating", l=num_vals))
        for i in range (num_vals):
            useval = i
            reg_val_lst.append (useval)

            useval = (useval << bf_end)
        
            out_opc_lst.append (useval)
    else:
        print ("ERROR: Range exceeds maximum.  Max #bits: {m}, Given #bits: {g}".
               format (m=max_list_length_bits, g=bf_nbits))

    out_lst = [is_arg_num, bf_name, bf_val_type, out_opc_lst, reg_val_lst, theval]
    print ("=== ... ... ... ... {m:20s}: {l}".format(m="DONE Doing GENERATE", l=out_lst))

    return out_lst

def do_range (bitfld, insn, is_arg_num):
    print ("=== ... ... ... ... {m:20s}: {l}".format(m="Doing RANGE", l=bitfld))
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

    print ("=== ... ... ... ...    {m:20s}: {d}".format(m="Num bits", d= bf_nbits))
    print ("=== ... ... ... ...    {m:20s}: {d:032b}".format(m="Bit mask", d= bf_mask))
    theval = -1                 # Does not make sense here
    useval = min
    useval = (useval << bf_end)
    print ("=== ... ... ... ...    {m:20s}: {l:032b} ({d})".format(m="Field Min val", l=min, d=min))
    print ("=== ... ... ... ...    {m:20s}: {l:032b} ({d})".format(m="Min val", l=useval, d= useval))
    
    out_opc_lst.append (useval)
    
    useval = max
    useval = (useval << bf_end) - 1
    print ("=== ... ... ... ...    {m:20s}: {l:032b} ({d})".format(m="Field Max val", l=max-1, d=max-1))
    print ("=== ... ... ... ...    {m:20s}: {l:032b} ({d})".format(m="Max val", l=useval, d= useval))
    
    out_opc_lst.append (useval)
    
    out_lst = [is_arg_num, bf_name, bf_val_type, out_opc_lst, reg_val_lst, theval]
    print ("=== ... ... ... ... {m:20s}: {l}".format(m="DONE Doing RANGE", l=out_lst))

    return out_lst

def is_which_arg (bitfld, insn):
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
            
    return argnum

def get_reg_rname (regno):
    return "%r" + str (regno) if (0 <= regno <= MAX_SPARC_REGS) else ""

def get_reg_gname (regno):
    the_gname = ""
    
    if (0 <= regno <= 7):
        the_gname = "%g" + str (regno)      # Global
    if (8 <= regno <= 15):
        the_gname = "%o" + str (regno - 8)  # Out
    if (16 <= regno <= 23):
        the_gname = "%l" + str (regno - 16) # Local
    if (24 <= regno <= 31):
        the_gname = "%i" + str (regno - 24) # In

    return the_gname

def expand_bit_field (bitfld, insn):
    bitlst = []
    n = 0
    gen_bitvals_lst = []
    rng_pat_str_lst = []
    
    print ("=== ... ... ... {m:20s}: {l}".format(m="Expanding BIT FLD", l=bitfld))
    
    bf_is_arg_num = is_which_arg (bitfld, insn) # -1 # write a function to get the argument number!
    bf_val_type = bitfld [bit_field_val_type_at]
    
    if (bf_val_type == "generate"):
       bitlst = do_generate (bitfld, insn, bf_is_arg_num)
    
    if (bf_val_type == "given"):
        bitlst = do_given (bitfld, insn, bf_is_arg_num)
    
    if (bf_val_type == "range"):
        bitlst = do_range (bitfld, insn, bf_is_arg_num)
    
    if (bf_val_type == "lookup"):
        bitlst = do_lookup (bitfld, insn, bf_is_arg_num)
    
    # print ("=== ... ... ... {m:20s}: {l}".format(m="Bit Field Expanded to", l=bitlst))
    # print ("=== ... ... ... {m:20s}: {l}".format(m="DONE Expanding Bit Field", l=bitfld))
    
    return bitlst

def expand_insn (insn):
    print ("=== ... ... Expanding insn: ")
    # pp.pprint (insn)
    # print (insn)
    print ("            {m:20s}: {n}".format (m="INSN name", n=insn[insn_name_at]))

    num_args    = insn [insn_asm_num_args_at]
    arg_1_str   = insn [insn_asm_arg_1_at]
    arg_2_str   = insn [insn_asm_arg_2_at]
    arg_3_str   = insn [insn_asm_arg_3_at]
    arg_4_str   = insn [insn_asm_arg_4_at]

    out_insn = [insn[insn_name_at],            # Name of the source database entry of this expansion
                "",                            # 32 bit string to fill; using "x" to ease debugging
                0xFFFFFFFF,                    # 32 bit integer code of the bit representation; the machine code
                insn [insn_asm_mnemonic_at],   # Concatenate the arguments to this string
                insn [insn_op_desc_at],        # The comment string to enhance!
                False]                         # Bit expansion not yet complete!

    # print ("            {m:20s}: {n}".format (m="num args", n=num_args))
    # print ("            {m:20s}: {n}".format (m="arg_1_str", n=arg_1_str if (arg_1_str != []) else "NULL"))
    # print ("            {m:20s}: {n}".format (m="arg_2_str", n=arg_2_str if (arg_2_str != []) else "NULL"))
    # print ("            {m:20s}: {n}".format (m="arg_3_str", n=arg_3_str if (arg_3_str != []) else "NULL"))
    # print ("            {m:20s}: {n}".format (m="arg_4_str", n=arg_4_str if (arg_4_str != []) else "NULL"))
    
    lst_out_insns = []
    expanded_outlst = []
    out_insn_str = out_insn [insn_32_bit_string_at]
    print ("            {m:20s}: {l}".format (m="Starting Out INSN", l=out_insn))
    print ("            {m:20s}: {l}".format (m="Using format", l=insn [insn_fmt_index_at][0][0]))
            
    fmt_iterator = iter (insn [insn_fmt_index_at])

    for fmt in fmt_iterator:
        print ("            {m:20s}: {n}".format (m="FMT name", n=fmt [fmt_name_at]))
        # print ("            {m:20s}: {l}".format (m="OLD FMT", l=fmt))

        bit_fields_iterator = iter (fmt [fmt_bit_field_list_at])
        
        total_bits = 0
        theOpcode  = 0xFFFFFFFF # Set the fields with bitwise ANDs
        tmpintval  = 0
        num_bitflds = fmt [fmt_num_bit_fields_at]
        len_bitflds = len(fmt [fmt_bit_field_list_at])
        for bitfld in bit_fields_iterator:
            thlst = expand_bit_field (bitfld, insn)
            print ("               {m:20s}: {l}".format (m="Appending bitfield", l=thlst))
            expanded_outlst.append (thlst)

        num_bitflds_processed = len (expanded_outlst)
        
        # # print ("         {m:20s}: {l}".format (m="Num bitfields",        l=num_bitflds))
        # # print ("         {m:20s}: {l}".format (m="Num bitlists",         l=len_bitflds))
        # # print ("         {m:20s}: {l}".format (m="Num Expanded bitlsts", l=num_bitflds_processed))
        # # print ("         {m:20s}:".format (m="Expanded bitlists"))
        # pp.pprint (expanded_outlst)
        
        # # print ("            {m:20s}: {l}".format (m="Output INSN", l=out_insn))
        
    insn [insn_fmt_index_at] = expanded_outlst
    # print ("=== ... ... ... {m:20s}:".format(m="Expanded insn"))
    # pp.pprint (insn[insn_fmt_index_at])
    do_final_expansion (insn)
    # print ("=== ... ... {m:20s}:".format(m="DONE Expanding insn"))
    # print (insn)
    # # print ("INSN:", end="")
    # pp.pprint (insn)

    return insn

def get_opcode (l):
    x = 0
    for i in l:
        x = x | i[0]

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
    
    return thecomment

def get_argnum_str (r, arg):
    thestr = ""
    for l in r:
        if (l[1] == arg):
            thestr = l[2]
            break

    return thestr
        
def get_argnum_val (r, arg):
    theval = -1
    for l in r:
        if (l[1] == arg):
            theval = l[3]
            break

    return theval
        
def build_list_of_opcodes (insn, l, il, res, rec):
    reslst = []

    # newopc = [
    #     0x0,                         # Opcode integer
    #     insn [insn_asm_mnemonic_at], # Mnemonic
    #     "",                          # Arg 1
    #     "",                          # Arg 2
    #     "",                          # Arg 3
    #     "",                          # Arg 4
    #     cmtstr
    #     ]
    # # print ("OPC: {v}".format (v=newopc))

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

        # Format of output list: [opcode, mnemonic, arg1, arg2, arg3, arg4, cmtstr]
        fin_expans.append ([theopc, insn [insn_asm_mnemonic_at], arg1, arg2, arg3, arg4, cmtstr, arg1val, arg2val, arg3val, arg4val])
        return res
    else:
        fst = l[0]
        rst = l[1:]
        # print ("fst = {f}".format (f=fst))
        numfst = len (fst)
        for i in range (numfst):
            # theinfo = [
            #   0 bf[out_bitlst_is_arg_num_at],
            #   1 bf[out_bitlst_bf_name_at],
            #   2 bf[out_bitlst_bf_val_type_at],
            #   3 bf[out_bitlst_reg_val_lst_at],
            #   4 bf[out_bitlst_given_val_at]
            # ]
            # out_bitlst_is_arg_num_at      = 0
            # out_bitlst_bf_name_at         = 1
            # out_bitlst_bf_val_type_at     = 2
            # out_bitlst_out_opc_lst_at     = 3
            # out_bitlst_reg_val_lst_at     = 4
            # out_bitlst_given_val_at       = 5

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
                # print ("xxx InfoLst[{r}][3]: {v}".format(r=rec, v=il[rec][3]))
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
            # print ("xxx InfoLst[{r}][3]: {v}".format(r=rec, v=il[rec][3]))
            reslst.append (thisreslst)
            build_list_of_opcodes (insn, rst, il, reslst, (rec + 1))
            
# The final expander: This is where we need iterative list flattening.
def do_final_expansion (insn):
    # new_insn = insn
    # bit_fields = insn [insn_info_end_at]
    bit_fields = insn [insn_fmt_index_at]
    num_bit_fields = len (bit_fields)

    # print ("=== ... {m:20s}: {i}".format(m="    Final INSN Expansion", i=insn))
    # # print ("=== ... {m:20s}:".format(m="Final INSN Expansion"))
    # pp.pprint (insn)
    # print ("=== ... {m:20s}: {i}".format(m="    ... Bit Fields at", i=out_bitlst_out_opc_lst_at))

    # Extract the expanded bit lists into a list of lists.
    oclst = []
    infolst = []

    for bf in bit_fields:
        # theinfo = [
        #     bf[out_bitlst_is_arg_num_at],
        #     bf[out_bitlst_bf_name_at],
        #     bf[out_bitlst_bf_val_type_at],
        #     bf[out_bitlst_out_opc_lst_at],
        #     bf[out_bitlst_given_val_at]
        #     ]
        theinfo = bf
        print ("=== ... ... ... {m:20s}: {d}".format(m="Bit field for Adding", d=bf))
        print ("=== ... ... ... {m:20s}: {d}".format(m="Adding info element", d=theinfo))
        infolst.append (theinfo)
        oclst.append (bf[out_bitlst_out_opc_lst_at])

    # print ("=== ... ... {m:20s}: {d}".format(m="#OC Lists:", d=len(oclst)))
    # print ("=== ... ... {m:20s}: {d}".format(m="#Info Lists:", d=len(infolst)))
    # print ("=== ... ... {m:20s}:".format(m="OC Lists:"))
    # pp.pprint (oclst)
    # print (oclst)
    # print ("=== ... ... {m:20s}:".format(m="Info Lists:"))
    # pp.pprint (infolst)
    # print (infolst)
    build_list_of_opcodes (insn, oclst, infolst, [], 0)

    # # print ("=== ... {m:20s}: {i}".format(m="DONE Final INSN Expansion", i=new_insn))
    # print ("=== ... {m:20s}:".format(m="DONE Final INSN Expansion"))
    # pp.p# print (insn)

    return insn

def final_expanded_insns (fe):
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

    return expanded_insns

# This is the expander!

# We implement the format based approach found from page 44 onwards in
# the SPARC V8 manual.   This is pretty much the same  idea as the GNU
# Binutils  implementation  to  support  the  SPARC.   However  the  C
# implementation and this Python3 implementation look very different!

def expand_all_insns (il):
    # print ("=== ... Expander started")
    insn_iterator = iter (il)
    out_insns_lst = []
    for insn in insn_iterator:
        if (insn [insn_name_at] != "Opcode"): # SKIP the headers list
            out_insns_lst = expand_insn (insn)
    
    # print ("=== ... DONE Expander")
    return out_insns_lst

def neat_print (l):
    numperline = 5
    numentries = len (l)
    numlines   = numentries // numperline
    remainent  = numentries % numperline
    
    for i in range (numlines):
        for j in range (numperline):
            enttoprn = (i * numperline) + j
            # print ("0x{v:08X}".format (v=l[enttoprn]), end='')
            # print ("{s}".format(s="   " if (j != (numperline - 1)) else "\n"), end='')

def print_results (ei):
    for i in ei:
        print (i)
            
# "Main" program.  We are now using the __main__
def main ():
    setup_globals()
    system_setup()

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
    # # print ("=== INSN list after expanding ...")
    # pp.pprint (new_il)

    ## fin_expans is set inside the function build_list_of_opcodes
    # print ("=== Opcode expansions list ...")
    # # pp.pprint (fin_expans)
    # neat_print (fin_expans)
    # pp.pprint (fin_expans)
    print ("=== #Opcode expansions list : {v}".format (v=len(fin_expans)))

    xx = final_expanded_insns (fin_expans)
    # print ("=== Final Opcode expansions list ...")
    # pp.pprint (xx)
    # # print (xx)
    # # print ("=== #Final opcode expansions list : {v}".format (v=len(xx)))
    # # All done.
    # print ("Done.")

    print_results (expanded_insns)

if __name__ == "__main__":
    main()
