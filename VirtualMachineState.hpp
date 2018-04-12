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

