
#pragma once // 防止循环引用

// 类的头文件
class MyTeacher
{
public:
	int age;
	char* name;
public:
	void setAge(int age);
	int getAge();
	void setName(char* name);
	char* getName();
};