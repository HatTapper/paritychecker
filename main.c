// check for even parity
// there should be an even number of 1 bits in the bit sequence + parity bit

#include <stdio.h>

#define NOPARITYBIT -1

// returns 1 if bit = 1, returns 0 if bit = 0
int bitCheck(unsigned int number, unsigned int bitIndex)
{
    return (number >> bitIndex) & 1;
}


int getParity(unsigned int num)
{
    // find if bit sequence is odd parity, if so, add parity bit 1
    // if bit sequence is even parity, add parity bit 0
    int activeBits = 0;
    for(unsigned int i = 0; i < sizeof(num) * 8; i++)
    {
        activeBits += bitCheck(num, i);
    }

    return activeBits;
}

// "receive" data and check if it has an even parity
// if so, return 1 to verify data is correctly received
// else, return 0 to warn that data is not correctly received
int dataVerifier(int data[2])
{
    // check if data has even parity and parity bit is set to 0
    if(getParity(data[0]) % 2 == 0 && data[1] == 0)
        return 1;
    // if data is odd parity, check if parity bit is set to 1
    else if(data[1] == 1)
        return 1;
    // if data is odd parity with the parity bit, return 0
    else
        return 0;
}


int main()
{
    printf("1. %d\n", getParity(15)); // expect 4
    printf("2. %d\n", getParity(1)); // expect 1
    printf("3. %d\n", getParity(16)); // expect 1
    printf("4. %d\n", getParity(32)); // expect 1
    printf("5. %d\n\n", getParity(31)); // expect 5

    // TEST 1: Data is correctly transmitted, expect it to be received correctly.
    int dataToSend[2] = {31, NOPARITYBIT};
    if(getParity(dataToSend[0] % 2 != 0))
        dataToSend[1] = 1;
    else 
        dataToSend[1] = 0;

    if(dataVerifier(dataToSend))
        printf("Data was correctly received.\n");
    else
        printf("Data was incorrectly received.\n");

    // TEST 2: Data is "damaged" during transit, expect it to be received incorrectly.
    int damagedData[2] = {7, 0};

    if(dataVerifier(damagedData))
        printf("Data was correctly received.\n");
    else
        printf("Data was incorrectly received.\n");
    
    return 0;
}