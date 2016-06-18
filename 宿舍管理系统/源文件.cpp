#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stu {
    char stuNo[20];
    char stuName[20];
    char dormNo[10];  //�����
    char stuAge[3];
    char stuSex[3];
    char stuNative[20];
    char stuMajor[20];//רҵ
}Stu;
/*********************************************
 *    ������������ļ���Ŀ¼
 *
 */

char routeStu[] = "E:\\�γ����\\Data\\stuData";
char routeStuNum[] = "E:\\�γ����\\Data\\stuNum";
char routeSq[] = "E:\\�γ����\\Data\\sq";     //�����Ϣ
/********************************************/
void Swap(Stu &a, Stu &b, int flag)
{
    /**
     *  �˺���ʵ�������ṹ����н���  ��������Ͳ��������
     *  flag ������ֵ 1  2  3
     *  flag == 1 ʱ����ѧ�űȽϲ�����
     *  flag == 2 ʱ���������Ƚϲ�����
     *  flag == 3 ʱ��������űȽϲ�����
     */
    Stu temp;       //�ṹ�彻����ʱ����
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
     *  ���ܣ�����Ҫ����ѧ����Ϣ ����ָ��˳�����
     *  st[] ��Ա�ṹ������
     *  stuNum  ѧ������
     *  stuTemp Ҫ����ѧ���ṹ��
     *  flag ������˳�����
     *  flag == 1 ѧ��
     *  flag == 2 ����
     *  flag == 3 �����
     *  ˵�����˺���������� Swap(Stu &a, Stu &b, int flag)   ����
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
     *  ���ܣ����ѧ����Ϣ �����м��Ű�
     *  stu[]   �ṹ������
     *  m   Ҫ���ѧ���ṹ���±�
     */
    //printf("***********************************************************************\n");
    //printf("*  ѧ��        ����      �Ա� ���� ����        רҵ           �����  *\n");
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
     *  ��������Ա��Ϣ ����һ��Ա stu[m]
     *  ��ѧ��˳��������������г�Ա��Ϣ
     *  �����м��Ű�
     */
    int min = m, max = m;
    while (strcmp(stu[min-1].dormNo, stu[min].dormNo) == 0)
        min--;
    while (strcmp(stu[max+1].dormNo, stu[max].dormNo) == 0)
        max++;
    printf("\n����������Ϊ %d\n", max-min+1);
    printf("***********************************************************************\n");
    printf("*  ѧ��        ����      �Ա� ���� ����        רҵ           �����  *\n");
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
     *  ����ʵ��ģ��ƥ���ж�
     *  ����str2 ƥ�� str1
     *  �涨�� str2 ���ȴ��ڵ��� str1
     *         str2 ˳����� str1���ַ�
     *         ��Ϊƥ��ɹ�
     *  �磺str1 = "abcde"   str2 == "ace" / "abd" �Ⱦ�Ϊ�ɹ�
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
     *  ���ܣ�ģ������
     *  ����һ���ַ�������ָ����flag ����ģ������
     *  flag ȡ 1 2
     *  flag == 1   ѧ��
     *  flag == 2   ����
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
        printf("\n!!! û��ƥ����\n");
}

/*****************************************************/
void BublleSort(Stu stu[], int stuNum, int flag)
{
    /**
     *  ���ܣ�Ϊð�������� ���ڽṹ������
     *  ������������
     *  stu[] �ṹ������ stuNumѧ������  flag �����ַ�ʽ����
     *  flag == 1  ��ѧ������
     *  flag == 2  ����������
     *  flag == 3  �����������
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
            printf("\n����ɰ�*ѧ��*������  ������ 4 ����չʾ\n");   break;
        case 2:
            printf("\n����ɰ�*����*������  ������ 4 ����չʾ\n");   break;
        case 3:
            printf("\n����ɰ�*�����*������  ������ 4 ����չʾ\n");   break;
    }

}

void BinarySearch(Stu stu[], int stuNum, char s[], int flag)
{
    /**
     *  ���ܣ�����4������  ���ж��ֲ���   �����ѧ����������Ϣ
     *  stu[]   ��Ա�ṹ������  stuNum ѧ������  s[] ��Ҫ���ҵ��ַ���
     *  flag ���ܵ����ַ���Ϊ������ʽ
     *  flag == 1   ��ѧ��ѧ�Ų���
     *  flag == 2   ����������
     *  flag = =3   ������Ų���
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
                return;   //������� ��־�Ŷ��ֲ��ҵĳɹ� �˳�����
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
    printf("\n���޴��� �������������Ƿ���ȷ\n");
}

/****************************************************/

int OrdinarySearch(Stu stu[], int &stuNum, char s[])
{
    /**
     *  ���ܣ���ͨ����
     *  �������� ֱ�ӿ��Խ�������������Ų���
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
     *  ����:��ѧ������ɾ�����޸�
     *  flag == 1   ɾ��
     *  flag == 2   �޸�
     *  i Ҫɾ�����޸ĵĽṹ�������±�ֵ
     */

    if (flag == 1)
    {
        for (int j=i; j<stuNum-1; j++)
        {
            stu[j] = stu[j+1];
        }
        stuNum--;
        printf("\n@ɾ���ɹ�@\n");
        return;
    }
    else
    {
        printf("\nѧ�ţ�");
        scanf("%s", stu[i].stuNo);
        printf("������");
        scanf("%s", stu[i].stuName);
        printf("���䣺");
        scanf("%s", stu[i].stuAge);
        printf("�Ա�: ");
        scanf("%s", stu[i].stuSex);
        printf("���᣺");
        scanf("%s", stu[i].stuNative);
        printf("����ţ�");
        scanf("%s", stu[i].dormNo);
        printf("רҵ��");
        scanf("%s", stu[i].stuMajor);
        getchar();
        printf("\n@������޸�@\n");
        return;
    }
    printf("\n���޴��� �������������Ƿ���ȷ\n");
}

/***************************************************/

/***************************************************
            ���ϲ���Ϊϵͳ����ʵ������
                ���鳤Э����Ա���
            ���²���Ϊ���沼�ֺ���ʾ
                  ���鳤���
*****************************************************/
void Init(Stu stu[], int &stuNum)
{
    printf("\n");
    printf("************************************\n");
    printf("*            ��ʾ                  *\n");
    printf("*   *   ����������������           *\n");
    printf("*   #  �˻���һ���������� ( > 1 )  *\n");
    printf("************************************\n");
    printf("\n��������Ҫ¼���ѧ������: ");
            scanf("%d", &stuNum);
    printf("\n������ʾ����ѧ����Ϣ\n");
    for (int i=0; i<stuNum; i++)
    {
        printf("\n�� %d ��ѧ��:\n", i+1);
        printf("ѧ��:");
        scanf("%s", stu[i].stuNo);
        if (stu[i].stuNo[0] == '*')
        {
            i--;    continue;
        }
        else if (stu[i].stuNo[0] == '#' && i>0)
        {
            i -= 2;    continue;
        }
        printf("����:");
        scanf("%s", stu[i].stuName);
        if (stu[i].stuName[0] == '*')
        {
            i--;    continue;
        }
        else if (stu[i].stuName[0] == '#' && i>0)
        {
            i -= 2;    continue;
        }
        printf("����:");
        scanf("%s", stu[i].stuAge);
        if (stu[i].dormNo[0] == '*')
        {
            i--;    continue;
        }
        else if (stu[i].dormNo[0] == '#' && i>0)
        {
            i -= 2;    continue;
        }
        printf("�Ա�");
        scanf("%s", stu[i].stuSex);
        if (stu[i].dormNo[0] == '*')
        {
            i--;    continue;
        }
        else if (stu[i].dormNo[0] == '#' && i>0)
        {
            i -= 2;    continue;
        }
        printf("���᣺");
        scanf("%s", stu[i].stuNative);
        if (stu[i].dormNo[0] == '*')
        {
            i--;    continue;
        }
        else if (stu[i].dormNo[0] == '#' && i>0)
        {
            i -= 2;    continue;
        }
        printf("רҵ��");
        scanf("%s", stu[i].stuMajor);
        if (stu[i].dormNo[0] == '*')
        {
            i--;    continue;
        }
        else if (stu[i].dormNo[0] == '#' && i>0)
        {
            i -= 2;    continue;
        }
        printf("�����:");
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
    printf("*        ��������ѯϵͳ          *\n");
    printf("*   ������Ӧ���ֿ�ʵ�ֶ�Ӧ����     *\n");
    printf("*   1     ¼��ѧ����Ϣ             *\n");
    printf("*   2    ��ѧ����Ϣ����            *\n");
    printf("*   3     ��ѯѧ����Ϣ             *\n");
    printf("*   4     ����ѧ����Ϣ             *\n");
    printf("*   5  ��ѧ����Ϣģ����ѯ          *\n");
    printf("*   6  ��ѧ����Ϣɾ���޸�          *\n");
    printf("*   0      �˳���ϵͳ              *\n");
    printf("************************************\n");
}

void EntryStuInfo(Stu stu[], int &stuNum)
{

    system("cls");
    printf("************************************\n");
    printf("*       ¼��ѧ����Ϣƽ̨           *\n");
    printf("*   1      ��ʼ¼��                *\n");
    printf("*   0     ����������               *\n");
    printf("************************************\n");
    char flag[2];
    while (true)
    {
        printf("\n��������Ҫ���еĲ���: ");
        scanf("%s", flag);
        getchar();
        if (flag[0] == '1')
        {
            if (stuNum != 0)
            {
                printf("\n���棡���Ѵ��� %d ��ѧ��  ��Ҫ����¼������ѧ�������� 1  ���� 0 �ɷ�����������в������\n", stuNum);
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
                        printf("\n���������� 0 �� 1 \n");
                }
            }
            Init(stu, stuNum);
            printf("\n¼�� %d ��ѧ�� ���س�������������\n", stuNum);
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
            printf("\n����ֵ����ϵͳ���ܷ�Χ����������\n");
    }
}

void FunctionSort(Stu stu[], int &stuNum, int &sq)
{
    system("cls");
    if (stuNum == 0)
    {
        printf("\n�Ѵ��� %d ��ѧ�� �밴�س����������������¼��ѧ������\n", stuNum);
        getchar();
        system("cls");
        MainFace();
        return;
    }
    printf("************************************\n");
    printf("*       ѧ����Ϣ����ƽ̨           *\n");
    printf("*   1    ��ѧ�Ž�������            *\n");
    printf("*   2    ��������������            *\n");
    printf("*   3   ������Ž�������           *\n");
    printf("*   4     �鿴������             *\n");
    printf("*   0      ����������              *\n");
    printf("************************************\n");

    char flag[2];
    while (true)
    {
        printf("\n��������Ҫ���еĲ���: ");
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
            printf("*  ѧ��        ����      �Ա� ���� ����        רҵ           �����  *\n");
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
            printf("\n����ֵ����ϵͳ���ܷ�Χ����������\n");
    }
}

void FunSearch(Stu stu[], int &stuNum, int &sq)
{
    system("cls");
    if (stuNum == 0)
    {
        printf("\n�Ѵ��� %d ��ѧ�� �밴�س����������������¼��ѧ������\n", stuNum);
        getchar();
        system("cls");
        MainFace();
        return;
    }
    if (sq == 0)
    {
        printf("\n��δ�����ݽ������� ���������ٽ��д˲��� �밴�س����������������¼��ѧ������\n");
        getchar();
        system("cls");
        MainFace();
        return;
    }
    printf("************************************\n");
    printf("*       ѧ����Ϣ��ѯƽ̨           *\n");
    printf("*   1    ��ѧ�Ž��в�ѯ            *\n");
    printf("*   2    ���������в�ѯ            *\n");
    printf("*   3   ������Ž��в�ѯ           *\n");
    printf("*   0      ����������              *\n");
    printf("************************************\n");
    if (sq == 1)
    {
        printf("\nֻ�ɽ���*ѧ��*��ѯ �������������ѯ�뷵�ؽ�����Ӧ�����ٲ���\n");
    }
    else if(sq == 2)
    {
        printf("\nֻ�ɽ���*����*��ѯ �������������ѯ�뷵�ؽ�����Ӧ�����ٲ���\n");
    }
    else
    {
        printf("\nֻ�ɽ���*�����*��ѯ �������������ѯ�뷵�ؽ�����Ӧ�����ٲ���\n");
    }
    char flag[2];
    while (true)
    {
        printf("\n��������Ҫ���еĲ���: ");
        scanf("%s", flag);
        getchar();
        if (flag[0]-'0' != sq && flag[0] != '0')
        {
            printf("\n�밴��Ҫ��������Ҫʵ�ֵĹ���\n");
            continue;
        }
        if (flag[0] == '1')
        {
            char s[20];
            printf("\n��������Ҫ��ѯ��ѧ�ţ�");
            scanf("%s", s);
            printf("***********************************************************************\n");
            printf("*  ѧ��        ����      �Ա� ���� ����        רҵ           �����  *\n");
            BinarySearch(stu, stuNum, s, 1);
            printf("***********************************************************************\n");
        }
        else if (flag[0] == '2')
        {
            char s[20];
            printf("\n��������Ҫ��ѯ��������");
            scanf("%s", s);
            printf("***********************************************************************\n");
            printf("*  ѧ��        ����      �Ա� ���� ����        רҵ           �����  *\n");
            BinarySearch(stu, stuNum, s, 2);
            printf("***********************************************************************\n");
        }
        else if (flag[0] == '3')
        {
            char s[20];
            printf("\n��������Ҫ��ѯ������ţ�");
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
        printf("\n�Ѵ��� %d ��ѧ�� �밴�س����������������¼��ѧ������\n", stuNum);
        getchar();
        system("cls");
        MainFace();
        return;
    }
    if (sq == 0)
    {
        printf("\n��δ�����ݽ������� ���������ٽ��д˲��� �밴�س����������������¼��ѧ������\n");
        getchar();
        system("cls");
        MainFace();
        return;
    }
    printf("************************************\n");
    printf("*       ѧ����Ϣ����ƽ̨           *\n");
    printf("*   1    ��Ĭ���������            *\n");
    printf("*   2     �鿴��Ϣ���             *\n");
    printf("*   0      ����������              *\n");
    printf("************************************\n");
    if (sq == 1)
    {
        printf("\nϵͳĬ�Ͻ���*ѧ��*˳�����\n");
    }
    else if(sq == 2)
    {
        printf("\nϵͳĬ�Ͻ���*����*˳�����\n");
    }
    else
    {
        printf("\nϵͳĬ�Ͻ���*�����*˳�����\n");
    }
    char flag[2];
    while (true)
    {
        printf("\n��������Ҫ���еĲ���: ");
        scanf("%s", flag);
        getchar();
        if (flag[0] == '1')
        {
            Stu temp;
            printf("\nѧ�ţ�");
            scanf("%s", temp.stuNo);
            printf("������");
            scanf("%s", temp.stuName);
            printf("���䣺");
            scanf("%s", temp.stuAge);
            printf("�Ա�: ");
            scanf("%s", temp.stuSex);
            printf("���᣺");
            scanf("%s", temp.stuNative);
            printf("����ţ�");
            scanf("%s", temp.dormNo);
            printf("רҵ��");
            scanf("%s", temp.stuMajor);
            getchar();
            InsertStu(stu, stuNum, temp, sq);
            stuNum++;
            printf("\n���������  ���� 2 ��չʾ���\n");
        }
        else if (flag[0] == '2')
        {
            printf("***********************************************************************\n");
            printf("*  ѧ��        ����      �Ա� ���� ����        רҵ           �����  *\n");
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
        printf("\n�Ѵ��� %d ��ѧ�� �밴�س����������������¼��ѧ������\n", stuNum);
        getchar();
        system("cls");
        MainFace();
        return;
    }
    printf("************************************\n");
    printf("*      ѧ����Ϣģ����ѯƽ̨        *\n");
    printf("*   1    ��ѧ�Ž��в�ѯ            *\n");
    printf("*   2    ���������в�ѯ            *\n");
    printf("*   0      ����������              *\n");
    printf("************************************\n");

    char flag[2];
    while (true)
    {
        printf("\n��������Ҫ���еĲ���: ");
        scanf("%s", flag);
        getchar();
        if (flag[0] == '1')
        {
            char s[20];
            printf("\n��������Ҫ��ѯ��ѧ�ţ�");
            scanf("%s", s);
            printf("***********************************************************************\n");
            printf("*  ѧ��        ����      �Ա� ���� ����        רҵ           �����  *\n");
            DimSearch(stu, stuNum, s, 1);
            printf("***********************************************************************\n");
        }
        else if (flag[0] == '2')
        {
            char s[20];
            printf("\n��������Ҫ��ѯ��������");
            scanf("%s", s);
            printf("***********************************************************************\n");
            printf("*  ѧ��        ����      �Ա� ���� ����        רҵ           �����  *\n");
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
            printf("\n����ֵ����ϵͳ���ܷ�Χ�����²���\n");
        }
    }
}

void FunDeleteChange(Stu stu[], int &stuNum, int &sq)
{
    system("cls");
    if (stuNum == 0)
    {
        printf("\n�Ѵ��� %d ��ѧ�� �밴�س����������������¼��ѧ������\n", stuNum);
        getchar();
        system("cls");
        MainFace();
        return;
    }
    printf("************************************\n");
    printf("*         ѧ����Ϣɾ���޸�ƽ̨     *\n");
    printf("*   1  ��ѧ�Ż��������в�ѯ��ɾ��  *\n");
    printf("*   2  ��ѧ�Ż��������в�ѯ���޸�  *\n");
    printf("*   3       �鿴��Ϣ���           *\n");
    printf("*   0        ����������            *\n");
    printf("************************************\n");

    char flag[2];
    while (true)
    {
        printf("\n��������Ҫ���еĲ���: ");
        scanf("%s", flag);
        getchar();
        if (flag[0] == '1')
        {
            char s[20];
            printf("\n��������Ҫɾ����ѧ�Ż�������");
            scanf("%s", s);
            getchar();
            int temp = OrdinarySearch(stu, stuNum, s);
            if (temp == -1)
            {
                printf("\n�����������޴���\n");
            }
            else
            {
                printf("***********************************************************************\n");
                printf("*  ѧ��        ����      �Ա� ���� ����        רҵ        �����     *\n");
                OutStuInfo(stu, temp);
                printf("***********************************************************************\n");
                printf("\nȷ��ɾ������? Y/N: ");
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
                        printf("\n���������밴����ʾ��������\n");
                    }
                }
            }
        }
        else if (flag[0] == '2')
        {
            sq = 0;
            char s[20];
            printf("\n��������Ҫ�޸ĵ�ѧ�Ż�������");
            scanf("%s", s);
            getchar();
            int temp = OrdinarySearch(stu, stuNum, s);
            if (temp == -1)
            {
                printf("\n�����������޴���\n");
            }
            else
            {
                printf("***********************************************************************\n");
                printf("*  ѧ��        ����      �Ա� ���� ����        רҵ           �����  *\n");
                OutStuInfo(stu, temp);
                printf("***********************************************************************\n");
                printf("\nȷ���޸Ĵ���? Y/N: ");
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
                        printf("\n���������밴����ʾ��������\n");
                    }
                }
            }
        }
        else if (flag[0] == '3')
        {
            printf("***********************************************************************\n");
            printf("*  ѧ��        ����      �Ա� ���� ����        רҵ           �����  *\n");
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
            printf("\n����ֵ����ϵͳ���ܷ�Χ����������\n");
        }
    }
}

void Read(Stu stu[], int &stuNum, int &sq)
{
    FILE *fp;

    if ((fp = fopen(routeStuNum, "rb")) == NULL) {
        printf("\n���ܴ��ļ� ����·���Ƿ���ȷ\n");
        return;
    }
    if (fread(&stuNum, sizeof (int), 1, fp) != 1) {
        printf("\n��ѧ����Ϣ\n");
        return;
    }

    if ((fp = fopen(routeSq, "rb")) == NULL) {
        printf("\n���ܴ��ļ� ����·���Ƿ���ȷ\n");
        return;
    }

    if (fread(&sq, sizeof (int), 1, fp) != 1) {
        printf("\n��ѧ����Ϣ\n");
        return;
    }

    if ((fp = fopen(routeStu, "rb")) == NULL) {
        printf("\n���ܴ��ļ� ����·���Ƿ���ȷ\n");
        return;
    }

    for (int i=0; i<stuNum; i++) {
        if (fread(&stu[i], sizeof (Stu), 1, fp) != 1) {
            printf("\n��ȡѧ����Ϣ����\n");
            return;
        }
    }

    printf("\n�Ѷ�ȡ�� %d ��ѧ����Ϣ\n", stuNum);
    fclose(fp);
}

void Save(Stu stu[], int &stuNum, int &sq)
{
    FILE *fp;

    if ((fp = fopen(routeStuNum, "wb")) == NULL) {
        printf("\n�޷�������Ϣ ���鱣���ļ�·���Ƿ���ȷ\n");
        return;
    }
    if (fwrite(&stuNum, sizeof (int), 1, fp) != 1) {
        printf("\n������Ϣ����\n");
        return;
    }

    if ((fp = fopen(routeSq, "wb")) == NULL) {
        printf("\n���ܴ��ļ� ����·���Ƿ���ȷ\n");
        return;
    }
    if (fwrite(&sq, sizeof (int), 1, fp) != 1) {
        printf("\n��ѧ����Ϣ\n");
        return;
    }
    if ((fp = fopen(routeStu, "wb")) == NULL) {
        printf("\n�޷�������Ϣ ���鱣���ļ�·���Ƿ���ȷ\n");
        return;
    }

    for (int i=0; i<stuNum; i++) {
        if (fwrite(&stu[i], sizeof (Stu), 1, fp) != 1) {
            printf("\n������Ϣ����\n");
            return;
        }
    }
    printf("\n�ѱ��� %d ��ѧ����Ϣ\n", stuNum);
    fclose(fp);
}

int main()
{
    MainFace();
    Stu stu[10000];
    char flag[2];
    int stuNum = 0;
    int sq = 0;           //��������ʽ  1Ϊѧ�� 2Ϊ����  3Ϊ�����
    Read(stu, stuNum, sq);
    while (true)
    {
        printf("\n��������Ҫ���еĲ���: ");
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
                printf("\n����ֵ����ϵͳ���ܷ�Χ����������\n");
        }
    }
    Save(stu, stuNum, sq);
    system("pause");
    return 0;
}
