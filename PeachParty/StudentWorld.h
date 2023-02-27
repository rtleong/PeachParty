#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Board.h"
#include "Actor.h"
#include <string>
#include <vector>



class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
  virtual int init();
  virtual int move();
  virtual void cleanUp();
  ~StudentWorld();
  bool validPos(double x, double y);
 

  PlayerActor* getPeach();
  PlayerActor* getYoshi();

  //addding objects 
  void addPlayerActor(double x, double y);
  void addBlueCoinSquare(double x, double y);
  void addRedCoinSquare(double x, double y);
  void addStarSquare(double x, double y);
  void addDirectionalSquare(double x, double y, int direction);
  void addBankSquare(double x, double y);
  void addEventSquare(double x, double y);
  void teleportRandomSquare();

  //accessors
  int getBankCoins();
  void addCoinstoBank(int n);
  void setBankBalanceToZero();

  bool intersecting(double x1, double y1, double x2, double y2);
  bool intersecting(Actor* a, Actor* b);
  bool overlap(double x1, double y1, double x2, double y2);
  bool overlap(Actor* a, Actor* b);

private:
	int m_bankCoins = 0;
	Board* m_board;
	std::vector<Actor*> actors;
	PlayerActor* m_peach;
	PlayerActor* m_yoshi;
};

#endif // STUDENTWORLD_H_
