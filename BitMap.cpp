#include<iostream>
#include<vector>
using namespace std;

typedef unsigned int uint32;
const int SHIFT = 5;
const int MASK = 0x1f;
const uint32 x = 2;
const uint32 MAX_UINT32 = (uint32)pow<uint32>(x, 32) - 1;

// @set function can be used to set one bit to 1 based on the input parameter @value
// for example: @value = 33 = 0x21, and we should set the 32th bit to 1.
// so I should set the bitmap[1]:1 to 1
void set(vector<uint32> &bitmap, uint32 value)
{
	bitmap[value >> SHIFT] |= (1 << (value & MASK));
}

// @test function can be used to test whether input @value is valid in @bitmap
bool test(vector<uint32> &bitmap, uint32 value)
{
	return bitmap[value >> SHIFT] & (1 << (value & MASK));
}

int main()
{

	vector<uint32> bitmap( (MAX_UINT32 >> SHIFT) + 1,0);
	
	uint32 a[] = { 1, 3, 2, 200000000, 1000, 20 };
	for (size_t i = 0; i < sizeof(a)/sizeof(int); i++)
	{
		set(bitmap, a[i]);
	}
	for (size_t i = 0; i < MAX_UINT32; i++)
	{
		if (test(bitmap,i))
		{
			cout << i << endl;
		}
	}
	return 0;
}