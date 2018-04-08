#pragma once

#include "VirtualMachine.h"

const uint8_t MEMPAGE_STACK = 0x01;

namespace przejproc {
	
	void no_operation (struct VirtualMachine*);
	
// ALU:
	void increment_a (struct VirtualMachine *);
	void increment_b (struct VirtualMachine *);
	void decrement_a (struct VirtualMachine *);
	void decrement_a (struct VirtualMachine *);
	void add_with_carry (struct VirtualMachine *);
	void subtract_with_carry (struct VirtualMachine*);
	void xor_bitwise (struct VirtualMachine*);
	void or_bitwise (struct VirtualMachine*);
	void and_bitwise (struct VirtualMachine*);
	void not_bitwise (struct VirtualMachine*);
	void rotate_left (struct VirtualMachine*);
	void rotate_right (struct VirtualMachineState *);
	void arithmetic_shift_left (struct VirtualMachine*);
	void arithmetic_shift_right (struct VirtualMachine*);

// Save/Load
	void save_a_to_memory (struct VirtualMachine*);
	void save_b_to_memory (struct VirtualMachine*);
	void load_a_from_xy (struct VirtualMachine*);
	void load_a_with_constant (struct VirtualMachine*);
	void load_b_from_xy (struct VirtualMachine*);
	void load_b_with_constant (struct VirtualMachine *);

// Mem
	// problematic: void set_memory_address
	

// Stack
	void push_register(class VirtualMachine*, char register_name);
	void pop_register(class VirtualMachine*, char register_name);

	
	

};
