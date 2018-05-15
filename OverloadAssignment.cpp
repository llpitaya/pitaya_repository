#include<iostream>
#include<string>
using namespace std;
class Base
{
public:
	Base(){ 
		_id = 0; 
		_name = nullptr;
		cout << "Base()" << endl;
	}

	Base(int idx, const char *str){
		cout << "Base(int idx, const char *str)" << endl;
		_id = idx;
		_name = new char[strlen(str) + 1];
		strcpy_s(_name, strlen(str) + 1, str);
	}

	Base(const Base& rhs)
	{
		cout << "Base(const Base& rhs)" << endl;
		_id = rhs._id;
		if (_name != nullptr)
		{
			delete[] _name;
		}
		_name = new char[strlen(rhs._name) + 1];
		strcpy_s(_name, strlen(rhs._name) + 1, rhs._name);
	}

	Base(Base&& rhs) :_name(move(rhs._name)), _id(move(rhs._id))
	{
		cout << "Base(Base&& rhs)" << endl;
	}

	Base& operator=(const Base& rhs)
	{
		cout << "Base& operator=(const Base& rhs)" << endl;
		if (this!=&rhs)
		{
			_id = rhs._id;
			_name = new char[strlen(rhs._name) + 1];
			strcpy_s(_name, strlen(rhs._name) + 1, rhs._name);
		}
		return *this;
	}

	~Base()
	{
		cout << "~Base()" << endl;
		if (_name!=nullptr)
		{
			delete[] _name;
		}
	}
private:
	int _id;
	char * _name;
};

Base fun1()
{
	Base b;
	return b;
}

void fun2(Base b)
{
	
}


void fun3(char a[])
{
	cout << sizeof(a) << endl;
	cout << strlen(a) << endl;
}
void fun4(const int & x){

}
int main()
{
	//Base b(0, "123");
	//Base a;
	//Base c = a = b;
	//fun4(3);
	Base b(0, "123");
	Base c(forward<Base>(b));
	b.~Base();
	return 0;
}


