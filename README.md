This repo implements the SSS algorithm for storing my private keys.

To generate the twelve word recovery phrase for my bitcoin wallet you will need two shares, which should be stored in the files first.txt and second.txt

Once you have the two shares, generate and run the code as follows:

g++ recover.cpp && ./a.out

which will print the recovery phrase without spaces between words.

This code works with c++17, and should hopefully be supported for a long time.
