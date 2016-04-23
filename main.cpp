/*
    File: main.cpp
    Author: Matthew White
    Contains the main function.  Handles command line arguments
    and calls on the DES class.
*/
#include <iostream>
#include <cstdlib>
#include "des.h"

using namespace std;

int main(int argc, char* argv[])
{
    string usage = "Usage is: " 
        + string(argv[0])
        + " (-e|-d) key message\n";
             
    if(argc == 4)
    {
        bool encrypt;
        string key = string(argv[2]);
        string text = string(argv[3]);
        string output = "";

        //test for proper size
        if(key.size() == 10 && text.size() == 8)
        {
            //ensure the input is in binary
            for(int k = 0; k < key.size(); k++)
            {
                if(key[k] != '1' && key[k] != '0') {
                    cout << usage
                        << "key must be 10 bits in binary, e.g. 1010101010\n"
                        << endl;

                    exit(0);
                }
            }
            for(int k = 0; k < text.size(); k++)
            {
                if(text[k] != '1' && text[k] != '0'){

                    cout << usage
                        << "text must be 8 bits in binary, e.g. 11111111\n"
                        << endl;

                    exit(0);
                }
            }
        }
        else
        {
            cout << usage
                << "key must be 10 bits in binary, e.g. 1010101010\n"
                << "text must be 8 bits in binary, e.g. 11111111\n"
                << endl;

            exit(0);
        }

        //handle mode parameter
        if(string(argv[1]) == "-e")
        {
            encrypt = true;
            DES* crypto = new DES(key, text, encrypt);
            output = crypto->encrypt();
        }
        else if(string(argv[1]) == "-d")
        {
            encrypt = false;
            DES* crypto = new DES(key, text, encrypt);
            output = crypto->decrypt();
        }
        else
        {
            cout << usage
                << "-e to encrypt\n"
                << "-d to decrypt\n"
                << "-e and -d are mutually exclusive\n"
                << endl;

            exit(0);
        }

        cout << output << "\n";
    }
    else
    {
        cout << usage
            << "-e to encrypt\n"
            << "-d to decrypt\n"
            << "-e and -d are mutually exclusive\n"
            << "key must be 10 bits in binary, e.g. 1010101010\n"
            << "text must be 8 bits in binary, e.g. 11111111"
            << endl;

        exit(0);
    }
}

