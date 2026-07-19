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
		void go();
		void getCartridgeType(const int data);

};