#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "headers/cpuLR35902.h"

using namespace std;

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

	return 0;
}