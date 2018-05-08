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
	vector_registers_adresable = std::vector<struct Register>();
	vector_registers_adresable.reserve(0x08);
	
	vector_registers_instruction = std::vector<uint8_t>();
	vector_registers_instruction.reserve(CPU_NUMBER_OF_INSTRUCTION_REGISTERS);
	vector_registers_instruction.resize(CPU_NUMBER_OF_INSTRUCTION_REGISTERS);
	//vector_registers_instruction = std::vector<uint8_t>();
	
	
	addAdrReg(
			"a", 
			0x00,
			"acumulator", 
			"main acumulator, where results of ALU operations are saved by default");
	
	addAdrReg(
			"b", 
			0x01,
			"b-acumulator", 
			"secondary acumulator, by default it is used as the second parameter for binary operators(`xor`, `and`, `add`, etc.)");
	
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


	/*register_names = std::vector<std::string>();
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
	}*/

	//uint8_t initial_register_value = 0;
	//std::string register_names = REGISTER_NAMES_STRING;
	//std::string internal_register_names = INTERNAL_REGISTER_NAMES_STRING;



	// The following is legacy(hopefully):
	/*
	for(char regnam : register_names) {
		register_map[regnam] = initial_register_value;
	}
	
	for(char intregnam : internal_register_names) {
		internal_register_map[intregnam] = initial_register_value;
	}*/
	std::cout << "\n Created VirtualMachineState. ";
}


VirtualMachineState::~VirtualMachineState()
{
	std::cout << "\n Destroying VirtualMachineState";
	// dtor
}

uint8_t* VirtualMachineState::accessMemoryAt (
		uint8_t page ,
		uint8_t cell )
{
	return &(mem[page][cell]);
}

uint8_t VirtualMachineState::getMemoryValueAt(
		uint8_t page,
		uint8_t cell )
{
	return mem[page][cell];
}
void VirtualMachineState::setMemoryValueAt(
		uint8_t page,
		uint8_t cell, 
		uint8_t value)
{
	mem[page][cell] = value;
}



uint8_t* VirtualMachineState::accessMemoryByXY (void) 
{
	uint8_t page = getRegisterValueByName("x");
	uint8_t cell = getRegisterValueByName("y");
	return accessMemoryAt(page, cell);
}
uint8_t* VirtualMachineState::accessMemoryByPC(void)
{
	uint8_t page = getRegisterValueByName("p");
	uint8_t cell = getRegisterValueByName("c");
	return accessMemoryAt(page, cell);
}


Register* VirtualMachineState::accessRegisterByName(std::string regnam)
{
	for( int i = 0; i < vector_registers_adresable.size(); i++ ) {
		if( regnam == vector_registers_adresable.at(i).codename ) {
			return &vector_registers_adresable.at(i);
		}
	}
	fprintf(stderr, "Warning: Tried to access a nonexistent register '%s' \n", regnam.c_str());
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
		return 0;
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

	//register_map.at(regnam) = value;
}


uint8_t VirtualMachineState::getRegisterByName(char regnam)
{
	std::string rname;
	rname.at(0) = regnam;
	return getRegisterValueByName(rname);

	//return register_map.at(regnam);
}

void VirtualMachineState::incrementPC()
{
	uint8_t page = getRegisterValueByName("p");
	uint8_t cell = getRegisterValueByName("c");
	
	cell++;
	if(cell == 0) { 
		page++; 
	}
	
	setRegisterValueByName("p", page);
	setRegisterValueByName("c", cell);
	
}


void VirtualMachineState::incrementPC_times(int times)
{
	for(int i = 0; i < times; i++) {
		incrementPC();
	}
}

void VirtualMachineState::loadSequenceOfBytesIntoMemory(
		std::vector<uint8_t> vector_of_bytes
		, uint8_t startpage 
		, uint8_t startcell 
) {
	uint8_t page = startpage;
	uint8_t cell = startcell;
	for( auto current_byte : vector_of_bytes ) {
		printf("Loading 0x%02x to @0x%02x%02x", current_byte, page, cell);
		setMemoryValueAt(page, cell, current_byte);
		printf("   Now is 0x%02x \n", getMemoryValueAt(page, cell));
		
		cell++;
		if(cell == 0) { 
			++page; 
			printf("Swapped page, now at @0x%02x.%02x", page, cell);
		}
	}
}





void VirtualMachineState::printMemory(
		uint8_t startpage, 
		uint8_t startcell, 
		uint8_t number_of_cells)
{
	uint8_t page = startpage;
	uint8_t cell = startcell;

	for(uint8_t i = 0; i < number_of_cells; ++i) {
		printf(" @0x%02x%02x: 0x%02x", page, cell, *accessMemoryAt(page, cell) );
		cell++;
		if(cell == 0) { 
			++page; 
			printf("    Swapped page, now at @0x%02x.%02x", page, cell);
		}
		putchar('\n');
	}
	
}

void VirtualMachineState::printAdresableRegisters(void)
{
	printf("\nAdresable registers:\n");
	for( auto reg : vector_registers_adresable ) {
		printf(" reg `%s`(0x%02x)  = 0x%02x \n", 
				reg.codename.c_str(),
				reg.numeric_code,
				reg.value);
	}
}



void VirtualMachineState::fetchCurrentInstruction(void)
{
	uint8_t page = getRegisterValueByName("p");
	uint8_t cell = getRegisterValueByName("c");

	for(size_t i = 0; i < vector_registers_instruction.size(); ++i ) {
		vector_registers_instruction.at(i) = getMemoryValueAt(page, cell);

		++cell;
		if(cell == 0) {
			++page;
		}
	}
}


int VirtualMachineState::evaluateCurrentInstruction()
{
	//struct Instruction instruction = instruction_set->findInstructionByBytecode(vector_registers_instruction);	
	
	//instruction		


	return 2;
}


void VirtualMachineState::doMachineCycle(void)
{
	std::cout << "\ndoMachineCycle Not done yet";
	fetchCurrentInstruction();
	int bytes_forwards = evaluateCurrentInstruction();
	incrementPC_times(bytes_forwards);
}







/*void VirtualMachineState::loadCurrentInstruction()
{
	uint8_t instruction = *accessMemoryByPC();
	internal_register_map.at('i') = instruction;
}*/


/*void VirtualMachineState::loadCurrentOperand()
{
	uint8_t instruction = *accessMemoryByPC();
	//internal_register_map.at('o') = instruction;
}*/



///
/// I hope to remove the following:
///

/*AdresableRegister::AdresableRegister(std::string register_name)
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
}*/
/*void VirtualMachineState::printAdresableRegisters()
{
	printf("\n Adresable registers:");
	regarr.printRegisters();
}*/
