#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

//void Peach::playerMove(double x1, double y1) {
//	if (getWorld->validPos(x1, y1)) {
//		moveTo(x1, y1);
//	}
//}

void Peach::doSomething() {
	if (checkRollStatus()) {
		int key{};
		if (getWorld()->getAction(key)) {
			switch (key)//get Action returns an int, so the cases need to be ints
			{
			case ACTION_NONE:
				break;
			case ACTION_LEFT:
				//change player direction to left, check if valid
				break;
			case ACTION_UP:
				//change player direction to up, check if valid OOHH CREATE HELPER FUNCTION THAT CHECKS VALIDITY
				break;
			case ACTION_RIGHT:
				//right
				break;
			case ACTION_DOWN:
				//down
				break;
			case ACTION_ROLL:
				die_roll = randInt(1, 10); //gives random int from 1 to 10 inclusive 
				ticks_to_move = die_roll * 8; //ticks to move is 8 times die roll
				isWalking(); //change avatars state to walking
				break;
			case ACTION_FIRE:
				//add vortex object in front of player
				break;
			default:
				break;
			}
			return;

		}
	}
	//continue with step 2 below
	if (checkRollStatus()) { //if walking, move as spec indicates
	//	if () {
		{
		}


	}
				//if avatar is in walking state
					//if avatar cant move forward in current direction, update avatars walk direction so it 
					//can turn a new direction perpendicular to the current walking direction
}

void CoinSquare::doSomething() {
	if (!isActivated()) {
		return;
	}
	else {

	}
}