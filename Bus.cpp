#include "headers/Bus.h"

Bus::Bus()
{
	// TODO: Connect to bus

	for (auto& i : ram) i = 0x00; // clear ram
}

Bus::~Bus()
{

}

// TODO: Read
// TODO: Write