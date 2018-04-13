#include "VirtualMachineState.hpp"

AdresableRegister::AdresableRegister(std::string register_name)
{
	name = register_name;
	value = 0;
}

AdresableRegister::AdresableRegister()
{
	value = 0;
}

Array_AdresableRegister::Array_AdresableRegister()
{
	regcount = 0;
}

	
std::string AdresableRegister::getName()
{
	return name;
}


void Array_AdresableRegister::addNewRegister(std::string regnam)
{
	if(regcount > 0xfe) { 
		std::cout<< "\nError: Trying to add a register '" << regnam << "', but array of registers is full!"; 
	} else {

		reg[regcount] = AdresableRegister(regnam);
		regcount++;	
	}
}


AdresableRegister* Array_AdresableRegister::findRegisterByName(const std::string regname)
{
	for(size_t i = 0; i < regcount; i++) {
		if( regname == reg[i].getName() ) { return &(reg[i]); }
	}

	return 0;
}


void Array_AdresableRegister::printRegisters()
{
	printf("\ncode | name\n");
	for(uint8_t i = 0; i < regcount; i++) {
		printf("$%02x  | ", i);
		std::cout << reg[i].getName() << std::endl;
	}
}


VirtualMachineState::VirtualMachineState()
{
	register_names = std::vector<std::string>();
	register_names.reserve(8);
	register_names.push_back("a");
	register_names.push_back("b");
	register_names.push_back("s");
	register_names.push_back("f");
	register_names.push_back("x");
	register_names.push_back("y");
	register_names.push_back("p");
	register_names.push_back("c");


	for(auto regnam : register_names) {
		regarr.addNewRegister(regnam);
	}

	uint8_t initial_register_value = 0;
	std::string register_names = REGISTER_NAMES_STRING;
	std::string internal_register_names = INTERNAL_REGISTER_NAMES_STRING;



	// The following is legacy(hopefully):

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


void VirtualMachineState::printAdresableRegisters()
{
	printf("\n Adresable registers:");
	regarr.printRegisters();
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



