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
    /*
    */

}

void Cartridge::go() {

    const int nameBuffer = 308;
    streampos size;

    int length = 0;

    ifstream file("C:\\Users\\logan\\Desktop\\blue.gb", ios::in | ios::binary);

    if (file.is_open())
    {
        size = file.tellg();

        vector<unsigned char> buffer(istreambuf_iterator<char>(file), {});


        //for (unsigned char i : buffer) {
         //   cout << unsigned(i) << " ";
       // }


        cout << "Title Name: ";

        for (int i = 0; i < 16; i++) {
            cout << (buffer[nameBuffer + i]);
        }

    }

    else cout << "Unable to open file";

}
Cartridge::~Cartridge()
{
}