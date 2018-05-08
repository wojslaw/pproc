#pragma once

#include <cstdint>

#include <iostream>
#include <string>
#include <vector>


#include "InstructionSetImplementation.hpp"





struct InstructionSet {
	std::vector<struct Instruction> instructions_vector;
	struct Instruction invalid_instruction;
	
	uint8_t number_of_instructions;
	
	// ctor/init
	InstructionSet();
	
	// methods
		// add instruction
	void addInstructionToSet(
			std::string mnemonic, 
			std::string fullname, 
			operationPointer_impliedAdres op_ptr );
	void addInstructionToSet(
			std::string mnemonic, 
			std::string fullname, 
			operationPointer_registerAdres op_ptr );
	void addInstructionToSet(
			std::string mnemonic, 
			std::string fullname, 
			operationPointer_valueAdres op_ptr );
		
		// other
	void printInstructionSet(void);

	struct Instruction findInstructionByMnemonic(std::string);
	struct Instruction findInstructionByBytecode(uint8_t);


	// operations:
};
