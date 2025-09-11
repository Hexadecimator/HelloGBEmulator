/*

===== INFO =====

https://gbdev.io/pandocs/

    CPU - 8-bit Sharp LR35902 (similar to the Z80 processor)
    Clock Speed - 4.194304MHz (4.295454MHz for SGB, max. 8.4MHz for CGB)
    Work RAM - 8K Byte (32K Byte for CGB)
    Video RAM - 8K Byte (16K Byte for CGB)
    Screen Size - 2.6"
    Resolution - 160x144 (20x18 tiles)
    Max sprites - Max 40 per screen, 10 per line
    Sprite sizes - 8x8 or 8x16 pixels
    Palettes - 1x4 BG, 2x3 OBJ (for CGB: 8x4 BG, 8x3 OBJ)
    Colors - 4 grayshades (32768 colors for CGB)
    Horiz Sync - 9198 KHz (9420 KHz for SGB)
    Vert Sync - 59.73 Hz (61.17 Hz for SGB)
    Sound - 4 channels with stereo sound
    Power - DC6V 0.7W (DC3V 0.7W for GB Pocket, DC3V 0.6W for CGB)

    ====================
    General Memory Map
    ====================

    Start 	End 	Description 	        Notes
    0000 	3FFF 	16KB ROM bank 00 	    From cartridge, usually a fixed bank
    4000 	7FFF 	16KB ROM Bank 01~NN 	From cartridge, switchable bank via MBC (if any)
    8000 	9FFF 	8KB Video RAM (VRAM) 	Only bank 0 in Non-CGB mode

    Switchable bank 0/1 in CGB mode
    A000 	BFFF 	8KB External RAM 	    In cartridge, switchable bank if any
    C000 	CFFF 	4KB Work RAM (WRAM)     bank 0
    D000 	DFFF 	4KB Work RAM (WRAM)     bank 1~N 	Only bank 1 in Non-CGB mode

    Switchable bank 1~7 in CGB mode
    E000 	FDFF 	Mirror of C000~DDFF (ECHO RAM) 	Typically not used
    FE00 	FE9F 	Sprite attribute table (OAM)
    FEA0 	FEFF 	Not Usable
    FF00 	FF7F 	I/O Registers
    FF80 	FFFE 	High RAM (HRAM)
    FFFF 	FFFF 	Interrupts Enable Register (IE)

    The following addresses are supposed to be used as jump vectors:
        RST commands: 0000,0008,0010,0018,0020,0028,0030,0038
        Interrupts: 0040,0048,0050,0058,0060

    The memory at 0100-014F contains the cartridge header

    ====================
    Registers
    ====================
    16-bit	Hi	Lo	Name/Function
    AF	    A	-	Accumulator & Flags
    BC	    B	C	BC
    DE	    D	E	DE
    HL	    H	L	HL
    SP	    -	-	Stack Pointer
    PC	    -	-	Program Counter/Pointer


*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "headers/Bus.h"

using namespace std;

class GBEmulator {

    private:
        Bus game; 
        Cartridge cart;

    public:
        

    void start() {

        // TO DO - Write basic step-through clock cycling for testing

    }

};

int main() {
    
    //GBEmulator game;
    //game.start();

    return 0;

}