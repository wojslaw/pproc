#include "Instruction.hpp"


Instruction::Instruction()
{
	opptr.voidFunctionPointer = nullptr;
	adrestype = -1;
	opcode = -1;
	mnemonic = "XXX";
	fullname = "INVALID-INSTRUCTION";

	op_ptr = 0;
}


Instruction::Instruction (
		std::string _mnemonic ,
		std::string _fullname ,
		operationPointer_impliedAdres op_ptr )
{
	mnemonic = _mnemonic;
	fullname = _fullname;
	opcode = 0;

	adrestype = InstructionAdrestype::implied;
	opptr.impliedAdres = op_ptr;
}


Instruction::Instruction (
		std::string _mnemonic ,
		std::string _fullname ,
		operationPointer_registerAdres op_ptr )
{
	mnemonic = _mnemonic;
	fullname = _fullname;
	opcode = 0;

	adrestype = InstructionAdrestype::reg;
	opptr.registerAdres = op_ptr;
}


Instruction::Instruction (
		std::string _mnemonic ,
		std::string _fullname ,
		operationPointer_valueAdres op_ptr )
{
	mnemonic = _mnemonic;
	fullname = _fullname;
	opcode = 0;

	adrestype = InstructionAdrestype::value;
	opptr.valueAdres = op_ptr;
}

void Instruction::printInstruction()
{
	printf("`0x%02x`:`", opcode);
	std::cout << mnemonic;
	printf("`:`");
	std::cout << fullname;
	printf("` (@%p)", opptr.voidFunctionPointer);
}
