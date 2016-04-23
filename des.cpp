/*
    File: des.cpp
    Author: Matthew White
    Contains the implementations for the DES class
*/
#include "des.h"
#include <sstream>
#include <iostream>
#include <cstdlib>

DES::DES(string key, string text, bool encrypt)
{
    //cout << "In constructor" << endl;

    this->m_key = key;

    if(encrypt)
    {
        this->m_text = text;
    }
    else
    {
        this->m_ciphertext = text;
    }

    this->fillTables();

    this->createKeys();

    //cout << "Out constructor" << endl;
}

string DES::encrypt()
{
    /*
    string current = this->m_text;
    cout << "start:\t" << current << endl;
    current = IP(current);
    cout << "IP:\t" << current << endl;
    current = fK(current, this->m_k1);
    cout << "fK1:\t" << current << endl;
    current = SW(current);
    cout << "SW:\t" << current << endl;
    current = fK(current, this->m_k2);
    cout << "fK2:\t" << current << endl;
    current = inverseIP(current);
    cout << "invIP:\t" << current << endl;*/

    //return current;

    return inverseIP(fK(SW(fK(IP(this->m_text), this->m_k1)), this->m_k2));
}

string DES::decrypt()
{
    return inverseIP(fK(SW(fK(IP(this->m_ciphertext), this->m_k2)), this->m_k1));
}

string DES::P10(string input)
{
    //cout << "In P10" << endl;
    
    string output = "";
    for(int k = 0; k < 10; k++)
    {
        output += input[this->tableP10[k] - 1];
    }

    //cout << "Out P10" << endl;

    return output;
}

string DES::leftShift(string input)
{
    //cout << "In leftShift" << endl;
    
    string output = "";
    //left side rotation
    for(int k = 1; k < input.size()/2; k++)
    {
        if(input.size() > k)
        {
            output += input[k];
        }
    }
    if(input.size() > 0)
    {
        output += input[0];
    }


    //right side rotation
    for(int k = input.size()/2 + 1; k < input.size(); k++)
    {
        if(input.size() > k)
        {
            output += input[k];
        }
    }
    if(input.size() > input.size()/2)
    {
        output += input[input.size()/2];
    }

    //cout << "Out leftShift" << endl;

    return output;
}

string DES::P8(string input)
{
    //cout << "In P8" << endl;
    
    if(input.size() < 8)
    {
        cout << "P8: input too small.  Exiting." << endl;
        exit(0);
    }

    string output = "";
    for(int k = 0; k < 8; k++)
    {
        output += input[this->tableP8[k] - 1];
    }

    //cout << "Out P8" << endl;

    return output;
}

void DES::createKeys()
{
    //cout << "In createKeys" << endl;
    
    if(m_key.size() < 10)
    {
        cout << "createKeys: key too small.  Exiting." << endl;
        exit(0);
    }

    //cout << "Key:\t" << this->m_key << endl;

    string temp = "";
    //apply P10
    for(int k = 0; k < 10; k++)
    {
        temp += this->m_key[this->tableP10[k] - 1];
    }

    //cout << "P10:\t" << temp << endl;

    //apply LS-1 function
    temp = leftShift(temp);

    //cout << "shift:\t" << temp << endl;

    if(temp.size() < 8)
    {
        cout << "createKeys: temp too small.  Exiting." << endl;
        exit(0);
    }

    this->m_k1 =  "";
    //apply P8, finding K1
    for(int k = 0; k < 8; k++)
    {
        this->m_k1 += temp[this->tableP8[k] - 1];
    }

    //cout << "P8(k1):\t" << this->m_k1 << endl;

    //cout << "preshift:\t" << temp << endl;

    //apply two more left shifts
    temp = leftShift(temp);
    temp = leftShift(temp);

    //cout << "2shifts:\t" << temp << endl;

    this->m_k2 =  "";
    //apply P8, finding K2
    for(int k = 0; k < 8; k++)
    {
        this->m_k2 += temp[this->tableP8[k] - 1];
    }

    //cout << "P8(k2):\t" << this->m_k2 << endl;

    //cout << "Out createKeys" << endl;
}

string DES::IP(string input)
{
    //cout << "In IP" << endl;
    
    if(input.size() < 8)
    {
        cout << "IP: input too small.  Exiting." << endl;
        exit(0);
    }

    string output = "";
    for(int k = 0; k < 8; k++)
    {
        output += input[this->tableIP[k] - 1];
    }

    //cout << "Out IP" << endl;

    return output;
}

string DES::inverseIP(string input)
{
    //cout << "In inverseIP" << endl;
    
    if(input.size() < 8)
    {
        cout << "inverseIP: input too small.  Exiting." << endl;
        exit(0);
    }

    string output = "";
    for(int k = 0; k < 8; k++)
    {
        output += input[this->tableInverseIP[k] - 1];
    }


    //cout << "Out inverseIP" << endl;

    return output;
}

string DES::fK(string input, string subKey)
{
    //cout << "In fK" << endl;
    
    if(input.size() < 8)
    {
        cout << "fK: input too small.  Exiting." << endl;
        exit(0);
    }

    //cout << "text:\t" << input << endl;
    string output = "";
    //apply E/P
    for(int k = 0; k < 8; k++)
    {
        output += input[this->tableEP[k] - 1 + 4];
    }
    //cout << "E/P:\t" << output << endl;

    //cout  << "Before XOR:\n" 
    //      << "input:\t" << output << endl
    //      << "subKey:\t" << subKey << endl;

    output = this->XOR(output, subKey);

    //cout << "XOR:\t" << output << endl;


    //cout << "sBox input: " << output << endl;

    //apply s boxes
    string temp = this->sBoxes(output);

    //cout << "sBox:\t" << temp << endl;

    output = input; //restores the original input.
                    //this is because we want to keep
                    //the last four bits as-is

    //apply P4
    for(int k = 0; k < 4; k++)
    {
        output[k] = temp[this->tableP4[k] - 1];
    }

    //cout << "P4:\t" << output << endl;

    //it should be noted that I could not find this XOR step in the 
    //S-DES attachment, but the output would not align with the test cases without it.
    output = this->XOR(output.substr(0,4), input.substr(0,4)) + input.substr(4,4);

    

    //cout << "Out fK" << endl;

    return output;
}

string DES::SW(string input)
{
    //cout << "In SW" << endl;
    
    /*
    if(input.size() < 8)
    {
        cout << "SW: input too small.  Exiting." << endl;
        exit(0);
    }*/

    string output = "";
    //puts the right four bits left
    for(int k = input.size()/2; k < input.size(); k++)
    {
        output += input[k];
    }
    //puts the left four bits right
    for(int k = 0; k < input.size()/2; k++)
    {
        output += input[k];
    }

    //cout << "Out SW" << endl;

    return output;
}

string DES::XOR(string one, string two)
{
    //cout << "In XOR" << endl;
    
    string output = "";
    //note: the strings should be of the same length and
    //      should only contains 1's and 0's
    for(int k = 0; k < one.size() && k < two.size(); k++)
    {
        if(one[k] == two[k])
        {
            output += "0";
        }
        else
        {
            output += "1";
        }
    }


    //cout << "Out XOR" << endl;

    return output;
}

string DES::sBoxes(string input)
{
    //cout << "In sBoxes" << endl;
    
    string row0 = input.substr(0, 1) + input.substr(3, 1);
    string column0 = input.substr(1, 1) + input.substr(2, 1);
    string row1 = input.substr(4, 1) + input.substr(7, 1);
    string column1 = input.substr(5, 1) + input.substr(6, 1);
    int numRow0, numColumn0, numRow1, numColumn1;
    numRow0 = numRow1 = numColumn0 = numColumn1 = -1;

    //cout  << "Sbox 0: row - " << row0 
    //      << " column - " << column0 << endl
    //      << "Sbox 1: row - " << row1 
    //      << " column - " << column1 << endl;

    //get the numerical row value for S0
    if(row0 == "00")
    {
        numRow0 = 0;
    }
    else if(row0 == "01")
    {
        numRow0 = 1;
    }
    else if(row0 == "10")
    {
        numRow0 = 2;
    }
    else if(row0 == "11")
    {
        numRow0 = 3;
    }

    //get the numerical row value for S1
    if(row1 == "00")
    {
        numRow1 = 0;
    }
    else if(row1 == "01")
    {
        numRow1 = 1;
    }
    else if(row1 == "10")
    {
        numRow1 = 2;
    }
    else if(row1 == "11")
    {
        numRow1 = 3;
    }

    //get the numerical column value for S0
    if(column0 == "00")
    {
        numColumn0 = 0;
    }
    else if(column0 == "01")
    {
        numColumn0 = 1;
    }
    else if(column0 == "10")
    {
        numColumn0 = 2;
    }
    else if(column0 == "11")
    {
        numColumn0 = 3;
    }

    //get the numerical column value for S1
    if(column1 == "00")
    {
        numColumn1 = 0;
    }
    else if(column1 == "01")
    {
        numColumn1 = 1;
    }
    else if(column1 == "10")
    {
        numColumn1 = 2;
    }
    else if(column1 == "11")
    {
        numColumn1 = 3;
    }

    //cout  << "Sbox 0: row - " << numRow0 
    //      << " column - " << numColumn0 << endl
    //      << "Sbox 1: row - " << numRow1 
    //      << " column - " << numColumn1 << endl;

    

    string output = "";
    int temp0 = tableS0[numRow0][numColumn0];
    int temp1 = tableS1[numRow1][numColumn1];

    //convert the number to binary pair
    switch(temp0)
    {
        case 0:
            output += "00";
            break;

        case 1:
            output += "01";
            break;

        case 2:
            output += "10";
            break;

        case 3:
            output += "11";
            break;

        default:
            cout << "Error in s-box" << endl;
            exit(0);
            break;
    }

    //convert the number to binary pair
    switch(temp1)
    {
        case 0:
            output += "00";
            break;

        case 1:
            output += "01";
            break;

        case 2:
            output += "10";
            break;

        case 3:
            output += "11";
            break;

        default:
            cout << "Error in s-box" << endl;
            exit(0);
            break;
    }



    //cout << "Out sBoxes" << endl;

    return output;
}

void DES::fillTables()
{
    //cout << "In fillTables" << endl;
    
    this->tableP10[0] = 3;
    this->tableP10[1] = 5;
    this->tableP10[2] = 2;
    this->tableP10[3] = 7;
    this->tableP10[4] = 4;
    this->tableP10[5] = 10;
    this->tableP10[6] = 1;
    this->tableP10[7] = 9;
    this->tableP10[8] = 8;
    this->tableP10[9] = 6;

    this->tableP8[0] = 6;
    this->tableP8[1] = 3;
    this->tableP8[2] = 7;
    this->tableP8[3] = 4;
    this->tableP8[4] = 8;
    this->tableP8[5] = 5;
    this->tableP8[6] = 10;
    this->tableP8[7] = 9;

    this->tableIP[0] = 2;
    this->tableIP[1] = 6;
    this->tableIP[2] = 3;
    this->tableIP[3] = 1;
    this->tableIP[4] = 4;
    this->tableIP[5] = 8;
    this->tableIP[6] = 5;
    this->tableIP[7] = 7;

    this->tableInverseIP[0] = 4;
    this->tableInverseIP[1] = 1;
    this->tableInverseIP[2] = 3;
    this->tableInverseIP[3] = 5;
    this->tableInverseIP[4] = 7;
    this->tableInverseIP[5] = 2;
    this->tableInverseIP[6] = 8;
    this->tableInverseIP[7] = 6;

    this->tableEP[0] = 4;
    this->tableEP[1] = 1;
    this->tableEP[2] = 2;
    this->tableEP[3] = 3;
    this->tableEP[4] = 2;
    this->tableEP[5] = 3;
    this->tableEP[6] = 4;
    this->tableEP[7] = 1;

    this->tableP4[0] = 2;
    this->tableP4[1] = 4;
    this->tableP4[2] = 3;
    this->tableP4[3] = 1;

    for(int k = 0; k < 4; k++)
    {
        vector<int> row;
        this->tableS0.push_back(row);
        this->tableS1.push_back(row);
    }

    this->tableS0[0].push_back(1);
    this->tableS0[0].push_back(0);
    this->tableS0[0].push_back(3);
    this->tableS0[0].push_back(2);

    this->tableS0[1].push_back(3);
    this->tableS0[1].push_back(2);
    this->tableS0[1].push_back(1);
    this->tableS0[1].push_back(0);

    this->tableS0[2].push_back(0);
    this->tableS0[2].push_back(2);
    this->tableS0[2].push_back(1);
    this->tableS0[2].push_back(3);

    this->tableS0[3].push_back(3);
    this->tableS0[3].push_back(1);
    this->tableS0[3].push_back(3);
    this->tableS0[3].push_back(2);


    this->tableS1[0].push_back(0);
    this->tableS1[0].push_back(1);
    this->tableS1[0].push_back(2);
    this->tableS1[0].push_back(3);

    this->tableS1[1].push_back(2);
    this->tableS1[1].push_back(0);
    this->tableS1[1].push_back(1);
    this->tableS1[1].push_back(3);

    this->tableS1[2].push_back(3);
    this->tableS1[2].push_back(0);
    this->tableS1[2].push_back(1);
    this->tableS1[2].push_back(0);

    this->tableS1[3].push_back(2);
    this->tableS1[3].push_back(1);
    this->tableS1[3].push_back(0);
    this->tableS1[3].push_back(3);

    //cout << "Out fillTables" << endl;
}


string DES::intToString(int input)
{
    //cout << "In intToString" << endl;
    
    ostringstream ss;
    ss << input;

    //cout << "Out intToString" << endl;

    return ss.str();
}



