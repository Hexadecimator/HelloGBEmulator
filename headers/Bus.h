#pragma once
#include <cstdint>
#include <array>

#include "cpuLR35902.h"
#include "ppu.h"
#include "Cartridge.h"

class Bus
{
public:

	Bus();
	~Bus();

public:

	cpuLR35902 cpu; 
	ppu ppu;
	Cartridge cart;
	std::array<uint8_t, 8 * 1024> wRam; // 8kb work ram
	std::array<uint8_t, 8 * 1024> vRam; // 8kb video ram

public:

	void writeWRAM(uint16_t addr, uint8_t data);
	uint8_t readWRAM(uint16_t addr, bool bReadOnly = false);

	void writeVRAM(uint16_t addr, uint8_t data);
	uint8_t readVRAM(uint16_t addr, bool bReadOnly = false);

};