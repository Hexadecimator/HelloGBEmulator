#pragma once
#include <cstdint>
#include <array>
#include <fstream>
#include <iostream>

class Cartridge
{
	public:

		Cartridge();
		~Cartridge();
		bool loadData();
		void getCartridgeType(const int data); 
		uint8_t* romData = NULL;

};