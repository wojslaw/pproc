#include "Execution_Interpreter.hpp"


void Interpreter::interpretInstruction(string instruction, string operand)
{
	//std::cout <<" \n\n" << operand.size() << "\n\n";
	// 1. If operand is empty, then adresing is implied
	if( operand.empty() ) {
		for( auto fun : functionvector ) {
			if( fun.mnemonic == instruction ) {
				(*fun.instptr.implied) (vmstate);
				return;
			}
		}
	} else if ( operand.size() > 1 ) {
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
	}




	std::cout << "\nCouldn't find any instruction to interpret: ` " << instruction << "`";
}



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
}



Interpreter::Interpreter(VirtualMachineState *st)
{
	vmstate = st;
	
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
	
}

void Interpreter::printFunction(interpreter_function fun)
{
	std::cout << fun.adrestype << ":`" << fun.mnemonic << "`:`" << fun.fullname << "`(@ " <<  fun.instptr.voidptr << ")\n" ;
}

void Interpreter::printAllFunctionsOfAdresType(int adtype)
{
	for (auto fun : functionvector ) {
		if ( fun.adrestype == adtype)  {
			printFunction(fun);
		}
			
	}
}

void Interpreter::printInterpreterFunctions()
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

}


