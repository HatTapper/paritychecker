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

typedef struct DataPacket
{
    int data;
    int parityBit;
} DataPacket;



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
int dataVerifier(DataPacket* dataPacket)
{
    // check if data has even parity and parity bit is set to 0
    if(getParity(dataPacket->data) % 2 == 0 && dataPacket->parityBit == 0)
        return 1;
    // if data is odd parity, check if parity bit is set to 1
    else if(dataPacket->parityBit == 1)
        return 1;
    // if data is odd parity with the parity bit, return 0
    else
        return 0;
}


// mimics sending of data from a different location by using a separate thread to initialize and transmit data to the original thread
void* sendData(void* dataBuffer)
{
    ((DataPacket*)dataBuffer)->data = 24;
    if(getParity(((DataPacket*)dataBuffer)->data % 2 != 0))
        ((DataPacket*)dataBuffer)->parityBit = 0;
    else 
        ((DataPacket*)dataBuffer)->parityBit = 1;

    return NULL;
}

void* sendBadData(void* dataBuffer)
{
    ((DataPacket*)dataBuffer)->data = 2;
    ((DataPacket*)dataBuffer)->parityBit = 0;

    return NULL;
}



int main(void)
{
    // struct to act as a location for data to be sent to
    DataPacket correctData;
    // create thread to simulate sending of data
    pthread_t threadId;
    pthread_create(&threadId, NULL, sendData, &correctData);
    pthread_join(threadId, NULL);
    

    if(dataVerifier(&correctData))
        printf("Data was correctly received.\n");
    else
        printf("Data was incorrectly received.\n");

    
    // intentionally incorrect data
    DataPacket badData;

    pthread_create(&threadId, NULL, sendBadData, &badData);
    pthread_join(threadId, NULL);

    if(dataVerifier(&badData))
        printf("Data was correctly received.\n");
    else
        printf("Data was incorrectly received.\n");


    return 0;
}