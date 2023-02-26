#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Board.h"
#include "Actor.h"
#include <string>
#include <vector>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
  virtual int init();
  virtual int move();
  virtual void cleanUp();
  ~StudentWorld();
  bool validPos(double x, double y);
  bool canWalk(double x, double y);
  void addPlayerActor(double x, double y);
  void addBlueCoinSquare(double x, double y);

private:

	bool intersecting(double x1, double y1, double x2, double y2);
	bool intersecting(Actor* a, Actor* b);
	bool overlap(double x1, double y1, double x2, double y2);
	bool overlap(Actor* a, Actor* b);
	Board* m_board;
	std::vector<Actor*> actors;
	PlayerActor* m_peach;
};

#endif // STUDENTWORLD_H_
