//ͨ�ú���ģ��
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#include <conio.h>
#include <string.h>

//������뻺����
#define CLEARSTDIN while(getchar() != '\n')
//����������ɫ��ָ������
#define setColor(num) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), num);
//��������ʾ��Ϣ
#define inputTip(num, total) printf("%66s\r", "����"#num"���"#total"�")

/*
//����������
#define CMDWIDTH 102
//��������߶�
#define CMDHEIGHT 32
*/

void displayProgress(float preTag, float curTag, int len) {    //��������������preTag��ʼ����curTag����������Ϊlen
    int i, k;
    if (len > 100) len = 100;   //�����Ϊ100
    if (preTag < 0) preTag = 0; //������С��0
    if (curTag > len) curTag = len;  //����������100%
    char *bar = (char *) malloc(sizeof(char) * (len + 1));
    for (i = 0; i < len + 1; i++) bar[i] = '\040';  //��ʼ���ǻ��Ԫ
    bar[len] = '\0';
    if (curTag == 0) { //���������0%
        bar[len / 2 + 1] = '%';
        bar[len / 2] = 0 + 48;
        printf("[%s]\r", bar);
        fflush(stdout);
    }
    else if (preTag == len) {   //���������ǰ���ȱ�ʶΪ100%
        for (i = 0; i < preTag; i++) bar[i] = '=';
        bar[len / 2 + 1] = '%';
        bar[len / 2] = 48;
        bar[len / 2 - 1] = 48;
        bar[len / 2 - 2] = 49;
        printf("[%s]\r", bar);
    }
    else {
        for (i = 0; i < preTag; i++) bar[i] = '=';
        printf("[%s]\r", bar);
        for (i = preTag; i < curTag; i++) {
            k = (float) (i + 1) / len * 100;
            bar[i] = '=';
            bar[len / 2 + 1] = '%';     //��ʾ�ٷֱ�
            bar[len / 2] = k % 10 + 48;
            if (k / 10 != 0) bar[len / 2 - 1] = k / 10 + 48;
            if (k / 100 == 1) {
                bar[len / 2 - 2] = 49;
                bar[len / 2 - 1] = 48;
            }
            printf("[%s]\r", bar);
            fflush(stdout);
            Sleep((srand((unsigned) i), rand() % (101 - len) + rand() % 25));   //ģ�����붯�����ӳ٣�
        }
    }
}

void displayBlock(int width, char *strPrint) {  //������ʾstrPrint�ַ���
    int i, len;
    char *strFormat;
    len = (width - strlen(strPrint)) / 2;
    strFormat = (char*) malloc(sizeof(char) * (len + 1));
    for (i = 0; i < len; i++) strFormat[i] = '\040';
    strFormat[len] = '\0';
    printf("%s%s\n", strFormat, strPrint);
    free(strFormat);    //�ͷ��ַ����ڴ�
}

int checkDate(int year, int month, int day) {   //�ж�����������Ƿ�����·ݲ�������-1�����ڲ�������-2��������0
    int leapTag = 0;
    //�ж����꣬ƽ��Ϊ0������Ϊ1
    if (year % 100 == 0) {
        if (year % 4 == 0) leapTag = 1;
    }
    else if (year % 4 == 0) leapTag = 1;
    //�ж��·�
    if (month > 12 || month < 1) return -1;
    //�ж�����
    if (day < 1) return -2;
    else
        switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            if (day > 31) return -2;
            break;
        case 4: case 6: case 9: case 11:
            if (day > 30) return -2;
            break;
        case 2:
            if (leapTag == 1) {
                if (day > 29) return -2;
            }
            else
                if (day > 28) return -2;
            break;
        }
    return 0;
}

/*
void windowSet(int width, int height) { //���ô�����Ϣ
    HANDLE hanOut = GetStdHandle(STD_OUTPUT_HANDLE);   //��ʼ��������
    COORD size = { width, height }; //���ô��ڴ�С
    SMALL_RECT rc = { 0, 0, width - 1, height - 1 };    //����������ڴ�С
    CONSOLE_CURSOR_INFO cursor = { 1, FALSE };  //���ù���ʽ���ߴ磬��ʾ���

    SetConsoleWindowInfo(hanOut, TRUE, &rc);
    SetConsoleScreenBufferSize(hanOut, size);
    SetConsoleCursorInfo(hanOut, &cursor);

    //CloseHandle(hanOut);  //�ر�������
}
*/

void setCursor(int size, BOOL visible) {    //���ù���С���ɼ���
    CONSOLE_CURSOR_INFO cursor = { size, visible };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

void setWindow(int width, int height) { //���ô��ڿ��
    char *strCmd = (char *) malloc(sizeof("mode con: cols=**** lines=****"));
    sprintf(strCmd, "mode con: cols=%d lines=%d", width, height);
    system(strCmd);
    system("cls");
    free(strCmd);   //�ͷ��ڴ�
}

