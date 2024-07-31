// goals:
/*
 - implement multithreading as a means of testing
 - optimize! (using bitwise AND?)
*/


// check for even parity
// there should be an even number of 1 bits in the bit sequence + parity bit

#include <stdio.h>
#include <pthread.h>

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


// mimics sending of data from a different location by using a separate thread to initialize and transmit data to the original thread
int* sendData(void)
{
    int dataToSend[2] = {31, NOPARITYBIT};
    if(getParity(dataToSend[0] % 2 != 0))
        dataToSend[1] = 1;
    else 
        dataToSend[1] = 0;

    return 31, 0;
}



int main(void)
{
    // ptr to store location of data array
    int* pdata;
    // create thread to simulate sending of data
    pthread_t threadId;
    pthread_create(&threadId, NULL, sendData, NULL);
    pthread_join(threadId, pdata);
    // dereference data

    if(dataVerifier(newData))
        printf("Data was correctly received.\n");
    else
        printf("Data was incorrectly received.\n");

    return 0;
}