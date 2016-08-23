# cpp-des
This is a C++ implementation of Simplified [DES](https://en.wikipedia.org/wiki/Data_Encryption_Standard). It only handles binary input of specific bit count. Further wrapping of the internals to make the utility handle arbitrary lengths and types of input would be required to make the encryption usable - but SDES is [inherently academic](https://en.wikipedia.org/wiki/Data_Encryption_Standard#Simplified_DES).

Compilation:

    g++ -o sdes *.cpp

Usage:

    ./sdes (-e|-d) key message
      -e to encrypt
      -d to decrypt
      -e and -d are mutually exclusive
      key must be 10 binary bits, e.g. 1010101010
      text must be 8 binary bits, e.g. 11111111
