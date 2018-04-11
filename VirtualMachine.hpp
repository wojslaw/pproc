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

#include "VirtualMachineState.hpp"


const std::string REGISTER_NAMES_STRING = "abfsxypc";
const std::string INTERNAL_REGISTER_NAMES_STRING = "io";

const uint16_t CPU_MEMORY_PAGES = 0xff;
const uint16_t CPU_MEMORY_CELLS_ON_PAGE = 0xff;


struct VirtualMachineState {
	uint8_t mem[CPU_MEMORY_PAGES][CPU_MEMORY_CELLS_ON_PAGE];

	map<char, uint8_t> internal_register_map;
	map<char, uint8_t> register_map;

	uint8_t simulator_lastread_p; // Updated on each clock cycle
	uint8_t simulator_lastread_c;

// methods - things for operating on the state
	void loadCurrentInstruction();
	void loadCurrentOperand();

	void setRegisterByName(char, uint8_t);
	uint8_t getRegisterByName(char);

	uint8_t* accessMemoryAt ( uint8_t page, uint8_t cell );
	uint8_t* accessMemoryByXY(void);
	uint8_t* accessMemoryByPC(void);
	
	VirtualMachineState();
	~VirtualMachineState();
};


typedef void Operation(struct VirtualMachineState *);
typedef Operation (*OperationPtr);
typedef void (*operation_ptr) (struct VirtualMachineState *);



struct Instruction {
	uint8_t opcode;
	std::string mnemonic;
	OperationPtr operation;
};


struct ISA {
	Instruction instruction[0xff];
};
struct ISA initializeInstructionSet();
void printInstructionSet();


class VirtualMachine {
private:
	struct VirtualMachineState state;
	struct ISA instruction_set;

	void evaluateLoadedOperation(void);
	void incrementPC(void);
public:
	void doMachineCycle(void);

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


};

void print_registers(const struct CpuRegisters *);
void print_memory(const uint8_t *, const uint16_t first); /** prints 8 memory cells starting from given point*/

