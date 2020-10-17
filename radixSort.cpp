// Radix Sort

#include<list>
using namespace std;
struct Rad
{
	x40 s, r;
	Rad(x40 a = 0, x40 b = 0) : s(a), r(b) {}
};
void RadixSort(list<Rad> &v)
{
	int count = 0;
	do
	{
		list<Rad> L[10];
		count = 0;
		while (v.empty() != true)
		{
			Rad i = v.front();
			int temp = i.r % 10;
			i.r = i.r / 10;
			L[temp].push_back(i);
			v.pop_front();
			if (count == 0)
				if (i.r != 0)
					count++;
		}
		for (int i = 0; i < 10; i++)
		{
			while (L[i].empty() == false)
			{
				v.push_back(L[i].front());
				L[i].pop_front();
			}
		}
	} while (count);
	return;
}
