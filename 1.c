#include<stdio.h>

char name[10];

void menu();
void startGame();
void print(FILE *file);
int checkAnswer(char answer,int qno);
void writeHighscore(int price);
void viewHighScore();
void resetHighScore();

int main()
{
	int choice;
	do
	{
		printf("---------------------MENU---------------------------\n");
		printf("\t1.Enter Game \n");
		printf("\t2.High Score \n");
		printf("\t3.Rest High Score \n");
		printf("\t4.Quit \n");
		printf("----------------------------------------------------\n");
		printf("Enter Your Choice\n");
		scanf("%d",&choice);

		switch (choice)
		{
		case 1:
			startGame();
			break;
		case 2:
			viewHighScore();
			break;
		case 3:
			resetHighScore();
			break;
		case 4:
			printf("..Quit..");
			break;
		default:
			printf("Invalid Choice Try Again ..");
			break;
		}
	} while (choice != 4);
}


void viewHighScore()
{
	FILE *file = fopen("HighScore.txt","r");
	char text[50];
	fgets(text,50,file);
	printf("%s",text);
	fclose(file);
}

void startGame()
{
	printf("Enter Your Name..! \n");
	scanf("%s",name);
	FILE *quizFile = fopen("quiz.txt","r");
    int qno=0;
    char answer;
	int cashPrice = 0;
    while (qno < 3)
    {
		//system("cls");
        printf("Quiz %d \n",qno + 1);
		printf("---------------------------------------------------------------------\n");
        print(quizFile);
		printf("----------------------------------------------------------------------\n");
        printf("\n Enter yor Answer : ");
        scanf(" %c",&answer);
		if(checkAnswer(answer,qno) == 0)
		{
			cashPrice += 1000;
		}
		else if(checkAnswer(answer,qno) == 1)
		{
			printf("SORRY YOU ARE NOT ELIGIBLE TO PLAY THIS GAME, BETTER LUCK NEXT TIME\n");
			printf("YOU WON %d\n",cashPrice);
			writeHighscore(cashPrice);
			return;
		}
        qno ++;
    }
	printf("**************** CONGRATULATION ****************\n");
	printf("\tYou have pass into second Round\n");
	printf("************************************************\n");
	while (qno < 7)
    {
		//system("cls");
        printf("Quiz %d \n",qno + 1);
		printf("---------------------------------------------------------------------\n");
        print(quizFile);
		printf("----------------------------------------------------------------------\n");
        printf("\n Enter yor Answer : ");
        scanf(" %c",&answer);
		checkAnswer(answer,qno);
		if(checkAnswer(answer,qno) == 0)
		{
			cashPrice += 2000;
		}
		else if(checkAnswer(answer,qno) == 1)
		{
			printf("SORRY YOU ARE NOT ELIGIBLE TO CONTINUE THIS GAME, BETTER LUCK NEXT TIME\n");
			printf("YOU WON %d\n",cashPrice);
			writeHighscore(cashPrice);
			return;
		}
        qno ++;
    }
	printf("**************** CONGRATULATION ****************\n");
	printf("\tYou have won the game\n");
	printf("************************************************\n");
	writeHighscore(cashPrice);
    fclose(quizFile);
	
}

void print(FILE *file)
{
    char ch;
    while (!feof(file))
    {
        ch = fgetc(file);
        if(ch == '#')
        {
            break;
        }
        printf("%c",ch);
    }
}

int checkAnswer(char answer,int qno)
{
	FILE *answerFile = fopen("answer.txt","r");
	char data[10];
	while (!feof(answerFile))
	{
		fgets(data,10,answerFile);
	}
	
	if(data[qno] == answer)
	{
		printf("\n correct ..!");
		fclose(answerFile);
		return 0;
	}
	else
	{
		printf("\n worang ..! \n");
		printf("%d answer is %c \n",qno + 1,data[qno]);
		fclose(answerFile);
		return 1;
	}
	
}

void writeHighscore(int price)
{
	FILE *highscorefile = fopen("HighScore.txt","r+");

    if (NULL != highscorefile) 
    {
        fseek (highscorefile, 0, SEEK_END);
        long size = ftell(highscorefile);

        if (0 == size) 
        {
            //printf("file is empty\n");
            rewind(highscorefile);
            fprintf(highscorefile,"%s %d",name,price);
		    fclose(highscorefile);
        }
        else
        {
            char tempName[10];
            int tempPrice;
            rewind(highscorefile);
            fscanf(highscorefile,"%s %d",tempName,&tempPrice);
            if(tempPrice < price)
            {
                fclose(highscorefile);
                highscorefile = fopen("HighScore.txt","w");
                fprintf(highscorefile,"%s %d",name,price);
                fclose(highscorefile);
            }
        }
       
    }
}

void resetHighScore()
{
	FILE *highscorefile = fopen("HighScore.txt","w");
	fclose(highscorefile);
}
