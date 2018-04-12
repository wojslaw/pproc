#include "InstructionSetImplementation.hpp"




void no_operation(class VirtualMachineState *state)
{
	// do nothing xD
	return;
}

// Incrementing
void  increment_register (
		class VirtualMachineState * vmstate, 
		char register_name )
{
	uint8_t regval = vmstate->getRegisterByName(register_name);
	regval++;
	vmstate->setRegisterByName(register_name, regval);

}


void  decrement_register (
		class VirtualMachineState *vmstate , 
		char register_name )
{
	uint8_t regval = vmstate->getRegisterByName(register_name);
	regval--;
	vmstate->setRegisterByName(register_name, regval);
}


// Stack {
void  push_register (
		class VirtualMachineState *vmstate ,
		char register_name ) 
{
	static const uint8_t stack_page = MEMPAGE_STACK;
	
	uint8_t pushed_reg = vmstate->getRegisterByName (register_name);
	uint8_t reg_s = vmstate->getRegisterByName ('s'); 
	
	uint8_t *ptr_stktop = vmstate->accessMemoryAt (stack_page, reg_s);
	(*ptr_stktop) = pushed_reg;
	vmstate->setRegisterByName('s', reg_s + 1);
}


void  pop_register(
		class VirtualMachineState *vmstate ,
		char register_name )
{
	static const uint8_t stack_page = MEMPAGE_STACK;
	
	uint8_t reg_s = vmstate->getRegisterByName('s');
	reg_s--;
	uint8_t *ptr_stktop = vmstate->accessMemoryAt (stack_page, reg_s);
	
	uint8_t popped_reg = *ptr_stktop;
	vmstate->setRegisterByName(register_name, *ptr_stktop);
	vmstate->setRegisterByName('s', reg_s);
}
// } endof Stack


// ALU {

void  add_with_carry (class VirtualMachineState *vmstate)
{
	uint8_t reg_a = vmstate->getRegisterByName('a');
	uint8_t reg_b = vmstate->getRegisterByName('b');
	reg_a = reg_a + reg_b;

	vmstate->setRegisterByName('a', reg_a);

}
void  subtract_with_carry (class VirtualMachineState *vmstate)
{
	uint8_t reg_a = vmstate->getRegisterByName('a');
	uint8_t reg_b = vmstate->getRegisterByName('b');
	reg_a = reg_a - reg_b;

	vmstate->setRegisterByName('a', reg_a);

}
void  xor_bitwise (class VirtualMachineState *vmstate)
{
	uint8_t reg_a = vmstate->getRegisterByName('a');
	uint8_t reg_b = vmstate->getRegisterByName('b');
	reg_a = reg_a ^ reg_b;

	vmstate->setRegisterByName('a', reg_a);
}
void  or_bitwise (class VirtualMachineState *vmstate)
{
	uint8_t reg_a = vmstate->getRegisterByName('a');
	uint8_t reg_b = vmstate->getRegisterByName('b');
	reg_a = reg_a | reg_b;

	vmstate->setRegisterByName('a', reg_a);
}
void  and_bitwise (class VirtualMachineState *vmstate)
{
	uint8_t reg_a = vmstate->getRegisterByName('a');
	uint8_t reg_b = vmstate->getRegisterByName('b');
	reg_a = reg_a & reg_b;

	vmstate->setRegisterByName('a', reg_a);
}
void  not_bitwise (class VirtualMachineState *vmstate)
{
	uint8_t reg_a = vmstate->getRegisterByName('a');
	uint8_t reg_b = vmstate->getRegisterByName('b');
	reg_a = ~reg_b;

	vmstate->setRegisterByName('a', reg_a);
	
}


void  rotate_left (class VirtualMachineState *vmstate)
{
	printf("\n WARNING: Rotate unimplemented.");
}
void  rotate_right (class VirtualMachineStateState *vmstate)
{
	printf("\n WARNING: Rotate unimplemented.");
}
// 
void  logical_shift_left (class VirtualMachineState *vmstate)
{
	uint8_t reg_a = vmstate->getRegisterByName('a');
	reg_a = reg_a << 1;

	vmstate->setRegisterByName('a', reg_a);
}
void  logical_shift_right (class VirtualMachineState *vmstate)
{
	uint8_t reg_a = vmstate->getRegisterByName('a');
	reg_a = reg_a >> 1;

	vmstate->setRegisterByName('a', reg_a);
}


// }



// { 
void  load_a_with_value (
		class VirtualMachineState * vmstate, 
		uint8_t value )
{
	vmstate->setRegisterByName('a', value);
}


void  load_a_from_memory (class VirtualMachineState *vmstate)
{
	uint8_t *memory_at_xy = vmstate->accessMemoryByXY();
	uint8_t value = *memory_at_xy;

	vmstate->setRegisterByName('a', value);
}


void  save_a_to_memory (class VirtualMachineState *vmstate)
{
	uint8_t *memory_at_xy = vmstate->accessMemoryByXY();
	uint8_t value = vmstate->getRegisterByName('a');

	*memory_at_xy = value;
}
// }


// Transfers {
void  transfer_a_to_register (
		class VirtualMachineState * vmstate, 
		char register_name )
{
	uint8_t reg_a = vmstate->getRegisterByName('a');
	vmstate->setRegisterByName(register_name, reg_a);
}


void  transfer_register_to_a (
		class VirtualMachineState * vmstate, 
		char register_name )
{
	uint8_t regval = vmstate->getRegisterByName(register_name);
	vmstate->setRegisterByName('a', regval);
}
// }

// */
