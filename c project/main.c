#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <termios.h>
#include <fcntl.h>
#include "main.h"


int main()
{
	// train
	system("clear");
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
	int j =1;
	int Choice =0,compteur=0;

	// passagers train qui sort
	int a = 0,b=0;
	int e = 1;
	int randomnum_2 = 0;
	int randomnum_3 = 0;
	int RandomPassStay_1 = 0;
	int RandomPassStay_2 = 0;

	int TablePassTrainNord_Y[6] = {20,57,68,33,44,81};
	int TablePassTrainNord_X[6] = {10,10,10,11,11,11};
	int CTablePassTrainNord_Y[6] = {20,57,68,33,44,81};
	int CTablePassTrainNord_X[6] ={10,10,10,11,11,11};
	char PassagersNord_Train[randomnum_2];
	int WagonMaxNord[6] = {69,93,117,69,93,117};
	int WagonMinNord[6] = {51,74,98,51,74,98};
	int PorteGoalNord[6] = {60,84,108,60,84,108};

	char PassagersSud_Train[randomnum_3];
	int WagonMaxSud[6] = {127,79,103,127,103,79};
	int WagonMinSud[6] = {109,61,85,109,85,61};
	int PorteGoalSud[6] = {119,71,95,119,95,71};
	int TablePassTrainSud_Y[6] = {158,97,121,145,134,110};
	int TablePassTrainSud_X[6] = {26,26,26,26,27,27};
	int CTablePassTrainSud_Y[6] = {158,97,121,145,134,110};
	int CTablePassTrainSud_X[6] = {26,26,26,26,27,27};



	// passagers aléatoire et passagers controller
	int x =2; // passagers controller Position
	int y =81; // passagers controller Position
	char pass = 'I';

	int WagonMin_Y[3] ={18,42,66};
	int WagonMax_Y[3] ={37,61,85};


	int randomnum=0; // chiffre aléatoire afin de faire bouger aléatoirement mes passagers
	int RandomNum_Pass = gennum_pass();
	int TablePassNord_Y[RandomNum_Pass];
	int TablePassNord_X[RandomNum_Pass];
	int TablePassSud_X[RandomNum_Pass];
	int TablePassSud_Y[RandomNum_Pass];
	char Passagers[RandomNum_Pass];


	for(i=0; i <= RandomNum_Pass;i++)
	{
		TablePassNord_Y[i] = 17;
		TablePassNord_X[i] = 3;
		TablePassSud_Y[i] = 17;
		TablePassSud_X[i] = 34;
		Passagers[i] = '*';
	}
	// passagers qui marche vers le train (in)
	int c=0;
	int h = 1;
	int CompteurBreakPass = 1;
	int PassPauseNord = 0; // variable pour quand le passagers nord s'arrete afin qu'il sera plus en mouvement
	int PassPauseSud = 0;
	int PassPauseStop[100] = {0,0,0,0,0,0,0,0,0};
	int RandomNumIn = 0;
	int RandomNumIn_Pass = 2;
	int TablePassNordIn_Y[RandomNumIn_Pass];
	int TablePassNordIn_X[RandomNumIn_Pass];
	int TablePassSudIn_Y[RandomNumIn_Pass];
	int TablePassSudIn_X[RandomNumIn_Pass];

	int CTablePassNordIn_Y[RandomNumIn_Pass]; // Copie des Tableaux
	int CTablePassNordIn_X[RandomNumIn_Pass];
	int CTablePassSudIn_Y[RandomNumIn_Pass];
	int CTablePassSudIn_X[RandomNumIn_Pass];
	char PassagersIn[RandomNum_Pass];

	for(i=0; i <= RandomNumIn_Pass;i++)
	{
		TablePassNordIn_Y[i] = 17;
		TablePassNordIn_X[i] = 3;
		TablePassSudIn_Y[i] = 17;
		TablePassSudIn_X[i] = 34;
		CTablePassNordIn_Y[i] = 17;
		CTablePassNordIn_X[i] = 3;
		CTablePassSudIn_Y[i] = 17;
		CTablePassSudIn_X[i] = 34;
		PassagersIn[i] = '*';
	}

	int TablePassPauseNord1_X[2] = {6,8};
	int TablePassPauseNord_Y[2] = {59,59};
	int TablePassPauseSud1_X[2] = {31,29};
	int TablePassPauseSud_Y[2] = {70,70};



	// Variable pour check pa position
	int NumCheckPosition = 0; // il sera égale au plus petit chiffre entre les 2 nombre aléa
	if(RandomNumIn_Pass >=RandomNum_Pass)
	{
		NumCheckPosition = RandomNum_Pass;
	}
	else if(RandomNumIn_Pass <= RandomNum_Pass)
	{
		NumCheckPosition = RandomNumIn_Pass;
	}


	// decors dans un malloc
	char** Tableau_Menu=(char**)malloc((10000)*sizeof(char*));
	char** MenuDraw= Tableau_Menu;
	char* MenuRead=(char*)malloc((BUFSIZ)*sizeof(char));
	int Menu_size=0;
	int k = 0;
	FILE *Menu_File=fopen("menu.txt","r");
	if(Menu_File==NULL) 
		exit(1);
	while(fgets(MenuRead,BUFSIZ,Menu_File)!=NULL)
	{
		MenuDraw[k]=(char*)malloc((strlen(MenuRead))*sizeof(char));
		strcpy(MenuDraw[k], MenuRead);
		k++;

	}
	Menu_size=k;
	k=0;
	while(k<Menu_size){
		printf("%s",Tableau_Menu[k]);
		k++;

	}

	int PosChoice_X = 34;
	int PosChoice_Y = 1;
	// Seulement un Chiffre
	do
	{

		printf ("\033[%d;%dH Your Choice : ",PosChoice_X,PosChoice_Y);

		scanf ("%d", &Choice);
		fflush(stdout);		
		purge();
		printf("\033[%d;%dH                                                                                                                                                                                                \n",PosChoice_X,PosChoice_Y+10);

		if(Choice <1 || Choice >= 3)
		{
			Choice = 0;
		}



	}
	while (Choice == 0);

	// Generation du décors 
	system("clear");
	char** Tableau_Dec=(char**)malloc((10000)*sizeof(char*));
	char ** DecDraw=Tableau_Dec;
	char* DecRead=(char*)malloc((BUFSIZ)*sizeof(char));
	int Dec_size=0;
	int p = 0;
	FILE *Dec_File=fopen("decors.txt","r");
	if(Dec_File==NULL) 
		exit(1);
	while(fgets(DecRead,BUFSIZ,Dec_File)!=NULL)
	{
		DecDraw[p]=(char*)malloc((strlen(DecRead))*sizeof(char));
		strcpy(DecDraw[p], DecRead);
		p++;

	}
	Dec_size=p;
	p=0;
	while(p<Dec_size){
		printf("%s",Tableau_Dec[p]);
		p++;

	}



	switch(Choice)

	{
		case(1):
		

			while(1)
			{
				if (z ==33) // Cas ou le train s'arrete
				{
					printf("\033[%d;%dH%s",Table_X[0],Table_Y[0],Train1_po);
					printf("\033[%d;%dH%s\n",Table_X[7],Table_Y[7],Train4_po);

					for(compteur=9;compteur>=0;compteur--) //compteur de train
					{
						printf("\033[%d;%dH%d\n",POSARRET_X+2,POSARRET_Y,compteur);

						printf("\033[%d;%dH\n",POSRESET_X,POSRESET_Y);

						if(x == 12)//delimiter la zone du train
						{
							x = x-1;
						}
						if(x == 8 || x == 6)//pour réafficher le décors
						{
							if(x == 6)
							{
								printf("\033[%d;%dH=",x+1,y);
							}
							else if(x == 8)
							{
								printf("\033[%d;%dH=",x-1,y);
							}
						}
						else if(x == 9 || x == 7)//pour réafficher le décors

						{	if(x == 7)
							{
								printf("\033[%d;%dH_",x+1,y);
							}
							else if(x == 9)
							{
								printf("\033[%d;%dH_",x-1,y);	
							}
						}


						printf("\033[%d;%dH%s\n",Table_X[1],Table_Y[1],Train2);
						printf("\033[%d;%dH%s\n",Table_X[2],Table_Y[2],Train3);



						for(a = PassPauseNord; a < h; a++) // boucle for pour les Passagers vers le train
						{
							RandomNumIn = rand()%10+1;
							PassagersInTrain(&TablePassNordIn_X[a],&TablePassNordIn_Y[a],&PassagersIn[a],RandomNumIn);
						}


						for(a=0;a<NumCheckPosition;a++) // boucle for pour check les positions
						{
							CheckPosition(&TablePassNord_X[a],&TablePassNord_Y[a],&TablePassNordIn_X[a],&TablePassSudIn_X[a]);
							CheckPosition(&TablePassNord_X[a],&TablePassNord_Y[a],&x,&y);
							CheckPosition(&TablePassNordIn_X[a],&TablePassNordIn_Y[a],&x,&y);
						}


						for(a = 0; a < j; a++) // boucle for pour les passagers aléatoire et le passagers controller
						{
							randomnum = rand()%10+1;
							Passagers_Func(&TablePassNord_X[a],&TablePassNord_Y[a],&TablePassSud_X[a],&TablePassSud_Y[a],&Passagers[a],randomnum,z,&x,&y);
						}


						for(a =  RandomPassStay_1 ; a <= randomnum_2; a++) // boucle for pour le passagers dans le train qui sors et ceux qui reste
						{

							PassagersNord_TrainFunc(&TablePassTrainNord_X[a],&TablePassTrainNord_Y[a],&PassagersNord_Train[a],WagonMaxNord[a],WagonMinNord[a],PorteGoalNord[a],z);

						}

						printf("\033[%d;%dH%s\n",Table_X[1],Table_Y[1],Train2);
						printf("\033[%d;%dH%s\n",Table_X[2],Table_Y[2],Train3);


						for(a =  RandomPassStay_2; a <= randomnum_3;a++) // boucle for pour les passagers dans le train sors et ceux qui reste
						{
							PassagersSud_TrainFunc(&TablePassTrainSud_X[a],&TablePassTrainSud_Y[a],&PassagersSud_Train[a],WagonMaxSud[a],WagonMinSud[a],PorteGoalSud[a],z);
						}

						printf("\033[%d;%dH%s \n",Table_X[5],Table_Y[5],Train2);
						printf("\033[%d;%dH%s \n",Table_X[6],Table_Y[6],Train3);

						if(compteur == 0 && x>=8 && x<=9)//au cas ou si on s'arrete en plein milieu entre le train et les bordures
						{
							x = x+2;
							printf("\033[%d;%dH ",x-2,y);
						}
						if(compteur ==0 && x >= 6 && x<= 7)//au cas ou si on s'arrete en plein milieu entre le train et les bordures
						{
							x = x-2;
							printf("\033[%d;%dH%c",x,y,pass);
							printf("\033[%d;%dH ",x+2,y);
							if(x+2 == 7)
							{
								printf("\033[%d;%dH=",x+2,y);
							}


						}


						if(PassPauseNord == 2) // if si les 2 passagers vont se prepare a prendre le train
						{
							for(a = 0;a<2;a++)
							{
								printf("\033[%d;%dH ",TablePassNordIn_X[a],TablePassNordIn_Y[a]);
								TablePassNordIn_X[a] = TablePassPauseNord1_X[a];
								TablePassNordIn_Y[a] = TablePassPauseNord_Y[a];
								printf("\033[%d;%dH%c",TablePassNordIn_X[a],TablePassNordIn_Y[a],PassagersIn[a]);
								printf("\033[%d;%dH ",TablePassNordIn_X[a],TablePassNordIn_Y[a]);


							}
							TablePassNordIn_X[0] = 10;
							TablePassNordIn_X[1] = 11;
							TablePassNordIn_Y[0] = 56;
							TablePassNordIn_Y[1] = 56;
							printf("\033[%d;%dH%c",TablePassNordIn_X[0],TablePassNordIn_Y[0],PassagersIn[0]);
							printf("\033[%d:%dH%c",TablePassNordIn_X[1],TablePassNordIn_Y[1],PassagersIn[1]);

						}
						if(PassPauseSud == 2)
						{
							for(a = 0;a<2;a++)
							{
								printf("\033[%d;%dH ",TablePassSudIn_X[a],TablePassSudIn_Y[a]);
								TablePassSudIn_X[a] = TablePassPauseSud1_X[a];
								TablePassSudIn_Y[a] = TablePassPauseSud_Y[a];
								printf("\033[%d;%dH%c",TablePassSudIn_X[a],TablePassSudIn_Y[a],PassagersIn[a]);
								printf("\033[%d;%dH ",TablePassSudIn_X[a],TablePassSudIn_Y[a]);


							}
							TablePassSudIn_X[0] = 26;
							TablePassSudIn_X[1] = 27;
							TablePassSudIn_Y[0] = 67;
							TablePassSudIn_Y[1] = 67;
							printf("\033[%d;%dH%c",TablePassSudIn_X[0],TablePassSudIn_Y[0],PassagersIn[0]);
							printf("\033[%d:%dH%c",TablePassSudIn_X[1],TablePassSudIn_Y[1],PassagersIn[1]);
							CompteurBreakPass = 0;

						}


						stopwatch(1);	







					}


					randomnum_2 = RandomPassStay_1;
					randomnum_3 = RandomPassStay_2;
					z =-45;



				}



				else if(Table_Y[0] == 80) // cas ou le train va disparaitre
				{
					Table_Y[0] = 178;
					Table_Y[1] = 179;
					Table_Y[2] = 179;
					Table_Y[3] = 178;

					if(x >= 10 && x <= 11)
					{
						x = 2;
						y = 81;
					}


					for (i =101;i>0;i--) // effacement du train
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

					for(compteur=9;compteur>=0;compteur--) // compteur pour les prochaine train qui arrive
					{
						printf("\033[%d;%dH%d\n",POSARRET_X+3,POSARRET_Y+3,compteur);

						printf("\033[%d;%dH\n",POSRESET_X,POSRESET_Y);
						stopwatch(1);
						for(a = 0; a < j; a++)
						{
							randomnum = rand()%10+1;
							Passagers_Func(&TablePassNord_X[a],&TablePassNord_Y[a],&TablePassSud_X[a],&TablePassSud_Y[a],&Passagers[a],randomnum,z,&x,&y);
						}
						for(a=0;a<NumCheckPosition;a++)
						{
							CheckPosition(&TablePassNord_X[a],&TablePassNord_Y[a],&TablePassNordIn_X[a],&TablePassSudIn_X[a]);
							CheckPosition(&TablePassNord_X[a],&TablePassNord_Y[a],&x,&y);
							CheckPosition(&TablePassNordIn_X[a],&TablePassNordIn_Y[a],&x,&y);
						}
						for(a = 0; a < j; a++)
						{
							randomnum = rand()%10+1;
							Passagers_Func(&TablePassNord_X[a],&TablePassNord_Y[a],&TablePassSud_X[a],&TablePassSud_Y[a],&Passagers[a],randomnum,z,&x,&y);
						}






					}
					// Reset du tableau
					Table_Y[0] = 2;
					Table_Y[1] = 1;
					Table_Y[2] = 1;
					Table_Y[3] = 2;
					Table_Y[4] = 79;
					Table_Y[5] = 78;
					Table_Y[6] = 78;
					Table_Y[7] = 79;
					e = 1;//reset les passagers train

					for(i=0;i<6;i++) // boucle for qui reprend les ancienne valeur
					{
						TablePassTrainNord_X[i] = CTablePassTrainNord_X[i];
						TablePassTrainNord_Y[i] = CTablePassTrainNord_Y[i];
						TablePassTrainSud_X[i] = CTablePassTrainSud_X[i];
						TablePassTrainSud_Y[i] = CTablePassTrainSud_Y[i];
					}

					if(PassPauseNord == 2 && TablePassNordIn_X[0] >=9 && TablePassNordIn_X[0] <= 12) // boucle for pour que les passagers reset leur positions
					{
						for(i=0;i<2;i++)
						{
							TablePassNordIn_X[i] = CTablePassNordIn_X[i];
							TablePassNordIn_Y[i] = CTablePassNordIn_Y[i];
						}
						PassPauseNord = PassPauseNord- 2;	
					}

					if(PassPauseSud == 2 && TablePassSudIn_X[0] >= 25 && TablePassSudIn_X[0] <= 28)
					{
						for(i=0;i<2;i++)
						{
							TablePassSudIn_X[i] = CTablePassSudIn_X[i];
							TablePassSudIn_Y[i] = CTablePassSudIn_Y[i];
						}
						PassPauseSud = PassPauseSud - 2;
					}





				}





				else 
				{
					b++;//pour les passagers aléatoire
					c++;//pour les passagers -> train
					z++;//variable pour l'arret du train

					if(e == 1 ) // condition lorsque les passagers qui sors du train puissent reset le nombre
					{
						RandomPassStay_1 = rand()%2+1;
						RandomPassStay_2 = rand()%2+1;
						randomnum_2 = rand()%5+2;
						randomnum_3 = rand()%5+2;
						memset(PassagersNord_Train,0,randomnum_2*sizeof(int));
						memset(PassagersSud_Train,0,randomnum_3*sizeof(int));

						for(i=0; i<randomnum_2; i++)
						{
							PassagersNord_Train[i]= '*';
						}
						for(i=0; i<randomnum_3;i++)
						{
							PassagersSud_Train[i]= '*';
						}


						e = 0;

					}

					// Deplacement du train des 2 sens
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


					if(x >=9) // c'est ici que je vais délimiter le train pour le passagers controller qui rentre dedans // pourvoir resortir du train //
					{
						y++;
						printf("\033[%d;%dH%c",x,y,pass);

						if(x == 9)
						{
							x = x+1;

						}
						if(x == 12)
						{
							x = x-1;
						}

						for(a=0; a < 3; a++)
						{
							if(y == WagonMin_Y[a] -1)
							{
								y = y+2;


							}
							else if(y == WagonMax_Y[a] + 2)
							{
								y = y-2;
							}
						}
						printf("\033[%d;%dH%c",x,y,pass);

					}
					if(TablePassNordIn_X[0] >= 9 && TablePassNordIn_X[0] <= 12) // Deplacement du passagers qui rentre vers la droite
					{
						for(a = 0; a<2;a++)
						{
							TablePassNordIn_Y[a] = TablePassNordIn_Y[a] + 1;
							printf("\033[%d;%dH%c",TablePassNordIn_X[a],TablePassNordIn_Y[a],PassagersIn[a]);
						}

					}
					if(TablePassSudIn_X[0] <= 28 && TablePassNordIn_X[0] >= 25)
					{
						for(a = 0; a<2;a++)
						{
							TablePassSudIn_Y[a] = TablePassSudIn_Y[a] - 1;
							printf("\033[%d;%dH%c",TablePassSudIn_X[a],TablePassSudIn_Y[a],PassagersIn[a]);
						}
					}




					if(j == RandomNum_Pass) // condition afin de limite les nombre de passagers qui rentre dedans

					{
						b=21;

					}
					if(h == RandomNumIn_Pass)
					{
						c = 21;
					}	

					for(a = 0; a < j; a++)
					{

						randomnum = rand()%10+1;
						Passagers_Func(&TablePassNord_X[a],&TablePassNord_Y[a],&TablePassSud_X[a],&TablePassSud_Y[a],&Passagers[a],randomnum,z,&x,&y);

					}
					for(a=0;a<NumCheckPosition;a++)
					{
						CheckPosition(&TablePassNord_X[a],&TablePassNord_Y[a],&TablePassNordIn_X[a],&TablePassSudIn_X[a]);
						CheckPosition(&TablePassNord_X[a],&TablePassNord_Y[a],&x,&y);
						CheckPosition(&TablePassNordIn_X[a],&TablePassNordIn_Y[a],&x,&y);
					}
					for(a = PassPauseNord; a < h; a++)
					{
						RandomNumIn = rand()%10+1;
						PassagersInTrain(&TablePassNordIn_X[a],&TablePassNordIn_Y[a],&PassagersIn[a],RandomNumIn);

					}

					if(CompteurBreakPass == 1 ) // afin d'eviter un conflit avec le passagers qui va vers le train et  qui avance lorsque le train demarre
					{
						for(a = PassPauseSud; a < h; a++)
						{
							RandomNumIn = rand()%10+1;
							PassagersInTrainSud(&TablePassSudIn_X[a],&TablePassSudIn_Y[a],&PassagersIn[a],RandomNumIn);
						}
					}

					for(a = 0; a < randomnum_2; a++)
					{
						PassagersNord_TrainFunc(&TablePassTrainNord_X[a],&TablePassTrainNord_Y[a],&PassagersNord_Train[a],WagonMaxNord[a],WagonMinNord[a],PorteGoalNord[a],z);
					}

					for(a = 0; a < randomnum_3;a++)
					{
						PassagersSud_TrainFunc(&TablePassTrainSud_X[a],&TablePassTrainSud_Y[a],&PassagersSud_Train[a],WagonMaxSud[a],WagonMinSud[a],PorteGoalSud[a],z);
					}






					if(b == 20) // pour 20 mouvement le prochain il apparait
					{
						j = j+1;
						b=0;
					}

					if(c == 10)
					{
						h = h+1;
						c = 0;
					}	


					for(a=0; a < 3; a++)//incrémenter la limite des Y pour le passagers controlé
					{
						WagonMin_Y[a] = WagonMin_Y[a] + 1;
						WagonMax_Y[a] = WagonMax_Y[a] + 1;
					}

					stopwatch(0.2);


					//Partie Passagers vers le train

					for(a=0;a<2;a++) // le deplacement du passagers qui va vers le train
					{
						if(TablePassNordIn_X[a] <=10)
						{
							if(TablePassNordIn_Y[a] >= 58)
							{
								printf("\033[%d;%dH ",TablePassNordIn_X[a],TablePassNordIn_Y[a]);
								TablePassNordIn_X[a] = 6;
								TablePassNordIn_Y[a] = 56 - PassPauseStop[0];
								PassPauseNord = PassPauseNord +1;
								printf("\033[%d;%dH%c",TablePassNordIn_X[a],TablePassNordIn_Y[a],PassagersIn[a]);
								PassPauseStop[0] = PassPauseStop[0] + 1;
							}



						}	

						if(TablePassSudIn_X[a] >= 29)
						{
							if(TablePassSudIn_Y[a] >= 69)
							{

								printf("\033[%d;%dH ",TablePassSudIn_X[a],TablePassSudIn_Y[a]);
								TablePassSudIn_X[a] = 31;
								TablePassSudIn_Y[a] = 67 - PassPauseStop[3];
								PassPauseSud = PassPauseSud +1;
								printf("\033[%d;%dH%c",TablePassSudIn_X[a],TablePassSudIn_Y[a],PassagersIn[a]);
								PassPauseStop[3] = PassPauseStop[3] + 1;
							}



						}



					}









				}		


			}	
			break;

		case(2):
			{
				// Train sans passagers
				Train();
				break;
			}

	}		

}






