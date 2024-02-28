#ifndef UCLASMVUTILS
#define UCLASMVUTILS

#include "ids.h"

union DoubleCaster//this is for type casting between double and int array
{
    double num;
    uint8_t arr[8];
};

int getIDField(int first, int last)
{
    return (first << 7) + last;
}

int getFirst(int id)
{
    return id << 21 >> 28; 
}

int getLast(int id)
{
    return id << 27 >> 27; 
}

#endif