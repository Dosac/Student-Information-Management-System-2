#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"
#include "Windows.h"

#include "function.h"

//����������
#define CMDWIDTH 66
//��������߶�
#define CMDHEIGHT 32
//���ݿ��ļ�����
#define FILENAME "Student Infomation.info"

//���뻷����Microsoft Visual Studio 2017 Community
//����Ԥ����
void start();       //������ϢԤ����
void end();        //������β����
void enterStuInfo(struct strStuInfo *ptr);  //��Ϣ����ģ�飬��Ҫ�ⲿ����
void printStuInfo(struct strStuInfo *ptr);  //��Ϣ���ģ��
void entryStuInfo();    //��Ϣ¼��ģ�飬���ɹ���
void inquireStuInfo();  //��Ϣ��ѯģ�飬���ɹ���
struct strStuInfo *searchStuInfo(char *name, int num);  //��Ϣ��ѯģ�飬��Ҫ�ⲿ����
void modifyStuInfo();   //��Ϣ�޸Ĺ��ܣ�����ģ��
int fileLoad(char *fileName);   //���ݶ�ȡģ��
int fileSave(char *fileName);   //���ݱ���ģ��

void start() {  //������ϢԤ����
    int len = 100;
    system("title ѧ����Ϣ����ϵͳ");   //���ô��ڱ���
    setCursor(1, FALSE);    //���ù��ɼ���
    setWindow(CMDWIDTH, CMDHEIGHT / 2); //���ô��ڴ�С
    putchar('\n');
    displayBlock(CMDWIDTH, "��ӭʹ��ѧ����Ϣ����ϵͳ");
    printf("\n\n\n%66s\n", "���ڶ�ȡѧ����Ϣ�����Ժ�...");
    fileLoad(FILENAME);    //��ȡ�ļ���Ϣ
    printf("\r\b\r%66s\n", "���������ɣ�����������...");
    system("color F0");
    Sleep(1500);
    setWindow(CMDWIDTH, CMDHEIGHT / 2);
}

void end() {    //������β����
    setWindow(CMDWIDTH, CMDHEIGHT / 2);
    putchar('\n');
    displayBlock(CMDWIDTH, "��лʹ��ѧ����Ϣ����ϵͳ");
    printf("\n\n%66s\n", "���ڱ���ѧ����Ϣ�����Ժ�......");
    fileSave(FILENAME);
    printf("\r\b\r%66s\n", "ѧ����Ϣ����ɱ��棬���������˳�...");
    Sleep(1000);
    setWindow(CMDWIDTH, CMDHEIGHT / 2);
    printf("\n\n\n\n\n\n");
    displayBlock(CMDWIDTH, "��л����ʹ�ã��ټ���");
    Sleep(2000);
    exit(0);
}

struct strStuInfo { //�洢���ݵĽṹ��
    int num;            //ѧ��
    char name[32];     //����
    char gender[8];   //�Ա�
    int age;            //����
    struct strScore {   //�ɼ�
        float math;       //����
        float english;  //Ӣ��
        float clang;    //C ����
        float pe;       //����
        float politics; //����ë��
        float total;    //�ܷ�
    }  score;
    char address[128];  //סַ
    struct strStuInfo *before;  //����ǰָ��
    struct strStuInfo *next;    //�����ָ��
} headStuInfo = { 0, "0", "0", 0, {0, 0, 0, 0, 0}, "0", NULL, NULL };

void enterStuInfo(struct strStuInfo *ptr) {   //��Ϣ����ģ�飬��Ҫ�ⲿ����
    inputTip(1, 10);
    printf("������ѧ�ţ�");
    scanf("%d", &(ptr->num));
    CLEARSTDIN;
    inputTip(2, 10);
    printf("������������");
    scanf("%s", &(ptr->name));
    CLEARSTDIN;
    inputTip(3, 10);
    printf("�������Ա�");
    scanf("%s", &(ptr->gender));
    CLEARSTDIN;
    inputTip(4, 10);
    printf("���������䣺");
    scanf("%d", &(ptr->age));
    CLEARSTDIN;
    inputTip(5, 10);
    printf("��������ѧ�ɼ���");
    scanf("%f", &(ptr->score.math));
    CLEARSTDIN;
    inputTip(6, 10);
    printf("������Ӣ��ɼ���");
    scanf("%f", &(ptr->score.english));
    CLEARSTDIN;
    inputTip(7, 10);
    printf("�������̳ɼ���");
    scanf("%f", &(ptr->score.clang));
    CLEARSTDIN;
    inputTip(8, 10);
    printf("�����������ɼ���");
    scanf("%f", &(ptr->score.pe));
    CLEARSTDIN;
    inputTip(9, 10);
    printf("���������ܳɼ���");
    scanf("%f", &(ptr->score.politics));
    ptr->score.total = ptr->score.math + ptr->score.english + ptr->score.clang + ptr->score.pe + ptr->score.politics;
    CLEARSTDIN;
    inputTip(10, 10);
    printf("�������ͥסַ��");
    scanf("%s", &(ptr->address));
    CLEARSTDIN;
}

void printStuInfo(struct strStuInfo *ptr) {   //��Ϣ���ģ��
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

void entryStuInfo() {   //��Ϣ¼��ģ�飬���ɹ���
    struct strStuInfo *entryPtr = NULL;
    displayBlock(CMDWIDTH, "------------");
    displayBlock(CMDWIDTH, "��Ϣ¼��˵�");
    displayBlock(CMDWIDTH, "------------");
    for (entryPtr = &headStuInfo; entryPtr->next != NULL; entryPtr = entryPtr->next);
    entryPtr->next = malloc(sizeof(struct strStuInfo));
    enterStuInfo(entryPtr->next);
    entryPtr->next->before = entryPtr;
    entryPtr = entryPtr->next;
    entryPtr->next = NULL;
    setWindow(CMDWIDTH * 2, CMDHEIGHT);
    printf("\n\nѧ��\t����\t�Ա�\t����\t��ѧ\tӢ��\t���\t����\t����\t�ܷ�\t��ַ\n");
    printStuInfo(entryPtr);
    printf("\n��Ϣ¼����ϣ���������������˵���\n");
    getch();
}

void inquireStuInfo() { //��Ϣ��ѯģ�飬���ɹ���
    int i, t, num, age;
    char name[32];
    struct strStuInfo *searchPtr = NULL;
    do {
        setWindow(CMDWIDTH, CMDHEIGHT / 2);
        putchar('\n');
        displayBlock(CMDWIDTH, "��ӭʹ��ѧ����Ϣ����ϵͳ");
        putchar('\n');
        displayBlock(CMDWIDTH, "----------------------------");
        displayBlock(CMDWIDTH, "------------");
        displayBlock(CMDWIDTH, "��Ϣ��ѯ�˵�");
        displayBlock(CMDWIDTH, "------------");
        displayBlock(CMDWIDTH, "1. ����ѧ�Ų���");
        displayBlock(CMDWIDTH, "2. ������������");
        displayBlock(CMDWIDTH, "3. �����������");
        displayBlock(CMDWIDTH, "4. ��ʾ������Ϣ");
        displayBlock(CMDWIDTH, "0. ���س���˵�");
        displayBlock(CMDWIDTH, "----------------------------");
        do {
            t = getch() - 48;
        } while ((t != 0) && (t != 1) && (t != 2) && (t != 3) && (t != 4));
        if (t == 1) {
            printf("������ѧ�ţ�");
            scanf("%d", &num);
            CLEARSTDIN;
            for (searchPtr = &headStuInfo; ; searchPtr = searchPtr->next) {
                if (searchPtr->num == num) {
                    setWindow(CMDWIDTH * 2, CMDHEIGHT);
                    putchar('\n');
                    displayBlock(CMDWIDTH, "��Ϣ���ҽ��");
                    putchar('\n');
                    printf("ѧ��\t����\t�Ա�\t����\t��ѧ\tӢ��\t���\t����\t����\t�ܷ�\t��ַ\n");
                    printStuInfo(searchPtr);
                    printf("\n�밴��������ز�ѯ�˵�...");
                    getch();
                    break;
                }
                else if (searchPtr->next == NULL) {
                    setWindow(CMDWIDTH, CMDHEIGHT / 2);
                    putchar('\n');
                    displayBlock(CMDWIDTH, "��Ϣ���ҽ��");
                    printf("\n\n\n");
                    displayBlock(CMDWIDTH, "δ�ҵ���ѧ�ţ����������Ƿ�����");
                    Sleep(2000);
                    break;
                }
            }
        }
        else if (t == 2) {
            printf("������������");
            scanf("%s", &name);
            CLEARSTDIN;
            for (searchPtr = &headStuInfo; ; searchPtr = searchPtr->next) {
                if (strcmp(searchPtr->name, name) == 0) {
                    setWindow(CMDWIDTH * 2, CMDHEIGHT);
                    setWindow(CMDWIDTH * 2, CMDHEIGHT);
                    putchar('\n');
                    displayBlock(CMDWIDTH, "��Ϣ���ҽ��");
                    putchar('\n');
                    printf("ѧ��\t����\t�Ա�\t����\t��ѧ\tӢ��\t���\t����\t����\t�ܷ�\t��ַ\n");
                    printStuInfo(searchPtr);
                    printf("\n�밴��������ز�ѯ�˵�...");
                    getch();
                    break;
                }
                else if (searchPtr->next == NULL) {
                    setWindow(CMDWIDTH, CMDHEIGHT / 2);
                    putchar('\n');
                    displayBlock(CMDWIDTH, "��Ϣ���ҽ��");
                    printf("\n\n\n");
                    displayBlock(CMDWIDTH, "δ�ҵ������������������Ƿ�����");
                    Sleep(2000);
                    break;
                }
            }
        }
        else if (t == 3) {
            printf("���������䣺");
            scanf("%d", &age);
            CLEARSTDIN;
            setWindow(CMDWIDTH * 2, CMDHEIGHT);
            putchar('\n');
            displayBlock(CMDWIDTH, "��Ϣ���ҽ��");
            putchar('\n');
            printf("ѧ��\t����\t�Ա�\t����\t��ѧ\tӢ��\t���\t����\t����\t�ܷ�\t��ַ\n");
            for (searchPtr = &headStuInfo, i = 0; ; searchPtr = searchPtr->next) {
                if (searchPtr == NULL) {
                    if (i == 0) {
                        setWindow(CMDWIDTH, CMDHEIGHT / 2);
                        putchar('\n');
                        displayBlock(CMDWIDTH, "��Ϣ���ҽ��");
                        printf("\n\n\n");
                        displayBlock(CMDWIDTH, "δ�ҵ������䣬���������Ƿ�����");
                        Sleep(2000);
                        break;
                    }
                    else {
                        printf("����%d��%d���ѧ����\n", i, age);
                        printf("\n�밴��������ز�ѯ�˵���");
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
                displayBlock(CMDWIDTH, "��Ϣ���ҽ��");
                printf("\n\n\n");
                displayBlock(CMDWIDTH, "ϵͳ����ѧ����Ϣ����¼������ԡ�");
                Sleep(2000);
            }
            else {
                setWindow(CMDWIDTH * 2, CMDHEIGHT);
                putchar('\n');
                displayBlock(CMDWIDTH, "��Ϣ���ҽ��");
                putchar('\n');
                printf("ѧ��\t����\t�Ա�\t����\t��ѧ\tӢ��\t���\t����\t����\t�ܷ�\t��ַ\n");
                for (total = 0, searchPtr = &headStuInfo; searchPtr->next != NULL; searchPtr = searchPtr->next) total++;    //ͳ����Ϣ����
                for (i = 1, searchPtr = headStuInfo.next; searchPtr != NULL; i++, searchPtr = searchPtr->next) {
                    printStuInfo(searchPtr);
                    if (i % (CMDWIDTH - 5) == 0) {
                        displayProgress((float) (i - (CMDWIDTH - 5)) / total * (CMDWIDTH - 2), (float) i / total * (CMDWIDTH - 2), CMDWIDTH - 2);
                        getch();
                    }
                }
                if (i < (CMDWIDTH - 5)) displayProgress(CMDWIDTH - 2, CMDWIDTH - 2, CMDWIDTH - 2);
                else displayProgress((float) (i - (CMDWIDTH - 5)) / total * (CMDWIDTH - 2), CMDWIDTH - 2, CMDWIDTH - 2);
                printf("\n�밴��������ز�ѯ�˵�...");
                getch();
            }
        }
    } while (t != 0);
}

//����ѧ��������ѯ������ѧ����Ϣ��ָ�룩��Ϊ�գ�NULL����δ�ҵ�
struct strStuInfo *searchStuInfo(char *name, int num) {     //��Ϣ��ѯģ�飬��Ҫ�ⲿ����
    struct strStuInfo *searchPtr = NULL;
    for (searchPtr = headStuInfo.next; searchPtr != NULL; searchPtr = searchPtr->next)
        if ((searchPtr->num == num) && strcmp(searchPtr->name, name) == 0) break;
    return searchPtr;
}

void modifyStuInfo() {  //��Ϣ�޸Ĺ��ܣ�����ģ��
    int num;
    char name[32], choose;
    struct strStuInfo *modifyPtr = NULL;
    displayBlock(CMDWIDTH, "----------------------------");
    displayBlock(CMDWIDTH, "------------");
    displayBlock(CMDWIDTH, "��Ϣ�޸Ĳ˵�");
    displayBlock(CMDWIDTH, "------------");
    printf("������ѧ�ţ�");
    scanf("%d", &num);
    CLEARSTDIN;
    printf("������������");
    scanf("%s", name);
    CLEARSTDIN;
    printf("\n----------------------------\n");
    modifyPtr = searchStuInfo(name, num);
    if (modifyPtr == NULL) {
        setWindow(CMDWIDTH, CMDHEIGHT / 2);
        putchar('\n');
        displayBlock(CMDWIDTH, "��Ϣ���ҽ��");
        printf("\n\n\n");
        displayBlock(CMDWIDTH, "δ�ҵ���ѧ����Ϣ�����������Ƿ�����");
    }
    else {
        setWindow(CMDWIDTH * 2, CMDHEIGHT);
        printf("�ҵ�������Ϣ��\n");
        printf("ѧ��\t����\t�Ա�\t����\t��ѧ\tӢ��\t���\t����\t����\t�ܷ�\t��ַ\n");
        printStuInfo(modifyPtr);
        printf("�밴\'Y\'��\'N\'ȷ���޸ģ���\'D\'ɾ������Ϣ��\040");
        do {
            printf("\b");
            choose = getche();
        } while ((choose != 'Y') && (choose != 'y') && (choose != 'N') && (choose != 'n') && (choose != 'D') && (choose != 'd'));
        printf("\n-------------------------\n");
        if ((choose == 'Y') || (choose == 'y')) {
            enterStuInfo(modifyPtr);
            setWindow(CMDWIDTH, CMDHEIGHT / 2);
            putchar('\n');
            displayBlock(CMDWIDTH, "��Ϣ�޸Ľ��");
            printf("\n\n\n");
            displayBlock(CMDWIDTH, "��Ϣ�޸���ɣ������������˵���");
            //printf("ѧ��\t����\t�Ա�\t����\t��ѧ\tӢ��\t���\t����\t����\t�ܷ�\t��ַ\n");
            //printStuInfo(modifyPtr);
        }
        else if ((choose == 'D') || (choose == 'd')) {
            modifyPtr->before->next = modifyPtr->next;
            if(modifyPtr->next != NULL) modifyPtr->next->before = modifyPtr->before;
            free(modifyPtr);
            modifyPtr = NULL;
            setWindow(CMDWIDTH, CMDHEIGHT / 2);
            putchar('\n');
            displayBlock(CMDWIDTH, "��Ϣ�޸Ľ��");
            printf("\n\n\n");
            displayBlock(CMDWIDTH, "��Ϣɾ����ϣ������������˵���");
        }
        else {
            setWindow(CMDWIDTH, CMDHEIGHT / 2);
            putchar('\n');
            displayBlock(CMDWIDTH, "��Ϣ�޸Ľ��");
            printf("\n\n\n");
            displayBlock(CMDWIDTH, "��Ϣδ�����޸ģ������������˵���");
        }
    }
    Sleep(2000);
}

//�Ӳ��� fileName ָ�����ļ��ж�ȡ����
int fileLoad(char *fileName) {  //���ݶ�ȡģ��
    int total = 0, i = 0;
    FILE *filePtr = NULL;
    struct strStuInfo *ptr = &headStuInfo;
    if ((filePtr = fopen(fileName, "rt+")) == NULL) {
        filePtr = fopen(fileName, "wt+");
        displayProgress(0, CMDWIDTH - 2, CMDWIDTH - 2); //��0��100
        return fclose(filePtr);   //����ֵΪ0�����������ݿ��ļ�
    }
    if (fgetc(filePtr) != EOF) {    //����Ƿ�Ϊ�����ݿ��ļ�
        rewind(filePtr);    //�����ļ�ָ��
        //fscanf(filePtr, "%d", &total);  //��ȡ��Ϣ����
        fscanf(filePtr, "%d\t%s\t%s\t%d\t", &total, &(ptr->name), &(ptr->gender), &(ptr->age));
        fscanf(filePtr, "%f\t%f\t%f\t%f\t%f\t%f\t", &(ptr->score.math), &(ptr->score.english), &(ptr->score.clang), &(ptr->score.pe), &(ptr->score.politics), &(ptr->score.total));
        fscanf(filePtr, "%s\n", &(ptr->address));
        if (total == 0) displayProgress(0, CMDWIDTH - 2, CMDWIDTH - 2);
        else {
            while (!feof(filePtr)) {    //��ȡ�ļ���Ϣ�������浽�ڴ���
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
        return fclose(filePtr) + 1;   //����ֵΪ1���ɹ����ļ������ɹ���ȡ��Ϣ
    }
    else {
        displayProgress(0, CMDWIDTH - 2, CMDWIDTH - 2);
        return fclose(filePtr) + 2;   //����ֵΪ2���ɹ����ļ������ļ�Ϊ��
    }
}

//����� fileName ָ�����ļ��б�������
int fileSave(char *fileName) {   //���ݱ���ģ��
    int total = 0, i = 0;
    FILE *filePtr = NULL;
    struct strStuInfo *ptr = &headStuInfo;
    filePtr = fopen(fileName, "wt+");   //�������ͣ��޷���ȡԭ�����ݿ��ļ�
    for (total = 0; ptr->next != NULL; ptr = ptr->next) total++;    //ͳ����Ϣ����
    if ((headStuInfo.num = total) == 0) {
        fprintf(filePtr, "%d\t%s\t%s\t%d\t", ptr->num, ptr->name, ptr->gender, ptr->age);
        fprintf(filePtr, "%f\t%f\t%f\t%f\t%f\t%f\t", ptr->score.math, ptr->score.english, ptr->score.clang, ptr->score.pe, ptr->score.politics, ptr->score.total);
        fprintf(filePtr, "%s\n", ptr->address);
        displayProgress(0, CMDWIDTH - 2, CMDWIDTH - 2);
    }
    else {
        for (i = 0, ptr = &headStuInfo; ptr != NULL; i++, ptr = ptr->next) {    //д����Ϣ
            fprintf(filePtr, "%d\t%s\t%s\t%d\t", ptr->num, ptr->name, ptr->gender, ptr->age);
            fprintf(filePtr, "%f\t%f\t%f\t%f\t%f\t%f\t", ptr->score.math, ptr->score.english, ptr->score.clang, ptr->score.pe, ptr->score.politics, ptr->score.total);
            fprintf(filePtr, "%s\n", ptr->address);
            displayProgress((float) (i - 1) / total * (CMDWIDTH - 2), (float) i / total * (CMDWIDTH - 2), CMDWIDTH - 2);
        }
    }
    return fclose(filePtr);   //����ֵΪ0���ɹ�д����Ϣ
}

int main() {    //ѧ����Ϣ����ϵͳ��������
    int choose;
    start();
    do {
        setWindow(CMDWIDTH, CMDHEIGHT / 2);
        putchar('\n');
        displayBlock(CMDWIDTH, "��ӭʹ��ѧ����Ϣ����ϵͳ");
        putchar('\n');
        displayBlock(CMDWIDTH, "----------------------------");
        displayBlock(CMDWIDTH, "------------");
        displayBlock(CMDWIDTH, "����ϵͳ�˵�");
        displayBlock(CMDWIDTH, "------------");
        displayBlock(CMDWIDTH, "1. ѧ����Ϣ��ѯ");
        displayBlock(CMDWIDTH, "2. ѧ����Ϣ¼��");
        displayBlock(CMDWIDTH, "3. ѧ����Ϣ�޸�");
        displayBlock(CMDWIDTH, "0. �˳�����ϵͳ");
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