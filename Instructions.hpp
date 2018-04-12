#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "VirtualMachineState.hpp"
#include "InstructionSetImplementation.hpp"
//#include "VirtualMachine.hpp"


const uint8_t _MEMPAGE_STACK = 0x01;

typedef struct InstructionSet s_instructionset ;

typedef void operation (VirtualMachineState * vmstate);
typedef operation (*operation_ptr);

struct Instruction {
	uint8_t opcode;
	std::string mnemonic;
	std::string fullname;
	operation_ptr op_ptr;
};


struct InstructionSet {
	uint8_t number_of_instructions;
	std::vector<struct Instruction> ins_vector;
	struct Instruction invalid_instruction = { 0x00, "xxx", "invalid-instruction", nullptr};

	// ctor/init
	InstructionSet();
	// methods
	void printInstructionSet(void);
	void addInstructionToSet(std::string, std::string, operation_ptr);
	struct Instruction findInstructionByMnemonic(std::string);


	// operations:
	
};


// struct InstructionSet {
//	uint8_t number_of_operations;
//	Instruction operation_array[0xff];
//};

// struct ISA initializeInstructionSet();
// void printInstructionSet();


/*
namespace przejproc {
	
	void no_operation (class VirtualMachine*);

	// Increment/decrement will be commonly used on probably all registers, so I decided to just make a set of inc/dec operations for all registers
	void increment_register (class VirtualMachine *, char register_name);
	void decrement_register (class VirtualMachine *, char register_name);

// ALU:
	void add_with_carry (class VirtualMachine *);
	void subtract_with_carry (class VirtualMachine*);
	void xor_bitwise (class VirtualMachine*);
	void or_bitwise (class VirtualMachine*);
	void and_bitwise (class VirtualMachine*);
	void not_bitwise (class VirtualMachine*);
	void rotate_left (class VirtualMachine*);
	void rotate_right (class VirtualMachineState *);
	void logical_shift_left (class VirtualMachine*);
	void logical_shift_right (class VirtualMachine*);


// Loading registers
	// Save
	void load_a_with_value (class VirtualMachine *, uint8_t value);
	void load_a_from_memory (class VirtualMachine *);
	void save_a_to_memory (class VirtualMachine *);

	//void save_a_to_memory (class VirtualMachine *);
	//void save_b_to_memory (class VirtualMachine *);
	// load
	//void load_a_from_xy (class VirtualMachine *);
	//void load_a_with_constant (class VirtualMachine *);
	//void load_b_from_xy (class VirtualMachine *);
	//void load_b_with_constant (class VirtualMachine *);
	// problematic: void set_memory_address
	
// Transfer between reg_a
	void transfer_a_to_register (class VirtualMachine *, char register_name);
	void transfer_register_to_a (class VirtualMachine *, char register_name);

// Stack
	void push_register(class VirtualMachine*, char register_name);
	void pop_register(class VirtualMachine*, char register_name);

// Conditions
	void is_zero (class VirtualMachine);
	void is_a_greater_than_b (class VirtualMachine);
// Jumps
	void jump_uncoditional (class VirtualMachine *);
	void jump_if(class VirtualMachine *);
	void jump_if_not(class VirtualMachine *);



}; */
