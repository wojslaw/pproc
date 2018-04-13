#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "VirtualMachineState.hpp"
#include "InstructionSetImplementation.hpp"
//#include "VirtualMachine.hpp"


const uint8_t _MEMPAGE_STACK = 0x01;

typedef struct InstructionSet s_instructionset ;

typedef void operation (VirtualMachineState * vmstate);
typedef operation (*operation_ptr);

struct Instruction {
	uint8_t opcode;
	std::string mnemonic;
	std::string fullname;
	operation_ptr op_ptr;
};


struct InstructionSet {
	uint8_t number_of_instructions;
	std::vector<struct Instruction> ins_vector;
	struct Instruction invalid_instruction = { 0x00, "xxx", "invalid-instruction", nullptr};

	// ctor/init
	InstructionSet();
	// methods
	void printInstructionSet(void);
	void addInstructionToSet(std::string, std::string, operation_ptr);
	struct Instruction findInstructionByMnemonic(std::string);


	// operations:
};

