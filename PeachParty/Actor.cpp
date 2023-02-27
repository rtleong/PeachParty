#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

void PlayerActor::playerMove() {
	moveAtAngle(walkingDirection, 2); //move two pixels in desired direction
	ticks_to_move--;
	if (ticks_to_move == 0) {
		waitToRoll();
	}
}

void PlayerActor::doSomething() {
	if (checkRollStatus() == true) { //if waiting to roll
		if (getWorld()->getAction(getPlayerNumber()) == ACTION_ROLL) { //and tab is hit
			int die_roll = randInt(1, 10); //walk a random number of steps
			ticks_to_move = die_roll * 8;
			startWalking();
			
		}
	else return;
	}
	else if (checkRollStatus() == false) { //if Walking
		
		int x, y;
		getPositionInThisDirection(getWalking(), 16, x, y); //check every position for validity in direction + 16
		if ((x % 16 == 0 && y % 16 == 0) && !(getWorld()->validPos(x, y))) {
			if (walkingDirection == right || walkingDirection == left) {
				int a, b;
				getPositionInThisDirection(up, 16, a, b); //check 90* for validity
				if (getWorld()->validPos(a, b)) {
					setDirection(right);
					walkingDirection = up; //change direction to move up
				}
				else {
					int e, f;
					getPositionInThisDirection(down, 16, e, f); //check 270* for validity
					if (getWorld()->validPos(e, f)) {
						setDirection(right);
						walkingDirection = down;
					}
					else {
						if (walkingDirection == right) { //if only way is left, go left
							setDirection(left);
							walkingDirection = left;
						}
						else {
							setDirection(right); //if going down and hit bottom, go right
							walkingDirection = right;
						}
					}
				}
			}
			else {
				if (walkingDirection == up){ //if going up and hit top, go left
					setDirection(left);
					walkingDirection = left;
				}
				if (walkingDirection == down) { //if walking down go right
					//if valid direction right move right, if valid left move left
					int g, h;                                                             //bugs, when hitting diretional square from lef tto down, peach doesnt turn to the right
					getPositionInThisDirection(right, 16, g, h);							//peach when going up and facing left, doesnt turn right
					if (getWorld()->validPos(g, h)) {										//maybe just updating directional square so she faces right will fix this
						setDirection(right);
						walkingDirection = right;
					}
					int j, k;
					getPositionInThisDirection(left, 16, j, k);
					if (getWorld()->validPos(j, k)) {
						setDirection(left);
						walkingDirection = left;
					}
				}
			}
		}
		else {
			playerMove(); //move if all positions are valid
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
	if (coins < n) {
		coins -= coins;
	}
	else {
		coins -= n;
	}
}

void PlayerActor::giveStar() {
	stars++;
}

void CoinSquare::doSomething() {
	if (!isActivated()) { //if not activated bc of bowser return
		return;
	}
	if (!(getWorld()->intersecting(this, getWorld()->getPeach())) || getWorld()->getPeach()->checkRollStatus() == false) {
		peach_activated = false;//if peach is walking dont activate
	}
	else {
		if (peach_activated) {
			return;
		}
		if (giveColor() == true) { //if color is blue add coins
			getWorld()->getPeach()->giveCoinstoActor(3);
			getWorld()->playSound(SOUND_GIVE_COIN);
			//std::cerr << getWorld()->getPeach()->checkCoins();
			peach_activated = true;
		}
		if (giveColor() == false) { //if color is red subtract coins
			getWorld()->getPeach()->takeCoinsfromActor(3);
			getWorld()->playSound(SOUND_TAKE_COIN);
			peach_activated = true;
		}
	}
	if (!(getWorld()->intersecting(this, getWorld()->getYoshi())) || getWorld()->getYoshi()->checkRollStatus() == false) {
		yoshi_activated = false; //set yoshi to not activate squares if walking
	}
	else {
		if (yoshi_activated) {
			return;
		}
		if (giveColor() == true) { //if square is blue give yoshi 3 coins
			getWorld()->getYoshi()->giveCoinstoActor(3);
			getWorld()->playSound(SOUND_GIVE_COIN);
			yoshi_activated = true;
		}
		if (giveColor() == false) {//if square is red take away 3 coins
			getWorld()->getYoshi()->takeCoinsfromActor(3);
			getWorld()->playSound(SOUND_TAKE_COIN);
			yoshi_activated = true;
		}
	}
}

void StarSquare::doSomething() {
	if (!(getWorld()->intersecting(this, getWorld()->getPeach()))) { //if not intersecting star square not active 
		peach_activated = false;
	}
	if (peach_activated) {
		return;
	}
	if (getWorld()->intersecting(this, getWorld()->getPeach())) { //if intersecting star square
		peach_activated = true;
		if (getWorld()->getPeach()->checkRollStatus() == false || getWorld()->getPeach()->checkRollStatus() == true){
			if (getWorld()->getPeach()->checkCoins() < 20) { //running over or landing on give star
				return;
			}
			else {
				getWorld()->getPeach()->takeCoinsfromActor(20); //take coins and give star
				getWorld()->getPeach()->giveStar();
				getWorld()->playSound(SOUND_GIVE_STAR);
				//std::cerr << getWorld()->getPeach()->checkStars();
				//peach_activated = true;
			}
		}
	}
	if (!(getWorld()->intersecting(this, getWorld()->getYoshi()))) { //if not intersecting set false
		yoshi_activated = false;
	}
	if (yoshi_activated) { //return if actor landed on square (dont keep giving stars)
		return;
	}
	if (getWorld()->intersecting(this, getWorld()->getYoshi())) { //if runs over or lands on square
		yoshi_activated = true;
		if (getWorld()->getYoshi()->checkRollStatus() == false || getWorld()->getYoshi()->checkRollStatus() == true) {
			if (getWorld()->getYoshi()->checkCoins() < 20) {
				return;
			}
			else {
				getWorld()->getYoshi()->takeCoinsfromActor(20); //give 20 coins and get a star.
				getWorld()->getYoshi()->giveStar();
				getWorld()->playSound(SOUND_GIVE_STAR);
			//	std::cerr << getWorld()->getYoshi()->checkStars();
			}
		}
	}
}

void DirectionalSquare::doSomething() {
	if (getWorld()->intersecting(this, getWorld()->getPeach())) {
		if (getSpriteDirection() == right)
			getWorld()->getPeach()->setWalking(right);
		else if (getSpriteDirection() == up)
			getWorld()->getPeach()->setWalking(up);
		else if (getSpriteDirection() == left)
			getWorld()->getPeach()->setWalking(left);
		else if (getSpriteDirection() == down)
			getWorld()->getPeach()->setWalking(down);
	}
}

void PlayerActor::setWalking(int n) {
	walkingDirection = n;
}

void BankSquare::doSomething() {
	if (!(getWorld()->intersecting(this, getWorld()->getPeach()))) { //if not intersecting bank square not active 
		peach_activated = false;
	}
	if (peach_activated) {
		return;
	}
	if (getWorld()->intersecting(this, getWorld()->getPeach()) && getWorld()->getPeach()->checkRollStatus() == true) { //if intersecting bank square
		getWorld()->getPeach()->giveCoinstoActor(getWorld()->getBankCoins());
		getWorld()->setBankBalanceToZero();
		getWorld()->playSound(SOUND_WITHDRAW_BANK);
		peach_activated = true;
	}
	else if (getWorld()->intersecting(this, getWorld()->getPeach()) && getWorld()->getPeach()->checkRollStatus() == false) {
		if (getWorld()->getPeach()->checkCoins() >= 5) {
			getWorld()->getPeach()->takeCoinsfromActor(5);
			getWorld()->addCoinstoBank(5);
			getWorld()->playSound(SOUND_DEPOSIT_BANK);
		}
		else {
			getWorld()->getPeach()->takeCoinsfromActor(getWorld()->getPeach()->checkCoins());
			getWorld()->addCoinstoBank(getWorld()->getPeach()->checkCoins());
			getWorld()->playSound(SOUND_DEPOSIT_BANK);
		}
	}
	
}


