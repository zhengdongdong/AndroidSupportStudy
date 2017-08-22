#define _CRT_SECURE_NO_WARNINGS
/*
C与C++的关系
1.C++可以与C代码进行混编
2.C++面向对象编程语言, C面向过程的编程语言
3.C++是对C的一个增强
*/


/******************预览*******************/
/*
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

// 使用命名空间
// 类似于 Java 中的包名(归类)
using namespace std;

// 自定义命名空间
namespace NSP_A{
	int a = 9;
}
namespace NSP_B{
	int a = 10;
	// 命名空间嵌套 -- 不推荐这样写
	namespace NSP_C{
		int a = 11;
	}
}
// 命名空间中的结构体
namespace NSP_C{
	struct Teacher
	{
		char* name;
		int age;
	};
}

void main(){
	// c 输出方法
	printf("this is c++\n");

	// c++ 输出方法 <iostream>
	// 加入命名空间(std -- standard 标准命名空间,包含很多标准的定义)
	//		<< 运算符重载
	// std::cout << "this is c++\n" << std::endl;

	// 使用 using namespace
	cout << "this is c++" << endl;

	// 使用自定义命名空间
	// :: 访问符, 相当于Java中的.
	cout << "空间A:" << NSP_A::a << endl;
	cout << "空间B->C:" << NSP_B::NSP_C::a << endl;

	// 命名空间中的结构体
	// struct NSP_C::Teacher t1; 
	NSP_C::Teacher t1; // struct 写与不写都可以
	t1.age = 10;

	//using namespace NSP_C;
	using NSP_C::Teacher;
	Teacher t;
	t.name = "abc";
	t.age = 10;

	system("pause");
}
*/

/*******************数据类型******************/
/*
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;
void main(){
	// C++ 多了bool
	// bool isTrue = true;
	// bool isTrue = 100;// 大于0都是 true
	bool isTrue = 0;

	cout << sizeof(bool) << endl;

	if (isTrue){
		cout << "是的:" << endl;
	}
	else{
		cout << "不是的" << endl;
	}

	// 三元表达式在C++中可以表示左值
	int a = 10, b = 20;
	((a > b) ? a : b) = 30;
	// b = 30
	cout << b << endl;

	system("pause");
}
*/

/*********************类*********************/
/*
#define PI 3.14

class Circle{
	// 属性
private: // 权限访问修饰符 -- 共用
	double r;
	double s;
public:
	double l;
	// 方法
public:
	void setR(double r){
		this->r = r;
	}
	double getS(){
		return PI*r*r;
	}
};

// 结构体在C++中也有了访问修饰符
struct Teacher
{
private:
	int age = 10;
public:
	void say(){
		cout << age << "岁" << endl;
	}
};

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

void main(){
	// 类: 可以直接使用
	Circle circle;
	circle.setR(4);
	cout << "圆的面积:" << circle.getS() << endl;

	// 结构体, 与类不同在于不能继承
	Teacher teacher;
	teacher.say();

	system("pause");
}
*/


/******************引用*****************/
// 引用的主要功能 : 作为函数的参数或返回值, 操作起来比指针方便
// 1. 单纯给变量起别名没有任何意义, 作为函数参数传递, 能保证参数传递过程中不产生副本
// 2. 引用可以直接操作变量, 而指针要通过取值(*p), 间接操作变量, 指针可读性差
/*
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

// 作为函数参数
void swap(int &a, int &b){
	// 交换 a,b 的值
	int c = 0;
	c = a;
	a = b;
	b = c;
}

struct Teacher{
	char* name;
	int age;
};
// 指针写法
void getTeacher(Teacher **p){
	Teacher *tmp = (Teacher*)malloc(sizeof(Teacher)); // 申请内存
	tmp->age = 20;
	*p = tmp;
}
// 指针的引用写法(Teacher* &p 代替二级指针  Teacher* &p = (Teacher* *p))
void getTeacher(Teacher* &p){
	p = (Teacher*)malloc(sizeof(Teacher)); // 申请内存
	p->age = 20;
}

// 常引用
void myPrint(const int &a){
	// 类似于 java 中的 final
	cout << a << endl;
}

void main(){
	int a = 10;
	// & 在 C++ 中表示引用(表示变量的别名), 和指针一样, 都是操作内存地址
	// 引用的 & 写在变量声明时
	// 引用必须要有值, 不能为空
	// int &a = NULL; // 错误
	int &b = a;
	int *c = &a;

	cout << b << endl;
	cout << *c << endl;

	int x = 10;
	int y = 20;
	printf("%d, %d\n", x,y);
	swap(x, y);
	printf("%d, %d\n", x,y);

	// 指针写法
	Teacher *t = NULL;
	getTeacher(t);
	cout << t->age << endl;

	Teacher *t1 = NULL;
	getTeacher(&t1);
	cout << t1->age << endl;

	// 常引用
	int a = 10, b = 9;
	const int &c = a;
	// c = b; // 错误

	// 常引用字面量写法
	const int &d = 10;

	system("pause");
}
*/

/********************指针常量/常量指针**********************/
/*
#include <stdlib.h>
#include <stdio.h>

void main(){
	int a = 2, b = 3;
	// 指针常量: 不改变地址的指针, 但是可以修改指向的内容
	int *const p1 = &a;
	// p1 = &b; // 错误 地址不可改变
	*p1 = 20; // 正确 可以改变内容

	// 常量指针: 指向常量的指针, 内容不可修改, 可以改变地址
	const int *p2 = &a;
	p2 = &b; // 正确 可以改变地址
	// *p2 = 10; // 错误 不可改变内容

	system("pause");
}
*/

/*********************函数******************/
/*
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <stdarg.h>

using namespace std;

// 函数可以有默认值(有默认值的参数只能在最后)
void add(int x = 1, int y = 2){
	cout << x + y << endl;
}
// 会导致调用时的重载问题
//void add(int x, int y = 10, int z =20){}

// 可变参数(java 是 int...)
void func(int x, ...){
	// 可变参数指针, ... 开始
	va_list args;
	// 读取, 从最后一个固定参数x
	va_start(args, x);
	// 第二个参数类型, 类型要自己控制
	int a = va_arg(args, int);
	cout << a << endl;
	// 读取结束
	va_end(args);
}

void main(){
	add();
	add(5);

	func(9);
	func(9,10);

	system("pause");
}
*/

/****************类的写法****************/
/*
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "MyTeacher.h"

using namespace std;

// c++中的类, 声明在.h文件中, 实现在 .cpp 中

void main(){
	MyTeacher t1;
	t1.name = "Json";
	// t1.setName("Jack"); 这样调会有问题, 下面构造函数理解
	t1.setAge(10);

	cout << t1.getName() << t1.getAge() << endl;

	system("pause");
}
*/

/****************构造函数/析构函数/拷贝构造函数*****************/
/*
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;
// 构造函数
class Teacher{
private:
	char* name;
	int age;
public:
	// 无参构造函数, 默认(没有其他构造函数时)只要创建了对象, 就会调用无参构造函数
	Teacher(){
		cout << "无参构造函数" << endl;
	}
	// 有参构造函数, 会覆盖默认的无参构造函数
	Teacher(char* name, int age){
		this->name = name;
		this->age = age;
		cout << "调用有参构造函数" << endl;
	}
};
// 析构函数
class Student{
private:
	char* name;
	int age;
public:
	Student(){
		this->name = (char*)malloc(100);
		strcpy(name, "jack");
		age = 20;
		cout << "无参构造函数" << endl;
	}
	// 析构函数, 当对象要被释放时调用
	// 作用 : 善后
	~Student(){
		// 释放内容
		free(this->name);
		cout << "析构函数" << endl;
	}
};
// 拷贝构造函数
// 浅拷贝 : 拷贝指针的地址
// 深拷贝 : 拷贝指针指向地址的内容
class Person{
private:
	char* name;
	int age;
public:
	Person(char* name, int age){
		this->name = (char*) malloc(100);
		strcpy(this->name, name); // 这种情况使用默认拷贝构造函数会有问题
		this->age = age;
		cout << "调用有参构造函数" << endl;
	}
	
	// 拷贝构造函数(值拷贝,用处很多,如集合)
	// 默认拷贝构造函数就是如下做法, 这是一种浅拷贝
	//Teacher(const Teacher &obj){
	//	this->name = obj.name;
	//	this->age = obj.age;
	//	cout << "拷贝构造函数" << endl;
	//}

	// 拷贝构造函数被调用场景(最基本的就是声明时被赋值时调用(t = t1 不算), 和java的clone类似)
	// 1. 声明时赋值  Teacher t = t1;
	// 2. 作为参数传入, 实参传递给形参 func(t)
	// 3. 作为函数返回值返回给变量初始化赋值 Teacher t = func();
	Person(const Person &obj){
		// 深拷贝
		int len = strlen(obj.name);
		this->name = (char*)malloc(len + 1);;
		strcpy(this->name, obj.name);
		this->age = obj.age;
		cout << "拷贝构造函数" << endl;
	}
	~Person(){
		free(this->name);
		cout << "析构函数" << endl;
	}
	void myPrint(){
		cout << name << " , " << age << endl;
	}
};
void func(){
	Student s2;
}
void func2(){
	// 若使用默认拷贝构造函数, func2()函数结束, Person的析构函数会被调用2次,  相当于一段内存释放两次
	// 所以, 使用默认拷贝构造函数进行浅拷贝会出现内存问题
	Person t4("ack", 20);
	Person t5 = t4; // 这时拷贝构造函数被调用
	t5.myPrint();
}
void main(){
	// Teacher t1;
	// Teacher t2("yuan", 20);
	// Teacher t3 = Teacher("jack", 20);

	// func(); // func被执行完毕的时候, 析构函数被调用

	func2();

	system("pause");
}
*/


/********************构造函数的属性初始化列表(属性对象赋值)***********************/
/*
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

class Teacher{
private:
	char* name;
public:
	Teacher(char* name){
		this->name = name;
		cout << "Teacher 有参构造函数" << endl;
	}
	~Teacher(){
		cout << "Teacher 析构函数" << endl;
	}
	char* getName(){
		return this->name;
	}
};

class Student{
private:
	int id;
	Teacher teacher_1;  // 属性对象
	Teacher teacher_2;
	Teacher teacher_3;
public:
									// 给属性对象 Teacher 构造函数传值, 多个用逗号分隔
	Student(int id, char* t_name) : teacher_1(t_name), 
									teacher_2(t_name),
									teacher_3("lala"){ 
		this->id = id;
		cout << "student 构造函数" << endl;
	}
	~Student(){
		cout << "student 析构函数" << endl;
	}
	void printModel(){
		cout << id << "," << teacher_1.getName() << endl;
	}
};

void main(){
	Student student(10, "Jsssson");
	student.printModel();
	system("pause");
}
*/


/******************new/delete**********************/
/*
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

class Teacher{
private:
	char* name;
public:
	char* getName(){
		return this->name;
	}
};

void main(){
	// ******类******
	// C++ 写法  和 malloc 一样
	Teacher *t1 = new Teacher(); 
	// new 出来的需要 delete 释放内存
	delete t1;

	// C 写法
	Teacher *t2 = (Teacher*)malloc(sizeof(Teacher));
	free(t2);

	// *****数组*****
	// c
	int *p1 = (int*)malloc(sizeof(int)* 10);
	p1[0] = 9;
	free(p1);
	
	// C++
	int *p2 = new int[10];
	p2[0] = 2;
	delete[] p2;  // 释放数组需要加上这个括号 ******

	system("pause");
}
*/


/************************static**************************/
/*
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

class Teacher{
private:
	char* name;
public:
	// 静态属性
	static int total; // 不能直接初始化
	Teacher(char* name){ // 不能在构造函数中初始化
		this->name = name;
	}
	// 静态方法
	static void count(){
		total++;
		cout << total << endl;
	}
};

// 静态属性初始化必须在外部
int Teacher::total = 9;

void main(){
	// 访问方式一
	Teacher t1("jack");
	cout << t1.count << endl;

	// 访问方式二
	Teacher::total++;
	cout << Teacher::total << endl;

	Teacher::count();

	system("pause");
}
*/

/*************************类的大小*************************/
/*
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

class A{
public:
	int a;
	int b;
	int c;
	static int d;
};
class B{
public:
	int a;
	int b;
	int c;
	void printModel(){  // 相当于函数指针 void(*printModel)() = printModel; 指针是4个字节, 实际不占内存

	}
};

void main(){
	cout << sizeof(A) << endl; // 12
	cout << sizeof(B) << endl; // 12

	// c/c++ 内存分区: 栈, 堆, 全局(静态, 全局), 常量区(字符串), 程序代码
	// 只有普通属性与结构体相同的内存分布
	// 静态属性(静态区) 和 方法(代码区)不计算在类之内

	system("pause");
}
*/

/**********************this*********************/
// 函数是共享的, 必须要有能够标识当前对象是谁的办法 -> this
// this 是一个常量指针 Teacher *const this
/*
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

class Teacher
{
public:
	Teacher(char* name, int age);
	~Teacher();
	void printModel(){
		printf("%#x\n", this);
		cout << this->name << " , " << this->age << endl;
	}

	// 常函数 修饰的是this
	// 保证数据安全
	void constFunc() const{ // 常函数内部不能修改this/属性的值 
		// const Teacher* const this
		// this->name = "ds";
	}
private:
	char* name;
	int age;
};

Teacher::Teacher(char* name, int age)
{
	this->name = name;
	this->age = age;
}
Teacher::~Teacher()
{
}

void main(){
	Teacher t1("abc", 10);
	t1.printModel();
	printf("%#x\n", t1);

	t1.constFunc(); // 非常量对象可以调用常量函数
	// 调用常函数
	const Teacher t2("cs", 22);
	// t2.printModel(); 常量对象不能调用非常量函数
	t2.constFunc();

	system("pause");
}
*/

/***********************友元函数**************************/
// 友元函数中可以访问类的私有属性
/*
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

class A{
private:
	int i;
public:
	A(int i){
		this->i = i;
	}

	void printModel(){
		cout << i << endl;
	}
	// 声明友元函数
	friend void modifyI(A*p, int a);
};

// 实现友元函数
void modifyI(A*p, int a){
	p->i = a;
}

void main(){
	A *a = new A(10);
	a->printModel();

	modifyI(a, 20);
	a->printModel();

	system("pause");
}
*/

/********************友元类**********************/
/*
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

// 友元类
class A{
	friend class B;
private:
	int i;
public:
	A(int i){
		this->i = i;
	}
	void printModel(){
		cout << i << endl;
	}
};

class B{
private:
	A a;
public:
	// B 这个友元类可以访问A类的任何成员
	void accessAny(){
		a.i = 30;
	}
};

void main(){


	system("pause");
}
*/


/******************运算符重载********************/
/*
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

class Point{
public:
	int x;
	int y;
	Point(int x = 0, int y = 0){
		this->x = x;
		this->y = y;
	}
	void printModel(){
		cout << this->x << " , " << this->y << endl;
	}
	// 和下面一样
	//Point operator+(Point &p2){
	//	Point tmp(this->x + p2.x, this->y + p2.y);
	//	return tmp;
	//}
};
// 重载+号
Point operator+(Point &p1, Point &p2){
	Point tmp(p1.x + p2.x, p1.y + p2.y);
	return tmp;
}

void main(){
	Point p1(100, 200);
	Point p2(200, 300);

	Point p3 = p1 + p2;
	system("pause");
}
*/

/*************************继承************************/
/*
基类中      继承方式             子类中
public     ＆ public继承        => public
public     ＆ protected继承     => protected   
public     ＆ private继承       => private

protected  ＆ public继承        => protected
protected  ＆ protected继承     => protected   
protected  ＆ private继承       => private

private    ＆ public继承        => 子类无权访问
private    ＆ protected继承     => 子类无权访问
private    ＆ private继承       => 子类无权访问
*/

/*
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

class Human{
public:
	Human(char* name, int age){
		this->name = name;
		this->age = age;
	}
	void say(){
		cout << "说话" << endl;
	}
private:
	char* name;
	int age;
};
// 继承于人类
// 只有public类型才能由子类对象访问到父类方法/属性, 子类内部不影响访问
class Man : public Human{
public:
	Man(char* name, int age) : Human(name, age){

	}
	void chasing(){
		cout << "泡妞" << endl;
	}
	void say(){
		cout << "男人说话" << endl;
	}
};

void main(){
	Man m("jj", 20);
	m.say(); // 重写父类方法
	m.Human::say();// 调用父类的方法
	m.chasing();

	//Human* hp = &m;
	//hp->say();

	//Human &h1 = m;
	//h1.say();

	system("pause");
}
*/

/*********************多继承-虚类******************/
/*
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

//class Person{
//public:
//	char* name;
//};
//class Citizen{
//	char* name;
//};
//// 多继承
//class Student :public Person, public Citizen{
//	void say(){
//		// 多继承存在二义性
//		// cout << name << endl; // 错误
//		cout << Person::name << endl;
//	}
//};
class A{
public:
	char* name;
};
// 虚继承 解决二义性
class B :virtual public A{

};
class C :virtual public A{

};
// 多继承
class Student : public B, public C{
	void say(){
		cout << name << endl;
	}
};
void main(){

	system("pause");
}
*/

/************************多态-虚函数**********************/
// 要实现多态, 父类声明时需加入 virtual 关键字

// 静态多态 : 函数重载
// 动态多态 : 程序运行过程中, 觉得哪个函数被调用(子类重写父类)

// 发生多态的条件
// 1. 继承
// 2. 父类的引用指向或指针指向子类的对象
// 3. 函数重写
/*
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

class Plane{
public:
	// 没有实现多态的方式
	void fly(){
		cout << "飞机起飞" << endl;
	}
	// 实现多态的方式
	virtual void land(){
		cout << "飞机降落" << endl;
	}
};
class Jet :public Plane{
	// 没有实现多态的方式
	void fly(){
		cout << "直升飞机起飞" << endl;
	}
	// 实现多态的方式 -- 子类加不加 virtual 貌似都可以
	virtual void land(){
		cout << "直升飞机降落" << endl;
	}
};

void bizPlay(Plane& p){
	// 没有实现多态的方式
	p.fly();
	// 实现多态的方式
	p.land();
}

void main(){
	Plane p1;
	bizPlay(p1); // 飞机起飞  飞机降落

	Jet p2;
	bizPlay(p2); // 飞机起飞  直升飞机降落

	system("pause");
}
*/

/*********************抽象类/接口-纯虚函数**********************/
/*
// 抽象类和接口实现方式一样, 只是逻辑上的划分
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

// 抽象类/接口 -- 具有纯虚函数的类
class Shape{
public:
	// 纯虚函数
	virtual void sayArea() = 0;
};

class Circle :public Shape{
public:
	Circle(int r){
		this->r = r;
	}
	void sayArea(){
		cout << "圆的面积" << r*r*3.14 << endl;
	}
private:
	int r;
};

void main(){
	// 抽象类不能实例化
	// Shape s;
	// 必须重写 sayArea() 抽象函数才能实例化对象, 如果没有实现, 子类也是抽象类
	Circle c1(5);
	c1.sayArea();

	system("pause");
}
*/


/*************************泛型--模板函数*********************/
/*
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

//void mySwap(int& a, int& b){
//	int tmp = 0;
//	tmp = a;
//	a = b;
//	b = tmp;
//}
//
//void mySwap(char& a, char& b){
//	char tmp = 0;
//	tmp = a;
//	a = b;
//	b = tmp;
//}

// 函数模板 -- 解决业务逻辑一样, 数据类型不一样
template <typename T>
void mySwap(T& a, T& b){
	T tmp = 0;
	tmp = a;
	a = b;
	b = tmp;
}

void main(){
	int a = 10, b = 20;
	mySwap(a, b);
	cout << a << "," << b << endl;

	char x = 'x', y = 'y';
	mySwap<char>(x, y); // 这种写法一样的
	cout << x << "," << y << endl;
	system("pause");
}
*/


/*************************模板类*********************/
/*
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

// 模板类
template<class T>
class A
{
public:
	A(T a){
		this->a = a;
	}
protected:
	T a;
};

// 普通类继承模板类
class B :public A<int>{
public:
	B(int a) :A<int>(a){

	}
};

// 模板类继承模板类
template <class T>
class C : public A<T>{
public:
	C(T c, T a) :A<T>(a){

	}
};

void main(){
	// 实例化模板类对象
	A<int> a(6);

	system("pause");
}
*/

/*************************异常*********************/
/*
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

class MyException{
public:
	MyException(){

	}
};

//void main(){
//	// 根据抛出的异常数据类型, 进入相应的catch块中
//	try{
//		int age = 300;
//		if (age > 200){
//			// throw age;
//			// throw "发生异常";
//			throw 9.8;
//		}
//	}
//	catch (int a){
//		cout << "int 异常" << endl;
//	}
//	catch (char* b){
//		cout << b << endl;
//	}
//	catch (...){
//		cout << "未知异常" << endl;
//	}
//
//	system("pause");
//}

//void main(){
//	try{
//		int a = 1;
//		if (a == 1){
//			throw MyException();
//			// throw new MyException; 不要抛出指针 需要释放对象
//		}
//	}
//	//catch (MyException ex){
//		//cout << "MyException" << endl;
//	//}
//	catch (MyException* ex1){
//		// 不推荐
//		cout << "MyException指针" << endl;
//		delete ex1;
//	}
//	catch (MyException& ex2){
//		// 需要注释掉 ex, 因为1和3都可以catch到
//		cout << "MyException引用" << endl;
//	}
//}

// throw 声明函数会抛出的异常类型
void myDiv(int a, int b) throw (char *){
	if (b == 0){
		throw "除数为0";
	}
}

// 标准异常(类似于 Java 的 NullPointerException)
#include<stdexcept>
class NullPointerException : public exception{
public:
	NullPointerException(char* msg) :exception(msg){

	}
};

void myDiv1(int a, int b){
	if (b == 0){
		// 超出范围
		throw out_of_range("超出范围");
	}
	else if (b > 19)
	{
		throw invalid_argument("参数不合法");
	}
	else
	{
		throw NullPointerException("为空");
	}
}

void main(){
	try{
		// myDiv1(1, 0);
		myDiv1(1, -1);
	}
	catch (out_of_range e1){
		cout << e1.what() << endl;
	}
	catch (NullPointerException& e2){
		cout << e2.what() << endl;
	}

	system("pause");
}
*/



/*************************类型转换*********************/
/*
// static_cast  基础类型和对象的转换
// const_cast  用来去除变量的const限定
// dynamic_cast 类的转换, 如多态子类转为实际类型, 转换失败结果是NULL, 直接强转失败也不知道
// reinterpret_cast 任意指针相互转换, 一般用于函数指针

// 原始自动转换, 可读性不高, 而且可能有潜在的风险

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

void* func(int type){
	switch (type)
	{
	case 1:{
			   int i = 9;
			   return &i;
	}
	case 2:{
			   int a = 'X';
			   return &a;
	}
	default:
		break;
	}
	return NULL;
}

void main(){
	//int i = 0;
	//// 自动转换
	//double d = i;

	//int i = 8;
	//double d = 9.5;
	//i = static_cast<int>(d);

	// char* c_p = static_cast<char*>(func(2));

	//const char c[] = "hello";
	//// 去常量写法
	//char* c_p = const_cast<char*>(c);
	//c_p[1] = 'X';
	//cout << c << endl;

	system("pause");
}
*/



/*************************IO操作*********************/
/*
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

//// 文本文件 创建/读取
//void main(){
//	char* fname = "D://test.txt";
//	// 输出流写出
//	ofstream fout(fname);
//	// 判断是否创建失败
//	if (fout.bad()){
//		return;
//	}
//
//	fout << "hello" << endl;
//	fout << "zdd" << endl;
//
//	//关闭
//	fout.close();
//
//	// 输入流读取
//	ifstream fin(fname);
//	if (fin.bad()){
//		return;
//	}
//	// 读取流
//	char ch;
//	while (fin.get(ch)){
//		cout << ch;
//	}
//	fin.close();
//	system("pause");
//}

// 二进制文件
void main(){
	char* fname = "d://test.jpg";

	char* fcopy = "d://copy.jpg";

	// 输入流
	ifstream fin(fname, ios::binary);
	// 输出流
	ofstream fout(fcopy, ios::binary);

	if (fin.bad() || fout.bad()){
		return;
	}

	while (!fin.eof()){ // eof 达到末尾
		// 读取
		char buff[2014] = { 0 };
		fin.read(buff, 1024);

		// 写入  0是不会写进去的 和java不同
		fout.write(buff, 1024);
	}

	fin.close();
	fout.close();

	system("pause");
}
*/

/*************************STL标准模板库*********************/
/*
// util, math 等
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

//// string 初始化
//void main(){
//	// c++ 中的 string  到 jni 中还需要转为 char*
//	string s1 = "sjfdfkj dfjd s";
//	string s2("33 fd");
//	string s3 = s1 + s2;
//
//	// string 转为 c 字符串
//	const char* s = s3.c_str();
//
//	// 声明10个长度 全是a
//	string s4(10, 'a');
//	cout << s4 << endl;
//
//	system("pause");
//}
//
////string遍历
//void main()
//{
//	string s1 = "craig david";
//	//			 ^
//	//1 数组方式
//	for (int i = 0; i < s1.length(); i++)
//	{
//		cout << s1[i] << endl;
//	}
//	//2 迭代器指针
//	for (string::iterator it = s1.begin(); it != s1.end(); it++)
//	{
//		cout << *it << " ";
//	}
//	cout << endl;
//	//3 at函数(charAt)
//	// 可能会抛出异常
//	try
//	{
//		for (int i = 0; i < s1.length() + 3; i++)
//		{
//			cout << s1.at(i) << " ";
//		}
//	}
//	catch (...)
//	{
//		cout << "异常" << endl;
//	}
//
//
//	system("pause");
//}
//
//
////string字符串->c字符串转换
//void main()
//{
//	//string -> char*
//	string s1 = "walking away";
//	const char* c = s1.c_str();
//	printf("%s\n",c);
//
//	//
//	string s2 = c;
//
//	//string->char[]
//	//从string中赋值字符到char[]
//	char arr[50] = {0};
//	s1.copy(arr,4,0);
//	
//	cout << arr << endl;
//
//	system("pause");
//}
//
//
////字符串拼接
//void main()
//{
//	string s1 = "alan";
//	string s2 = "jackson";
//	
//	//1.
//	string s3 = s1 + s2;
//
//	string s4 = " pray";
//
//	//2.
//	s3.append(s4);
//
//	cout << s3 << endl;
//
//	system("pause");
//}
//
////字符串查找替换
//void main()
//{
//	string s1 = "apple google apple iphone";
//	//从0开始查找"google"的位置
//	int idx = s1.find("google", 0);
//	cout << idx << endl;
//
//	//统计apple出现的次数
//	int idx_app = s1.find("apple",0);
//	//npos大于任何有效下标的值
//	int num = 0;
//	while (idx_app != string::npos)
//	{
//		num++;
//		cout << "找到的索引:" << idx_app << endl;
//		idx_app+=5;
//		idx_app = s1.find("apple", idx_app);
//	}
//
//	cout << num << endl;
//	system("pause");
//}
//
//void main()
//{
//	string s1 = "apple google apple iphone";
//	//0-5（不包含5）替换为jobs
//	s1.replace(0, 5, "jobs");
//	cout << s1 << endl;
//
//	//所有apple替换为jobs
//	int idx = s1.find("apple", 0);
//	while (idx != string::npos)
//	{
//		s1.replace(idx, 5, "jobs");
//		idx += 5;
//		idx = s1.find("apple", idx);
//	}
//
//	cout << s1 << endl;
//	system("pause");
//}
//
////删除（截取）和插入
//void main()
//{
//	string s1 = "apple google apple iphone";
//	//删除a，找到a所在的指针
//	string::iterator it = find(s1.begin(),s1.end(),'g');
//	//只能删除一个字符
//	s1.erase(it);
//	
//	//开头末尾插入字符串
//	s1.insert(0, "macos");
//	s1.insert(s1.length(), " facebook");
//
//	cout << s1 << endl;
//	system("pause");
//}
//
////java StringBuffer才可变
////String 不可变
////大小写转换
//void main()
//{
//	string s1 = "JASON";
//	//原始字符串的起始地址，原始字符串的结束地址, 目标字符串的起始地址, 函数名称
//	transform(s1.begin(), s1.end()-1,s1.begin(), tolower);
//	cout << s1 << endl;
//
//
//	transform(s1.begin(), s1.end() - 1, s1.begin(), toupper);
//	cout << s1 << endl;
//
//	system("pause");
//}
//
//
////容器
////Vector
////初始化
//#include <vector>
//void printVector(vector<int> &v)
//{
//	//通过数组的方式遍历
//	for (int i = 0; i < v.size(); i++)
//	{
//		cout << v[i] << endl;
//	}
//}
//void main()
//{
//	//1.
//	vector<int> v1;
//	v1.push_back(20);
//	v1.push_back(40);
//	v1.push_back(15);
//	v1.push_back(7);
//
//	//2.
//	vector<int> v2 = v1;
//
//	//3.部分复制
//	vector<int> v3(v1.begin(),v1.begin()+2);
//	
//	printVector(v3);
//	
//
//	system("pause");
//}
//
////添加 删除
//void main()
//{
//	//添加到结尾
//	vector<int> v1;
//	v1.push_back(20);
//	v1.push_back(40);
//	v1.push_back(15);
//	v1.push_back(7);
//
//	//访问头部
//	v1.front() = 11;
//	//访问尾部
//	v1.back() = 90;
//
//	//删除结尾的元素
//	//v1.pop_back();
//	while (v1.size() > 0)
//	{
//		cout << "末尾的元素：" << v1.back() << endl;
//		v1.pop_back();
//	}
//
//	printVector(v1);
//
//	system("pause");
//}
//
////数组的方式
//void main()
//{
//	vector<int> v1;
//	v1.push_back(20);
//	v1.push_back(40);
//	v1.push_back(15);
//	v1.push_back(7);
//
//	v1[2] = v1[2] +10;
//
//	//容器等价于动态数组	
//	vector<int> v2(10);
//	for (int i = 0; i < v2.size(); i++)
//	{
//		v2[i] = i + 1;
//	}
//
//	printVector(v2);
//
//	system("pause");
//}
//
////迭代器遍历
////迭代器的种类（正向，反向迭代器）
//void main()
//{
//	vector<int> v1;
//	v1.push_back(20);
//	v1.push_back(40);
//	v1.push_back(15);
//	v1.push_back(7);
//	//正向
//	for (vector<int>::iterator it = v1.begin(); it < v1.end(); it++)
//	{
//		cout << *it << endl;
//	}
//	cout << "-----------------" << endl;
//	//反向迭代
//	for (vector<int>::reverse_iterator it = v1.rbegin(); it < v1.rend(); it++)
//	{
//		cout << *it << endl;
//	}
//
//	system("pause");
//}
//
////删除
//void main()
//{
//	vector<int> v1(10);
//	for (int i = 0; i < v1.size(); i++)
//	{
//		v1[i] = i + 1;
//	}
//
//	//删除指定位置
//	vector<int>::iterator it = v1.begin();
//	it += 3;
//	v1.erase(it);
//
//	//distance(v1.begin(), it);
//
//	//删除区间
//	v1.erase(v1.begin(), v1.begin() + 3);
//
//	for (vector<int>::iterator it = v1.begin(); it < v1.end(); it++)
//	{
//		if (*it == 5)
//		{		
//			printf("%x\n", it);
//			vector<int>::iterator tmp = v1.erase(it); //注意以后开发中编译器版本问题
//			printf("%x,%x\n",it,tmp);
//		}
//	}
//
//	//插入
//	v1.insert(v1.begin() + 2, 100);
//	v1.insert(v1.end() - 1, 200);
//
//	printVector(v1);
//
//	system("pause");
//}
//
////双向队列
//#include <deque>
//void printDeque(deque<int>& q)
//{
//	for (int i = 0; i < q.size(); i++)
//	{
//		cout << q[i] << endl;
//	}
//}
//
//void main()
//{
//	deque<int> d1;
//	//添加到尾部
//	d1.push_back(2);
//	d1.push_back(10);
//	//添加到头部
//	d1.push_front(-90);
//	d1.push_front(-30);	
//
//	//printDeque(d1);
//
//	//cout << d1.front() << endl;
//	//cout << d1.back() << endl;
//
//	//两个方向弹出
//	//d1.pop_back();
//	//d1.pop_front();
//
//	printDeque(d1);
//
//	//查找第一个-90元素索引位置，无需遍历
//	deque<int>::iterator it = find(d1.begin(),d1.end(),-90);
//	if (it != d1.end())
//	{
//		int idx = distance(d1.begin(), it);
//		cout << "索引位置为：" << idx << endl;
//	}
//
//
//	system("pause");
//}
//
//
//
////队列（没有迭代器）
//void main()
//{
//	queue<int> q;
//	q.push(78);
//	q.push(18);
//	q.push(20);
//	q.push(33);
//	
//	//q.front();
//	//q.back();
//	while (!q.empty())
//	{
//		int tmp = q.front();
//		cout << tmp << endl;
//		q.pop();
//	}	
//	system("pause");
//}
//
////优先级队列
//#include <functional>
//
//void main()
//{
//	//默认 最大值优先级
//	priority_queue<int> pq1;
//	pq1.push(12);
//	pq1.push(3);
//	pq1.push(40);
//	pq1.push(15);
//
//	while (!pq1.empty())
//	{
//		int tmp = pq1.top();
//		cout << tmp << endl;
//		pq1.pop();
//	}
//
//	cout << "----------" << endl;
//	//最小值优先级队列
//	priority_queue<int, vector<int>,greater<int>> pq2;
//	pq2.push(12);
//	pq2.push(3);
//	pq2.push(40);
//	pq2.push(15);
//
//	while (!pq2.empty())
//	{
//		int tmp = pq2.top();
//		cout << tmp << endl;
//		pq2.pop();
//	}
//
//	system("pause");
//}
//
//
////栈
//#include <stack>
//void main()
//{
//	stack<int> s;
//	for (int i = 0; i < 10; i++)
//	{
//		s.push(i+1);
//	}
//	
//	while (!s.empty())
//	{
//		int tmp = s.top();
//		cout << tmp << endl;
//		s.pop();
//	}
//	
//	system("pause");
//}
//
////list
//#include <list>
//void printList(list<int>& lst)
//{
//	//迭代器
//	//没有重载“<”运算符
//	for (list<int>::iterator it = lst.begin(); it != lst.end(); it++)
//	{
//		cout << *it << endl;
//	}
//}
//
////基本操作
//void main()
//{
//	list<int> lst;
//	for (int i = 0; i < 10; i++)
//	{
//		//尾部插入元素
//		lst.push_back(i);
//	}
//
//	//头部插入元素
//	lst.push_front(80);
//	lst.push_front(90);
//
//	list<int>::iterator it = lst.begin();
//	it++;
//	cout << *it << endl;
//	//it = it + 3; 注意：不支持随机访问		
//
//	printList(lst);
//
//	system("pause");
//}
//
//
////删除
//void main()
//{
//	list<int> lst;
//	for (int i = 0; i < 10; i++)
//	{
//		//尾部插入元素
//		lst.push_back(i);
//	}
//
//	list<int>::iterator it = lst.begin();
//	//删除
//	it++;
//	//删除第二个元素
//	//lst.erase(it);
//
//	//删除区间（已经被删除了元素不能再删除）
//	list<int>::iterator it_begin = lst.begin();
//	list<int>::iterator it_end = lst.begin();
//	it_end++;
//	it_end++;
//	it_end++;
//	lst.erase(it_begin, it_end);
//
//	//直接根据内容删除元素
//	lst.remove(5);
//
//	printList(lst);
//
//	system("pause");
//}
//
////list插入（应用：频繁的修改）
////vector（应用：随机访问v[100]）
//void main()
//{
//	list<int> lst;
//	for (int i = 0; i < 10; i++)
//	{
//		//尾部插入元素
//		lst.push_back(i);
//	}
//
//	list<int>::iterator it = lst.begin();
//	it++;
//	lst.insert(it, 100);
//
//	printList(lst);
//	system("pause");
//}
//
////set 元素唯一 默认从小到大
//#include <set>
//
//void printSet(set<int> &s)
//{
//	for (set<int>::iterator it = s.begin(); it != s.end(); it++)
//	{
//		cout << *it << endl;
//	}
//}
//
//void main()
//{
//	set<int> s;
//	//添加元素
//	for (int i = 0; i < 10; i++)
//	{
//		s.insert(i+1);
//	}
//	s.insert(20);
//	s.insert(15);
//	s.insert(15);
//
//	//删除
//	set<int>::iterator it = s.begin();
//	it++;
//	s.erase(it);	
//
//	printSet(s);
//	system("pause");
//}
//
//
////元素按照从大到小排列
//#include <functional>
//void main()
//{
//	//同Java中：Map<String,List<String>> 
//	set<int,greater<int>> s;
//	s.insert(10);
//	s.insert(5);
//	s.insert(20);
//	s.insert(99);
//
//	for (set<int,greater<int>>::iterator it = s.begin(); it != s.end(); it++)
//	{
//		cout << *it << endl;
//	}
//
//	system("pause");
//}
//
//
////元素类型为Teacher对象，按照年龄排序
//class Teacher
//{
//public:
//	Teacher(char* name, int age)
//	{
//		this->name = name;
//		this->age = age;
//	}
//
//	void print()
//	{
//		cout << name << "," << age << endl;
//	}	
//
//public:
//	char* name;
//	int age;
//};
//
////自定义排序规则
////仿函数
//struct MyAgeSorter
//{
//	bool operator()(const Teacher &left, const Teacher &right)
//	{
//		return left.age < right.age;
//	}
//};
//
//void main()
//{
//	set<Teacher, MyAgeSorter> s;
//	s.insert(Teacher("jack",18));
//	s.insert(Teacher("rose", 20));
//	s.insert(Teacher("jason", 22));
//	s.insert(Teacher("alan", 5));
//	//s.insert(Teacher("jimy", 5)); //不会插入
//
//	for (set<Teacher>::iterator it = s.begin(); it != s.end(); it++)
//	{
//		cout << (*it).name << "," << (*it).age << endl;
//	}
//
//	system("pause");
//}
//
//
////set查找
//void main()
//{
//	set<int> s;
//	//添加元素
//	for (int i = 0; i < 10; i++)
//	{
//		s.insert(i + 1);
//	}
//
//	//printSet(s);
//
//	//等于4的元素指针
//	set<int>::iterator s_4 = s.lower_bound(4); 
//	//cout << *s_4 << endl;
//	//大于4的元素指针
//	set<int>::iterator s_5 = s.upper_bound(4);
//	//cout << *s_5 << endl;
//
//	//一次性获取等于4的元素指针，和大于4的元素指针\
//	//BasicNameValuePair
//	pair<set<int>::iterator, set<int>::iterator> p = s.equal_range(4);
//	cout << *p.first << endl;
//	cout << *p.second << endl;
//	system("pause");
//}
//
//
////multiset 允许重复的元素
//void main()
//{
//	multiset<int> s;
//	s.insert(2);
//	s.insert(8);
//	s.insert(2);
//	s.insert(8);
//
//	for (multiset<int>::iterator it = s.begin(); it != s.end(); it++)
//	{
//		cout <<  *it << endl;
//	}
//
//	system("pause");
//}
//
//
////map添加元素的方式
//#include <map>
//
//void main()
//{
//	//key -> value
//	//1.
//	map<int, string> map1;
//	map1.insert(pair<int, string>(1,"jack"));
//	map1.insert(pair<int, string>(2, "rose"));
//
//	//2
//	map1.insert(make_pair(3,"jason"));
//
//	//3
//	map1.insert(map<int,string>::value_type(4,"alan"));
//
//	//4
//	map1[5] = "jimmy"; //map["NO1"] = 90;
//
//	//前三种方式，如果key已经存在，重复添加会报错
//	//第四种方式，如果key已经存在，重复添加会覆盖
//	
//	//遍历输出
//	for (map<int, string>::iterator it = map1.begin(); it != map1.end(); it++)
//	{
//		cout << it->first << "," << it->second << endl;		
//	}
//
//
//	system("pause");
//}
//
//
//void printMap(map<int, string> &map1)
//{
//	for (map<int, string>::iterator it = map1.begin(); it != map1.end(); it++)
//	{
//		cout << it->first << "," << it->second << endl;
//	}
//}
//
////删除
//void main()
//{
//	map<int, string> map1;
//	map1.insert(pair<int, string>(1, "jack"));
//	map1.insert(pair<int, string>(2, "rose"));
//	map1.insert(pair<int, string>(3, "jason"));	
//
//	map<int, string>::iterator it = map1.begin();
//	it++;
//	map1.erase(it);
//
//	printMap(map1);
//
//	system("pause");
//}
//
//
////添加的结果
//void main()
//{
//	map<int, string> map1;
//	map1.insert(pair<int, string>(1, "jack"));
//	map1.insert(pair<int, string>(2, "rose"));
//	map1.insert(pair<int, string>(3, "jason"));
//	//获取添加的结果（first元素指针，second 是否成功）
//	pair<map<int, string>::iterator, bool> res = map1.insert(pair<int, string>(3, "alan"));
//	if (res.second)
//	{
//		cout << "添加成功" << endl;
//	}
//	else
//	{
//		cout << "添加失败" << endl;
//	}
//
//	printMap(map1);
//
//	system("pause");
//}
//
//
//
////查找
//void main()
//{
//	map<int, string> map1;
//	map1.insert(pair<int, string>(1, "jack"));
//	map1.insert(pair<int, string>(2, "rose"));
//	map1.insert(pair<int, string>(3, "jason"));	
//
//	printMap(map1);
//
//	cout << "---------" << endl;
//
//	//获取key等于大于5的元素的值
//	pair<map<int, string>::iterator, map<int, string>::iterator> p = map1.equal_range(2);
//	if (p.first != map1.end()){
//		//等于2的元素key value
//		cout << p.first->first << p.first->second << endl;
//
//		//大于2的元素key value
//		cout << p.second->first << p.second->second << endl;
//	}
//
//	system("pause");
//}
//
//
////一个key对应多个value
////一个部门多个员工
////multimap
//class Employee
//{
//public:
//	Employee(char* name,int age)
//	{
//		this->name = name;
//		this->age = age;
//	}
//
//public:
//	char* name;
//	int age;
//};
//
//void main()
//{
//	multimap<string, Employee> map1;
//	
//	//开发部
//	map1.insert(make_pair("开发", Employee("搁浅", 20)));
//	map1.insert(make_pair("开发", Employee("彪哥", 20)));
//
//	//财务
//	map1.insert(make_pair("财务", Employee("小颖", 16)));
//	map1.insert(make_pair("财务", Employee("rose", 20)));
//
//	//销售
//	map1.insert(make_pair("销售", Employee("阿呆", 30)));
//	map1.insert(make_pair("销售", Employee("呵呵", 30)));
//
//	//遍历输出
//	for (multimap<string, Employee>::iterator it = map1.begin(); it != map1.end(); it++)
//	{
//		cout << it->first << "," << it->second.name  << "," << it->second.age << endl;
//	}
//
//	cout << "----------------" << endl;
//	//只获取“财务”部的员工
//	//获取“财务部”员工的个数，key对应的value的个数
//	int num = map1.count("财务");
//	multimap<string, Employee>::iterator it = map1.find("财务");
//	int c = 0; //控制循环的次数
//	while (it != map1.end() && c < num)
//	{		
//		cout << it->first << "," << it->second.name << "," << it->second.age << endl;
//		it++;
//		c++;
//	}
//
//	system("pause");
//}
*/


/******************POSIX标准多线程(pthread)*******************/
// 引入#include <pthread.h>
// windows 下需要下载 ftp://sourceware.org/pub/pthreads-win32 还需要配置下
// 这里在linux下编写

/*
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// 互斥锁
pthread_mutex_t mutex;

void* thr_fun(void* arg){
    // 加锁
    pthread_mutex_lock(&mutex);
    char* no = (char*)arg;
    int i=0;
    for(;i<10;i++){
        printf("%s thread, i:%d\n", no, i);
    }
    // 解锁
    pthread_mutex_unlock(&mutex);
}

void main(){
    printf("main thread\n");
    // 线程id
    pthread_t tid, tid2;
    // 初始化互斥锁
    pthread_mutex_init(&mutex, NULL);
    // 创建线程
    pthread_create(&tid, NULL, thr_fun, "1");
    pthread_create(&tid2, NULL, thr_fun, "2");
 
    // 调用线程
    pthread_join(tid, NULL);
    pthread_join(tid2, NULL);
 
    // 销毁互斥锁
    pthread_mutex_destroy(&mutex);
}    
*/



/******************多线程生产消费者*******************/
// 条件变量 pthread_cond_t
/*
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

//消费者数量
#define CONSUMER_NUM 2
//生产者数量
#define PRODUCER_NUM 1

pthread_t pids[CONSUMER_NUM+PRODUCER_NUM];

//产品队列
int ready = 0;

//互斥锁
pthread_mutex_t mutex;
//条件变量
pthread_cond_t has_product;

//生产
void* producer(void* arg){
    int no = (int)arg;
    //条件变量
    for(;;){
        pthread_mutex_lock(&mutex);
        //往队列中添加产品
        ready++;
        printf("producer %d, produce product\n",no);
        //fflush(NULL);
        //通知消费者，有新的产品可以消费了
        //会阻塞输出
        pthread_cond_signal(&has_product);
        printf("producer %d, singal\n",no);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}

//消费者
void* consumer(void* arg){
    int num = (int)arg;
    for(;;){
        pthread_mutex_lock(&mutex);
        //while?
        //superious wake ‘惊群效应’
        while(ready==0){
            //没有产品，继续等待
            //1.阻塞等待has_product被唤醒
            //2.释放互斥锁，pthread_mutex_unlock
            //3.被唤醒时，解除阻塞，重新申请获得互斥锁pthread_mutex_lock
            printf("%d consumer wait\n",num);
            pthread_cond_wait(&has_product,&mutex);
        }
        //有产品，消费产品
        ready--;
        printf("%d consume product\n",num);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}


void main(){
    //初始化互斥锁和条件变量                                                
    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&has_product,NULL);
    printf("init\n");

    int i;
    for(i=0; i<PRODUCER_NUM;i++){
        //生产者线程
        printf("%d\n",i);
        pthread_create(&pids[i],NULL,producer,(void*)i);
    }
    
    for(i=0; i<CONSUMER_NUM;i++){
        //消费者线程
        pthread_create(&pids[PRODUCER_NUM+i],NULL,consumer,(void*)i);
    }
    
    //等待
    sleep(10);
    for(i=0; i<PRODUCER_NUM+CONSUMER_NUM;i++){
        pthread_join(pids[i],NULL);
    }
    
    //销毁互斥锁和条件变量
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&has_product);
    
}
*/

/*
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

void main(){
    system("pause");
}
*/

