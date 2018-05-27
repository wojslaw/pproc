#include "CPUState.hpp"

CPUState::CPUState()
{
	setRegisterDescription(0x00, "aa", "acumulator", "Accumulates and does arithmetic and logic and stuff!!!");
	setRegisterDescription(0x01, "ba", "b-acumulator", "Secondary accumulator, used in some ALU functions");
	setRegisterDescription(0x02, "ip", "instruction-page", "Memory page from which the instruction is being read");
	setRegisterDescription(0x03, "ic", "instruction-page", "Memory page from which the instruction is being read");
	setRegisterDescription(0x04, "sp", "stack-pointer", "Pointer to the top of processor's stack");
	setRegisterDescription(0x05, "fl", "flags", "Various values that are read during operation");
	setRegisterDescription(0x06, "pp", "pointer-page", "Page-pointer register");
	setRegisterDescription(0x07, "pc", "pointer-cell", "Cell-pointer");
}

CPUState::~CPUState()
{

}


void CPUState::setRegisterDescription (
		uint8_t register_bytecode ,
		std::string register_symbol ,
		std::string register_fullname ,
		std::string register_description )
{
	array_of_adresable_registers_descriptions.at(register_bytecode) = 
		{ register_symbol, 
		  register_fullname, 
		  register_description };
}





void CPUState::incrementRegister(uint8_t register_bytecode)
{
	++(registers_adresable.at(register_bytecode));
}
void CPUState::decrementRegister(uint8_t register_bytecode)
{
	--(registers_adresable.at(register_bytecode));
}

void CPUState::incrementPairOfRegisters(
		uint8_t register_bytecode_primary ,
		uint8_t register_bytecode_secondary )
{
	incrementRegister(register_bytecode_primary);

	if(registers_adresable.at(register_bytecode_primary) == 0 ) { incrementRegister(register_bytecode_secondary); }
}


uint8_t CPUState::getRegisterBytecodeBySymbol(std::string register_symbol)
{
	for ( uint8_t i = 0; i < array_of_adresable_registers_descriptions.size() ; ++i) {
		if(	array_of_adresable_registers_descriptions.at(i).symbol == register_symbol) {
			return i;
		}
	}
	
	throw std::domain_error("Couldn't return registerbytecode, because the given symbol doesn't correspond to any existent register.");
	return -1;
}


std::string CPUState::getRegisterSymbolByBytecode(uint8_t register_bytecode)
{
	return array_of_adresable_registers_descriptions.at(register_bytecode).symbol;
}


void CPUState::printFetchedInstruction()
{
	printf("( 0x%02x", registers_instruction.at(0));
	for (int i = 1; i < registers_instruction.size(); ++i ) {
		printf( " 0x%02x ", registers_instruction.at(i) );
	}

	printf(")");
}


void CPUState::printAdresableRegisters()
{
	putchar('\n');
	for(int i = 0; i < registers_adresable.size(); ++i) {
		printf("  '%s'(0x%02x) = 0x%02x   :   ", 
				array_of_adresable_registers_descriptions.at(i).symbol.c_str(), 
				i ,
				(uint8_t) registers_adresable.at(i) 
				);
		std::cout << "b_" << (std::bitset<8>) registers_adresable.at(i) << "\n";
	}
}


void CPUState::printAdresableRegistersDescription()
{
	printf("\nAdresable registers:\n");
	int i = 0;
	for( auto register_description : array_of_adresable_registers_descriptions ) {
		printf(" 0x%02x `%s`: %s - %s \n", i, 
				register_description.symbol.c_str() ,
				register_description.fullname.c_str() , 
				register_description.description.c_str()
				);
		++i;
	}
}





void CPUState::setBitOfRegister(uint8_t register_code, uint8_t bit_number, bool bit_value)
{
	if(bit_number > 8) {
		throw std::out_of_range("Trying to access a bit of register that's greater than 0x07.");
	}

	std::bitset<8> as_bits = registers_adresable.at(register_code);
	as_bits[bit_number] = bit_value;

	registers_adresable.at(register_code) = (uint8_t) (as_bits.to_ulong());
}


bool CPUState::getBitOfRegister(uint8_t register_code, uint8_t bit_number)
{
	if(bit_number > 8) {
		throw std::out_of_range("Trying to access a bit of register that's greater than 0x07.");
	}

	return ((std::bitset<8>) registers_adresable.at(register_code))[bit_number];
}





void CPUState::setValueOfFlag(uint8_t flagnumber, bool value)
{
	setBitOfRegister(regcode_flags, flagnumber, value);
}


bool CPUState::getValueOfFlag(uint8_t flagnumber)
{
	getBitOfRegister(regcode_flags, flagnumber);
}




void CPUState::printMemory(
		uint8_t page, 
		uint8_t cell,
		uint8_t number_of_cells )
{
	std::cout << "\n";
	for( int i = 0; i < number_of_cells; ++i) {
		printf( "@0x%02x%02x : 0x%02x\n", 
				page ,
				cell ,
				memory.at( 0x100*page + cell ) );
		
		++cell;
		if( cell == 0) { ++page; }
	}
}


void CPUState::loadVectorOfBytesToMemory(
		uint8_t page , 
		uint8_t cell , 
		std::vector<uint8_t> vector_of_bytes )
{
	for( uint8_t current_byte : vector_of_bytes) {
		memory.at( 0x100*page + cell ) = current_byte;
		
		++cell;
		if( cell == 0) { ++page; }
	}
}


void CPUState::loadCurrentInstructionToPosition(uint8_t pos)
{

	registers_instruction.at(pos) = memory[
			0x100 * registers_adresable[regcode_p] 
			+ registers_adresable[regcode_c] ];
}

void CPUState::fetchTwoByteInstruction(void)
{
	loadCurrentInstructionToPosition(0);
	incrementPairOfRegisters(regcode_c, regcode_p);
	loadCurrentInstructionToPosition(1);
	incrementPairOfRegisters(regcode_c, regcode_p);
}

	

uint8_t CPUState::getMemoryValueAt(uint8_t page, uint8_t cell)
{
	return memory.at(0x100*page + cell);
}

void CPUState::setMemoryValueAt(uint8_t page, uint8_t cell, uint8_t value)
{
	memory.at(0x100*page + cell) = value;
}


void CPUState::loadSequenceOfBytesIntoMemory(
		std::vector<uint8_t> vector_of_bytes
		, uint8_t startpage 
		, uint8_t startcell 
) {
	uint8_t page = startpage;
	uint8_t cell = startcell;
	for( auto current_byte : vector_of_bytes ) {
		setMemoryValueAt(page, cell, current_byte);
		
		cell++;
		if(cell == 0) { 
			++page; 
		}
	}
}








