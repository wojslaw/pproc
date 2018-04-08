#include "Instructions.h"

void przejproc::no_operation(class VirtualMachine *vm)
{
	// do nothing xD
	return;
}

// Incrementing
void przejproc::increment_register (
		class VirtualMachine *vm, 
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
	static const uint8_t stack_page = MEMPAGE_STACK;
	
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
	static const uint8_t stack_page = MEMPAGE_STACK;
	
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

/*
void przejproc::rotate_left (class VirtualMachine *vm)
{

}
void przejproc::rotate_right (class VirtualMachineState *vm)
{

}
// */
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
