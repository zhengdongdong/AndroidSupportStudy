#define _CRT_SECURE_NO_WARNINGS // 宏定义, 这里不让 scanf 报错, 或者直接使用 scanf_s()
// 引入头文件(.h)  -- 头文件中只有声明, 实现在 .c 中
#include<stdio.h>
#include<stdlib.h> // scanf
#include<string.h>

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
/*
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
*/

// 指针运算  -- 一般针对数组的 ++ -- (因为数组在内存中是线性排列的)
/*
void main(){
	int ids[] = { 1, 2, 3, 5, 7 };
	
	// 输出数据变量名 就是数组的首地址
	printf("%#x\n", ids);
	printf("%#x\n", &ids[0]);

	int *p = ids;
	printf("*p %d \n", *p);
	p++; // 向前移动 sizeof(数据类型) 个字节
	printf("*p(p++后) %d \n", *p);

	// p 首地址
	// p 等价于 &ids[0]  p+1 等价于 &ids[1]
	// p+i 等价于 &ids[i]

	// *p 等价于 ids[0], *(a+1) 等价于 a[1]
	// *(p+i) 等价于 a[i]

	int uids[5];
	int *p = uids;
	int i = 0;
	for (; p < uids + 5; p++){ // 最老的写法
		*p = i;
		i++;
	}

	system("pause");
}
*/

//指针引用二维数组（行指针，列指针）
/*
void main(){
	int a[2][3] = {95,82,56,17,29,30};
	//遍历输出
	//外层循环控制行，内层循环控制列
	int i = 0;
	for (; i < 2; i++){
		int j = 0;
		for (; j < 3; j++){
			printf("%d,%#x	", a[i][j], &a[i][j]);
		}
		printf("\n");
	}

	//
	//printf("%#x,%#x,%#x\n",a,&a,*a);
	//printf("%d,%d,%d\n", sizeof(*a), sizeof(*&a), sizeof(**a));
	//a是一个行指针，指向一个有三个元素的数组，12
	//&a是一个指向二维数组的指针，当前二维 数组6个元素，24
	//*a 是一个指向int类型数据的指针（a[0][0]），4
	//printf("%d\n", **a);

	//a是一个行指针，是数组第一行的指针，a+1第二行的指针，以此类推
	printf("%#x,%#x\n",a,a+1);
	//*a是数组的第一行第一个元素的指针，*a+1是数组第一行第二个元素的指针
	printf("%#x,%#x\n",*a,*a+1);
	//*(a+1)是数组的第二（1）行第一(0)个元素的指针
	//注意：不一定是正常逻辑
	printf("%#x,%#x\n",*(a+1),*(a+1)+1);


	//取数组的第1（二）行，第2（三）个元素
	printf("%d\n",a[1][2]);
	printf("%d\n",*(*(a+1)+2));

	//总结：
	//a[i][j] 等价于 *(*(a+i)+j)
	//&a[i][j] 等价于 (*(a+i)+j)

	getchar();
}
*/

// 函数指针
/*
void msg(int i){
	printf("消息队列: %d\n", i);
}

void main(){
	// 函数指针
	// 组成
	// 返回值类型, 函数指针名称, 函数参数列表
	void(*fun_p)(int i) = msg;

	fun_p(1);

	printf("%#x\n", msg);
	printf("%#x\n", &msg);

	system("pause");
}
*/

// 函数指针例子
/*
int add(int a, int b){
	return a + b;
}

int minus(int a, int b){
	return a - b;
}

// 相当于 java 的回调
void msg(int(*p)(int a, int b), int m, int n){
	int result = p(m, n);
	printf("输出结果: %d\n", result);
}

void main(){
	msg(add, 8, 9);
	msg(minus, 10, 2);

	system("pause");
}
*/

// 动态内存分配
/*
// 栈内存
void stackFun(){
	// 运行到这里自动分配, 方法结束, 自动释放
	int a[1024];
}

// 堆内存
void heapFun(){
	// 在堆内存上分配 40M
	int *p = malloc(1024 * 1024 * 10 * sizeof(int));
	// int *p = calloc(len, sizeof(int));

	// 释放堆内存
	free(p);
}

void main(){
	// c 语言内存分配
	// 1.栈区 (stack)  
	// 1.1.windows下, 一个应用栈内存一般分配 2M(确定的长度)
	// 1.2.自动分配,自动释放
	// 2.堆区 (heep)
	// 2.1.可分配操作系统 80% 的内存
	// 2.2.手动分配,手动释放
	// 3.静态区(全局变量)
	// 4.字符常量区
	// 5.程序代码区

	system("pause");
}
*/

// 例:动态数组
/*
void main(){
	// 静态分配
	// int a[10];

	// 动态分配
	int len;
	printf("请输入数据长度:");
	scanf_s("%d", &len);

	// 开辟内存, p 可当成数组首地址
	int *p = malloc(len * sizeof(int));
	// int *p = calloc(len, sizeof(int));
	// 给数组元素赋值
	int i = 0;
	for (; i < len; i++){
		p[i] = i;
		printf("%d, %#x\n", p[i], &p[i]);
	}

	// 扩大 p 内存
	// realloc(原内存指针, 内存扩大后的总大小)
	int *p2 = realloc(p, (5 + len) * sizeof(int)); // p2 的地址可能和 p 一样

	// 重新分配的两种情况:
	// 1. 缩小, 缩小的部分数据会丢失
	// 2. 扩大, 动态内存分配的内存是连续的(为什么可以代表数组)
	// 2.1 若果当前内存后有需要的内存空间大小, 直接扩展内存, 返回原指针
	// 2.2 若没有足够的空间大小, 再找堆中另一块有足够大小的内存空间, 把之前的数据复制过来, 并释放原来的内存
	// 2.3 若系统没有足够的空间分配, 申请失败, 返回 NULL, 原来的指针仍然有效

	if (p2 != NULL){
		int j = 0;
		for (; j < 5 + len; j++){
			p2[j] = j;
			printf("%d, %#x\n", p2[j], &p2[j]);
		}
		// 其实只要释放 p2 就好了, 因为只有成功分配, p 要么就是 p2, 要么就是已经被释放
		if (p != NULL){
			free(p2);
			p = NULL;
		}
		if (p2 != NULL){
			free(p2);
			p2 = NULL;
		}
	}
	else
	{
		free(p);
	}

	system("pause");
}
*/

// 字符串
/*
void main(){
	// 字符串写法
	// char str[] = { 'c', 'h', 'i', 'n', 'a', '\0' };
	// char str[] = { 'c', 'h', 'i', 'n', 'a' }; // 这个后面会有乱码
	// char str[8] = { 'c', 'h', 'i', 'n', 'a' }; // 这个没有, 区别在是否声明长度
	// char str[10] = "china";
	char* str = "china";
	// str[0] = 'a';  char* str 不允许修改 若想修改, 使用 str[]
	printf("%s\n", str);

	system("pause");
}
*/

// 字符串函数
/*
void main(){
	// 引入 <string.h>
}
*/

// 结构体  -- 把不同数据类型整合起来, 成为自定义的数据类型
/*
struct Man{
	// 成员
	char name[20];
	// char *name;
	int age;
	// int(*func)();
};

void main(){
	// 初始化结构体变量
	// struct Man m1 = { "jack", 21 };
	// m1 = {"Dick", 12};  // 这种方法赋值完之后, 只能通过 m1.age 赋值
	struct Man m1;
	m1.age = 23;
	// m1.name = "Dd";  // 当类型为 char name[20] 时不可这样赋值, 只能用下面的方法
	strcpy(m1.name, "Dd");
	sprintf(m1.name, "Json"); // 把内容格式化写入某个字符串

	struct Man m2 = m1;

	printf("%s, %d\n", m1.name, m1.age);
	printf("%s, %d\n", m2.name, m2.age);

	system("pause");
}
*/

// 结构体的几种写法
/*
// 上面是写法一
// 写法二:  声明就给了变量
struct Man{
	char name[20];
} m1; // 结构体变量名
// 写法三: 声明就赋值
struct Man1{
	char name[20];
} m2 = {"Sendy"};
// 写法四: 匿名结构体 -- 限制结构体个数
struct{
	char name[20];
} m3 = {"Dd"};

void main(){
	// 写法二:
	strcpy(m1.name, "Jack");
	printf("%s\n", m1.name);
	
	// 写法三:
	printf("%s\n", m2.name);

	// 写法四:
	printf("%s\n", m3.name);

	system("pause");
}
*/

// 结构体嵌套
/*
// 写法一
//struct Teacher{
//	char name[20];
//};
//struct Student{
//	char name[20];
//	struct Teacher t;
//};

// 写法二
struct Student{
	char name[20];
	struct Teacher{   // 内部声明的结构体 也能在外部使用
		char name[20];
	} t;
};

void main(){
	struct Student s = { "Dd", { "Dd" } };
	

	printf("%s, %s\n", s.name, s.t.name);

	system("pause");
}
*/

// 结构体与指针
/*
struct Man{
	char name[20];
};

void main(){
	struct Man m1 = { "Dd"};
	struct Man *p = &m1;

	printf("%s\n", m1.name);
	printf("%s\n", (*p).name);
	printf("%s\n", p->name);

	system("pause");
}
*/

// 结构体数组
/*
struct Man{
	char name[20];
};

void main(){
	struct Man mans[] = { { "Dd1" }, { "Dd2" }, { "Dd3" }, { "Dd4" } };
	struct Man *p = mans;

	// 结构体大小 -- 必须是最宽基本数据类型的整数倍, 如 结构体中有 {int a; double d;} 则 大小为 8*2 = 16
	printf("%d\n", sizeof(mans));

	for (; p < mans + 4; p++){
		printf("%s\n", p->name);
	}

	system("pause");
}
*/

/*
typedef struct Letter{
	char letter;
} Letter;

void main(){
	Letter letter[] = { 
		{ 74 }, { 88 }, { 44 }, { 32 }, 
		{ 73 }, { 32 }, { 76 }, { 111 }, { 118 }, 
		{ 101 }, { 32 }, { 89 }, { 111 }, { 117 }
	};

	Letter *p = letter;

	for (; p < letter + sizeof(letter); p++){
		printf("%c", p->letter);
	}

	printf("\n");
	system("pause");
}
*/

// 结构体动态内存分配
/*
struct Man{
	char *name;
	int age;
};

void main(){
	// 分配内存
	struct Man *mans = (struct Man*)malloc(sizeof(struct Man) * 10);
	struct Man *p = mans;

	p->name = "Dd";
	p->age = 10;
	p++;
	p->name = "Ad";
	p->age = 11;

	struct Man *loop_man = mans;
	for (; loop_man < mans + 2; loop_man ++){
		printf("%s, %d\n", loop_man->name, loop_man->age);
	}

	free(mans);

	system("pause");
}
*/

// typedef 起别名
/*
typedef int AA; // 给 int 起一个别名, 使用时 AA a = 1; 实质就是一个 int 类型
typedef int *AP;
typedef struct Man{
	char *name;
} M, *MP; // Man 的别名为 M, Man 的指针类型别名为 MP

void main(){
	M m = { "aa" };
	MP p = &m;

	system("pause");
}
*/

// 结构体函数指针成员

typedef struct Man{
	char name[20];
	void(*sayHi)(char*); // 函数指针
} Man;

void hello(char* str){
	printf("hello %s\n", str);
}

void main(){
	Man man = { "Dd", hello};

	man.sayHi(man.name);

	system("pause");
}