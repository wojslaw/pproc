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

/*
void przejproc::no_operation(class VirtualMachine *vm)
{
	// do nothing xD
	return;
}


// Incrementing
void przejproc::increment_register (
		class VirtualMachine * vm, 
		char register_name )
{
	uint8_t regval = vm->getRegisterByName(register_name);
	regval++;
	vm->setRegisterByName(register_name, regval);

}


void przejproc::decrement_register (
		class VirtualMachine *vm , 
		char register_name )
{
	uint8_t regval = vm->getRegisterByName(register_name);
	regval--;
	vm->setRegisterByName(register_name, regval);
}


// Stack {
void przejproc::push_register (
		class VirtualMachine *vm ,
		char register_name ) 
{
	static const uint8_t stack_page = _MEMPAGE_STACK;
	
	uint8_t pushed_reg = vm->getRegisterByName (register_name);
	uint8_t reg_s = vm->getRegisterByName ('s'); 
	
	uint8_t *ptr_stktop = vm->accessMemoryAt (stack_page, reg_s);
	(*ptr_stktop) = pushed_reg;
	vm->setRegisterByName('s', reg_s + 1);
}


void przejproc::pop_register(
		class VirtualMachine *vm ,
		char register_name )
{
	static const uint8_t stack_page = _MEMPAGE_STACK;
	
	uint8_t reg_s = vm->getRegisterByName('s');
	reg_s--;
	uint8_t *ptr_stktop = vm->accessMemoryAt (stack_page, reg_s);
	
	uint8_t popped_reg = *ptr_stktop;
	vm->setRegisterByName(register_name, *ptr_stktop);
	vm->setRegisterByName('s', reg_s);
}
// } endof Stack


// ALU {

void przejproc::add_with_carry (class VirtualMachine *vm)
{
	uint8_t reg_a = vm->getRegisterByName('a');
	uint8_t reg_b = vm->getRegisterByName('b');
	reg_a = reg_a + reg_b;

	vm->setRegisterByName('a', reg_a);

}
void przejproc::subtract_with_carry (class VirtualMachine *vm)
{
	uint8_t reg_a = vm->getRegisterByName('a');
	uint8_t reg_b = vm->getRegisterByName('b');
	reg_a = reg_a - reg_b;

	vm->setRegisterByName('a', reg_a);

}
void przejproc::xor_bitwise (class VirtualMachine *vm)
{
	uint8_t reg_a = vm->getRegisterByName('a');
	uint8_t reg_b = vm->getRegisterByName('b');
	reg_a = reg_a ^ reg_b;

	vm->setRegisterByName('a', reg_a);
}
void przejproc::or_bitwise (class VirtualMachine *vm)
{
	uint8_t reg_a = vm->getRegisterByName('a');
	uint8_t reg_b = vm->getRegisterByName('b');
	reg_a = reg_a | reg_b;

	vm->setRegisterByName('a', reg_a);
}
void przejproc::and_bitwise (class VirtualMachine *vm)
{
	uint8_t reg_a = vm->getRegisterByName('a');
	uint8_t reg_b = vm->getRegisterByName('b');
	reg_a = reg_a & reg_b;

	vm->setRegisterByName('a', reg_a);
}
void przejproc::not_bitwise (class VirtualMachine *vm)
{
	uint8_t reg_a = vm->getRegisterByName('a');
	uint8_t reg_b = vm->getRegisterByName('b');
	reg_a = ~reg_b;

	vm->setRegisterByName('a', reg_a);
	
}


void przejproc::rotate_left (class VirtualMachine *vm)
{

}
void przejproc::rotate_right (class VirtualMachineState *vm)
{

}
// 
void przejproc::logical_shift_left (class VirtualMachine *vm)
{
	uint8_t reg_a = vm->getRegisterByName('a');
	reg_a = reg_a << 1;

	vm->setRegisterByName('a', reg_a);
}
void przejproc::logical_shift_right (class VirtualMachine *vm)
{
	uint8_t reg_a = vm->getRegisterByName('a');
	reg_a = reg_a >> 1;

	vm->setRegisterByName('a', reg_a);
}


// }



// { 
void przejproc::load_a_with_value (
		class VirtualMachine * vm, 
		uint8_t value )
{
	vm->setRegisterByName('a', value);
}


void przejproc::load_a_from_memory (class VirtualMachine *vm)
{
	uint8_t *memory_at_xy = vm->accessMemoryByXY();
	uint8_t value = *memory_at_xy;

	vm->setRegisterByName('a', value);
}


void przejproc::save_a_to_memory (class VirtualMachine *vm)
{
	uint8_t *memory_at_xy = vm->accessMemoryByXY();
	uint8_t value = vm->getRegisterByName('a');

	*memory_at_xy = value;
}
// }


// Transfers {
void przejproc::transfer_a_to_register (
		class VirtualMachine * vm, 
		char register_name )
{
	uint8_t reg_a = vm->getRegisterByName('a');
	vm->setRegisterByName(register_name, reg_a);
}


void przejproc::transfer_register_to_a (
		class VirtualMachine * vm, 
		char register_name )
{
	uint8_t regval = vm->getRegisterByName(register_name);
	vm->setRegisterByName('a', regval);
}
// }
*/

