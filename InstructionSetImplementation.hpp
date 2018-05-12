#pragma once

#include <cstdio>

#include "typedefs.hpp"
#include "CPUState.hpp"
#include "Instruction.hpp"

static const uint8_t MEMPAGE_STACK = 0x01;
	











// Legacy:

void no_operation (class VirtualMachineState*);

// Increment/decrement will be commonly used on probably all registers, so I decided to just make a set of inc/dec operations for all registers
void increment_register (class VirtualMachineState *, std::string register_name);
void decrement_register (class VirtualMachineState *, std::string register_name);

// ALU:
void add_with_carry (class VirtualMachineState *);
void subtract_with_carry (class VirtualMachineState*);
void xor_bitwise (class VirtualMachineState*);
void or_bitwise (class VirtualMachineState*);
void and_bitwise (class VirtualMachineState*);
void not_bitwise (class VirtualMachineState*);
void rotate_left (class VirtualMachineState*);
void rotate_right (class VirtualMachineState*);
void logical_shift_left (class VirtualMachineState*);
void logical_shift_right (class VirtualMachineState*);


// Loading registers
// Save
void load_a_with_value (class VirtualMachineState *, uint8_t value);
void load_a_from_memory (class VirtualMachineState *);
void save_a_to_memory (class VirtualMachineState *);


// Transfer between reg_a
void transfer_a_to_register (class VirtualMachineState *, std::string register_name);
void transfer_register_to_a (class VirtualMachineState *, std::string register_name);

// Stack
void push_register(class VirtualMachineState*, std::string register_name);
void pop_register(class VirtualMachineState*, std::string register_name);

// Conditions
void is_zero (class VirtualMachineState *);
void is_a_greater_than_b (class VirtualMachineState *);
// Jumps
void jump_uncoditional (class VirtualMachineState *);
void jump_if(class VirtualMachineState *);
void jump_if_not(class VirtualMachineState *);


void instruction_increment_register(class VirtualMachineState *, uint8_t );
void instruction_decrement_register(class VirtualMachineState *, uint8_t );

void  instruction_push_register (
		class VirtualMachineState *,
		uint8_t );

void  instruction_pop_register (
		class VirtualMachineState * ,
		uint8_t );
