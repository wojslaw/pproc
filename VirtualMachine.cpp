#include "VirtualMachine.h"

VirtualMachineState::VirtualMachineState()
{
	uint8_t initial_register_value = 0;
	std::string register_names = REGISTER_NAMES_STRING;

	for(char regnam : register_names) {
		register_map[regnam] = initial_register_value;
	}

}


VirtualMachineState::~VirtualMachineState()
{
	// dtor
}


void VirtualMachine::printRegisters(void)
{	
	printf("\nRegisters:");
	for(char regname : REGISTER_NAMES_STRING) {
		uint8_t value = state.register_map.at(regname);
		printf("\n %c = $%02x    b_", regname, value);
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



// legacy:
/*
void print_registers(const struct CpuRegisters  *state)
{
	printf("\nA = $%02x", state->reg_a);
	printf("\nB = $%02x", state->reg_b);
	printf("\nF = $%02x", state->reg_f);
	printf("\nS = $%02x", state->reg_s);
	printf("\nX = $%02x", state->reg_x);
	printf("\nY = $%02x", state->reg_y);
	printf("\nP = $%02x", state->reg_p);
	printf("\nC = $%02x", state->reg_c);
}

void print_memory(const int8_t *memzero, const uint16_t first)
{
	for(uint16_t i = 0; i < 8; i++) {
		printf("\n$(%04x) =  $%02x", (first+i), *(memzero+first+i) );
	}
} */

