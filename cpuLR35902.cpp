#include "cpuLR35902.h"
#include "Bus.h"

cpuLR35902::cpuLR35902()
{
	using a = cpuLR35902;
	// each {} is an INSTRUCTION struct: 
	// string name, pointer to opcode function, total cycles for instruction
	// TODO 1: done
	// TODO 2: There are a lot of instructions that operate on different registers (LD for example), 
	//         will one LD function satisfy all the permutations? How to do this?
	// TODO 3: Every opcode also has "length in bytes" that is not captured here... should it be? 
	//         ...maybe this "length in bytes" attribute can be used to organize some kind of polymorphism?
	lookup =
	{
		// only doing 1 row for now to figure things out
		{"NOP", &a::NOP, 4},{"LD", &a::LD, 12},{"LD", &a::LD, 8},{"INC", &a::INC, 8},{"INC", &a::INC, 4},{"DEC", &a::DEC, 4},{"LD", &a::LD, 8},{"RLCA", &a::RLCA, 4},{"LD", &a::LD, 20},{"ADD", &a::ADD, 8},{"LD", &a::LD, 8},{"DEC", &a::DEC, 8},{"INC", &a::INC, 4},{"DEC", &a::DEC, 4},{"LD", &a::LD, 8},{"RRCA", &a::RRCA, 4},
		{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
		{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
		{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
		{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
		{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
		{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
		{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
		{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
		{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
		{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
		{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
		{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
		{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
		{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
		{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}
	};
}

cpuLR35902::~cpuLR35902()
{
}

uint8_t cpuLR35902::GetFlag(FLAGS35902 f)
{
	return ((status & f) > 0) ? 1 : 0;
}

void cpuLR35902::SetFlag(FLAGS35902 f, bool v)
{
	if (v)
		status |= f;
	else
		status &= ~f;
}

uint8_t cpuLR35902::fetch()
{
	// TODO: If there are different types of addressing modes,
	//       take care of them here
	fetched = read(addr_abs);

	return fetched;
}

uint8_t cpuLR35902::NOP()
{
	// TODO: Game compatibility may necessitate handling different
	// NOP opcodes differently, thus the switch statement
	switch (opcode)
	{
	case 0xFC:
		return 1;
		break;
	}
	return 0;
}