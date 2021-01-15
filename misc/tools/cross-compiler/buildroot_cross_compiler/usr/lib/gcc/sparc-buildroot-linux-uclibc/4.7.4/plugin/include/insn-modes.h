/* Generated automatically from machmode.def and config/sparc/sparc-modes.def
   by genmodes.  */

#ifndef GCC_INSN_MODES_H
#define GCC_INSN_MODES_H

enum machine_mode
{
  VOIDmode,                /* machmode.def:173 */
  BLKmode,                 /* machmode.def:177 */
  CCmode,                  /* machmode.def:205 */
  CCXmode,                 /* config/sparc/sparc-modes.def:39 */
  CC_NOOVmode,             /* config/sparc/sparc-modes.def:40 */
  CCX_NOOVmode,            /* config/sparc/sparc-modes.def:41 */
  CCFPmode,                /* config/sparc/sparc-modes.def:42 */
  CCFPEmode,               /* config/sparc/sparc-modes.def:43 */
  BImode,                  /* machmode.def:180 */
  QImode,                  /* machmode.def:185 */
  HImode,                  /* machmode.def:186 */
  SImode,                  /* machmode.def:187 */
  DImode,                  /* machmode.def:188 */
  TImode,                  /* machmode.def:189 */
  QQmode,                  /* machmode.def:208 */
  HQmode,                  /* machmode.def:209 */
  SQmode,                  /* machmode.def:210 */
  DQmode,                  /* machmode.def:211 */
  TQmode,                  /* machmode.def:212 */
  UQQmode,                 /* machmode.def:214 */
  UHQmode,                 /* machmode.def:215 */
  USQmode,                 /* machmode.def:216 */
  UDQmode,                 /* machmode.def:217 */
  UTQmode,                 /* machmode.def:218 */
  HAmode,                  /* machmode.def:220 */
  SAmode,                  /* machmode.def:221 */
  DAmode,                  /* machmode.def:222 */
  TAmode,                  /* machmode.def:223 */
  UHAmode,                 /* machmode.def:225 */
  USAmode,                 /* machmode.def:226 */
  UDAmode,                 /* machmode.def:227 */
  UTAmode,                 /* machmode.def:228 */
  SFmode,                  /* machmode.def:200 */
  DFmode,                  /* machmode.def:201 */
  TFmode,                  /* config/sparc/sparc-modes.def:24 */
  SDmode,                  /* machmode.def:240 */
  DDmode,                  /* machmode.def:241 */
  TDmode,                  /* machmode.def:242 */
  CQImode,                 /* machmode.def:236 */
  CHImode,                 /* machmode.def:236 */
  CSImode,                 /* machmode.def:236 */
  CDImode,                 /* machmode.def:236 */
  CTImode,                 /* machmode.def:236 */
  SCmode,                  /* machmode.def:237 */
  DCmode,                  /* machmode.def:237 */
  TCmode,                  /* machmode.def:237 */
  V4QImode,                /* config/sparc/sparc-modes.def:48 */
  V2HImode,                /* config/sparc/sparc-modes.def:48 */
  V1SImode,                /* config/sparc/sparc-modes.def:50 */
  V8QImode,                /* config/sparc/sparc-modes.def:47 */
  V4HImode,                /* config/sparc/sparc-modes.def:47 */
  V2SImode,                /* config/sparc/sparc-modes.def:47 */
  V1DImode,                /* config/sparc/sparc-modes.def:49 */
  V16QImode,               /* config/sparc/sparc-modes.def:46 */
  V8HImode,                /* config/sparc/sparc-modes.def:46 */
  V4SImode,                /* config/sparc/sparc-modes.def:46 */
  V2DImode,                /* config/sparc/sparc-modes.def:46 */
  MAX_MACHINE_MODE,

  MIN_MODE_RANDOM = VOIDmode,
  MAX_MODE_RANDOM = BLKmode,

  MIN_MODE_CC = CCmode,
  MAX_MODE_CC = CCFPEmode,

  MIN_MODE_INT = QImode,
  MAX_MODE_INT = TImode,

  MIN_MODE_PARTIAL_INT = VOIDmode,
  MAX_MODE_PARTIAL_INT = VOIDmode,

  MIN_MODE_FRACT = QQmode,
  MAX_MODE_FRACT = TQmode,

  MIN_MODE_UFRACT = UQQmode,
  MAX_MODE_UFRACT = UTQmode,

  MIN_MODE_ACCUM = HAmode,
  MAX_MODE_ACCUM = TAmode,

  MIN_MODE_UACCUM = UHAmode,
  MAX_MODE_UACCUM = UTAmode,

  MIN_MODE_FLOAT = SFmode,
  MAX_MODE_FLOAT = TFmode,

  MIN_MODE_DECIMAL_FLOAT = SDmode,
  MAX_MODE_DECIMAL_FLOAT = TDmode,

  MIN_MODE_COMPLEX_INT = CQImode,
  MAX_MODE_COMPLEX_INT = CTImode,

  MIN_MODE_COMPLEX_FLOAT = SCmode,
  MAX_MODE_COMPLEX_FLOAT = TCmode,

  MIN_MODE_VECTOR_INT = V4QImode,
  MAX_MODE_VECTOR_INT = V2DImode,

  MIN_MODE_VECTOR_FRACT = VOIDmode,
  MAX_MODE_VECTOR_FRACT = VOIDmode,

  MIN_MODE_VECTOR_UFRACT = VOIDmode,
  MAX_MODE_VECTOR_UFRACT = VOIDmode,

  MIN_MODE_VECTOR_ACCUM = VOIDmode,
  MAX_MODE_VECTOR_ACCUM = VOIDmode,

  MIN_MODE_VECTOR_UACCUM = VOIDmode,
  MAX_MODE_VECTOR_UACCUM = VOIDmode,

  MIN_MODE_VECTOR_FLOAT = VOIDmode,
  MAX_MODE_VECTOR_FLOAT = VOIDmode,

  NUM_MACHINE_MODES = MAX_MACHINE_MODE
};

#define CONST_MODE_SIZE const
#define CONST_MODE_BASE_ALIGN const
#define CONST_MODE_IBIT const
#define CONST_MODE_FBIT const

#endif /* insn-modes.h */
