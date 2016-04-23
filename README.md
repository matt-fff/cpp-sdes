# cpp-des
C++ DES symmetric encryption implementation.

This is a simple [DES](https://en.wikipedia.org/wiki/Data_Encryption_Standard) implementation. Currently, it only handles specific sizes of binary input. Further wrapping of the internals to make the utility handle arbitrary lengths and types of input would be required to make the encryption practical rather than academic.

Compilation:

    g++ -o sdes *.cpp

Usage:

    ./sdes (-e|-d) key message
      -e to encrypt
      -d to decrypt
      -e and -d are mutually exclusive
      key must be 10 bits in binary, e.g. 1010101010
      text must be 8 bits in binary, e.g. 11111111
