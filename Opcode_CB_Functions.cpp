#include "headers/cpuLR35902.h"


//-o------------------------------------------------------------------o
// |   CB OPCODE: RLC B (0x00)                                        |
//-o------------------------------------------------------------------o
uint8_t cpuLR35902::OP_CB_00()
{
	// shifts all bits of register B left, what was bit 7 becomes bit 0
	// what was bit 7 also is stored in the carry flag
	// clears half-carry and subtract flags
	uint8_t b = GetRegB();
	
	// set carry bit, plus carry becomes bit 0

	/*** REDEFINED VARIABLES COMPILER ISSUE ***
	uint8_t carry = 0x80 & b; // 0b1000 0000
	uint8_t carry = carry >> 8;

	SetFlag(FLAGS35902::C, carry);


	// actually rotate b register left
	b = b << 1;
	b = b | carry;
	SetRegB(b);
	*/

	// clear half carry and subtract flags
	SetFlag(FLAGS35902::H, 0);
	SetFlag(FLAGS35902::N, 0);

	return 0;
}

//-o------------------------------------------------------------------o
// |   CB OPCODE: RLC C (0x01)                                        |
//-o------------------------------------------------------------------o
uint8_t cpuLR35902::OP_CB_01()
{
	uint8_t c = GetRegC();

	// set carry bit, plus carry becomes bit 0

	/*** REDEFINED VARIABLES COMPILER ISSUE ***
	uint8_t carry = 0x80 & c; // 0b1000 0000
	uint8_t carry = carry >> 8;
	

	SetFlag(FLAGS35902::C, carry);


	c = c << 1;
	c = c | carry;
	*/

	SetFlag(FLAGS35902::H, 0);
	SetFlag(FLAGS35902::N, 0);

	return 0;
}
