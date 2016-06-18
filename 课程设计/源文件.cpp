#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stu {
    char stuNo[20];
    char stuName[20];
    char dormNo[10];  //宿舍号
    char stuAge[3];
    char stuSex[3];
    char stuNative[20];
    char stuMajor[20];//专业
}Stu;
/*********************************************
 *    用来存放数据文件的目录
 *
 */

char routeStu[] = "E:\\课程设计\\Data\\stuData";
char routeStuNum[] = "E:\\课程设计\\Data\\stuNum";
char routeSq[] = "E:\\课程设计\\Data\\sq";     //标记信息
/********************************************/
void Swap(Stu &a, Stu &b, int flag)
{
    /**
     *  此函数实现两个结构体进行交换  用于排序和插入操作中
     *  flag 有三个值 1  2  3
     *  flag == 1 时进行学号比较并交换
     *  flag == 2 时进行姓名比较并交换
     *  flag == 3 时进行宿舍号比较并交换
     */
    Stu temp;       //结构体交换临时变量
    if (flag == 1)
    {
        if (strcmp(a.stuNo, b.stuNo) > 0) {
            temp = a;
            a = b;
            b = temp;
        }
    }
    else if (flag == 2)
    {
        if (strcmp(a.stuName, b.stuName) > 0) {
            temp = a;
            a = b;
            b = temp;
        }
    }
    else
    {
        if (strcmp(a.dormNo, b.dormNo) > 0)
        {
            temp = a;
            a = b;
            b = temp;
        }
        else if(strcmp(a.dormNo, b.dormNo)==0 && strcmp(a.stuNo, b.stuNo)>0)
        {
            temp = a;
            a = b;
            b = temp;
        }
    }
}

void InsertStu(Stu stu[], int stuNum, Stu &stuTemp, int flag)
{
    /**
     *  功能：接受要插入学生信息 并按指定顺序插入
     *  st[] 成员结构体数组
     *  stuNum  学生人数
     *  stuTemp 要插入学生结构体
     *  flag 按何种顺序插入
     *  flag == 1 学号
     *  flag == 2 姓名
     *  flag == 3 宿舍号
     *  说明：此函数可需调用 Swap(Stu &a, Stu &b, int flag)   函数
     */
    stu[stuNum] = stuTemp;

    for (int i=stuNum; i>0; i--)
    {
        Swap(stu[i-1], stu[i], flag);
    }
}

/****************************************************/
void OutStuInfo(Stu stu[], int m)
{
    /**
     *  功能：输出学生信息 并进行简单排版
     *  stu[]   结构体数组
     *  m   要输出学生结构体下标
     */
    //printf("***********************************************************************\n");
    //printf("*  学号        姓名      性别 年龄 籍贯        专业           宿舍号  *\n");
    printf("*                                                                     *\n");
    printf("*  %-12s", stu[m].stuNo);

    printf("%-10s", stu[m].stuName);
    printf("%-5s", stu[m].stuSex);
    printf("%-5s", stu[m].stuAge);

    printf("%-12s", stu[m].stuNative);
    printf("%-15s", stu[m].stuMajor);
    printf("%-8s", stu[m].dormNo);

    printf("*\n");

}


void OutDormInfo(Stu stu[], int m)
{
    /**
     *  输出宿舍成员信息 接收一成员 stu[m]
     *  按学号顺序输出该宿舍所有成员信息
     *  并进行简单排版
     */
    int min = m, max = m;
    while (strcmp(stu[min-1].dormNo, stu[min].dormNo) == 0)
        min--;
    while (strcmp(stu[max+1].dormNo, stu[max].dormNo) == 0)
        max++;
    printf("\n该宿舍人数为 %d\n", max-min+1);
    printf("***********************************************************************\n");
    printf("*  学号        姓名      性别 年龄 籍贯        专业           宿舍号  *\n");
    for (int i=min; i<=max; i++)
    {
        OutStuInfo(stu, i);
    }
    printf("***********************************************************************\n");
}

/*****************************************************/
bool JudgeMarry(char str1[], char str2[])
{
    /**
     *  功能实现模糊匹配判断
     *  假设str2 匹配 str1
     *  规定： str2 长度大于等于 str1
     *         str2 顺序包含 str1中字符
     *         即为匹配成功
     *  如：str1 = "abcde"   str2 == "ace" / "abd" 等均为成功
     */
    int s1 = strlen(str1), s2 = strlen(str2);
    if (s1 < s2)   return false;
    int i=0, j=0;
    while (j<s2 && i<s1)
    {
        if (str1[i] == str2[j])
        {
            i++;    j++;
        }
        else
        {
            i++;
        }
    }
    if (j == s2)    return true;
    else    return false;
}

void DimSearch(Stu stu[], int stuNum, char s[], int flag)
{
    /**
     *  功能：模糊查找
     *  接受一个字符串按照指定的flag 进行模糊查找
     *  flag 取 1 2
     *  flag == 1   学号
     *  flag == 2   姓名
     */
    bool temp = true;
    if (flag == 1)
    {
        for (int i=0; i<stuNum; i++)
        {
            if (JudgeMarry(stu[i].stuNo, s))
            {
                OutStuInfo(stu, i);
                temp = false;
            }
        }

    }
    else
    {
        for (int i=0; i<stuNum; i++)
        {
            if (JudgeMarry(stu[i].stuName, s))
            {
                OutStuInfo(stu, i);
                temp = false;
            }
        }
        return;
    }
    if (temp)
        printf("\n!!! 没有匹配结果\n");
}

/*****************************************************/
void BublleSort(Stu stu[], int stuNum, int flag)
{
    /**
     *  功能：为冒泡排序函数 用于结构体排序
     *  接收三个参数
     *  stu[] 结构体数组 stuNum学生人数  flag 按哪种方式排序
     *  flag == 1  按学号排序
     *  flag == 2  按姓名排序
     *  flag == 3  按宿舍号排序
     */
    for (int i=0; i<stuNum; i++)
    {
        for (int j=1; j<stuNum; j++)
        {
            Swap(stu[j-1], stu[j], flag);
        }
    }
    switch (flag)
    {
        case 1:
            printf("\n已完成按*学号*的排序  可输入 4 进行展示\n");   break;
        case 2:
            printf("\n已完成按*姓名*的排序  可输入 4 进行展示\n");   break;
        case 3:
            printf("\n已完成按*宿舍号*的排序  可输入 4 进行展示\n");   break;
    }

}

void BinarySearch(Stu stu[], int stuNum, char s[], int flag)
{
    /**
     *  功能：接收4个参数  进行二分查找   并输出学生或宿舍信息
     *  stu[]   成员结构体数组  stuNum 学生人数  s[] 需要查找的字符串
     *  flag 接受到的字符串为何种形式
     *  flag == 1   按学生学号查找
     *  flag == 2   按姓名查找
     *  flag = =3   按宿舍号查找
     */
    if (flag == 1)
    {
        int low = 0, high = stuNum-1, mid;
        while (low <= high)
        {
            mid = (low + high) / 2;
            if (strcmp(stu[mid].stuNo, s) > 0)
                high = mid-1;
            else if (strcmp(stu[mid].stuNo, s) < 0)
                low = mid+1;
            else
            {
                OutStuInfo(stu, mid);
                return;
            }
        }
    }
    else if (flag == 2)
    {
        int low = 0, high = stuNum-1, mid;
        while (low <= high)
        {
            mid = (low + high) / 2;
            if (strcmp(stu[mid].stuName, s) > 0)
                high = mid-1;
            else if (strcmp(stu[mid].stuName, s) < 0)
                low = mid+1;
            else
            {
                OutStuInfo(stu, mid);
                return;   //必须得有 标志着二分查找的成功 退出函数
            }
        }
    }
    else
    {
        int low = 0, high = stuNum-1, mid;
        while (low <= high)
        {
            mid = (low + high) / 2;
            if (strcmp(stu[mid].dormNo, s) > 0)
                high = mid-1;
            else if (strcmp(stu[mid].dormNo, s) < 0)
                low = mid+1;
            else
            {
                OutDormInfo(stu, mid);
                return;
            }
        }

    }
    printf("\n查无此人 请检查您的输入是否正确\n");
}

/****************************************************/

int OrdinarySearch(Stu stu[], int &stuNum, char s[])
{
    /**
     *  功能：普通查找
     *  无需排序 直接可以进行姓名或宿舍号查找
     */
    for (int i=0; i<stuNum; i++)
    {
        if (strcmp(s, stu[i].stuNo)==0
                || strcmp(s, stu[i].stuName)==0)
        {
            return i;
        }

    }
    return -1;
}

void DeleteChangeStu(Stu stu[], int &stuNum, int i, int flag)
{
    /**
     *  功能:对学生进行删除和修改
     *  flag == 1   删除
     *  flag == 2   修改
     *  i 要删除或修改的结构体数组下标值
     */

    if (flag == 1)
    {
        for (int j=i; j<stuNum-1; j++)
        {
            stu[j] = stu[j+1];
        }
        stuNum--;
        printf("\n@删除成功@\n");
        return;
    }
    else
    {
        printf("\n学号：");
        scanf("%s", stu[i].stuNo);
        printf("姓名：");
        scanf("%s", stu[i].stuName);
        printf("年龄：");
        scanf("%s", stu[i].stuAge);
        printf("性别: ");
        scanf("%s", stu[i].stuSex);
        printf("籍贯：");
        scanf("%s", stu[i].stuNative);
        printf("宿舍号：");
        scanf("%s", stu[i].dormNo);
        printf("专业：");
        scanf("%s", stu[i].stuMajor);
        getchar();
        printf("\n@已完成修改@\n");
        return;
    }
    printf("\n查无此人 请检查您的输入是否正确\n");
}

/***************************************************/

/***************************************************
            以上操作为系统功能实现区域
                由组长协助组员完成
            以下操作为界面布局和提示
                  由组长完成
*****************************************************/
void Init(Stu stu[], int &stuNum)
{
    printf("\n");
    printf("************************************\n");
    printf("*            提示                  *\n");
    printf("*   *   输入有误重新输入           *\n");
    printf("*   #  退回上一个重新输入 ( > 1 )  *\n");
    printf("************************************\n");
    printf("\n请输入您要录入的学生人数: ");
            scanf("%d", &stuNum);
    printf("\n按照提示输入学生信息\n");
    for (int i=0; i<stuNum; i++)
    {
        printf("\n第 %d 个学生:\n", i+1);
        printf("学号:");
        scanf("%s", stu[i].stuNo);
        if (stu[i].stuNo[0] == '*')
        {
            i--;    continue;
        }
        else if (stu[i].stuNo[0] == '#' && i>0)
        {
            i -= 2;    continue;
        }
        printf("姓名:");
        scanf("%s", stu[i].stuName);
        if (stu[i].stuName[0] == '*')
        {
            i--;    continue;
        }
        else if (stu[i].stuName[0] == '#' && i>0)
        {
            i -= 2;    continue;
        }
        printf("年龄:");
        scanf("%s", stu[i].stuAge);
        if (stu[i].dormNo[0] == '*')
        {
            i--;    continue;
        }
        else if (stu[i].dormNo[0] == '#' && i>0)
        {
            i -= 2;    continue;
        }
        printf("性别：");
        scanf("%s", stu[i].stuSex);
        if (stu[i].dormNo[0] == '*')
        {
            i--;    continue;
        }
        else if (stu[i].dormNo[0] == '#' && i>0)
        {
            i -= 2;    continue;
        }
        printf("籍贯：");
        scanf("%s", stu[i].stuNative);
        if (stu[i].dormNo[0] == '*')
        {
            i--;    continue;
        }
        else if (stu[i].dormNo[0] == '#' && i>0)
        {
            i -= 2;    continue;
        }
        printf("专业：");
        scanf("%s", stu[i].stuMajor);
        if (stu[i].dormNo[0] == '*')
        {
            i--;    continue;
        }
        else if (stu[i].dormNo[0] == '#' && i>0)
        {
            i -= 2;    continue;
        }
        printf("宿舍号:");
        scanf("%s", stu[i].dormNo);
        if (stu[i].dormNo[0] == '*')
        {
            i--;    continue;
        }
        else if (stu[i].dormNo[0] == '#' && i>0)
        {
            i -= 2;    continue;
        }

    }
}

void MainFace()
{
    printf("************************************\n");
    printf("*        宿舍管理查询系统          *\n");
    printf("*   输入相应数字可实现对应功能     *\n");
    printf("*   1     录入学生信息             *\n");
    printf("*   2    对学生信息排序            *\n");
    printf("*   3     查询学生信息             *\n");
    printf("*   4     插入学生信息             *\n");
    printf("*   5  对学生信息模糊查询          *\n");
    printf("*   6  对学生信息删除修改          *\n");
    printf("*   0      退出本系统              *\n");
    printf("************************************\n");
}

void EntryStuInfo(Stu stu[], int &stuNum)
{

    system("cls");
    printf("************************************\n");
    printf("*       录入学生信息平台           *\n");
    printf("*   1      开始录入                *\n");
    printf("*   0     返回主界面               *\n");
    printf("************************************\n");
    char flag[2];
    while (true)
    {
        printf("\n请输入您要进行的操作: ");
        scanf("%s", flag);
        getchar();
        if (flag[0] == '1')
        {
            if (stuNum != 0)
            {
                printf("\n警告！：已存在 %d 个学生  如要重新录入所有学生请输入 1  输入 0 可返回主界面进行插入操作\n", stuNum);
                char temp[2];
                while (true)
                {
                    scanf("%s", temp);
                    getchar();
                    if (temp[0] == '1') break;
                    else if (temp[0] == '0')
                    {
                        system("cls");
                        MainFace();
                        return;
                    }
                    else
                        printf("\n请重新输入 0 或 1 \n");
                }
            }
            Init(stu, stuNum);
            printf("\n录入 %d 个学生 按回车键返回主界面\n", stuNum);
            getchar();
            getchar();
            system("cls");
            MainFace();
            return;
        }
        else if (flag[0] == '0')
        {
            system("cls");
            MainFace();
            return;
        }
        else
            printf("\n输入值超出系统功能范围请重新输入\n");
    }
}

void FunctionSort(Stu stu[], int &stuNum, int &sq)
{
    system("cls");
    if (stuNum == 0)
    {
        printf("\n已存在 %d 个学生 请按回车键返回主界面进行录入学生操作\n", stuNum);
        getchar();
        system("cls");
        MainFace();
        return;
    }
    printf("************************************\n");
    printf("*       学生信息排序平台           *\n");
    printf("*   1    按学号进行排序            *\n");
    printf("*   2    按姓名进行排序            *\n");
    printf("*   3   按宿舍号进行排序           *\n");
    printf("*   4     查看排序结果             *\n");
    printf("*   0      返回主界面              *\n");
    printf("************************************\n");

    char flag[2];
    while (true)
    {
        printf("\n请输入您要进行的操作: ");
        scanf("%s", flag);
        getchar();
        if (flag[0] == '1')
        {
            sq = 1;
            BublleSort(stu, stuNum, 1);
        }
        else if (flag[0] == '2')
        {
            sq = 2;
            BublleSort(stu, stuNum, 2);
        }
        else if (flag[0] == '3')
        {
            sq = 3;
            BublleSort(stu, stuNum, 3);
        }
        else if (flag[0] == '4')
        {
            printf("***********************************************************************\n");
            printf("*  学号        姓名      性别 年龄 籍贯        专业           宿舍号  *\n");
            for (int i=0; i<stuNum; i++)
                OutStuInfo(stu, i);
            printf("***********************************************************************\n");
        }
        else if (flag[0] == '0')
        {
            system("cls");
            MainFace();
            return;
        }
        else
            printf("\n输入值超出系统功能范围请重新输入\n");
    }
}

void FunSearch(Stu stu[], int &stuNum, int &sq)
{
    system("cls");
    if (stuNum == 0)
    {
        printf("\n已存在 %d 个学生 请按回车键返回主界面进行录入学生操作\n", stuNum);
        getchar();
        system("cls");
        MainFace();
        return;
    }
    if (sq == 0)
    {
        printf("\n还未对数据进行排序 请先排序再进行此操作 请按回车键返回主界面进行录入学生操作\n");
        getchar();
        system("cls");
        MainFace();
        return;
    }
    printf("************************************\n");
    printf("*       学生信息查询平台           *\n");
    printf("*   1    按学号进行查询            *\n");
    printf("*   2    按姓名进行查询            *\n");
    printf("*   3   按宿舍号进行查询           *\n");
    printf("*   0      返回主界面              *\n");
    printf("************************************\n");
    if (sq == 1)
    {
        printf("\n只可进行*学号*查询 如需进行其它查询请返回进行相应排序再操作\n");
    }
    else if(sq == 2)
    {
        printf("\n只可进行*姓名*查询 如需进行其它查询请返回进行相应排序再操作\n");
    }
    else
    {
        printf("\n只可进行*宿舍号*查询 如需进行其它查询请返回进行相应排序再操作\n");
    }
    char flag[2];
    while (true)
    {
        printf("\n请输入您要进行的操作: ");
        scanf("%s", flag);
        getchar();
        if (flag[0]-'0' != sq && flag[0] != '0')
        {
            printf("\n请按照要求输入需要实现的功能\n");
            continue;
        }
        if (flag[0] == '1')
        {
            char s[20];
            printf("\n请输入您要查询的学号：");
            scanf("%s", s);
            printf("***********************************************************************\n");
            printf("*  学号        姓名      性别 年龄 籍贯        专业           宿舍号  *\n");
            BinarySearch(stu, stuNum, s, 1);
            printf("***********************************************************************\n");
        }
        else if (flag[0] == '2')
        {
            char s[20];
            printf("\n请输入您要查询的姓名：");
            scanf("%s", s);
            printf("***********************************************************************\n");
            printf("*  学号        姓名      性别 年龄 籍贯        专业           宿舍号  *\n");
            BinarySearch(stu, stuNum, s, 2);
            printf("***********************************************************************\n");
        }
        else if (flag[0] == '3')
        {
            char s[20];
            printf("\n请输入您要查询的宿舍号：");
            scanf("%s", s);
            BinarySearch(stu, stuNum, s, 3);
        }
        else
        {
            system("cls");
            MainFace();
            return;
        }
        getchar();
    }
}

void FunInsert(Stu stu[], int &stuNum, int sq)
{
    system("cls");
    if (stuNum == 0)
    {
        printf("\n已存在 %d 个学生 请按回车键返回主界面进行录入学生操作\n", stuNum);
        getchar();
        system("cls");
        MainFace();
        return;
    }
    if (sq == 0)
    {
        printf("\n还未对数据进行排序 请先排序再进行此操作 请按回车键返回主界面进行录入学生操作\n");
        getchar();
        system("cls");
        MainFace();
        return;
    }
    printf("************************************\n");
    printf("*       学生信息插入平台           *\n");
    printf("*   1    按默认排序插入            *\n");
    printf("*   2     查看信息结果             *\n");
    printf("*   0      返回主界面              *\n");
    printf("************************************\n");
    if (sq == 1)
    {
        printf("\n系统默认进行*学号*顺序插入\n");
    }
    else if(sq == 2)
    {
        printf("\n系统默认进行*姓名*顺序插入\n");
    }
    else
    {
        printf("\n系统默认进行*宿舍号*顺序插入\n");
    }
    char flag[2];
    while (true)
    {
        printf("\n请输入您要进行的操作: ");
        scanf("%s", flag);
        getchar();
        if (flag[0] == '1')
        {
            Stu temp;
            printf("\n学号：");
            scanf("%s", temp.stuNo);
            printf("姓名：");
            scanf("%s", temp.stuName);
            printf("年龄：");
            scanf("%s", temp.stuAge);
            printf("性别: ");
            scanf("%s", temp.stuSex);
            printf("籍贯：");
            scanf("%s", temp.stuNative);
            printf("宿舍号：");
            scanf("%s", temp.dormNo);
            printf("专业：");
            scanf("%s", temp.stuMajor);
            getchar();
            InsertStu(stu, stuNum, temp, sq);
            stuNum++;
            printf("\n插入已完成  输入 2 可展示结果\n");
        }
        else if (flag[0] == '2')
        {
            printf("***********************************************************************\n");
            printf("*  学号        姓名      性别 年龄 籍贯        专业           宿舍号  *\n");
            for (int i=0; i<stuNum; i++)
                OutStuInfo(stu, i);
            printf("***********************************************************************\n");
        }
        else
        {
            system("cls");
            MainFace();
            return;
        }
    }
}

void FunDimSearch(Stu stu[], int &stuNum)
{
    system("cls");
    if (stuNum == 0)
    {
        printf("\n已存在 %d 个学生 请按回车键返回主界面进行录入学生操作\n", stuNum);
        getchar();
        system("cls");
        MainFace();
        return;
    }
    printf("************************************\n");
    printf("*      学生信息模糊查询平台        *\n");
    printf("*   1    按学号进行查询            *\n");
    printf("*   2    按姓名进行查询            *\n");
    printf("*   0      返回主界面              *\n");
    printf("************************************\n");

    char flag[2];
    while (true)
    {
        printf("\n请输入您要进行的操作: ");
        scanf("%s", flag);
        getchar();
        if (flag[0] == '1')
        {
            char s[20];
            printf("\n请输入您要查询的学号：");
            scanf("%s", s);
            printf("***********************************************************************\n");
            printf("*  学号        姓名      性别 年龄 籍贯        专业           宿舍号  *\n");
            DimSearch(stu, stuNum, s, 1);
            printf("***********************************************************************\n");
        }
        else if (flag[0] == '2')
        {
            char s[20];
            printf("\n请输入您要查询的姓名：");
            scanf("%s", s);
            printf("***********************************************************************\n");
            printf("*  学号        姓名      性别 年龄 籍贯        专业           宿舍号  *\n");
            DimSearch(stu, stuNum, s, 2);
            printf("***********************************************************************\n");
        }
        else if (flag[0] == '0')
        {
            system("cls");
            MainFace();
            return;
        }
        else
        {
            printf("\n输入值超出系统功能范围请重新操作\n");
        }
    }
}

void FunDeleteChange(Stu stu[], int &stuNum, int &sq)
{
    system("cls");
    if (stuNum == 0)
    {
        printf("\n已存在 %d 个学生 请按回车键返回主界面进行录入学生操作\n", stuNum);
        getchar();
        system("cls");
        MainFace();
        return;
    }
    printf("************************************\n");
    printf("*         学生信息删除修改平台     *\n");
    printf("*   1  按学号或姓名进行查询并删除  *\n");
    printf("*   2  按学号或姓名进行查询并修改  *\n");
    printf("*   3       查看信息结果           *\n");
    printf("*   0        返回主界面            *\n");
    printf("************************************\n");

    char flag[2];
    while (true)
    {
        printf("\n请输入您要进行的操作: ");
        scanf("%s", flag);
        getchar();
        if (flag[0] == '1')
        {
            char s[20];
            printf("\n请输入您要删除的学号或姓名：");
            scanf("%s", s);
            getchar();
            int temp = OrdinarySearch(stu, stuNum, s);
            if (temp == -1)
            {
                printf("\n！！！！查无此人\n");
            }
            else
            {
                printf("***********************************************************************\n");
                printf("*  学号        姓名      性别 年龄 籍贯        专业        宿舍号     *\n");
                OutStuInfo(stu, temp);
                printf("***********************************************************************\n");
                printf("\n确认删除此人? Y/N: ");
                char tyn;
                while (true)
                {
                    tyn = getchar();
                    getchar();
                    if (tyn == 'Y' || tyn == 'y')
                    {
                        DeleteChangeStu(stu, stuNum, temp, 1);
                        break;
                    }
                    else if (tyn == 'N' || tyn == 'n')
                    {
                        break;
                    }
                    else
                    {
                        printf("\n输入有误请按照提示重新输入\n");
                    }
                }
            }
        }
        else if (flag[0] == '2')
        {
            sq = 0;
            char s[20];
            printf("\n请输入您要修改的学号或姓名：");
            scanf("%s", s);
            getchar();
            int temp = OrdinarySearch(stu, stuNum, s);
            if (temp == -1)
            {
                printf("\n！！！！查无此人\n");
            }
            else
            {
                printf("***********************************************************************\n");
                printf("*  学号        姓名      性别 年龄 籍贯        专业           宿舍号  *\n");
                OutStuInfo(stu, temp);
                printf("***********************************************************************\n");
                printf("\n确认修改此人? Y/N: ");
                char tyn;
                while (true)
                {
                    tyn = getchar();
                    getchar();
                    if (tyn == 'Y' || tyn == 'y')
                    {
                        DeleteChangeStu(stu, stuNum, temp, 2);
                        break;
                    }
                    else if (tyn == 'N' || tyn == 'n')
                    {
                        break;
                    }
                    else
                    {
                        printf("\n输入有误请按照提示重新输入\n");
                    }
                }
            }
        }
        else if (flag[0] == '3')
        {
            printf("***********************************************************************\n");
            printf("*  学号        姓名      性别 年龄 籍贯        专业           宿舍号  *\n");
            for (int i=0; i<stuNum; i++)
                OutStuInfo(stu, i);
            printf("***********************************************************************\n");
        }
        else if (flag[0] == '0')
        {
            system("cls");
            MainFace();
            return;
        }
        else
        {
            printf("\n输入值超出系统功能范围请重新输入\n");
        }
    }
}

void Read(Stu stu[], int &stuNum, int &sq)
{
    FILE *fp;

    if ((fp = fopen(routeStuNum, "rb")) == NULL) {
        printf("\n不能打开文件 请检查路径是否正确\n");
        return;
    }
    if (fread(&stuNum, sizeof (int), 1, fp) != 1) {
        printf("\n无学生信息\n");
        return;
    }

    if ((fp = fopen(routeSq, "rb")) == NULL) {
        printf("\n不能打开文件 请检查路径是否正确\n");
        return;
    }

    if (fread(&sq, sizeof (int), 1, fp) != 1) {
        printf("\n无学生信息\n");
        return;
    }

    if ((fp = fopen(routeStu, "rb")) == NULL) {
        printf("\n不能打开文件 请检查路径是否正确\n");
        return;
    }

    for (int i=0; i<stuNum; i++) {
        if (fread(&stu[i], sizeof (Stu), 1, fp) != 1) {
            printf("\n读取学生信息错误\n");
            return;
        }
    }

    printf("\n已读取到 %d 个学生信息\n", stuNum);
    fclose(fp);
}

void Save(Stu stu[], int &stuNum, int &sq)
{
    FILE *fp;

    if ((fp = fopen(routeStuNum, "wb")) == NULL) {
        printf("\n无法保存信息 请检查保存文件路径是否正确\n");
        return;
    }
    if (fwrite(&stuNum, sizeof (int), 1, fp) != 1) {
        printf("\n保存信息错误\n");
        return;
    }

    if ((fp = fopen(routeSq, "wb")) == NULL) {
        printf("\n不能打开文件 请检查路径是否正确\n");
        return;
    }
    if (fwrite(&sq, sizeof (int), 1, fp) != 1) {
        printf("\n无学生信息\n");
        return;
    }
    if ((fp = fopen(routeStu, "wb")) == NULL) {
        printf("\n无法保存信息 请检查保存文件路径是否正确\n");
        return;
    }

    for (int i=0; i<stuNum; i++) {
        if (fwrite(&stu[i], sizeof (Stu), 1, fp) != 1) {
            printf("\n保存信息错误\n");
            return;
        }
    }
    printf("\n已保存 %d 个学生信息\n", stuNum);
    fclose(fp);
}

int main()
{
    MainFace();
    Stu stu[10000];
    char flag[2];
    int stuNum = 0;
    int sq = 0;           //标记排序格式  1为学号 2为姓名  3为宿舍号
    Read(stu, stuNum, sq);
    while (true)
    {
        printf("\n请输入您要进行的操作: ");
        scanf("%s", flag);
        getchar();
        if (flag[0] == '0')  break;
        switch (flag[0]) {
            case '1':
                EntryStuInfo(stu, stuNum);   break;
            case '2':
                FunctionSort(stu, stuNum, sq);   break;
            case '3':
                FunSearch(stu, stuNum, sq);   break;
            case '4':
                FunInsert(stu, stuNum, sq);   break;
            case '5':
                FunDimSearch(stu, stuNum);  break;
            case '6':
                FunDeleteChange(stu, stuNum, sq);   break;
            default:
                printf("\n输入值超出系统功能范围请重新输入\n");
        }
    }
    Save(stu, stuNum, sq);
    system("pause");
    return 0;
}
