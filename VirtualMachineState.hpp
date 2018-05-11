#pragma once

#include <cstdint>
#include <cstdio>

#include <map>
#include <string>
#include <vector>

#include <iostream>
using std::cout;
#include <bitset>
using std::bitset;



const std::string REGISTER_NAMES_STRING = "abfsxypc";
const std::string INTERNAL_REGISTER_NAMES_STRING = "io";

const size_t CPU_MEMORY_PAGES = 0x100;
const size_t CPU_MEMORY_CELLS_ON_PAGE = 0x100;
const uint8_t CPU_NUMBER_OF_INSTRUCTION_REGISTERS = 3;


struct Register {
	std::string codename;
	uint8_t numeric_code;

	uint8_t value;

	std::string name;
	std::string description;

	Register( std::string regcode , 
			uint8_t regnumcode ,
			std::string regname , 
			std::string regdescription );
};






typedef void (*vm_operationPointer_noOperand) (void); 
typedef void (*vm_operationPointer_oneByteOperand) (uint8_t);
typedef void (*vm_operationPointer_twoByteOperand) (uint8_t, uint8_t);


typedef void (*vm_operationPointer) (uint8_t, uint8_t);


union vm_OperationPointer {	
	vm_operationPointer_noOperand no_operand;
	vm_operationPointer_oneByteOperand one_byte_operand;
	vm_operationPointer_twoByteOperand two_byte_operand;

	vm_operationPointer_noOperand void_pointer;
};



struct vm_Instruction {
	uint8_t bytecode;
	int adrestype;
	
	vm_OperationPointer operation_pointer;

	std::string mnemonic;
	std::string fullname;


	// constructors:
	vm_Instruction (
			uint8_t input_bytecode ,
			std::string input_mnemonic ,
			std::string input_fullname ,
			vm_operationPointer_noOperand input_operation_pointer );
	vm_Instruction (
			uint8_t input_bytecode ,
			std::string input_mnemonic ,
			std::string input_fullname ,
			vm_operationPointer_oneByteOperand input_operation_pointer );
	vm_Instruction (
			uint8_t input_bytecode ,
			std::string input_mnemonic ,
			std::string input_fullname ,
			vm_operationPointer_twoByteOperand input_operation_pointer );

	vm_Instruction(); // makes invalid instruction



	// display:
	void printInstruction();
};








struct VirtualMachineState {
	// The State: //Taxation is theft




		// State itself:
	uint8_t mem[CPU_MEMORY_PAGES][CPU_MEMORY_CELLS_ON_PAGE];
	std::vector<struct Register> vector_registers_adresable;
	std::vector<uint8_t> vector_registers_instruction; // instruction registers are unnamed
	std::vector<std::string> register_names;
	

		// Instructions vector:
	std::vector<vm_Instruction> vector_of_instructions;

		// ctors and dtors
	VirtualMachineState();
	~VirtualMachineState();



	// { 
	struct InstructionSet *instruction_set_ptr;
	uint8_t simulator_lastread_p; // Updated on each clock cycle
	uint8_t simulator_lastread_c;
	// }
	


		// simulator-specific(printing and stuff
	void printMemory(uint8_t startpage, uint8_t startcell, uint8_t number_of_cells);
	void printAdresableRegisters(void);
	void printRegistersDescription();

		// methods for operating on the state
	void    setRegisterValueByName(std::string, uint8_t);
	uint8_t getRegisterValueByName(std::string);
	void    setRegisterValueByBytecode(uint8_t, uint8_t);
	uint8_t getRegisterValueByBytecode(uint8_t);





	Register* accessRegisterByName(std::string regnam);
	void setRegisterByName(char, uint8_t);
	uint8_t getRegisterByName(char);
	void incrementPC();
	void incrementPC_times(int);

	uint8_t getMemoryValueAt(
		uint8_t page,
		uint8_t cell );
	void setMemoryValueAt(
		uint8_t page,
		uint8_t cell, 
		uint8_t value);
	uint8_t* accessMemoryAt  (uint8_t page, uint8_t cell );
	uint8_t* accessMemoryByXY(void);
	uint8_t* accessMemoryByPC(void);
	

// helper methods:
	void addAdrReg(
			std::string code,
			uint8_t numeric_code,
			std::string name, 
			std::string description); /// Adresable register

	
	void loadSequenceOfBytesIntoMemory(
		std::vector<uint8_t> vector_of_bytes
		, uint8_t startpage 
		, uint8_t startcell);


	void fetchCurrentInstruction(void);






	/*
	// 
	// ---[ Instruction set ] --- {
	//
		
		void no_operation(void);
		
		// Arithmetic and logic
		void increment_register(uint8_t register_bytecode);
		void decrement_register(uint8_t register_bytecode);
		
		
		void add_alu (void);
		void subtract_alu (void);
		void xor_bitwise_alu (void);
		void or_bitwise_alu (void);
		void and_bitwise_alu (void);
		void not_bitwise_alu (void);
		void rotate_left_alu (void);
		void rotate_right_alu (void);
		void logical_shift_left_alu (void);
		void logical_shift_right_alu (void);
		

		// save/load accumulator
		void set_a_to_value(uint8_t);

		void save_register_to_memory_at_xy ();
		void load_a_from_memory_at_xy ();
		void save_a_to_memory_at_xy ();


		// Transfer between reg_a
		void transfer_a_to_register (uint8_t);
		void transfer_register_to_a (uint8_t);
		void transfer_a_to_zeropage (uint8_t);
		void transfer_zeropage_to_a  (uint8_t);

		void move_value_register_to_register(uint8_t, uint8_t);
		void move_value_register_to_zeropage(uint8_t, uint8_t);
		void move_value_zeropage_to_zeropage(uint8_t, uint8_t);
		void move_value_zeropage_to_register(uint8_t, uint8_t);


		// Stack
		void push_a(void);
		void push_register(uint8_t);
		void push_zeropage(uint8_t);
		void pop_a(void);
		void pop_register(uint8_t);
		void pop_zeropage(uint8_t);


		// Conditions
		void is_a_zero (void);
		void is_a_nonzero (void);
		void is_a_greater_than_b (void);
		void is_a_equal_b(void);
		
		
		// Jumps
		void jump_to_xy_uncoditional (void);
		void jump_to_xy_if_true (void);
		void jump_to_xy_if_false (void);
		void jump_to_adres_unconditional(uint8_t, uint8_t);
		void jump_to_adres_if_true(uint8_t, uint8_t);
		void jump_to_adres_if_false(uint8_t, uint8_t);
			


	//--
	//--  }
	//--
*/

















};




















/*struct AdresableRegister {
private:
	std::string name;
public:
	std::string getName();
	uint8_t value;
	AdresableRegister(std::string);
	AdresableRegister();
};

struct Array_AdresableRegister {
	struct AdresableRegister reg[0xff];
	size_t regcount;
	
	
	Array_AdresableRegister();
	// methods
	void addNewRegister(std::string regnam);
	void printRegisters();
	AdresableRegister* findRegisterByName(const std::string regname);
};*/
