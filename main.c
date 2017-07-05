#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"
#include "Windows.h"

#include "function.h"

//输出环境宽度
#define CMDWIDTH 66
//输出环境高度
#define CMDHEIGHT 32
//数据库文件名称
#define FILENAME "Student Infomation.info"

//编译环境：Microsoft Visual Studio 2017 Community
//函数预声明
void start();       //环境信息预处理
void end();        //程序收尾工作
void enterStuInfo(struct strStuInfo *ptr);  //信息输入模块，需要外部调用
void printStuInfo(struct strStuInfo *ptr);  //信息输出模块
void entryStuInfo();    //信息录入模块，集成功能
void inquireStuInfo();  //信息查询模块，集成功能
struct strStuInfo *searchStuInfo(char *name, int num);  //信息查询模块，需要外部调用
void modifyStuInfo();   //信息修改功能，集成模块
int fileLoad(char *fileName);   //数据读取模块
int fileSave(char *fileName);   //数据保存模块

void start() {  //环境信息预处理
    int len = 100;
    system("title 学生信息管理系统");   //设置窗口标题
    setCursor(1, FALSE);    //设置光标可见性
    setWindow(CMDWIDTH, CMDHEIGHT / 2); //设置窗口大小
    putchar('\n');
    displayBlock(CMDWIDTH, "欢迎使用学生信息管理系统");
    printf("\n\n\n%66s\n", "正在读取学生信息，请稍后...");
    fileLoad(FILENAME);    //读取文件信息
    printf("\r\b\r%66s\n", "程序加载完成，正在启动中...");
    system("color F0");
    Sleep(1500);
    setWindow(CMDWIDTH, CMDHEIGHT / 2);
}

void end() {    //程序收尾工作
    setWindow(CMDWIDTH, CMDHEIGHT / 2);
    putchar('\n');
    displayBlock(CMDWIDTH, "感谢使用学生信息管理系统");
    printf("\n\n%66s\n", "正在保存学生信息，请稍后......");
    fileSave(FILENAME);
    printf("\r\b\r%66s\n", "学生信息已完成保存，程序正在退出...");
    Sleep(1000);
    setWindow(CMDWIDTH, CMDHEIGHT / 2);
    printf("\n\n\n\n\n\n");
    displayBlock(CMDWIDTH, "感谢您的使用，再见！");
    Sleep(2000);
    exit(0);
}

struct strStuInfo { //存储数据的结构体
    int num;            //学号
    char name[32];     //姓名
    char gender[8];   //性别
    int age;            //年龄
    struct strScore {   //成绩
        float math;       //高数
        float english;  //英语
        float clang;    //C 语言
        float pe;       //体育
        float politics; //马哲毛概
        float total;    //总分
    }  score;
    char address[128];  //住址
    struct strStuInfo *before;  //链表前指针
    struct strStuInfo *next;    //链表后指针
} headStuInfo = { 0, "0", "0", 0, {0, 0, 0, 0, 0}, "0", NULL, NULL };

void enterStuInfo(struct strStuInfo *ptr) {   //信息输入模块，需要外部调用
    inputTip(1, 10);
    printf("请输入学号：");
    scanf("%d", &(ptr->num));
    CLEARSTDIN;
    inputTip(2, 10);
    printf("请输入姓名：");
    scanf("%s", &(ptr->name));
    CLEARSTDIN;
    inputTip(3, 10);
    printf("请输入性别：");
    scanf("%s", &(ptr->gender));
    CLEARSTDIN;
    inputTip(4, 10);
    printf("请输入年龄：");
    scanf("%d", &(ptr->age));
    CLEARSTDIN;
    inputTip(5, 10);
    printf("请输入数学成绩：");
    scanf("%f", &(ptr->score.math));
    CLEARSTDIN;
    inputTip(6, 10);
    printf("请输入英语成绩：");
    scanf("%f", &(ptr->score.english));
    CLEARSTDIN;
    inputTip(7, 10);
    printf("请输入编程成绩：");
    scanf("%f", &(ptr->score.clang));
    CLEARSTDIN;
    inputTip(8, 10);
    printf("请输入体育成绩：");
    scanf("%f", &(ptr->score.pe));
    CLEARSTDIN;
    inputTip(9, 10);
    printf("请输入马哲成绩：");
    scanf("%f", &(ptr->score.politics));
    ptr->score.total = ptr->score.math + ptr->score.english + ptr->score.clang + ptr->score.pe + ptr->score.politics;
    CLEARSTDIN;
    inputTip(10, 10);
    printf("请输入家庭住址：");
    scanf("%s", &(ptr->address));
    CLEARSTDIN;
}

void printStuInfo(struct strStuInfo *ptr) {   //信息输出模块
    printf("%4d\t", ptr->num);
    printf("%4s\t", ptr->name);
    printf("%4s\t", ptr->gender);
    printf("%4d\t", ptr->age);
    printf("%3.1f\t", ptr->score.math);
    printf("%3.1f\t", ptr->score.english);
    printf("%3.1f\t", ptr->score.clang);
    printf("%3.1f\t", ptr->score.pe);
    printf("%3.1f\t", ptr->score.politics);
    printf("%3.1f\t", ptr->score.total);
    printf("%s\n", ptr->address);
}

void entryStuInfo() {   //信息录入模块，集成功能
    struct strStuInfo *entryPtr = NULL;
    displayBlock(CMDWIDTH, "------------");
    displayBlock(CMDWIDTH, "信息录入菜单");
    displayBlock(CMDWIDTH, "------------");
    for (entryPtr = &headStuInfo; entryPtr->next != NULL; entryPtr = entryPtr->next);
    entryPtr->next = malloc(sizeof(struct strStuInfo));
    enterStuInfo(entryPtr->next);
    entryPtr->next->before = entryPtr;
    entryPtr = entryPtr->next;
    entryPtr->next = NULL;
    setWindow(CMDWIDTH * 2, CMDHEIGHT);
    printf("\n\n学号\t姓名\t性别\t年龄\t数学\t英语\t编程\t体育\t马哲\t总分\t地址\n");
    printStuInfo(entryPtr);
    printf("\n信息录入完毕，按任意键返回主菜单。\n");
    getch();
}

void inquireStuInfo() { //信息查询模块，集成功能
    int i, t, num, age;
    char name[32];
    struct strStuInfo *searchPtr = NULL;
    do {
        setWindow(CMDWIDTH, CMDHEIGHT / 2);
        putchar('\n');
        displayBlock(CMDWIDTH, "欢迎使用学生信息管理系统");
        putchar('\n');
        displayBlock(CMDWIDTH, "----------------------------");
        displayBlock(CMDWIDTH, "------------");
        displayBlock(CMDWIDTH, "信息查询菜单");
        displayBlock(CMDWIDTH, "------------");
        displayBlock(CMDWIDTH, "1. 根据学号查找");
        displayBlock(CMDWIDTH, "2. 根据姓名查找");
        displayBlock(CMDWIDTH, "3. 根据年龄查找");
        displayBlock(CMDWIDTH, "4. 显示所有信息");
        displayBlock(CMDWIDTH, "0. 返回程序菜单");
        displayBlock(CMDWIDTH, "----------------------------");
        do {
            t = getch() - 48;
        } while ((t != 0) && (t != 1) && (t != 2) && (t != 3) && (t != 4));
        if (t == 1) {
            printf("请输入学号：");
            scanf("%d", &num);
            CLEARSTDIN;
            for (searchPtr = &headStuInfo; ; searchPtr = searchPtr->next) {
                if (searchPtr->num == num) {
                    setWindow(CMDWIDTH * 2, CMDHEIGHT);
                    putchar('\n');
                    displayBlock(CMDWIDTH, "信息查找结果");
                    putchar('\n');
                    printf("学号\t姓名\t性别\t年龄\t数学\t英语\t编程\t体育\t马哲\t总分\t地址\n");
                    printStuInfo(searchPtr);
                    printf("\n请按任意键返回查询菜单...");
                    getch();
                    break;
                }
                else if (searchPtr->next == NULL) {
                    setWindow(CMDWIDTH, CMDHEIGHT / 2);
                    putchar('\n');
                    displayBlock(CMDWIDTH, "信息查找结果");
                    printf("\n\n\n");
                    displayBlock(CMDWIDTH, "未找到该学号，请检查输入是否有误。");
                    Sleep(2000);
                    break;
                }
            }
        }
        else if (t == 2) {
            printf("请输入姓名：");
            scanf("%s", &name);
            CLEARSTDIN;
            for (searchPtr = &headStuInfo; ; searchPtr = searchPtr->next) {
                if (strcmp(searchPtr->name, name) == 0) {
                    setWindow(CMDWIDTH * 2, CMDHEIGHT);
                    setWindow(CMDWIDTH * 2, CMDHEIGHT);
                    putchar('\n');
                    displayBlock(CMDWIDTH, "信息查找结果");
                    putchar('\n');
                    printf("学号\t姓名\t性别\t年龄\t数学\t英语\t编程\t体育\t马哲\t总分\t地址\n");
                    printStuInfo(searchPtr);
                    printf("\n请按任意键返回查询菜单...");
                    getch();
                    break;
                }
                else if (searchPtr->next == NULL) {
                    setWindow(CMDWIDTH, CMDHEIGHT / 2);
                    putchar('\n');
                    displayBlock(CMDWIDTH, "信息查找结果");
                    printf("\n\n\n");
                    displayBlock(CMDWIDTH, "未找到该姓名，请检查输入是否有误。");
                    Sleep(2000);
                    break;
                }
            }
        }
        else if (t == 3) {
            printf("请输入年龄：");
            scanf("%d", &age);
            CLEARSTDIN;
            setWindow(CMDWIDTH * 2, CMDHEIGHT);
            putchar('\n');
            displayBlock(CMDWIDTH, "信息查找结果");
            putchar('\n');
            printf("学号\t姓名\t性别\t年龄\t数学\t英语\t编程\t体育\t马哲\t总分\t地址\n");
            for (searchPtr = &headStuInfo, i = 0; ; searchPtr = searchPtr->next) {
                if (searchPtr == NULL) {
                    if (i == 0) {
                        setWindow(CMDWIDTH, CMDHEIGHT / 2);
                        putchar('\n');
                        displayBlock(CMDWIDTH, "信息查找结果");
                        printf("\n\n\n");
                        displayBlock(CMDWIDTH, "未找到该年龄，请检查输入是否有误。");
                        Sleep(2000);
                        break;
                    }
                    else {
                        printf("共有%d名%d岁的学生。\n", i, age);
                        printf("\n请按任意键返回查询菜单。");
                        getch();
                        break;
                    }
                }
                else if (searchPtr->age == age) {
                    printStuInfo(searchPtr);
                    i++;
                }
            }
        }
        else if (t == 4) {
            int total;
            char strSpace[CMDWIDTH + 1];
            memset(strSpace, '\040', sizeof(strSpace) - 1);
            strSpace[CMDWIDTH] = '\0';
            if (headStuInfo.next == NULL) {
                setWindow(CMDWIDTH, CMDHEIGHT / 2);
                putchar('\n');
                displayBlock(CMDWIDTH, "信息查找结果");
                printf("\n\n\n");
                displayBlock(CMDWIDTH, "系统暂无学生信息，请录入后重试。");
                Sleep(2000);
            }
            else {
                setWindow(CMDWIDTH * 2, CMDHEIGHT);
                putchar('\n');
                displayBlock(CMDWIDTH, "信息查找结果");
                putchar('\n');
                printf("学号\t姓名\t性别\t年龄\t数学\t英语\t编程\t体育\t马哲\t总分\t地址\n");
                for (total = 0, searchPtr = &headStuInfo; searchPtr->next != NULL; searchPtr = searchPtr->next) total++;    //统计信息总数
                for (i = 1, searchPtr = headStuInfo.next; searchPtr != NULL; i++, searchPtr = searchPtr->next) {
                    printStuInfo(searchPtr);
                    if (i % (CMDWIDTH - 5) == 0) {
                        displayProgress((float) (i - (CMDWIDTH - 5)) / total * (CMDWIDTH - 2), (float) i / total * (CMDWIDTH - 2), CMDWIDTH - 2);
                        getch();
                    }
                }
                if (i < (CMDWIDTH - 5)) displayProgress(CMDWIDTH - 2, CMDWIDTH - 2, CMDWIDTH - 2);
                else displayProgress((float) (i - (CMDWIDTH - 5)) / total * (CMDWIDTH - 2), CMDWIDTH - 2, CMDWIDTH - 2);
                printf("\n请按任意键返回查询菜单...");
                getch();
            }
        }
    } while (t != 0);
}

//依据学号姓名查询并返回学生信息（指针），为空（NULL）则未找到
struct strStuInfo *searchStuInfo(char *name, int num) {     //信息查询模块，需要外部调用
    struct strStuInfo *searchPtr = NULL;
    for (searchPtr = headStuInfo.next; searchPtr != NULL; searchPtr = searchPtr->next)
        if ((searchPtr->num == num) && strcmp(searchPtr->name, name) == 0) break;
    return searchPtr;
}

void modifyStuInfo() {  //信息修改功能，集成模块
    int num;
    char name[32], choose;
    struct strStuInfo *modifyPtr = NULL;
    displayBlock(CMDWIDTH, "----------------------------");
    displayBlock(CMDWIDTH, "------------");
    displayBlock(CMDWIDTH, "信息修改菜单");
    displayBlock(CMDWIDTH, "------------");
    printf("请输入学号：");
    scanf("%d", &num);
    CLEARSTDIN;
    printf("请输入姓名：");
    scanf("%s", name);
    CLEARSTDIN;
    printf("\n----------------------------\n");
    modifyPtr = searchStuInfo(name, num);
    if (modifyPtr == NULL) {
        setWindow(CMDWIDTH, CMDHEIGHT / 2);
        putchar('\n');
        displayBlock(CMDWIDTH, "信息查找结果");
        printf("\n\n\n");
        displayBlock(CMDWIDTH, "未找到该学生信息，请检查输入是否有误。");
    }
    else {
        setWindow(CMDWIDTH * 2, CMDHEIGHT);
        printf("找到如下信息：\n");
        printf("学号\t姓名\t性别\t年龄\t数学\t英语\t编程\t体育\t马哲\t总分\t地址\n");
        printStuInfo(modifyPtr);
        printf("请按\'Y\'或\'N\'确认修改，或按\'D\'删除该信息：\040");
        do {
            printf("\b");
            choose = getche();
        } while ((choose != 'Y') && (choose != 'y') && (choose != 'N') && (choose != 'n') && (choose != 'D') && (choose != 'd'));
        printf("\n-------------------------\n");
        if ((choose == 'Y') || (choose == 'y')) {
            enterStuInfo(modifyPtr);
            setWindow(CMDWIDTH, CMDHEIGHT / 2);
            putchar('\n');
            displayBlock(CMDWIDTH, "信息修改结果");
            printf("\n\n\n");
            displayBlock(CMDWIDTH, "信息修改完成，即将返回主菜单。");
            //printf("学号\t姓名\t性别\t年龄\t数学\t英语\t编程\t体育\t马哲\t总分\t地址\n");
            //printStuInfo(modifyPtr);
        }
        else if ((choose == 'D') || (choose == 'd')) {
            modifyPtr->before->next = modifyPtr->next;
            if(modifyPtr->next != NULL) modifyPtr->next->before = modifyPtr->before;
            free(modifyPtr);
            modifyPtr = NULL;
            setWindow(CMDWIDTH, CMDHEIGHT / 2);
            putchar('\n');
            displayBlock(CMDWIDTH, "信息修改结果");
            printf("\n\n\n");
            displayBlock(CMDWIDTH, "信息删除完毕，即将返回主菜单。");
        }
        else {
            setWindow(CMDWIDTH, CMDHEIGHT / 2);
            putchar('\n');
            displayBlock(CMDWIDTH, "信息修改结果");
            printf("\n\n\n");
            displayBlock(CMDWIDTH, "信息未进行修改，即将返回主菜单。");
        }
    }
    Sleep(2000);
}

//从参数 fileName 指定的文件中读取数据
int fileLoad(char *fileName) {  //数据读取模块
    int total = 0, i = 0;
    FILE *filePtr = NULL;
    struct strStuInfo *ptr = &headStuInfo;
    if ((filePtr = fopen(fileName, "rt+")) == NULL) {
        filePtr = fopen(fileName, "wt+");
        displayProgress(0, CMDWIDTH - 2, CMDWIDTH - 2); //从0到100
        return fclose(filePtr);   //返回值为0：创建新数据库文件
    }
    if (fgetc(filePtr) != EOF) {    //检测是否为空数据库文件
        rewind(filePtr);    //重置文件指针
        //fscanf(filePtr, "%d", &total);  //获取信息总数
        fscanf(filePtr, "%d\t%s\t%s\t%d\t", &total, &(ptr->name), &(ptr->gender), &(ptr->age));
        fscanf(filePtr, "%f\t%f\t%f\t%f\t%f\t%f\t", &(ptr->score.math), &(ptr->score.english), &(ptr->score.clang), &(ptr->score.pe), &(ptr->score.politics), &(ptr->score.total));
        fscanf(filePtr, "%s\n", &(ptr->address));
        if (total == 0) displayProgress(0, CMDWIDTH - 2, CMDWIDTH - 2);
        else {
            while (!feof(filePtr)) {    //读取文件信息，并保存到内存中
                ptr->next = (struct strStuInfo*)malloc(sizeof(struct strStuInfo));
                ptr->next->before = ptr;
                ptr->next->next = NULL;
                ptr = ptr->next;
                fscanf(filePtr, "%d\t%s\t%s\t%d\t", &(ptr->num), &(ptr->name), &(ptr->gender), &(ptr->age));
                fscanf(filePtr, "%f\t%f\t%f\t%f\t%f\t%f\t", &(ptr->score.math), &(ptr->score.english), &(ptr->score.clang), &(ptr->score.pe), &(ptr->score.politics), &(ptr->score.total));
                fscanf(filePtr, "%s\n", &(ptr->address));
                /*if (total == 0) displayProgress(0, CMDWIDTH - 2, CMDWIDTH - 2);
                else displayProgress((float) (i - 1) / total * (CMDWIDTH - 2), (float) (++i) / total * (CMDWIDTH - 2), CMDWIDTH - 2);*/
                displayProgress((float) (i - 1) / total * (CMDWIDTH - 2), (float) (++i) / total * (CMDWIDTH - 2), CMDWIDTH - 2);
            }
        }
        return fclose(filePtr) + 1;   //返回值为1：成功打开文件，并成功读取信息
    }
    else {
        displayProgress(0, CMDWIDTH - 2, CMDWIDTH - 2);
        return fclose(filePtr) + 2;   //返回值为2：成功打开文件，但文件为空
    }
}

//向参数 fileName 指定的文件中保存数据
int fileSave(char *fileName) {   //数据保存模块
    int total = 0, i = 0;
    FILE *filePtr = NULL;
    struct strStuInfo *ptr = &headStuInfo;
    filePtr = fopen(fileName, "wt+");   //警告类型，无法读取原有数据库文件
    for (total = 0; ptr->next != NULL; ptr = ptr->next) total++;    //统计信息总数
    if ((headStuInfo.num = total) == 0) {
        fprintf(filePtr, "%d\t%s\t%s\t%d\t", ptr->num, ptr->name, ptr->gender, ptr->age);
        fprintf(filePtr, "%f\t%f\t%f\t%f\t%f\t%f\t", ptr->score.math, ptr->score.english, ptr->score.clang, ptr->score.pe, ptr->score.politics, ptr->score.total);
        fprintf(filePtr, "%s\n", ptr->address);
        displayProgress(0, CMDWIDTH - 2, CMDWIDTH - 2);
    }
    else {
        for (i = 0, ptr = &headStuInfo; ptr != NULL; i++, ptr = ptr->next) {    //写入信息
            fprintf(filePtr, "%d\t%s\t%s\t%d\t", ptr->num, ptr->name, ptr->gender, ptr->age);
            fprintf(filePtr, "%f\t%f\t%f\t%f\t%f\t%f\t", ptr->score.math, ptr->score.english, ptr->score.clang, ptr->score.pe, ptr->score.politics, ptr->score.total);
            fprintf(filePtr, "%s\n", ptr->address);
            displayProgress((float) (i - 1) / total * (CMDWIDTH - 2), (float) i / total * (CMDWIDTH - 2), CMDWIDTH - 2);
        }
    }
    return fclose(filePtr);   //返回值为0：成功写入信息
}

int main() {    //学生信息管理系统，主函数
    int choose;
    start();
    do {
        setWindow(CMDWIDTH, CMDHEIGHT / 2);
        putchar('\n');
        displayBlock(CMDWIDTH, "欢迎使用学生信息管理系统");
        putchar('\n');
        displayBlock(CMDWIDTH, "----------------------------");
        displayBlock(CMDWIDTH, "------------");
        displayBlock(CMDWIDTH, "管理系统菜单");
        displayBlock(CMDWIDTH, "------------");
        displayBlock(CMDWIDTH, "1. 学生信息查询");
        displayBlock(CMDWIDTH, "2. 学生信息录入");
        displayBlock(CMDWIDTH, "3. 学生信息修改");
        displayBlock(CMDWIDTH, "0. 退出管理系统");
        displayBlock(CMDWIDTH, "----------------------------");
        do {
            choose = getch() - 48;
        } while ((choose != 1) && (choose != 2) && (choose != 3) && (choose != 0));
        switch (choose) {
            case 1: system("cls"); inquireStuInfo(); break;
            case 2: system("cls"); entryStuInfo(); break;
            case 3: system("cls"); modifyStuInfo(); break;
        }
    } while (choose != 0);

    end();
}