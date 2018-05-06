#pragma once

#include <cstdint>
#include <cstdio>

#include <map>
using std::map;
#include <string>
using std::string;
#include <iostream>
using std::cout;
#include <bitset>
using std::bitset;



#include "InstructionSet.hpp"
#include "VirtualMachineState.hpp"







class VirtualMachine {
public:
	struct VirtualMachineState state;
	struct InstructionSet isa;

	Instruction findInstructionByMnemonic(std::string);
	void evaluateLoadedOperation(void);
	void incrementPC(void);
	
	
	
	
	std::string label;
	VirtualMachine();
	~VirtualMachine();

	VirtualMachineState* getPointerToState(void);


	void printRegisters(void);
	void printOperationRegisters(void);
	void printMemory(
			uint8_t page ,
			uint8_t start_cell ,
			uint8_t cellcount );

	

	void setRegisterByName(char, uint8_t);
	uint8_t getRegisterByName(char);

	uint8_t* accessMemoryAt ( 
			uint8_t page, 
			uint8_t cell );
	uint8_t* accessMemoryByXY(void);
	uint8_t* accessMemoryByPC(void);


	void loadBytesIntoMemory(std::vector<uint8_t> vector_of_bytes, uint8_t startpage, uint8_t startcell);

	void loadInstructionAtPC(void);
	void executeCurrentlyLoadedInstruction(void);
	void doMachineCycle(void);
};




