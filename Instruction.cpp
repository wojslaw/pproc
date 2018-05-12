#include "Instruction.hpp"


CPU_WrappedInstruction::~CPU_WrappedInstruction()
{
	// dtor
}




Instruction::Instruction()
{
	op_ptr.voidFunctionPointer = nullptr;
	adrestype = -1;
	opcode = -1;
	mnemonic = "XXX";
	fullname = "INVALID-INSTRUCTION";

	op_ptr.voidFunctionPointer = nullptr;
}


Instruction::Instruction (
		std::string _mnemonic ,
		std::string _fullname ,
		operationPointer_impliedAdres input_op_ptr )
{
	mnemonic = _mnemonic;
	fullname = _fullname;
	opcode = 0;

	adrestype = adrestype_implied;
	op_ptr.impliedAdres = input_op_ptr;
}


Instruction::Instruction (
		std::string _mnemonic ,
		std::string _fullname ,
		operationPointer_registerAdres input_op_ptr )
{
	mnemonic = _mnemonic;
	fullname = _fullname;
	opcode = 0;

	adrestype = adrestype_register;
	op_ptr.registerAdres = input_op_ptr;
}


Instruction::Instruction (
		std::string _mnemonic ,
		std::string _fullname ,
		operationPointer_valueAdres input_op_ptr )
{
	mnemonic = _mnemonic;
	fullname = _fullname;
	opcode = 0;

	adrestype = adrestype_value;
	op_ptr.valueAdres = input_op_ptr;
}


void Instruction::printInstruction()
{
	printf("`0x%02x`:`", opcode);
	std::cout << mnemonic;
	printf("`:`");
	std::cout << fullname;
	printf("`:`0x%x`adrestype (@%p)", adrestype, op_ptr.voidFunctionPointer);
}





















