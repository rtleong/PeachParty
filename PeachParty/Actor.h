#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;
/*
 
 
 
 
 
 
 
			PlayerActor
	Alive Actor
Actor		Baddies
			Coin Square
	

*/




class Actor : public GraphObject
{
public:
	Actor(StudentWorld* world, int imageID, int startX, int startY, int startDirection, double size, int depth) 
		: GraphObject(imageID, startX, startY, startDirection, depth), m_world(world) {};
	virtual void doSomething() = 0;
	StudentWorld* getWorld() { return m_world; };
	virtual bool canBeHitByVortex() const = 0;
	virtual void hitByVortex() { }
	bool isActive() const { return m_ObjectActive; }
	void setInactive() { m_ObjectActive = false; }
	void reActivate() { m_ObjectActive = true; }
	bool canWalk(int x, int y, int direction);
	bool isAtFork();
private:
	StudentWorld* m_world;
	bool m_ObjectActive = true;
};

/*
		Alive Actors that MOVE: PlayerActor, Yoshi, Boo, Bowser
*/

class PlayerActor : public Actor //main actors ->  PlayerActor
{
public:
	PlayerActor(StudentWorld* world, int imageID, int boardX, int boardY, int playerNumber)
		: Actor(world, imageID, SPRITE_WIDTH* boardX, SPRITE_HEIGHT* boardY, right, 1, 0), waitingtoroll(true), walkingDirection(right), m_num(playerNumber)
	, coins(0), stars(0) {}; // m_num(playerNumber) {};//right initializes peach with starting direction of right

	virtual void doSomething();
	//accessors
	int checkCoins() { return coins; }
	int checkStars() { return stars; }
	int checkTicks() { return ticks_to_move; }
	int checkDirection() { return walkingDirection; }
	void changeDirection(int direction) { walkingDirection = direction; if (direction == left) setDirection(180); else setDirection(0); }
	int getPlayerNumber();
	bool checkRollStatus() { return waitingtoroll; }
	int getWalking(); //gets actual walking direction
	//movement
	void waitToRoll() { waitingtoroll = true; }
	void startWalking() { waitingtoroll = false; }
	void setWalking(int n);
	void moveAtFork();
	int getAngle() { return walkingDirection; }
	bool checkIfHasVortex() { return hasAVortex; }

	//mutators
	void addMultipleStars(int n);
	void takeMultipleStars(int n);
	void swapStars();
	void swapCoins();
	void swapPositions();
	void swapTicks();
	void swapWalkingDirection();
	void swapWalkingState();
	void teleportToRandomSquare();

	bool canBeHitByVortex() const { return false; }

	//giving stuff
	void giveCoinstoActor(int n);
	void takeCoinsfromActor(int n);
	void giveStar();
	void takeStar();
	void giveVortex() { hasAVortex = true;  vortexCount++; }
	void removeVortex() { vortexCount--; if (vortexCount <= 0) hasAVortex = false; }

private:
	void playerMove();
	int stars;
	int coins;
	int walkingDirection;
	int m_num; // initialize peach as 1 and yoshi as 2
	int ticks_to_move = 0;
	bool waitingtoroll;
	bool isForked = false;
	int vortexCount = 0;
	bool hasAVortex = false;
};

class AliveActor : public Actor //Actors -> alive actors 
{
public:
	AliveActor(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth) //took out imageID after world
		: Actor(world, imageID, startX, startY, startDirection, 1, depth), activate(true) {}; //and here too
	bool isActivated() { return activate; } //used to indicate if bowser, boo, etc are activated 
	virtual void reActivate() { activate = true; }
	virtual void deactivate() { activate = false; }
	virtual void doSomething() = 0;
private:
	bool activate;
};

class Vortex : public AliveActor
{
public:
	Vortex(StudentWorld* sw, int imageID, int startX, int startY, int direction) //may need to make it DIR direction
		: AliveActor(sw, imageID, startX* SPRITE_WIDTH, startY* SPRITE_HEIGHT, 0, 0), firing_direction(direction) {}
	bool canBeHitByVortex() const { return false; }
	void doSomething();
	std::vector<Actor*> do_i_activate;
private:
	int firing_direction;
	bool isActive;
};

class CoinSquare : public AliveActor {
public:
	CoinSquare(StudentWorld* world, int imageID, int startX, int startY, bool color) //activate is false when initialized
		: AliveActor(world, imageID, startX * SPRITE_WIDTH, startY * SPRITE_HEIGHT, right, 1),
		colorOfSquare(color) {};
	virtual void doSomething();
	bool canBeHitByVortex() const { return false; }
	bool giveColor() { return colorOfSquare; }
private:
	bool colorOfSquare;
	bool peach_activated;
	bool yoshi_activated;
};

class StarSquare : public AliveActor {
public:
	StarSquare(StudentWorld* world, int imageID, int startX, int startY) :
		AliveActor(world, imageID, startX * SPRITE_WIDTH, startY * SPRITE_HEIGHT, right, 1) {};
	void doSomething();
	bool canBeHitByVortex() const { return false; }
private:
	bool peach_activated;
	bool yoshi_activated;
};

class DirectionalSquare : public AliveActor {
public:
	DirectionalSquare(StudentWorld *world, int imageID, int startX, int startY, int spriteDirection) : //a forcing direction should be the same as a sprite direction
		AliveActor(world, imageID, startX* SPRITE_WIDTH, startY* SPRITE_HEIGHT, spriteDirection, 1), 
		theSpriteDirection(spriteDirection) {};
	int getSpriteDirection() { return theSpriteDirection; }
	void doSomething();
	bool canBeHitByVortex() const { return false; }
private:
	int theSpriteDirection;
};

class BankSquare : public AliveActor {
public:
	BankSquare(StudentWorld* world, int imageID, int startX, int startY) :
		AliveActor(world, imageID, startX* SPRITE_WIDTH, startY* SPRITE_HEIGHT, right, 1) {};
	void doSomething();
	bool canBeHitByVortex() const { return false; }
private:
	bool peach_activated;
	bool yoshi_activated;
};

class EventSquare : public AliveActor {
public:
	EventSquare(StudentWorld* world, int imageID, int startX, int startY) 
		: AliveActor(world, imageID, startX* SPRITE_WIDTH, startY* SPRITE_HEIGHT, right, 1) {};
	void doSomething();
	bool canBeHitByVortex() const { return false; }
private:
	bool peach_activated;
	bool yoshi_activated;
};

class DroppingSquare : public AliveActor {
public:
	DroppingSquare(StudentWorld* world, int imageID, int startX, int startY) //have to have bowser activate or something? Bowser passes in x and y?
		: AliveActor(world, imageID, startX* SPRITE_WIDTH, startY* SPRITE_HEIGHT, right, 1) {};
	void doSomething();
	bool canBeHitByVortex() const { return false; }
private:
	bool peach_activated;
	bool yoshi_activated;
};

class Baddies : public AliveActor //Actor --> AliveActor --> Baddies
{
public:
	Baddies(StudentWorld* sw, int imageID, int startX, int startY, int dir, double size, int depth, //activate = waking or paused state
		bool activate_when_go_lands, int num_sq_to_move, int number_of_ticks_to_pause) :
		AliveActor(sw, imageID, startX, startY, dir, depth), IAmPaused(activate_when_go_lands), numberOfTicksPaused(number_of_ticks_to_pause), 
		squaresToMove(num_sq_to_move) {}			//num to move is num pixels to move
	virtual void doSomething() = 0;		//ticks to pause starts as 180 ticks until pause
	bool canBeHitByVortex() const { return true; }
	void hitByVortex() {}; //called by vortex projectile when enemy is hit with projectile
	bool checkPausedState() { return IAmPaused; }
	void decrementPauseCounter() { numberOfTicksPaused--; }
	void adjustPauseCounterto180() { numberOfTicksPaused = 180; }
	int checkPauseCounter() { return numberOfTicksPaused; }
	void adjustSquaresToMove(int n);
	int checkSquaresToMove() { return squaresToMove; }
	void adjustTicksToMove(int n);
	void decrementTicksToMove() { if (ticks_to_move <= 0) return; ticks_to_move--; }
	int returnTicksToMove() { return ticks_to_move; }

	void BaddieMove();
	void changeWalkingDirection(int n) { walkingDirection = n; }
	void moveRandomly();
	void startWalking() {IAmPaused = false; }
	void goBackToPaused() { IAmPaused = true; }
private:
	bool IAmPaused; //use to show boo starts in paused state
	int numberOfTicksPaused;
	int squaresToMove;
	int ticks_to_move = 0;
	int walkingDirection;
};

class Boo : public Baddies //Baddies --> Boo 
{
public:
	Boo(StudentWorld* sw, int imageID, int startX, int startY) 
	: Baddies(sw, imageID, startX*SPRITE_WIDTH, startY*SPRITE_HEIGHT, right, 1, 0, true, 0, 180), walkingDirection(right) {}
	void doSomething();
private:
	bool m_activatedPeach = false;
	bool m_activatedYoshi = false;
	int walkingDirection;
};

class Bowser : public Baddies //Baddies --> Bowser
{
public:
	Bowser(StudentWorld* sw, int imageID, int startX, int startY) : 
		Baddies(sw, imageID, startX*SPRITE_WIDTH, startY*SPRITE_HEIGHT, right, 1, 0, true, 0, 180), walkingDirection(right) {}
	void doSomething();
private:
	bool m_activatedPeach = false;
	bool m_activatedYoshi = false;
	int walkingDirection;
};


#endif // ACTOR_H_
