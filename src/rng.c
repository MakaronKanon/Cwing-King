//#include "stdio.h"



/*
int main()
{

    for (int i = 0; i < 50; i++)
    {
        unsigned int randNum = genRandomNum();
        setSeed(i);
        printf("Rand num is %u\n", randNum % 64);
    }

    return 0;
}*/

int seed = 0xda1ce2a9;
int x = 0;
int w = 0;

void setSeed(unsigned int newSeed)
{
    seed = newSeed;
}

unsigned int genRandomNum()
{   
    x *=x;
    w += seed;
    x += w;
    return (x>>16) | (x << 16);
}