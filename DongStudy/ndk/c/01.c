//#define _CRT_SECURE_NO_WARNINGS // �궨��, ���ﲻ�� scanf ����, ����ֱ��ʹ�� scanf_s()
// ����ͷ�ļ�(.h)  -- ͷ�ļ���ֻ������, ʵ���� .c ��
#include<stdio.h>
#include<stdlib.h> // scanf

// ��ں��� - 1
/*
int main(int arg, char* str){

}
*/

// ��ں��� - 2
/*
void main(){
	printf("hello world \n");

	system("pause"); // pause:�����������. (windows ����, �� system("mspaint") ��ϵͳ����)
	// getchar(); // �ȴ�����
}
*/

// ������������
// int short long float double char
/*
void main(){
	// ����
	int input;
	//scanf("%d", &input); #define _CRT_SECURE_NO_WARNINGS
	scanf_s("%d", &input); 

	// ����/���ռλ��
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
	printf("ʮ������ = %x \n", p);
	int e = 12;
	printf("�˽��� = %o \n", e);
	char str[] = "hello world";
	printf("string = %s \n", str);
	
	// ��ռ�ֽڴ�С
	printf("int :  %d \n", sizeof(int));  //4
	printf("short :  %d \n", sizeof(short)); //2
	printf("long :  %d \n", sizeof(long)); //4
	printf("float :  %d \n", sizeof(float)); //4
	printf("double :  %d \n", sizeof(double)); //8
	printf("char :  %d \n", sizeof(char)); //1

	system("pause");
}
*/

// ѭ��
/*
void main(){
	int i = 0;
	for (; i < 10; i++){ // ע��: ����� java �Ȳ�һ��, �� windows �� for(int i=0;..) ����û����, linux ���ܻ������, ������c�ı�׼д��
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

// ָ�� -- ָ��洢���Ǳ������ڴ��ַ
/*
void main(){
	int i = 100;
	int *p = &i; // ָ������һ����ַ, ����ָ��Ϊ�λ�������?  ָ��ĵ�ַֻ�ǿ�ʼ, ���ͻ��֪����ʲôλ�� (��int, �����4���ֽ�)
	printf("i : %d\n", i);
	printf("p : %#x \n", p);  //%x ��ʮ������, %#x �Ǹ�ʽ���� -- 0x..
	printf("*p : %d\n", *p);

	*p = 10;
	printf("ͨ�� *p �ı��� i : %d\n", i);

	// NULL ��ָ��
	int *pn = NULL;
	// printf("p - NULL : %#x\n", pn); 0x000000 ϵͳ����λ��, ���������, �� 100 1000 ����Щλ�ö�������� ���������
	printf("p - NULL : %d\n", *pn);

	system("pause");
}
*/

// �༶ָ�� -- ����һ��ָ�������ַ��ָ��

void main(){
	int a = 50;
	// p1 ���� a �ĵ�ַ
	int *p1 = &a;
	// p2 ���� p1 �ĵ�ַ
	int **p2 = &p1;

	printf("p1 -> %#x\n", p1);
	printf("p2 -> %#x\n", p2);
	printf("*p2 -> %#x\n", *p2);

	system("pause");
}