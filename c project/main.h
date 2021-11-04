#ifndef __Train_h__
#define __Train_h__


void purge ();
void stopwatch(float temps);
int gennum_pass();
void Train();
void PassagersNord_TrainFunc(int *TablePassTrainNord_X,int *TablePassTrainNord_Y,char *PassagersNord_Train,int WagonMaxNord,int WagonMinNord,int PorteGoalNord,int z);
void PassagersSud_TrainFunc(int *TablePassTrainSud_X,int *TablePassTrainSud_Y,char *PassagersSud_Train,int WagonMaxSud,int WagonMinSud,int PorteGoalSud,int z);
void CheckPosition(int *Pass1_X,int *Pass1_Y,int *Pass2_X,int *Pass2_Y);
void PassagersInTrain(int *TablePassNordIn_X,int *TablePassNordIn_Y,char *PassagersIn,int RandomNumIn);
void PassagersInTrainSud(int *TablePassSudIn_X,int *TablePassSudIn_Y,char *PassagersIn,int RandomNumIn);
void Passagers_Func(int *TablePassNord_X,int *TablePassNord_Y,int *TablePassSud_X,int *TablePassSud_Y,char *Passagers,int randomnum,int z,int *x,int *y);
char key_pressed();

#endif
