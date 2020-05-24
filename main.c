#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>
#include <stdbool.h>
#define num 25

char name[20];
FILE *fp;
FILE *info;
char s[40] ;
int arr[20] = {0}, lvl;
time_t start, end;
double sum_of_score, dif;

typedef struct node
{
    char value[20];
    struct node *next;
} node ;
node * wordsHead;

struct players
{
    char esm[20];
    int lvl;
    double score;
};

struct players pl2;
struct players pl1;

int gotoxy(int x,int y)
{
    COORD coord = {x,y};
    Sleep(200);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

int number_of_files()
{
  DIR *dp;
  int i=0;
  struct dirent *ep;
  dp = opendir ("./");

  if (dp != NULL)
  {
     while (ep = readdir (dp))
     i++;

     closedir (dp);
  }
  return i+10-6-9;
}

int show_menu (void)
{
    HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    int a, i;
    char str[20];
    SetConsoleTextAttribute(hstdout,701);
    system("cls");
    for(i=0 ; i<=5 ; i++)
        printf("%c", 210);
    printf("   ENTER\n");
    Sleep(700);
    for(i=0 ; i<=16; i++)
        printf("%c", 210);
    printf("         YOUR\n");
    Sleep(700);
    for(i=0 ; i<=25 ; i++)
        printf("%c", 210);
    printf("                NAME\n");
    Sleep(700);
    for(i=0 ; i<=35 ; i++)
        printf("%c", 210);
    printf("                      PLEASE   :D  \n");
    scanf("%s", str);
    strcpy(name, str);
    printf("HI %s Ready to play?\n 1: new game\n 2: Resume \n", name);
    scanf("%d", &a);
    system("cls");
    return a;
}

void choose_levels (int x)
{
    switch(x)
    {
    case 1:
         fp = fopen("level-1.txt", "r");
          break;
    case 2:
         fp = fopen("level-2.txt", "r");
          break;
    case 3:
         fp = fopen("level-3.txt", "r");
         break;
    case 4:
         fp = fopen("level-4.txt", "r");
         break;
    case 5:
         fp = fopen("level-5.txt", "r");
         break;
    case 6:
         fp = fopen("level-6.txt", "r");
         break;
    case 7:
         fp = fopen("level-7.txt", "r");
         break;
    case 8:
         fp = fopen("level-8.txt", "r");
         break;
    case 9:
         fp = fopen("level-9.txt", "r");
         break;
    case 10:
         fp = fopen("level-10.txt", "r");
         break;
        }
    if(x < 1 || x > number_of_files() )
    {
            printf("this level is not available");
        exit(0);
    }
}

int number_of_words()
{
    int counter=0 ;
    char c;
    while((c=fgetc(fp)) != EOF)
        {
        if(c ==' ')
            counter++;
        }
        rewind(fp);
    return counter;
}

int strup( char word[])
{
    int k=0 , i;
    for(i=0 ; word[i] != '\0'; i++)
        {
       if(word[i]== toupper( word[i]))
            k++;
        }
        if( k == i)
            return 0;
    return 1;
}
/*
bool is_there(int random, int w)
{
	int i;
	for(i=0; i<w ; i++)
	{
		if (random == arr[i])
		{
			return false;
		}
	}
	return true;
}
/*
void randomize (int randsize)
{
	srand(time(0));
	int i,random ;
	for(i=0 ; i<randsize ;)
	{
		random = rand() % randsize + 1;
		if(is_there (random , randsize))
		{
			arr[i] = random;
			i++;
		}
	}
}*/
int how_to_score()
{
    int q;
    printf("which way do you want me to score you?( 1 , 2 )\n");
    scanf("%d", &q);
        return q;
}

double score_of_word_one (int huruf, int falseguess, double dif )
{
    double score;
    score= (double)(huruf*3 - falseguess) / dif;
    if( score < 0 )
        score = 0;
    return score;
}

double score_of_word_two (int huruf, int falseguess, double dif )
{
    double score;
    if( huruf < 3 )
        score= (double)(huruf*3 - falseguess*6)/ dif;
    else if((huruf >3) && (huruf < 6))
        score= (double)(huruf*6 - falseguess*3)/ dif;
    else
        score= (double)(huruf*9 - falseguess)/ dif;
    if( score < 0 )
        score = 0;
    return score;
}

void gameover(double dif, int lvl)
{
    int k ;
    for(k=0 ; k <= 4 ; k++)
    {
        if((lvl == 10 ) || (lvl == (2*k +1) ))
        {
            if (dif > 25)
            {
                system("cls");
                printf(" GAME IS OVER ");
                exit(0);
            }
        }
        else if( lvl == (2*k) )
        {
            if( dif > 12)
            {
                 system("cls");
                 printf(" GAME IS OVER ");
                 exit(0);
            }
        }
    }
}

void main_game()
{
                            HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    int huruf , fal=0 , m=0;
    double dif;
    struct node *current;
    wordsHead = (node* ) malloc(sizeof(node));
    strcpy(wordsHead->value , "NULL");
    wordsHead->next = NULL;
    current = wordsHead;
    int counter= number_of_words(fp), w, i;
    int random, x=1, y=1;
    int q = how_to_score();
    while( !feof(fp) )
    {
        node* newNode = (node* )malloc(sizeof(node));
        fscanf(fp , "%s " , s);
        strcpy(newNode->value , s);
        newNode->next = NULL;
        current->next = newNode;
        current = current->next;
    }
    rewind(fp);
    srand(time(0));
    w = counter;
   while(w > 0)
   {
       char alaki[30];
       int alaki2 =0;
       node *previous;
       current = wordsHead->next;
       previous = wordsHead;
       random = rand()%w;
      while(alaki2 < random)
      {
          previous = current ;
          current= current->next ;
          alaki2 ++ ;
      }
    strcpy(s, current->value);
    double d1=0 ;
    for( huruf=0 ;  s[huruf] != '\0' ; huruf++);
    //system("cls");                                // comments in this function are for the bonus parts
    printf("%s", s);
    printf("\n");
    //system("cls");
    time (&start);
    while( strup(s))
    {
       /* while(!kbhit())
        {
            gotoxy(x, y);
            printf("%s", s);
            Sleep(1100);
            system("cls");
            y++;
            if(y == 18)
            {
                printf("Game Over");
                Sleep(100);
                exit(1);
            }
        }*/
        char harf = getche();
        if(harf == s[m])
        {
            s[m] = toupper(s[m]) ;
            m++;
        }
        else if(harf == 'Q')
        {
            printf("\n");
            if(finish())
            {
                printf("THE END");
                exit(0);
            }
        }
        else if(harf == 'P')
        {
            time( &end );
            d1 = difftime (end , start);
            printf("\nThe game is paused press R to continue\n");
            if(getche() == 'R')
                time( &start );
        }
        else
            fal++ ;
    printf("\n");
    SetConsoleTextAttribute(hstdout,701);
    //system("cls");
    //gotoxy(x, y+1);
    //y++;
    printf("%s", s);
    printf("\n");
    strup(s);
   }
   // y=0;
    //gotoxy (x, y);
    system("cls");
    time(&end);
    dif = difftime(end , start) + d1;
    gameover(dif, lvl);
    if(q == 1)
       sum_of_score += score_of_word_one(huruf , fal , dif) ;
    else if (q == 2)
       sum_of_score += score_of_word_two(huruf ,fal,  dif) ;
     fal = 0;
     m = 0;
     previous->next = current->next;
     current = current->next;
     sum_of_score = (double)sum_of_score/counter;
     w-- ;
    }
}
void save_info (int lvl, char name[], double score )
{
    strcpy (pl1.esm , name);
    pl1.lvl= lvl;
    pl1.score = score;
    info=fopen("info.bin","a+b");
    rewind(info);
    fwrite(&pl1, sizeof(pl1), 1, info);
}
/*
void save_player(int lvl, char name[], double score )
{
    info=fopen("info.bin","r+b");
     struct players *pl1=(struct players *)malloc(sizeof(struct players));
    strcpy (pl1->esm , name);
    printf("%s",pl1->esm );
    pl1->lvl= lvl;
    pl1->score= score;
    struct players *pl2=(struct players *)malloc(sizeof(struct players));
    while(!feof(info))
    {
        fread(pl2 , sizeof(struct players), 1, info);
        if(strcmp(pl2->esm , pl1->esm) == 0)
        {
            fseek(info, (-1)*sizeof(struct players), SEEK_CUR);
            fwrite(pl1, 1*sizeof(struct players), 1, info);
            fclose(info);
            return;
        }
    }
    fwrite(pl1, sizeof(struct players),1, info);
    fclose(info);
    return;
}*/

int search_info(char name[])
{
    info= fopen("info.bin", "a+b");
    fread(&pl2 , sizeof(pl2), 1, info);
    while( strcmp(pl2.esm , name) != 0 )
    {
        if(!feof(info))
           fread(&pl2 , sizeof(pl2), 1, info);
        else
            return 0;
    }
    lvl = pl2.lvl ;
    sum_of_score = pl2.score;
 return 1;
}

int finish ()
{
    int a;
    rewind(info);
    system("cls");
    HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hstdout,459);
    printf("finished! your score is:%.2f\n", sum_of_score);
    printf("save your current state?y/n\n");
    if(getche() == 'y')
        save_info(lvl, name, sum_of_score);
    printf("\n1:exit\n2:next level\n");
    scanf("%d", &a);
    return a;
}

void jadvale_emtiaz()
{
    struct players player_arr[num];
    double arraye[num];
    struct players swap;
    int i=0, j, d;
    info = fopen("info.bin", "a+b");
    while(!feof(info))
    {
        fread(&pl2 , sizeof(pl2), 1, info);
        player_arr[i]= pl2;
        i++;
    }
    for (j = 0 ; j < ( i - 1 ); j++)
    {
        for (d = 0 ; d < i - j - 1; d++)
        {
            if (player_arr[d].score < player_arr[d+1].score)
            {
                swap            = player_arr[d];
                player_arr[d]   = player_arr[d+1];
                player_arr[d+1] = swap;
            }
        }
   }
    for(j=0 ; j< i ; j++)
        printf("\n%s \t %.2f\n", player_arr[j].esm, player_arr[j].score);

}
void game_handle()
{
    while(1)
    {
        choose_levels (lvl);
        main_game();
        if(finish() == 1)
        {
            printf ("THE END\n");
            fclose (fp);
            break;
        }
        else
        {
            lvl++ ;
            sum_of_score = 0;
            fclose (fp);
        }
    }
}

int main()
{
  MessageBox(NULL, TEXT("WELCOME TO TYPERACER!"), TEXT("Hello!"), MB_OK);
  int a = show_menu();
    if(a == 1)
    {
        printf("Okay,let's start Please Enter the Level I have at most %d levels\n", number_of_files());
        scanf("%d", &lvl);
        game_handle();
    }
    else
    {
        if(search_info(name))
        {
          lvl++;
          game_handle() ;
        }
     else
         printf("user not found");

    }
   /* printf("Do you wanna see the scoring table?y/n");
      if(getche() == 'y')
          jadvale_emtiaz();

*/
    return 0;
}
