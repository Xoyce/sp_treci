//red_polje.h
//implementacija pomocu polja
#include <iostream>
using namespace std;

const int QUEUE_SIZE = 1000;//PARAMETAR ZA ODREÐIVANJE VELICINE POLJA

struct st_CETVORKA{
	int ai, bi, ci, di;
};

struct st_KLIJENT{
	char ime[5];
	char prezime[7];
	int datum_rodjenja[3];
	st_CETVORKA cetvorka;
	bool spol;
};

struct st_RED{
	st_KLIJENT klijent[QUEUE_SIZE];
	int front, rear, brojac;
};

bool IS_EMPTY_Q(st_RED *red){
	if(red->brojac == 0)
		return 1;
	else return 0;
}

int ADD_ONE(int n){
	return ((n+1)%QUEUE_SIZE);
}

st_KLIJENT *FRONT_Q(st_RED *red){
	if(IS_EMPTY_Q(red)){
		cerr <<"\nPOLJE JE PRAZNO!\n";
	}	
	return &(red->klijent[red->front]);
}

void EN_QUEUE_Q(st_KLIJENT *klijent, st_RED *red){
	if(QUEUE_SIZE == red->brojac)
		cerr << "\nPOLJE PUNO!\n";
	else{
		red->rear = ADD_ONE(red->rear);
		red->klijent[red->rear]= *klijent;
		red->brojac++;
	}	
}

void DE_QUEUE_Q(st_RED *red){
	if(!IS_EMPTY_Q(red)){
	red->front++;
	red->brojac--;
	}
}

void INIT_Q(st_RED *red){
	red->front = 0;
	red->brojac = 0;
	red->rear = QUEUE_SIZE-1;
}
