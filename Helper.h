#include <cctype>
#include <ctime>
#include <iostream>
#include <string>

#include "Missions.h"
#include "Functions.h"

using namespace std;

#ifndef HELPER_H_
#define HELPER_H_

const int UNKNOWN = 0, YES = 1, NO = 2;																//Konstanta ord som anv�nds i switch funktioner i "player placebo - the ripoff.cpp"


//ASS� VA SCH�EN, DEN TAR DET F�RSTA ORDET OCH KOLLAR ANTALET BOKST�VER. ?!?!?!?!?! VA SHC�EN! OKEJ TYP FIXAT NU!
const string EMOTION_POSITIVE[] = { "yes", "ofc", "sure", "ok", "fine" };
const string EMOTION_NEGATIVE[] = { "no", "never", "die", "qwerty", "asdf" };						//Konstanta k�nslo-ord i form utav string[]

string name, suitguy = "Man in suit", roomleader = "Roomer";										//Namn som an�nds lite h�r och var
string returnSaying;																				//En string som �ndras av makeSentence(), villket bara s�tter punkt och stor bokstav.



void waitSeconds(clock_t seconds) { 	//En funktion som f�r programmet att stanna i "seconds" antal sekunder.

	if (seconds > 0) {										//Kollar om "seconds" �r st�rre �n 0, s� inte detta k�rs i on�dan
		clock_t start_time = clock();						//G�r en ny variabel som s�tts till nuvarande tiden
		clock_t end_time = start_time + (seconds * 1000);	//En ny variabel d�r slut-tiden blir start tiden plus antalet mille-"seconds" * 1000, s� det blir sekunder

		while (clock() < end_time)
			//En while loop som g�r ingentin tills nuvarande tiden blir st�rre �n "end_time"
			;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void checkFeels(string s, int* f, const string EMOTION[]) {	//En funktion som tar den sagda meningen och kollar efter k�nslo-ord i en string[], i detta fall antingen EMOTIONS_POSITIVE/NEGATIVE, och l�gger till antalet positiva/negativa ord i yes- och noCount.

	//DETTA �R CHEAP, D� DET BARA LOOPAR IGENOM 5 ORD OCH DET M�STE FINNAS LIKA M�NGA POSITIVA SOM NEGATIVA ORD! HJ�LP MIG MARTIN!
	for (int i = 0; i < 5; i++) {					//Loopar igenom 5 k�nslo-ord i EMOTION[].
		if (s.find(EMOTION[i]) != string::npos) {				//Kollar efter k�nslo-ord i meningen, i detta fall "s".
			*f += 1;											//Om ett k�nslo-ord finns, l�gg till det i *f, som motsvarar yes- eller noCount som finns i getInput()
		}
	}
}

int yesno(int yesCount, int noCount) {		//Simpel funktion som kollar villkea k�nslo-ord det finns mest av.
	if (yesCount > noCount) return YES;			//Om det finns mer positiva ord �n negativa, ge tillbaka YES, som tidigare definerats som 1
	else if (noCount > yesCount) return NO;		//Om det finns mer negativa ord �n positiva, ge tillbaka NO, som tidigare definerats som 2
	else return UNKNOWN;						//Om det finns lika m�nga positiva som negativa ord (eller inga alls), ge tillbaka UNKNOWN, som tidigare definerats som 0
}

void makeSentence() {	//Funktion som tar den skrivna meningen och g�r om den s� den f�r stor bokstav i b�rjan och f�r punkt p� slutet.
	int nl;					//Variabel som st�r f�r 'number letter'

	for (nl = 0; nl < returnSaying.size(); nl++)		//Loop som g�r alla bokst�ver sm�.
		returnSaying[nl] = tolower(returnSaying[nl]);
	nl--; //Detta �r en cheap l�sning p� varf�r nedast�ende gav ett substring out of bounds. Anledning, tror jag, �r att n�r ovanst�ende k�rts f�rdigt s� �r "nl" "returnSaying.size() + 1" basically.
	
	if (returnSaying[nl] != '.' || returnSaying[nl] != '!' || returnSaying[nl] != '?') {	//N�r ovanst�ende loop �r f�rdig s� s�tts "nl" till "returnSaying.size()", och d� kollar det om sista bokstaven inte �r en punkt, utropstecken eller fr�getecken.
		returnSaying += ".";						//Om sista bokstaven inte var en punkt s� s�tts det dit en punkt. Hela denna �r till f�r om det redan finns en punkt s� ska det inte s�ttas dit en till
	}
	returnSaying[0] = toupper(returnSaying[0]);			//G�r f�rsta bokstaven stor
}

int getInput() { //En funktion som tar in en mening och avg�r om det ska betyda ja eller nej
	cout << endl;				//Ny rad f�r l�sbarhetens skull
	string sentence;			//En ny variabel som kommer att bli en mening
	getline(cin, sentence);		//En funktion som tar in en mening. "getline()" anv�nds f�r att kunna f� med mellanslag.

	returnSaying = sentence;	//S�tter "returnSaying" till den skrivna meningen.
	makeSentence();				//G�r en bra mening

	for (int l = 0; l < sentence.size(); l++) {		//G�r igenom alla bokst�ver och g�r alla bokst�ver sm�
		sentence[l] = tolower(sentence[l]);
	}

	paskagg(sentence);	//Tar meningen och kollar efter p�sk�gg ;)

	int yesCount = 0, noCount = 0;	//Variabler som senare kommer h�lla antalet positiva och negativa ord det finns i meningen
	int* yes = &yesCount;			//En pointer till "yesCount"
	int* no = &noCount;				//En pointer till "noCount"

	checkFeels(sentence, yes, EMOTION_POSITIVE);	//Kollar antalet positiva ord, och l�gger sedan till antalet till "yesCount"
	checkFeels(sentence, no, EMOTION_NEGATIVE);		// -''- fast negativa ord och "noCount"

	return yesno(yesCount, noCount);	//Ger tillbaka antingen YES, NO eller UNKNOWN som motsvarar 1, 2 och 0 respektive.
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void say(string message) {			//Funktion som �ndast skriver ut ett meddelande p� en ny enskilld rad
	cout << endl << message << endl;	//Skriver ut meddelandet
}

void say(string message, int delay) {	//Funktion som �ndast skriver ut ett meddelande p� en ny enskilld rad, och sedan v�ntar antalet sekunder som anges via "delay"
	cout << endl << message << endl;		//Skriver ut meddelandet
	waitSeconds(delay);						//V�ntar antalet sekunder
}

void say(string name, string message, int delay) {	//Funktion som tar ett string som ska motsvara ett namn, skriver ut "namn: mening" p� enskilld rad, och sedan v�ntar antalet sekunder som anges via "delay". En delay m�ste anges vid talad mening, eftersom l�saren m�ste ha tid att l�sa vad personen s�ger
	cout << endl << name << ": " << message << endl;	//Skriver ut namnet, sedan ett kolon, och sist meningen
	waitSeconds(delay);									//V�ntar antalet sekunder
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void getName() {
	//cin.ignore();
	getline(cin, name);								//Ber anv�ndaren att skriva in sitt namn. "getline()" anv�nds f�r att kunna f� med mellanslag.
	if(name != ""){
		for (int l = 0; l < name.size(); l++) {

			name[l] = tolower(name[l]);					//G�r alla bokst�ver sm�

			if (isspace(name.at(l))) {
				name[l + 1] = toupper(name[l + 1]);		//G�r igenom alla bokst�ver och kollar om det finns n�gra mellanslag och sedan g�r alla separerade ords f�rsta bokstav stor
				l++;
			}
		}
		name[0] = toupper(name[0]); 					//G�r f�rsta bokstaven stor
	}else{
		say(suitguy, "What was your name?", 1);
		getName();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loose() {		//Simpel funktion som anv�nds n�r spelaren f�rlorar
	say("You loose.", 4);	//Skriver ut att man har f�rlorat i fyra sekunder
	say("Play again?");
	if(getInput() == 1) start();

}

void paskagg(string s) {	//Simpel funktion som kollar om meningen inneh�ller n�gra hemliga ord ;)
	if (s.find("anka") != string::npos) {
		cout << endl << "\tAnka-chan is love, Anka-chan is life." << endl;
	}
	if (s.find("the game") != string::npos) {
		cout << endl << "\tYou just lost the game." << endl;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif /* HELPER_H_ */
