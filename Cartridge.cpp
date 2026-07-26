#pragma once
#include <cstdint>
#include <array>
#include <fstream>
#include <iostream>

#include "headers/Cartridge.h"
#include "headers/cpuLR35902.h"
#include "headers/Bus.h"

using namespace std;

Cartridge::Cartridge()
{

}

void Cartridge::getCartridgeType(int data)
{
    switch (data)
    {
        case 0x00:
            cout << "ROM ONLY";
            break;

        case 0x01:
            cout << "MBC1";
            break;

        case 0x02:
            cout << "MBC1+RAM";
            break;

        case 0x03:
            cout << "MBC1+RAM+BATTERY";
            break;

        case 0x05:
            cout << "MBC2";
            break;

        case 0x06:
            cout << "MBC2+BATTERY";
            break;

        case 0x08:
            cout << "ROM+RAM";
            break;

        case 0x09:
            cout << "ROM+RAM+BATTERY";
            break;

        case 0x0B:
            cout << "MMM01";
            break;

        case 0x0C:
            cout << "MMM01+RAM";
            break;

        case 0x0D:
            cout << "MMM01+RAM+BATTERY";
            break;

        case 0x0F:
            cout << "MBC3+TIMER+BATTERY";
            break;

        case 0x10:
            cout << "MBC3+TIMER+RAM+BATTERY";
            break;

        case 0x11:
            cout << "MBC3";
            break;

        case 0x12:
            cout << "MBC3+RAM";
            break;

        case 0x13:
            cout << "MBC3+RAM+BATTERY";
            break;

        case 0x19:
            cout << "MBC5";
            break;

        case 0x1A:
            cout << "MBC5+RAM";
            break;

        case 0x1B:
            cout << "MBC5+RAM+BATTERY";
            break;

        case 0x1C:
            cout << "MBC5+RUMBLE";
            break;

        case 0x1D:
            cout << "MBC5+RUMBLE+RAM";
            break;

        case 0x1E:
            cout << "MBC5+RUMBLE+RAM+BATTERY";
            break;

        case 0x20:
            cout << "MBC6";
            break;

        case 0x22:
            cout << "MBC7+SENSOR+RUMBLE+RAM+BATTERY";
            break;

        case 0xFC:
            cout << "POCKET CAMERA";
            break;

        case 0xFD:
            cout << "BANDAI TAMA5";
            break;

        case 0xFE:
            cout << "HuC3";
            break;

        case 0xFF:
            cout << "HuC1+RAM+BATTERY";
            break;

        default:
            cout << "UNKNOWN CARTRIDGE TYPE";
            break;
    }
}

bool Cartridge::loadData() {

    const int nameBuffer = 308;
    const int headerAddressCartridgeType = 0x147;
    const int headerAddressRomSize = 0x148;
    const int headerAddressRamSize = 0x149;
    streampos size;

    int length = 0;
    ifstream file("blue.gb", ios::in | ios::binary);

    if (file.is_open())
    {
        size = file.tellg();
        vector<uint8_t> buffer(istreambuf_iterator<char>(file), {});

        romData = (uint8_t*)malloc(buffer.size()+1);
        
        if (romData) { // Makes sure malloc was successful before trying to write to the address
            for (int i = 0; i < buffer.size(); i++) {
                romData[i] = buffer[i];
                // Debug printing to make sure each byte matches the index
                // printf("%#X - %d\n", romData[i], i); 
            }
        }

        cout << "\nCartridge Type: ";
        getCartridgeType(buffer[headerAddressCartridgeType]);


        cout << "\nTitle Name: ";
        for (int i = 0; i < 16; i++) {
            cout << (buffer[nameBuffer + i]);
        } 
        return true;
    }

    else {
        return false;
    }

}

Cartridge::~Cartridge()
{
    free(romData);
}