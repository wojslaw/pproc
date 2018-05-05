#include "VirtualMachineState.hpp"

Register::Register(
		std::string regcode , 
		uint8_t regnumcode,
		std::string regname , 
		std::string regdescription ) 
{
	codename = regcode;
	numeric_code = regnumcode; 
	description = regdescription;
	name = regname;
	numeric_code = regnumcode;
	value = 0;
}



void VirtualMachineState::addAdrReg(
		std::string code, 
		uint8_t numeric_code,
		std::string name, 
		std::string description) /// Adresable register
{
	vector_registers_adresable.emplace_back( Register(
			code,
			numeric_code,
			name,
			description	));
}

VirtualMachineState::VirtualMachineState()
{
	std::cout << "Called construction";
	vector_registers_adresable = std::vector<struct Register>();
	vector_registers_adresable.reserve(10);
	//vector_registers_adresable.resize(10);

	
	
	addAdrReg(
			"a", 
			0x00,
			"acumulator", 
			"main acumulator, where results of ALU operations are saved by default");
	
	addAdrReg(
			"b", 
			0x01,
			"b-acumulator", 
			"secondary acumulator,  default");
	
	addAdrReg(
			"s",
			0x02,
			"stack-pointer", 
			"holds the pointer to top of stack");
	
	addAdrReg(
			"f", 
			0x03,
			"flag-register", 
			"stores various 1-bit information");


	addAdrReg(
			"x", 
			0x04,
			"index-page", 
			"used for jumps and memory write/load, as a pair with y");

	addAdrReg(
			"y", 
			0x05,
			"index-cell", 
			"used for jumps and memory write/load, as a pair with x");

	addAdrReg(
			"p",
			0x06,
			"program-page",
			"the memory page from which the machine is reading currently");

	addAdrReg(
			"c",
			0x07,
			"program-cell",
			"the memory cell from which the machine is reading currently");


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


Register* VirtualMachineState::accessRegisterByName(std::string regnam)
{
	for( int i = 0; i < vector_registers_adresable.size(); i++ ) {
		//std::cout << "\n" << regnam << " vs " << vector_registers_adresable.at(i).codename;
		if( regnam == vector_registers_adresable.at(i).codename ) {
			//std::cout << vector_registers_adresable.at(i).name;
			//std::cout << "FOUND MATCH at \n";
			printf("%p  %x", &vector_registers_adresable.at(i), vector_registers_adresable.at(i).value);
			
			return &vector_registers_adresable.at(i);
		}
	}
	fprintf(stderr, "Warning: Tried to access a nonexistent register '%s' \n", regnam.c_str());
	//printf("Warning: Tried to access a nonexistent register '%s' \n", regnam.c_str());
	return 0;
}


void VirtualMachineState::setRegisterValueByName(std::string regnam, uint8_t value)
{
	auto reg = accessRegisterByName(regnam);
	if(reg == nullptr) {
		fprintf(stderr, "Error: Couldn't set register '%s' to 0x%0x", regnam.c_str(), value);
		return;
	}

	reg->value = value;
}

uint8_t VirtualMachineState::getRegisterValueByName(std::string regnam)
{
	auto reg = accessRegisterByName(regnam);
	if(reg == nullptr) {
		fprintf(stderr, "Error: Couldn't get value of register '%s'", regnam.c_str() );
		return -1;
	}
	return reg->value;
}


void VirtualMachineState::printRegistersDescription()
{
	putchar('\n');
	for( auto reg : vector_registers_adresable ) {
		std::cout << reg.codename;
		printf("(0x%0x):", reg.numeric_code);
		std::cout << reg.name;
		std::cout << ": " << reg.description << "\n";
	}
}

void VirtualMachineState::setRegisterByName(char regnam, uint8_t value)
{
	std::string rname;
	rname.at(0) = regnam;
	setRegisterValueByName(rname, value);
	return;


	register_map.at(regnam) = value;
}


uint8_t VirtualMachineState::getRegisterByName(char regnam)
{
	std::string rname;
	rname.at(0) = regnam;
	return getRegisterValueByName(rname);

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



///
/// I hope to remove the following:
///

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
