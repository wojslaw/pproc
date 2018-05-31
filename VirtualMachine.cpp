#include "VirtualMachine.hpp"








void VirtualMachine::doMachineCycle(void)
{
	cpu_state.fetchTwoByteInstruction();

	executeBytecodeInstruction(
			cpu_state.registers_instruction.at(0) ,
			cpu_state.registers_instruction.at(1) ,
			cpu_state.registers_instruction.at(2)
			);
	
}




void VirtualMachine::addWrappedInstruction (
			std::string input_mnemonic ,
			std::string input_fullname ,
			std::function<int (struct CPUState *, uint8_t , uint8_t)> input_instruction
		)
{
	vector_of_wrapped_instructions.emplace_back(WrappedInstruction(
		vector_of_wrapped_instructions.size() ,
		input_instruction ,
		input_mnemonic,
		input_fullname
	));
}

void VirtualMachine::addWrappedInstruction (
		std::string input_mnemonic , uint8_t input_argcount,
		std::string input_fullname ,
		std::function<int (struct CPUState *, uint8_t , uint8_t)> input_instruction 
		)
{
	vector_of_wrapped_instructions.emplace_back( WrappedInstruction(
		vector_of_wrapped_instructions.size() ,
		input_mnemonic ,
		input_fullname ,
		input_instruction ,
		input_argcount
	));
}

	




void VirtualMachine::createDefaultInstructionSet ()
{
	vector_of_wrapped_instructions.reserve(30);

	addWrappedInstruction( "nop", 0,
			"no-operation", 
			[] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				return 0;
			});

	//
	//----------------[ increment/decrement ]---
	//
	addWrappedInstruction( "inc-reg" , 1,
			"increment-register" , 
			[] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1) 
			{
				cpu_state_pointer->registers_adresable.at(operand0) = cpu_state_pointer->registers_adresable.at(operand0) + 1;
				return 1;
			});


	addWrappedInstruction( "dec-reg", 1,
			"decrement-register", 
			[] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				cpu_state_pointer->registers_adresable.at(operand0) = cpu_state_pointer->registers_adresable.at(operand0) - 1;
				return 1;
			});
	


	//
	//------------------[ arithmetic, logic ]---
	//
	addWrappedInstruction( "adc-alu", 0, 
			"add-with-carry-alu", 
			[] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				int a = cpu_state_pointer->registers_adresable.at(regcode_a);
				int b = cpu_state_pointer->registers_adresable.at(regcode_a);
				
				a += b;
				if ( a > 0xff ) {
					cpu_state_pointer->setBitOfRegister(regcode_flags, flagnumber_carry, 1);
				} else {
					cpu_state_pointer->setBitOfRegister(regcode_flags, flagnumber_carry, 0);
				}

				cpu_state_pointer->registers_adresable.at(regcode_a) = (uint8_t) a;
				return 0;
			} );

	addWrappedInstruction( "sbc-alu", 0, 
			"subtract-with-carry-alu", [] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				cpu_state_pointer->registers_adresable.at(regcode_a) = 
					cpu_state_pointer->registers_adresable.at(regcode_a)  
					-
					cpu_state_pointer->registers_adresable.at(regcode_a)  ;
				return 0;
			});

	addWrappedInstruction( "xor-alu", 0, 
			"xor-bitwise-alu", 
			[] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				cpu_state_pointer->registers_adresable.at(regcode_a) = 
					cpu_state_pointer->registers_adresable.at(regcode_a)  
					xor
					cpu_state_pointer->registers_adresable.at(regcode_a)  ;
				return 0;
			});
	addWrappedInstruction( "or-alu", 0,
			"or-bitwise-alu", [] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				cpu_state_pointer->registers_adresable.at(regcode_a) = 
					cpu_state_pointer->registers_adresable.at(regcode_a)  
					|
					cpu_state_pointer->registers_adresable.at(regcode_a)  ;
				return 0;
			});
	addWrappedInstruction( "and-alu", "and-bitwise-alu", [] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				cpu_state_pointer->registers_adresable.at(regcode_a) = 
					cpu_state_pointer->registers_adresable.at(regcode_a)  
					&
					cpu_state_pointer->registers_adresable.at(regcode_a)  ;
				return 0;
			});
	addWrappedInstruction( "not-alu", "not-bitwise-alu", [] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				cpu_state_pointer->registers_adresable.at(regcode_a) = 
					~cpu_state_pointer->registers_adresable.at(regcode_a)  ;
				return 0;
			});
	addWrappedInstruction( "lsl-alu", "logical-shift-left-alu", [] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				cpu_state_pointer->registers_adresable.at(regcode_a) = 
					cpu_state_pointer->registers_adresable.at(regcode_a) << 1 ;
				return 0;
			});

	addWrappedInstruction( "lsr-alu", "logical-shift-left-alu", [] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				cpu_state_pointer->registers_adresable.at(regcode_a) = 
					cpu_state_pointer->registers_adresable.at(regcode_a) >> 1 ;
				return 0;
			});


			//
			//  
			//
	addWrappedInstruction( "seta-val", 1, 
			"set-a-to-value", [] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				cpu_state_pointer->registers_adresable.at(regcode_a) = 
					operand0 ;
				return 1;
			});


			//
			//-------------[ memory - xy ]---
			//
	addWrappedInstruction( "save-reg-xy", "save-register-to-memory-at-xy", [] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				cpu_state_pointer->registers_adresable.at(regcode_a) = 
					operand0 ;
				return 1;
			});
	addWrappedInstruction( "load-reg-xy", "load-register-from-memory-at-xy", [] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				cpu_state_pointer->memory.at( 
						0x100*cpu_state_pointer->registers_adresable.at(regcode_x)
						+ 
						cpu_state_pointer->registers_adresable.at(regcode_x) 
					) = operand0;
				return 1;
			});


			//
			//------------[ memory - adres ]---
			//
			
			//
			//------------[ jumps ]
			//
			
			addWrappedInstruction( "jump-adres", "jump_to_adres_unconditional", [] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				cpu_state_pointer->registers_adresable.at(regcode_p) 
					 = operand0;
				cpu_state_pointer->registers_adresable.at(regcode_c) 
					= operand1;
				return 2;
			});


			//
			//-----------------[ stack ]---
			//
			addWrappedInstruction( "push-aa", 0, 
					"push-acumulator", 
					[] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				cpu_state_pointer->memory.at (0x100 + cpu_state_pointer->registers_adresable.at(regcode_s)) 
					= cpu_state_pointer->registers_adresable.at(regcode_a);
				cpu_state_pointer->incrementRegister(regcode_s);
				return 0;
			});
			addWrappedInstruction( "pop-aa", 0, 
					"pop-to-acumulator", 
					[] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				cpu_state_pointer->decrementRegister(regcode_s);
				cpu_state_pointer->memory.at (0x100 + cpu_state_pointer->registers_adresable.at(regcode_s)) 
					= cpu_state_pointer->registers_adresable.at(regcode_a);
				return 0;
			});
}




VirtualMachine::VirtualMachine()
{
	createDefaultInstructionSet();

	//ctor
}


void VirtualMachine::executeBytecodeInstruction(uint8_t instruction_bytecode, uint8_t operand0, uint8_t operand1)
{
	vector_of_wrapped_instructions.at(instruction_bytecode).instruction (&cpu_state, operand0, operand1);

	return;



	auto instruction = vector_of_wrapped_instructions.at(instruction_bytecode);
	std::cout << "Argcount = " << instruction.argcount;
}


void VirtualMachine::printInstructionSet()
{
	printf("\nInstruction set:\n");
	int i = 0;
	for(auto ins : vector_of_wrapped_instructions) {
		printf("%02d.  0x%02x  `%s`: '%s'  \n", 
				i ,   
				ins.bytecode ,
				ins.mnemonic.c_str() ,
				ins.fullname.c_str()
				);
		++i;
	}
}


uint8_t VirtualMachine::findInstructionByMnemonic(std::string mnemonic)
{
	return getInstructionBytecodeByMnemonic(mnemonic);
}


uint8_t VirtualMachine::getInstructionBytecodeByMnemonic(std::string mnemonic)
{
	for ( struct WrappedInstruction instr : vector_of_wrapped_instructions ) {
		if (instr.mnemonic == mnemonic) {
			return instr.bytecode;
		}
	}
	std::cout << "\nDidn't find instruction of mnemonic `" << mnemonic << "`";
}


struct WrappedInstruction VirtualMachine::getInstructionByMnemonic(std::string mnemonic)
{
	for ( size_t i = 0; i < vector_of_wrapped_instructions.size(); ++i ) {
		if ( vector_of_wrapped_instructions.at(i).mnemonic == mnemonic) {
			return vector_of_wrapped_instructions.at(i);
		}
	}
	std::cout << "\nDidn't find instruction of mnemonic `" << mnemonic << "`";
}



VirtualMachine::~VirtualMachine()
{

}



















void VirtualMachine::loadBytesIntoMemory(std::vector<uint8_t> vector_of_bytes, uint8_t startpage, uint8_t startcell)
{
	cpu_state.loadVectorOfBytesToMemory(startpage, startcell, vector_of_bytes);
}









void VirtualMachine::printMemory(
		uint8_t page ,
		uint8_t start_cell ,
		uint8_t cellcount 
) {
	printf("\nDeprecated functions was called: %s", __func__);
	for(uint8_t i = 0; i < cellcount; i++) {
		uint8_t curcell = start_cell+i;
		uint8_t value = *accessMemoryAt(page, curcell);
		printf("\n @$%02x%02x: $%02x   b_", page, curcell, value );
		cout << bitset<8>(value);
	}
}




uint8_t* VirtualMachine::accessMemoryAt (
		uint8_t page ,
		uint8_t cell )
{
	printf("\nDeprecated functions was called: %s", __func__);
	return 0;
}


uint8_t* VirtualMachine::accessMemoryByXY (void) 
{

	printf("\nDeprecated functions was called: %s", __func__);
	return 0;
}


uint8_t* VirtualMachine::accessMemoryByPC(void)
{
	printf("\nDeprecated functions was called: %s", __func__);
}

