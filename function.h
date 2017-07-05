//通用函数模块
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#include <conio.h>
#include <string.h>

//清空输入缓冲区
#define CLEARSTDIN while(getchar() != '\n')
//设置字体颜色（指定区域）
#define setColor(num) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), num);
//输入项提示信息
#define inputTip(num, total) printf("%66s\r", "（第"#num"项，共"#total"项）")

/*
//输出环境宽度
#define CMDWIDTH 102
//输出环境高度
#define CMDHEIGHT 32
*/

void displayProgress(float preTag, float curTag, int len) {    //进度条函数，从preTag开始，到curTag结束，长度为len
    int i, k;
    if (len > 100) len = 100;   //最大宽度为100
    if (preTag < 0) preTag = 0; //进度条小于0
    if (curTag > len) curTag = len;  //进度条超过100%
    char *bar = (char *) malloc(sizeof(char) * (len + 1));
    for (i = 0; i < len + 1; i++) bar[i] = '\040';  //初始化非活动单元
    bar[len] = '\0';
    if (curTag == 0) { //特殊情况，0%
        bar[len / 2 + 1] = '%';
        bar[len / 2] = 0 + 48;
        printf("[%s]\r", bar);
        fflush(stdout);
    }
    else if (preTag == len) {   //特殊情况，前进度标识为100%
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
            bar[len / 2 + 1] = '%';     //显示百分比
            bar[len / 2] = k % 10 + 48;
            if (k / 10 != 0) bar[len / 2 - 1] = k / 10 + 48;
            if (k / 100 == 1) {
                bar[len / 2 - 2] = 49;
                bar[len / 2 - 1] = 48;
            }
            printf("[%s]\r", bar);
            fflush(stdout);
            Sleep((srand((unsigned) i), rand() % (101 - len) + rand() % 25));   //模拟载入动画（延迟）
        }
    }
}

void displayBlock(int width, char *strPrint) {  //居中显示strPrint字符串
    int i, len;
    char *strFormat;
    len = (width - strlen(strPrint)) / 2;
    strFormat = (char*) malloc(sizeof(char) * (len + 1));
    for (i = 0; i < len; i++) strFormat[i] = '\040';
    strFormat[len] = '\0';
    printf("%s%s\n", strFormat, strPrint);
    free(strFormat);    //释放字符串内存
}

int checkDate(int year, int month, int day) {   //判断输入的日期是否合理，月份不合理返回-1，日期不合理返回-2，合理返回0
    int leapTag = 0;
    //判断闰年，平年为0，闰年为1
    if (year % 100 == 0) {
        if (year % 4 == 0) leapTag = 1;
    }
    else if (year % 4 == 0) leapTag = 1;
    //判断月份
    if (month > 12 || month < 1) return -1;
    //判断日期
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
void windowSet(int width, int height) { //设置窗口信息
    HANDLE hanOut = GetStdHandle(STD_OUTPUT_HANDLE);   //初始化输出句柄
    COORD size = { width, height }; //设置窗口大小
    SMALL_RECT rc = { 0, 0, width - 1, height - 1 };    //设置输出窗口大小
    CONSOLE_CURSOR_INFO cursor = { 1, FALSE };  //设置光标格式（尺寸，显示与否）

    SetConsoleWindowInfo(hanOut, TRUE, &rc);
    SetConsoleScreenBufferSize(hanOut, size);
    SetConsoleCursorInfo(hanOut, &cursor);

    //CloseHandle(hanOut);  //关闭输出句柄
}
*/

void setCursor(int size, BOOL visible) {    //设置光标大小及可见性
    CONSOLE_CURSOR_INFO cursor = { size, visible };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

void setWindow(int width, int height) { //设置窗口宽高
    char *strCmd = (char *) malloc(sizeof("mode con: cols=**** lines=****"));
    sprintf(strCmd, "mode con: cols=%d lines=%d", width, height);
    system(strCmd);
    system("cls");
    free(strCmd);   //释放内存
}

