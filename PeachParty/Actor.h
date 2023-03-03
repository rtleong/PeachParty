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

private:
	StudentWorld* m_world;
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
	int getPlayerNumber();
	bool checkRollStatus() { return waitingtoroll; }
	int getWalking(); //gets actual walking direction
	//movement
	void waitToRoll() { waitingtoroll = true; }
	void startWalking() { waitingtoroll = false; }
	void setWalking(int n);

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

	//giving stuff
	void giveCoinstoActor(int n);
	void takeCoinsfromActor(int n);
	void giveStar();
	void takeStar();
private:
	void playerMove();
	int stars;
	int coins;
	int walkingDirection;
	int m_num; // initialize peach as 1 and yoshi as 2
	int ticks_to_move = 0;
	bool waitingtoroll;
	bool isAtFork;
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

class CoinSquare : public AliveActor {
public:
	CoinSquare(StudentWorld* world, int imageID, int startX, int startY, bool color) //activate is false when initialized
		: AliveActor(world, imageID, startX * SPRITE_WIDTH, startY * SPRITE_HEIGHT, right, 1),
		colorOfSquare(color) {};
	virtual void doSomething();
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
private:
	int theSpriteDirection;
};

class BankSquare : public AliveActor {
public:
	BankSquare(StudentWorld* world, int imageID, int startX, int startY) :
		AliveActor(world, imageID, startX* SPRITE_WIDTH, startY* SPRITE_HEIGHT, right, 1) {};
	void doSomething();
private:
	bool peach_activated;
	bool yoshi_activated;
};

class EventSquare : public AliveActor {
public:
	EventSquare(StudentWorld* world, int imageID, int startX, int startY) 
		: AliveActor(world, imageID, startX* SPRITE_WIDTH, startY* SPRITE_HEIGHT, right, 1) {};
	void doSomething();
private:
	bool peach_activated;
	bool yoshi_activated;
};

class DroppingSquare : public AliveActor {
public:
	DroppingSquare(StudentWorld* world, int imageID, int startX, int startY) //have to have bowser activate or something? Bowser passes in x and y?
		: AliveActor(world, imageID, startX* SPRITE_WIDTH, startY* SPRITE_HEIGHT, right, 1) {};
	void doSomething();
private:
	bool peach_activated;
	bool yoshi_activated;
};

class Baddies : public AliveActor //Actor --> AliveActor --> Baddies
{
public:
	Baddies(StudentWorld* sw, int imageID, int startX, int startY, int dir, double size, int depth, //activate = waking or paused state
		bool activate_when_go_lands, int num_sq_to_move, int number_of_ticks_to_pause) :
	AliveActor(sw, imageID, startX, startY, dir, size) {}			//num to move is num pixels to move
	void doSomething();																				//ticks to pause starts as 180 ticks until pause
private:

};

class Boo : public Baddies //Baddies --> Boo 
{
public:
	Boo(StudentWorld* sw, int imageID, int startX, int startY) 
	: Baddies(sw, imageID, startX*SPRITE_WIDTH, startY*SPRITE_HEIGHT, right, 1, 0, false, 0, 180) {} 

private:

};

class Bowser : public Baddies //Baddies --> Bowser
{
public:
	Bowser(StudentWorld* sw, int imageID, int startX, int startY) : 
		Baddies(sw, imageID, startX*SPRITE_WIDTH, startY*SPRITE_HEIGHT, right, 1, 0, false, 0, 180) {}
	void doSomething();
private:

};


#endif // ACTOR_H_
