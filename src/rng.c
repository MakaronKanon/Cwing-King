static int seed = 0xda1ce2a9;
static int x = 0;
static int w = 0;

void setSeed(unsigned int newSeed)
{
    seed = newSeed;
}

unsigned int genRandomNum()
{   
    x *= x;
    w += seed;
    x += w;
    return (x>>16) | (x << 16);
}