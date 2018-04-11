#pragma once

#include "VirtualMachineState.hpp"
#include "VirtualMachine.hpp"

const uint8_t MEMPAGE_STACK = 0x01;

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



};
