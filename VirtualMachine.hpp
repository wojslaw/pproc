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



#include "Instructions.hpp"
#include "VirtualMachineState.hpp"


//typedef void Operation(struct VirtualMachineState *);
//typedef Operation (*OperationPtr);





class VirtualMachine {
private:
	struct VirtualMachineState state;
	// struct InstructionSet instrset;

	void evaluateLoadedOperation(void);
	void incrementPC(void);
public:
	VirtualMachineState* getPointerToState(void);

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

