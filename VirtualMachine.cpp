#include "VirtualMachine.hpp"


VirtualMachine::VirtualMachine()
{
	//ctor
}
VirtualMachine::~VirtualMachine()
{

}
VirtualMachineState* VirtualMachine::getPointerToState()
{
	return &(state);
}


void VirtualMachine::incrementPC()
{
	uint8_t reg_p = state.getRegisterValueByName("p");
	uint8_t reg_c = state.getRegisterValueByName("c");
	
	reg_c++;
	if(reg_c == 0) { reg_p++; }
	

	state.setRegisterValueByName("p", reg_p);
	state.setRegisterValueByName("c", reg_c);
}


Instruction VirtualMachine::findInstructionByMnemonic(std::string mnemonic)
{
	for( auto ins : isa.instructions_vector ) {
		if(ins.mnemonic == mnemonic ) {
			return ins;
		}
	}
	std::cout << "\nCouldn't find any instruction matching mnemonic `" << mnemonic << "`";
	return Instruction();
}


void VirtualMachine::printMemory(
		uint8_t page ,
		uint8_t start_cell ,
		uint8_t cellcount 
) {
	for(uint8_t i = 0; i < cellcount; i++) {
		uint8_t curcell = start_cell+i;
		uint8_t value = *accessMemoryAt(page, curcell);
		printf("\n @$%02x%02x: $%02x   b_", page, curcell, value );
		cout << bitset<8>(value);
	}
}




uint8_t* VirtualMachine::accessMemoryAt (
		uint8_t page ,
		uint8_t cell )
{
	return &(state.mem[page][cell]);
}


uint8_t* VirtualMachine::accessMemoryByXY (void) 
{
	uint8_t page = state.getRegisterValueByName("x");
	uint8_t cell = state.getRegisterValueByName("y");
	return accessMemoryAt(page, cell);
}


uint8_t* VirtualMachine::accessMemoryByPC(void)
{
	uint8_t page = state.getRegisterValueByName("p");
	uint8_t cell = state.getRegisterValueByName("c");
	return accessMemoryAt(page, cell);
}


void VirtualMachine::loadBytesIntoMemory(std::vector<uint8_t> vector_of_bytes, uint8_t startpage, uint8_t startcell)
{
	state.setRegisterValueByName("p", startpage);
	state.setRegisterValueByName("c", startcell);
	for(uint8_t current_byte : vector_of_bytes ) {
		*accessMemoryByPC() = current_byte;
		incrementPC();
	}
}


void VirtualMachine::doMachineCycle(void)
{
	std::cout << "\nMACHINE CYCLE UNIMPLEMENTED!!!!!";
	incrementPC();
	incrementPC();
}































/*
void VirtualMachine::setRegisterByName(char regnam, uint8_t value)
{
	state.register_map.at(regnam) = value;
}


uint8_t VirtualMachine::getRegisterByName(char regnam)
{
	return state.register_map.at(regnam);
}
*/

/*void VirtualMachine::printOperationRegisters(void)
{
	uint8_t reg_p = state.register_map.at('p');
	uint8_t reg_c = state.register_map.at('c');
	uint8_t instruction = state.internal_register_map.at('i');
	uint8_t operand = state.internal_register_map.at('o');

	printf("\n oper at $%02x%02x: $%02x %02x ", 
				state.simulator_lastread_p , 
				state.simulator_lastread_c , 
				instruction ,
				operand );
}*/
/*void VirtualMachine::printRegisters(void)
{
	printf("\nRegisters:");
	for(char regname : REGISTER_NAMES_STRING) {
		uint8_t value = state.register_map.at(regname);
		printf("\n %c = $%02x  (%c)    b_", regname, value, value);
		cout << bitset<8>(value); 
	}
}*/

/*void VirtualMachine::evaluateLoadedOperation()
{
	const uint8_t instruction_code = state.internal_register_map.at('i');
	const uint8_t operand_code = state.internal_register_map.at('o');
	printf("\n Warning: virtual machine has called evaluateLoadedOperation(%02x %02x). Evaluation isn't implemented!.", instruction_code, operand_code);
	// TODO
}*/
