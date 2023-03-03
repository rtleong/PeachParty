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
					int m, n;                                                             //bugs, when hitting diretional square from lef tto down, peach doesnt turn to the right
					getPositionInThisDirection(right, 16, m, n);							//peach when going up and facing left, doesnt turn right
					if (getWorld()->validPos(m, n)) {										//maybe just updating directional square so she faces right will fix this
						setDirection(right);
						walkingDirection = right;
					}
					int s, v;
					getPositionInThisDirection(left, 16, s, v);
					if (getWorld()->validPos(s, v)) {
						setDirection(left);
						walkingDirection = left;
					}
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

void PlayerActor::takeStar() {
	stars--;
}

void PlayerActor::takeMultipleStars(int n) {
	if (stars < n) {
		stars -= stars;
	}
	else {
		stars -= n;
	}
}

void PlayerActor::addMultipleStars(int n) {
	stars += n;
}
void PlayerActor::swapTicks() {
	int peachTicks = getWorld()->getPeach()->checkTicks();
	getWorld()->getPeach()->ticks_to_move = getWorld()->getYoshi()->ticks_to_move;
	getWorld()->getYoshi()->ticks_to_move = peachTicks;
}

void PlayerActor::swapWalkingDirection() {
	int peachWalkDirection = getWorld()->getPeach()->checkDirection();
	getWorld()->getPeach()->walkingDirection = getWorld()->getYoshi()->walkingDirection;
	getWorld()->getYoshi()->walkingDirection = peachWalkDirection;
}


void PlayerActor::swapWalkingState() {
	int peachWalkState = getWorld()->getPeach()->checkRollStatus();
	getWorld()->getPeach()->waitingtoroll = getWorld()->getYoshi()->waitingtoroll;
	getWorld()->getYoshi()->waitingtoroll = peachWalkState;
}

void PlayerActor::swapCoins() {
	int tempPeachCoins = getWorld()->getPeach()->checkCoins();
	int tempYoshiCoins = getWorld()->getYoshi()->checkCoins();

	getWorld()->getPeach()->takeCoinsfromActor(getWorld()->getPeach()->checkCoins());
	getWorld()->getPeach()->giveCoinstoActor(tempYoshiCoins);

	getWorld()->getYoshi()->takeCoinsfromActor(getWorld()->getYoshi()->checkCoins());
	getWorld()->getYoshi()->giveCoinstoActor(tempPeachCoins);
}

void PlayerActor::swapStars() {
	int tempPeachStars = getWorld()->getPeach()->checkStars();
	int tempYoshiStars = getWorld()->getYoshi()->checkStars();

	getWorld()->getPeach()->takeMultipleStars((getWorld()->getPeach()->checkStars()));
	getWorld()->getPeach()->addMultipleStars(tempYoshiStars); //add stars 

	getWorld()->getYoshi()->takeMultipleStars(getWorld()->getYoshi()->checkStars());
	getWorld()->getYoshi()->addMultipleStars(tempPeachStars);
}

void PlayerActor::swapPositions() {
	int peachX = getWorld()->getPeach()->getX(); int peachY = getWorld()->getPeach()->getY();
	int peachSpriteDirection = getWorld()->getPeach()->getDirection(); //makes temp variables for yoshi and peaches location and sprite direction
	int yoshiX = getWorld()->getYoshi()->getX(); int yoshiY = getWorld()->getYoshi()->getY();
	int yoshiSpriteDirection = getWorld()->getYoshi()->getDirection();

	getWorld()->getPeach()->moveTo(yoshiX, yoshiY);
	getWorld()->getPeach()->setDirection(yoshiSpriteDirection); //swaps peach and yoshi
	getWorld()->getYoshi()->moveTo(peachX, peachY);
	getWorld()->getYoshi()->setDirection(peachSpriteDirection);
	swapTicks();  //swaps ticks, walking direction, and walking/waiting to roll state
	swapWalkingDirection();
	swapWalkingState();
}

void PlayerActor::teleportToRandomSquare() {
	/*int x = randInt(0, 15);
	int y = randInt(0, 15);

	if (getWorld()->validPos(x, y))*/
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
		if (getSpriteDirection() == right) {
			getWorld()->getPeach()->setWalking(right);
			getWorld()->getPeach()->setDirection(right);
		}
		else if (getSpriteDirection() == up) {
			getWorld()->getPeach()->setWalking(up);
			getWorld()->getPeach()->setDirection(right);
		}
		else if (getSpriteDirection() == left) {
			getWorld()->getPeach()->setWalking(left);
			getWorld()->getPeach()->setDirection(left);
		}
		else {
			getWorld()->getPeach()->setWalking(down);
			getWorld()->getPeach()->setDirection(right);
		}
	}
	if (getWorld()->intersecting(this, getWorld()->getYoshi())) {
		if (getSpriteDirection() == right) {
			getWorld()->getYoshi()->setWalking(right);
			getWorld()->getYoshi()->setDirection(right);
		}
		else if (getSpriteDirection() == up) {
			getWorld()->getYoshi()->setWalking(up);
			getWorld()->getYoshi()->setDirection(right);
		}
		else if (getSpriteDirection() == left) {
			getWorld()->getYoshi()->setWalking(left);
			getWorld()->getYoshi()->setDirection(left);
		}
		else {
			getWorld()->getYoshi()->setWalking(down);
			getWorld()->getYoshi()->setDirection(right);
		}
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
	if (!(getWorld()->intersecting(this, getWorld()->getYoshi()))) { //if not intersecting bank square not active 
		yoshi_activated = false;
	}
	if (yoshi_activated) {
		return;
	}
	if (getWorld()->intersecting(this, getWorld()->getYoshi()) && getWorld()->getYoshi()->checkRollStatus() == true) { //if intersecting bank square
		getWorld()->getYoshi()->giveCoinstoActor(getWorld()->getBankCoins());
		getWorld()->setBankBalanceToZero();
		getWorld()->playSound(SOUND_WITHDRAW_BANK);
		yoshi_activated = true;
	}
	else if (getWorld()->intersecting(this, getWorld()->getYoshi()) && getWorld()->getYoshi()->checkRollStatus() == false) {
		if (getWorld()->getYoshi()->checkCoins() >= 5) {
			getWorld()->getYoshi()->takeCoinsfromActor(5);
			getWorld()->addCoinstoBank(5);
			getWorld()->playSound(SOUND_DEPOSIT_BANK);
		}
		else {
			getWorld()->getYoshi()->takeCoinsfromActor(getWorld()->getYoshi()->checkCoins());
			getWorld()->addCoinstoBank(getWorld()->getYoshi()->checkCoins());
			getWorld()->playSound(SOUND_DEPOSIT_BANK);
		}
	}
}


void EventSquare::doSomething() {
	if (!(getWorld()->intersecting(this, getWorld()->getPeach()))) { //if not intersecting bank square not active 
		peach_activated = false;
	}
	if (peach_activated) {
		return;
	}
	if (getWorld()->intersecting(this, getWorld()->getPeach()) && getWorld()->getPeach()->checkRollStatus() == true) {
		int x;
		x = randInt(1, 2);
		if (x == 1) {
			//teleport
			getWorld()->playSound(SOUND_PLAYER_TELEPORT);
		}
		if (x == 2) {
			getWorld()->getPeach()->swapPositions(); //will this work if I just pass in peach?? I think so... maybe not...
			getWorld()->playSound(SOUND_PLAYER_TELEPORT);
		}
		if (x == 3) {
			//give vortex
		}
	}
}

void DroppingSquare::doSomething() { //havent tested dropping square check when we finally do bowser...
	if (!(getWorld()->intersecting(this, getWorld()->getPeach()))) { //if not intersecting bank square not active 
		peach_activated = false;
	}
	if (peach_activated) {
		return;
	}
	if (getWorld()->intersecting(this, getWorld()->getPeach()) && getWorld()->getPeach()->checkRollStatus() == true) {
		int r;
		r = randInt(1, 2);
		if (r == 1) {
			if (getWorld()->getPeach()->checkCoins() >= 10) {
				getWorld()->getPeach()->takeCoinsfromActor(10);
				getWorld()->playSound(SOUND_DROPPING_SQUARE_ACTIVATE);
				peach_activated = true;
			}
			if (peach_activated = true) return; //if 1st condition is true dont keep taking coins until 0

			if (getWorld()->getPeach()->checkCoins() < 10) {
				getWorld()->getPeach()->takeCoinsfromActor(getWorld()->getPeach()->checkCoins());
				getWorld()->playSound(SOUND_DROPPING_SQUARE_ACTIVATE);
				peach_activated = true;
			}
		}
		if (r == 2) {
			if (getWorld()->getPeach()->checkStars() >= 1) {
				getWorld()->getPeach()->takeStar();
				getWorld()->playSound(SOUND_DROPPING_SQUARE_ACTIVATE);
				peach_activated = true;
			}
		}
	}
	if (!(getWorld()->intersecting(this, getWorld()->getYoshi()))) { //if not intersecting bank square not active 
		yoshi_activated = false;
	}
	if (yoshi_activated) {
		return;
	}
	if (getWorld()->intersecting(this, getWorld()->getYoshi()) && getWorld()->getYoshi()->checkRollStatus() == true) {
		int j;
		j = randInt(1, 2);
		if (j == 1) {
			if (getWorld()->getYoshi()->checkCoins() >= 10) {
				getWorld()->getYoshi()->takeCoinsfromActor(10);
				getWorld()->playSound(SOUND_DROPPING_SQUARE_ACTIVATE);
				yoshi_activated = true;
			}
			if (yoshi_activated = true) return; //if 1st condition is true dont keep taking coins until 0

			if (getWorld()->getYoshi()->checkCoins() < 10) {
				getWorld()->getYoshi()->takeCoinsfromActor(getWorld()->getYoshi()->checkCoins());
				getWorld()->playSound(SOUND_DROPPING_SQUARE_ACTIVATE);
				yoshi_activated = true;
			}
		}
		if (j == 2) {
			if (getWorld()->getYoshi()->checkStars() >= 1) {
				getWorld()->getYoshi()->takeStar();
				getWorld()->playSound(SOUND_DROPPING_SQUARE_ACTIVATE);
				yoshi_activated = true;
			}
		}
	}
}

void Bowser::doSomething() { //then make bowsers functionality like Boo, just added like nachen says

}

void Baddies::doSomething() { //make this boos functionality

}


