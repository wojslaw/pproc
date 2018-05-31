#pragma once

#include <cstdint>
#include <cstdio>

#include <cstdint>

#include <functional>
#include <map>
using std::map;
#include <string>
using std::string;
#include <iostream>
using std::cout;
#include <bitset>
using std::bitset;

#include "CPUState.hpp"






struct WrappedInstruction {
	uint8_t bytecode;
	std::function<int (struct CPUState *, uint8_t, uint8_t)> instruction;
	std::string fullname;
	std::string mnemonic;
	uint8_t argcount;

	WrappedInstruction(
			uint8_t input_bytecode ,
			std::function<int (struct CPUState *, uint8_t, uint8_t)> input_instruction ,
			std::string input_mnemonic ,
			std::string input_fullname
			) 
	{
		bytecode    =  input_bytecode ;
		instruction =  input_instruction ;
		mnemonic    =  input_mnemonic ;
		fullname    =  input_fullname ;
	}

	WrappedInstruction(
			uint8_t input_bytecode ,
			std::string input_mnemonic ,
			std::string input_fullname ,
			std::function<int (struct CPUState *, uint8_t, uint8_t)> input_instruction ,
			uint8_t input_argcount
			) 
	{
		argcount	=  input_argcount;
		bytecode    =  input_bytecode ;
		instruction =  input_instruction ;
		mnemonic    =  input_mnemonic ;
		fullname    =  input_fullname ;
	}
};


class VirtualMachine {
public:
	struct CPUState cpu_state;
	
	std::vector<struct WrappedInstruction> vector_of_wrapped_instructions;
	
	void addBareInstruction ( std::function<int (struct CPUState *, uint8_t, uint8_t)> bare_instruction);
	void addWrappedInstruction (
			std::string input_mnemonic ,
			std::string input_fullname ,
			std::function<int (struct CPUState *, uint8_t , uint8_t)> input_instruction );

	void addWrappedInstruction (
			std::string input_mnemonic , uint8_t input_argcount ,
			std::string input_fullname ,
			std::function<int (struct CPUState *, uint8_t , uint8_t)> input_instruction 
			);


	struct WrappedInstruction getInstructionByMnemonic(std::string);
	uint8_t findInstructionByMnemonic(std::string mnemonic);

	uint8_t getInstructionBytecodeByMnemonic(std::string mnemonic);
	
	

	void createDefaultInstructionSet();
	void executeBytecodeInstruction(uint8_t instruction_bytecode, uint8_t operand0, uint8_t operand1);

	void printInstructionSet();



	void evaluateLoadedOperation(void);
	void incrementPC(void);
	
	
	
	
	std::string label;
	VirtualMachine();
	~VirtualMachine();



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




