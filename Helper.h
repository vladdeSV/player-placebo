#include <cctype>
#include <ctime>
#include <iostream>
#include <string>

#include "Missions.h"
#include "Functions.h"

using namespace std;

#ifndef HELPER_H_
#define HELPER_H_

const int UNKNOWN = 0, YES = 1, NO = 2;																//Konstanta ord som används i switch funktioner i "player placebo - the ripoff.cpp"


//ASSÅ VA SCHÖEN, DEN TAR DET FÖRSTA ORDET OCH KOLLAR ANTALET BOKSTÄVER. ?!?!?!?!?! VA SHCÖEN! OKEJ TYP FIXAT NU!
const string EMOTION_POSITIVE[] = { "yes", "ofc", "sure", "ok", "fine" };
const string EMOTION_NEGATIVE[] = { "no", "never", "die", "qwerty", "asdf" };						//Konstanta känslo-ord i form utav string[]

string name, suitguy = "Man in suit", roomleader = "Roomer";										//Namn som anänds lite här och var
string returnSaying;																				//En string som ändras av makeSentence(), villket bara sätter punkt och stor bokstav.



void waitSeconds(clock_t seconds) { 	//En funktion som får programmet att stanna i "seconds" antal sekunder.

	if (seconds > 0) {										//Kollar om "seconds" är större än 0, så inte detta körs i onödan
		clock_t start_time = clock();						//Gör en ny variabel som sätts till nuvarande tiden
		clock_t end_time = start_time + (seconds * 1000);	//En ny variabel där slut-tiden blir start tiden plus antalet mille-"seconds" * 1000, så det blir sekunder

		while (clock() < end_time)
			//En while loop som gör ingentin tills nuvarande tiden blir större än "end_time"
			;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void checkFeels(string s, int* f, const string EMOTION[]) {	//En funktion som tar den sagda meningen och kollar efter känslo-ord i en string[], i detta fall antingen EMOTIONS_POSITIVE/NEGATIVE, och lägger till antalet positiva/negativa ord i yes- och noCount.

	//DETTA ÄR CHEAP, DÅ DET BARA LOOPAR IGENOM 5 ORD OCH DET MÅSTE FINNAS LIKA MÅNGA POSITIVA SOM NEGATIVA ORD! HJÄLP MIG MARTIN!
	for (int i = 0; i < 5; i++) {					//Loopar igenom 5 känslo-ord i EMOTION[].
		if (s.find(EMOTION[i]) != string::npos) {				//Kollar efter känslo-ord i meningen, i detta fall "s".
			*f += 1;											//Om ett känslo-ord finns, lägg till det i *f, som motsvarar yes- eller noCount som finns i getInput()
		}
	}
}

int yesno(int yesCount, int noCount) {		//Simpel funktion som kollar villkea känslo-ord det finns mest av.
	if (yesCount > noCount) return YES;			//Om det finns mer positiva ord än negativa, ge tillbaka YES, som tidigare definerats som 1
	else if (noCount > yesCount) return NO;		//Om det finns mer negativa ord än positiva, ge tillbaka NO, som tidigare definerats som 2
	else return UNKNOWN;						//Om det finns lika många positiva som negativa ord (eller inga alls), ge tillbaka UNKNOWN, som tidigare definerats som 0
}

void makeSentence() {	//Funktion som tar den skrivna meningen och gör om den så den får stor bokstav i början och får punkt på slutet.
	int nl;					//Variabel som står för 'number letter'

	for (nl = 0; nl < returnSaying.size(); nl++)		//Loop som gör alla bokstäver små.
		returnSaying[nl] = tolower(returnSaying[nl]);
	nl--; //Detta är en cheap lösning på varför nedastående gav ett substring out of bounds. Anledning, tror jag, är att när ovanstående körts fördigt så är "nl" "returnSaying.size() + 1" basically.
	
	if (returnSaying[nl] != '.' || returnSaying[nl] != '!' || returnSaying[nl] != '?') {	//När ovanstående loop är färdig så sätts "nl" till "returnSaying.size()", och då kollar det om sista bokstaven inte är en punkt, utropstecken eller frågetecken.
		returnSaying += ".";						//Om sista bokstaven inte var en punkt så sätts det dit en punkt. Hela denna är till för om det redan finns en punkt så ska det inte sättas dit en till
	}
	returnSaying[0] = toupper(returnSaying[0]);			//Gör första bokstaven stor
}

int getInput() { //En funktion som tar in en mening och avgör om det ska betyda ja eller nej
	cout << endl;				//Ny rad för läsbarhetens skull
	string sentence;			//En ny variabel som kommer att bli en mening
	getline(cin, sentence);		//En funktion som tar in en mening. "getline()" används för att kunna få med mellanslag.

	returnSaying = sentence;	//Sätter "returnSaying" till den skrivna meningen.
	makeSentence();				//Gör en bra mening

	for (int l = 0; l < sentence.size(); l++) {		//Går igenom alla bokstäver och gör alla bokstäver små
		sentence[l] = tolower(sentence[l]);
	}

	paskagg(sentence);	//Tar meningen och kollar efter påskägg ;)

	int yesCount = 0, noCount = 0;	//Variabler som senare kommer hålla antalet positiva och negativa ord det finns i meningen
	int* yes = &yesCount;			//En pointer till "yesCount"
	int* no = &noCount;				//En pointer till "noCount"

	checkFeels(sentence, yes, EMOTION_POSITIVE);	//Kollar antalet positiva ord, och lägger sedan till antalet till "yesCount"
	checkFeels(sentence, no, EMOTION_NEGATIVE);		// -''- fast negativa ord och "noCount"

	return yesno(yesCount, noCount);	//Ger tillbaka antingen YES, NO eller UNKNOWN som motsvarar 1, 2 och 0 respektive.
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void say(string message) {			//Funktion som ändast skriver ut ett meddelande på en ny enskilld rad
	cout << endl << message << endl;	//Skriver ut meddelandet
}

void say(string message, int delay) {	//Funktion som ändast skriver ut ett meddelande på en ny enskilld rad, och sedan väntar antalet sekunder som anges via "delay"
	cout << endl << message << endl;		//Skriver ut meddelandet
	waitSeconds(delay);						//Väntar antalet sekunder
}

void say(string name, string message, int delay) {	//Funktion som tar ett string som ska motsvara ett namn, skriver ut "namn: mening" på enskilld rad, och sedan väntar antalet sekunder som anges via "delay". En delay måste anges vid talad mening, eftersom läsaren måste ha tid att läsa vad personen säger
	cout << endl << name << ": " << message << endl;	//Skriver ut namnet, sedan ett kolon, och sist meningen
	waitSeconds(delay);									//Väntar antalet sekunder
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void getName() {
	//cin.ignore();
	getline(cin, name);								//Ber användaren att skriva in sitt namn. "getline()" används för att kunna få med mellanslag.
	if(name != ""){
		for (int l = 0; l < name.size(); l++) {

			name[l] = tolower(name[l]);					//Gör alla bokstäver små

			if (isspace(name.at(l))) {
				name[l + 1] = toupper(name[l + 1]);		//Går igenom alla bokstäver och kollar om det finns några mellanslag och sedan gör alla separerade ords första bokstav stor
				l++;
			}
		}
		name[0] = toupper(name[0]); 					//Gör första bokstaven stor
	}else{
		say(suitguy, "What was your name?", 1);
		getName();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loose() {		//Simpel funktion som används när spelaren förlorar
	say("You loose.", 4);	//Skriver ut att man har förlorat i fyra sekunder
	say("Play again?");
	if(getInput() == 1) start();

}

void paskagg(string s) {	//Simpel funktion som kollar om meningen innehåller några hemliga ord ;)
	if (s.find("anka") != string::npos) {
		cout << endl << "\tAnka-chan is love, Anka-chan is life." << endl;
	}
	if (s.find("the game") != string::npos) {
		cout << endl << "\tYou just lost the game." << endl;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif /* HELPER_H_ */
