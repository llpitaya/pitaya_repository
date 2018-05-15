#include<iostream>
#include<vector>
using namespace std;

void testUniformInit()
{
	int a[]{0, 1, 2, 3};
	int a_[] = { 0, 1, 2, 3 };
	vector<int> v{ 0, 1, 2, 3 };
	vector<int> v_(4, 0);
	int ival(3.5);
	// int ival_{3.5}; Error
	// int v_{1,1.0,2}; Error
	// it is illeagal in c++11, because the narrowing initialization is required with braces.
}

void print(initializer_list<int> vals)
{
	for (auto val : vals)
	{
		cout << val << endl;
	}

}

void print1(initializer_list<int> vals)
{
	for (auto p = vals.begin(); p != vals.end();++p)
	{
		cout << *p << endl;
	}
}

// range-based for loops
template<class T>
void printElements(const T& coll)
{
	for (const auto& elem : coll)
	{
		cout << elem << endl;
	}
}
// �����Ҫһ����֧���б��ʼ������Ҫ�ø���Ĺ��캯���Ϳ������캯��֧���б��ʼ����
// ��������֧�ֳ�ʼ���б���������
class Base
{
public:
	Base(int x, int y)
	{
		cout << "Base(int x, int y)" << endl;
	}

	Base(initializer_list<int> vals)
	{ 
		cout << "Base(initializer_list<int> vals)" << endl; 
	}
};

// vector<bool> �д洢�Ĳ�����bool,Ϊ�˽�ʡ�ռ䣬���ڴ���ÿ��Ԫ�ؽ�ռ
// 1��bit����ΪC++������ֱ������λ������vector<bool>ʹ�ô�������ģ��bool&
// vector<bool> v; bool * b = &v[0];bool& refb = vb[0];
// ���ϲ�������ͨ������
void test_vector_bool()
{
	vector<bool> c{ false, true, false, true, false }; //0,1,0,1,0
	for (auto i : c)
		cout << i << " ";            //���0 1 0 1 0
	cout << endl;
	for (auto i : c){
		i = !i;
	}
	for (auto i : c)
		cout << i << " ";            //���1 0 1 0 1
	cout << endl;
}
int main()
{
	//testUniformInit();
	//print({ 0, 1, 2, 3, 4 });
	//Base b{ 0, 1, 2 };
	vector<bool> bvec;
	bvec.push_back(1);
	bvec.push_back(0);
	bvec.push_back(1);
	//printElements(bvec);
	bool b = *(bvec.begin());
	cout << b << endl;
	//test_vector_bool();
	return 0;
}