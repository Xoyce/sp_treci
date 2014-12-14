//red_pokazivac.h
//implementacija pomocu pokazivaèa
#include <iostream>
using namespace std;

struct st_CETVORKA{
	int ai, bi, ci, di;
};

struct st_KLIJENT{
	char ime[5];
	char prezime[7];
	int datum_rodjenja[3];	
	bool spol;
	st_CETVORKA cetvorka;
	st_KLIJENT *sljedeci;
};

struct st_RED{
	st_KLIJENT *front, *rear;
};

bool IS_EMPTY_Q(st_RED *red){
	if(red->front == red->rear)
		return 1;
	else return 0;
}

st_KLIJENT *FRONT_Q(st_RED *red){
	if(IS_EMPTY_Q(red)){
		cerr <<"\nRED JE PRAZNO!\n";
	}
	else{
		st_KLIJENT *klijent = red->front->sljedeci;
		return klijent;
	}
}

void EN_QUEUE_Q(st_KLIJENT *klijent, st_RED *red){
	st_KLIJENT *novi = new st_KLIJENT;
	novi = klijent;
	red->rear->sljedeci = novi;
	red->rear= novi;
}

void DE_QUEUE_Q(st_RED *red){
	if(IS_EMPTY_Q(red))
		cerr << "\nRED JE PRAZAN!\n";
	else{
		st_KLIJENT *temp = new st_KLIJENT;
		temp = red->front;
		red->front = red->front->sljedeci;
		delete temp;
	}
}

void INIT_Q(st_RED *red){
	st_KLIJENT *glava = new st_KLIJENT;
	red->front = glava;
	red->rear = red->front;
}
