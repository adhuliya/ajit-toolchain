#!/usr/bin/perl

# This script will analyse register-wirte traces.
# It compares reference (write-trace generated form C-model) and trace (which one 
# need to be checkked). It compares each register_write PC, reg_id, re_value, cwp.
# each line in reference and trace represents a register write. Script read one 
# line of reference and one line of trace then compare them, report erros if any, go 
# to next line. Generates a report at the same name as reference file (eg; add.report) 
#
# author: Ashfaque Ahammed

use strict;
use warnings;
use 5.010;
use Getopt::Long qw(GetOptions);
use Data::Dumper qw(Dumper);

# initializations
my $ref_line_count = 0;
my $trace_line_count = 0;
my $last_reference_fh = 0;      #used to seek file handler to last read position
my ($pc, $reg_id, $cwp, $double_flag, $reg_value_high, $reg_value_low);
my ($trace_double_flag) = 0;
my $current_pc = '';
my @PC_id_maping=();           # ({thread_id, $stream_id, $slot_id, PC}, )
my @grabbed;                    # temporary storage of grabbed lines
my $ref_last_exec_pc;           # where sub2 stop analyzing trace file
my $trace_last_exec_line;       # Last line analyzed on trace file
my $end_of_reference_file = 0;  # flag for finished reading reference file
my $end_of_trace_file = 0;      # flag for finished reading trace file
my @error = ();                 # Arrays to store errors, warnings and infos
my @warning = ();
my @info = ();
my $last_ref_line = "";
my @changed_register=();
my $ref_pc;
my $ref_cwp;
my $ref_reg_id;
my $ref_reg_val_low;
my $ref_reg_val_high;
my $ref_double_flag;
my $ref_pc_sign;
my $ref_reg_val_sign;
my $trace_file; 
my $reference_file;
my $report_file = 'analysis_results.txt';
my $last_cwp = ''; 
my $starting_window = 1; # '1' indicates begining of execution no need of changing window
# Keeping track of trace file lines
my $both_traces_finished = 0;
my $ref_hav_pending = 0;
my $trace_hav_pending = 0;
my $invalid_lines = 0;
my $finish_status = "";
my $pending_type = 0;
my $count_reg_writes = 0;

GetOptions(
    'ref=s' => \$reference_file,
    'trace=s' => \$trace_file,
    'result=s' => \$report_file,
) or die "\nUsage: $0 [--trace <trace file name>] [--ref <reference file name>\n\n";

if (!defined $trace_file || !defined $reference_file) {
    say "\nUsage: $0 [--trace <trace file name>] [--ref <reference file ename>\n\n";
    exit;
} 

# Chekking both trace have same line counts
my $count_ref;
my $count_trace;
$count_ref = `wc -l < $reference_file`;
die "wc failed do you have word-count program installed: $?" if $?;
$count_trace =`wc -l < $trace_file`; 
chomp($count_ref);
chomp($count_trace);
if ($count_trace != $count_ref) {
    push @warning, {'comment' => "Traces have diffrent line counts:> reference: $count_ref, trace: $count_trace.", 'register' => ""};
}
$count_ref = $count_trace = 0; # Now used for stroring current line count

open (my $trace_fh, '<', $trace_file) or die "Could not open the '$trace_file' $!";
open (my $reference_fh, '<', $reference_file) or die "Could not open the '$reference_file' $!";
open (my $trace_fh_x, '<', $trace_file) or die "Could not open the '$trace_file' $!";     # trace file handle

read_reference($reference_fh);	# Start first subroutine

##################################################################################
#---------------------------- Actual execution loop -----------------------------#
##################################################################################

REFERENCE_LOOP:
    if($end_of_trace_file) {
        # The trace file is ended where reference have entries remaining
        # Possibility: u-arch model might be stuck at some place
        goto CREATE_REPORT;
    }
    read_reference($reference_fh);

TRACE_ANALYZE_LOOP:
    analyze_trace($trace_fh_x);

#----------------------------_Actual Execution Loop Ends_--------------------------

CREATE_REPORT:
    # verdict for diffrent number of lines in trace files
    if($end_of_reference_file && $end_of_trace_file) {  # Have same number of lines
        if(!@error) { $pending_type = 0;   } # pending_type:0 => have no pending lines
        $finish_status = "Analyzed all the Lines\n";
    } elsif(!$end_of_reference_file && $end_of_trace_file){ # Trace file have less number of lines
        if(!@error) { $pending_type = 1;   } # pending_type:1 => trace file have less lines
        push @error, {'comment' => "Trace file ended before Expected: last executed ", 'register' => "$ref_last_exec_pc"};
        $finish_status = "Trace file has less number of lines ( u-arch model stuck ?! )\n";
    } elsif($end_of_reference_file && !$end_of_trace_file){ # Trace have more number of entries.
        if(!@error) { $pending_type = 2;  }  # pending_type:2 => ref file have less lines 
        push @error, {'comment' => "Trace file have entries even after test finished(reference compleeted)", 'register' => "$ref_last_exec_pc"};
        $finish_status = "Trace file have unexpected entries after finishing the test\n";
    } else {
        print "should not reach here\n";
        $finish_status = "Something went wrong. problem with inner script\n";
        exit;
    }
    generate_report();
    send_return_val();
    exit;   # Normal exit point of script
#################################################################################


#--------- First subroutine  Analyze reference file -----------#
sub read_reference {
    my ($reference_fh) = @_;
    while (my $row = <$reference_fh>) {

        # Informing ending of reference to trace-analyze loop
        $count_ref++;   #line count
        if(eof($reference_fh)) { 
            $end_of_reference_file = 1; 
        }
        if ($row =~ /^\/\//) {
            if ($end_of_reference_file) { goto CREATE_REPORT;}
            next;
        } # Skip commented lines
        if ($row =~ /^\s*$/) {  # Skip blank lines
            if ($end_of_reference_file) { goto CREATE_REPORT;}
            next;
        }
        chomp $row;     #removing new-line charector(\n)

        # Skipping unknown lines
        unless ($row =~ /^pc\[0x[0-9a-fA-F]{8}\]\s?:\s+cwp\[[0-7]\]\s+reg_id\[\d+\]\s+flag\[[0-1]\]\s+value_high\[0x[0-9a-fA-F]{8}\]\s+value_low\[0x[0-9-a-fA-F]{8}\]/) {
            # Do not have proper trace format
            $invalid_lines++;
            push @error, {'comment' => "Invalid line in reference file", 'register' => "", 'line' => "reference - line : $count_ref"};
            if ($end_of_reference_file) { goto CREATE_REPORT;}
            next;
        } else {

            $count_reg_writes++;    # To keep count of total number of reg-writes
            # Extracting register write details from each line
            if ($row =~ /reg_id\[(.*?)\]/) { $reg_id = $1; }
            if ($row =~ /pc\[(.*?)\]/) { $pc = $1; }
            if ($row =~ /cwp\[(.*?)\]/) { $cwp = $1; }
            if ($row =~ /flag\[(.*?)\]/) { $double_flag = $1; }
            if ($row =~ /value_high\[(.*?)\]/) { $reg_value_high = $1; }
            if ($row =~ /value_low\[(.*?)\]/) { $reg_value_low = $1; }

            # ------------ Switch window if changed ---------------#
            if($last_cwp ne $cwp) {
                #print "\nwindow changed:>\tprevious window: $last_cwp | current window: $cwp\n";
                if(!$starting_window ) {
                    #load_window($last_cwp, $cwp);
                } else {
                    $starting_window = 0;
                } 
                $last_cwp = $cwp;
            }
            
            my %reg = decode_regid($reg_id);    # Identify register from reg_id
            
            # passing reference value to analyze-trace loop
            $ref_pc             = substr $pc, 2; #remove 0x at the begining
            $ref_cwp            = hex($cwp); 
            $ref_reg_id         = $reg_id;
            $ref_reg_val_high   = substr $reg_value_high, 2;
            $ref_reg_val_low    = substr $reg_value_low, 2;
            $ref_double_flag    = hex($double_flag);

            $ref_last_exec_pc = $pc;

        }   
        goto TRACE_ANALYZE_LOOP;
    } # file reading while loop
}

# Trace signature
#   b31 - b18 => PC (14 bits)
#   b17 - b15 => CWP (3 bits)
#   b14 => iu_reg updated (1 bit)
#   b13 => double flag (1 bit)
#   b12 - b8 => reg_id (5 bits)
#   b7 - b0 => reg_value (8 bits)
#   reg_value = reg_val_low (xor) reg_val_high
#------- Second subroutine Read the trace file ----------#
sub analyze_trace {
    my($in, $write) = @_;
    while (my $row = <$in>) {
        # Informing ending of trace-analyze loop
        $count_trace++;   #line count
        if(eof($in)) { 
            $end_of_trace_file = 1; 
        }
        if ($row =~ /^\/\//) {  # Skip commented lines
            if($end_of_trace_file) {push @warning, {'comment' => "Last line of trace is commented!. Didn't verified the last register write", 'register' => "Line no($count_trace)", 'line' => ""};
            }
            next;
        }
        if ($row =~ /^\s*$/) {# Skip blank lines
            if($end_of_trace_file) {push @warning, {'comment' => "Last line of trace is blank!. Didn't verified the last register write", 'register' => "Line no($count_trace)", 'line' => ""};
            }
            next;
        }
        chop($row); # removing newline charector @ end
        unless ($row =~ /^Log\[\d+\]\s+=\s+[0-9a-fA-F]{8}$/) {
            # Do not have proper trace format
            $invalid_lines++;
            push @error, {'comment' => "Invalid line in trace file", 'register' => "", 'line' => "at line : $count_trace"};
            next;
        } else {
            # Proper formatted entry, Extracting signature from trace row
            my @row_split_arr = split /\s+/, $row;
            my $signature = $row_split_arr[2];

            #---------- Check CWP, reg_id, write_double_flag matches ----#
            my $trace_cwp           = extract_cwp( $signature );
            my $trace_reg_id        = extract_reg_id( $signature );
            my $trace_pc_sign       = extract_pc_sign( $signature );
            my $trace_reg_val_sign  = extract_reg_val_sign( $signature );
            my $trace_pc_val        = extract_trace_pc_value( $signature );
               $ref_pc_sign         = create_pc_sign($ref_pc);

            if ( $trace_pc_sign == $ref_pc_sign ) {
                if( $trace_cwp == $ref_cwp) {
                    if($trace_reg_id == $ref_reg_id ) {
                        $ref_reg_val_sign = create_reg_val_sign($ref_double_flag, $ref_reg_val_low, $ref_reg_val_high);
                        if ($trace_reg_val_sign == $ref_reg_val_sign) {
                            push @info, {'comment' => "Register value chaged as expected", 'register' => "on PC: $ref_pc"};
                        } else {
                            push @error, {'comment' => "register-values does not match", 'register' => "on PC: $ref_pc", 'line' => "ref-line: $count_ref | trace-line: $count_trace"};
                        }
                    } else {
                        # Register is diffrent in reference and trace
                        my %ref_register = decode_regid($ref_reg_id);    # Identify register from reg_id
                        my %trace_register = decode_regid($trace_reg_id);    # Identify register from reg_id
                        push @error, {'comment' => "Register-ids are different :> reference: $ref_register{type}\[$ref_register{id}\] | trace: $trace_register{type}\[$trace_register{id}\]", 'line' => "ref-line: $count_ref | trace-line: $count_trace" 
                                        ,'register' => "on PC: $ref_pc"};
                    }
                } else {
                    # CWP of trace and reference are diffrent
                    push @error, {'comment' => "Have different windows    :> reference cwp: $ref_cwp | trace cwp: $trace_cwp "
                                        , 'register' => "on PC: $ref_pc", 'line' => "ref-line: $count_ref | trace-line: $count_trace"};
                }
            } else {
                push @error, {'comment' => "PC does not match, trace PC $trace_pc_val", 'register' => "on PC: $ref_pc", 'line' => "ref-line: $count_ref | trace-line: $count_trace"};
            }
        } #--- End of comparison -----#
            
        if($end_of_reference_file) {
        # All entries in reference has been tested
            goto CREATE_REPORT;
        }
        #---- test not yet complete ----#
        goto REFERENCE_LOOP;
    } # end of file reading while loop --- #
} # -------------------------- End of Second subroutine ------------------------------#



#----------- Retrive register details from regid -------#
sub decode_regid {
    my ( $reg_id ) = @_;
    my %register = ('type' => "", 'id' => "");
    if ($reg_id >= 0 && $reg_id <8) {
        $register{type} = "globals";
        $register{id} = $reg_id;
    } elsif ($reg_id>=8 && $reg_id <16){
        $register{type} = "outs";
        $register{id} = $reg_id - 8;
    } elsif ($reg_id>=16 && $reg_id <24){
        $register{type} = "locals";
        $register{id} = $reg_id - 16;
    } elsif ($reg_id>=24 && $reg_id <32){
        $register{type} = "ins";
        $register{id} = $reg_id - 24;
    } else {
        #print "invalid regid\n";
        exit;
    }
    return %register;
}


#---------------------------- Report Generation ------------------------------#
sub generate_report {
    open (my $report_fh, '>', $report_file) or die "Could not open the '$report_file' $!";
    print $report_fh "Summery of execution\n====================\n";
    my $error_count = scalar(grep $_, @error);
    my $warning_count = scalar(grep $_, @warning);
    my $info_count = scalar(grep $_, @info);
    print $report_fh "\tTotal register writes    : $count_reg_writes (as per reference file)\n";
    print $report_fh " "x33 if ($end_of_trace_file && !$end_of_reference_file);

    print $report_fh ": before execution stopped at reference line: $count_ref\n" if ($end_of_trace_file && !$end_of_reference_file);
    print $report_fh "\tTotal Errors             : $error_count";
    print $report_fh " (out of which '$invalid_lines' invalid line errors)"if ($invalid_lines > 0);
    print $report_fh "\n\tTotal Warnings           : $warning_count\n";
    print $report_fh "\tNumber of lines matched  : $info_count\n";
    print $report_fh "\tExecution finish status  : $finish_status"; # If lines of trace files are not equal
    print $report_fh "-"x57; print $report_fh "-"x39 if (!$end_of_reference_file || !$end_of_trace_file); print $report_fh "\n";

    if(!@error) { print $report_fh "\nError:\n======\n\tThere are no Errors!\n"; } else {
        print $report_fh "\nError:\n======\n";
        foreach my $index (@error) {
            print $report_fh "\tError: $index->{comment}  $index->{register} \t($index->{line})\n";
        }
    }
    if(!@warning) { print $report_fh "\nWarning:\n=======\n\tThere are no Warnings!\n"; } else {
        print $report_fh "\nWarning:\n=======\n";
        foreach my $index (@warning) {
            print $report_fh "\tWarning: $index->{comment}  $index->{register}\n";
        }
    }
    if(!@info) { print $report_fh "\nInfo:\n======\n\tThere are no Infos!\n"; } else {
        print $report_fh "\nInfo:\n======\n";
        foreach my $index (@info) {
            print $report_fh "\tInfo: $index->{comment} on: $index->{register}\n";
        }
    }
}   #------------------------- End of Report Generation -----------------------#


# ------------ CWP is represented by 3 bits (b17, b16, b15) -----#
sub extract_cwp {
    my($window) = @_;
    my $trace_cwp_sign =  hex( substr( $window, 3, 2) );
    $trace_cwp_sign &= 0x38;
    my $trace_cwp = $trace_cwp_sign >> 3;
    return $trace_cwp
}

#------------ reg_id is represented by 5 bits (b12 - b8)-----------#
sub extract_reg_id {
    my($reg_id) = @_;
    $reg_id = hex($reg_id) & 0x00001F00;
    $reg_id = $reg_id >> 8;
    return $reg_id;
}

#----------- Extracting least significat 14 bits ------------#
sub create_pc_sign {
    my($pc_sgn) = @_;
    $pc_sgn = hex( $pc_sgn ) & 0x00003FFF;
    return $pc_sgn;
}

#------ Extracting Most significat 14 bits of signature -----#
sub extract_pc_sign {
    my ($pc_sgn) = @_;
    $pc_sgn = hex($pc_sgn) & 0xFFFC0000;
    $pc_sgn = $pc_sgn >> 18;
    return $pc_sgn;
}

#------ Extracting last 3 hex bits of trace pc form signature -----#
sub extract_trace_pc_value {
    my ($pc_val) = @_;
    $pc_val = hex($pc_val) & 0x3FFC0000;
    $pc_val = $pc_val >> 18;
    $pc_val = sprintf("0x-----%03x", $pc_val);
    return $pc_val;
}


#---------- Create signature of register_value ------#
sub create_reg_val_sign {
    my($double_flag, $reg_low_val, $reg_high_val) = @_;

    my ( $reg_val_low_sgn, $reg_val_high_sgn ) = 0x00;
    my @arr1 = unpack("(A2)*", $reg_low_val);
    my @arr2 = unpack("(A2)*", $reg_high_val);

    $reg_val_low_sgn  ^= hex($_) for @arr1;
    $reg_val_high_sgn ^= hex($_) for @arr2;
    my $reg_val_signature = ( $double_flag ) ? ($reg_val_high_sgn ^ $reg_val_low_sgn) : $reg_val_low_sgn;

    return $reg_val_signature;
}


#------- Register value is specified in 8 bits (7 - 0) ------#
sub extract_reg_val_sign {
    my ( $reg_val ) = @_;
    $reg_val = hex($reg_val) & 0x000000FF;
    return $reg_val;
}

#----- Informing calling script ------#
# Pending type:
#  0 :> No pending, all lines has been executed
#  1 :> Trace file have less number of lines
#  2 :> Reference file have less number of lines
sub send_return_val {
    my $error_count = scalar(grep $_, @error);
    my $warning_count = scalar(grep $_, @warning);
    if ((!@error) && (!@warning) && $pending_type == 0) {
        print "SUCCESS|0|NONE"
    }elsif ((!@error) && (@warning)) {
        print "WARNING|$warning_count|WARNINGS" 
    }elsif ((@error)  && $pending_type == 1) {
        print "FAIL|$error_count|TRACE"
    }elsif ((@error) && $pending_type == 2) {
        print "FAIL|$error_count|REF"
    } else {
        print "FAIL|$error_count|ERROR"
    }
}
