#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BOOKSIZE 60
#define BOOKNAMESIZE 30 
#define BOOKINDEX 15  

typedef struct book
{
 char book[BOOKNAMESIZE];
 char author[BOOKINDEX];
 char publish[BOOKINDEX];
 char price[BOOKINDEX];
 char year[BOOKINDEX];
 struct book *next;
}BOOK;

enum {add=1, print, del, end};

int Menu(int);
BOOK* Filecreat(BOOK*);
BOOK* Addbook(BOOK*);
void Filewrite(BOOK*);
void Listout(BOOK*);
BOOK* Insertbook(BOOK*, BOOK *);
void Free(BOOK *);
BOOK * Delete(BOOK *);

bookcnt=0;

int main()
{
 int select;

 BOOK *list=0;

 list = Filecreat(list);
 while(1)
 {
  select = Menu(select);

  switch(select)
  {
   case add:
    list = Addbook(list);
    break ;
                                                                                                                                                                                          1,18          Top
case print:
    Listout(list);
    break;

   case del:
    list = Delete(list);
    break;

   case end:
    Filewrite(list);
    Free(list);
    printf("\n프로그램음 종료 합니다.    -감사합니다- \n");
    return 0;

   default:
    printf("\n\n //////////정확한 번호를 선택해주세요//////////\n\n");
    fflush(select);
    break;
  }
 }
 return 0;
}

BOOK* Addbook(BOOK* list)
{
 BOOK temp ;

 printf("\n ★띄어쓰기금지 ★");
 memset(&temp,' ',sizeof(BOOK));
 printf("\n책 이 름  :");
 scanf("%s", temp.book);
 printf("저 자 명  :");
 scanf("%s", temp.author);
 printf("출 판 사  :");
 scanf("%s", temp.publish);
 printf("가    격  :");
 scanf("%s", temp.price);
 printf("\n\n입력이 완료 되었습니다.\n\n");

 temp.next = 0;
 list=Insertbook(&temp,list);

 return list;
                                                                                                                                                                                          86,20-18      22%
}

void Listout(BOOK * list)
{
 int cnt =1;

 printf("\n\n\t#####전체 %d 권의 책#####\n\n", bookcnt);
 while(0 != list)
 {
  printf("\n- NO.% d -\n", cnt);
  printf("책 이 름 : %s \n",  list->book);
  printf("저    자 : %s \n",  list->author);
  printf("출 판 사 : %s \n",  list->publish);
  printf("가    격 : %s \n",  list->price);
  list = list->next;
  cnt++;
 }
}

void Filewrite(BOOK* list)
{
 int outfd ;

 outfd= open("BOOK.DBF", O_WRONLY |O_TRUNC);

 while(list !=0)
 {
  write(outfd, list ,90);
  list = list->next;
 }
 close(outfd);
}

int Menu(int select)
{
 printf("\n***************************\n");
 printf("***  도서관리 프로그램  ***\n");
 printf("***        Made by Jung Uk*\n");
 printf("***************************\n");
 printf("*****    1. 책추가    *****\n");
 printf("*****    2. 출  력    *****\n");
 printf("*****    3. 수  정    *****\n");
 printf("*****    4. 종  료    *****\n");
 printf("***************************\n\n");
 printf("번호를 선택해 주세요(1-4): ");
                                                                                                                                                                                          131,19        45%
fscanf(stdin, "%d" , &select);
 return select;
}

BOOK* Filecreat(BOOK* list)
{
 int outfd;
 BOOK temp;

 outfd = open("BOOK.DBF", O_CREAT , S_IREAD|S_IWRITE);
 while(read(outfd,&temp,90))
 {
  temp.next = NULL ;
  list = Insertbook(&temp, list);
 }
 close(outfd);
 return list;
}

BOOK* Insertbook(BOOK* temp, BOOK *list)
{
 BOOK *add;
 BOOK *current;
 BOOK *follow;
 follow = current = list;

 add = (BOOK*)malloc(sizeof(BOOK));
 *add = *temp;

 bookcnt++;

 while((current !=NULL)&& strcmp(current->book, add->book)<0)
 {
  follow = current;
  current = current->next;
 }
 add->next = current;

 if(current == list)
 {
  list = add;
 }
 else
 {
                                                                                                                                                                                          176,19        69%
 follow->next = add;
 }

 return list;
}
BOOK *Delete(BOOK *list)
{
 BOOK *current;
 BOOK *follow;
 char deletebook[BOOKNAMESIZE]={0};

 current = follow = list;

 printf("\n삭제할 책의 제목을 ◈정확히◈ 넣어주세요 : ");
 scanf("%s", &deletebook);

 if((current !=NULL) && (strcmp(current->book, deletebook)!=0))  {
  follow = current;
  current = current->next;
 }

 if(current == NULL)
 {
  printf("\n찾으시는 제목의 책이 없습니다.\n");
  return list ;
 }
 else
 {
  printf("[ %s ] 의 정보가 삭제 되었습니다. \n", deletebook);
 }

 if(list == current)
 {
  list = current->next;
 }
 else if(current->next == NULL)
 {
  follow->next = NULL;
 }
 else
                                                                                                                                                                                          216,2         89%
{
  follow->next = current->next;
 }
 free(current);

 return list;
}

void Free(BOOK *list)
{
 BOOK *temp;
 while(list !=0)
 {
  temp = list->next;
  free(list);
  list = temp;
 }
}


