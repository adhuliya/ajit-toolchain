#include <stdio.h>
#include "Opcodes.h"


uint32_t decodeInstruction(uint32_t instruction, uint32_t isa_mode,
				Opcode *code, uint32_t trap_vector, uint8_t *rs1, uint8_t *rs2, 
				uint16_t *simm13, uint8_t *shcnt, uint32_t *disp30, uint32_t *disp22, uint8_t *software_trap, 
				uint8_t *dest_reg, uint8_t *i, uint8_t *a, uint8_t *asi, InstructionType *inst_type, 
				uint8_t *fp_uimp_inst,
				uint8_t *vector_data_type);

void readOperands(RegisterFile* rf,
			Opcode opcode, uint8_t rs1, uint8_t rs2, uint8_t rd, uint16_t simm13, 
			uint8_t shcnt, uint32_t disp30,
			uint32_t disp22, uint8_t software_trap, uint8_t i, 
			uint32_t *operand2_3, uint32_t *operand2_2, uint32_t *operand2_1,
			uint32_t *operand2_0, uint32_t *operand1_3, uint32_t *operand1_2, 
			uint32_t *operand1_1, uint32_t *operand1_0,
			InstructionType type, uint8_t cwp, uint32_t *data1, 
			uint32_t *data, uint8_t *fp_invalid_reg);

uint8_t calculateReadByteMask(Opcode opcode, uint32_t address);
