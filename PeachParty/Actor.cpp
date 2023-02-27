#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

void PlayerActor::playerMove() {
	moveAtAngle(walkingDirection, 2);
	ticks_to_move--;
	if (ticks_to_move == 0) {
		waitToRoll();
	}
}

void PlayerActor::doSomething() {
	if (checkRollStatus() == true) { //rollStatus and waitingtoroll is not working
		if (getWorld()->getAction(getPlayerNumber()) == ACTION_ROLL) { //this is the problem fix hardcoded 1
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
				getPositionInThisDirection(up, 16, a, b);
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
				if (walkingDirection == up){
					setDirection(left);
					walkingDirection = left;
				}
				if (walkingDirection == down) {
					setDirection(right);
					walkingDirection = right;
				}
			}
		}
		else {
			playerMove();
		}
	}
}

int PlayerActor::getPlayerNumber() {
	return m_num;
}

int PlayerActor::getWalking() {
	return walkingDirection;
}

void PlayerActor::giveCoinstoActor(int n) {
	coins += n;
}

void PlayerActor::takeCoinsfromActor(int n) {
	coins -= n;
}

void CoinSquare::doSomething() {
	if (!isActivated()) {
		return;
	}
	if (!(getWorld()->intersecting(this, getWorld()->getPeach())) || getWorld()->getPeach()->checkRollStatus() == false) {//if peach is walking dont activate, does false work?
		peach_activated = false;
	}
	else {
		if (peach_activated) {
			return;
		}
		if (giveColor() == true) {
			getWorld()->getPeach()->giveCoinstoActor(3);
			getWorld()->playSound(SOUND_GIVE_COIN);
			peach_activated = true;
		}
		if (giveColor() == false) {
			getWorld()->getPeach()->takeCoinsfromActor(3);
			getWorld()->playSound(SOUND_TAKE_COIN);
			peach_activated = true;
		}
	}
	if (!(getWorld()->intersecting(this, getWorld()->getYoshi())) || getWorld()->getYoshi()->checkRollStatus() == false) {
		yoshi_activated = false;
	}
	else {
		if (yoshi_activated) {
			return;
		}
		if (giveColor() == true) {
			getWorld()->getYoshi()->giveCoinstoActor(3);
			getWorld()->playSound(SOUND_GIVE_COIN);
			yoshi_activated = true;
		}
		if (giveColor() == false) {
			getWorld()->getYoshi()->takeCoinsfromActor(3);
			getWorld()->playSound(SOUND_TAKE_COIN);
			yoshi_activated = true;
		}
	}
}
