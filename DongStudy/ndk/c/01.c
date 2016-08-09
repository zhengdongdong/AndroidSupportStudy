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