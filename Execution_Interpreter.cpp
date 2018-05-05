#include "Execution_Interpreter.hpp"

Interpreter::Interpreter(VirtualMachine *virtual_machine_ptr)
{
	vm = virtual_machine_ptr;
	
	display_mode.memory_page = 0x01;
	display_mode.memory_startcell = 0x00;
	display_mode.memory_cellcount = 0x0b;
}



void Interpreter::interpretInstruction(std::string instruction, std::string operand)
{
	//const int adrt_implied = Instruction::InstructionAdrestype::implied;
	//const int adrt_reg = Instruction::InstructionAdrestype::reg;
	//const int adrt_value = Instruction::InstructionAdrestype::value;
	const int adrt_implied = InstructionAdrestype::implied;
	const int adrt_reg = InstructionAdrestype::reg;
	const int adrt_value = InstructionAdrestype::value;
	
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
				(*ins.op_ptr.impliedAdres) (vm->getPointerToState());
				return;
			case adrt_reg:
				(*ins.op_ptr.registerAdres) (vm->getPointerToState(), operand.at(0) );
				return;
			case adrt_value:
				(*ins.op_ptr.valueAdres) ( vm->getPointerToState(), val );
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

	std::string instruction = std::string();
	std::string operand = std::string();
	int current_readmode = noread;


	for ( char& c : input_string ) {
		if ( current_readmode == noread ) {
			if ( c == '(' ) { 
				current_readmode = read_inst; 
			}
		} else if( c== ')' ) {
			current_readmode = noread;
			interpretInstruction(instruction, operand);
			instruction.clear();
			operand.clear();
		} else {
			if( current_readmode == read_inst ) {
				if ( c == ' ') { 
					current_readmode = read_oper; 
				} else {
					instruction.push_back(c);
				}
			} else if( current_readmode == read_oper) {
					operand.push_back(c);
			}
		}
	}
}



void Interpreter::readEvalPrintLoop()
{
	std::string input_string = std::string();
	bool repl_working = true;

	std::cout << "\nWelcome to the przejproc interpreter REPL! Write commands to make the processor interpret them, or input empty line to finish.\n";

	while(repl_working) {
		std::getline(std::cin, input_string);
		if( input_string.size() == 0 ) {
			std::cout << "\nFinished working the REPL";
			repl_working = false;
			break;
		} else {
			interpretGivenString_parens(input_string);
			vm->printRegisters();
			vm->printMemory ( display_mode.memory_page, display_mode.memory_startcell, display_mode.memory_cellcount);
			std::cout << std::endl;
		}
	}

	std::cout << "\nWork finished. Printing history:";
	for( std::vector<std::string>::iterator it = history_vector.begin(); 
			it != history_vector.end(); 
			++it ) {
		std::cout << "\n" << *it ;
	}
}
