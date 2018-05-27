#pragma once

#include <cstdlib>
#include <cstdint>

#include <cstdio>
#include <string>
#include <iostream>
#include <functional>

#include "typedefs.hpp"
#include "CPUState.hpp"








typedef void (cpu_instruction_template) (struct CPUState *state_ptr,  uint8_t operand0, uint8_t operand1);
typedef cpu_instruction_template (*cpu_instruction_pointer);


struct CPU_WrappedInstruction {
	uint8_t bytecode;
	cpu_instruction_pointer instruction_pointer;
	std::function<cpu_instruction_template> instruction;
	int adrestype;

	std::string mnemonic;
	std::string fullname;




	CPU_WrappedInstruction (
			uint8_t input_bytecode ,
			cpu_instruction_pointer input_instruction_pointer ,
			int input_adrestype ,
			std::string input_mnemonic ,
			std::string input_fullname
	) {
		instruction_pointer = input_instruction_pointer;
		bytecode            = input_bytecode;
		mnemonic            = input_mnemonic;
		fullname            = input_fullname;
		adrestype           = input_adrestype;
	}


	
	CPU_WrappedInstruction (
			uint8_t input_bytecode ,
			std::function<cpu_instruction_template> input_instruction ,
			int input_adrestype ,
			std::string input_mnemonic ,
			std::string input_fullname
	) {
		instruction = input_instruction;
		bytecode    = input_bytecode;
		mnemonic    = input_mnemonic;
		fullname    = input_fullname;
		adrestype   = input_adrestype;
	}


	~CPU_WrappedInstruction();
};




















typedef void (*operationPointer_impliedAdres) (class VirtualMachineState *);
typedef void (*operationPointer_registerAdres) (class VirtualMachineState *, std::string);
typedef void (*operationPointer_valueAdres) (class VirtualMachineState *, uint8_t);
//typedef void (*operationPointer_adresAdres) (class VirtualMachineState *, uint8_t, uint8_t);

struct AdrestypeDescription {
	int adrestype;
	std::string name;
	std::string description;
}; 

const struct AdrestypeDescription ADRESTYPE_DESCRIPTION_IMPLIED = { 
	adrestype_implied,
	"implied" ,
	"Doesn't accept parameters"
};
const struct AdrestypeDescription ADRESTYPE_DESCRIPTION_REG = {
	adrestype_register,
	"register" ,
	"1 paramname of adressable register(consult implementation documentation). Either character-string or a 1byte number(in bytecode)"
}; 
/*const struct AdrestypeDescription ADRESTYPE_DESCRIPTION_VALUE = {
	InstructionAdrestype::value,
	"value",
	"1 param: 1byte hexadecimal value(from 0x00 to 0xff)"
};
const struct AdrestypeDescription ADRESTYPE_DESCRIPTION_ADRES = {
	InstructionAdrestype::adres ,
	"adres" ,
	"2 params: 2x 1byte hexadecimal value(from 0x00 to 0xff)"
	};*/



















namespace cpu_instruction {

	static void no_operation (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{
		return;
	}





	static void increment_register(struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{
		state_ptr->registers_adresable.at(operand0) = 1 + state_ptr->registers_adresable.at(operand1);
	}
		

		
	static void decrement_register (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{
		state_ptr->registers_adresable.at(operand0) = -1 + state_ptr->registers_adresable.at(operand1);
	}

		



	// ALU
	static void add_alu (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{
		state_ptr->registers_adresable.at(regcode_a) = 
			state_ptr->registers_adresable.at(regcode_b) 
			+ 
			state_ptr->registers_adresable.at(regcode_a);
	}
	static void subtract_alu (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{
		state_ptr->registers_adresable.at(regcode_a) = 
			state_ptr->registers_adresable.at(regcode_a) 
			-
			state_ptr->registers_adresable.at(regcode_b);
	}
	static void xor_bitwise_alu (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{
		state_ptr->registers_adresable.at(regcode_a) = 
			state_ptr->registers_adresable.at(regcode_a) 
			^
			state_ptr->registers_adresable.at(regcode_b);

	}
	static void or_bitwise_alu (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{
		state_ptr->registers_adresable.at(regcode_a) = 
			state_ptr->registers_adresable.at(regcode_a) 
			|
			state_ptr->registers_adresable.at(regcode_b);
	}
	static void and_bitwise_alu (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{
		state_ptr->registers_adresable.at(regcode_a) = 
			state_ptr->registers_adresable.at(regcode_a) 
			&
			state_ptr->registers_adresable.at(regcode_b);
	}
	static void not_bitwise_alu (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{
		state_ptr->registers_adresable.at(regcode_a) = 
			~ state_ptr->registers_adresable.at(regcode_a);

	}
	static void logical_shift_left_alu (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{
		state_ptr->registers_adresable.at(regcode_a) = 
			state_ptr->registers_adresable.at(regcode_a) << 1;

	}
	static void logical_shift_right_alu (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{	
		state_ptr->registers_adresable.at(regcode_a) = 
			state_ptr->registers_adresable.at(regcode_a) >> 1;
	}
		




	// save/load accumulator
	static void set_a_to_value (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{
		state_ptr->registers_adresable.at(regcode_a) = operand0;
	}
	static void save_register_to_memory_at_xy (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{

	}
	static void load_a_from_memory_at_xy (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{

	}
	static void save_a_to_memory_at_xy  (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{

	}

	// Transfer between reg_a
	static void transfer_a_to_register (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{

	}
	static void transfer_register_to_a (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{

	}
	static void transfer_a_to_zeropage (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{

	}
	static void transfer_zeropage_to_a (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{

	}
	static void move_value_register_to_register (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{

	}
	static void move_value_register_to_zeropage (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{

	}
	static void move_value_zeropage_to_zeropage (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{

	}
	static void move_value_zeropage_to_register (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{

	}


	// Stack
	static void push_a (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{

	}
	static void push_register (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{

	}
	static void push_zeropage (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{

	}
	static void pop_a (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{

	}
	static void pop_register (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{

	}
	static void pop_zeropage (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{

	}


	// Conditions
	static void is_a_zero (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{

	}
	static void is_a_nonzero (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{

	}
	static void is_a_greater_than_b (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{

	}
	static void is_a_equal_b (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{

	}
	
	
	// Jumps
	static void jump_to_xy_uncoditional (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{

	}
	static void jump_to_xy_if_true (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{

	}
	static void jump_to_xy_if_false (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{

	}
	static void jump_to_adres_unconditional (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{

	}
	static void jump_to_adres_if_true (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{

	}
	static void jump_to_adres_if_false (struct CPUState *state_ptr, uint8_t operand0, uint8_t operand1)
	{

	}

}







































typedef void operation (VirtualMachineState * vmstate);
typedef operation (*operation_ptr);

union OperationPointer {	
	operationPointer_impliedAdres impliedAdres;
	operationPointer_registerAdres registerAdres;
	operationPointer_valueAdres valueAdres;
	

	void (*voidFunctionPointer)();
};


struct Instruction {
	uint8_t opcode;
	std::string mnemonic;
	std::string fullname;
	int adrestype;

	OperationPointer op_ptr;


	// methods
		// initializers:
	Instruction (
			std::string _mnemonic ,
			std::string _fullname ,
			operationPointer_impliedAdres op_ptr );
	Instruction (
			std::string _mnemonic ,
			std::string _fullname ,
			operationPointer_registerAdres op_ptr );
	Instruction (
			std::string _mnemonic ,
			std::string _fullname ,
			operationPointer_valueAdres op_ptr );

	Instruction(); // makes invalid instruction
		
		// other
	void printInstruction();

};














