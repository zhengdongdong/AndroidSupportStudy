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
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

void swap(int &a, int &b){
	int c = 0;
	c = a;
	a = b;
	b = c;
}

void main(){
	int a = 10;
	// & 在C++中表示引用, 和指针一样, 都是操作内存地址
	int &b = a;
	int *c = &a;

	cout << b << endl;
	cout << *c << endl;

	int x = 10;
	int y = 20;
	printf("%d, %d\n", x,y);
	swap(x, y);
	printf("%d, %d\n", x,y);

	system("pause");
}



/*
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

void main(){

}
*/











