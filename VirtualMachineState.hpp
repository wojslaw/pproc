#pragma once

#include <cstdint>
#include <cstdio>

#include <map>
#include <string>
#include <vector>

#include <iostream>
using std::cout;
#include <bitset>
using std::bitset;


const std::string REGISTER_NAMES_STRING = "abfsxypc";
const std::string INTERNAL_REGISTER_NAMES_STRING = "io";

const size_t CPU_MEMORY_PAGES = 0x100;
const size_t CPU_MEMORY_CELLS_ON_PAGE = 0x100;
const uint8_t CPU_NUMBER_OF_INSTRUCTION_REGISTERS = 3;


struct Register {
	std::string codename;
	uint8_t numeric_code;

	uint8_t value;

	std::string name;
	std::string description;

	Register( std::string regcode , 
			uint8_t regnumcode ,
			std::string regname , 
			std::string regdescription );
};


struct VirtualMachineState {
// State itself:
	uint8_t mem[CPU_MEMORY_PAGES][CPU_MEMORY_CELLS_ON_PAGE];
	//Array_AdresableRegister regarr;
	std::vector<struct Register> vector_registers_adresable;
	std::vector<uint8_t> vector_registers_instruction; // instruction registers are unnamed
// 
	std::vector<std::string> register_names;


	uint8_t simulator_lastread_p; // Updated on each clock cycle
	uint8_t simulator_lastread_c;
	

// ctors and dtors
	VirtualMachineState();
	~VirtualMachineState();

// simulator-specific(printing and stuff
	void printMemory(uint8_t startpage, uint8_t startcell, uint8_t number_of_cells);
	void printAdresableRegisters(void);
	void printRegistersDescription();

// methods for operating on the state
	void    setRegisterValueByName(std::string, uint8_t);
	uint8_t getRegisterValueByName(std::string);
	void    setRegisterValueByBytecode(uint8_t, uint8_t);
	uint8_t getRegisterValueByBytecode(uint8_t);

	//void loadCurrentInstruction();
	//void loadCurrentOperand();

	Register* accessRegisterByName(std::string regnam);
	void setRegisterByName(char, uint8_t);
	uint8_t getRegisterByName(char);
	void incrementPC();
	void incrementPC_times(int);

	uint8_t getMemoryValueAt(
		uint8_t page,
		uint8_t cell );
	void setMemoryValueAt(
		uint8_t page,
		uint8_t cell, 
		uint8_t value);
	uint8_t* accessMemoryAt  (uint8_t page, uint8_t cell );
	uint8_t* accessMemoryByXY(void);
	uint8_t* accessMemoryByPC(void);
	

// helper methods:
	void addAdrReg(
			std::string code,
			uint8_t numeric_code,
			std::string name, 
			std::string description); /// Adresable register

	
	void loadSequenceOfBytesIntoMemory(
		std::vector<uint8_t> vector_of_bytes
		, uint8_t startpage 
		, uint8_t startcell);


	void fetchCurrentInstruction(void);

	int evaluateCurrentInstruction();
	
	void doMachineCycle();
};




















/*struct AdresableRegister {
private:
	std::string name;
public:
	std::string getName();
	uint8_t value;
	AdresableRegister(std::string);
	AdresableRegister();
};

struct Array_AdresableRegister {
	struct AdresableRegister reg[0xff];
	size_t regcount;
	
	
	Array_AdresableRegister();
	// methods
	void addNewRegister(std::string regnam);
	void printRegisters();
	AdresableRegister* findRegisterByName(const std::string regname);
};*/
