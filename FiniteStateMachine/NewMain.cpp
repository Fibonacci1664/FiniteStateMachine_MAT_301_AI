/*
*	INPUT VOCABULARY
*
*	a = If NPC hears noise & no one else is around
*	b = If noise stops & nothing else happens
*	c = If NPC sees another character
*	d = If other character appears friendly
*	e = If other character acts aggressively
*	f = If other character is friendly & makes a joke
*	g = If other character is aggressive & attacks
*	h = If other character moves away
*
*/

#include <iostream>		
#include <thread>	 
#include <chrono>
#include <conio.h>
#include <map>
#include "BaseState.h"
#include "Calm.h"
#include "Alert.h"
#include "Agitated.h"
#include "Surprised.h"
#include "Happy.h"
#include "Angry.h"

using namespace std;			// cout, endl
using namespace this_thread;	// sleep_for
using namespace chrono;			// seconds, milliseconds

bool hearsNoise = false;		// a
bool someoneNear = false;		// a or b
bool seesAnother = false;		// c
bool isFriendly = false;		// d
bool isAggressive = false;		// e
bool makesJoke = false;			// f
bool attacks = false;			// g
bool movesAway = false;			// h

std::map<std::string, BaseState*> states;

Calm* calmState = new Calm;
Alert* alertState = new Alert;
Agitated* agitatedState = new Agitated;
Surprised* surprisedState = new Surprised;
Happy* happyState = new Happy;
Angry* angryState = new Angry;
BaseState* currentState = nullptr;

void initStatesMap()
{
	// Populate map
	states.emplace(std::make_pair("calm", calmState));
	states.emplace(std::make_pair("alert", alertState));
	states.emplace(std::make_pair("agitated", agitatedState));
	states.emplace(std::make_pair("surprised", surprisedState));
	states.emplace(std::make_pair("happy", happyState));
	states.emplace(std::make_pair("angry", angryState));

	// Assign default state
	currentState = calmState;
}

void printVocabConditions()
{
	std::cout << "Hears Noise = " << hearsNoise << '\n';
	std::cout << "Someone Near = " << someoneNear << '\n';
	std::cout << "Sees Another = " << seesAnother << '\n';
	std::cout << "Is Friendly = " << isFriendly << '\n';
	std::cout << "Is Agressive = " << isAggressive << '\n';
	std::cout << "Makes Joke = " << makesJoke << '\n';
	std::cout << "Attacks = " << attacks << '\n';
	std::cout << "Moves Away = " << movesAway << '\n';
}

void resetVocabConditions()
{
	hearsNoise = false;
	someoneNear = false;
	seesAnother = false;
	isFriendly = false;
	isAggressive = false;
	makesJoke = false;
	attacks = false;
	movesAway = false;
}

void switchState(std::string newState)
{
	currentState->onExit();
	currentState = states[newState];
	currentState->onEnter();
}

void checkCalm()
{
	// a
	if (hearsNoise && !someoneNear)
	{
		std::cout << "Heard noise but no one is near, switching state...\n";

		// move to ALERT state
		switchState("alert");
	}
	else if (seesAnother)		// c
	{
		std::cout << "Seen another, switching state...\n";

		// move to AGITATED state
		switchState("agitated");
	}

	// Priority goes to the more specific AND conditions
	if (isFriendly && makesJoke)	// f
	{
		std::cout << "Other is friendly AND they make a joke, switching state...\n";

		// move to HAPPY state
		switchState("happy");
	}
}

void checkAlert()
{
	// b
	if (!hearsNoise)
	{
		std::cout << "Noise stopped, switching state...\n";

		// Reset all vocab conditions to defaults
		resetVocabConditions();

		// Switch to CALM state
		switchState("calm");
	}
}

void checkAgitated()
{
	// d
	if (isFriendly)
	{
		std::cout << "Other is friendly, switching state...\n";

		// Dont reset conditions, as we need to be able to recognise that other was friendly
		// in order to move from CALM to HAPPY

		// move to CALM state
		switchState("calm");
	}
	else if (movesAway)		// h
	{
		std::cout << "Other is moving away, switching state...\n";

		// Reset all vocab conditions to defaults
		resetVocabConditions();
		// move to CALM state
		switchState("calm");
	}

	// e
	if (isAggressive)
	{
		std::cout << "Other is agrressive, switching state...\n";

		// move to SURPRISED state
		switchState("surprised");
	}
}

void checkSurprised()
{
	// e & g, Priority goes to more specific AND conditions
	if (isAggressive && attacks) // g
	{
		std::cout << "Other is agrressive AND attacks, switching state...\n";

		// move to ANGRY state
		switchState("angry");
	}

	// h, then singular conditions
	if (movesAway)
	{
		std::cout << "Other moves away, switching state...\n";

		// Reset all vocab conditions to defaults
		resetVocabConditions();
		// move to CALM state
		switchState("calm");
	}
}

void checkHappyAngry()
{
	// h, then singular conditions
	if (movesAway)
	{
		std::cout << "Other moves away, switching state...\n";

		// Reset all vocab conditions to defaults
		resetVocabConditions();
		// move to CALM state
		switchState("calm");
	}
}

int main()
{
	bool program_running = true;

	std::cout << "Starting Finite State Machine... Press ESC key to close." << endl;

	initStatesMap();

	do
	{
		/*

		Write your code here for the finite state machine example

		*/

		currentState->run();
		
		if (currentState == calmState)
		{
			checkCalm();
		}
		else if (currentState == alertState)
		{
			checkAlert();
		}
		else if (currentState == agitatedState)
		{
			checkAgitated();
		}
		else if (currentState == surprisedState)
		{
			checkSurprised();
		}
		else if (currentState == happyState || currentState == angryState)
		{
			checkHappyAngry();
		}

		// Sleep the current thread for 1000 milliseconds. Can be repalce with seconds(1)
		sleep_for(milliseconds(1000));

		if (_kbhit())
		{
			char input_char = _getch();

			// Check for ESC key. See table here http://www.asciitable.com/
			if (input_char == 27)
			{
				program_running = false;
			}

			// 'p'
			if (input_char == 112)
			{
				printVocabConditions();
			}

			// 'r'
			if (input_char == 114)
			{
				resetVocabConditions();
			}

			// 'a'
			if (input_char == 97 && !hearsNoise)
			{
				hearsNoise = true;
				continue;
			}
			if (input_char == 97 && hearsNoise)
			{
				hearsNoise = false;
				continue;
			}

			// 'b'
			if (input_char == 98)
			{
				// Manually stop the 'noise'
				hearsNoise = false;
				continue;
			}

			// 'c'
			if (input_char == 99 && !seesAnother)
			{
				seesAnother = true;
				continue;
			}
			if (input_char == 99 && seesAnother)
			{
				seesAnother = false;
				continue;
			}

			// None of these conditions should be able to trigger unless we have 'seen' someone
				// 'd'
			if (input_char == 100 && !isFriendly && seesAnother)
			{
				isFriendly = true;
				continue;
			}
			if (input_char == 100 && isFriendly)
			{
				isFriendly = false;
				continue;
			}

			// 'e'
			if (input_char == 101 && !isAggressive && seesAnother)
			{
				isAggressive = true;
				continue;
			}
			if (input_char == 101 && isAggressive)
			{
				isAggressive = false;
				continue;
			}

			// 'f'
			if (input_char == 102 && !makesJoke && seesAnother)
			{
				makesJoke = true;
				continue;
			}
			if (input_char == 102 && makesJoke)
			{
				makesJoke = false;
				continue;
			}

			// 'g'
			if (input_char == 103 && !attacks && seesAnother)
			{
				attacks = true;
				continue;
			}
			if (input_char == 103 && attacks)
			{
				attacks = false;
				continue;
			}

			// 'h'
			if (input_char == 104 && !movesAway && seesAnother)
			{
				movesAway = true;
				continue;
			}
			if (input_char == 104 && movesAway)
			{
				movesAway = false;
				continue;
			}
		}
	} while (program_running);

	cout << "Ending Finite State Machine..." << endl;

	return 0;
}