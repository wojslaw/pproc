#include "Instructions.hpp"


InstructionSet::InstructionSet()
{
	ins_vector.reserve(0xff);
/*
	// List of instructions/operations, added to the vector:
	addInstructionToSet("nop", "no-operation" &no_operation );

	// Increment/decrement will be commonly used on probably all registers, so I decided to just make a set of inc/dec operations for all registers
	addInstructionToSet( "inc", "increment_register" &increment_register );
	addInstructionToSet( "dec", "decrement-register" &decrement_register );

	// ALU:
	addInstructionToSet("add", "add-with-carry", &add_with_carry );
	addInstructionToSet("sub", "subtract-with-carry", &subtract_with_carry );
	addInstructionToSet("xor", "xor-bitwise", &xor_bitwise );
	addInstructionToSet("ora", "or-bitwise", &or_bitwise );
	addInstructionToSet("and", "and-bitwise", &and_bitwise );
	addInstructionToSet("not", "not-bitwise", &not_bitwise );
	addInstructionToSet("rol", "rotate-left", &rotate_left );
	addInstructionToSet("ror", "rotate-right", &rotate_right );
	addInstructionToSet("shl", "logical-shift-left", &logical_shift_left );
	addInstructionToSet("shr", "logical-shift-right", &logical_shift_right );


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
*/

}

void InstructionSet::printInstructionSet()
{
	for(auto ins : ins_vector ) {
		printf("\n %02x:", ins.opcode );
		std::cout << ins.mnemonic << ", " << ins.fullname;
		printf("(funptr = %p)", ins.op_ptr);
	}
}

void InstructionSet::addInstructionToSet(
		std::string mnemonic, 
		std::string fullname, 
		operation_ptr function_pointer)
{
	printf("Not finished adding instruction");
	number_of_instructions++;
}


struct Instruction InstructionSet::findInstructionByMnemonic(std::string mnemonic)
{
	printf("Not finished finding instruction");
	for( auto ins : ins_vector ) {
		if( ins.mnemonic == mnemonic ) {
			return ins;
		}
	}
	
	std::cout << "\nWarning: Instruction with mnemonic " << mnemonic << "not found";

	return invalid_instruction;
}
