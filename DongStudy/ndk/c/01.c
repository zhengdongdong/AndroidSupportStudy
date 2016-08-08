//#define _CRT_SECURE_NO_WARNINGS // 宏定义, 这里不让 scanf 报错, 或者直接使用 scanf_s()
// 引入头文件(.h)  -- 头文件中只有声明, 实现在 .c 中
#include<stdio.h>
#include<stdlib.h> // scanf

// 入口函数 - 1
/*
int main(int arg, char* str){

}
*/

// 入口函数 - 2
/*
void main(){
	printf("hello world \n");

	system("pause"); // pause:按任意键继续. (windows 命令, 如 system("mspaint") 打开系统画板)
	// getchar(); // 等待输入
}
*/

// 基本数据类型
// int short long float double char
/*
void main(){
	// 输入
	int input;
	//scanf("%d", &input); #define _CRT_SECURE_NO_WARNINGS
	scanf_s("%d", &input); 

	// 输入/输出占位符
	int i = 1;
	printf("int = %d \n", i);
	float f = 2.2f;
	printf("float = %f \n", f);
	short s = 2;
	printf("short = %d \n", s);
	long l = 3;
	printf("long = %ld \n", l);
	double d = 3.3;
	printf("double = %lf \n", d);
	char c = 'a';
	printf("char = %c \n", c);
	int *p = &i;
	printf("十六进制 = %x \n", p);
	int e = 12;
	printf("八进制 = %o \n", e);
	char str[] = "hello world";
	printf("string = %s \n", str);
	
	// 所占字节大小
	printf("int :  %d \n", sizeof(int));  //4
	printf("short :  %d \n", sizeof(short)); //2
	printf("long :  %d \n", sizeof(long)); //4
	printf("float :  %d \n", sizeof(float)); //4
	printf("double :  %d \n", sizeof(double)); //8
	printf("char :  %d \n", sizeof(char)); //1

	system("pause");
}
*/

// 循环
/*
void main(){
	int i = 0;
	for (; i < 10; i++){ // 注意: 这里和 java 等不一样, 在 windows 下 for(int i=0;..) 可能没问题, linux 可能会出问题, 这里是c的标准写法
		printf("%d \n", i);
	}

	int j = 0;
	while (j<10)
	{
		printf("%d \n", j);
		j++;
	}

	getchar();
}
*/

// 指针 -- 指针存储的是变量的内存地址
/*
void main(){
	int i = 100;
	int *p = &i; // 指针存的是一个地址, 但是指针为何会有类型?  指针的地址只是开始, 类型会告知读到什么位置 (如int, 往后读4个字节)
	printf("i : %d\n", i);
	printf("p : %#x \n", p);  //%x 是十六进制, %#x 是格式化的 -- 0x..
	printf("*p : %d\n", *p);

	*p = 10;
	printf("通过 *p 改变了 i : %d\n", i);

	// NULL 空指针
	int *pn = NULL;
	// printf("p - NULL : %#x\n", pn); 0x000000 系统特殊位置, 不允许访问, 像 100 1000 等这些位置都是特殊的 不允许访问
	printf("p - NULL : %d\n", *pn);

	system("pause");
}
*/

// 多级指针 -- 保存一个指针变量地址的指针

void main(){
	int a = 50;
	// p1 保存 a 的地址
	int *p1 = &a;
	// p2 保存 p1 的地址
	int **p2 = &p1;

	printf("p1 -> %#x\n", p1);
	printf("p2 -> %#x\n", p2);
	printf("*p2 -> %#x\n", *p2);

	system("pause");
}