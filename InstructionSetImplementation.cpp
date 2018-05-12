#include "InstructionSetImplementation.hpp"


void no_operation(class VirtualMachineState *state)
{
	// do nothing xD
	return;
}

void instruction_increment_register(class VirtualMachineState *vmstate_ptr, uint8_t register_bytecode)
{
	vmstate_ptr->setRegisterValueByBytecode(
			register_bytecode, 
			1 + vmstate_ptr->getRegisterValueByBytecode(register_bytecode));
}
void instruction_decrement_register(class VirtualMachineState *vmstate_ptr, uint8_t register_bytecode)
{
	vmstate_ptr->setRegisterValueByBytecode(
			register_bytecode, 
			(-1) + vmstate_ptr->getRegisterValueByBytecode(register_bytecode));
}


// Stack {
void  instruction_push_register (
		class VirtualMachineState *vmstate_ptr ,
		uint8_t register_code) 
{
	uint8_t stack_pointer = vmstate_ptr->getRegisterValueByName("s");
	vmstate_ptr->setRegisterValueByName("s", stack_pointer+1);

	vmstate_ptr->setMemoryValueAt (
			MEMPAGE_STACK, 
			stack_pointer, 
			vmstate_ptr->getRegisterValueByBytecode(register_code) );
}


void  instruction_pop_register (
		class VirtualMachineState *vmstate_ptr ,
		uint8_t register_code ) 
{
	static const uint8_t stack_page = MEMPAGE_STACK;
	
	uint8_t stack_pointer = vmstate_ptr->getRegisterValueByName("s");
	--stack_pointer;
	vmstate_ptr->setRegisterValueByName("s", stack_pointer);

	uint8_t value = vmstate_ptr->getMemoryValueAt(MEMPAGE_STACK, stack_pointer);
	vmstate_ptr->setRegisterValueByBytecode(register_code, value);
	
}
// } endof Stack

















// Old, legacy instructions:

// Incrementing
void  increment_register (
		class VirtualMachineState * vmstate, 
		std::string register_name )
{
	uint8_t regval = vmstate->getRegisterValueByName(register_name);
	regval++;
	vmstate->setRegisterValueByName(register_name, regval);

}


void  decrement_register (
		class VirtualMachineState *vmstate , 
		std::string register_name )
{
	uint8_t regval = vmstate->getRegisterValueByName(register_name);
	regval--;
	vmstate->setRegisterValueByName(register_name, regval);
}


// Stack {
void  push_register (
		class VirtualMachineState *vmstate ,
		std::string register_name ) 
{
	static const uint8_t stack_page = MEMPAGE_STACK;
	
	uint8_t pushed_reg = vmstate->getRegisterValueByName (register_name);
	uint8_t reg_s = vmstate->getRegisterValueByName ("s"); 
	
	uint8_t *ptr_stktop = vmstate->accessMemoryAt (stack_page, reg_s);
	(*ptr_stktop) = pushed_reg;
	vmstate->setRegisterValueByName("s", reg_s + 1);
}


void  pop_register(
		class VirtualMachineState *vmstate ,
		std::string register_name )
{
	static const uint8_t stack_page = MEMPAGE_STACK;
	
	uint8_t reg_s = vmstate->getRegisterValueByName("s");
	reg_s--;
	uint8_t *ptr_stktop = vmstate->accessMemoryAt (stack_page, reg_s);
	
	uint8_t popped_reg = *ptr_stktop;
	vmstate->setRegisterValueByName(register_name, *ptr_stktop);
	vmstate->setRegisterValueByName("s", reg_s);
}
// } endof Stack


// ALU {

void  add_with_carry (class VirtualMachineState *vmstate)
{
	uint8_t reg_a = vmstate->getRegisterValueByName("a");
	uint8_t reg_b = vmstate->getRegisterValueByName("b");
	reg_a = reg_a + reg_b;

	vmstate->setRegisterValueByName("a", reg_a);

}
void  subtract_with_carry (class VirtualMachineState *vmstate)
{
	uint8_t reg_a = vmstate->getRegisterValueByName("a");
	uint8_t reg_b = vmstate->getRegisterValueByName("b");
	reg_a = reg_a - reg_b;

	vmstate->setRegisterValueByName("a", reg_a);

}
void  xor_bitwise (class VirtualMachineState *vmstate)
{
	uint8_t reg_a = vmstate->getRegisterValueByName("a");
	uint8_t reg_b = vmstate->getRegisterValueByName("b");
	reg_a = reg_a ^ reg_b;

	vmstate->setRegisterValueByName("a", reg_a);
}
void  or_bitwise (class VirtualMachineState *vmstate)
{
	uint8_t reg_a = vmstate->getRegisterValueByName("a");
	uint8_t reg_b = vmstate->getRegisterValueByName("b");
	reg_a = reg_a | reg_b;

	vmstate->setRegisterValueByName("a", reg_a);
}
void  and_bitwise (class VirtualMachineState *vmstate)
{
	uint8_t reg_a = vmstate->getRegisterValueByName("a");
	uint8_t reg_b = vmstate->getRegisterValueByName("b");
	reg_a = reg_a & reg_b;

	vmstate->setRegisterValueByName("a", reg_a);
}
void  not_bitwise (class VirtualMachineState *vmstate)
{
	uint8_t reg_a = vmstate->getRegisterValueByName("a");
	reg_a = ~reg_a;

	vmstate->setRegisterValueByName("a", reg_a);
	
}


void  logical_shift_left (class VirtualMachineState *vmstate)
{
	uint8_t reg_a = vmstate->getRegisterValueByName("a");
	reg_a = reg_a << 1;

	vmstate->setRegisterValueByName("a", reg_a);
}
void  logical_shift_right (class VirtualMachineState *vmstate)
{
	uint8_t reg_a = vmstate->getRegisterValueByName("a");
	reg_a = reg_a >> 1;

	vmstate->setRegisterValueByName("a", reg_a);
}


// }



// { 
void  load_a_with_value (
		class VirtualMachineState *vmstate, 
		uint8_t value )
{
	vmstate->setRegisterValueByName("a", value);
}


void  load_a_from_memory (class VirtualMachineState *vmstate)
{
	uint8_t *memory_at_xy = vmstate->accessMemoryByXY();
	uint8_t value = *memory_at_xy;

	vmstate->setRegisterValueByName("a", value);
}


void  save_a_to_memory (class VirtualMachineState *vmstate)
{
	uint8_t *memory_at_xy = vmstate->accessMemoryByXY();
	uint8_t value = vmstate->getRegisterValueByName("a");

	*memory_at_xy = value;
}
// }


// Transfers {
void  transfer_a_to_register (
		class VirtualMachineState * vmstate, 
		std::string register_name )
{
	uint8_t reg_a = vmstate->getRegisterValueByName("a");
	vmstate->setRegisterValueByName(register_name, reg_a);
}


void  transfer_register_to_a (
		class VirtualMachineState * vmstate, 
		std::string register_name )
{
	uint8_t regval = vmstate->getRegisterValueByName(register_name);
	vmstate->setRegisterValueByName("a", regval);
}
// }

// Conditions
void is_zero (class VirtualMachineState *vmstate)
{
	if ( vmstate->getRegisterValueByName("a") == 0 ) {
		vmstate->setRegisterValueByName("f", 1);
	} else {
		vmstate->setRegisterValueByName("f", 0);
	}
}
void is_a_greater_than_b (class VirtualMachineState *vmstate)
{
	if ( vmstate->getRegisterValueByName("a") > vmstate->getRegisterValueByName("b") ) {
		vmstate->setRegisterValueByName("f", 1);
	} else {
		vmstate->setRegisterValueByName("f", 0);
	}
}

// Jumps
void jump_uncoditional (class VirtualMachineState *vmstate)
{
	vmstate->setRegisterValueByName("p", vmstate->getRegisterValueByName("x") );
	vmstate->setRegisterValueByName("c", vmstate->getRegisterValueByName("y") );
}
void jump_if(class VirtualMachineState *vmstate)
{
	if( vmstate->getRegisterValueByName("f") == 1 ) {
		jump_uncoditional(vmstate);
	}
}
void jump_if_not(class VirtualMachineState *vmstate)
{
	if( vmstate->getRegisterValueByName("f") == 0 ) {
		jump_uncoditional(vmstate);
	}
}
























