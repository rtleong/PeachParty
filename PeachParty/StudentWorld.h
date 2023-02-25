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
  bool insertPeach(double x, double y);
  bool insertBlueSquare(double x, double y);

private:

	std::vector<Actor*> actors;
	Peach* m_peach;
};

#endif // STUDENTWORLD_H_
