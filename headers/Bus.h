#pragma once
#include <cstdint>
#include <array>

#include "cpuLR35902.h"
#include "ppu.h"
#include "Cartridge.h"

class Bus
{
public:

	//-o------------------------------------------------------------------o
	// |   CONSTRUCTOR/DECONSTRUCTOR                                      |
	//-o------------------------------------------------------------------o

	Bus();
	~Bus();

public:

	//-o------------------------------------------------------------------o
	// |   CONNECTED COMPONENTS	                                          |
	//-o------------------------------------------------------------------o
	cpuLR35902 cpu; 
	//ppu ppu; Uncomment once ppu.h is implemented
	Cartridge cart;

	//-o------------------------------------------------------------------o
	// |   WRAM/VRAM					                                  |
	//-o------------------------------------------------------------------o

	std::array<uint8_t, 8 * 1024> wRam; // 8kb work ram
	std::array<uint8_t, 8 * 1024> vRam; // 8kb video ram

	//-o------------------------------------------------------------------o
	// |   WRAM/VRAM READ/WRITE FUNCTIONS					              |
	//-o------------------------------------------------------------------o

	void writeWRAM(uint16_t addr, uint8_t data);
	uint8_t readWRAM(uint16_t addr, bool bReadOnly = false);

	void writeVRAM(uint16_t addr, uint8_t data);
	uint8_t readVRAM(uint16_t addr, bool bReadOnly = false);

};