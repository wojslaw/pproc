#include "VirtualMachine.hpp"

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









void VirtualMachine::incrementPC()
{
	uint8_t reg_p = state.getRegisterByName('p');
	uint8_t reg_c = state.getRegisterByName('c');
	
	reg_c++;
	if(reg_c == 0) { reg_p++; }
	

	state.setRegisterByName('p', reg_p);
	state.setRegisterByName('c', reg_c);
}


void VirtualMachine::evaluateLoadedOperation()
{
	printf("\n virtual machine has called evaluateLoadedOperation().");
	// TODO
}


void VirtualMachine::doMachineCycle(void)
{
	state.simulator_lastread_p = state.register_map.at('p');
	state.simulator_lastread_c = state.register_map.at('c');

	state.loadCurrentInstruction();
	incrementPC();
	state.loadCurrentOperand();
	incrementPC();

	evaluateLoadedOperation();
}


void VirtualMachine::printRegisters(void)
{
	printf("\nRegisters:");
	for(char regname : REGISTER_NAMES_STRING) {
		uint8_t value = state.register_map.at(regname);
		printf("\n %c = $%02x  (%c)    b_", regname, value, value);
		cout << bitset<8>(value); 
	}
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


void VirtualMachine::printOperationRegisters(void)
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
}


uint8_t* VirtualMachine::accessMemoryAt (
		uint8_t page ,
		uint8_t cell )
{
	return &(state.mem[page][cell]);
}


uint8_t* VirtualMachine::accessMemoryByXY (void) 
{
	uint8_t page = getRegisterByName('x');
	uint8_t cell = getRegisterByName('y');
	return accessMemoryAt(page, cell);
}


uint8_t* VirtualMachine::accessMemoryByPC(void)
{
	uint8_t page = getRegisterByName('p');
	uint8_t cell = getRegisterByName('c');
	return accessMemoryAt(page, cell);
}


void VirtualMachine::setRegisterByName(char regnam, uint8_t value)
{
	state.register_map.at(regnam) = value;
}


uint8_t VirtualMachine::getRegisterByName(char regnam)
{
	return state.register_map.at(regnam);
}



