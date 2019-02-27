// Common properties between platforms
/*
unsigned int backBuffer[128][8];

void setPixel(int x, int y, int set)
{
	// Checks for valid range
	if (x < 0 || x > 127 || y < 0 ||y > 63)
	{
		return;
	}
	
	int page = y / 8;
	int pixel = y % 8;
	
	if (set == 0)
	{
		backBuffer[x][page] &= ~(1<<pixel);
	}
	else
	{
		backBuffer[x][page] |= (1<<pixel);
	}
}*/