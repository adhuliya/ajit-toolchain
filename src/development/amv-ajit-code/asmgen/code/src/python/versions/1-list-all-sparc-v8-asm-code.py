#!/usr/bin/env python3

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

    global final_expansions         # The Master list of all expansions.
    global insn_iterator
    global fmt_iterator
    global bit_fields_iterator

    global list_length_max
    global max_list_length_bits

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
    insnlistcsv = asmgendata + '/' + 'sie.csv'        ### 'sparc-insn-expand.csv'

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

    final_expansions = []
    
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

    MAX_SPARC_REGS = 32
    
#####
# I/O functions section
#####

# Read in data files
def read_data_file(df):
    print("Reading data file {f:82s} ...".format(f=df), end='')
    rv = []
    with open(df, 'r') as f1:
        raw_data = csv.reader(f1, delimiter=',')
        rv = list(raw_data)
    f1.closed
    print("Done.")
    return rv

# Print a list
def print_list(l):
    pp (l)
        
def write_csv_file(in_data, out_file_name, msg):
    out_file = open(out_file_name, 'w')
    with out_file as o:
        owrite = csv.writer(out_file, delimiter='|', quotechar="'")
        for row in range(len(in_data)):
            row_data = in_data[row]
            owrite.writerow(row_data)
    o.closed

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

def indentit (rec):
    for i in range (rec):
        print (indentstr, end="")
    print (" ", end="")
    
#####
# Processing functions section
#####

# Convert a string representation of a binary number to its value.
def convert_bin_to_val (binstr):
    num_digits = len(binstr)
    max_pow = num_digits - 1
    val = 0
    pow_to_use = 1
    for i in range (num_digits):
        pow_to_use = max_pow - i
        if (binstr[i] == "1"):
            to_mult = 2**(max_pow - i)
            val = val + to_mult

    return val

def make_subfield_pattern_str (name, length, value):
    if (type (value) == type (1)):
        usestr = str (value)
    elif (type (value) == type ("abc")):
        if (value != ""):
            usestr = str (int (value, 16))
        else:
            usestr = name
        
    patstr = usestr.center(length,'-')
        
    return patstr

def lookup_value_of_name (insn, name):
    val = -1
    if (insn[1] == name):
        val = insn[2]

    return val

def make_subfield_pattern_val (insn, name, start, length, value, valsrc):
    patval = []
        
    if (valsrc == "given"):
        patval.append (value)
    elif (valsrc == "generate"):
        patval.append (value)
    elif (valsrc == "lookup"):
        val = lookup_value_of_name (insn, name)
        print ("Value source \"{v:s}\" for field name {s:s} returns {ans:d}.".
               format(v=valsrc, s=name, ans=val))
        patval.append (val)
    elif (valsrc == "parameter"):
        patval.append (value)
    else:
        print ("Unknown value source \"{v:s}\" for field name {s:s}.".
               format(v=valsrc, s=name))

    return patval
        
def get_mask_of_length (masklen):
    val = 0
    i = 0
    while (i < masklen):
        set_bit = 0x1 << i
        val = val | set_bit
        i = i + 1
        
    return val

def make_val (bin_str):
    strlen = len (bin_str)
    result = 0

    for i in range (0, strlen):
        bit_val = 1 if (bin_str[i] == '1') else 0
        result = result + bit_val * (2 ** (strlen - i - 1))
    
    return result

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
    
def bit_field_val_str_to_pat_str (insn, fmt, fld):
    bitstr   = ""
    usestr   = ""
    valtype  = fld [bit_field_val_type_at]
    valstr   = fld [bit_field_val_str_at]
    num_bits = fld [bit_field_length_at]
    name     = fld [bit_field_name_at]
    
    if (valtype == "given"):
        usestr = "{v:b}".format (v=int (valstr, 16))
    elif (valtype == "generate"):
        usestr = "{v:s}".format (v=fld [bit_field_name_at])
    elif (valtype == "lookup"):
        usestr = insn [insn_value_to_set_at] if (insn[insn_field_to_set_at] == name) else ""
    elif (valtype == "parameter"):
        usestr = "{v:s}".format (v=fld [bit_field_name_at])
    else:                       # ERROR: Return a string of N.
        usestr = "N"
        print ("Unknown value source \"{v:s}\" for field name {s:s}.".
               format(v=valtype, s=name))
    bitstr = usestr.center(num_bits, usestr) if (usestr == "N") else usestr.center(num_bits,'-')
        
    return bitstr

def bit_field_val_str_to_val_lst (insn, fmt, fld):
    bitlst   = []
    uselst   = []
    valtype  = fld [bit_field_val_type_at]
    valstr   = fld [bit_field_val_str_at]
    num_bits = fld [bit_field_length_at]
    
    if (valtype == "given"):
        bitlst.append (int (valstr, 16))
    elif ((valtype == "generate") or
          (valtype == "parameter")):
        valmax= fld[bit_field_mask_at]
        bitlst = list (range (valmax+1)) if (valmax < list_length_max) else []
    elif (valtype == "lookup"):
        name   = fld [bit_field_name_at]
        bitlst = int (insn [insn_value_to_set_at], 2)
    else:                       # ERROR: Return a string of N.
        uselst = "N"
        bitlst = uselst.center(num_bits, uselst)
        print ("Unknown value source \"{v:s}\" for field name {s:s}.".
               format(v=valtype, s=name))
        
    return bitlst

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
    useval = (useval << bf_end)

    out_opc_lst = [useval]
    out_lst = [is_arg_num, bf_name, bf_val_type, out_opc_lst, reg_val_lst]
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
    useval = bf_mask | (useval << bf_end)

    print ("=== ... ... ... ... {m:20s}: {l}".format(m="DONE Doing LOOKUP", l=out_lst))
    out_opc_lst.append (useval)

    out_lst = [is_arg_num, bf_name, bf_val_type, out_opc_lst, reg_val_lst]
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

    out_lst = [is_arg_num, bf_name, bf_val_type, out_opc_lst, reg_val_lst]
    print ("=== ... ... ... ... {m:20s}: {l}".format(m="DONE Doing GENERATE", l=out_lst))

    return out_lst

def do_range (bitfld, insn, is_arg_num):
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

    min = 0
    max = pow (2, bf_nbits) # Careful: This could be a very large number, e.g. > 24 bits!
    
    useval = min
    useval = bf_mask | (useval << bf_end)
    
    out_opc_lst.append (useval)
    
    useval = max
    useval = bf_mask | (useval << bf_end)
    
    out_opc_lst.append (useval)
    
    out_lst = [is_arg_num, bf_name, bf_val_type, out_opc_lst, reg_val_lst]
    print ("=== ... ... ... ... {m:20s}: {l}".format(m="DONE Doing GENERATE", l=out_lst))

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
    
    print ("=== ... ... ... {m:20s}: {l}".format(m="DONE Expanding Bit Field", l=bitfld))
    
    return bitlst

def expand_insn (insn):
    print ("=== ... ... Expanding insn: ")
    ## pp.pprint (insn)
    print (insn)
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
            expanded_outlst.append (expand_bit_field (bitfld, insn))

        num_bitflds_processed = len (expanded_outlst)
        
        # print ("         {m:20s}: {l}".format (m="Num bitfields",        l=num_bitflds))
        # print ("         {m:20s}: {l}".format (m="Num bitlists",         l=len_bitflds))
        # print ("         {m:20s}: {l}".format (m="Num Expanded bitlsts", l=num_bitflds_processed))
        # print ("         {m:20s}:".format (m="Expanded bitlists"))
        # pp.pprint (expanded_outlst)
        
        # print ("            {m:20s}: {l}".format (m="Output INSN", l=out_insn))
        
    insn [insn_fmt_index_at] = expanded_outlst
    insn = do_final_expansion (insn)
    print ("=== ... ... {m:20s}:".format(m="DONE Expanding insn"))
    # pp.pprint (insn)
    print (insn)

    return insn

def get_opcode_and_rest (l):
    x = 0
    for i in l:
        x = x | i

    return x

def build_list_of_opcodes (l, res, rec):
    reslst = []
    x = len (l)
    if (x == 0):
        # print ("List is: {l}".format (l=res))
        theopc = get_opcode_and_rest (res)
        final_expansions.append (theopc)
        return res
    else:
        fst = l[0]
        rst = l[1:]
        numfst = len (fst)
        for i in range (numfst):
            reslst = res.copy()
            reslst.append (fst[i])
            build_list_of_opcodes (rst, reslst, (rec + 1))
            
# The final expander: This is where we need iterative list flattening.
def do_final_expansion (insn):
    new_insn = insn
    # bit_fields = insn [insn_info_end_at]
    bit_fields = insn [insn_fmt_index_at]
    num_bit_fields = len (bit_fields)
    num_asm_args = insn [insn_asm_num_args_at]

    newopc = [
        0x0,                         # Opcode integer
        insn [insn_asm_mnemonic_at], # Mnemonic
        "",                          # Arg 1
        "",                          # Arg 2
        "",                          # Arg 3
        "",                          # Arg 4
        "# " +                       # Comment
        insn [insn_name_at] +
        ", " +
        insn [insn_op_desc_at]
        ]
    
    print ("=== ... {m:20s}: {i}".format(m="    Final INSN Expansion", i=insn))
    # print ("=== ... {m:20s}:".format(m="Final INSN Expansion"))
    # pp.pprint (insn)
    print ("=== ... {m:20s}: {i}".format(m="    ... Bit Fields at", i=out_bitlst_out_opc_lst_at))

    # Extract the expanded bit lists into a list of lists.
    oclst = []
    for bf in bit_fields:
        oclst.append (bf[out_bitlst_out_opc_lst_at])
        # oclst.extend (bf[out_bitlst_out_opc_lst_at])

    print ("=== ... ... {m:20s}: {d}".format(m="#OC Lists:", d=len(oclst)))
    print ("=== ... ... {m:20s}:".format(m="OC Lists:"))
    # pp.pprint (oclst)
    print (oclst)
    build_list_of_opcodes (oclst, [], 0)

    # print ("=== ... {m:20s}: {i}".format(m="DONE Final INSN Expansion", i=new_insn))
    print ("=== ... {m:20s}:".format(m="DONE Final INSN Expansion"))
    # pp.pprint (insn)

    return new_insn

# This is the expander!

# We implement the format based approach found from page 44 onwards in
# the SPARC V8 manual.   This is pretty much the same  idea as the GNU
# Binutils  implementation  to  support  the  SPARC.   However  the  C
# implementation and this Python3 implementation look very different!

def expand_all_insns (il):
    print ("=== ... Expander started")
    insn_iterator = iter (il)
    out_insns_lst = []
    for insn in insn_iterator:
        if (insn [insn_name_at] != "Opcode"): # SKIP the headers list
            out_insns_lst = expand_insn (insn)
    
    print ("=== ... DONE Expander")
    return out_insns_lst

def get_patterns_list (insns):
    patlist = []
    insn_iterator = iter (insns)
    for insn in insn_iterator:
        if (insn [insn_name_at] != "Opcode"): # SKIP the headers list
            # print (".. {m:<15s}: {n}".format (m="INSN name", n=insn[insn_name_at]))
            name = insn [insn_name_at]
            fmt_iterator = iter (insn [insn_fmt_index_at])

            for fmt in fmt_iterator:
                # print (".... {m:<15s}: {n}".format (m="FMT name", n=fmt [fmt_name_at]))
                p=fmt[fmt_opcode_pat_str_at]
                t = (name, p)
                patlist.append (t)
                
    return patlist

def display_patterns (pl):
    line_count = 0
    pli = iter (pl)
    print ("{n:<10s} : {s}".format (n="NAME", s="PATTERN"))
    for insn in pli:
        if (line_count % 16 == 0):
            print ("{n:<10s}   {s}".format (n="", s="31 28  24  20  16  12  8   4   0"))
            print ("{n:<10s}   {s}".format (n="", s="|--|---|---|---|---|---|---|---|"))
        print ("{n:<10s} : {s}".format (n=insn[0], s=insn[1]))
        line_count = line_count + 1
        
    return

def neat_print (l):
    numperline = 5
    numentries = len (l)
    numlines   = numentries // numperline
    remainent  = numentries % numperline
    
    for i in range (numlines):
        for j in range (numperline):
            enttoprn = (i * numperline) + j
            print ("0x{v:08X}".format (v=l[enttoprn]), end='')
            print ("{s}".format(s="   " if (j != (numperline - 1)) else "\n"), end='')

# "Main" program.  We are not using the __main__
setup_globals()
system_setup()

# Read in the  data.
fmtlst  = read_data_file (insnformatscsv)
insnlst = read_data_file (insnlistcsv)
print ("=== INSNs list ...")
## pp.pprint (insnlst)
print (insnlst)

fl = make_lists_of_flat_bit_fields_in_formats (fmtlst)
## pp.pprint (fmtlst)
## print ("=== Format list after reorganising flat bit fields into lists ...")
## pp.pprint (fl)
## pp.pprint (insnlst)

il = replace_format_specs_by_lists (insnlst, fl)
## print ("=== INSN list after including format list ...")
## pp.pprint (il)

new_il = expand_all_insns (il)
# print ("=== INSN list after expanding ...")
# pp.pprint (new_il)

print ("=== Final opcode expansions list ...")
# pp.pprint (final_expansions)
# neat_print (final_expansions)
print (final_expansions)
print ("=== #Final opcode expansions list : {v}".format (v=len(final_expansions)))

# All done.
print ("Done.")
