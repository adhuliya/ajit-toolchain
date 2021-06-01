#!/usr/bin/env python3

import csv
import csv
import os
import pprint as pp                  # pretty printer

#####
# Information section
#####

def setup_globals():
    # Declare the globals
    # global ajitcsvprefix
    # global asmgenccode, asmgenpycode, asmgenschemecode, asmgentop, asmgencode, asmgendata
    global top, curr_dir, tmpdir, indentstr
    global ajitformatscsv, ajitlistcsv
    global fmtlst, insnlst

    global insn_name_at         
    global insn_field_to_set_at 
    global insn_value_to_set_at 
    global insn_op_desc_at      
    global insn_category_at     
    global insn_fmt_index_at    
    global insn_proc_stat_at    
    global insn_privilege_at
    
    global fmt_name_at           
    global fmt_index_at          
    global fmt_num_bit_fields_at 
    global fmt_insn_format_at
    global fmt_opcode_pat_str_at 
    global fmt_opcode_bit_str_at 
    global fmt_opcode_int_val_at 
    global fmt_bit_field_list_at
    global fmt_processing_state
    
    global bit_field_name_at     
    global bit_field_start_at    
    global bit_field_end_at      
    global bit_field_length_at   
    global bit_field_val_str_at  
    global bit_field_val_type_at
    global bit_field_mask_at
    global bit_field_pattern_str_at
    global bit_field_processing_state_at
    global bit_field_val_lst_at  

    global insn_iterator
    global fmt_iterator
    global bit_fields_iterator

    global list_length_max

    # Directory structure
    top = '/lindata/My-work/Professional/iitb/development'
    asmgentop = top + '/asmgen'
    asmgencode = asmgentop + '/code'
    asmgendata = asmgentop + '/data'
    asmgenccode = asmgencode + '/c'
    asmgenpycode = asmgencode + '/python'
    asmgenschemecode = asmgencode + '/scheme'
    
    ajitcsvprefix = asmgendata + '/' + 'ajit-insn-set-layout'

    indentstr="..."

    tmpdir = '/tmp'               # Temporary work area. Check for existence

    ### Input file names
    ajitformatscsv = ajitcsvprefix + '-formats.csv'
    ajitlistcsv = ajitcsvprefix + '-insns.csv'

    # Lists
    fmtlst  = []
    insnlst = []

    # Some global constants
    # List offsets: INSN list
    insn_name_at         = 0
    insn_field_to_set_at = 1
    insn_value_to_set_at = 2
    insn_op_desc_at      = 3
    insn_category_at     = 4
    insn_fmt_index_at    = 5
    insn_proc_stat_at    = 6
    insn_privilege_at    = 7

    # List offsets: FORMATS list
    fmt_name_at           = 0
    fmt_index_at          = 0            # alias for format name
    fmt_num_bit_fields_at = 1
    fmt_insn_format_at    = 2
    fmt_opcode_pat_str_at = 3
    fmt_opcode_bit_str_at = 4
    fmt_opcode_int_val_at = 5
    fmt_bit_field_list_at = 6
    fmt_processing_state  = 7

    # List offsets: BIT FIELDS list
    bit_field_name_at             = 0
    bit_field_start_at            = 1
    bit_field_end_at              = 2
    bit_field_length_at           = 3
    bit_field_val_str_at          = 4
    bit_field_val_type_at         = 5
    bit_field_mask_at             = 6
    bit_field_pattern_str_at      = 7
    bit_field_processing_state_at = 8
    bit_field_val_lst_at          = 9

    # Maximum length of generated lists. Larger lists are put in as empty lists.
    list_length_max = 8

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

def write_csv_file(in_data, out_file_name, msg):
    print("Writing {m:s} \n   to CSV file {f:72s} ...".format(m=msg, f=out_file_name), end='')
    out_file = open(out_file_name, 'w')
    with out_file as o:
        owrite = csv.writer(out_file, delimiter='|', quotechar="'")
        for row in range(len(in_data)):
            row_data = in_data[row]
            owrite.writerow(row_data)
    o.closed
    print("Done.")

#####
# System and setup functions section
#####

def check_and_create_if_necessary(the_dir):
    if not os.path.exists(the_dir):
        os.mkdir(the_dir, mode=0o777)
    return os.path.exists(the_dir)

def system_setup():

    curr_dir = os.getcwd()        # Current directory
    print("{m:25s}: {d:s}\n".format(m="Original directory", d=curr_dir), end='')
    os.chdir(top)

    check_and_create_if_necessary(tmpdir)
    curr_dir = os.getcwd()
    print("{m:25s}: {d:s}\n".format(m="Current directory", d=curr_dir), end='')

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

    num_bit_fields = bit_field_val_type_at - bit_field_name_at + 1
    sl = fl[fmt_bit_field_list_at:]
    num_bit_fields_lists = (int) (len (sl) / num_bit_fields)
    
    bit_fields = []
    reformatted_list = []

    reformatted_list.append (fl[fmt_name_at])
    reformatted_list.append (fl[fmt_num_bit_fields_at])
    reformatted_list.append (fl[fmt_insn_format_at])
    reformatted_list.append (fl[fmt_opcode_pat_str_at])
    reformatted_list.append (fl[fmt_opcode_bit_str_at])
    reformatted_list.append (fl[fmt_opcode_int_val_at])

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

        bit_fields.append ([name, start, end, length, value, value_type, mask, pattern_str, processing_state, value_list])
        
        i = i + 1
    
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
        if (i != 0):
            il[i][insn_proc_stat_at] = 'insn-fmt-combined'
    
    return il
    
# --------------------------------------------------------------------
# Top   level  controller:
#
# Processes the _entire_ set of  instructions.  It returns a flat list
# of each individual instance  of expansion.  Each individual instance
# itself is  a list of:
#    (a) a single 32  bit integer opcode,
#    (b) the instruction mnemonic  string,
#    (c) a  list of arguments  in the  exact sequence expected  by the
#        syntax, and
#    (d) a  comment string  that describes the operation.
#
# Initially, we focus on (a) only. i.e. we generate only opcodes.
# --------------------------------------------------------------------
def generate_opcodes_and_asm (insn_list, reclevel):
    result = []

    for i in range (1, len (insn_list)):
        insn_to_expand = insn_list[i]
        print ("{m:<15s} :\n{v}".
               format (m="Expanding INSN ...", v=pp.pformat (insn_to_expand)))
        expanded_list = expand_insn (insn_to_expand)
        for j in range (len (expanded_list)):
            result.append (expanded_list[j])

    return result

# --------------------------------------------------------------------
# Focus on  target (a) of generate_opcodes_and_asm()  above.  However,
# we will collect the other information pieces as we come across them.
# We will  also define the  structure of  the result of  expanding one
# insn.
#
# One single expansion is
#    0 - Opcode                                 - Integer
#    1 - Mnemonic                               - String
#    2 - List of arguments in "standard" syntax - String
#    4 - Comment for ASM code                   - String
#
# An instruction pattern may be expanded  into _a list of_ one or more
# such single expansions.
#
# We return such a list of single expansions.
# --------------------------------------------------------------------
def expand_insn (insn):
    result = []

    mnemonic  = insn[0]
    comment   = insn[3]
    fmts_list = insn[5]
    bit_flds_index = 3          # This element in a given formats list
                                # tells us the bit fields layout.

    num_fmts  = len (fmts_list)
    for i in range (num_fmts):
        curr_fmt_list = fmts_list [i]
        # ans = expand_fmt_list (insn, curr_fmt_list, bit_flds_index)
        ans = expand_fmt_list (mnemonic, comment, curr_fmt_list, bit_flds_index)
        result = result + ans

    return result

def expand_fmt_list (m, c, fmtlst, idx):
    result = []
    theflds = fmtlst[idx]
    numflds = len (theflds)
    numfldsspec = int (fmtlst[1])
    ppfmtlst = pp.pformat (fmtlst, indent=1)
    pptheflds = pp.pformat (theflds, indent=1)

    print ("EFL: ", end="")
    print ("{m:<15s} : {v}".format (m="List Index",       v=idx),     end="\n     ")
    print ("{m:<15s} : {v}".format (m="Mnemonic",         v=m),       end="\n     ")
    print ("{m:<15s} : {v}".format (m="Comment",          v=c),       end="\n     ")
    #print ("{m:<15s} : {v}".format (m="Formats List",     v=fmtlst),  end="\n     ")
    print ("{m:<15s} :\n {v}".format (m="Formats List",  v=ppfmtlst),  end="\n     ")
    #print ("{m:<15s} : {v}".format (m="Bit fields List",  v=theflds), end="\n     ")
    print ("{m:<15s} : {v}".format (m="#Bit fields List", v=numflds), end="\n     ")
    print ("{m:<15s} :\n {v}".format (m="Bit fields List",  v=pptheflds), end="")
    print ("\n")

    if (numflds == numfldsspec): # Consistency of specification and information within.
        total_bits  = 0
        name_at     = 0
        start_at    = 1
        end_at      = 2
        length_at   = 3
        val_list_at = 4
        val_type_at = 5
        
        for i in range (numflds):
            curr_fld    = theflds [i]
            num_bits    = curr_fld [length_at]
            total_bits  = total_bits + num_bits

        if (total_bits == 32):
            print ("HURRAY: Total number of bits is {n1:d} is 32!".
                   format (n1=total_bits))

            bitpat = expand_bit_fields_to_opcodes_list (m, c, theflds, 1)

            print ("XXX Mnemonic {m:<5s} expanded to: {v}".
                   format (m=m, v=bitpat))
            
            # for i in range (numflds):
            #     curr_fld    = theflds [i]
                
            #     name        = curr_fld [name_at]
            #     start       = curr_fld [start_at]
            #     end         = curr_fld [end_at]
            #     num_bits    = curr_fld [length_at]
            #     vallst      = curr_fld [val_list_at]
            #     valtype     = curr_fld [val_type_at]
                
            #     print ("xxx {m:<15s} : {v}".format (m="#Expanding fields List", v=curr_fld), end="\n")
        else:
            print ("ERROR ERROR: Total number of bits is {n1:d} and not 32!".
                   format (n1=total_bits))
    else:
        print ("ERROR ERROR: numflds {n1:d} != numfldsspec {n1:d}".
               format (n1=numflds, n2=numfldsspec))
            

    return result

def indentit (rec):
    for i in range (rec):
        print (indentstr, end="")
    print (" ", end="")
    
def expand_bit_fields_to_opcodes_list (m, c, flds, rec):
    code = []

    indentit (rec)
    ppflds = pp.pformat (flds)
        
    if (flds == []):
        print ("{m:<15s} : {v} (END OF LIST)".format (m="Expanding fields List", v=ppflds), end="\n")
        return flds
    else:
        print ("{m:<15s} :\n {v}".format (m="Expanding fields List", v=ppflds), end="\n")
    
        name_at     = 0
        start_at    = 1
        end_at      = 2
        length_at   = 3
        val_list_at = 4
        val_type_at = 5

        curr = flds[0]
        rest = flds[1:]

        ppcurr = pp.pformat (curr)
        pprest = pp.pformat (rest)
        
        indentit (rec)
        print ("{m:<15s} : {v}".format (m="Current field", v=ppcurr), end="\n")
        # indentit (rec)
        # print ("{m:<15s} :\n {v}".format (m="Other fields", v=pprest), end="\n")
        
        name        = curr [name_at]
        start       = curr [start_at]
        end         = curr [end_at]
        num_bits    = curr [length_at]
        vallst      = curr [val_list_at]
        valtype     = curr [val_type_at]

        indentit (rec)
        print ("{m:<15s} : {v}".format (m="Curr field name", v=name), end="\n")
        indentit (rec)
        print ("{m:<15s} : {v}".format (m="Values list is", v=vallst), end="\n")
        indentit (rec)
        print ("{m:<15s} : {v}".format (m="#Values are", v=len(vallst)), end="\n")
        indentit (rec)
        print ("{m:<15s} : {v}".format (m="Currfield width", v=num_bits), end="\n")

        if (len (vallst) == 0):
            outval     = ["AMV0"] + expand_bit_fields_to_opcodes_list (m, c, rest, (rec + 1))
            code       = code + outval
            indentit (rec)
            print ("{m:<15s} : {v}".format (m="Output value", v=outval), end="\n")
            indentit (rec)
            print ("{m:<15s} : {v}".format (m="Returning ... ", v=code), end="\n")
            print ("XXX")
        else:
            for i in range (len (vallst)):
                indentit (rec)
                print ("{m:<15s} : {v}".format (m="Curr field name", v=name), end="\n")
                currval    = int (vallst[i])
                currvalstr = "{v:0{width}b}".format(v=vallst[i], width=num_bits)
                placedval  = currval << start
                
                indentit (rec)
                print ("{m:<15s} : {v}".format (m="#Current value", v=i), end="\n")
                indentit (rec)
                print ("{m:<15s} : {v}".format (m="Current value", v=currval), end="\n")
                indentit (rec)
                print ("{m:<15s} : {v}".format (m="BinStr Currval", v=currvalstr), end="\n")
                indentit (rec)
                print ("{m:<15s} : {v}".format (m="To be placed at", v=start), end="\n")
                indentit (rec)
                print ("{m:<15s} : {v:0{width}b}".format (m="Shifted and is", v=placedval, width=num_bits), end="\n")

                outval     = [placedval] + expand_bit_fields_to_opcodes_list (m, c, rest, (rec + 1))
                # code.append (outval)
                code       = code + outval

                indentit (rec)
                print ("{m:<15s} : {v}".format (m="Output value", v=outval), end="\n")
                indentit (rec)
                print ("{m:<15s} : {v}".format (m="Returning ... ", v=code), end="\n")
                print ("XXX")
            
        print (code)
    
    return code
    
# --------------------------------------------------------------------
# Python does not have tail  recursion (as yet!).  The following naive
# recursion is very  likely to crash the interpreter as  it may exceed
# the recursion limits.
# --------------------------------------------------------------------
# 
# def generate_opcodes_and_asm (insn_list, reclevel):
#     result = []
# 
#     if (insn_list == []):
#         print ("DONE.")
#     else:
#         car = insn_list[0]
#         cdr = insn_list[1:]
#         print ("Rec: {r:0>2d}\n   Current: {l}\n   Rest: {l1}".
#                format (r=reclevel, l=car, l1=cdr))
#         generate_opcodes_and_asm (cdr, (reclevel + 1))
# 
#     return result

def bit_field_val_str_to_pat_str (insn, fmt, fld):
    # print ("...... {m:<15s}: {v} ".format (m="FLD is", v=fld))
    bitstr   = ""
    usestr   = ""
    valtype  = fld [bit_field_val_type_at]
    valstr   = fld [bit_field_val_str_at]
    num_bits = fld [bit_field_length_at]
    name     = fld [bit_field_name_at]
    
    if (valtype == "given"):
        # usestr = "{v:{width}b}".format (v=int (valstr, 16), width=num_bits)
        # print ("...... {m:<15s}: {v} ".format (m="VALSTR is", v=valstr))
        usestr = "{v:b}".format (v=int (valstr, 16))
        bitstr = usestr.center(num_bits,'-')
    elif (valtype == "generate"):
        usestr = "{v:s}".format (v=fld [bit_field_name_at])
        bitstr = usestr.center(num_bits,'-')
    elif (valtype == "lookup"):
        usestr = insn [insn_value_to_set_at] if (insn[insn_field_to_set_at] == name) else ""
        print ("XXX... {m:<15s}: {v} ".format (m="INSN   is", v=insn[insn_name_at]))
        print ("XXX... {m:<15s}: {v} ".format (m="INSNFLDis", v=insn[insn_field_to_set_at]))
        print ("XXX... {m:<15s}: {v} ".format (m="NAME   is", v=name))
        print ("XXX... {m:<15s}: {v} ".format (m="LOOKUP is", v=usestr))
        bitstr = usestr.center(num_bits,'-')
    elif (valtype == "parameter"):
        usestr = "{v:s}".format (v=fld [bit_field_name_at])
        bitstr = usestr.center(num_bits,'-')
    else:                       # ERROR: Return a string of N.
        usestr = "N"
        bitstr = usestr.center(num_bits, usestr)
        print ("Unknown value source \"{v:s}\" for field name {s:s}.".
               format(v=valtype, s=name))
        
    return bitstr

def bit_field_val_str_to_val_lst (insn, fmt, fld): # AMV
    # print ("...... {m:<15s}: {v} ".format (m="VALLST FLD is", v=fld))
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
        #bitlst = int (insn [insn_value_to_set_at], 2) if (insn[insn_field_to_set_at] == name) else 0
        bitlst = int (insn [insn_value_to_set_at], 2)
    else:                       # ERROR: Return a string of N.
        uselst = "N"
        bitlst = uselst.center(num_bits, uselst)
        print ("Unknown value source \"{v:s}\" for field name {s:s}.".
               format(v=valtype, s=name))
        
    return bitlst

def process_insns (il):
    insn_iterator = iter (il)
    new_insns_lst = []
    for insn in insn_iterator:
        if (insn [insn_name_at] != "Opcode"): # SKIP the headers list
            print (".. {m:<15s}: {n}".format (m="INSN name", n=insn[insn_name_at]))
            new_insn = [insn[insn_name_at],
                        insn[insn_field_to_set_at],
                        insn[insn_value_to_set_at],
                        insn[insn_op_desc_at],
                        insn[insn_category_at],
                        [],     # Format index will be replaced by updated format lists
                        insn[insn_proc_stat_at],
                        insn[insn_privilege_at]]

            # print ("III: Old INSN {l}".format (l=insn))
            print ("III: New INSN {l}".format (l=new_insn))
                        
            fmt_iterator = iter (insn [insn_fmt_index_at])
            new_fmt_lst = []

            for fmt in fmt_iterator:
                print (".... {m:<15s}: {n}".format (m="FMT name", n=fmt [fmt_name_at]))

                new_fmt = [fmt[fmt_name_at],
                           fmt[fmt_num_bit_fields_at],
                           fmt[fmt_insn_format_at],
                           "",  # here will be the opcode pattern string
                           "",  # here will be the opcode bit     string
                           0,   # here will be the opcode integer value
                           fmt[fmt_bit_field_list_at],
                           fmt[fmt_processing_state]
                ]
                print ("FFF: OLD FMT {l}".format (l=fmt))
                print ("FFF: NEW FMT {l}".format (l=new_fmt))

                bit_fields_iterator = iter (fmt [fmt_bit_field_list_at])
                # fmt[fmt_opcode_pat_str_at] = ""
                # fmt[fmt_opcode_bit_str_at] = ""
                # fmt[fmt_opcode_int_val_at] = 0

                total_bits  = 0
                pat_str = ""
                for bitfld in bit_fields_iterator:
                    total_bits = total_bits + bitfld[bit_field_length_at]
                    
                    new_bit_field = [bitfld[bit_field_name_at],
                                     bitfld[bit_field_start_at],
                                     bitfld[bit_field_end_at],
                                     bitfld[bit_field_end_at],
                                     bitfld[bit_field_val_str_at],
                                     bitfld[bit_field_val_type_at],
                                     bitfld[bit_field_mask_at],
                                     "", # bit field pattern string
                                     "", # bit field processing state
                                     []] # bit field values list
                    
                    print ("BBB: NEW BIT {l}".format (l=new_bit_field))
                    print ("...... {m:<15s}: {l}".format (m="BITFLD Name", l=new_bit_field))

                    p = bit_field_val_str_to_pat_str (insn, fmt, bitfld)
                    new_bit_field [bit_field_pattern_str_at] = p
                    new_bit_field [bit_field_processing_state_at] = "pattern str done"
                    print ("...... {m:<15s}: {l}".format (m="BITFLD Name", l=new_bit_field))

                    l = bit_field_val_str_to_val_lst (insn, fmt, bitfld)
                    new_bit_field [bit_field_val_lst_at] = l
                    new_bit_field [bit_field_processing_state_at] = "values list done"
                    print ("...... {m:<15s}: {l}".format (m="BITFLD Name", l=new_bit_field))

                    # v = bit_field_val_str_to_int_val (bit_fld, bit_field_val_str_at)

                    pat_str = pat_str + p
                    # print ("...... {m:<15s}: {l}".format (m="BITFLD Name", l=bitfld))
                    
                    # new_bit_field = [bitfld[bit_field_name_at],
                    #                  bitfld[bit_field_start_at],
                    #                  bitfld[bit_field_end_at],
                    #                  bitfld[bit_field_end_at],
                    #                  bitfld[bit_field_val_str_at],
                    #                  bitfld[bit_field_val_type_at],
                    #                  bitfld[bit_field_mask_at],
                    #                  bitfld[bit_field_pattern_str_at],
                    #                  bitfld[bit_field_processing_state_at],
                    #                  bitfld[bit_field_val_lst_at]
                    # ]
                    
                print ("YYY {m:<15s}: {l} (Length: {v:d}/{v1:d}) (Insn: {n:s})".
                       format (m="FORMAT Pat str",
                               l=pat_str,
                               v=len(pat_str),
                               v1=total_bits,
                               n=insn[insn_name_at]))
                print ("FFF {m:<15s}: {l}".format (m="Final FORMAT",l=fmt))
                new_fmt[fmt_opcode_pat_str_at] = pat_str
                print ("FFF: Its FMT {l}".format (l=new_fmt))

                new_insn[insn_fmt_index_at].append (new_fmt)
            print ("III: New INSN {l}".format (l=new_insn))
            new_insns_lst.append (new_insn)
    
    return new_insns_lst

def get_patterns_list (insns):
    patlist = []
    insn_iterator = iter (insns)       # AMV
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

# "Main" program.  We are not using the __main__
setup_globals()
system_setup()

# Read in the  data.
fmtlst  = read_data_file (ajitformatscsv)
insnlst = read_data_file (ajitlistcsv)
print ("===")
print ("Original INSNs list is (Flat structure):")
pp.pprint (insnlst)
print ("===")
print ("Original formats list is (Flat structure):")
pp.pprint (fmtlst)
print ("===")

fl = make_lists_of_flat_bit_fields_in_formats (fmtlst)
print ("Made lists of flat bit fields in format specifications:")
pp.pprint (fl)
print ("===")
il = replace_format_specs_by_lists (insnlst, fl)
print ("Format specs in INSNs replaced by lists is:")
pp.pprint (il)
print ("===")
new_il = process_insns (il)
print ("INSN patterns generated:")
pp.pprint (new_il)
print ("===")
patlst = get_patterns_list (new_il)
print ("INSN patterns list:")
pp.pprint (patlst)
print ("===")

display_patterns (patlst)

# opcodes_list  = generate_opcodes_and_asm (final, 0) # TODO
# print ("OPCODES LIST:")
# print (opcodes_list)
# print ("===")
# # patterns_list = generate_insn_patterns (final)   # TODO

# write_csv_file (insnlst, tmp_1_file, "Temporary copy.")

# All done.
print ("Done.")
