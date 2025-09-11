#include "headers/cpuLR35902.h"

//-o------------------------------------------------------------------o
// |   OPCODE: NOP (0x00)                                             |
//-o------------------------------------------------------------------o
uint8_t cpuLR35902::OP_00()
{
	// TODO: Game compatibility may necessitate handling different
	// NOP opcodes differently, thus the switch statement
	
	switch (opcode)
	{
	case 0xFC:
		return 1;
		break;
	}

	/* Example clock cycle

	 cpu.clock(lookup[OP_00].cycles);

	*/

	return 0;
}