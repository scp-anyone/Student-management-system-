#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>

typedef struct STU
{
	int num;
	int cla;
	char name[10];
	char sex[8];
	char profession[10];
	float chinese_score;
	float math_score;
	float english_score;
	float all_score;
}stu;
typedef struct LIST
{
	stu all_message[200];
	int length;
}list;
//密读读取
void get_key_func(char* key)
{
	FILE* fp;
	int N = 100;
	if ((fp = fopen("C:\\key.txt", "r")) == NULL)
	{
		printf("学生信息文件打开失败\n");
		exit(0);
	}
	fgets(key, N, fp);
	fclose(fp);
}
//密码写入记忆
void put_key_func(char* key)
{
	FILE* fp;
	if ((fp = fopen("C:\\key.txt", "w")) == NULL)
	{
		printf("学生信息文件打开失败\n");
		exit(0);
	}

	fputs(key, fp);
	fclose(fp);
}

//读取函数
int read_func(list& peo)
{
	FILE* fp;
	char str[1000];
	int N = 1000;
	int i, flog = 0;
	if ((fp = fopen("C:\\get.txt", "r")) == NULL)
	{
		printf("学生信息文件打开失败\n");
		exit(0);
	}

	fgets(str, N, fp);
	while (fscanf(fp, "%d%d%s%s%s%f%f%f%f", &peo.all_message[flog].num, &peo.all_message[flog].cla, peo.all_message[flog].name, peo.all_message[flog].sex, peo.all_message[flog].profession, &peo.all_message[flog].chinese_score, &peo.all_message[flog].math_score, &peo.all_message[flog].english_score, &peo.all_message[flog].all_score) != EOF)
		flog++;
	peo.length = flog;
	fclose(fp);
	return 0;
}


//覆盖写回
int cover_func(list& peo)
{
	FILE* fp;
	int i;
	char ko = '\n';
	void sort_func(list & peo, int flog);
	if ((fp = fopen("C:\\put.txt", "w+")) == NULL)
	{
		printf("学生信息文件打开失败\n");
		exit(0);
	}
	sort_func(peo, 1);
	fprintf(fp, "学号      班级     姓名         性别      专业      语文成绩    数学成绩    英语成绩   总成绩\n");
	for (i = 0; i < peo.length; i++)
	{
		fprintf(fp, "%-11d%-10d%-13s%-11s%-12s%-13.2f%-14.2f%-15.2f%-8.2f%c", peo.all_message[i].num, peo.all_message[i].cla, peo.all_message[i].name, peo.all_message[i].sex, peo.all_message[i].profession, peo.all_message[i].chinese_score, peo.all_message[i].math_score, peo.all_message[i].english_score, peo.all_message[i].all_score, ko);
	}
	fclose(fp);
	return 0;
}
//备份到其他文件
void backups_func(list peo)
{
	system("color B4");
	void sort_func(list & peo, int flog);
	FILE* fp;
	int i, flog = 0;
	char ko = '\n';
	char filename[20];
	printf("输入备份目标文件路径与文件名:");
	scanf("%s", filename);
	if ((fp = fopen(filename, "w+")) == NULL)
	{
		printf("学生信息文件打开失败\n");
		exit(0);
	}
	sort_func(peo, 1);
	fprintf(fp, "学号      班级     姓名         性别      专业      语文成绩    数学成绩    英语成绩   总成绩\n");
	for (i = 0; i < peo.length; i++)
	{
		fprintf(fp, "%-11d%-10d%-13s%-11s%-12s%-13.2f%-14.2f%-15.2f%-8.2f%c", peo.all_message[i].num, peo.all_message[i].cla, peo.all_message[i].name, peo.all_message[i].sex, peo.all_message[i].profession, peo.all_message[i].chinese_score, peo.all_message[i].math_score, peo.all_message[i].english_score, peo.all_message[i].all_score, ko);
	}
	fclose(fp);
	printf("备份成功......\n");
	system("pause");
	system("cls");
}

//-------
void a_func()
{
	printf("------------------------------------------------------------------------------------------\n");
}
void b_func()
{
	printf("你的选择是：");
}
//
void c_func()
{
	printf("---------------------------------------------\n");
}
//返回主菜单
void return_func()
{
	printf("按任意键返回主菜单......");
	getch();
	system("cls");
}
//输入错误
void error_func()
{
	system("color 4");
	printf("输入错误，重新输入\n");
	Sleep(3000);
	system("color B4");

}

//总成绩计算函数
void  all_score_func(list& peo)
{
	int i;
	for (i = 0; i < peo.length; i++)
		peo.all_message[i].all_score = peo.all_message[i].chinese_score + peo.all_message[i].math_score + peo.all_message[i].english_score;
}


//输出函数
void a_output_func(list& peo, int i)
{
	if (peo.all_message[i].chinese_score < 60 || peo.all_message[i].english_score < 60 || peo.all_message[i].math_score < 60)
	{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //获取输出设备的句柄
		CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
		GetConsoleScreenBufferInfo(handle, &csbiInfo);  //获取窗口缓冲区信息
		WORD wOldColorAttrs = csbiInfo.wAttributes;     //获取初始定义的文本属性，即默认属性
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
		printf("学号:%-5d班级:%-5d姓名:%-15s性别:%-8s专业:%-8s语文:%-8.2f数学:%-8.2f英语:%-8.2f总成绩:%-8.2f\n", peo.all_message[i].num, peo.all_message[i].cla, peo.all_message[i].name, peo.all_message[i].sex, peo.all_message[i].profession, peo.all_message[i].chinese_score, peo.all_message[i].math_score, peo.all_message[i].english_score, peo.all_message[i].all_score);
		SetConsoleTextAttribute(handle, wOldColorAttrs);
	}
	else
		printf("学号:%-5d班级:%-5d姓名:%-15s性别:%-8s专业:%-8s语文:%-8.2f数学:%-8.2f英语:%-8.2f总成绩:%-8.2f\n", peo.all_message[i].num, peo.all_message[i].cla, peo.all_message[i].name, peo.all_message[i].sex, peo.all_message[i].profession, peo.all_message[i].chinese_score, peo.all_message[i].math_score, peo.all_message[i].english_score, peo.all_message[i].all_score);


}
void b_outpute_func(list& peo, int i)
{
	printf("%-11d%-10d%-13s%-11s%-12s%-13.2f%-14.2f%-15.2f%-8.2f%c", peo.all_message[i].num, peo.all_message[i].cla, peo.all_message[i].name, peo.all_message[i].sex, peo.all_message[i].profession, peo.all_message[i].chinese_score, peo.all_message[i].math_score, peo.all_message[i].english_score, peo.all_message[i].all_score);
}


//排序函数
void sort_func(list& peo, int flog)
{
	FILE* fp;
	int i, j;
	stu tem;
	//	1、按学号排序
	if (flog == 1)
	{
		for (i = 1; i < peo.length; i++)
		{
			for (j = 0; j < peo.length - i; j++)
				if (peo.all_message[j].num > peo.all_message[j + 1].num)
				{
					tem = peo.all_message[j];
					peo.all_message[j] = peo.all_message[j + 1];
					peo.all_message[j + 1] = tem;
				}
		}
	}
	//	2、按语文成绩排序
	if (flog == 2)
	{
		for (i = 1; i < peo.length; i++)
		{
			for (j = 0; j < peo.length - i; j++)
				if (peo.all_message[j].chinese_score > peo.all_message[j + 1].chinese_score)
				{
					tem = peo.all_message[j];
					peo.all_message[j] = peo.all_message[j + 1];
					peo.all_message[j + 1] = tem;
				}
		}
	}
	//	3、按数学成绩排序
	if (flog == 3)
	{
		for (i = 1; i < peo.length; i++)
		{
			for (j = 0; j < peo.length - i; j++)
				if (peo.all_message[j].math_score < peo.all_message[j + 1].math_score)
				{
					tem = peo.all_message[j];
					peo.all_message[j] = peo.all_message[j + 1];
					peo.all_message[j + 1] = tem;
				}
		}
	}
	// 4、按英语成绩排序
	if (flog == 4)
	{
		for (i = 1; i < peo.length; i++)
		{
			for (j = 0; j < peo.length - i; j++)
				if (peo.all_message[j].english_score < peo.all_message[j + 1].english_score)
				{
					tem = peo.all_message[j];
					peo.all_message[j] = peo.all_message[j + 1];
					peo.all_message[j + 1] = tem;
				}
		}
	}
	//5、按总成绩排序
	if (flog == 5)
	{
		for (i = 1; i < peo.length; i++)
		{
			for (j = 0; j < peo.length - i; j++)
				if (peo.all_message[j].all_score < peo.all_message[j + 1].all_score)
				{
					tem = peo.all_message[j];
					peo.all_message[j] = peo.all_message[j + 1];
					peo.all_message[j + 1] = tem;
				}
		}
	}
}

//分配到班级
void distribute_func(list& peo, list& peo1, list& peo2, list& peo3)
{
	int i, n1 = 0, n2 = 0, n3 = 0;
	peo1.length = 0;
	peo2.length = 0;
	peo3.length = 0;
	for (i = 0; i < peo.length; i++)
	{
		if (peo.all_message[i].cla == 1)
		{
			peo1.all_message[n1] = peo.all_message[i];
			n1++;
			peo1.length++;
		}
		if (peo.all_message[i].cla == 2)
		{
			peo2.all_message[n2] = peo.all_message[i];
			n2++;
			peo2.length++;
		}
		if (peo.all_message[i].cla == 3)
		{
			peo3.all_message[n3] = peo.all_message[i];
			n3++;
			peo3.length++;
		}
	}
	sort_func(peo1, 5);
	sort_func(peo2, 5);
	sort_func(peo3, 5);
}



//匹配函数
int match1_func(list& peo, int num)
{
	//学号匹配
	int i;
	for (i = 0; i < peo.length; i++)
	{
		if (peo.all_message[i].num == num)
			return i;
	}
	return -1;
}

int match2_func(list peo, char* name)
{
	//姓名匹配
	int i;
	for (i = 0; i < peo.length; i++)
	{
		if (strcmp(peo.all_message[i].name, name) == 0)//应该有问题   已经改
			return i;
	}
	return -1;
}






//挂科函数
void do_not_pass_func(list& peo, int cla, int flog)
{
	int i, n1 = 0, n2 = 0, n3 = 0;
	if (flog == 1)
	{//年级挂科
		printf("   1.年级语文挂科名单\n");
		for (i = 0; i < peo.length; i++)
		{
			if (peo.all_message[i].chinese_score < 60)
			{
				n1++;
				a_output_func(peo, i);
			}
		}
		if (n1 == 0)
			printf("      语文无挂科人员\n");
		c_func();
		printf("\n   2.年级数学挂科名单:\n");
		for (i = 0; i < peo.length; i++)
		{
			if (peo.all_message[i].math_score < 60)
			{
				n2++;
				a_output_func(peo, i);
			}
		}
		if (n2 == 0)
			printf("      数学无挂科人员:\n");
		c_func();
		printf("\n   3.年级英语挂科名单\n");
		for (i = 0; i < peo.length; i++)
		{
			if (peo.all_message[i].english_score < 60)
			{
				n3++;
				a_output_func(peo, i);
			}
		}
		if (n3 == 0)
			printf("      英语无挂科人员:\n");

	}
	//班级挂科
	else if (flog == 2)
	{

		printf("   %d班语文挂科名单:\n", cla);
		for (i = 0; i < peo.length; i++)
		{
			if (peo.all_message[i].chinese_score < 60)
				a_output_func(peo, i);
		}
		a_func();
		printf("\n   %d班数学挂科名单:\n", cla);
		for (i = 0; i < peo.length; i++)
		{
			if (peo.all_message[i].math_score < 60)
				a_output_func(peo, i);
		}
		a_func();
		printf("\n   %d班英语挂科名单:\n", cla);
		for (i = 0; i < peo.length; i++)
		{
			if (peo.all_message[i].english_score < 60)
				a_output_func(peo, i);
		}
		a_func();
		putchar(10);
	}
}
//班级情况函数
void class_condition_func(list& peo, int cla)
{
	float ave_chinese, ave_math, ave_english;
	float count_chinese = 0, count_math = 0, count_english = 0;
	int i;
	for (i = 0; i < peo.length; i++)
	{
		count_chinese += peo.all_message[i].chinese_score;
		count_math += peo.all_message[i].math_score;
		count_english += peo.all_message[i].english_score;
	}
	ave_chinese = count_chinese / peo.length;
	ave_math = count_math / peo.length;
	ave_english = count_english / peo.length;
	printf("%d班情况:\n", cla);

	printf("   %d班语文平均成绩:%-8.2f最高语文成绩:%-8.2f最低语文成绩:%-8.2f\n", cla, ave_chinese, peo.all_message[0].chinese_score, peo.all_message[peo.length - 1].chinese_score);
	printf("   %d班数学平均成绩:%-8.2f最高数学成绩:%-8.2f最低数学成绩:%-8.2f\n", cla, ave_math, peo.all_message[0].math_score, peo.all_message[peo.length - 1].math_score);
	printf("   %d班英语平均成绩:%-8.2f最高英语成绩:%-8.2f最低英语成绩:%-8.2f\n", cla, ave_english, peo.all_message[0].english_score, peo.all_message[peo.length - 1].english_score);
	a_func();
	printf("%d班级挂科名单:\n", cla);

	do_not_pass_func(peo, cla, 2);
	printf("%d班详细情况:\n", cla);
	for (i = 0; i < peo.length; i++)
		a_output_func(peo, i);
	a_func();
}

//密码函数
void key_show(char* key)
{
	while (1)
	{
		char key1[20];
		system("color 2");
		printf("请输入密码:");
		scanf("%s", key1);
		if (strcmp(key, key1) == 0)
		{
			printf("密码正确，正在进入......");
			Sleep(1000);
			system("cls");
			break;
		}
		else
			printf("输入错误，请重新输入密码......");
		Sleep(1000);
		system("cls");
	}
}

//欢迎界面
void welcome_show()
{
	system("color A1");
	printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t欢  ");
	Sleep(1000);
	system("color B2");
	printf("迎  ");
	Sleep(1000);
	system("color C3");
	printf("使  ");
	Sleep(1000);
	system("color E5");
	printf("用  ");
	Sleep(2000);
	system("cls");
}

//增删查改
//查询函数
void inquire_func(list& peo)
{
	int flog, flog1;
	int num, i;
	char name[15];
	while (1)
	{
		system("color B4");
		printf("选择查询方式\n");
		printf("   1、按照学号查询\n");
		printf("   2、按照线姓名查询\n");
		printf("   3、返回主菜单\n");
		b_func();
		scanf("%d", &flog1);

		switch (flog1)
		{
		case 1:
			printf("输入学号：");
			scanf("%d", &num);
			flog = match1_func(peo, num);
			if (flog != -1)
				a_output_func(peo, flog);
			else
				printf("无此人，查询失败\n");
			break;
		case 2:
			printf("输入姓名：");
			scanf("%s", name);
			flog = match2_func(peo, name);
			if (flog != -1)
				a_output_func(peo, flog);
			else
				printf("无此人，查询失败\n");
			break;
		case 3:
			break;
		default:
			error_func();
			break;
		}

		if (flog1 != 3)
		{
			printf("按任意键以继续查询......");
			getch();
			system("cls");
		}
		if (flog1 == 3)
		{
			system("cls");
			break;
		}
	}
}
//添加函数
void add_func(list& peo, list& peo1, list& peo2, list& peo3)
{
	system("color B4");
	int n, i, flog;
	char c;
	printf("输入添加学生的人数：");

	scanf("%d", &n);

	while ((c = getchar()) != '\n' && c != EOF);
	for (i = 0, flog = peo.length; i < n; i++, flog++)
	{
		printf("学号:");
		scanf("%d", &peo.all_message[flog].num);
		printf("班级:");
		scanf("%d", &peo.all_message[flog].cla);
		printf("姓名:");
		scanf("%s", peo.all_message[flog].name);
		printf("性别:");
		scanf("%s", peo.all_message[flog].sex);
		printf("专业:");
		scanf("%s", peo.all_message[flog].profession);
		printf("语文成绩:");
		scanf("%f", &peo.all_message[flog].chinese_score);
		printf("数学成绩:");
		scanf("%f", &peo.all_message[flog].math_score);
		printf("英语成绩:");
		scanf("%f", &peo.all_message[flog].english_score);
		if (n != 1)
			system("cls");
	}

	while ((c = getchar()) != '\n' && c != EOF);
	peo.length += n;
	all_score_func(peo);
	sort_func(peo, 5);
	distribute_func(peo, peo1, peo2, peo3);
	printf("添加%d个人成功，按任意键以返回主菜单...", n);
	getch();
	system("cls");
}

//修改函数
void change_func(list& peo, list& peo1, list& peo2, list& peo3)
{
	system("color B4");
	int flog, n, num, cla;
	float chinese_score = 0, math_score = 0, english_score = 0;
	char name[15], sex[8], profession[15];
	system("cls");
	while (1)
	{
		printf("输入需要修改学生的学号:");
		scanf("%d", &num);
		flog = match1_func(peo, num);
		if (flog == -1)
		{
			printf("查无此人，修改失败。\n按任意键以重新输出......");
			getch();
			system("cls");
			continue;
		}
		printf("   1、修改学号\n");
		printf("   2、修改班级\n");
		printf("   3、修改姓名\n");
		printf("   4、修改性别\n");
		printf("   5、修改专业\n");
		printf("   6、修改语文成绩\n");
		printf("   7、修改数学成绩\n");
		printf("   8、修改英语成绩\n");
		printf("   9、取消修改，返回主菜单\n");
		b_func();
		scanf("%d", &n);
		switch (n)
		{
		case 1:
			printf("学号修改为：");
			scanf("%d", &num);
			peo.all_message[flog].num = num;
			distribute_func(peo, peo1, peo2, peo3);
			break;
		case 2:
			printf("班级修改为：");
			scanf("%d", &cla);
			peo.all_message[flog].cla = cla;
			sort_func(peo, 5);
			distribute_func(peo, peo1, peo2, peo3);
			break;
		case 3:
			printf("姓名修改为：");
			scanf("%s", name);
			strcpy(peo.all_message[flog].name, name);
			distribute_func(peo, peo1, peo2, peo3);
			break;
		case 4:
			printf("性别修改为：");
			scanf("%s", sex);
			strcpy(peo.all_message[flog].sex, sex);
			distribute_func(peo, peo1, peo2, peo3);
			break;
		case 5:
			printf("专业修改为:");
			scanf("%s", profession);
			strcpy(peo.all_message[flog].profession, profession);
			distribute_func(peo, peo1, peo2, peo3);
			break;
		case 6:
			printf("语文成绩修改为：");
			scanf("%f", &chinese_score);

			peo.all_message[flog].chinese_score = chinese_score;
			all_score_func(peo);
			sort_func(peo, 5);
			distribute_func(peo, peo1, peo2, peo3);
			break;
		case 7:
			printf("数学成绩修改为：");
			scanf("%f", &math_score);
			peo.all_message[flog].math_score = math_score;
			all_score_func(peo);
			sort_func(peo, 5);
			distribute_func(peo, peo1, peo2, peo3);
			break;
		case 8:
			printf("英语成绩修改为：");
			scanf("%f", &english_score);
			peo.all_message[flog].english_score = english_score;
			all_score_func(peo);
			sort_func(peo, 5);
			distribute_func(peo, peo1, peo2, peo3);
			break;
		case 9:
			return_func();
			break;
		default:
			error_func();
		}
		if (n != 9)
		{
			printf("修改成功\n");
			printf("按任意键以继续......");
			getch();
			system("cls");
			break;
		}
		if (n == 9)
			break;
	}
}
//删除函数
void delete_func(list& peo, list& peo1, list& peo2, list& peo3)
{

	int i, num, flog, flog1;
	char name[15];
	while (1)
	{
		system("color B4");
		printf("选择删除方式\n");
		printf("   1、学号匹配删除\n");
		printf("   2、姓名匹配删除\n");
		printf("   3、返回主菜单\n");
		printf("你的选择为：");
		scanf("%d", &flog1);
		switch (flog1)
		{
		case 1:
			printf("输入学号：");
			scanf("%d", &num);
			flog = match1_func(peo, num);
			if (flog != -1)
			{
				for (i = flog; i < peo.length; i++)
				{
					peo.all_message[i] = peo.all_message[i + 1];
				}
				peo.length--;
				distribute_func(peo, peo1, peo2, peo3);
				sort_func(peo, 5);
				printf("删除成功,");
				printf("按任意键以继续......");
			}
			else
			{
				printf("删除失败，查无此人\n");
				printf("按任意键以继续......");
			}
			getch();
			system("cls");
			break;
		case 2:
			printf("输入姓名：");
			scanf("%s", name);
			flog = match2_func(peo, name);
			if (flog != -1)
			{
				for (i = flog; i < peo.length; i++)
				{
					peo.all_message[i] = peo.all_message[i + 1];
				}
				peo.length--;
				distribute_func(peo, peo1, peo2, peo3);
				sort_func(peo, 5);
				printf("删除成功,");
				printf("按任意键以继续......");
			}
			else
			{
				printf("删除失败，查无此人\n");
				printf("按任意键以继续......");
			}
			getch();
			system("cls");
			break;
		case 3:
			break;
		}
		if (flog1 == 3)
		{
			system("cls");
			break;
		}
	}

}

//班级函数
void class_func(list& peo, list& peo1, list& peo2, list& peo3)
{
	void class1_func(list & all, list & peo, int cla);
	int cla;
	while (1)
	{
		system("color B4");
		printf("选择查看的班级\n");
		printf("   1.一班成绩情况\n");
		printf("   2.二班成绩情况\n");
		printf("   3.三班成绩情况\n");
		printf("   4.返回主菜单\n");
		b_func();
		scanf("%d", &cla);
		switch (cla)
		{
		case 1:
			class1_func(peo, peo1, cla);

			break;
		case 2:
			class1_func(peo, peo2, cla);

			break;
		case 3:
			class1_func(peo, peo3, cla);

			break;
		case 4:
			return_func();
			break;
		default:
			error_func();
			break;
		}
		if (cla == 4)
			break;
	}
}
//班级副菜单

void class1_func(list& all, list& peo, int cla)
{
	system("color B4");
	float ave_chinese, ave_math, ave_english;
	float count_chinese = 0, count_math = 0, count_english = 0;
	int i, n;
	for (i = 0; i < peo.length; i++)
	{
		count_chinese += peo.all_message[i].chinese_score;
		count_math += peo.all_message[i].math_score;
		count_english += peo.all_message[i].english_score;
	}
	ave_chinese = count_chinese / peo.length;
	ave_math = count_math / peo.length;
	ave_english = count_english / peo.length;
	system("cls");
	while (1)
	{
		printf("%d班成绩情况\n", cla);
		printf("   1、语文成绩情况:\n");
		printf("   2、数学成绩情况:\n");
		printf("   3、英语成绩情况:\n");
		printf("   4、挂科名单:\n");
		printf("   5、情况总览:\n");
		printf("   6、返回上一层班级列表\n");
		printf("你的选择:");
		scanf("%d", &n);
		system("cls");
		switch (n)
		{
		case 1:
			printf("   %d班语文平均成绩:%-8.2f最高语文成绩:%-8.2f最低语文成绩:%-8.2f\n", cla, ave_chinese, peo.all_message[0].chinese_score, peo.all_message[peo.length - 1].chinese_score);
			break;
		case 2:
			printf("   %d班数学平均成绩:%-8.2f最高数学成绩:%-8.2f最低数学成绩:%-8.2f\n", cla, ave_math, peo.all_message[0].math_score, peo.all_message[peo.length - 1].math_score);
			break;
		case 3:
			printf("   %d班英语平均成绩:%-8.2f最高英语成绩:%-8.2f最低英语成绩:%-8.2f\n", cla, ave_english, peo.all_message[0].english_score, peo.all_message[peo.length - 1].english_score);
			break;
		case 4:
			do_not_pass_func(peo, cla, 2); break;
		case 5:
			class_condition_func(peo, cla);
		case 6:
			break;
		default:
			error_func();
			continue;
		}
		if (n != 6)
		{
			printf("按任意键以继续......");
			getch();
			system("cls");
		}
		if (n == 6)
			break;
	}
}
//年级函数
void grade_func(list& peo)
{
	system("color B4");
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //获取输出设备的句柄
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(handle, &csbiInfo);  //获取窗口缓冲区信息
	WORD wOldColorAttrs = csbiInfo.wAttributes;     //获取初始定义的文本属性，即默认属性
	int i;
	float ave_chinese, ave_math, ave_english;
	float count_chinese = 0, count_math = 0, count_english = 0;
	for (i = 0; i < peo.length; i++)
	{
		count_chinese += peo.all_message[i].chinese_score;
		count_math += peo.all_message[i].math_score;
		count_english += peo.all_message[i].english_score;
	}

	ave_chinese = count_chinese / peo.length;
	ave_math = count_math / peo.length;
	ave_english = count_english / peo.length;

	SetConsoleTextAttribute(handle, BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("一、年级成绩情况:\n");
	SetConsoleTextAttribute(handle, wOldColorAttrs);
	printf("   1.年级语文平均成绩:%-8.2f最高语文成绩:%-8.2f最低语文成绩:%-8.2f\n", ave_chinese, peo.all_message[0].chinese_score, peo.all_message[peo.length - 1].chinese_score);
	printf("   2.年级数学平均成绩:%-8.2f最高数学成绩:%-8.2f最低数学成绩:%-8.2f\n", ave_math, peo.all_message[0].chinese_score, peo.all_message[peo.length - 1].chinese_score);
	printf("   3.年级英语平均成绩:%-8.2f最高英语成绩:%-8.2f最低英语成绩:%-8.2f\n", ave_english, peo.all_message[0].english_score, peo.all_message[peo.length - 1].english_score);
	a_func();
	printf("\n\n");
	SetConsoleTextAttribute(handle, BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("二、年级挂科名单:\n");
	SetConsoleTextAttribute(handle, wOldColorAttrs);
	do_not_pass_func(peo, 0, 1);
	a_func();
	printf("\n\n");
	sort_func(peo, 5);
	SetConsoleTextAttribute(handle, BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("三、年级成绩详细情况:\n");
	SetConsoleTextAttribute(handle, wOldColorAttrs);
	for (i = 0; i < peo.length; i++)
		a_output_func(peo, i);
	a_func();
	putchar(10);
	return_func();
}
//读取其他文件
int read_other_func(list& peo, list& peo1, list& peo2, list& peo3)
{
	system("color B4");
	FILE* fp;
	char str[1000];
	int N = 1000;
	int i, flog = 0;
	char filename[20];
	printf("输入读取的文件路径与文件名:");
	scanf("%s", filename);

	if ((fp = fopen(filename, "r")) == NULL)
	{
		printf("学生信息文件打开失败\n");
		printf("按任意键返回主菜单......");
		getch();
		system("cls");
		return 0;
	}
	fgets(str, N, fp);
	while (fscanf(fp, "%d%d%s%s%s%f%f%f%f", &peo.all_message[flog].num, &peo.all_message[flog].cla, peo.all_message[flog].name, peo.all_message[flog].sex, peo.all_message[flog].profession, &peo.all_message[flog].chinese_score, &peo.all_message[flog].math_score, &peo.all_message[flog].english_score, &peo.all_message[flog].all_score) != EOF)
		flog++;
	peo.length = flog;
	fclose(fp);
	sort_func(peo, 5);
	distribute_func(peo, peo1, peo2, peo3);
	printf("读取成功......\n");
	Sleep(2000);
	system("cls");

}



//退出函数
void quit_func(list& peo)
{
	cover_func(peo);
}

//修改密码函数
void change_key_func(char* key)
{
	system("color B4");
	char key1[20];
	printf("密码修改为:");
	scanf("%s", key1);

	strcpy(key, key1);
	put_key_func(key);
	printf("修改成功......");
	Sleep(1000);
	system("cls");

}

int main()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //获取输出设备的句柄
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(handle, &csbiInfo);  //获取窗口缓冲区信息
	WORD wOldColorAttrs = csbiInfo.wAttributes;     //获取初始定义的文本属性，即默认属性
	int flog;
	char key[20];
	list peo, peo1, peo2, peo3;
	get_key_func(key);
	key_show(key);
	welcome_show();
	read_func(peo);
	sort_func(peo, 5);
	all_score_func(peo);
	distribute_func(peo, peo1, peo2, peo3);
	system("cls");
	while (1)
	{
		system("color B4");
		SetConsoleTextAttribute(handle, BACKGROUND_RED);
		printf("\n***************欢迎进入第二学期学生信息管理系统***************\n\n\n");
		SetConsoleTextAttribute(handle, wOldColorAttrs);
		SetConsoleTextAttribute(handle, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
		printf("-------------- 1、查询学生信息 ----------\n");
		SetConsoleTextAttribute(handle, wOldColorAttrs);
		SetConsoleTextAttribute(handle, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
		printf("-------------- 2、增添学生信息 ----------\n");
		SetConsoleTextAttribute(handle, wOldColorAttrs);
		SetConsoleTextAttribute(handle, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
		printf("-------------- 3、修改学生信息 ----------\n");
		SetConsoleTextAttribute(handle, wOldColorAttrs);
		SetConsoleTextAttribute(handle, BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
		printf("-------------- 4、删除学生信息 ----------\n");
		SetConsoleTextAttribute(handle, wOldColorAttrs);
		SetConsoleTextAttribute(handle, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
		printf("-------------- 5、班级学生信息 ----------\n");
		SetConsoleTextAttribute(handle, wOldColorAttrs);
		SetConsoleTextAttribute(handle, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
		printf("-------------- 6、年级学生信息 ----------\n");
		SetConsoleTextAttribute(handle, wOldColorAttrs);
		SetConsoleTextAttribute(handle, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
		printf("-------------- 7、备份信息 --------------\n");
		SetConsoleTextAttribute(handle, wOldColorAttrs);
		SetConsoleTextAttribute(handle, BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
		printf("-------------- 8、读取信息 --------------\n");
		SetConsoleTextAttribute(handle, wOldColorAttrs);
		SetConsoleTextAttribute(handle, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
		printf("-------------- 9、退出系统 --------------\n");
		SetConsoleTextAttribute(handle, wOldColorAttrs);
		SetConsoleTextAttribute(handle, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
		printf("---------------10、修改密码--------------\n");
		SetConsoleTextAttribute(handle, wOldColorAttrs);
		SetConsoleTextAttribute(handle, BACKGROUND_RED | BACKGROUND_INTENSITY);
		printf("\n**************************************************************\n");
		SetConsoleTextAttribute(handle, wOldColorAttrs);
		b_func();
		scanf("%d", &flog);
		//		fflush(stdin);
		system("cls");
		switch (flog)
		{
		case 1:
			inquire_func(peo); break;
		case 2:
			add_func(peo, peo1, peo2, peo3); break;
		case 3:
			change_func(peo, peo1, peo2, peo3); break;
		case 4:
			delete_func(peo, peo1, peo2, peo3); break;
		case 5:
			class_func(peo, peo1, peo2, peo3); break;
		case 6:
			grade_func(peo);
			break;
		case 7:
			backups_func(peo);
			break;
		case 8:
			read_other_func(peo, peo1, peo2, peo3); break;
		case 9:
			quit_func(peo);
			break;
		case 10:
			change_key_func(key);
			break;
		default:
			error_func();
			break;
		}
		if (flog == 9)
			break;
	}
	system("color E4");
	printf("感谢使用此系统，按任意键以退出\n");
	getch();

}