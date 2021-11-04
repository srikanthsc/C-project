#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <termios.h>
#include <fcntl.h>
#include "main.h"

// pour eviter les lettres
void purge ()
{
	int c;
	while ((c = getchar ()) != '\n' && c != EOF)
	{
	}
}
// Pour stop le temps
void stopwatch(float temps)
{
	clock_t arrivee=clock()+(temps*CLOCKS_PER_SEC); // On calcule le moment où l'attente devra s'arrêter

	while(clock()<arrivee);
}

// generation du nombre aléas
int gennum_pass()
{
	srand((int)time(NULL));
	int nbgen=rand()%5+2; //de 2 a 6
	return nbgen;
}
// check la positions
void CheckPosition(int *Pass1_X,int *Pass1_Y,int *Pass2_X,int *Pass2_Y)
{
	if( *Pass1_X == *Pass2_X && *Pass1_Y == *Pass2_Y)
	{
		if(*Pass1_X >=2 && *Pass1_X <= 6)
		{
			*Pass1_Y = *Pass1_Y-1;
			printf("\033[%d;%dH*",*Pass1_X,*Pass1_Y);
			printf("\033[%d;%dH ",*Pass1_X,*Pass1_Y+1);
		}
		if(*Pass1_X >=31 && *Pass1_X<= 36)
		{
			*Pass1_Y = *Pass1_Y-1;
			printf("\033[%d;%dH*",*Pass1_X,*Pass1_Y);
			printf("\033[%d;%dH ",*Pass1_X,*Pass1_Y+1);
		}

	}


}

// Passagers aléatoire et le passagers controller
void Passagers_Func(int *TablePassNord_X,int *TablePassNord_Y,int *TablePassSud_X,int *TablePassSud_Y,char *Passagers,int randomnum,int z,int *x,int *y)// Passagers aléatoire + Passagers controlé
{	
	char ch;
	int POSRESET_X =50, POSRESET_Y=1;

	char pass='I';

	if(randomnum >= 1 && randomnum <= 2) // les different if pour deplacer le voyageur en aléas
	{
		*TablePassNord_Y = *TablePassNord_Y - 1;// passagers nord recule
		*TablePassSud_X = *TablePassSud_X +1;// passagers sud descend
		printf("\033[%d;%dH ",*TablePassNord_X,*TablePassNord_Y+1);
		printf("\033[%d;%dH ",*TablePassSud_X-1,*TablePassSud_Y);
		printf("\033[%d;%dH ",POSRESET_X,POSRESET_Y);	
		if(*TablePassNord_Y == 6) // délimiter la zone
		{
			*TablePassNord_Y = *TablePassNord_Y +1;

		}
		if(*TablePassSud_X == 36)
		{
			*TablePassSud_X = *TablePassSud_X - 1;
			*TablePassSud_Y = *TablePassSud_Y + 2;

		}

	}
	else if(randomnum >= 3 && randomnum <=4)
	{
		*TablePassNord_X = *TablePassNord_X + 1;//passagers nord descend
		*TablePassSud_X = *TablePassSud_X - 1;//passagers sud monte
		printf("\033[%d;%dH ",*TablePassNord_X-1,*TablePassNord_Y);
		printf("\033[%d;%dH ",*TablePassSud_X+1,*TablePassSud_Y);
		printf("\033[%d;%dH ",POSRESET_X,POSRESET_Y);
		if(*TablePassNord_X == 5)
		{
			*TablePassNord_X = *TablePassNord_X - 1;
		}
		if(*TablePassSud_X == 32)
		{
			*TablePassSud_X = *TablePassSud_X + 1;
		}
	}
	else if(randomnum >=5 && randomnum <=8)
	{
		*TablePassNord_Y = *TablePassNord_Y + 2;//passagers nord avance
		*TablePassSud_Y = *TablePassSud_Y + 2;//passavers sud avance
		printf("\033[%d;%dH ",*TablePassNord_X,*TablePassNord_Y-2);
		printf("\033[%d;%dH ",*TablePassSud_X,*TablePassSud_Y-2);
		printf("\033[%d;%dH ",POSRESET_X,POSRESET_Y);
		if(*TablePassNord_Y >= 164)
		{
			*TablePassNord_Y = *TablePassNord_Y -3;
		}
		if(*TablePassSud_Y >= 164)
		{
			*TablePassSud_Y = *TablePassSud_Y - 3;
		}
	}
	else if(randomnum >=9 && randomnum <=10)
	{
		*TablePassNord_X = *TablePassNord_X - 1;//passagers nord monte
		*TablePassSud_Y = *TablePassSud_Y - 1;//passagers sud recule
		printf("\033[%d;%dH ",*TablePassNord_X+1,*TablePassNord_Y);
		printf("\033[%d;%dH ",*TablePassSud_X,*TablePassSud_Y+1);
		printf("\033[%d;%dH ",POSRESET_X,POSRESET_Y);
		if(*TablePassNord_X == 1)
		{
			*TablePassNord_X = *TablePassNord_X + 1;
			*TablePassNord_Y = *TablePassNord_Y + 2;
		}
		if(*TablePassSud_Y == 6)
		{
			*TablePassSud_Y = *TablePassSud_Y + 1;

		}

	}
	printf("\033[%d;%dH%c\n",*TablePassNord_X,*TablePassNord_Y,*Passagers);
	printf("\033[%d;%dH%c\n",*TablePassSud_X,*TablePassSud_Y,*Passagers);
	printf("\033[%d;%dH ",POSRESET_X,POSRESET_Y); 	



	if(*TablePassNord_Y >= 158 && *TablePassNord_Y <= 163 && *TablePassNord_X == 2) // lorsqu'il va vers la sortie il revien a sa position
	{
		printf("\033[%d;%dH%c\n",*TablePassNord_X,*TablePassNord_Y,*Passagers); 
		printf("\033[%d;%dH ",*TablePassNord_X,*TablePassNord_Y);
		*TablePassNord_X = 3;
		*TablePassNord_Y = 17;
	}
	if(*TablePassSud_Y >=158 && *TablePassSud_Y <= 164 && *TablePassSud_X == 35)
	{
		printf("\033[%d;%dH%c\n",*TablePassSud_X,*TablePassSud_Y,*Passagers); 
		printf("\033[%d;%dH ",*TablePassSud_X,*TablePassSud_Y);
		*TablePassSud_X = 34;
		*TablePassSud_Y = 17;
	}

	printf("\033[%d;%dH ",POSRESET_X,POSRESET_Y); 	
	ch = key_pressed(); // fonction qui permet d'appuyer sur le clavier sans pour autant appuyer entrer

	if(ch)
	{

		if(ch == 65)//fleche haut
		{
			*x = *x-1;
			printf("\033[%d;%dH ",*x+1,*y);
			if(*x ==1) // delimiter la zone
			{
				*x = *x+1;
			}
		}
		else if(ch == 66)//fleche bas
		{
			*x = *x+1;
			printf("\033[%d;%dH ",*x-1,*y);

		}
		else if(ch == 67)//fleche droite
		{
			*y = *y +2;
			printf("\033[%d;%dH ",*x,*y-2);
			if(*y >=168)
			{
				*y = *y-2;
			}
		}
		else if(ch == 68)//fleche gauche
		{
			*y = *y -2;
			printf("\033[%d;%dH ",*x,*y+2);
			if(*y <= 5)
			{
				*y = *y+2;
			}
		}


		if(z != 33)
		{
			if(*x == 6)
			{
				*x = *x-1;
			}
		}
		else
		{
			if(*x == 6 && *y >= 5 && *y <= 58)
			{
				*x = *x-1;
			}
			else if(*x == 6 && *y >= 61 && *y <82)
			{
				*x = *x-1;
			}
			else if(*x == 6 && *y >= 85 && *y <= 106)
			{
				*x = *x-1;
			}
			else if(*x == 6 && *y >= 109 && *y  <= 148)
			{
				*x = *x-1;
			}
		}

		printf("\033[%d;%dH%c",*x,*y,pass);
		printf("\033[%d;%dH ",*TablePassSud_X,*TablePassSud_Y);
		printf("\033[%d;%dH ",POSRESET_X,POSRESET_Y);

	}


}


// Passagers qui vont vers le train
void PassagersInTrain(int *TablePassNordIn_X,int *TablePassNordIn_Y,char *PassagersIn,int RandomNumIn)
{

	int POSRESET_X =50, POSRESET_Y=1;

	if(RandomNumIn >= 1 && RandomNumIn <= 2)
	{
		*TablePassNordIn_Y = *TablePassNordIn_Y - 1;// passagers nord recule
		printf("\033[%d;%dH ",*TablePassNordIn_X,*TablePassNordIn_Y+1);
		printf("\033[%d;%dH ",POSRESET_X,POSRESET_Y);	
		if(*TablePassNordIn_Y == 6)
		{
			*TablePassNordIn_Y = *TablePassNordIn_Y +1;

		}

	}
	else if(RandomNumIn >= 3 && RandomNumIn <=4)
	{
		*TablePassNordIn_X = *TablePassNordIn_X + 1;//passagers nord descend
		printf("\033[%d;%dH ",*TablePassNordIn_X-1,*TablePassNordIn_Y);
		printf("\033[%d;%dH ",POSRESET_X,POSRESET_Y);
		if(*TablePassNordIn_X == 5)
		{
			*TablePassNordIn_X = *TablePassNordIn_X - 1;
		}
	}
	else if(RandomNumIn >=5 && RandomNumIn <=8)
	{
		*TablePassNordIn_Y = *TablePassNordIn_Y + 2;//passagers nord avance
		printf("\033[%d;%dH ",*TablePassNordIn_X,*TablePassNordIn_Y-2);
		printf("\033[%d;%dH ",POSRESET_X,POSRESET_Y);
		if(*TablePassNordIn_Y >= 164)
		{
			*TablePassNordIn_Y = *TablePassNordIn_Y -3;
		}
	}
	else if(RandomNumIn >=9 && RandomNumIn <=10)
	{
		*TablePassNordIn_X = *TablePassNordIn_X - 1;//passagers nord monte
		printf("\033[%d;%dH ",*TablePassNordIn_X+1,*TablePassNordIn_Y);
		printf("\033[%d;%dH ",POSRESET_X,POSRESET_Y);
		if(*TablePassNordIn_X == 1)
		{
			*TablePassNordIn_X = *TablePassNordIn_X + 1;
			*TablePassNordIn_Y = *TablePassNordIn_Y + 2;
		}

	}
	printf("\033[%d;%dH%c\n",*TablePassNordIn_X,*TablePassNordIn_Y,*PassagersIn);
	printf("\033[%d;%dH ",POSRESET_X,POSRESET_Y); 	

}


void PassagersInTrainSud(int *TablePassSudIn_X,int *TablePassSudIn_Y,char *PassagersIn,int RandomNumIn)
{
	int POSRESET_X =50, POSRESET_Y=1;

	if(RandomNumIn >= 1 && RandomNumIn <= 2)
	{
		*TablePassSudIn_X = *TablePassSudIn_X +1;// passagers sud descend
		printf("\033[%d;%dH ",*TablePassSudIn_X-1,*TablePassSudIn_Y);
		printf("\033[%d;%dH ",POSRESET_X,POSRESET_Y);	
		if(*TablePassSudIn_X == 36)
		{
			*TablePassSudIn_X = *TablePassSudIn_X - 1;
			*TablePassSudIn_Y = *TablePassSudIn_Y + 2;

		}

	}
	else if(RandomNumIn >= 3 && RandomNumIn <=4)
	{
		*TablePassSudIn_X = *TablePassSudIn_X - 1;//passagers sud monte
		printf("\033[%d;%dH ",*TablePassSudIn_X+1,*TablePassSudIn_Y);
		printf("\033[%d;%dH ",POSRESET_X,POSRESET_Y);
		if(*TablePassSudIn_X == 32)
		{
			*TablePassSudIn_X = *TablePassSudIn_X + 1;
		}
	}
	else if(RandomNumIn >=5 && RandomNumIn <=8)
	{
		*TablePassSudIn_Y = *TablePassSudIn_Y + 2;//passavers sud avance
		printf("\033[%d;%dH ",*TablePassSudIn_X,*TablePassSudIn_Y-2);
		printf("\033[%d;%dH ",POSRESET_X,POSRESET_Y);
		if(*TablePassSudIn_Y >= 164)
		{
			*TablePassSudIn_Y = *TablePassSudIn_Y - 3;
		}
	}
	else if(RandomNumIn >=9 && RandomNumIn <=10)
	{
		*TablePassSudIn_Y = *TablePassSudIn_Y - 1;//passagers sud recule
		printf("\033[%d;%dH ",*TablePassSudIn_X,*TablePassSudIn_Y+1);
		printf("\033[%d;%dH ",POSRESET_X,POSRESET_Y);
		if(*TablePassSudIn_Y == 6)
		{
			*TablePassSudIn_Y = *TablePassSudIn_Y + 1;

		}

	}
	printf("\033[%d;%dH%c\n",*TablePassSudIn_X,*TablePassSudIn_Y,*PassagersIn);
	printf("\033[%d;%dH ",POSRESET_X,POSRESET_Y); 	
}

// Passagers qui sont dans le train Nord
void PassagersNord_TrainFunc(int *TablePassTrainNord_X,int *TablePassTrainNord_Y,char *PassagersNord_Train,int WagonMaxNord,int WagonMinNord,int PorteGoalNord,int z)
{
	int i = 2;
	if( z!=33)
	{
		*TablePassTrainNord_Y = *TablePassTrainNord_Y + 1;
		printf("\033[%d;%dH%c\n",*TablePassTrainNord_X,*TablePassTrainNord_Y,*PassagersNord_Train);
	}

	if( z == 33)
	{

		if(*TablePassTrainNord_Y >= WagonMinNord && *TablePassTrainNord_Y <= WagonMaxNord)//faire sortir les passagers vers la sortie
		{



			if(*TablePassTrainNord_Y  == PorteGoalNord)
			{
				if(*TablePassTrainNord_X >=2)
				{	
					*TablePassTrainNord_X = *TablePassTrainNord_X - i;
					printf("\033[%d;%dH%c\n",*TablePassTrainNord_X,*TablePassTrainNord_Y,*PassagersNord_Train);
					printf("\033[%d;%dH ",*TablePassTrainNord_X+i,*TablePassTrainNord_Y);
				}
				else
				{	*TablePassTrainNord_X = 1;
					printf("\033[%d;%dH ",*TablePassTrainNord_X,*TablePassTrainNord_Y);
				}


			}

			else if(*TablePassTrainNord_Y < PorteGoalNord)
			{

				*TablePassTrainNord_Y = *TablePassTrainNord_Y + 2;
				if(*TablePassTrainNord_Y > PorteGoalNord)
				{
					*TablePassTrainNord_Y = *TablePassTrainNord_Y - 1;
				}
			}
			else if(*TablePassTrainNord_Y > PorteGoalNord)
			{
				*TablePassTrainNord_Y = *TablePassTrainNord_Y - 2;
				if(*TablePassTrainNord_Y < PorteGoalNord)
				{
					*TablePassTrainNord_Y = *TablePassTrainNord_Y + 1;

				}


			}
			if(*TablePassTrainNord_X == 5)//réecrire  le décors
			{
				printf("\033[%d;%dH=",*TablePassTrainNord_X+2,*TablePassTrainNord_Y);
				printf("\033[%d;%dH_",*TablePassTrainNord_X+3,*TablePassTrainNord_Y);
			}
			if(*TablePassTrainNord_X == 7)
			{
				printf("\033[%d;%dH_",*TablePassTrainNord_X+1,*TablePassTrainNord_Y);
			}

		}

	}



}

void PassagersSud_TrainFunc(int *TablePassTrainSud_X,int *TablePassTrainSud_Y,char *PassagersSud_Train,int WagonMaxSud,int WagonMinSud,int PorteGoalSud,int z)
{
	int i = 2;
	if(z != 33)
	{
		*TablePassTrainSud_Y = *TablePassTrainSud_Y - 1;
		printf("\033[%d;%dH%c\n",*TablePassTrainSud_X,*TablePassTrainSud_Y,*PassagersSud_Train);
	}
	if( z == 33)
	{

		if(*TablePassTrainSud_Y >= WagonMinSud && *TablePassTrainSud_Y <= WagonMaxSud)
		{
			if(*TablePassTrainSud_Y  == PorteGoalSud)
			{
				if(*TablePassTrainSud_X <= 34)
				{
					*TablePassTrainSud_X = *TablePassTrainSud_X + i;
					printf("\033[%d;%dH%c\n",*TablePassTrainSud_X,*TablePassTrainSud_Y,*PassagersSud_Train);
					printf("\033[%d;%dH ",*TablePassTrainSud_X-i,*TablePassTrainSud_Y);


				}
				else
				{
					printf("\033[%d;%dH ",*TablePassTrainSud_X,*TablePassTrainSud_Y);
					*TablePassTrainSud_X = 36;

				}





			}

			else if(*TablePassTrainSud_Y < PorteGoalSud)
			{

				*TablePassTrainSud_Y = *TablePassTrainSud_Y + 2;
				if(*TablePassTrainSud_Y > PorteGoalSud)
				{
					*TablePassTrainSud_Y = *TablePassTrainSud_Y - 1;
				}
				printf("\033[%d;%dH%c\n",*TablePassTrainSud_X,*TablePassTrainSud_Y,*PassagersSud_Train);
				printf("\033[%d;%dH ",*TablePassTrainSud_X,*TablePassTrainSud_Y-2);
			}
			else if(*TablePassTrainSud_Y > PorteGoalSud)
			{
				*TablePassTrainSud_Y = *TablePassTrainSud_Y - 2;
				if(*TablePassTrainSud_Y < PorteGoalSud)
				{
					*TablePassTrainSud_Y = *TablePassTrainSud_Y + 1;

				}
				printf("\033[%d;%dH%c\n",*TablePassTrainSud_X,*TablePassTrainSud_Y,*PassagersSud_Train);
				printf("\033[%d;%dH ",*TablePassTrainSud_X,*TablePassTrainSud_Y+2);


			}
			if(*TablePassTrainSud_X == 32)//réécrire le décors
			{
				printf("\033[%d;%dH=",*TablePassTrainSud_X-2,*TablePassTrainSud_Y);
				printf("\033[%d;%dH_",*TablePassTrainSud_X-3,*TablePassTrainSud_Y);
			}
			if(*TablePassTrainSud_X == 30)
			{
				printf("\033[%d;%dH_",*TablePassTrainSud_X-1,*TablePassTrainSud_Y);
			}
		}

	}
}




char key_pressed()
{
	struct termios oldterm, newterm;
	int oldfd; char c, result = 0;
	tcgetattr (STDIN_FILENO, &oldterm);
	newterm = oldterm; newterm.c_lflag &= ~(ICANON | ECHO);
	tcsetattr (STDIN_FILENO, TCSANOW, &newterm);
	oldfd = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl (STDIN_FILENO, F_SETFL, oldfd | O_NONBLOCK);
	c = getchar();
	tcsetattr (STDIN_FILENO, TCSANOW, &oldterm);
	fcntl (STDIN_FILENO, F_SETFL, oldfd);
	if (c != EOF) {
		ungetc(c, stdin); result = getchar();
	}
	return result;
}


