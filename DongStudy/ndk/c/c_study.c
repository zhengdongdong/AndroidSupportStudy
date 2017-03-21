#define _CRT_SECURE_NO_WARNINGS // �궨��, ���ﲻ�� scanf ����, ����ֱ��ʹ�� scanf_s()
// ����ͷ�ļ�(.h)  -- ͷ�ļ���ֻ������, ʵ���� .c ��
#include<stdio.h>
#include<stdlib.h> // scanf
#include<string.h>

//ganquan.info/standard-c/function/  c���Ժ����ٲ�

/*
c����ִ������
   Ԥ���� : Ϊ������׼������,����ı����滻����
1. ����   : �γ�Ŀ�����
2. ����   : ��Ŀ�������c���������Ӻϲ�,�γɿ�ִ���ļ�
3. ִ��

ͷ�ļ����߱���������ôһ������, �����������ҵ����������ʵ��

*/


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

	// long long  ->  %lld

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
/*
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
*/

// ָ������  -- һ���������� ++ -- (��Ϊ�������ڴ������������е�)
/*
void main(){
	int ids[] = { 1, 2, 3, 5, 7 };
	
	// ������ݱ����� ����������׵�ַ
	printf("%#x\n", ids);
	printf("%#x\n", &ids[0]);

	int *p = ids;
	printf("*p %d \n", *p);
	p++; // ��ǰ�ƶ� sizeof(��������) ���ֽ�
	printf("*p(p++��) %d \n", *p);

	// p �׵�ַ
	// p �ȼ��� &ids[0]  p+1 �ȼ��� &ids[1]
	// p+i �ȼ��� &ids[i]

	// *p �ȼ��� ids[0], *(a+1) �ȼ��� a[1]
	// *(p+i) �ȼ��� a[i]

	int uids[5];
	int *p = uids;
	int i = 0;
	for (; p < uids + 5; p++){ // ���ϵ�д��
		*p = i;
		i++;
	}

	system("pause");
}
*/

//ָ�����ö�ά���飨��ָ�룬��ָ�룩
/*
void main(){
	int a[2][3] = {95,82,56,17,29,30};
	//�������
	//���ѭ�������У��ڲ�ѭ��������
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
	//a��һ����ָ�룬ָ��һ��������Ԫ�ص����飬12
	//&a��һ��ָ���ά�����ָ�룬��ǰ��ά ����6��Ԫ�أ�24
	//*a ��һ��ָ��int�������ݵ�ָ�루a[0][0]����4
	//printf("%d\n", **a);

	//a��һ����ָ�룬�������һ�е�ָ�룬a+1�ڶ��е�ָ�룬�Դ�����
	printf("%#x,%#x\n",a,a+1);
	//*a������ĵ�һ�е�һ��Ԫ�ص�ָ�룬*a+1�������һ�еڶ���Ԫ�ص�ָ��
	printf("%#x,%#x\n",*a,*a+1);
	//*(a+1)������ĵڶ���1���е�һ(0)��Ԫ�ص�ָ��
	//ע�⣺��һ���������߼�
	printf("%#x,%#x\n",*(a+1),*(a+1)+1);


	//ȡ����ĵ�1�������У���2��������Ԫ��
	printf("%d\n",a[1][2]);
	printf("%d\n",*(*(a+1)+2));

	//�ܽ᣺
	//a[i][j] �ȼ��� *(*(a+i)+j)
	//&a[i][j] �ȼ��� (*(a+i)+j)

	getchar();
}
*/

// ����ָ��
/*
void msg(int i){
	printf("��Ϣ����: %d\n", i);
}

void main(){
	// ����ָ��
	// ���
	// ����ֵ����, ����ָ������, ���������б�
	void(*fun_p)(int i) = msg;

	fun_p(1);

	printf("%#x\n", msg);
	printf("%#x\n", &msg);

	system("pause");
}
*/

// ����ָ������
/*
int add(int a, int b){
	return a + b;
}

int minus(int a, int b){
	return a - b;
}

// �൱�� java �Ļص�
void msg(int(*p)(int a, int b), int m, int n){
	int result = p(m, n);
	printf("������: %d\n", result);
}

void main(){
	msg(add, 8, 9);
	msg(minus, 10, 2);

	system("pause");
}
*/

// ��̬�ڴ����
/*
// ջ�ڴ�
void stackFun(){
	// ���е������Զ�����, ��������, �Զ��ͷ�
	int a[1024];
}

// ���ڴ�
void heapFun(){
	// �ڶ��ڴ��Ϸ��� 40M
	int *p = malloc(1024 * 1024 * 10 * sizeof(int));
	// int *p = calloc(len, sizeof(int)); // calloc ������ malloc, ֻ���� calloc ����ڴ���г�ʼ��(��ֵ0), Ч�ʵ�һЩ

	// �ͷŶ��ڴ�
	free(p);
}

void main(){
	// c �����ڴ����
	// 1.ջ�� (stack)  
	// 1.1.windows��, һ��Ӧ��ջ�ڴ�һ����� 2M(ȷ���ĳ���)
	// 1.2.�Զ�����,�Զ��ͷ�
	// 2.���� (heep)
	// 2.1.�ɷ������ϵͳ 80% ���ڴ�
	// 2.2.�ֶ�����,�ֶ��ͷ�
	// 3.��̬��(ȫ�ֱ���)
	// 4.�ַ�������
	// 5.���������

	system("pause");
}
*/

// ��:��̬����
/*
void main(){
	// ��̬����
	// int a[10];

	// ��̬����
	int len;
	printf("���������ݳ���:");
	scanf_s("%d", &len);

	// �����ڴ�, p �ɵ��������׵�ַ
	int *p = malloc(len * sizeof(int));
	// int *p = calloc(len, sizeof(int));
	// ������Ԫ�ظ�ֵ
	int i = 0;
	for (; i < len; i++){
		p[i] = i;
		printf("%d, %#x\n", p[i], &p[i]);
	}

	// ���� p �ڴ�
	// realloc(ԭ�ڴ�ָ��, �ڴ��������ܴ�С)
	int *p2 = realloc(p, (5 + len) * sizeof(int)); // p2 �ĵ�ַ���ܺ� p һ��

	// ���·�����������:
	// 1. ��С, ��С�Ĳ������ݻᶪʧ
	// 2. ����, ��̬�ڴ������ڴ���������(Ϊʲô���Դ�������)
	// 2.1 ������ǰ�ڴ������Ҫ���ڴ�ռ��С, ֱ����չ�ڴ�, ����ԭָ��
	// 2.2 ��û���㹻�Ŀռ��С, ���Ҷ�����һ�����㹻��С���ڴ�ռ�, ��֮ǰ�����ݸ��ƹ���, ���ͷ�ԭ�����ڴ�
	// 2.3 ��ϵͳû���㹻�Ŀռ����, ����ʧ��, ���� NULL, ԭ����ָ����Ȼ��Ч

	if (p2 != NULL){
		int j = 0;
		for (; j < 5 + len; j++){
			p2[j] = j;
			printf("%d, %#x\n", p2[j], &p2[j]); // ����ʹ�� *p++ ���, �ᵼ���ͷ�ʧ��
		}
		// ��ʵֻҪ�ͷ� p2 �ͺ���, ��Ϊֻ�гɹ�����, p Ҫô���� p2, Ҫô�����Ѿ����ͷ�
		if (p != NULL){
			free(p);
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

// �ַ���
/*
void main(){
	// �ַ���д��
	// char str[] = { 'c', 'h', 'i', 'n', 'a', '\0' };
	// char str[] = { 'c', 'h', 'i', 'n', 'a' }; // ��������������
	// char str[8] = { 'c', 'h', 'i', 'n', 'a' }; // ���û��, �������Ƿ���������
	// char str[10] = "china";
	char* str = "china";
	// str[0] = 'a';  char* str �������޸� �����޸�, ʹ�� str[]
	printf("%s\n", str);

	system("pause");
}
*/

// �ַ�������
/*
void main(){
	// ���� <string.h>
}
*/

// �ṹ��  -- �Ѳ�ͬ����������������, ��Ϊ�Զ������������
/*
struct Man{
	// ��Ա
	char name[20];
	// char *name;
	int age;
	// int(*func)();
};

void main(){
	// ��ʼ���ṹ�����
	// struct Man m1 = { "jack", 21 };
	// m1 = {"Dick", 12};  // ���ַ�����ֵ��֮��, ֻ��ͨ�� m1.age ��ֵ
	struct Man m1;
	m1.age = 23;
	// m1.name = "Dd";  // ������Ϊ char name[20] ʱ����������ֵ, ֻ��������ķ���
	strcpy(m1.name, "Dd");
	sprintf(m1.name, "Json"); // �����ݸ�ʽ��д��ĳ���ַ���

	struct Man m2 = m1;

	printf("%s, %d\n", m1.name, m1.age);
	printf("%s, %d\n", m2.name, m2.age);

	system("pause");
}
*/

// �ṹ��ļ���д��
/*
// ������д��һ
// д����:  �����͸��˱���
struct Man{
	char name[20];
} m1; // �ṹ�������
// д����: �����͸�ֵ
struct Man1{
	char name[20];
} m2 = {"Sendy"};
// д����: �����ṹ�� -- ���ƽṹ�����
struct{
	char name[20];
} m3 = {"Dd"};

void main(){
	// д����:
	strcpy(m1.name, "Jack");
	printf("%s\n", m1.name);
	
	// д����:
	printf("%s\n", m2.name);

	// д����:
	printf("%s\n", m3.name);

	system("pause");
}
*/

// �ṹ��Ƕ��
/*
// д��һ
//struct Teacher{
//	char name[20];
//};
//struct Student{
//	char name[20];
//	struct Teacher t;
//};

// д����
struct Student{
	char name[20];
	struct Teacher{   // �ڲ������Ľṹ�� Ҳ�����ⲿʹ��
		char name[20];
	} t;
};

void main(){
	struct Student s = { "Dd", { "Dd" } };
	

	printf("%s, %s\n", s.name, s.t.name);

	system("pause");
}
*/

// �ṹ����ָ��
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

// �ṹ������
/*
struct Man{
	char name[20];
};

void main(){
	struct Man mans[] = { { "Dd1" }, { "Dd2" }, { "Dd3" }, { "Dd4" } };
	struct Man *p = mans;

	// �ṹ���С -- �������������������͵�������, �� �ṹ������ {int a; double d;} �� ��СΪ 8*2 = 16
	// {int a; double d; int b} Ҳ�� 16    {int a; double d; int b; char c} �� 24
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

// �ṹ�嶯̬�ڴ����
/*
struct Man{
	char *name;
	int age;
};

void main(){
	// �����ڴ�
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

// typedef �����
/*
typedef int AA; // �� int ��һ������, ʹ��ʱ AA a = 1; ʵ�ʾ���һ�� int ����
typedef int *AP;
typedef struct Man{
	char *name;
} M, *MP; // Man �ı���Ϊ M, Man ��ָ�����ͱ���Ϊ MP

void main(){
	M m = { "aa" };
	MP p = &m;

	system("pause");
}
*/

// �ṹ�庯��ָ���Ա
/*
typedef struct Man{
	char name[20];
	void(*sayHi)(char*); // ����ָ��
} Man;

void hello(char* str){
	printf("hello %s\n", str);
}

void main(){
	Man man = { "Dd", hello};
	man.sayHi(man.name);

	system("pause");
}
*/

// ������(��ͬ��)
// ��ͬ���͵ı�����ͬռ��һ���ڴ�(�໥����), ���ϱ����κ�ʱ��ֻ��һ����Ա����, ��ʡ�ڴ�
// ��С: ���ĳ�Ա��ռ���ֽ���
/*
union MyUnion{
	int x;
	int y;
	double z;
};

void main(){
	// �������� 
	// �ȸ� double ��ֵ, ������ֵ(z=2,x=1,y=3 -- 3,3,2.00)
	// �ȸ� int ��ֵ, intֵ���� 0(x=1,y=3,z=2 -- 0,0,2.00)
	// ֻ�����һ�θ�ֵ��Ч
	union MyUnion u; 
	u.x = 10;
	u.y = 11; // ������ע�͵�ʱ��, x��y ����ֵ, ����11
	//u.z = 11.2; // x , y û��ֵ, ֻ�� z ��ֵ

	
	printf("%d, %d, %lf\n", u.x, u.y, u.z);

	system("pause");
}
*/

// ö�� -- �޶�ȡֵ��Χ, 
/*
enum Day{  // �ڲ�ʵ���� 0,1,2,3...  Ҳ�����ֶ���ֵ, �������ظ�
	one,
	two,
	three,
	four
};
void main(){
	enum Day d = one;
	printf("%#x, %d\n", &d, d);

	d = 2;
	printf("%#x, %d\n", &d, d);

	system("pause");
}
*/

// IO ���� -- ��
// c ��д�ı��ļ���������ļ��Ĳ��������ڻس����з�
// д����ʱ, ÿ����һ�� \n , �Ὣ��ת���� \r\n
// ���ı�ʱ, ÿ����һ�� \r\n , �Ὣ��ת���� \n

/*
void main(){
	char path[] = "D:\\a.txt";

	// ���¿������ ��: ab ׷�Ӵ�һ���������ļ�, ��ĩβд��
	// b   �������ļ�
	// r   ֻ��, �ļ������
	// r+  �ɶ�д, �ļ������
	// w   ֻд, ���ļ�������, �ᴴ��
	// w+  �ɶ�д, ���ļ�������, �ᴴ��
	// a   �Ը��ӷ�ʽ��ֻд�ļ�, ���ļ�������, �ᴴ��, д��ᱻ��ӵ��ļ�β
	// a+  �Ը��ӷ�ʽ�򿪿ɶ�д�ļ�, ���ļ�������, �ᴴ��, д��ᱻ��ӵ��ļ�β
	// ����ֵ:  �ļ�ָ��, ����ʧ��, ����NULL, ���Ѵ��������� errno ��
	FILE *f = fopen(path, "r");
	if (f == NULL){
		printf("�ļ���ʧ��\n");
	}
	else {
		// ��ȡ
		char buff[50];
		while (fgets(buff, 50, f)) {  // fgets Ϊ��ȡ�ַ���
			printf("%s", buff);
		}
		fclose(f);
	}

	printf("\n");

	system("pause");
}
*/

// IO ���� -- д
/*
void main(){
	char path[] = "D:\\a.txt";

	FILE *f = fopen(path, "w");  // w ��д�Ḳ��
	if (f == NULL){
		printf("�ļ���ʧ��\n");
	}
	else {
		// д��
		char *txt = "I'm fine";
		fputs(txt, f);

		printf("д��ɹ�\n");

		fclose(f);
	}
	printf("\n");

	system("pause");
}
*/

// IO ���� -- �������ļ� -- ����
/*
void main(){
	char path_read[] = "D:\\a.txt";
	char path_write[] = "D:\\b.txt";

	FILE *f_read = fopen(path_read, "rb"); //rb ��ȡ�������ļ�
	FILE *f_write = fopen(path_write, "wb"); //rb д��������ļ�
	if (f_read == NULL){
		printf("�ļ���ʧ��\n");
	}
	else {
		int buff[50]; // ������
		int len = 0; // ÿ�ζ�ȡ�������ݳ���
		while ((len = fread(buff, sizeof(int), 50, f_read)) != 0) {
			fwrite(buff, sizeof(int), len, f_write);
		}

		fclose(f_read);
		fclose(f_write);
	}
	printf("\n");

	system("pause");
}
*/

// IO ���� -- ��ȡ�ļ���С
/*
void main(){
	char *path = "D:\\a.txt";
	FILE *f = fopen(path, "r");
	// ���¶�λ�ļ�ָ�� 
	// 0 ƫ���� ,SEEK_END �ļ�ĩβ
	fseek(f, 0, SEEK_END);
	// ���ص�ǰ�ļ�ָ������ļ���ͷ��ƫ����
	long len = ftell(f);
	
	printf("%ld\n", len);

	system("pause");
}
*/

// IO ��ϰ -- �ļ����ܽ���
/*
// ���ܷ��� -- �ı��ļ�
void crypt(char normal_path[], char crypt_path[]){
	FILE *normal_f = fopen(normal_path, "r");
	FILE *crypt_f = fopen(crypt_path, "w");
	// һ�ζ�һ���ַ�
	int ch;//(ch = fgetc(normal_f) != EOF)
	while ((ch = fgetc(normal_f)) != EOF){ // End of File
		// ����(���)
		fputc(ch ^ 9, crypt_f);
	}
	fclose(crypt_f);
	fclose(normal_f);
}

// ���ܷ���
void decrypt(char crypt_path[], char decrypt_path[]){
	FILE *crypt_f = fopen(crypt_path, "r");
	FILE *decrypt_f = fopen(decrypt_path, "w");
	// һ�ζ�һ���ַ�
	int ch;
	while ((ch = fgetc(crypt_f)) != EOF){ // End of File
		// ����(���)
		fputc(ch ^ 9, decrypt_f);
	}
	fclose(decrypt_f);
	fclose(crypt_f);
}

void main(){
	//crypt("D:\\a.txt", "D:\\b.txt");

	decrypt("D:\\b.txt", "D:\\c.txt");

	system("pause");
}
*/

// IO ��ϰ -- �ļ����ܽ���
// ��ȡ�������ļ��е�����ʱ, һ��һ���ַ���ȡ
// ����: love
/*
// ���ܷ��� -- �ı��ļ�
void crypt(char normal_path[], char crypt_path[], char password[]){
	FILE *normal_f = fopen(normal_path, "rb");
	FILE *crypt_f = fopen(crypt_path, "wb");
	// һ�ζ�һ���ַ�
	int ch;
	int i = 0;
	int pwd_len = strlen(password);
	while ((ch = fgetc(normal_f)) != EOF){ // End of File
		// ����(���)
		fputc(ch ^ password[i % pwd_len], crypt_f);
		i++;
	}
	fclose(crypt_f);
	fclose(normal_f);
}

// ���ܷ���
void decrypt(char normal_path[], char crypt_path[], char password[]){
	FILE *normal_f = fopen(normal_path, "rb");
	FILE *crypt_f = fopen(crypt_path, "wb");
	// һ�ζ�һ���ַ�
	int ch;
	int i = 0;
	int pwd_len = strlen(password);
	while ((ch = fgetc(normal_f)) != EOF){ // End of File
		// ����(���)
		fputc(ch ^ password[i % pwd_len], crypt_f);
		i++;
	}
	fclose(crypt_f);
	fclose(normal_f);
}

void main(){
	//crypt("D:\\a.txt", "D:\\b.txt", "love");

	decrypt("D:\\b.txt", "D:\\c.txt", "love");

	system("pause");
}
*/

// define ����
// �궨��(���滻,Ԥ����ָ��), û��ָ������, ���ڱ���ʱ�滻����Ӧλ��
// 1. �����ʾ
// 2. ���峣��
// 3. ����"�꺯��"

// ���û�ж��� XX, ����XX, ����д��ֹ�ظ�����, һ����ͷ�ļ�ʹ��
// �°汾�������� #pragma once void printB();
//#ifndef XX
//#define XX
////#include <string.h>
//#endif

#define MAX_LEN 100  

void dd_read(){
	printf("read\n");
}
void dd_write(){
	printf("write\n");
}

#define jni(NAME) dd_##NAME();

// #define LOG(FORMAT,...) printf(FORMAT, __VA_ARGS__); // __VA_ARGS__ �ɱ����
#define LOG(LEVEL, FORMAT, ...) printf(LEVEL); printf(FORMAT, __VA_ARGS__);
#define LOG_I(FORMAT, ...) LOG("INFO:", FORMAT, __VA_ARGS__);
void main(){
	int i = 10;
	if (i < MAX_LEN){
		printf("aaa");
	}

	jni(read);
	jni(write);

	// LOG("%s%d\n","abc:", 123);

	LOG_I("%s%d\n","abc:", 123);

	system("pause");
}