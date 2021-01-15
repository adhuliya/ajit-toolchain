/* Generated automatically by the program 'build/genpreds'
   from the machine description file '../../gcc/config/sparc/sparc.md'.  */

#ifndef GCC_TM_PREDS_H
#define GCC_TM_PREDS_H

#ifdef HAVE_MACHINE_MODES
extern int general_operand (rtx, enum machine_mode);
extern int address_operand (rtx, enum machine_mode);
extern int register_operand (rtx, enum machine_mode);
extern int pmode_register_operand (rtx, enum machine_mode);
extern int scratch_operand (rtx, enum machine_mode);
extern int immediate_operand (rtx, enum machine_mode);
extern int const_int_operand (rtx, enum machine_mode);
extern int const_double_operand (rtx, enum machine_mode);
extern int nonimmediate_operand (rtx, enum machine_mode);
extern int nonmemory_operand (rtx, enum machine_mode);
extern int push_operand (rtx, enum machine_mode);
extern int pop_operand (rtx, enum machine_mode);
extern int memory_operand (rtx, enum machine_mode);
extern int indirect_operand (rtx, enum machine_mode);
extern int ordered_comparison_operator (rtx, enum machine_mode);
extern int comparison_operator (rtx, enum machine_mode);
extern int const_zero_operand (rtx, enum machine_mode);
extern int const_all_ones_operand (rtx, enum machine_mode);
extern int const_4096_operand (rtx, enum machine_mode);
extern int small_int_operand (rtx, enum machine_mode);
extern int uns_small_int_operand (rtx, enum machine_mode);
extern int const_high_operand (rtx, enum machine_mode);
extern int const_compl_high_operand (rtx, enum machine_mode);
extern int fp_const_high_losum_operand (rtx, enum machine_mode);
extern int const_double_or_vector_operand (rtx, enum machine_mode);
extern int zero_or_v7_operand (rtx, enum machine_mode);
extern int symbolic_operand (rtx, enum machine_mode);
extern int tgd_symbolic_operand (rtx, enum machine_mode);
extern int tld_symbolic_operand (rtx, enum machine_mode);
extern int tie_symbolic_operand (rtx, enum machine_mode);
extern int tle_symbolic_operand (rtx, enum machine_mode);
extern int medium_pic_operand (rtx, enum machine_mode);
extern int label_ref_operand (rtx, enum machine_mode);
extern int data_segment_operand (rtx, enum machine_mode);
extern int text_segment_operand (rtx, enum machine_mode);
extern int register_or_zero_operand (rtx, enum machine_mode);
extern int register_or_v9_zero_operand (rtx, enum machine_mode);
extern int register_or_zero_or_all_ones_operand (rtx, enum machine_mode);
extern int fp_register_operand (rtx, enum machine_mode);
extern int int_register_operand (rtx, enum machine_mode);
extern int fcc_register_operand (rtx, enum machine_mode);
extern int fcc0_register_operand (rtx, enum machine_mode);
extern int icc_or_fcc_register_operand (rtx, enum machine_mode);
extern int arith_operand (rtx, enum machine_mode);
extern int arith_double_operand (rtx, enum machine_mode);
extern int arith_add_operand (rtx, enum machine_mode);
extern int arith_double_add_operand (rtx, enum machine_mode);
extern int arith10_operand (rtx, enum machine_mode);
extern int arith11_operand (rtx, enum machine_mode);
extern int uns_arith_operand (rtx, enum machine_mode);
extern int compare_operand (rtx, enum machine_mode);
extern int input_operand (rtx, enum machine_mode);
extern int call_address_operand (rtx, enum machine_mode);
extern int call_operand (rtx, enum machine_mode);
extern int mem_noofs_operand (rtx, enum machine_mode);
extern int noov_compare_operator (rtx, enum machine_mode);
extern int noov_compare64_operator (rtx, enum machine_mode);
extern int v9_register_compare_operator (rtx, enum machine_mode);
extern int cc_arith_operator (rtx, enum machine_mode);
extern int cc_arith_not_operator (rtx, enum machine_mode);
#endif /* HAVE_MACHINE_MODES */

#define CONSTRAINT_NUM_DEFINED_P 1
enum constraint_num
{
  CONSTRAINT__UNKNOWN = 0,
  CONSTRAINT_b,
  CONSTRAINT_c,
  CONSTRAINT_d,
  CONSTRAINT_e,
  CONSTRAINT_f,
  CONSTRAINT_h,
  CONSTRAINT_w,
  CONSTRAINT_G,
  CONSTRAINT_C,
  CONSTRAINT_H,
  CONSTRAINT_I,
  CONSTRAINT_J,
  CONSTRAINT_K,
  CONSTRAINT_L,
  CONSTRAINT_M,
  CONSTRAINT_N,
  CONSTRAINT_O,
  CONSTRAINT_P,
  CONSTRAINT_D,
  CONSTRAINT_Q,
  CONSTRAINT_R,
  CONSTRAINT_S,
  CONSTRAINT_T,
  CONSTRAINT_U,
  CONSTRAINT_W,
  CONSTRAINT_Y,
  CONSTRAINT_Z,
  CONSTRAINT__LIMIT
};

extern enum constraint_num lookup_constraint (const char *);
extern bool constraint_satisfied_p (rtx, enum constraint_num);

#define CONSTRAINT_LEN(c_,s_) 1

extern enum reg_class regclass_for_constraint (enum constraint_num);
#define REG_CLASS_FROM_CONSTRAINT(c_,s_) \
    regclass_for_constraint (lookup_constraint (s_))
#define REG_CLASS_FOR_CONSTRAINT(x_) \
    regclass_for_constraint (x_)

extern bool insn_const_int_ok_for_constraint (HOST_WIDE_INT, enum constraint_num);
#define CONST_OK_FOR_CONSTRAINT_P(v_,c_,s_) \
    insn_const_int_ok_for_constraint (v_, lookup_constraint (s_))

#define CONST_DOUBLE_OK_FOR_CONSTRAINT_P(v_,c_,s_) \
    constraint_satisfied_p (v_, lookup_constraint (s_))

#define EXTRA_CONSTRAINT_STR(v_,c_,s_) \
    constraint_satisfied_p (v_, lookup_constraint (s_))

extern bool insn_extra_memory_constraint (enum constraint_num);
#define EXTRA_MEMORY_CONSTRAINT(c_,s_) insn_extra_memory_constraint (lookup_constraint (s_))

#define EXTRA_ADDRESS_CONSTRAINT(c_,s_) false

#endif /* tm-preds.h */
