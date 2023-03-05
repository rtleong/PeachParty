#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Board.h"
#include "Actor.h"
#include <string>
#include <vector>


class PlayerActor;
class Actor;

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
  virtual int init();
  virtual int move();
  virtual void cleanUp();
  ~StudentWorld();
  bool validPos(int x, int y);
 

  PlayerActor* getPeach();
  PlayerActor* getYoshi();
  PlayerActor* returnPlayer(int playerNumber) { if (playerNumber == 1) return m_peach; if (playerNumber == 2) return m_yoshi; }

  //addding objects 
  void addPlayerActor(double x, double y);
  void addBlueCoinSquare(double x, double y);
  void addRedCoinSquare(double x, double y);
  void addStarSquare(double x, double y);
  void addDirectionalSquare(double x, double y, int direction);
  void addBankSquare(double x, double y);
  void addEventSquare(double x, double y);
  void addBowser(int x, int y);
  void addBoo(int x, int y);
  void addVortex(int x, int y, int direction);

  //mutators
  

  //accessors
  int getBankCoins();
  void addCoinstoBank(int n);
  void setBankBalanceToZero();
  bool isThereASquareAtLocation(int dest_x ,int dest_y) const;
  Actor* getRandomSquare(double x, double y) const;
  Board* getBoard() { return m_board; }
  int getTicks(PlayerActor* a);
  int getStars(PlayerActor* a);
  int getCoins(PlayerActor* a);

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
