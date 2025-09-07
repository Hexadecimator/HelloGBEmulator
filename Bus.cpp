#include "headers/Bus.h"

Bus::Bus()
{
	cpu.ConnectBus(this);

	for (auto& i : wRam) i = 0x00; // clear wram
	for (auto& i : vRam) i = 0x00; // clear vram
}

Bus::~Bus()
{

}

void Bus::writeWRAM(uint16_t addr, uint8_t data)
{
	if (addr >= 0x0000 && addr <= 0xFFFF)
		wRam[addr] = data;
}

uint8_t Bus::readWRAM(uint16_t addr, bool bReadOnly)
{
	if (addr >= 0x0000 && addr <= 0xFFFF)
		return wRam[addr];

	return 0x00;
}

void Bus::writeVRAM(uint16_t addr, uint8_t data)
{
	if (addr >= 0x0000 && addr <= 0xFFFF)
		vRam[addr] = data;
}

uint8_t Bus::readVRAM(uint16_t addr, bool bReadOnly)
{
	if (addr >= 0x0000 && addr <= 0xFFFF)
		return vRam[addr];

	return 0x00;
}