#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <termios.h>
#include <fcntl.h>
#include "main.h"




void Train()
{

	char *Train1="\033[0;31m/\033[0m────────────────────┌──────┐────────────────┌──────┐────────────────┌──────┐────────────────────\033[0;31m\\\033[0m";
	char *Train2="| | ████████ ¦¦ \033[1;34m████\033[0m\033[0;31m██\033[0m\033[1;34m████████\033[0m\033[0;31m██\033[0m\033[1;34m████\033[0m ¦¦ \033[1;34m████\033[0m\033[0;31m██\033[0m\033[1;34m████████\033[0m\033[0;31m██\033[0m\033[1;34m████\033[0m ¦¦ \033[1;34m████\033[0m\033[0;31m██\033[0m\033[1;34m████████\033[0m\033[0;31m██\033[0m\033[1;34m████\033[0m ¦¦ ████████ | |";
	char *Train3="| | ████████ ¦¦ \033[1;34m████\033[0m\033[0;31m██\033[0m\033[1;34m████████\033[0m\033[0;31m██\033[0m\033[1;34m████\033[0m ¦¦ \033[1;34m████\033[0m\033[0;31m██\033[0m\033[1;34m████████\033[0m\033[0;31m██\033[0m\033[1;34m████\033[0m ¦¦ \033[1;34m████\033[0m\033[0;31m██\033[0m\033[1;34m████████\033[0m\033[0;31m██\033[0m\033[1;34m████\033[0m ¦¦ ████████ | |";
	char *Train4="\033[0;31m\\\033[0m────────────────────└──────┘────────────────└──────┘────────────────└──────┘────────────────────\033[0;31m/\033[0m";
	char *Train1_po="\033[0;31m/\033[0m──────────────────┌───    ───┐────────────┌───    ───┐────────────┌───    ───┐──────────────────\033[0;31m\\\033[0m";
	char *Train4_po="\033[0;31m\\\033[0m──────────────────└───    ───┘────────────└───    ───┘────────────└───    ───┘──────────────────\033[0;31m/\033[0m";
	int POSRESET_X =50, POSRESET_Y=1;
	static int POSARRET_X = 37,POSARRET_Y=14;
	int Table_Y[8] = {2,1,1,2,79,78,78,79};
	int Table_X[8] = {9,10,11,12,25,26,27,28};
	int i=0,z=0;
	int compteur = 0;


	while(1)
	{
		if (z ==33)//33
		{
			printf("\033[%d;%dH%s",Table_X[0],Table_Y[0],Train1_po);
			printf("\033[%d;%dH%s\n",Table_X[7],Table_Y[7],Train4_po);

			for(compteur=9;compteur>=0;compteur--)
			{
				printf("\033[%d;%dH%d\n",POSARRET_X+2,POSARRET_Y,compteur);
				printf("\033[%d;%dH\n",POSRESET_X,POSRESET_Y);
				stopwatch(1);
			}
			z =-45;



		}



		else if(Table_Y[0] == 80)
		{
			Table_Y[0] = 178;
			Table_Y[1] = 179;
			Table_Y[2] = 179;
			Table_Y[3] = 178;
			for (i =101;i>0;i--)
			{
				stopwatch(0.02);
				printf("\033[%d;%dH-\n",Table_X[0],Table_Y[0]);
				Table_Y[0] = Table_Y[0] - 1;

				printf("\033[%d;%dH \n",Table_X[1],Table_Y[1]);
				Table_Y[1] = Table_Y[1] - 1;

				printf("\033[%d;%dH \n",Table_X[2],Table_Y[2]);
				Table_Y[2] = Table_Y[2] - 1;

				printf("\033[%d;%dH-\n",Table_X[3],Table_Y[3]);
				Table_Y[3] = Table_Y[3] - 1;

				printf("\033[%d;%dH-\n",Table_X[4],Table_Y[4]);
				Table_Y[4] = Table_Y[4] + 1;

				printf("\033[%d;%dH \n",Table_X[5],Table_Y[5]);
				Table_Y[5] = Table_Y[5] + 1;

				printf("\033[%d;%dH \n",Table_X[6],Table_Y[6]);
				Table_Y[6] = Table_Y[6] + 1;

				printf("\033[%d;%dH-\n",Table_X[7],Table_Y[7]);
				Table_Y[7] = Table_Y[7] + 1;

				printf("\033[%d;%dH\n",POSRESET_X,POSRESET_Y);





			}

			for(compteur=9;compteur>=0;compteur--)
			{
				printf("\033[%d;%dH%d\n",POSARRET_X+3,POSARRET_Y+3,compteur);

				printf("\033[%d;%dH\n",POSRESET_X,POSRESET_Y);
				stopwatch(1);



			}

			Table_Y[0] = 2;
			Table_Y[1] = 1;
			Table_Y[2] = 1;
			Table_Y[3] = 2;
			Table_Y[4] = 79;
			Table_Y[5] = 78;
			Table_Y[6] = 78;
			Table_Y[7] = 79;




		}





		else 
		{
			z++;//variable pour l'arret du train

			Table_Y[0] = Table_Y[0] +1; //2 3 4 5 6 7 8 9 10
			printf("\033[%d;%dH- ",Table_X[0],Table_Y[0]-1);
			printf("\033[%d;%dH%s",Table_X[0],Table_Y[0],Train1);

			Table_Y[1] = Table_Y[1]+1;
			printf("\033[%d;%dH ",Table_X[1],Table_Y[1]-1);
			printf("\033[%d;%dH%s\n",Table_X[1],Table_Y[1],Train2);

			Table_Y[2] = Table_Y[2]+1;
			printf("\033[%d;%dH ",Table_X[2],Table_Y[2]-1);
			printf("\033[%d;%dH%s\n",Table_X[2],Table_Y[2],Train3);

			Table_Y[3] = Table_Y[3]+1;
			printf("\033[%d;%dH- ",Table_X[3],Table_Y[3]-1);
			printf("\033[%d;%dH%s\n",Table_X[3],Table_Y[3],Train4);

			Table_Y[4] = Table_Y[4]-1;
			printf("\033[%d;%dH%s-\n",Table_X[4],Table_Y[4],Train1);

			Table_Y[5] = Table_Y[5]-1;
			printf("\033[%d;%dH%s \n",Table_X[5],Table_Y[5],Train2);

			Table_Y[6] = Table_Y[6]-1;
			printf("\033[%d;%dH%s \n",Table_X[6],Table_Y[6],Train3);

			Table_Y[7] = Table_Y[7]-1;
			printf("\033[%d;%dH%s-\n",Table_X[7],Table_Y[7],Train4);


			stopwatch(0.2);



		}		


	}	
}

