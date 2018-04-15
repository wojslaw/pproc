#include "Execution_Interpreter.hpp"

Interpreter::Interpreter(VirtualMachine *virtual_machine_ptr)
{
	vm = virtual_machine_ptr;
}



void Interpreter::interpretInstruction(std::string instruction, std::string operand)
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
	} else if(operand.size()== 4 && operand.at(0) == '0' && operand.at(1) == 'x') {
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
	std::cout << "\nCouldn't interpret: `" << instruction << "`";
}


void Interpreter::interpretGivenString_parens(std::string input_string)
{
	history_vector.emplace_back(input_string);
	
	enum Readmodes{ noread, read_inst, read_oper };

	std::string instruction;
	std::string operand;
	int current_readmode = noread;


	for ( char& c : input_string ) {
		if ( c == '(' ) {
			if ( current_readmode == noread ) { 
				current_readmode = read_inst; 
			} else {
				std::cout << "\nError: unexpected `(` parenthesis while reading input. " 
					<<" (results so far: instruction=`" << instruction
					<< "`, operand=`" << operand
					<< "`) I force-stop reading.";
				return;
			}
		} else if ( c == ')' ) {
			if( 
					current_readmode == read_inst 
					|| 
					current_readmode == read_oper ) {
				interpretInstruction(instruction, operand);
			} else {
				std::cout << "\nWarning: unexpected `)` closing parenthesis while not in reading mode. I'm ignoring it.";
			}
		} else if( (c == ' ') && (current_readmode == read_inst) ) { 
			current_readmode = read_oper; 
		} else if (current_readmode == read_inst) {
			instruction.push_back(c);
		} else if (current_readmode == read_oper) {
			instruction.push_back(c);
		}
	}
}
/*
	if( input_string.front() != '(' || input_string.back() != ')' ) {
		std::cout << "\nTried to interpret unsupported string(not parentheses-enclosed.)";
		return;
	} else {
		std::string instruction;
		std::string operand;
		int i;
		for( i = 1; input_string.at(i) != ')'; i++) {
			instruction.push_back ( input_string.at(i) );
			
			operand.push_back ( input_string.at(i) );
		}
		
		interpretInstruction(instruction, operand);
	}
*/

