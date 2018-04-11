#include "VirtualMachineState.hpp"



VirtualMachineState::VirtualMachineState()
{
	uint8_t initial_register_value = 0;
	std::string register_names = REGISTER_NAMES_STRING;
	std::string internal_register_names = INTERNAL_REGISTER_NAMES_STRING;

	for(char regnam : register_names) {
		register_map[regnam] = initial_register_value;
	}
	
	for(char intregnam : internal_register_names) {
		internal_register_map[intregnam] = initial_register_value;
	}
}


VirtualMachineState::~VirtualMachineState()
{
	// dtor
}

uint8_t* VirtualMachineState::accessMemoryAt (
		uint8_t page ,
		uint8_t cell )
{
	return &(mem[page][cell]);
}


uint8_t* VirtualMachineState::accessMemoryByXY (void) 
{
	uint8_t page = getRegisterByName('x');
	uint8_t cell = getRegisterByName('y');
	return accessMemoryAt(page, cell);
}


uint8_t* VirtualMachineState::accessMemoryByPC(void)
{
	uint8_t page = getRegisterByName('p');
	uint8_t cell = getRegisterByName('c');
	return accessMemoryAt(page, cell);
}


void VirtualMachineState::setRegisterByName(char regnam, uint8_t value)
{
	register_map.at(regnam) = value;
}


uint8_t VirtualMachineState::getRegisterByName(char regnam)
{
	return register_map.at(regnam);
}


void VirtualMachineState::loadCurrentInstruction()
{
	uint8_t instruction = *accessMemoryByPC();
	internal_register_map.at('i') = instruction;
}


void VirtualMachineState::loadCurrentOperand()
{
	uint8_t instruction = *accessMemoryByPC();
	internal_register_map.at('o') = instruction;
}



