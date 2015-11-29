
#include <SimpleMultiArray.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

void fail()
{
	cout << "TEST_FAILED\n";
	exit(1);
}

void test_SimpleMultiArray()
{
	SimpleMultiArray<int> x;
	x.resize(2, 3, 4);
	unsigned n = x.size();
	if (n != 2 * 3 * 4)
		fail();
	int count;
	for (unsigned i = 0; i < 2; i++)
	{
		for (unsigned j = 0; j < 3; j++)
		{
			for (unsigned k = 0; k < 3; k++)
			{
				x(i, j, k) = count;
				count ++;
			}
		}
	}
	x.resize(n);
	if (n != x.size())
	for (unsigned i = 0; i < n; i++)
	{
		if (x[i] != (int)i)
			fail();
	}
	cout << "TEST_PASSED\n";
}

int main(int argc, char *argv[])
{
	test_SimpleMultiArray();
	return 0;
}
