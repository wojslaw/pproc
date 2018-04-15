#include "Execution_Interpreter.hpp"

Interpreter::Interpreter(VirtualMachine *virtual_machine_ptr)
{
	vm = virtual_machine_ptr;
}



void Interpreter::interpretInstruction(string instruction, string operand)
{
	const int adrt_implied = Instruction::InstructionAdrestype::implied;
	const int adrt_reg = Instruction::InstructionAdrestype::reg;
	const int adrt_value = Instruction::InstructionAdrestype::value;
	
	uint8_t val = 0 ;
	
	Instruction ins = vm->findInstructionByMnemonic(instruction);
	if( ins.adrestype == -1 ) {
		std::cout << "\nReceived invalid function. Maybe mnemonic isn't matching?";
	}
	int adresing_type;
	// 1. find out required adresing type:
	if(operand.size() == 0) {
		adresing_type = adrt_implied;
	} else if(operand.size() == 1) {
		adresing_type = adrt_reg;
	} else if(operand.size() > 2 && operand.at(0) == '0' && operand.at(1) == 'x') {
		adresing_type = adrt_value;
		val = std::stoi(operand, 0, 16);
	} else {
		adresing_type = -1;
		std::cout << "\nInterpreter couldn't match any adrestype for operand: `" << operand << "`";
		return;
	}

	// 2. Do it!
	if(ins.adrestype != adresing_type) {
		std::cout << "\nUnmatching adrestype! (" << ins.adrestype << "vs" << adresing_type << ")";
	} else {
		switch (adresing_type) {
			case adrt_implied: 
				(*ins.opptr.impliedAdres) (vm->getPointerToState());
				return;
			case adrt_reg:
				(*ins.opptr.registerAdres) (vm->getPointerToState(), operand.at(0) );
				return;
			case adrt_value:
				(*ins.opptr.valueAdres) ( vm->getPointerToState(), val );
				return;
			default :
				std::cout << "\nWrong adrestype???";
		}
	}

	


	std::cout << "\nNo match for `" << instruction << "`";



	//std::cout <<" \n\n" << operand.size() << "\n\n";
	// 1. If operand is empty, then adresing is implied
	/*if( operand.empty() ) {
		for( auto fun : functionvector ) {
			if( fun.mnemonic == instruction ) {
				(*fun.instptr.implied) (vmstate);
				return;
			}
		}
	} else if ( operand.size() > 1 && operand.at(0) == '0' && operand.at(1) == 'x' ) {
		for( auto fun : functionvector ) {
			if(fun.mnemonic == instruction) {
				(*fun.instptr.value) (vmstate, stoi(operand) );
				return;
			}
		}
	} else if (operand.size() == 1 ) {
		for( auto fun : functionvector ) {
			if(fun.mnemonic == instruction) {
				(*fun.instptr.reg) (vmstate, operand.at(0) );
				return;
			}
		}
	}*/




	std::cout << "\nCouldn't interpret: `" << instruction << "`";
}


/*
void Interpreter::addFunction_implied( 
		std::string fullname ,
		instructionptr_impliedOperand insptr)
{	
	interpreter_function new_fun;
	new_fun.instptr.implied = insptr;
	new_fun.adrestype = interpreter_function::InstructionAdrestype::implied;
	new_fun.fullname = fullname;
	new_fun.mnemonic = GLOBAL_INSTRUCTION_DESCRIPTION_MAP.at(fullname);
	
	functionvector.push_back(new_fun);

}
void Interpreter::addFunction_register(
		std::string fullname ,
		instructionptr_register insptr)
{	
	interpreter_function new_fun;
	new_fun.instptr.reg = insptr;
	new_fun.adrestype = interpreter_function::InstructionAdrestype::reg;
	new_fun.fullname = fullname;
	new_fun.mnemonic = GLOBAL_INSTRUCTION_DESCRIPTION_MAP.at(fullname);
	
	functionvector.push_back(new_fun);

} 
void Interpreter::addFunction_value(	
		std::string fullname, 
		instructionptr_value insptr)
{
	interpreter_function new_fun;
	new_fun.instptr.value = insptr;
	new_fun.adrestype = interpreter_function::InstructionAdrestype::value;
	new_fun.fullname = fullname;
	new_fun.mnemonic = GLOBAL_INSTRUCTION_DESCRIPTION_MAP.at(fullname);
	
	functionvector.push_back(new_fun);
} */


/*
Interpreter::Interpreter(VirtualMachine *virtualmachineptr)
{
	vm = virtualmachineptr;
	
	
	addFunction_implied( "no-operation", &no_operation );
	addFunction_implied( "add-with-carry", &add_with_carry   );
	addFunction_implied( "subtract-with-carry", &subtract_with_carry ); 
	addFunction_implied( "xor-bitwise", &xor_bitwise ); 
	addFunction_implied( "or-bitwise", &or_bitwise ); 
	addFunction_implied( "and-bitwise", &and_bitwise ); 
	addFunction_implied( "not-bitwise", &not_bitwise ); 
	//addFunction_implied( "rotate-left", &rotate_left ); 
	//addFunction_implied( "rotate-right", &rotate_right );
	addFunction_implied( "logical-shift-left", &logical_shift_left );
	addFunction_implied( "logical-shift-right", &logical_shift_right );
	addFunction_implied( "load-a-from-memory", &load_a_from_memory  );
	addFunction_implied( "save-a-to-memory", &save_a_to_memory  );


	addFunction_value( "load-a-with-value", &load_a_with_value );
	
	
	addFunction_register("transfer-a-to-register" , &transfer_a_to_register    );
	addFunction_register( "transfer-register-to-a" , &transfer_register_to_a    );
	addFunction_register( "push-register", &push_register  );
	addFunction_register( "pop-register", &pop_register  );
	addFunction_register( "increment-register", &increment_register );
	addFunction_register( "decrement-register", &decrement_register ); 
	
}*/


/*void Interpreter::printInterpreterFunctions()
{
	std::cout << "\nFunctions loaded by interpreter:" << std::endl;
	std::cout << "\nadrestype(implied: " << interpreter_function::InstructionAdrestype::implied << ", register: " << interpreter_function::InstructionAdrestype::reg << ", ";
	std::cout << "\n|: mnemonic : fullname";
	std::cout << "\n|:  |  : .-----' ";
	std::cout << "\nv:  v  : v";
		
	std::cout << "\n\t\tIMPLIED:\n";
	printAllFunctionsOfAdresType(interpreter_function::InstructionAdrestype::implied);
		
	std::cout << "\n\t\tREGISTER:\n";
	printAllFunctionsOfAdresType(interpreter_function::InstructionAdrestype::reg);
	
	std::cout << "\n\t\tVALUE:\n";
	printAllFunctionsOfAdresType(interpreter_function::InstructionAdrestype::value);

} */


