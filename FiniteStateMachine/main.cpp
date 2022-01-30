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

enum class EmotionalState
{
	CALM, ALERT, AGITATED, HAPPY, SURPRISED, ANGRY
};

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

EmotionalState es = EmotionalState::CALM;

void switchState(EmotionalState newState)
{
	es = newState;
}

int main()
{
	bool program_running = true;

	std::cout << "Starting Finite State Machine... Press ESC key to close." << endl;

	do
	{
		/*

		Write your code here for the finite state machine example

		*/

		switch (es)
		{
			// S0
			case EmotionalState::CALM:
			{
				std::cout << "Currently CALM, nothing is happening...\n";

				// a
				if (hearsNoise && !someoneNear)
				{
					std::cout << "Heard noise but no one is near, switching to ALERT state...\n";

					// move to ALERT state
					switchState(EmotionalState::ALERT);
				}
				else if (seesAnother)		// c
				{
					std::cout << "Seen another, switching to AGITATED state...\n";

					// move to AGITATED state
					switchState(EmotionalState::AGITATED);
				}

				// Priority goes to the more specific AND conditions
				if (isFriendly && makesJoke)	// f
				{
					std::cout << "Other is friendly AND they make a joke, switching to HAPPY state...\n";

					// move to HAPPY state
					switchState(EmotionalState::HAPPY);
				}

				break;
			}
			// S1
			case EmotionalState::ALERT:
			{
				std::cout << "Currently ALERT, listening to noise...\n";

				// b
				if (!hearsNoise)
				{
					std::cout << "Noise stopped, switching to CALM state...\n";

					// Reset all vocab conditions to defaults
					resetVocabConditions();
					switchState(EmotionalState::CALM);
				}

				break;
			}
			// S2
			case EmotionalState::AGITATED:
			{
				std::cout << "Currently AGITATED...\n";

				// d
				if (isFriendly)
				{
					std::cout << "Other is friendly, switching to CALM state...\n";

					// Dont reset conditions, as we need to be able to recognise that other was friendly
					// in order to move from CALM to HAPPY

					// move to CALM state
					switchState(EmotionalState::CALM);
				}
				else if (movesAway)		// h
				{
					std::cout << "Other is moving away, switching to CALM state...\n";

					// Reset all vocab conditions to defaults
					resetVocabConditions();
					// move to CALM state
					switchState(EmotionalState::CALM);
				}

				// e
				if (isAggressive)
				{
					std::cout << "Other is agrressive, switching to SURPRISED state...\n";

					// move to SURPRISED state
					switchState(EmotionalState::SURPRISED);
				}
				
				break;
			}
			// S3, S4, S5
			case EmotionalState::SURPRISED:
			{
				std::cout << "Currently SURPRISED...\n";

				// e & g, Priority goes to more specific AND conditions
				if (isAggressive && attacks) // g
				{
					std::cout << "Other is agrressive AND attacks, switching to ANGRY state...\n";

					// move to ANGRY state
					switchState(EmotionalState::ANGRY);
				}

				// h, then singular conditions
				if (movesAway)
				{
					std::cout << "Other moves away, switching to CALM state...\n";

					// Reset all vocab conditions to defaults
					resetVocabConditions();
					// move to CALM state
					switchState(EmotionalState::CALM);
				}

				break;
			}
			// S4, S5
			case EmotionalState::HAPPY: case EmotionalState::ANGRY:
			{
				std::cout << "Currently HAPPY OR ANGRY...\n";

				// h, then singular conditions
				if (movesAway)
				{
					std::cout << "Other moves away, switching to CALM state...\n";

					// Reset all vocab conditions to defaults
					resetVocabConditions();
					// move to CALM state
					switchState(EmotionalState::CALM);
				}

				break;
			}
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
	}
	while (program_running);

	cout << "Ending Finite State Machine..." << endl;

	return 0;
}