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
		: AliveActor(world, imageID, SPRITE_WIDTH* boardX, SPRITE_HEIGHT* boardY, right, 0), waitingtoroll(true), walkingDirection(right), m_num(playerNumber) {}; // m_num(playerNumber) {};//right initializes peach with starting direction of right
	virtual void doSomething();
	//accessors

	//movement
	int getPlayerNumber();
	bool checkRollStatus() { return waitingtoroll; }
	void waitToRoll() { waitingtoroll = true; }
	void startWalking() { waitingtoroll = false; }
	int getWalking();

	//giving stuff
	void giveCoinstoActor(int n);
private:
	void playerMove();
	int coins = 0;
	int walkingDirection;
	int m_num; // initialize peach as 1 and yoshi as 2
	int ticks_to_move = 0;
	bool waitingtoroll;
};

class CoinSquare : public AliveActor {
public:
	CoinSquare(StudentWorld* world, int imageID, double startX, double startY, bool color) //activate is false when initialized
		: AliveActor(world, imageID, startX * SPRITE_WIDTH, startY * SPRITE_HEIGHT, right, 1), coins(3) {};
	virtual void doSomething();
private:
	int coins;
	bool isRed = false;
	bool isBlue = true;
	bool peach_activated;
	bool yoshi_activated;
};

//class BlueCoinSquare : public CoinSquare {
//public:
//	BlueCoinSquare(StudentWorld* world, int imageID, double startX, double startY)
//		: CoinSquare(world, IID_BLUE_COIN_SQUARE, SPRITE_WIDTH * startX, SPRITE_HEIGHT * startY) {};
//	virtual void doSomething();
//private:
//	bool peach_activated;
//	bool yoshi_activated;
//};
//
//class RedCoinSquare : public CoinSquare {
//public:
//	RedCoinSquare(StudentWorld* world, double startX, double startY)
//		: CoinSquare(world, IID_RED_COIN_SQUARE, SPRITE_WIDTH* startX, SPRITE_HEIGHT* startY) {}
//	virtual void doSomething();
//private:
//
//};

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

//class BoardActor : public AliveActor
//{
//public:
//	BoardActor(StudentWorld* world, int imageID, double startX, double startY, int startDirection, int depth)
//		: AliveActor(world, imageID, startX, startY, startDirection), m_activated(true) {};
//	virtual void doSomething() = 0;
//	bool isActivated() { return m_activated; }
//	void deActivate() { m_activated = false; }
//
//private:
//	bool m_activated;
//};
//
//class CoinSquare : public BoardActor
//{
//public:
//	CoinSquare(StudentWorld* world, double startX, double startY)
//		: BoardActor(world, IID_BLUE_COIN_SQUARE, startX, startY, 0, 1) {};
//	virtual void doSomething();
//private:
//
//
//};

//class StarSquare : public //BoardActor
//{
//public:
//
//private:
//
//};
//
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
