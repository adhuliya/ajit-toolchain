#ifndef __EXECUTE_H__
#define __EXECUTE_H__

#endif /* EXECUTE_H_ */
uint8_t isNaN32(float op);
uint8_t isNaN64(double op);
uint8_t check_sNaN32(float op);
uint8_t check_sNaN64(double op);
uint32_t executeInstruction(Opcode opcode, uint32_t operand2, uint32_t operand1, uint32_t *result_h, uint32_t *result_l,
		 		uint8_t *flags, ProcessorState *s, uint8_t rs1, uint8_t rd, uint8_t asi, uint32_t data1, uint32_t data0);

uint32_t executeFPInstruction(Opcode opcode, uint32_t operand2_3, uint32_t operand2_2, uint32_t operand2_1,
		uint32_t operand2_0, uint32_t operand1_3, uint32_t operand1_2, uint32_t operand1_1, uint32_t operand1_0, uint32_t *result_h2,
		uint32_t *result_h1, uint32_t *result_l2, uint32_t *result_l1, uint32_t trap_vector, uint8_t *flags, uint8_t *ft, StatusRegisters *ptr);

void executeTrap(uint32_t *trap_vector, uint32_t *psr, uint32_t *tbr, uint8_t *interrupt_level, ProcessorMode *p_mode,
		uint8_t ticc_trap_type, uint32_t *pc, uint32_t *npc);



