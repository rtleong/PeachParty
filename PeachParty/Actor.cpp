#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

void Peach::playerMove(double x1, double y1) {
	if (getWorld()->validPos(x1, y1)) {
		moveTo(x1, y1);
	}
	ticks_to_move--;
	if (ticks_to_move == 0)
		waitToRoll();
}

void Peach::doSomething() {
	if (checkRollStatus() == true) { //rollStatus and waitingtoroll is not working
		
		if (getWorld()->getAction(getPlayerNumber()) == ACTION_ROLL) { //this is the problem
			int die_roll = randInt(1, 10);
			ticks_to_move = die_roll * 8;
			startWalking();
			
		}
	else return;
	}
	else if (checkRollStatus() == false) { //if Walking
		int x, y;
		getPositionInThisDirection(getWalking(), 16, x, y); //return side and walking direction with member variables 
		if ((x % 16 == 0 && y % 16 == 0) && !(getWorld()->validPos(x, y))) {
			if (walkingDirection == right || walkingDirection == left) {
				int a, b;
				//std::cerr << "NOW here\n";
				getPositionInThisDirection(up, 16, a, b);
				if (getWorld()->validPos(a, b)) {
					setDirection(right);
					walkingDirection = up;
					std::cerr << "NOW here\n";
					std::cerr << "here\n";
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
				if (walkingDirection == up){
					setDirection(left);
					walkingDirection = left;
				}
			}
		}
		else {
			moveAtAngle(walkingDirection, 2);
			/*if (walkingDirection = right) {
				playerMove(getX() + 2, getY());
			}
			else if (walkingDirection = up) {
				playerMove(getX(), getY() + 2);
			}
			else if (walkingDirection = left) {
				playerMove(getX() - 2, getY());
			}
			else {
				playerMove(getX(), getY() - 2);
			}*/
			/*ticks_to_move--;
			if (ticks_to_move == 0)
				waitToRoll();*/
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