#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

void Peach::playerMove(double x1, double y1) {
	if (getWorld()->validPos(x1, y1)) {
		moveTo(x1, y1);
	}
}

void Peach::doSomething() {
	if (rollStatus == waitingtoroll) {
		if (getWorld()->getAction(getPlayerNumber()) == ACTION_ROLL) {
			int die_roll = randInt(1, 10);
			ticks_to_move = die_roll * 8;
			rollStatus = walking;
		}
		else return;
	}
	else if (rollStatus == walking) {
		int x, y;
		getPositionInThisDirection(getWalking(), 16, x, y); //return side and walking direction with member variables 
		if ((x % 16 == 0 && y % 16 == 0) && !(getWorld()->validPos(x, y))) {
			if (walkingDirection == right || walkingDirection == left) {
				int a, b;
				getPositionInThisDirection(up, 16, x, y);
				if (getWorld()->validPos(a, b)) {
					setDirection(right);
					walkingDirection = up;
				}
				else {
					int e, f;
					getPositionInThisDirection(down, 16, e, f);
					if (getWorld()->validPos(e, f)) {
						setDirection(right);
						walkingDirection = down;
					}
					else {
						if (walkingDirection == right) {
							setDirection(left);
							walkingDirection = left;
						}
						else {
							setDirection(right);
							walkingDirection = right;
						}
					}
				}
			}
			else {

			}
		}
	}
}

int Peach::getPlayerNumber() {
	return player_side;
}

int Peach::getWalking() {
	return walkingDirection;
}
void CoinSquare::doSomething() {
	if (!isActivated()) {
		return;
	}
	else {

	}
}