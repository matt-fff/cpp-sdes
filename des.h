/*
    File: des.h
    Author: Matthew White
    Contains the DES class and prototypes
*/
/*
    Class: DES
    A simple S-DES encryption implementation.

    Constructor: DES(string key, string text, bool encrypt)
    Initiates the tables, creates the subkeys, sets m_key equal to key,
    and either m_text or m_ciphertext equal to text depending on the value
    of encrypt.

        Parameters:
        key - the binary key of the user's choosing. Characters limited to 1's and 0's.
        text - either the ciphertext or the text of the user's choosing. 
                Characters limited to 1's and 0's.
        encrypt - true if the encrypt flag was used, false if the decrypt flag was used

    Function: string encrypt()
    Calculates the ciphertext using the pre-loaded keys and plaintext

        Returns:
        The ciphertext.

    Function: string encrypt()
    Calculates the plaintext using the pre-loaded keys and ciphertext

        Returns:
        The plaintext.

    Function: string P10(string input)
    Permutes the input based on the tableP10

        Parameters:
        input - the text to be altered. Characters limited to 1's and 0's.

        Returns:
        The permuted input.

    Function: leftShift(string input)
    Divides the input into halves, independently shifts each half left by one
    character, and concatenates the two halves back together.

        Parameters:
        input - the text to be altered. Characters limited to 1's and 0's.

        Returns:
        The result of shifting both halves one character left.

    Function: string P8(string input)
    Permutes the input based on the tableP8

        Parameters:
        input - the text to be altered. Characters limited to 1's and 0's.

        Returns:
        The permuted input.

    Function: void createKeys()
    Uses the preloaded key to generate the subkeys k1 and k2

    Function: string IP(string input)
    Permutes the input based on the tableIP

        Parameters:
        input - the text to be altered. Characters limited to 1's and 0's.

        Returns:
        The permuted input.

    Function: string inverseIP(string input)
    Permutes the input based on the tableInverseIP

        Parameters:
        input - the text to be altered. Characters limited to 1's and 0's.

        Returns:
        The permuted input.

    Function: string fK(string input, string subKey)
    Does the bulk of the encryption. Uses permutations, XOR's, and s-Boxes
    to encrypt the input.

        Parameters:
        input - the text to be altered. Characters limited to 1's and 0's.
        subKey - the subKey to be used (will be either k1 or k2)

        Returns:
        The altered input.

    Function: string SW(string input)
    Splits the input into two halves and swaps their positions.

        Parameters:
        input - the text to be altered. Characters limited to 1's and 0's.

        Returns:
        The altered input (the last half will be first and the first half will be last)

    Function: string XOR(string one, string two)
    XORs one against two and returns the result

        Parameters:
        one - the first string to be XORed.  Characters limited to 1's and 0's.
        two - the second string to be XORed.  Characters limited to 1's and 0's.

        Returns:
        The result of XORing one and two.

    Function: string sBoxes(string input)
    Applies the S0 and S1 s-boxes to the input and outputs the result.

        Parameters:
        input - the text to be altered.  Characters limited to 1's and 0's.

        Returns:
        The result of applying the s-boxes to input.

    Function: void fillTables()
    Populates all the tables and vectors found in the data section of
    the DES class.

    Function: string intToString(int input)
    Returns the string equivalent of a given integer

        Parameters:
        input - the integer to be converted

        Returns:
        The string equivalent of input

*/

#ifndef DES_H
#define DES_H
#include <string>
#include <vector>

using namespace std;

class DES
{
    public:
    DES(string key, string text, bool encrypt);
    string encrypt();
    string decrypt();

    private:
    //key generation functions
    string P10(string input);
    string leftShift(string input);
    string P8(string input);
    void createKeys();

    //encryption functions
    string IP(string input);
    string inverseIP(string input);
    string fK(string input, string subKey);
    string SW(string input);

    //misc functions
    string XOR(string one, string two);
    string sBoxes(string input);
    void fillTables();
    string intToString(int input);

    //data
    string m_key;
    string m_k1;
    string m_k2;
    string m_text;
    string m_ciphertext;
    int tableP10[10];
    int tableP8[8];
    int tableIP[8];
    int tableInverseIP[8];
    int tableEP[8];
    int tableP4[4];
    vector< vector<int> > tableS0;
    vector< vector<int> > tableS1;
};

#endif

