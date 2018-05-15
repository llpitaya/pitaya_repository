#include<iostream>
using namespace std;
void f(int)
{
	cout << "f(int)" << endl;
}

void f(void *)
{
	cout << "f(void *)" << endl;
}

// main function
int main()
{
	f(nullptr);
	f(2);
	return 0;
}