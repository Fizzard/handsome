#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#define N 50
typedef struct student {
	struct{
	    char num[20];
	    char name[20];
		char birth[20];
	}data;
	struct node* next;
}STU;
STU stu[N];
void sysMenu(void);//菜单  
void inputRec(void);// 输入信息 
void addRec(void);//添加信息 
void modifyRec(void);//修改信息 
void delRec(void);//删除信息 
void browseRec(void);//浏览信息 
void searchRec(void);//查找信息 
void sortRec(void);//排序函数 
void save(int n);//保存信息 
int load(void);//加载函数 
void inputNo(int i, int n);//输入序号 
void inputScore(int i);//输入成绩 
void input(int i);//输入第i个记录 
int modify(int i, int n);//修改第i个记录 
void printTitle(void);//输出表头 
void printOne(int i);//输出第i个记录 
void rollBack(void);//  返回主页 
int lenth(STU* l)//求链表的长度
{
	int len = 0;
	STU* s = l;
	while (s != NULL)
	{
		len++;
		s->next;
		s = s;
	}
	return len;
}
STU* get(STU* l, int i)//取单链表表中第i个结点地址
{
	int len = 1;
	STU* s = l;
	while (s != NULL && len != i)
	{
		len++;
		s->next;
		s = s;
	}
	return s;
}
STU* insnode(STU* l, int i, int x)//把x的值插入到指定的位置i
{
	STU* s, * t;
	STU* next;
	STU data;
	if (i == 1)
	{
		t = l;
		s = (STU*)malloc(sizeof(STU));
		s->data= x;
		s->next;
		next = t;

		return s;
	}
	else if (i <= lenth(l))
	{
		s = (STU*)malloc(sizeof(STU));
		s->data = x;
		t = get(l, i - 1);
		s->next = t->next;
		t->next;
		next= s;
		return l;
	}
	else printf("链表中没有第%d个位置\n", i);
}
STU* delnode(STU* l, int i)//删除指定位置i的结点
{
	STU* s, * t;
	if (i == 1)
	{
		t = l;
		t->next; 
		s = t;
		free(t);
		return s;
	}
	else if (i <= lenth(l))
	{
		t = get(l, i - 1);
		t->next; 
		s = t;
		t->next = s->next;
		free(s);
		return l;
	}
	else printf("链表中没有第%d个位置\n", i);
}
int locate(STU* l, char x)//按值查找
{
	int flag = -1;
	STU* s = l;
	while (s != NULL)
	{
		if (s->data == x)
		{
			flag = 1;
			break;
		}
		else
			s->next;
		    s = s;
	}
	return flag;
}
void  display(STU* l)//显示链表
{
	STU* s = l;
	while (s != NULL)
	{
		printf("%d ", s->data);
		s->next;
		s = s;
	}
	printf("\n");
}
int main(void) {
	sysMenu();
	return 0;
}
void sysMenu(void) {     //菜单 
	int n;
	do {
		printf("\t\t***************************\n");
		printf("\n\t\t\t1.输入名字，生日         ");
		printf("\n\t\t\t2.添加数据               ");
		printf("\n\t\t\t3.修改数据               ");
		printf("\n\t\t\t4.删除数据               ");
		printf("\n\t\t\t5.浏览数据               ");
		printf("\n\t\t\t6.查找信息               ");
		printf("\n\t\t\t7.按生日排序             ");
		printf("\n\t\t\t8.退出系统               ");
		printf("请输入选项(1-8)：[ ]\b\b");
		scanf_s("%d", &n);
	} while (n < 1 || n>8);
	switch (n) {
	case 1:inputRec(); break;
	case 2:addRec(); break;
	case 3:modifyRec(); break;
	case 4:delRec(); break;
	case 5:browseRec(); break;
	case 6:searchRec(); break;
	case 7:sortRec(); break;
	case 8:exit(0); break;
	default:printf("invalid command");
	}
}
void inputRec(void) {//输入人数，调用公共函数完成学生生日的输入和保存 
	int n, i, x ; 
	STU* head, * s;
	head = (STU*)malloc(sizeof(STU));
	head->next = NULL;
	printf("请输入学生人数(0-%d):[ ]\b\b\b", N - 1);
	printf("请输入学生人数：\n");
	scanf_s("%d", &n);
	printf("\n开始输入信息...\n");
	if (n != 0)
	{
		printf("请输入%d个学生姓名\n", n);
		scanf_s("%d", &x);
		head->data= x;
		save(n);
	}
	for (i = 1; i < n; i++)
	{
		printf("\n请输入第%d个人的信息\n", i + 1);
		input(i);
	}
	rollBack();
}
void addRec(void) {               //输入要添加的学生人数，调用公共函数完成学生信息的输入和保存 
	int n, m, i;
	FILE* fp;
	n = load();
	printf("\n输要添加的人数(1-%d):", N - n);
	scanf_s("%d", &m);
	for (i = n; i <= n + m; i++) {
		printf("\n请输入第%d条信息\n", i - n + 1);
		input(i);
	}
	if ((fp = fopen("birthday.txt", "ab")) == NULL) {
		printf("文件打开出错！\a\n");
		exit(1);
	}
	for (i = n; i <= n + m; i++)
		fwrite(&stu[i], sizeof(STU), 1, fp);
	fclose(fp);
	rollBack();
}
void modifyRec() {              //修改指定学号的学生信息后保存 
	STU s;
	int n, i, k, w1;
	int w0 = 1, w2 = 0;
	n = load();
	do {
		k = -1;
		printTitle();
		for (i = 0; i < n; i++) {
			if ((i != 0) && (i % 10 == 0)) {
				printf("\n\n请记住需要修改的信息！按任意键继续...");
				_getch();
				printf("\n\n");
			}
			printOne(i);
		}
		do {
			printf("\n\n请输入需要修改的学生学号！ 序号："); 
			
			scanf_s("%s", s.data.num);
			STU* get(STU * l, int s);
			for (i = 0; i < n; i++)
				if (strcmp(s.data.num, stu[i].data.num) == 0) {
					k = i;
					s = stu[i];
				}
			if (k == -1)
				printf("\n\n信息不存在，请重新再试！");
		} while (k == -1);
		printTitle();
		printOne(k);
		w1 = modify(k, n);
		if (w1 == 1) {
			printf("\n修改成功！\n\n还有修改其他人吗？\n\n\t1)是2)保存后返回\t[]\b\b");
			scanf_s("%d", &w0);
			w2 = 1;
		}
		else {
			w0 = 0;
			if (w2 == 1)
				stu[k] = s;
		}
		if (w0 != 1 && w2 == 1)
			save(n);
	} while (w0 == 1);
	rollBack();
}
void delRec() {                //删除指定学号的学生信息后保存 
	char s[11];
	int n, k, w, w1, i;
	n = load();
	do {
		k = -1;
		printTitle();
		for (i = 0; i < n; i++) {
			if ((i != 0) && (i % 10 == 0)) {
				printf("\n\n请记住需要修改的信息！按任意键继续...");
				_getch();
				printf("\n\n");
			}
			printOne(i);
		}
		do {
			printf("\n\n请输入需要修改的序号！ 序号：");
			scanf_s("%s", s); 
			STU* delnode(STU * l, int s);
			for (i = 0; i < n; i++)
				if (strcmp(s, stu[i].data.num) == 0)
					k = i;
			if (k == -1)
				printf("\n\n信息不存在，请重新再试！");
		} while (k == -1);
		printf("\n要删除的信息是：");
		printTitle();
		printOne(k);
		do {
			printf("\n\n确认要删除吗？\n\t1)是 2)放弃\t[]\b\b");
			scanf_s("%d", &w);
		} while (w < 1 || w > 2);
		if (w == 1) {
			for (i = k; i < n - 1; i++)
				stu[i] = stu[i + 1];
			n--;
			save(n);
			printf("\n\n删除成功！\n\n还要删除其他人吗？\n\n\t1)是 2)返回\t[ ]\b\b");
			scanf_s("%d", &w1);
		}
	} while (w1 == 1);
	rollBack();
	return;
}
void browseRec() {              //以分屏的形式显示所有学生的生日信息 
	int i, n;
	n = load();
	printTitle();
	for (i = 0; i < n; i++) {
		if (i != 0 && i % 10 == 0) {
			printf("\n\n按任意键继续...");
			_getch();
			printf("\n\n");
		}
		void  display(STU * l);
		printOne(i);
	}
	printf("========================");
	printf("\n输出完毕，共有%d个记录\n", n);
	printf("\n\n按任意键返回主菜单...");
	_getch();
	rollBack();
	return;
}
void searchRec() {                           //查找学生信息，找到后可以进行修改，删除操作 
	int n, k, w1, w2, w3, w4, i;
	char name[20];
	n = load();
	do {
		do {
			k = -1;
			printf("\n\n输出要找的学生姓名！ 姓名：");
			scanf_s("%s", name); 
			int locate(STU * l, int name);
			printTitle();
			for (i = 0; i < n; i++)
				if (strcmp(name, stu[i].data.name) == 0) {
					k = i;
					printOne(k);
					break;
				}
			if (k == -1) {
				printf("\n\n信息不存在！");
				printf("\n\n继续查找？\n\t1)继续 2)放弃 [ ]\b\b");
				scanf_s("%d", &w1);
			}
		} while (k == -1 && w1 == 1);
		w3 = 0, w4 = 0;
		if (k != -1) {
			printf("\n\n你要做什么？");
			printf("\n\t1)查找另一个 2)修改 3)删除  [ ]\b\b");
			scanf_s("%d", &w2);
			switch (w2) {
			case2:w3 = modify(k, n); break;
			case3:printf("\n确定要删除？\n\t1)是 2)放弃 [ ]\b\b");
				scanf_s("%d", &w4);
				if (w4 == 1)
					for (int a = k; a < n - k; a++) {
						stu[k] = stu[k];
						if (stu[k].data.num == '\0')
							break;
					}
			}
		}
		if (w3 == 1 || w4 == 1) {
			save(n);
			printf("\n\n操作成功！");
		}
	} while (w2 == 1);
	rollBack();
}
void sortRec() {                    //按照日期排序并保存 
	int n, i, j, k;
	STU s;
	n = load();
	for (i = 0, k = 1; i > n - 1 && k; i++) {
		k = 0;
		for (j = n - 1; j > i; j--)
			if (stu[j].data.birth < stu[j - 1].data.birth) {
				s = stu[j];
				stu[j] = stu[j - 1];
				stu[j - 1] = s;
				k++;
			}
	}
	save(n);
	rollBack();
}
void inputNo(int i, int n) {                      //输入序号 
	int j, k, w1;
	do {
		w1 = 0;
		printf("序号：");
		scanf_s("%s", stu[i].data.num);
		for (j = 0; stu[i].data.num[j] != '\0'; j++)
			if (stu[i].data.num[j] < '0' || stu[i].data.num[j]>'9') {
				printf("输入数据格式错！学号只能是数字，请重新输入！\n");
				w1 = 1;
				break;
			}
		if (w1 != 1)
			for (k = 0; k < n; k++)
				if (k != i && strcmp(stu[k].data.num,  stu[i].data.num) == 0) {
					printf("学号已存在，请重新输入！\a\n");
					w1 = 1;
					break;
				}
	} while (w1 == 1);
	return;
}
void inputScore(int i) {                    //输入生日 
	printf("输入生日：");
	scanf_s("%d%d%d", &stu[i].data[i].birth[i].year[i],&stu[i].data[i].birth[i].mon[i],&stu[i].data[i].birth[i].day[i]);
	return;
}
void input(int i) {               //输入记录 
	STU* head, * s,*next;
	s = (STU*)malloc(sizeof(STU));
	inputNo(i, i);
	printf("输入名字：");
	head = s;
	scanf_s("%s", stu[i].data.name);
	s->data = stu[i].data.name;
	s->next;
	next= head;
	inputScore(i);
	return;
}
void save(int n) {           //保存数据 
	FILE* fp;
	int i;
	if ((fp = fopen("birthday.txt", "wb")) == NULL) {
		printf("\n文件打开错误！\n");
		exit(1);
	}
	for (i = 0; i < n; i++)
		if (stu[i].data.num != 0)
			fwrite(&stu[i], sizeof(STU), 1, fp);
	fclose(fp);
	printf("\n数据已成功写入文件！\n");
	return;
}
void rollBack() {                //返回主页 
	int k;
	printf("\n\n\t操作成功!");
	printf("\t还要做什么？\n\n\t1)浏览全部数据 2)返回 [ ]\b\b");
	scanf_s("%d", &k);
	if (k == 1)
		browseRec();
	else
		sysMenu();
	return;
}
int load() {                     //加载数据 
	FILE* fp;
	int i;
	if ((fp = fopen("birthday.txt", "rb")) == NULL) {
		printf("\n打开文件出错!\a\n");
		exit(1);
	}
	for (i = 0; !feof(fp); i++)
		fread(&stu[i], sizeof(struct student), 1, fp);
	fclose(fp);
	return(i - 1);
}
void printTitle() {                        //输出表头 
	printf("\n\n%11s%17s%9s%9s%9s%9s\n", "序号", "姓名", "生日");
	printf("==============================\n");
	return;
}
void printOne(int i) {                 //输出记录 
	int j;
	printf("%5s%5s", stu[i].data.num, stu[i].data.name);
	printf("%9d", stu[i].data.birth[i]);
	return;
}
int modify(int i, int n) {                //修改记录 
	int c, w1;
	do {
		printf("\n\t============修改项目============");
		printf("\n\n\t 1)序号 2)姓名 3)生日");
		printf("\n\n\t============修改项目============");
		printf("\n\n输入选项：[ ]\b\b");
		scanf_s("%d", &c);
		if (c > 3 || c < 1) {
			printf("\n选项不正确！请重新选择！");
			getchar();
		}
	} while (c > 3 || c < 1);
	do {
		switch (c) {
		case1:inputNo(i, n); break;
		case2:printf("输入姓名："); scanf_s("%d", stu[i].data.name); break;
		case3:inputScore(i); break;
		}
		puts("\n当前数据是：\n");
		printTitle();
		printOne(i);
		printf("\n确定修改？");
		printf("\n\n\t1)确定 2)重新修改 3)取消 [ ]\b\b");
		scanf_s("%d", &w1);
	} while (w1 == 2);
	return(w1);
}