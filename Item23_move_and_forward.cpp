// example 1
class Annotation{
public:
	explicit Annotation(const string text);
	:value(move(text)){ // move will cast 'an lvaue const string' to 'an rvalue const string'
		                // and call the copy constructor of string.
	}
private:
	string value;
};

class string{
public:
	string(const string& rhs); //copy ctor
	string(string&& rhs); //move ctor
};
// Tip1: Do not declare objects const if you want to be able to move from them. 
// Tip2: Move not only does not move anything, it does not guarantee that the object it's casting
// will be eligible to be moved.

// example 2
void process(const Widget& lvalArg);
void process(Widget&& rvalArg);
template<class T>
void logAndProcess(T&& param)
{
	auto now = 
		chrono::system_clock::now();
	makeLogEntry("Calling 'process'", now);
	process(forward(param));
}

Widget w;
logAndProcess(w);       // call with lvalue
logAndProcess(move(w)); // call with rvalue
// There are two very different actions
// The first one sets up a move, while the second one just passes- forward-an object\
// to another function in a way that retains its original lvalueness or rvalueness.


// example 3
void f(Widget&& param); // rvalue reference
Widget&& var1 = Widget(); // rvalue reference
auto&& var2 = var1; // not rvalue reference

template<class T>
void f(vector<T>&& param); // rvalue reference

template<class T>
void f(T&& param); // nor rvalue reference

Widget w;
f(w); // param's type is rvalue reference
f(move(w)) // param's type is lvalue reference

vector<int> v; 
f(v); // error! can not bind lvaue to rvalue reference

template<class T, class Allocator = allocator<T>>
class vector{
	public:
	void push_back(T&& x);
};


vector<Widget> v;
// vector template to be instantiated as follows:
class vector<Widget, allocator<Widget>>{
	public:
	void push_back(Widget& x); // rvalue reference
};

template<class T, class Allocator = allocator<T>>
class vector{
	public:
	template<class... Args>
	void emplace_back(Args&&...args);
};


// example4
class Widget{
public:
Widget(Widget&& rhs) // rhs definitely refers to an object eligible for moving	
		:name(move(rhs.name)),
		p(move(rhs.p)){
			...
		}
	void seteName(T&& newName)
	{
		name = forward<T>(newName); // newName is universal reference
	}
	
	void set_name(T&& newName)
	{
		name = move(newName); // this is bad
	}
private:
	string name;
	shared_ptr<SomeDataStructure> p;
};

string getWidgetName();
Widget w;

auto n = getWidgetName(); // n is local variable

w.setName(n); // moves n into w! n's value now unknown

// example5
class Widget{
public:
Widget(Widget&& rhs) // rhs definitely refers to an object eligible for moving	
		:name(move(rhs.name)),
		p(move(rhs.p)){
			...
		}
	void set_name(const T& newName)
	{
		name = newName; // set from const lvalue
	}
	
	void set_name(T&& newName)
	{
		name = move(newName); // set from rvalue
	}
private:
	string name;
	shared_ptr<SomeDataStructure> p;
};

string getWidgetName();
Widget w;
w.setName("Adela Novak");// a temporary string object would be created for setName's parameter to bind to
//, and this temporary string would then be moved into w's data member.


// example6
template<class T, class... Args>
shared_ptr<T> make_shared(Args&&...args);

template<typename T>
void setSignText(T&& text)
{
	sign.setText(text); // use text , but do not modify it
	auto now = now();
	signHistory.add(now,forward<T>(text)); // conditionally cast text to rvalue
}

// example 7
template<class T>
Fraction
reduceAndCopy(T&& farc)
{
	frac.reduce();
	return forward<T>(frac); // move rvalue into return value, copy lvalue
}

//RVO conditions
// (1) the type of the local object is the same as that returned by the function
// (2) the local object is what's being returned.


// example8
multiset<string> names;
void logAndAdd(const string& name)
{
	auto now = now();
	log(now,"logAndAdd");
	names.emplace(name);
}

sting petName("Darla");
logAndAdd(petName); // pass lvalue
logAndAdd(string("Dog")); // pass rvalue
logAndAdd("Patty dog"); // pass string literal


multiset<string> names;
void logAndAdd(const string& name)
{
	auto now = now();
	log(now,"logAndAdd");
	names.emplace(forward<string>(name));
}

sting petName("Darla");
logAndAdd(petName); // as before, copy lvalue into multiset
logAndAdd(string("Dog")); // move rvalue instead of copying it
logAndAdd("Patty dog"); // creat string in multiset instead of copying a temporay string



// example 9
string nameFromIdx(int idx); // return name corresponding to idx

void logAndAdd(int idx)
{
	auto now = now();
	log(now,"logAndAdd");
	names.emplace(nameFromIdx(idx));
}

sting petName("Darla");
logAndAdd(petName); // as before, copy lvalue into multiset
logAndAdd(string("Dog")); // move rvalue instead of copying it
logAndAdd("Patty dog");
logAndAdd(22); // calls int overload

short nameIdx;
logAndAdd(nameIdx); // error! universal reference overload is a better match for a short argument than an int.

// example 10
class Person{
public:
	template<class T>
	explicit Person(T&& n)
	:name(forward<T>(n)){}
	
	explicit Person(ind idx)
	:name(nameFromIdx(idx)){}
	
private:
	string name;
};

// item17 explains that under the appropriate conditions, C++ 
// will generate both copy and move constructors
class Person{
public:
	template<class T>
	explicit Person(T&& n)
	:name(forward<T>(n)){}
	
	explicit Person(ind idx)
	:name(nameFromIdx(idx)){}
	
	Person(const Person& rhs); // compiler-generated
	Person(Person&& rhs);// move ctor
	
private:
	string name;
};


class Person{
public:
	template<class T>
	explicit Person(Person& n):
	 name(forward<Person&>(n)){} //instantiated from perfect-forwarding template
	
	Person(Person&& rhs);// move ctor
	
private:
	string name;
};

Person p("Nancy");
auto cloneOfP(p); // will not compile. For it will call perfect-forward overload function


class Person{
public:
	template<class T>
	explicit Person(const Person& n):
	 name(forward<Person&>(n)){} //instantiated from perfect-forwarding template
	
	Person(Person&& rhs);// move ctor
	
private:
	string name;
};

const Person cp("Nancy");
auto cloneOfP(cp); // calls copy constructor!


// example 11

multiset<string> names;
template<typename T>
void logAndAdd(T&& name)
{
	logAndAddImlp(forward<T>(name),is_integral<T>()); // NOT quit correct. an lvaue of type int is passed to logAndAdd, T will be deduced to be int&
	                                                  // That means that is_integral<T> will be false
}

// the proper way to write logAndAdd
multiset<string> names;
template<typename T>
void logAndAdd(T&& name)
{
	logAndAddImlp(forward<T>(name),is_integral<typename remove_reference<T>::type>());
}

template<typename T>
void logAndAddImpl(T&& name, std::false_type)
{
	auto now = now();
	log(now,"logAndAdd");
	names.emplace(forward<T>(name));
}

string nameFromIdx(itn idx);

void logAndAddImpl(int idx, std::true_type) //integral
{
	logAndAdd(nameFromIdx(idx));
}

//use enable_if
class Person{
public:
	template<class T,
	         typename = typename std::enable_if<condition>::type>
	explicit Person(T&& n); // condition = !std::is_same<Person>,typename std::decay<T>::type>::value>::type
	...
};