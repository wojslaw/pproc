#include "InstructionSet.hpp"



void InstructionSet::addInstructionToSet(
		std::string mnemonic, 
		std::string fullname, 
		operationPointer_impliedAdres op_ptr )
{
	instructions_vector.push_back( Instruction(mnemonic, fullname, op_ptr) );
	number_of_instructions++;
}
void InstructionSet::addInstructionToSet(
		std::string mnemonic, 
		std::string fullname, 
		operationPointer_registerAdres op_ptr )
{
	instructions_vector.push_back( Instruction(mnemonic, fullname, op_ptr) );
	number_of_instructions++;
}
void InstructionSet::addInstructionToSet(
		std::string mnemonic, 
		std::string fullname, 
		operationPointer_valueAdres op_ptr )
{
	instructions_vector.push_back( Instruction(mnemonic, fullname, op_ptr) );
	number_of_instructions++;
}

InstructionSet::InstructionSet()
{
	invalid_instruction = Instruction();
	int implied = Instruction::InstructionAdrestype::implied;
	int reg = Instruction::InstructionAdrestype::reg;
	int value = Instruction::InstructionAdrestype::value;


	instructions_vector.reserve(0xff);
	
	addInstructionToSet("nop", "no-operation", &no_operation );

	addInstructionToSet("inc", "increment-register", &increment_register);
	addInstructionToSet("dec", "decrement-register", &decrement_register );

	// ALU:
	addInstructionToSet("add", "add-with-carry", &add_with_carry );
	addInstructionToSet("sub", "subtract-with-carry", &subtract_with_carry );
	addInstructionToSet("xor", "xor-bitwise", &xor_bitwise );
	addInstructionToSet("ora", "or-bitwise", &or_bitwise );
	addInstructionToSet("and", "and-bitwise", &and_bitwise );
	addInstructionToSet("not", "not-bitwise", &not_bitwise );
	addInstructionToSet("shl", "shift-left", &logical_shift_left );
	addInstructionToSet("shr", "shift-right", &logical_shift_right );


	// Loading registers
	// Save
	addInstructionToSet("ldv", "load-a-with-value", &load_a_with_value );
	addInstructionToSet("ldm", "load-a-from-memory", &load_a_from_memory );
	addInstructionToSet("sva", "save-a-to-memory", &save_a_to_memory );


	// Transfer between reg_a
	addInstructionToSet("tat", "transfer-a-to-register", &transfer_a_to_register );
	addInstructionToSet("tta", "transfer-register-to-a", &transfer_register_to_a );

	// Stack
	addInstructionToSet("psh", "push-register-onto-stack", &push_register);
	addInstructionToSet("pop", "pop-stack-to-register", &pop_register);

	// Conditions
	addInstructionToSet("isz", "is-a-zero", &is_zero );
	addInstructionToSet("igb", "is-a-greater-than-b", &is_a_greater_than_b );
	// Jumps
	addInstructionToSet("jmp", "jump-uncoditional", &jump_uncoditional );
	addInstructionToSet("jif", "jump-if", &jump_if);
	addInstructionToSet("jin", "jump-if-not", &jump_if_not);
	
	
	if ( instructions_vector.size() != number_of_instructions ) { 
		std::cout << "\nWarning: size of instructions_vector is different from the count number_of_instructions!"; 
	} else {
		//set opcodes:
		for( size_t i = 0; i < instructions_vector.size(); i++) {
			instructions_vector.at(i).opcode = i ;
		}
	}
	
}


void InstructionSet::printInstructionSet()
{
	for(auto instruction : instructions_vector ) {
		printf("\n");
		instruction.printInstruction();
	}
}


struct Instruction InstructionSet::findInstructionByMnemonic(std::string mnemonic)
{
	for( auto instruction : instructions_vector ) {
		if( instruction.mnemonic == mnemonic ) {
			return instruction;
		}
	}
	
	std::cout << "\nWarning: Instruction with mnemonic " << mnemonic << "not found";

	return invalid_instruction;
}
