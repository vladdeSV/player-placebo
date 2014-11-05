#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "Helper.h"
#include "Missions.h"

//Snabbkopiering av frågefunktion
/**

 switch (getInput()) {
 case YES:

 break;
 case NO:

 break;
 case UNKNOWN:

 break;
 }

 */

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
	cout << endl << "<PRESS ANY BUTTON TO START>" << endl << endl;
	system("pause");
	start();
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void start() {
/*
	say("Welcome to:\nPLAYER PLACEBO - THE RIPOFF", 2);
	say("Chapter 1:", 2);
	say("The Hotel", 4);

	say("You walk in to the hotel,\nup to the guy in a very nice suit.\nHe looks at you.", 3);
	say(suitguy, "And who might you be?", 2); */
	say("<Please enter your name>");
	getName();
	say(name, "My name is " + name + ".", 2);
	say(suitguy, "Welcome " + name + ".", 1);
	askWantRoom();
}

void askWantRoom() {
	say(suitguy, "Would you like to rent a room?", 0);
	switch (getInput()) {
	case YES:
		say(name, returnSaying, 2);
		say(suitguy, "Nice, please follow the roomer.", 2);
		followRoomer();
		break;
	case NO:
		say(name, returnSaying, 2);
		say(suitguy, "Then why would you even go here?", 2);
		loose();
		break;
	case UNKNOWN:
		say("As you gurgle words with no meaning, the man in the suit brings up his shotgun and murders you.", 4);
		loose();
		break;
	}
}

void followRoomer() {
	say("Are you going to follow the roomer?");

	switch (getInput()) {
	case YES:
		goToRoom();
		break;
	case NO:
		say("You stand still, doing nothing\nBoth the man in suit and the roomer looks at you.", 4);
		say(suitguy, "Do you not wish a room?", 2);
		wishRoom();
		break;
	case UNKNOWN:
		say("...I'll take that as a no?", 4);
		loose();
		break;
	}

}

void wishRoom() {
	switch (getInput()) {
	case YES:
		say(name, "Sorry, yes please.", 2);
		say(suitguy, "Then please follow the roomer.", 2);
		goToRoom();
		break;
	case NO:
		say(name, returnSaying, 2);
		say("The man in suit and the roomer gets mad at you and kills you", 4);
		loose();
		break;
	case UNKNOWN:
		say(name, "Of course, please forgive me for my rudeness.", 2);
		goToRoom();
		break;
	}
}

void goToRoom() {
	say("You follow the roomer to your room", 2);
	say("When you get to your room you notice that the room is dirty, the bedsheets are dirty and it smells weird.", 4);
	say("Are you going to complain?");
	switch (getInput()) {
	case YES:
		say(name, "Excuse me, but this room is shit. I want another one.", 2);
		say(roomleader, "Well screw you.", 2);
		loose();
		break;
	case NO:
		say(name, "Thank you.", 1);
		say(roomleader, "No, thank YOU for not complaining.\nAs the first customer to not complain\nyou will get to stay for free and get free breakfast.", 4);
		win();
		break;
	case UNKNOWN:
		say("Anka-chan is love, Anka-chan is life");
		win();
		break;
	}
}

void win() {
	say("You win the game you just lost.", 5);
}
