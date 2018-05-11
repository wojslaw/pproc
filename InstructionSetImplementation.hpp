#pragma once

#include <cstdio>

#include "typedefs.hpp"
#include "CPUState.hpp"
#include "Instruction.hpp"

static const uint8_t MEMPAGE_STACK = 0x01;
	
namespace cpu_instruction {
	static void no_operation(struct CPUState *state_ptr) {
		return;
	}


	static void increment_register(struct CPUState *state_ptr, uint8_t register_bytecode) ;

	static void decrement_register(struct CPUState *state_ptr, uint8_t register_bytecode);
		
		
	// ALU
	static void add_alu (struct CPUState *state_ptr);
	static void subtract_alu (struct CPUState *state_ptr);
	static void xor_bitwise_alu (struct CPUState *state_ptr);
	static void or_bitwise_alu  (struct CPUState *state_ptr);
	static void and_bitwise_alu (struct CPUState *state_ptr);
	static void not_bitwise_alu (struct CPUState *state_ptr);
	static void rotate_left_alu (struct CPUState *state_ptr);
	static void rotate_right_alu (struct CPUState *state_ptr);
	static void logical_shift_left_alu (struct CPUState *state_ptr);
	static void logical_shift_right_alu (struct CPUState *state_ptr);
		

	// save/load accumulator
	static void set_a_to_value(struct CPUState *state_ptr, uint8_t);
	static void save_register_to_memory_at_xy ( struct CPUState *state_ptr );
	static void load_a_from_memory_at_xy (struct CPUState *state_ptr);
	static void save_a_to_memory_at_xy  (struct CPUState *state_ptr);


	// Transfer between reg_a
	static void transfer_a_to_register (struct CPUState *state_ptr,  uint8_t);
	static void transfer_register_to_a (struct CPUState *state_ptr,  uint8_t);
	static void transfer_a_to_zeropage (struct CPUState *state_ptr,  uint8_t);
	static void transfer_zeropage_to_a  (struct CPUState *state_ptr,  uint8_t);

	static void move_value_register_to_register(struct CPUState *state_ptr,  uint8_t, uint8_t);
	static void move_value_register_to_zeropage(struct CPUState *state_ptr,  uint8_t, uint8_t);
	static void move_value_zeropage_to_zeropage(struct CPUState *state_ptr,  uint8_t, uint8_t);
	static void move_value_zeropage_to_register(struct CPUState *state_ptr,  uint8_t, uint8_t);


	// Stack
	static void push_a(struct CPUState *state_ptr );
	static void push_register(struct CPUState *state_ptr , uint8_t);
	static void push_zeropage(struct CPUState *state_ptr,  uint8_t);
	static void pop_a(struct CPUState *state_ptr );
	static void pop_register(struct CPUState *state_ptr , uint8_t);
	static void pop_zeropage(struct CPUState *state_ptr, uint8_t);


	// Conditions
	static void is_a_zero (struct CPUState *state_ptr  );
	static void is_a_nonzero (struct CPUState *state_ptr  );
	static void is_a_greater_than_b (struct CPUState *state_ptr  );
	static void is_a_equal_b(struct CPUState *state_ptr  );
	
	
	// Jumps
	static void jump_to_xy_uncoditional (struct CPUState *state_ptr  );
	static void jump_to_xy_if_true (struct CPUState *state_ptr  );
	static void jump_to_xy_if_false (struct CPUState *state_ptr);
	static void jump_to_adres_unconditional(struct CPUState *state_ptr,  uint8_t, uint8_t);
	static void jump_to_adres_if_true(struct CPUState *state_ptr,  uint8_t, uint8_t);
	static void jump_to_adres_if_false(struct CPUState *state_ptr,  uint8_t, uint8_t);
}











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
