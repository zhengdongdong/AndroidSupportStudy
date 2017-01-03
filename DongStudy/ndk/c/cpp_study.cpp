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
	/*Teacher(const Teacher &obj){
		this->name = obj.name;
		this->age = obj.age;
		cout << "拷贝构造函数" << endl;
	}*/

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



/*
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

void main(){
	system("pause");
}
*/







