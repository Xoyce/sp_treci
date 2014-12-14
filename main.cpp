#include <iostream>
#include <cstdlib>
#include "unistd.h"
#include <ctime>
#include <cstring>
//#include "red_pokazivac.h"
#include "red_polje.h"

#define _gg 2
#define _mm 1
#define _dd 0

using namespace std;

st_KLIJENT funk_generator_osoba(st_KLIJENT *osoba){

    static const char num[] = "123456789";
    char alfa[][3] = {"da", "ka", "ra", "ma", "an", "lo", "re", "pe", "jo", "zo", "ja", "za", "ro", "te", "to", "vo", "no", "tr", "rl", "na", "nj", "pr", "dr", "va", "un", "il", "el", "im"};
    //ime
    for (int i = 0; i < 4; i+=2) {
        int k = rand() % (28 - 1);
        osoba->ime[i] = alfa[k][0];
        osoba->ime[i+1] = alfa[k][1];
    }
    osoba->ime[0] = (int)osoba->ime[0] - 32;
    osoba->ime[4] = '\0';
    //prezime
    for (int i = 0; i < 4; i+=2) {
        int k = rand() % (28 - 1);
        osoba->prezime[i] = alfa[k][0];
        osoba->prezime[i+1] = alfa[k][1];
    }
    osoba->prezime[0] = (int)osoba->prezime[0] - 32;
    osoba->prezime[4] = 'i';
    osoba->prezime[5] = 'c';
    osoba->prezime[6] = '\0';
    //spol
    if(rand()%(3-1)+1 == 1)
        osoba->spol = 1;
    else if(rand()%(3-1)+1 == 2){
        osoba->spol = 0;
        osoba->ime[3] = 'a';
    }
       
    //datum_rodjenja
    osoba->datum_rodjenja[_dd]=rand()%(31-1)+1;
    osoba->datum_rodjenja[_mm]=rand()%(12-1)+1;
    osoba->datum_rodjenja[_gg]=rand()%(1993-1900)+1900;
   
}

void funk_A(int N, st_CETVORKA *cetvorke){
	srand(time(NULL));
	int ai, bi, ci, di;
	st_CETVORKA cetvorka;
	for(int i = 0; i < N; i++){	
		ai = rand()%491+10;
		bi = rand()%721+80;
		ci = rand()%5+1; 
		di = rand()%5+1;
		cetvorka.ai = ai;
		cetvorka.bi = bi;
		cetvorka.ci = ci;
		cetvorka.di = di; 
		cetvorke[i] = cetvorka;
	}
}

void funk_B(st_RED *red, int N, st_CETVORKA *cetvorke){
	st_KLIJENT *klijent = new st_KLIJENT;
	st_KLIJENT klijenti[N*5];
	cout << "Klijenti koji cekaju na uplatu lutrije, a po horoskopu su 'Jarac' i mladji su od 40 godina:\n";
	for(int i,j = 0; i<N*5; i++){
		if(i%5 == 0 && i!=0)j++;
		funk_generator_osoba(klijent);
		if(cetvorke[j].ci == 3) klijent->spol = 0;
		klijent->cetvorka = cetvorke[j];
		klijenti[i] = *klijent;
		EN_QUEUE_Q(klijent, red);
		sleep((klijent->cetvorka.ai+klijent->cetvorka.bi)/1000);
		if(klijent->datum_rodjenja[_mm] == 1 && klijent->datum_rodjenja[_gg]>1974 && klijent->spol == 1)
		cout<< "-----------------------------------------------\n"
			<< "Ime: " << klijent->ime << endl
			<< "Prezime: " << klijent->prezime << endl
			<< "Datum rodjenja: " << klijent->datum_rodjenja[_dd] << "." << klijent->datum_rodjenja[_mm] << "." << klijent->datum_rodjenja[_gg] << ".\n"
			<< "-----------------------------------------------\n";
	}
}
	
void funk_C(st_RED *red){
	bool ima = 0;
	st_RED *pomocni_red = new st_RED;
	INIT_Q(pomocni_red);
	while(!IS_EMPTY_Q(red)){
		if(not(FRONT_Q(red)->cetvorka.ci == 3 && FRONT_Q(red)->cetvorka.di == 5)){
			EN_QUEUE_Q(FRONT_Q(red), pomocni_red);
			DE_QUEUE_Q(red);
		}
		else{
			if(!ima)cout << "Trudnice koje 'oce EvoTV:\n";
			ima = 1;
			cout<< "-----------------------------------------------\n"
				<< "Ime: " << FRONT_Q(red)->ime << endl
				<< "Prezime: " << FRONT_Q(red)->prezime << endl
				<< "Datum rodjenja: " << FRONT_Q(red)->datum_rodjenja[_dd] << "." << FRONT_Q(red)->datum_rodjenja[_mm] << "." << FRONT_Q(red)->datum_rodjenja[_gg] << ".\n"
				<< "Kategorija: " << FRONT_Q(red)->cetvorka.ci << endl
				<< "Trazena usluga: " << FRONT_Q(red)->cetvorka.di<< endl
				<< "-----------------------------------------------\n";
			DE_QUEUE_Q(red);
		}
						
	}
	if(!ima)cout << "Nema trudnica koje 'oce EvoTV!\n";	
	cout << "ISPIS GLAVNOG REDA:"<<endl;
	while(!IS_EMPTY_Q(pomocni_red)){		
		cout<< "-----------------------------------------------\n"
		<< "Ime: " << FRONT_Q(pomocni_red)->ime << endl
		<< "Prezime: " << FRONT_Q(pomocni_red)->prezime << endl
		<< "Spol: " << FRONT_Q(pomocni_red)->spol << endl
		<< "Datum rodjenja: " << FRONT_Q(pomocni_red)->datum_rodjenja[_dd] << "." << FRONT_Q(red)->datum_rodjenja[_mm] << "." << FRONT_Q(red)->datum_rodjenja[_gg] << ".\n"
		<< "Kategorija: " << FRONT_Q(red)->cetvorka.ci << endl
		<< "Trazena usluga: " << FRONT_Q(red)->cetvorka.di<< endl
		<< "-----------------------------------------------\n";
		EN_QUEUE_Q(FRONT_Q(pomocni_red), red);
		DE_QUEUE_Q(pomocni_red);
	}
}

int main(){
	st_RED *red = new st_RED;
	st_RED *brzi = new st_RED;
	INIT_Q(red);
	INIT_Q(brzi);
	int N;
	cout << "Unesi N: ";
	cin >> N;
	st_CETVORKA cetvorke[N];
	funk_A(N, cetvorke);
	funk_B(red, N, cetvorke);
	funk_C(red);
	return 0;	
}
