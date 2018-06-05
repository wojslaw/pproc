#pragma once

#include <cstdint>


#include <bitset>
#include <iostream>
#include <stdexcept>

#include <array>
#include <string>
#include <vector>


static const size_t NUMBER_OF_REGISTERS_ADRESABLE= 0x100;

static const uint8_t regcode_a = 0x00;
static const uint8_t regcode_accumulator = 0x00;
static const uint8_t regcode_b = 0x01;
static const uint8_t regcode_s = 0x04;
static const uint8_t regcode_stackpointer = 0x04;
static const uint8_t regcode_f = 0x05;
static const uint8_t regcode_flags = 0x05;
static const uint8_t regcode_x = 0x06;
static const uint8_t regcode_index_page = 0x06;
static const uint8_t regcode_y = 0x07;
static const uint8_t regcode_index_cell = 0x06;
static const uint8_t regcode_p = 0x02;
static const uint8_t regcode_programcounter_page = 0x02;
static const uint8_t regcode_c = 0x03;
static const uint8_t regcode_programcounter_cell = 0x03;

static const uint8_t flagnumber_carry = 0x00;



struct RegisterDescription {
	std::string symbol;
	std::string fullname;
	std::string description;
};


struct CPUState {
	CPUState();
	~CPUState();


	std::array<uint8_t, NUMBER_OF_REGISTERS_ADRESABLE> registers_adresable;
	std::vector<uint8_t> registers_instruction;
	std::array<uint8_t, 0x100*0x100+1> memory;
	
	std::vector<struct RegisterDescription> array_of_adresable_registers_descriptions;


	uint8_t fetchInstructionAtProgramCounter(void);


	void setBitOfRegister(uint8_t register_code, uint8_t bit_number, bool bit_value);
	bool getBitOfRegister(uint8_t register_code, uint8_t bit_number);

	void printStack ();

	void setValueOfFlag (uint8_t flagnumber, bool value);
	bool getValueOfFlag (uint8_t flagnumber);

	void incrementProgramCounter (uint8_t);
	void printFetchedInstruction (const char * text);

	void loadSequenceOfBytesIntoMemory(
		std::vector<uint8_t> vector_of_bytes
		, uint8_t startpage 
		, uint8_t startcell);

	uint8_t stackPop();
	void    stackPush(uint8_t value);

	void setMemoryValueAt (uint8_t page, uint8_t cell, uint8_t value);
	uint8_t getMemoryValueAt (uint8_t page, uint8_t cell);
	uint8_t getMemoryValueAtProgramCounter (void);

	void setRegisterValue (uint8_t regcode, uint8_t value);
	uint8_t getRegisterValue (uint8_t regcode);

	void incrementRegister (uint8_t register_bytecode);
	void incrementRegister (uint8_t register_bytecode, uint8_t value);
	void decrementRegister (uint8_t register_bytecode);
	void decrementRegister (uint8_t register_bytecode, uint8_t value);


	void incrementPairOfRegisters(
		uint8_t register_bytecode_primary ,
		uint8_t register_bytecode_secondary );

	void setRegisterDescription (
			uint8_t register_bytecode ,
			std::string register_symbol ,
			std::string register_fullname ,
			std::string register_description );
	
	uint8_t getRegisterBytecodeBySymbol(std::string register_symbol);
	std::string getRegisterSymbolByBytecode(uint8_t register_bytecode);


	void printMemory(
			uint8_t page, 
			uint8_t cell ,
			uint8_t number_of_cells);

	void loadVectorOfBytesToMemory(
			uint8_t page , 
			uint8_t cell , 
			std::vector<uint8_t> vector_of_bytes );





	void printAdresableRegisters();
	void printAdresableRegistersDescription();




	void loadCurrentInstructionToPosition(uint8_t pos);
	//void fetchInstruction(void);



	std::string getRegisterNameByBytecode(uint8_t register_bytecode);
};
