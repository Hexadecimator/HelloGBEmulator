#pragma once
#include <cstdint>
#include <array>

class Cartridge
{

/******************* TEMPORARY CODE FOR READING ROM DATA *******************

    const int nameBuffer = 308;
    streampos size;

    int length = 0;

    ifstream file("../blue.gb", ios::in | ios::binary);

    if (file.is_open())
    {
        size = file.tellg();

        vector<unsigned char> buffer(istreambuf_iterator<char>(file), {});

        
        for (unsigned char i : buffer) {
            cout << unsigned(i) << " ";
        }
        

        cout << "Title Name: ";

        for (int i = 0; i < 16; i++) {
            cout << (buffer[nameBuffer+i]);
        }

    }

    else cout << "Unable to open file";

****************************************************************************/

};