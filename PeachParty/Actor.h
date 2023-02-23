#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;

class Actor : public GraphObject
{
public:
	Actor(StudentWorld* world, int imageID, double startX, double startY, int startDirection, int depth) 
		: GraphObject(imageID, startX, startY, startDirection, depth), m_world(world) {};
	virtual void doSomething() = 0;
	StudentWorld* getWorld() { return m_world; }

private:
	StudentWorld* m_world;
};

/*
		Alive Actors that MOVE: Peach, Yoshi, Boo, Bowser
*/
class AliveActor : public Actor //Actors -> alive actors 
{
public:
	AliveActor(StudentWorld* world, int imageID, double startX, double startY, int startDirection)
		: Actor(world, imageID, startX, startY, startDirection, 0), activate(true) {};
	bool isActivated() { return activate; } //used to indicate if bowser, boo, etc are activated 
	bool deactivate() { activate = false; 
							return; }
	bool waitingToRoll() { return waitingtoroll; }
	bool isWalking() { waitingtoroll = false; 
	return; }
private:
	bool activate;
	bool waitingtoroll;
};

//class MainActors : public AliveActor //alive actors -> main actors  (probably will never need to be deactivated)
//{
//public:
//	MainActors(StudentWorld* world, double startX, double startY)
//		: AliveActor(world, imageID, startX, startY, startDirection, depth) {};
//private:
//
//};

class Peach : public AliveActor //main actors ->  Peach
{
public:
	Peach(StudentWorld* world, double startX, double startY)
		: AliveActor(world, IID_PEACH, SPRITE_WIDTH* startX, SPRITE_HEIGHT* startY, right) {};//right initializes peach with starting direction of right
	virtual void doSomething();
private:
	
};

class Yoshi : public AliveActor //MainActors -> Yoshi
{
public:
	Yoshi(StudentWorld* world, double startX, double startY)
		: AliveActor(world, IID_YOSHI, SPRITE_WIDTH* startX, SPRITE_HEIGHT* startY, right) {};
private:

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

class BoardActor : public Actor
{
public:

private:

};

class CoinSquare : BoardActor
{
public:

private:


};

class StarSquare : BoardActor
{
public:

private:

};

class DirectionalSquare : BoardActor
{
public:

private:

};

class BankSquare : BoardActor
{
public:

private:

};

class EventSquare : BoardActor
{
public:

private:

};

class DroppingSquare : BoardActor
{
public:

private:

};

#endif // ACTOR_H_
