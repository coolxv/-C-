#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#define STUSIDE 9    //ѧ����
#define TEACHSIDE 11   //��ʦ��
#define INTRODUCTION 13   //����
#define DECLARE 15    //����
#define LEAVE 17    //�˳�
#define ACCOUNT_IN 5  //  ��¼�˻�
#define PSWD_IN 8   //   ��¼����
#define _OK 11  //  ��ť����¼��
#define SIGN_UP 14  //ע��
#define FORGET_PSWD 17  //��������
#define _CANCEL 20//  ��ť��ȡ����
#define WINDOW_X 80   //����̨���ڿ��
#define WINDOW_Y 25   //����̨���ڸ߶�
#define DOWN 80    //�����ϼ�
#define UP 72     //�����¼�
#define ENTER 13  //���̻س�
#define _INPUT 3  //��������
#define MAKE_SURE 6  //ȷ������
#define _QUESTION 9  //�ܱ�
#define _ANSWER 12   //��
#define _YES 15 // ȷ��
#define _NO 18  //ȡ��;

#define VIEW 7  //�鿴�ɼ�
#define INCREASE 9 //���ӳɼ�
#define MODIFY 11 //�޸ĳɼ�
#define DELETE_GRADE 13//ɾ���ɼ�
#define MODIFY_PSWD 15//�޸�����
#define MODIFY_STU_PSWD 17//�޸�ѧ������
#define LEAVE_TEACH_SIDE 19//�˳���ʦ��
typedef struct Student{
    int id;
    char pswd[11];
    char name[20];
    int c_grade;
    int math_grade;
    int english_grade;
}Student;

typedef struct node{//����ڵ㣬��������һ��Student���͵ı���
    Student stu;
    struct node *next;
}Node;
////////////////////////////////////////////////////////������ļ���������
void myExchange(Node * ,Node *);                  //�������ڵ�������򽻻�
Node* listSort(Node *head,const char *grade_file_name);//���ļ����������򣨴Ӹߵ��ͣ�
Node* readAndWrite(Node *head,const char *file_name);//���ļ���ָ������
Node* writeAndRead(Node *head,const char *file_name);//��ָ������д���ļ�
Node* getMinNode(Node* head);           //����һ�������е���������С�Ľڵ�ָ��
Node* creatList(const char* file);    //��������
void printList(Node *head);//��ӡ
void deleteList(Node *head);//ɾ����������
//void deleteNode(Node* head, int n);//ɾ�������ڵ�
void insertNode(Node*  , const char* );//���뵥���ڵ�
/**��������ĺ���**/
Node* searchStudentNode(Node* head ,int id);    //���Ҷ�Ӧid�Ľڵ�
Node* modifyStudentInfo(Node* head ,const char *file_name);// �޸�ѧ����Ϣ
Node* deleteNode(Node* head, const char* file_name);
void searchCgrade(Node* head ,int id, int grade);//����C���Գɼ�
void searchMgrade(Node* head ,int id, int grade);//������ѧ�ɼ�

////////////////////////////////////////////��¼ǰ����

typedef struct teacherMesg Teacher;
struct teacherMesg{//     ����ṹ�壺��ʦ�˺���Ϣ
    char account[11] ;
    char pswd[11] ;
    char question[50];     //�ܱ�
    char answer[30];       //��
}teacher_mesg;

typedef struct teacherNode{
    Teacher teach;
    struct teacherNode *next;
}tNode;

void noticeCopyright();//   ��Ȩ����
void setConsoleSize();//   ���ÿ���̨��С
void printCorlor(int corlor);//   ��������򱳾���ɫ
void cursorGoto(int x , int y);//   ���ƹ��
void isCursorActive(int state);//  ����Ƿ�ɼ�
void outputContents();//    ��ҵ�¼��Ϸ�ڽ���
void gameUI(int color);    //   ��Ϸװ�λ���
void funnyThing();//   һЩ��Ȥ�Ķ���
int warningDialog(const char *text , const char *title ,const char *opResult);//  ������ʾ  ���������ݡ����⡢�����ɹ���ӡ����
void printArrow(int x , int y);//  ��Ϸ������ͷ��������꣩
int choiceReact();//    һ���ӿ� �����ѡ�����
void moveNotice(int x,int y,const char* text);//   һ����ͷ��������ʾ
void gameBuffer();//   ���涯̬��Ϸ�������
void inputAccountFace();//  ��ӡ��ʾ�û���¼����
void signUpFace();//��ӡ�û�ע�����
void forgetPswdFace();//��ӡ�����������
void userUI();//   �û���¼�˺�ҳ�漰�ӿ�ʵ��
void goToAccount();//���������˺ż���ʾ���
void goToPswd();// �����������뼰��ʾ���
void saveOrNot(int is_not);//�Ƿ���ʾ�˺�����
void WelcomeUI();//��ҵ�¼�����
void creatAccountFace();//���ע��ҳ��
void creatAccount();//ע���˺Žӿ�
void findPswd();//   �һ�����ӿ�
void drawItem(int face_x , int face_y,const char*);
void creatImplement(int number);
void repeatPrintPswd();//���´�ӡע��ҳ�����������Ϣ
void clearList(char *list,int index);//����ַ�������ֵΪ�մ�

///////////////////////////////////////��¼���������

void teacherOpUI();//��ʦ�˵�¼�����ҳ����
void teacherOPImplement();//��ʦ��������ʵ�ֺ���
FILE *teacher_file = NULL;  //������д��ʦ��Ϣ�ļ���ָ��
FILE *student_file = NULL;//ָ��洢ѧ����Ϣ���ļ�
char pswd1[11];  //ע�����������
char pswd2[11];
char question[41];     //�ܱ�
char answer[21];       //��
int press_times;
/*��Ϸ����һ����С��bugӰ�쵽�������ԣ�����Ϊ�˲�Ӱ�쵽����ģ���������ã����ٽ����޲�*/

///////////////////////////////////////////������
int main()
{
    //Node *head = NULL;
    srand(time(0));
    //int i = rand()%9;
    //printf("%d",i);
    setConsoleSize();//���ÿ���̨��С
    isCursorActive(0);//��겻�ɼ�
    //printCorlor(14);//����Ϊ��ɫ
    //funnyThing();//���汣��..
    //system("cls");
    //gameBuffer();
    //system("cls");
    userUI();//�û���¼�˺��������
    //WelcomeUI();//�û���Ϸ�ڽ���
    //deleteList(head);//�������������ڴ�
    //teacherOpUI();
    //teacherOPImplement("1779249225");
    //listSort(head,"6985924183.txt");
    //deleteList(head);
    return 0;

}
///////////////////////////////////////////��¼ǰ����

void WelcomeUI(){//    deeperUserUI()     ��¼����漰��ӿ�
    while(1){
        int i;
        outputContents();
        i = choiceReact(32,9,2,STUSIDE,LEAVE,outputContents);
        switch(i){
          case STUSIDE :
                        break;

        case TEACHSIDE :    Sleep(1000);
                            userUI();
                        break;

     case INTRODUCTION :    system("cls");
                        break;

          case DECLARE :    system("cls");
                            noticeCopyright();
                        break;

            case LEAVE :    if(warningDialog("��ȷ��Ҫ�˳�ϵͳ��","�˳�����","�����˳�ϵͳ")){
                                exit(1);
                            }
                        break;
        }
    }
}

void drawItem(int face_x , int face_y,const char* item){//    drawItem()     ������(face_x,face_y)����ӡһ��ָ���ַ�������
    cursorGoto(face_x , face_y);
    printf("%s",item);
}

void noticeCopyright(){//    noticeCopyright()     �����Ȩ��Ϣ������Ҫ��
    //printf("\n\n");
    gameUI(0x02);
    printCorlor(12);
    cursorGoto(2,3);
    printf("�ó���ԭ����19����רҵ������������ƿ���ʵ������ֹ����һ����ҵ��;��\n");
    cursorGoto(2,4);
    printf("����ת���븽�ϴ�������ע������:\n\n");
    cursorGoto(2,5);
    printf("https://github.com/Prograper/FirstRepository/blob/master/ClassTest\n\n");
    cursorGoto(2,8);
    isCursorActive(0);
    printf("��Ȼ���������С���ã���������һ��Ҫ���ذ�Ȩ��^_^");
    cursorGoto(2,10);
    system("pause");
    system("cls");
}

void printCorlor(int corlor){//  PrintCorlor()    �ӿڣ� ������ƿ���̨background��foreground��ɫ���Լ�text��ɫ

    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hOut,corlor);
    //CloseHandle(hOut);
    /**������һЩ����**/
    /*
    *SetConsoleTextAttribute�����ǿ�һ���ֽڵĵ���λ������ǰ��ɫ������λ�����Ʊ���ɫ
    *FOREGROUND_BLUE      ���壺��         ��Ӧֵ��0X01
    *FOREGROUND_GREEN    ���壺��     ��Ӧֵ��0X02
    *FOREGROUND_RED       ���壺��    ��Ӧֵ��0X04
    *FOREGROUND_INTENSITY    ǰ������   ��Ӧֵ��0X08
    *BACKGROUND_BLUE     ��������   ��Ӧֵ��0X10
    *BACKGROUND_GREEN   ��������   ��Ӧֵ��0X20
    *BACKGROUND_RED     ��������    ��Ӧֵ��0X40
    *BACKGROUND_INTENSITY   ��������   ��Ӧֵ��0X80
    *12  Ϊ��ɫ    9  Ϊ����ɫ    14  Ϊ��ɫ   13  Ϊ��ɫ  7  Ϊϵͳɫ�����Ͼ���������ɫ��
    */
}

void setConsoleSize(){//    setConsoleSize()    ��ʼ������̨�ߴ�Ϊ��80   ��25
    system("mode con cols=80 lines=25");
}

void cursorGoto(int x , int y){//    cursorGoto()     �ӿڣ�������ƿ���̨����ƶ��������x,y

    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD myCoord;
    myCoord.X = x;
    myCoord.Y = y;

    SetConsoleCursorPosition(hOut,myCoord);
    /****/
    //CloseHandle(hOut);
}

void isCursorActive(int state){//    isCursorActive()    �ӿڣ� ����һ��ֵ����������Ƿ�����,0���أ�1��ʾ

    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor;

    GetConsoleCursorInfo(hOut,&cursor);
    cursor.bVisible = state;
    SetConsoleCursorInfo(hOut,&cursor);
}

void outputContents(){//    outputContents()     ��ϷĿ¼   �ӿڣ����ѡ��Ŀ¼����������


    isCursorActive(0);
    //gameUI(14);
    printCorlor(13);
    cursorGoto(14,1);
    printf("                �X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[ ");
    cursorGoto(14,2);
    printf("****************�Uѧ���ɼ�����ϵͳ�U ***************");
    cursorGoto(14,3);
    printf("                �^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a ");
    cursorGoto(35,9);
    printf("ѧ����");
    cursorGoto(35,11);
    printf("��ʦ��");
    cursorGoto(35,13);
    printf("���ܽ���");
    cursorGoto(35,15);
    printf("��Ȩ����");
    cursorGoto(35,17);
    printf("�˳�ϵͳ");
    moveNotice(10,23,"Tips:���ü������¼������Ƽ�ͷ�����ƶ������س�����ѡ��");
}
//choiceReact()   ��������ֱ���Ŀ¼��һ�е�x��y����;Ŀ¼���gap�����¶�Ŀ¼ֵ(sorry �����������)��Ҫ��ӡ�Ŀ�ܺ���
int choiceReact(int content_x,int content_y,int gap,int up_lim,int down_lim, void (*fOut)()){//    choicReact()
/***����������������1��2������Ŀ¼���꣬����3��Ŀ¼���������4��5���ϡ��¶������꣬����6��ָ�뺯��***/
    //content_x = 30;     //������                 //    �ڿ�ʼĿ¼�����ͷָ�������һ������������һ����ҵ�ѡ��intֵ
    //content_y = 11;
    int sub = down_lim - up_lim;
    int user_keyboard;     //�û��������̼�λֵ
    int user_choice = up_lim;
    printCorlor(14);
    printArrow(content_x , content_y);
    printCorlor(12);
    moveNotice(10,23,"Tips:���ü������¼������Ƽ�ͷ�����ƶ������س�����ѡ��");
    while(1){
        fOut();
        if((user_keyboard = getch())){
            switch(user_keyboard){

                case UP: if(user_choice == up_lim){
                             system("cls");
                             fOut();
                             printCorlor(14);
                             printArrow(content_x , content_y + sub);
                             user_choice = down_lim;
                             content_y = down_lim;
                         }
                         else{
                            system("cls");
                            fOut();
                            printCorlor(14);
                            printArrow(content_x , content_y - gap);
                            content_y -= gap;
                            user_choice -= gap;
                         }
                         break;
             case DOWN: if(user_choice == down_lim){
                            system("cls");
                            fOut();
                            printCorlor(14);
                            printArrow(content_x , content_y - sub);
                            user_choice = up_lim;
                            content_y = up_lim;
                        }
                        else{
                            system("cls");
                            fOut();
                            printCorlor(14);
                            printArrow(content_x , content_y + gap);
                            content_y += gap;
                            user_choice += gap;
                        }
                        break;
            case ENTER: Sleep(400);
                        system("cls");
                        return user_choice;
                        break;
            }
        }
    }
}

void printArrow(int x , int y){//    printArrow()     ������������ͷ,�൱����꣨sorry��������ϣ�
    cursorGoto(x,y);
    printf(">>>");
}

void moveNotice(int x,int y,const char* text){//    moveNotice()     ������ʾ��ͷ�ƶ����÷�
    isCursorActive(0);
    printCorlor(0x02);
    cursorGoto(x,y);
    printf("%s",text);
}

void gameUI(int color){//    gameUI()     Ϊ����̨��ӡ������   ����������ɫ
    int i,j;
    printCorlor(color);
    for(i=0;i<79;i++){//     ��ӡ��һȦС����
        for(j=0;j<=24;j++){
            if(i==0||i==78){
                drawItem(i,j,"��");
            }
            if(j==24){
                drawItem(i,j,"��");
            }
        }
    }
    printCorlor(7);
}

int warningDialog(const char *text , const char *title , const char *opResult){//    warningDialog()     �˳���Ϸ������ʾ
    int result =
    MessageBox(NULL,text,TEXT(title),MB_ICONINFORMATION|MB_OKCANCEL);

        if(result == IDOK){
            printCorlor(7);
            system("cls");
            printf("\n\n%s\n\n\n\n",opResult);
            return 1;
        }
        //else if(result == IDCANCEL){}
        return 0;
}

void funnyThing(){//    funnyThing()     ����ҳ��ӡ��һЩ��Ȥ�Ķ���
    cursorGoto(15,0);
    printf("                   _ooOoo_\n");
    cursorGoto(15,1);
    printf("                  o8888888o\n");
    cursorGoto(15,2);
    printf("                  88\" . \"88\n");
    cursorGoto(15,3);
    printf("                  (| -_- |)\n");
    cursorGoto(15,4);
    printf("                  O\\  =  /O\n");
    cursorGoto(15,5);
    printf("               ____/`---'\\____\n");
    cursorGoto(15,6);
    printf("             .'  \\\\|     |//  `.\n");
    cursorGoto(15,7);
    printf("            /  \\\\|||  :  |||//  \\\n");
    cursorGoto(15,8);
    printf("           /  _||||| -:- |||||-  \\\n");
    cursorGoto(15,9);
    printf("           |   | \\\\\\  -  /// |   |\n");
    cursorGoto(15,10);
    printf("           | \\_|  ''\\---/''  |   |\n");
    cursorGoto(15,11);
    printf("           \\  .-\\__  `-`  ___/-. /\n");
    cursorGoto(15,12);
    printf("         ___`. .'  /--.--\\  `. . __\n");
    cursorGoto(15,13);
    printf("      .\"\" '<  `.___\\_<|>_/___.'  >'\"\".\n");
    cursorGoto(15,14);
    printf("     | | :  `- \\`.;`\\ _ /`;.`/ - ` : | |\n");
    cursorGoto(15,15);
    printf("     \\  \\ `-.   \\_ __\\ /__ _/   .-` /  /\n");
    cursorGoto(15,16);
    printf("======`-.____`-.___\\_____/___.-`____.-'======\n");
    cursorGoto(15,17);
    printf("                   `=---='\n");
    cursorGoto(15,18);
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    cursorGoto(15,19);
    printf("         ���汣��       ����BUG\n");
    cursorGoto(15,23);
    system("pause");

}

void gameBuffer(){//    gameBuffer()    ���� ģ�������Ϸ����Ļ���Ч��
    int i;

    system("cls");
    gameUI(7);
    cursorGoto(7,7);
    printf("____________________________________________________________");
    cursorGoto(6,8);
    printf("||");
    cursorGoto(66,8);
    printf("||");
    cursorGoto(7,9);
    printf("������������������������������������������������������������");
    printCorlor(9);
    cursorGoto(25,10);
    printf("������...���ع��̲��ķ�����");
    cursorGoto(7,8);
    printCorlor(12);
    Sleep(1000);
    for(i = 0; i < 30; i++){
        if(i == 2){
            Sleep(1000);
        }
        if(i > 10 && i < 24){
            Sleep(200);
        }
        if(i > 25) {
            Sleep(1500);
        }
        printf("��");
    }
    Sleep(800);
    printCorlor(9);
    cursorGoto(25,10);
    printf("������ɡ�                 ");
    Sleep(2000);
    printCorlor(7);
    system("cls");
}

void userUI(){//    userUI()     �û���¼����Ĳ�������
    char verify_account[11];
    char verify_pswd[11];
    char verify_question[41];
    char verify_answer[21];
    int break1 = 1;//��������while����־����
    int break2 = 1;
    int break3 = 1;
    /*int i ;
    for(i = 0; i < 10; i ++){
        teacher_mesg.account[i] = ' ';
        teacher_mesg.pswd[i] = ' ';
    }*/
    strcpy(teacher_mesg.account,"");
    strcpy(teacher_mesg.pswd,"");
    while(break1){
        int to_achieve;
        to_achieve = choiceReact(21,5,3,ACCOUNT_IN,_CANCEL,inputAccountFace);
        press_times = 0;
        switch(to_achieve){

        case ACCOUNT_IN: inputAccountFace();
                          goToAccount();
                          break;
          case PSWD_IN : inputAccountFace();
                          goToPswd();
                          break;
              case _OK : if(strcmp(teacher_mesg.account,"")==0){
                             inputAccountFace();
                             cursorGoto(52,5);
                             printCorlor(0x04);
                             printf("���������˺�");
                         }else if(strcmp(teacher_mesg.pswd,"")==0){
                            inputAccountFace();
                            printCorlor(0x04);
                            cursorGoto(52,8);
                            printf("������������");
                         }else{/**һ���ļ������������ж��˺������Ƿ���ȷ**/
                            teacher_file = fopen("Teacher.txt","r");
                            if(teacher_file == NULL){
                                warningDialog("��¼ʧ�ܣ��ļ�����ʧ��","��¼ʧ��","");
                            }else{
                                while((fscanf(teacher_file,"%s %s %s %s\n",verify_account,verify_pswd,verify_question,verify_answer)) != EOF){
                                    if(strcmp(teacher_mesg.account,verify_account) == 0){
                                            break2 = 0;
                                        if(strcmp(teacher_mesg.pswd,verify_pswd) == 0){
                                               // printf("%s\n%s\n%s",verify_account,verify_pswd,teacher_mesg.pswd);
                                                //system("pause");
                                      /**/      teacherOPImplement(verify_account);
                                            cursorGoto(31,5);
                                            printf("��¼�ɹ�");
                                            break3 = 0;
                                            break;
                                        }
                                    }

                                }
                                fclose(teacher_file);
                                if(break2){
                                    warningDialog("���˺Ż�δע��","��¼ʧ��","");
                        /***/            printf("%s\n%s\n%s",verify_account,verify_pswd,teacher_mesg.pswd);
                                    break;
                                }else{
                                    if(break3){
                                        warningDialog("������������¼������","��¼ʧ��","");
                       /***/                 printf("%s\n%s\n%s",verify_account,verify_pswd,teacher_mesg.pswd);
                                        break;
                                    }

                                }

                            }

                             //gameBuffer();
                             break1 = 0;
                         }
                        /*cursorGoto(10,21);
                        printf("%styu",teacher_mesg.account);
                        cursorGoto(10,22);
                        printf("%swer",teacher_mesg.pswd);*/

                         break;
          case _CANCEL: if(warningDialog("��Ҫ������¼��","������¼����","")){
                            break1 = 0;
                        }
                         break;
         case SIGN_UP : creatAccount();
                         break;
     case FORGET_PSWD : findPswd();
                         break;
        }
    }
}

void inputAccountFace(){//    inputAccountFace()     ��ӡ�û���¼����

    printCorlor(14);
    isCursorActive(0);
    //gameUI(14);
    printCorlor(0x02);
    cursorGoto(18,1);
    printf("tips:�˺�Ϊ10λ���֣���������ĸ���������");
    printCorlor(9);
    cursorGoto(24,5);
    printf("�˺ţ�");
    cursorGoto(31,4);
    printf("____________________");
    cursorGoto(30,5);
    printf("|");
    cursorGoto(51,5);
    printf("|");
    cursorGoto(31,6);
    printf("��������������������");
    cursorGoto(24,8);
    printf("���룺");
    cursorGoto(31,7);
    printf("____________________");
    cursorGoto(30,8);
    printf("|");
    cursorGoto(51,8);
    printf("|");
    cursorGoto(31,9);
    printf("��������������������");
    cursorGoto(24,11);
    printf("��¼");
    printCorlor(12);
    cursorGoto(24,14);
    printf("��û���˻��𣬴���һ����");
    cursorGoto(24,17);
    printCorlor(13);
    printf("�������룿");
    printCorlor(7);
    cursorGoto(24,20);
    printf("ȡ��");
    moveNotice(10,23,"Tips:���ü������¼������Ƽ�ͷ�����ƶ������س�����ѡ��");
    saveOrNot(1);
}

void findPswd(){/**�ÿ�ܻ�û��ʵ��**/
    cursorGoto(38,8);
    printf("�ù�����δ����");
    system("pause");
    system("cls");
}

void creatAccount(){//    creatAccount()     ʵ��ע���˺ŵĽӿ�
    int mark = 1;    //��������ѭ���ı�Ǳ���
    strcpy(pswd1,"");  //ÿ�ζ�����ַ�
    strcpy(pswd2,"");
    strcpy(question,"");
    strcpy(answer,"");
    while(mark){
        int reciever;
        printCorlor(7);
        reciever = choiceReact(17,3,3,_INPUT,_NO,creatAccountFace);
        switch(reciever){
            case _INPUT : creatAccountFace();
                          creatImplement(1);
                          break;
         case MAKE_SURE : creatAccountFace();
                          creatImplement(2);
                          break;
         case _QUESTION : creatAccountFace();
                          creatImplement(4);
                          break;
           case _ANSWER : creatAccountFace();
                          creatImplement(5);
                          break;
              case _YES : creatAccountFace();
                          creatImplement(3);
                          /*cursorGoto(10,21);
                          printf("%sqwe %s[[",pswd1,question);
                          cursorGoto(10,22);
                          printf("%syui %s[[",pswd2,answer);*/
                          break;
               case _NO : if(warningDialog("��ȷ��Ҫ����ע������","��������","")){
                             strcpy(pswd1,"");
                             strcpy(pswd2,"");
                             mark = 0;
                         }
                         break;
        }
    }
}

void creatAccountFace(){//    creatAccountFace()     ��ӡһ��ע���˺�ҳ��
    printCorlor(7);
    cursorGoto(18,1);
    printCorlor(12);
    printf("��������Ϊ��ĸ�����ֻ���ͣ��Ҳ�����10λ��");
    printCorlor(7);
    cursorGoto(20,3);
    printf("�������룺");
    cursorGoto(31,2);
    printf("____________________");
    cursorGoto(30,3);
    printf("|");
    cursorGoto(51,3);
    printf("|");
    cursorGoto(31,4);
    printf("��������������������");
    cursorGoto(20,6);
    printf("ȷ�����룺");
    cursorGoto(31,5);
    printf("____________________");
    cursorGoto(30,6);
    printf("|");
    cursorGoto(51,6);
    printf("|");
    cursorGoto(31,7);
    printf("��������������������");
    repeatPrintPswd();
    cursorGoto(20,9);
    printf("�����ܱ���");
    cursorGoto(31,8);
    printf("________________________________");
    cursorGoto(30,9);
    printf("|");
    cursorGoto(63,9);
    printf("|");
    cursorGoto(31,10);
    printf("��������������������������������");
    cursorGoto(20,12);
    printf("���ô𰸣�");
    cursorGoto(31,11);
    printf("____________________");
    cursorGoto(30,12);
    printf("|");
    cursorGoto(51,12);
    printf("|");
    cursorGoto(31,13);
    printf("��������������������");
    cursorGoto(20,15);
    printf("ȷ��");
    cursorGoto(20,18);
    printf("ȡ��");
    printCorlor(0x02);
    cursorGoto(28,15);
    printf("Tips:");
    cursorGoto(28,17);
    printf("�ܱ�����ʹ𰸾����������Ӣ�ġ�");
    printCorlor(7);
    cursorGoto(28,19);
    printf("���磺what's your QQ number? : 177****225");
    moveNotice(10,23,"Tips:���ü������¼������Ƽ�ͷ�����ƶ������س�����ѡ��");
}

void saveOrNot(int is_not){//    saveOrNot()     �Ƿ���ʾ�˺�����
    int i = 0;
    if(is_not){
        cursorGoto(31,5);
        printf("%s",teacher_mesg.account);
        if(*teacher_mesg.pswd != ' '){
            cursorGoto(31,8);
            for(;i < press_times; i ++){
                printf("*");
            }
            cursorGoto(41,5);
            printf("          ");
        }
    }
}

void goToAccount(){//    goToAccount()     �����˺Žӿ�ʵ�ֺ���
    int i = 0;
    int j = 31;
    char str;
    isCursorActive(1);
    strcpy(teacher_mesg.account,"");
    cursorGoto(31,5);
    printf("                    ");
    while(1){
        if(i == 10){
            break;
        }
        cursorGoto(j,5);
        str = getch();
        if( str >= '0' && str <= '9'){
            teacher_mesg.account[i] = str;
            printf("%c",teacher_mesg.account[i]);
            i ++;
            j ++;
        }
        else{
            cursorGoto(52,5);
            printCorlor(0x04);
            printf("����������Ч����");
            printCorlor(0x02);
        }
    }
}

void goToPswd(){//    goToPswd()    ��������ӿ�ʵ�ֺ���
    int i = 0;
    int j = 31;
    char str;
    press_times = 0;
    isCursorActive(1);
    strcpy(teacher_mesg.pswd,"");
    cursorGoto(31,8);
    printf("                    ");
    while(1){
        if(i == 10){
            break;
        }
        cursorGoto(j,8);
        str = getch();
        if(str == ENTER){
            //strcpy(teacher_mesg.account,temp);
            /*strcpy(temp,teacher_mesg.account);
            int k = 0;
            for(;k < 10; k ++){
                teacher_mesg.account[k] = temp[k];
            }*/
            break;
        }
        if((str>='0' && str<='9') || ((str>='A' && str<='Z') || (str>='a' && str<='z'))){
            teacher_mesg.pswd[i] = str;
            printf("%c",teacher_mesg.pswd[i]);
            i ++;
            j ++;
            ++ press_times;
        }
        else{
            cursorGoto(52,8);
            printCorlor(0x04);
            printf("����������Ч����");
            printCorlor(0x02);
        }
    }
}

void creatImplement(int number){//    creatPswd()    ע��ʱ��������ӿ�
    int i = 0;
    int j = 31;
    char str;
    //strcpy(pswd1,"");  //ÿ�ζ�����ַ�
    //strcpy(pswd2,"");
    isCursorActive(1);
    if(number == 1){
        cursorGoto(31,3);
        //strcpy(pswd1,"");/**�ַ��ظ���ֵ����bug**/
        //pswd1[2] = '\0';
        clearList(pswd1,11);
        printf("                    ");
        while(1){
            if(i == 10){
                if((strcmp(pswd2,"") != 0) && (strcmp(pswd1,pswd2) != 0)){
                    cursorGoto(52,3);
                    printCorlor(0x04);
                    printf("���������벻һ��");
                    printCorlor(0x02);
                }
                break;
            }
            cursorGoto(j,3);
            str = getch();
            if(str == ENTER){
                if((strcmp(pswd2,"") != 0) && (strcmp(pswd1,pswd2) != 0)){
                    cursorGoto(52,3);
                    printCorlor(0x04);
                    printf("���������벻һ��");
                    printCorlor(0x02);
                }
                break;
            }
            if((str>='0' && str<='9') || ((str>='A' && str<='Z') || (str>='a' && str<='z'))){
                *(pswd1 + i) = str;
                printf("%c",*(pswd1 + i));
                i ++;
                j ++;
            }
            else{
                cursorGoto(52,3);
                printCorlor(0x04);
                printf("����������Ч����");
                printCorlor(0x02);
            }
        }
    }
    if(number == 2){
        cursorGoto(31,6);
        clearList(pswd2,11);
        printf("                    ");
        while(1){
            if(i == 10){
                if(strcmp(pswd1,"") == 0){
                    cursorGoto(52,3);
                    printCorlor(0x04);
                    printf("!�����Ϊ��");
                    printCorlor(0x02);
                }else if(strcmp(pswd2,pswd1) != 0){
                    cursorGoto(52,6);
                    printCorlor(0x04);
                    printf("���������벻һ��");
                    printCorlor(0x02);
                }
                break;
            }
            cursorGoto(j,6);
            str = getch();
            if(str == ENTER){
                if(strcmp(pswd1,"") == 0){
                    cursorGoto(52,3);
                    printf("!�����Ϊ��");
                }else if(strcmp(pswd2,pswd1) != 0){
                    cursorGoto(52,6);
                    printCorlor(0x04);
                    printf("���������벻һ��");
                    printCorlor(0x02);
                }
                break;
            }
            if((str>='0' && str<='9') || ((str>='A' && str<='Z') || (str>='a' && str<='z'))){
                *(pswd2 + i) = str;
                printf("%c",*(pswd2 + i));
                i ++;
                j ++;
            }
            else{
                cursorGoto(52,6);
                printCorlor(0x04);
                printf("����������Ч����");
                printCorlor(0x02);
            }
        }
    }
    if(number == 3){
        int isTrue = 1;
        int times = 0;
        char temp_account[11];//�����ȡ0~9����ʮ��
        char file_account[11];//���ļ��ж�������ʱ�˺�
        char file_pswd[11];//���ļ��ж�ȡ����ʱ����
        char file_question[21];
        char file_answer[11];
        if(strcmp(pswd1,"")==0){
            isTrue = 0;
            cursorGoto(52,3);
            printCorlor(0X04);
            printf("!����Ϊ��");
            printCorlor(0X02);
        }
        if(strcmp(pswd2,"")==0){
            isTrue = 0;
            cursorGoto(52,6);
            printCorlor(0X04);
            printf("!����Ϊ��");
            printCorlor(0X02);
        }
        if((strcmp(question,"")==0) != (strcmp(answer,"")==0)){
            isTrue = 0;
            cursorGoto(64,9);
            printCorlor(0X04);
            printf("!����𰸲�ƥ��");
            cursorGoto(52,12);
            printf("!����𰸲�ƥ��");
            printCorlor(0X02);
        }
        if(isTrue){
            teacher_file = fopen("Teacher.txt","r+");
            if(teacher_file == NULL){
                warningDialog("ע��ʧ�ܣ��ļ�����ʧ��","ע��ʧ��","");
                clearList(pswd1,11);
                clearList(pswd2,11);
                clearList(question,41);
                clearList(answer,21);
            }else{
                int temp_mark = 1;
                while(temp_mark){
                    for(; times < 10; times ++){
                        temp_account[times] = rand()%9 + 49;
                    }
                    temp_account[10] = '\0';
                    temp_mark = 0;
                    while(fscanf(teacher_file,"%s %s %s %s\n",file_account,file_pswd,file_question,file_answer) != EOF){
                        if(strcmp(file_account,temp_account)==0){
                            temp_mark = 1;
                            break;
                        }
                    }
                }
                rewind(teacher_file);
                fseek(teacher_file,0,SEEK_END);
                fprintf(teacher_file,"%s %s %s %s\n",temp_account,pswd1,question,answer);
                clearList(pswd1,11);
                clearList(pswd2,11);
                clearList(question,41);
                clearList(answer,21);
                char temp_list[35] = "Account:";
                int de = 0;
                int now = 8;
                for(;de < 10,now < 19; de ++,now ++){
                    temp_list[now] = temp_account[de];
                }
                warningDialog(temp_list,"ע��ɹ���������˺�","");
            }
            fclose(teacher_file);
        }
    }
    if(number == 4){
        clearList(question,21);
        cursorGoto(31,9);
        printf("                ");
        cursorGoto(31,9);
        gets(question);
    }
    if(number == 5){
        clearList(answer,11);
        cursorGoto(31,12);
        printf("          ");
        cursorGoto(31,12);
        gets(answer);
        if(strcmp(question,"") == 0){
            cursorGoto(52,9);
            printCorlor(0X04);
            printf("!����Ϊ��");
            printCorlor(0X02);
        }
    }
}

void repeatPrintPswd(){//    repeatPrintPswd()    ���û�ѡ��ʱ�ظ���ӡ����
    cursorGoto(31,3);
    printf("%s",pswd1);
    cursorGoto(31,6);
    printf("%s",pswd2);
    cursorGoto(31,9);
    printf("%s",question);
    cursorGoto(31,12);
    printf("%s",answer);
}

void clearList(char *list,int index){//    deleteList(char *,int)    �����鸳ֵΪ�մ�
    int k = 0;
    for(;k < index; k ++){
        *(list + k) = '\0';
    }
}

/////////////////////////////��¼����ز�������

void teacherOpUI(){//    teacherOpUI()    ��ʦ�˵�¼�����������
    isCursorActive(0);
    gameUI(12);
    printCorlor(9);
    cursorGoto(14,1);
    printf("                �X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[ ");
    cursorGoto(14,2);
    printf("################�U��ʦ�˲���ҳ��U ###############");
    cursorGoto(14,3);
    printf("                �^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a ");
    cursorGoto(35,7);
    printf("�鿴�ɼ�");
    cursorGoto(35,9);
    printf("���ӳɼ�");
    cursorGoto(35,11);
    printf("�޸ĳɼ�");
    cursorGoto(35,13);
    printf("ɾ���ɼ�");
    cursorGoto(35,15);
    printf("�޸�����");
    cursorGoto(35,17);
    printf("�޸�ѧ������");
    cursorGoto(35,19);
    printf("�˳�");
    moveNotice(10,23,"Tips:���ü������¼������Ƽ�ͷ�����ƶ������س�����ѡ��");
    cursorGoto(10,22);
    //system("pause");
}

void teacherOPImplement(char *class_id){//    teacherOpImplement()    ��ʦ��������ʵ�ֺ���
    char teacher_account[11];
    strcpy(teacher_account,class_id);
    char creat_class[15];
    Node *temp_head = NULL;
    int times = 0;
    for(; times < 10; times ++){
        creat_class[times] = class_id[times];
    }
    creat_class[10] = '.';
    creat_class[11] = 't';
    creat_class[12] = 'x';
    creat_class[13] = 't';
    creat_class[14] = '\0';
    FILE *class_vertify = NULL;
    //class_vertify = fopen(creat_class,"r");
    /*cursorGoto(2,0);
    printf("%s",creat_class);*/
    /*if(class_vertify == NULL){
        class_vertify = fopen(creat_class,"w");
    }
    fclose(class_vertify);*/
    temp_head = readAndWrite(temp_head,creat_class);
    temp_head = listSort(temp_head,creat_class);
    temp_head = writeAndRead(temp_head,creat_class);

    while(1){
        int i;
        teacherOpUI();
        i = choiceReact(32,7,2,VIEW,LEAVE_TEACH_SIDE,teacherOpUI);//ע�⺯��ָ����û��()
        switch(i){
          case 7 :      system("cls");
                        printCorlor(7);
                        system("pause");
                        printList(temp_head);
                        //deleteList(temp_head);
                        //cursorGoto(45,7);
                        //printf("7�鿴�ɼ�");
                        system("pause");
                        system("cls");
                        break;

        case 9 :        //cursorGoto(45,9);
                        //printf("9���ӳɼ�");
                        system("cls");
                        insertNode(temp_head,creat_class);
 /**free������**/       //deleteList(temp_head);
                        system("pause");
                        system("cls");
                        break;

     case 11 :          modifyStudentInfo(temp_head,creat_class);
                        //deleteList(temp_head);
                        system("pause");
                        system("cls");
                        break;

          case 13 :    //cursorGoto(45,13);
                        //printf("13ɾ���ɼ�");
                        temp_head = deleteNode(temp_head,creat_class);
                        deleteList(temp_head);
                        system("pause");
                        system("cls");
                        break;
            case 15 :   cursorGoto(45,15);
                        printf("15�޸�����");
                        system("pause");
                        break;
            case 17 :cursorGoto(45,17);
                     printf("17�޸�ѧ������");
                     system("pause");
                     break;
            case 19 :    if(warningDialog("��ȷ��Ҫ�˳���ʦ����","�˳�����","�����˳�ϵͳ")){
                                exit(1);
                            }
                        break;
        }
    }
    deleteList(temp_head);
}

/////////////////////////////////////////////////������غ���

Node* creatList(const char* file){//    creatList()     ��������
    Node *head = NULL;                        //ͷ�ڵ�
    Node *end = NULL;                  //����ָ�����һ������ǰ�����ģ��ڵ�
    Node *current = NULL;              //ָ��ÿһ���´����Ľڵ�
    head = (Node*)malloc(sizeof(Node));
    int temp_id;
    char temp_pswd[11];
    char temp_name[21];
    int temp_C;
    int temp_M;
    int temp_E;

    if(head == NULL){
        printf("can't open up space\n");
    }else{
        end = head;                      //����β�ڵ�ָ��ͷ�ڵ�
        if((student_file = fopen(file,"r")) != NULL){
            while((fscanf(student_file,"%d %s %s %d %d %d\n",&temp_id,temp_pswd,temp_name,&temp_C,&temp_M,&temp_E)) != EOF){
                current = (Node*)malloc(sizeof(Node));
                //gets(current->stu.name);ʹ��gets�����������س�
                /*scanf("%s",current->stu.name);
                scanf("%d",&current->stu.id);
                scanf("%d",&current->stu.c_grade);
                scanf("%d",&current->stu.math_grade);
                scanf("%d",&current->stu.english_grade);*/
                current->stu.id = temp_id;
                strcpy(current->stu.pswd,temp_pswd);
                strcpy(current->stu.name,temp_name);
                current->stu.c_grade = temp_C;
                current->stu.math_grade = temp_M;
                current->stu.english_grade = temp_E;
                end->next = current;               //�������ڲ����Ľڵ�nextָ���´����Ľڵ�
                current->next = NULL;              //�´�����nextָ�븳ֵΪ��
                end = current;                     //β�ڵ㱻��ֵΪ�´����ģ��½ڵ㴴�����
            }

            fclose(student_file);
        }else{
                printf("error");
                exit(-1);
            }

    }
    return head;
}

void printList(Node *head){//    printList()     ��ӡ����
    Node *this_node = NULL;
    Node *this_head = head;          //��������ͷ�ڵ��ָ��
    this_node = this_head;
    this_node = this_node->next;             //ֱ�Ӹ�ֵΪnext�����ӡ
    //printf("\n\n");
    //printf("jinru");
    if(this_head != NULL){
            printf("  ID         ����   C����  ��ѧ  Ӣ��  �ܳɼ�\n");
        while(this_node != NULL){
            printCorlor(0X02);
            printf("%d  ",this_node->stu.id);
            printCorlor(7);
            //printf("%s  ",this_node->stu.pswd);
            printf("%s   ",this_node->stu.name);
            printf("%d     ",this_node->stu.c_grade);
            printf("%d    ",this_node->stu.math_grade);
            printf("%d    ",this_node->stu.english_grade);
            int score = this_node->stu.c_grade + this_node->stu.math_grade + this_node->stu.english_grade;
            printf("%d\n",score);
            this_node = this_node->next;
        }
    }else{
        printf("head == NULL");
    }
}

void deleteList(Node *head){//    deleteList()     �ͷ����������ڴ棬ָ���ʽ��ΪNULL
    Node *deleteP = NULL;                     //ԭ��ʹ��������һ��
    Node *currentP = NULL;
    currentP = head;

    while(currentP != NULL){
        deleteP = currentP;
        currentP = currentP->next;
        free(deleteP);
        deleteP = NULL;           /**ǧ��ע�⸳ΪNULL����ֹϵͳ�ٴε���Ұָ����ɵĲ����ֲ��Ĵ���**/
    }
}

/**�����Ǳ����ɼ��ĺ���**/
Node* searchStudentNode(Node* head , int id){//    searchStudentNode()    ����һ��ָ����id��Ӧ�ڵ�
    Node *now = head;
    now = now->next;
    Node *the_node = NULL;
    while(now!=NULL){
        if(now->stu.id == id){
           the_node = now;
           break;
        }
        now = now->next;
    }
    return the_node;
}

Node* modifyStudentInfo(Node* head ,const char *file_name){//    nodifyStudentInfo()    ���������ֱ���ͷָ�룬ѧ��id��ѧ����ѧ�ɼ�
    Node *this_node = head;
    Node *now = this_node;
    Node *receive = NULL;
    int mark = 1;
    int temp_id = 0;
    int temp_c_grade = 0;
    int temp_m_grade = 0;
    int temp_e_grade = 0;
    char temp_name[21];
    char temp_pswd[11];
    printf("����������Ҫ�޸ĵ�ѧ����id��\n");
    isCursorActive(1);
    scanf("%d",&temp_id);
    receive = searchStudentNode(this_node,temp_id);
    if(receive != NULL){
        printf("����������������Ҫ�޸ĵ�ѧ�����룬���֣�C���ԡ���ѧ��Ӣ��ɼ���\n");
        scanf("%s",temp_pswd);
        scanf("%s",temp_name);
        scanf("%d",&temp_c_grade);
        scanf("%d",&temp_m_grade);
        scanf("%d",&temp_e_grade);
        isCursorActive(0);
        receive->stu.c_grade = temp_c_grade;
        receive->stu.math_grade = temp_m_grade;
        receive->stu.english_grade = temp_e_grade;
        strcpy(receive->stu.pswd,temp_pswd);
        strcpy(receive->stu.name,temp_name);
    }else{
        mark = 0;
        isCursorActive(0);
        printf("��id��δ��ӣ���������Ƿ���ȷ\n");
    }
    if(mark){
        writeAndRead(this_node,file_name);
        this_node = listSort(this_node,file_name);
        readAndWrite(this_node,file_name);
        now = now->next;
        printCorlor(7);
        while(now != NULL){
            if(now->stu.id == temp_id){
                printCorlor(0X04);
            }
            printf("%d %s %s %d %d %d\n",now->stu.id,now->stu.pswd,now->stu.name,now->stu.c_grade,now->stu.math_grade,now->stu.english_grade);
            now = now->next;
        }
    }
    return this_node;
}
/***δ���***/
Node* modifyTeacherPswd( char *account){//���������ֱ���ͷָ�룬ѧ��id��ѧ��C���Գɼ�
    char temp_pswd[11];
    char temp_account[11];
    char vertify_pswd[11];
    char useless_ques[41];
    char useless_answ[21];
    tNode temp_head = NULL;
    temp_head = (tNode*)malloc(sizeof(tNode));/**ѭ�����붯̬�ڴ棬������ʦ�������и�д**/
    tNode now = temp_head;
    isCursorActive(1);
    printf("���������ľ����룺\n");
    scanf("%s",temp_pswd);
    FILE *temp_file = NULL;
    temp_file = fopen("Teacher.txt","r+");
    if(temp_file == NULL){
        printf("Modify_Pswd_File_Error\n");
    }else{
        while(fscanf(temp_file,"%s %s %s %s\n",temp_account,vertify_pswd,useless_ques,useless_answ) != EOF){

        }
    }
}

Node* deleteNode(Node* head, const char* file_name){//    deleteNode()    ɾ��ָ��id��ѧ���ڵ�
    Node *now = head;
    Node *this_head = head;
    Node *temp = NULL;
    int mark = 0;
    int temp_id = 0;
    isCursorActive(1);
    printf("�루����������Ҫɾ��ѧ����id��\n");
    scanf("%d",&temp_id);

    while(now->next != NULL){
        if(now->next->stu.id == temp_id){
            now->next = now->next->next;
            free(now->next);
            now->next == NULL;
            mark = 1;
        }
        now = now->next;
    }
    if(mark){
        writeAndRead(this_head,file_name);
        printf("ɾ�����\n");
    }else{
        printf("δ�ҵ���ѧ��\n");
    }

    return this_head;
}

void insertNode(Node* head , const char *file_name ){//    ������ͷ�ڵ��Ҫ�����½ڵ����ĸ��ڵ���(ͷ�ڵ㻹δ�����ڴ�)
    Node* current = NULL;                             //���뵽ͷ�ڵ�֮���ٵ�������������
    Node* foreNode = NULL;
    Node* newNode = NULL;
    Node *insert_node = NULL;
    Node *temp_head = head;
    temp_head = temp_head->next;
    insert_node = (Node*)malloc(sizeof(Node));
    int mark = 1;
    isCursorActive(1);
    printCorlor(7);
    printf("��������Ҫ�����ѧ����Ϣ������ID ��ʼ���� ���� C���� ��ѧ Ӣ��ɼ������룺\n");
    printCorlor(0X02);
    scanf("%d",&insert_node->stu.id);
    scanf("%s",insert_node->stu.pswd);
    scanf("%s",insert_node->stu.name);
    scanf("%d",&insert_node->stu.c_grade);
    scanf("%d",&insert_node->stu.math_grade);
    scanf("%d",&insert_node->stu.english_grade);
    isCursorActive(0);
    //int insert_score = insert_node->stu.c_grade + insert_node->stu.english_grade + insert_node->stu.math_grade;
    //int score = 0;
    while(temp_head != NULL){
        if(insert_node->stu.id == head->stu.id){
            mark = 0;
            //printCorlor(12);
        }
        //printf("%d %s\n",temp_head->stu.id,temp_head->stu.name);
        temp_head = temp_head->next;
        //printCorlor(7);
    }
    if(mark){                         //�ж��Ƿ������ѧ���Ѿ�����
        Node *temp_node = NULL;
        temp_node = head->next;
        head->next = insert_node;
        insert_node->next = temp_node;
        head = writeAndRead(head,file_name);
    }else{
        printf("�����ѧ���Ѵ���");
    }
    listSort(head,file_name);
    head = readAndWrite(head,file_name);
    Node *now = head;
    now = now->next;
    printCorlor(12);
    printf("------------��ӡ------------\n");
    printCorlor(7);
    while(now != NULL){
        if(now->stu.id == insert_node->stu.id){
            printCorlor(0X04);
        }
        printf("%d %s %d %d %d\n",now->stu.id,now->stu.name,now->stu.c_grade,now->stu.math_grade,now->stu.english_grade);
        printCorlor(7);
        now = now->next;
    }
}

////////////////////////////////////////////////////�ļ���д��������

void myExchange(Node *exchanged_node,Node *swapped_node){//    myExchange()    �������ڵ�������򽻻�
    int num = 0;
    char pswd[11];
    char name[20];
    /////////////////////
    if((exchanged_node == NULL) && (swapped_node == NULL)){//��������ڵ㶼Ϊ���򱨴�
        printf("Exchange_NullPointer_Error\n");
        exit(-1);
    }else{
        num = exchanged_node->stu.english_grade;
        exchanged_node->stu.english_grade = swapped_node->stu.english_grade;
        swapped_node->stu.english_grade = num;
        num = exchanged_node->stu.math_grade;
        exchanged_node->stu.math_grade = swapped_node->stu.math_grade;
        swapped_node->stu.math_grade = num;
        num = exchanged_node->stu.c_grade;
        exchanged_node->stu.c_grade = swapped_node->stu.c_grade;
        swapped_node->stu.c_grade = num;
        num = exchanged_node->stu.id;
        exchanged_node->stu.id = swapped_node->stu.id;
        swapped_node->stu.id = num;
        strcpy(name,exchanged_node->stu.name);
        strcpy(exchanged_node->stu.name,swapped_node->stu.name);
        strcpy(swapped_node->stu.name,name);
        strcpy(pswd,exchanged_node->stu.pswd);
        strcpy(exchanged_node->stu.pswd,swapped_node->stu.pswd);
        strcpy(swapped_node->stu.pswd,pswd);
    }

}

Node* listSort(Node *head,const char *grade_file_name){//    listSort()    ������Ϊ���彫�ļ��е���Ϣ�������ݴ�С����
    FILE *file = NULL;
    Node *this_head = head;
    Node *temp_min = NULL;
    this_head = readAndWrite(this_head,grade_file_name);
    Node *now = this_head->next;
    //printList(this_head);
    //printf("------------�ֽ���----------\n");
    int score = 0;
    int next_score = 0;
    while(now->next != NULL){                      //��ѡ�������㷨���ڶ�������õ���getMinNode������
        temp_min = getMinNode(now);
        score = temp_min->stu.c_grade + temp_min->stu.math_grade + temp_min->stu.english_grade;
        next_score = now->stu.c_grade + now->stu.math_grade + now->stu.english_grade;
        if(score != next_score){
            myExchange(temp_min,now);
        }
        now = now->next;
    }
    //printList(this_head);
    this_head = writeAndRead(this_head,grade_file_name);
    fclose(file);
    return this_head;
}

Node* getMinNode(Node* head){//    getMinNode()    ����������ָ��ͷ�ڵ���������С���ݵĽڵ�
    Node *minp = head;
    Node *p = head->next;
    int score = 0;
    int next_score = 0;
    while(p != NULL){
        score = minp->stu.c_grade + minp->stu.english_grade + minp->stu.math_grade;
        next_score = p->stu.c_grade + p->stu.english_grade + p->stu.math_grade;
        if(score < next_score){
            minp = p;
        }
        p = p->next;
    }
    return minp;
}

Node* readAndWrite(Node *head,const char *file_name){//    readAndWrite()    ���������ָ���ļ���
    FILE *file = NULL;
    Node *this_head = head;
    Node *temp = NULL;
    this_head = (Node*)malloc(sizeof(Node));
    Node *now = this_head;
    file = fopen(file_name,"r");
    if(this_head == NULL){
        printf("Read_Write_NullPointer_Error\n");
        exit(-1);
    }else{
        int id = 0;
        int c_gra = 0;
        int m_gra = 0;
        int e_gra = 0;
        char name[20];
        char pswd[11];
        while((fscanf(file,"%d %s %s %d %d %d\n",&id,pswd,name,&c_gra,&m_gra,&e_gra)) != EOF){
            temp = (Node*)malloc(sizeof(Node));
            temp->next = NULL;
            now->next = temp;
            now = temp;
            now->stu.id = id;
            strcpy(now->stu.pswd,pswd);
            strcpy(now->stu.name,name);
            now->stu.c_grade = c_gra;
            now->stu.math_grade = m_gra;
            now->stu.english_grade = e_gra;
        }
    }
    fclose(file);
    return this_head;
}

Node* writeAndRead(Node *head,const char *file_name){// writeAndRead()    ������洢��ָ�����ļ���
    Node *this_head = head;
    FILE *file = NULL;
    Node *now = this_head->next;
    file = fopen(file_name,"w");
    int id = 0;
    int c_gra = 0;
    int m_gra = 0;
    int e_gra = 0;
    char name[20];
    char pswd[11];
    if(this_head->next == NULL){
        printf("Write_Read_NullPointer_Error\n");
        exit(-1);
    }else{
        while(now != NULL){
            id = now->stu.id;
            strcpy(pswd,now->stu.pswd);
            strcpy(name,now->stu.name);
            c_gra = now->stu.c_grade;
            m_gra = now->stu.math_grade;
            e_gra = now->stu.english_grade;
            fprintf(file,"%d %s %s %d %d %d\n",id,pswd,name,c_gra,m_gra,e_gra);
            now = now->next;
       }
    }
    fclose(file);
    return this_head;
}
