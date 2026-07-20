#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "headers/cpuLR35902.h"
#include "headers/Bus.h"

using namespace std;

//-o------------------------------------------------------------------o
// |   OPCODE: NOP (0x00)                                             |
//-o------------------------------------------------------------------o
uint8_t cpuLR35902::OP_00()
{
	// TODO: Game compatibility may necessitate handling different
	// NOP opcodes differently, thus the switch statement
	printf("Am I gay?");
	switch (opcode)
	{
	case 0xFC:
		return 1;
		break;
	}

	return 0;
}

//-o------------------------------------------------------------------o
// |   OPCODE: LD BC,d16 (0x01)                                       |
//-o------------------------------------------------------------------o
uint8_t cpuLR35902::OP_01()
{
	uint16_t temp = (bus->cart.romData[pc+2] << 8) | bus->cart.romData[pc+1];
	SetRegBC(temp);
	pc = pc + 3;
	return 0;
}

//-o------------------------------------------------------------------o
// |   OPCODE: LD BC,d16 (0x01)                                       |
//-o------------------------------------------------------------------o
uint8_t cpuLR35902::OP_01()
{
	uint16_t temp = (bus->cart.romData[pc + 2] << 8) | bus->cart.romData[pc + 1];
	SetRegBC(temp);
	pc = pc + 3;
	return 0;
}

//-o------------------------------------------------------------------o
// |   OPCODE: LD (BC),A (0x02)                                       |
//-o------------------------------------------------------------------o
uint8_t cpuLR35902::OP_02()
{
	
	return 0;
}