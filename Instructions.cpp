#include "Instructions.h"

void przejproc::no_operation(class VirtualMachine *vm)
{
	// do nothing xD
	return;
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
	vm->set_registerByName('s', reg_s + 1);


}


void przejproc::pop_register(
		class VirtualMachine *vm ,
		char register_name )
{
	static const uint8_t stack_page = MEMPAGE_STACK;
	
	const uint8_t reg_s = vm->getRegisterByName ('s');
	const uint8_t *ptr_stktop = vm->accessMemoryAt (stack_page, reg_s);
	
	uint8_t popped_reg = *ptr_stktop;
	vm->set_registerByName('s', reg_s - 1);
}
// } endof Stack


