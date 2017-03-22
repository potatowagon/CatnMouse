#include<stdio.h>
#include<stdbool.h>
#include<string.h>

#define max 90
#define maxL 79
#define maxH 53
typedef struct
{
   int r;
   int c;
} object;

bool outsidebox(int row, int col, int L, int H);
void menu(char h[], char e[], int *L, int *H, char board[][max]);
void getBoard(int *L, int*H);
void setBoard(int *L, int *H, char board[][max]);
void printb(char board[][max], int H);
void setPosm(object *m, char board[][max], int L, int H);
void setPosc(object *m, char board[][max], int L, int H);
void setPosC(object *m, char board[][max], int L, int H);
void movemouse(object *m, char dir[], char board[][max], int *cheese, int L, int H);
void movec(object *c, object *m, char board[][max]);
void moveC(object *C, object *m, char board[][max], int L, int H);
bool mEaten(object m, object c, object C);
void getHole(object *hT, object *hB, char  board[][max], int H);
bool mHoleT(object hT, object m);
bool mHoleB(object hB, object m);


int main(void)
{
   char board[max][max]=
   {
      {"-----------------\0"},/* c=17,r=9*/
      {"|*c            *|\0"},
      {"|              0|\0"},
      {"|               |\0"},
      {"|       m       |\0"},
      {"|               |\0"},
      {"|0              |\0"},
      {"|*            C*|\0"},
      {"-----------------\0"},
   }; 

   char dir[2];
   char e[2];
   object m, c ,C, hT, hB;
   int k, i;
   int cheese=0;
   char h[1];
   int L=17, H=9;
   char t;

   menu(h, e, &L, &H, board);

   printf("\nUse 'W' 'A' 'S' 'D' to move mouse\n");

   printb(board, H);

   for(k=0;k>-1;k++)
   {
      getHole(&hT, &hB, board, H);
      board[hT.r][hT.c]='0';
      board[hB.r][hB.c]='0';

      printf("\nMove mouse:");
      /* t='0';
         while(t!='w'&& t!='a'&& t!='s' && t!='d')
         {
         scanf("%c", &t);

         }
         dir[0]=t;*/

      scanf("%c", &dir[0]);
      scanf("%c", &e[0]);

      if(dir[0]=='\n')
      {
         t=e[0];
         e[0]=dir[0];
         dir[0]=t;
      }

      setPosm(&m, board, L, H);
      setPosc(&c, board, L, H);
      setPosC(&C, board, L, H);
      movemouse(&m, dir, board, &cheese, L, H);
      setPosm(&m, board, L, H);

      movec(&c, &m, board);
      setPosc(&c, board, L, H);
      moveC(&C, &m, board, L, H);
      setPosC(&C, board, L, H);

      if (mHoleT(hT, m))
      {
         m.r=hB.r;
         m.c=hB.c;
         board[hT.r][hT.c]='0';
         board[m.r][m.c]='m';
         /* printf("\nm.r %d\nm.c %d", m.c, m.c);*/
      }

      else 
      { 
         if (mHoleB(hB, m))
         {
            m.r=hT.r;
            m.c=hT.c;
            board[hB.r][hB.c]='0';
            board[m.r][m.c]='m';
         }
      }


      if (mEaten(m, c, C))
      {
         printb(board, H);
         printf("\nMouse eaten by cat. GAME OVER.\n %d rounds survived\n", k);
         scanf("%c%c", &e[0], &e[0]);


         break;

      }
      if(m.r!=hT.r || m.c!=hT.c)
      {
         board[hT.r][hT.c]='0';
      }

      if(m.r!=hB.r || m.c!=hB.c)
      {

         board[hB.r][hB.c]='0';
      }

      printb(board, H);

      if(cheese>0)
      {
         printf("\n");
         for(i=1; i<=cheese; i++)
         {
            printf("*");
         }
         printf("\n");
      }

      if(cheese==4)
      {
         printf("Mouse collected all the cheese. YOU WIN!!!\n");
         printf("Coded by Sherry. Thanks for playing :)\nCheat code unlocked: Enter 'e' at menu screen to change box dimensions.\n");
         scanf("%c%c", &e[0], &e[0]);
         break;
      }

   }
   return 0;
}

void setBoard(int *L, int *H, char board[][max])
{

   int i, j;

   for(i=0;i<max;i++)
   {
      for(j=0;j<max;j++)
      {
         board[i][j]='\0';
      }
   }

   for(i=0; i<*H; i++)
   {
      for(j=0; j<*L; j++)
      {
         if(i==0 || i==(*H-1))
         {
            board[i][j]='-';
         }
         else
         {
            if(j==0 || j==(*L-1))
            {
               board[i][j]='|';
            }
            else
            {
               board[i][j]=' ';
            }
         }
         board[i][*L]='\0';

      }
   }
   board[1][1]='*';
   board[*H-2][1]='*';
   board[1][*L-2]='*';
   board[*H-2][*L-2]='*';
   board[*H-3][1]='0';
   board[2][*L-2]='0';
   board[*H/2][*L/2]='m';
   board[1][2]='c';
   board[*H-2][*L-3]='C';

   return;
}


void printb(char board[][max], int H)
{
   int i;
   for(i=0; i<H; i++)
   {
      printf("%s\n", board[i]);
   }
   return;
}

void setPosm(object *m, char board[][max], int L, int H)
{
   int i, j;

   for(i=0; i<H; i++)
   {
      for(j=0; j<L; j++)
      {
         if(board[i][j]=='m')
         {
            (*m).r=i;
            (*m).c=j;
            break;
         }
      }
   }
   /*printf("m.r %d", (*m).r);
     printf("m.c %d", (*m).c);*/

   return;
}

void setPosc(object *m, char board[][max], int L, int H)
{
   int i, j;

   for(i=0; i<H; i++)
   {
      for(j=0; j<L; j++)
      {
         if(board[i][j]=='c')
         {
            (*m).r=i;
            (*m).c=j;
            break;
         }
      }
   }
   /*printf("m.r %d", (*m).r);
     printf("m.c %d", (*m).c);*/

   return;
}

void setPosC(object *m, char board[][max], int L, int H)
{
   int i, j;

   for(i=0; i<H-1; i++)
   {
      for(j=0; j<L-1; j++)
      {
         if(board[i][j]=='C')
         {
            (*m).r=i;
            (*m).c=j;
            break;
         }
      }
   }
   /*printf("m.r %d", (*m).r);
     printf("m.c %d", (*m).c);*/

   return;
}

bool outsidebox(int row, int col, int L, int H)
{
  /* printf("L %d,H %d", L, H);*/
   bool ob=false;
   if (row==H-1 || row==0 || col==L-1 || col==0)
   {
      ob=true;
   }
   return ob;
}

void movemouse(object *m, char dir[], char board[][max], int *cheese, int L,int H)
{
   int row=(*m).r, col=(*m).c;

   if(dir[0]== 'w')
   {
      row=(*m).r-1;
   }
   if(dir[0]=='s')
   {
      row=(*m).r+1;
   }
   if(dir[0]=='a')
   {
      col=(*m).c-1;
   }
   if(dir[0]=='d')
   {
      col=(*m).c+1;
   }

   if(board[row][col]=='*')
   {
      *cheese=*cheese+1;
      printf("Yay mouse collected a cheese\n");
   }

   if(!outsidebox(row, col, L, H))
   {
      board[(*m).r][(*m).c]=' ';
      board[row][col]='m';
   }
   return;
}

void movec(object *c, object *m, char board[][max])
{

   int row=(*c).r, col=(*c).c;
   board[(*c).r][(*c).c]=' ';

   if((*c).r > (*m).r)
   {
      row=row-1;
   }

   if((*c).r < (*m).r)
   {
      row=row+1;
   }

   if((*c).c > (*m).c)
   {
      col=col-1;
   }

   if((*c).c < (*m).c)
   {
      col=col+1;
   }

   board[row][col]='c';

   return;
}

void moveC(object *C, object *m, char board[][max],int L,int H)
{


   int row=(*C).r, col=(*C).c;
   board[(*C).r][(*C).c]=' ';

   if((*C).r >= (*m).r)
   {
      row=row-2;

   }
   else
   {

      if((*C).c >= (*m).c)
      {
         col=col-2;

      }
   }


   if((*C).r <= (*m).r)
   {
      row=row+2;
   }

   else
   {
      if((*C).c <= (*m).c)
      {
         col=col+2;
      }
   }
   if(row==H-1)
   {
      row=row-1;
   }
   if(row==0)
   {
      row=row+1;
   }
   if(col==L-1)
   {
      col=col-1;
   }
   if(col==0)
   {
      col=col+1;
   }

   board[row][col]='C';


   return;
}


bool mEaten(object m, object c, object C)
{
   bool eaten=false;
   if(m.c==c.c && m.r==c.r)
   {
      eaten=true;
   }
   if(m.c==C.c && m.r==C.r)
   {
      eaten=true;
   }
   return eaten;
}

void getHole(object *hT, object *hB,  char  board[][max], int H)
{
   int j;
   for(j=0; j<max; j++)
   {
      if(board[2][j]=='0')
      {
         (*hT).r=2;
         (*hT).c=j;
      }
      if(board[H-3][j]=='0')
      {
         (*hB).r=H-3;
         (*hB).c=j;
      }
   }
   /* printf("\n(*hT).r %d, (*hT).c %d", (*hT).r , (*hT).c);
      printf("\n(*hB).r %d, (*hB).c %d", (*hB).r , (*hB).c);*/

   return;
}

bool mHoleT(object hT, object m)
{
   bool drop=false;
   if(hT.r==m.r && hT.c==m.c)
   {
      drop=true;
   }
   return drop;
}

bool mHoleB(object hB, object m)
{
   bool drop=false;
   if(hB.r==m.r && hB.c==m.c)
   {
      drop=true;
   }
   return drop;
}

void getBoard(int *L, int *H)
{
   *L=0;
   *H=0;
   printf("\nEnter length:");
   scanf("%d", &(*L));
   printf("\nEnter height:");
   scanf("%d", &(*H));
   return;
}

void menu(char h[], char e[], int *L, int *H, char board[][max])
{
   char c='0';
   int i=0;

   printf("Enter 'h' for HOW TO PLAY.\nEnter 's' to BEGIN.\n");


   while(c!='h'&& c!='e'&& c!='s')
   {
      scanf("%c", &c);
      if(c!='\n')
      {
         scanf("%c", &e[0]);
      }

      /* printf("%c", c);*/
   }
   h[0]=c;


   /* scanf("%c", &e[0]);*/

   if(h[0]=='h')
   {
      printf("\nHOW TO PLAY\n");
      printb(board, *H);
      printf("m-mouse   c-small cat   C-big  cat\n0-mouse tunnel           * -cheese\n\n");
      printf("You play as mouse.\nMouse can only move up 'W', down 'S', left 'A', right 'D'\nSmall cat is slow but nimble.\nBig cat leaps and pounces, but as a result tends to miss prey that is close by.\n");
      printf("Don't get eaten by the cats. Eat all the cheese to win.\n***GOOD LUCK***\n");
   }
   else
   {

      if(h[0]=='e')
      {
         getBoard(&(*L), &(*H));
        /* printf("%d, %d", *L, *H);*/

         while(*L<5 || *L>maxL || *H<5 || *H>maxH)
         {
            if(i==0)
            {
               printf("\nINVALID INPUT, 'q' to quit setup, 'r' to retry.");
               i=1;
            }
            scanf("%c", &h[0]);
            /* scanf("%c", &e[0])*/

            if(h[0]=='q')
            {
               *L=17;
               *H=9;
               menu(h, e, L, H, board);

            }
            if(h[0]=='r')
            {
               getBoard(&(*L), &(*H));
               i=0;
            }
         }

         setBoard(L, H, board);
      }
      else
      {
         return;
      }
   }
   return;
}











