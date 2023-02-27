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
	Actor(StudentWorld* world, int imageID, double startX, double startY, int startDirection, int depth) 
		: GraphObject(imageID, startX, startY, startDirection, depth), m_world(world) {};
	virtual void doSomething() = 0;
	StudentWorld* getWorld() { return m_world; };

private:
	StudentWorld* m_world;
};

/*
		Alive Actors that MOVE: PlayerActor, Yoshi, Boo, Bowser
*/
class AliveActor : public Actor //Actors -> alive actors 
{
public:
	AliveActor(StudentWorld* world, int imageID, double startX, double startY, int startDirection, int depth) //took out imageID after world
		: Actor(world, imageID, startX, startY, startDirection, depth), activate(true) {}; //and here too
	bool isActivated() { return activate; } //used to indicate if bowser, boo, etc are activated 
	virtual void reActivate() { activate = true; }
	virtual void deactivate() { activate = false; }
	virtual void doSomething() = 0;
private:
	bool activate;
};

class PlayerActor : public AliveActor //main actors ->  PlayerActor
{
public:
	PlayerActor(StudentWorld* world, int imageID, int boardX, int boardY, int playerNumber)
		: AliveActor(world, imageID, SPRITE_WIDTH* boardX, SPRITE_HEIGHT* boardY, right, 0), waitingtoroll(true), walkingDirection(right), m_num(playerNumber)
	, coins(0), stars(0) {}; // m_num(playerNumber) {};//right initializes peach with starting direction of right

	virtual void doSomething();
	//accessors
	int checkCoins() { return coins; }
	int checkStars() { return stars; }
	//movement
	int getPlayerNumber();
	bool checkRollStatus() { return waitingtoroll; }
	void waitToRoll() { waitingtoroll = true; }
	void startWalking() { waitingtoroll = false; }
	int getWalking();
	void setWalking(int n);

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
};

class CoinSquare : public AliveActor {
public:
	CoinSquare(StudentWorld* world, int imageID, double startX, double startY, bool color) //activate is false when initialized
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
	StarSquare(StudentWorld* world, double startX, double startY) :
		AliveActor(world, IID_STAR_SQUARE, startX * SPRITE_WIDTH, startY * SPRITE_HEIGHT, right, 1) {};
	void doSomething();
private:
	bool peach_activated;
	bool yoshi_activated;
};

class DirectionalSquare : public AliveActor {
public:
	DirectionalSquare(StudentWorld *world, double startX, double startY, int spriteDirection) : //a forcing direction should be the same as a sprite direction
		AliveActor(world, IID_DIR_SQUARE, startX* SPRITE_WIDTH, startY* SPRITE_HEIGHT, spriteDirection, 1), 
		theSpriteDirection(spriteDirection) {};
	int getSpriteDirection() { return theSpriteDirection; }
	void doSomething();
private:
	int theSpriteDirection;
};

class BankSquare : public AliveActor {
public:
	BankSquare(StudentWorld* world, double startX, double startY) :
		AliveActor(world, IID_BANK_SQUARE, startX* SPRITE_WIDTH, startY* SPRITE_HEIGHT, right, 1) {};
	void doSomething();
private:
	bool peach_activated;
	bool yoshi_activated;
};

class EventSquare : public AliveActor {
public:
	EventSquare(StudentWorld* world, double startX, double startY) 
		: AliveActor(world, IID_EVENT_SQUARE, startX* SPRITE_WIDTH, startY* SPRITE_HEIGHT, right, 1) {};
	void doSomething();
private:
	bool peach_activated;
	bool yoshi_activated;
};

class DroppingSquare : public AliveActor {
public:
	DroppingSquare(StudentWorld* world, double startX, double startY) //have to have bowser activate or something? Bowser passes in x and y?
		: AliveActor(world, IID_DROPPING_SQUARE, startX* SPRITE_WIDTH, startY* SPRITE_HEIGHT, right, 1) {};
	void doSomething();
private:
	bool peach_activated;
	bool yoshi_activated;
};

class Baddies : public AliveActor //Actor --> AliveActor --> Baddies
{
public:

private:

};

class Boo : public Baddies //Baddies --> Boo 
{
public:

private:

};

class Bowser : public Baddies //Baddies --> Bowser
{
public:

private:

};

/*
		Actors that DO NOT MOVE and are on the board
*/


//class DirectionalSquare : public //BoardActor
//{
//public:
//
//private:
//
//};
//
//class BankSquare : public //BoardActor
//{
//public:
//
//private:
//
//};
//
//class EventSquare : public BoardActor
//{
//public:
//
//private:
//
//};
//
//class DroppingSquare : public BoardActor
//{
//public:
//
//private:
//
//};

#endif // ACTOR_H_
