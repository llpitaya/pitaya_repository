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
// 如果需要一个类支持列表初始化，需要让该类的构造函数和拷贝构造函数支持列表初始化，
// 即让它们支持初始化列表数据类型
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

// vector<bool> 中存储的并非是bool,为了节省空间，在内存中每个元素仅占
// 1个bit。因为C++不允许直接引用位，所以vector<bool>使用代理类来模拟bool&
// vector<bool> v; bool * b = &v[0];bool& refb = vb[0];
// 以上操作不能通过编译
void test_vector_bool()
{
	vector<bool> c{ false, true, false, true, false }; //0,1,0,1,0
	for (auto i : c)
		cout << i << " ";            //输出0 1 0 1 0
	cout << endl;
	for (auto i : c){
		i = !i;
	}
	for (auto i : c)
		cout << i << " ";            //输出1 0 1 0 1
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