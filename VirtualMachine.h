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


const std::string REGISTER_NAMES_STRING = "abfsxypc";

const uint16_t CPU_MEMORY_PAGES = 0xff;
const uint16_t CPU_MEMORY_CELLS_ON_PAGE = 0xff;
struct CpuRegisters {
	uint8_t reg_a;
	uint8_t reg_b;

	uint8_t reg_f;
	uint8_t reg_s;

	uint8_t reg_x;
	uint8_t reg_y;

	uint8_t reg_p;
	uint8_t reg_c;
};

struct VirtualMachineState {
	struct CpuRegisters regs;
	uint8_t mem[CPU_MEMORY_PAGES][CPU_MEMORY_CELLS_ON_PAGE];


	map<char, uint8_t> register_map;

// methods

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

public:
	void printRegisters(void);

	void printMemory(
			uint8_t page ,
			uint8_t start_cell ,
			uint8_t cellcount );



	void setRegisterByName(char, uint8_t);
	uint8_t getRegisterByName(char);

	uint8_t* accessMemoryAt ( uint8_t page, uint8_t cell );
	uint8_t* accessMemoryByXY(void);
	uint8_t* accessMemoryByPC(void);


};

void print_registers(const struct CpuRegisters *);
void print_memory(const uint8_t *, const uint16_t first); /** prints 8 memory cells starting from given point*/

