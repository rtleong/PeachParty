#include "StudentWorld.h"
#include "Actor.h"
#include "GameConstants.h"
#include <string>
#include <vector>
#include "Board.h"
using namespace std;


GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}



StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{   
    actors.clear(); //clear all actors
    m_board = new Board(); //update m_board to point at board
    m_yoshi = nullptr;
    m_peach = nullptr; //set the peach pointer to nullptr, she can be seperate from all actors
    
}

int StudentWorld::init()
{
   
        startCountdownTimer(99);
        string board_file = assetPath() + "board0" + to_string(getBoardNumber()) + ".txt"; 
        Board::LoadResult result = m_board->loadBoard(board_file);
        if (result == Board::load_fail_file_not_found)
            cerr << "Could not find board01.txt data file\n";
        else if (result == Board::load_fail_bad_format)
            cerr << "Your board was improperly formatted\n";
        else if (result == Board::load_success) {
            cerr << "Successfully loaded board\n";
            for (int x = 0; x < 16; x++) {
                for (int y = 0; y < 16; y++) {
                    Board::GridEntry ge = m_board->getContentsOf(x, y); 
                    switch (ge) {
                    case Board::empty:
                        cerr << "Location " << x << " " << y << " is empty.\n";
                        break;
                    case Board::boo:
                        cerr << "Location " << x << " " << y << " has a boo.\n";
                        break;
                    case Board::bowser:
                        cerr << "Location " << x << " " << y << " has a bowser.\n";
                        break;
                    case Board::player:
                        cerr << "Location " << x << " " << y << " has a player Yoshi and PlayerActor\n";
                        addPlayerActor(x, y);
                        break;
                    case Board::red_coin_square:
                        cerr << "Location " << x << " " << y << " has a red coin square\n";
                        addRedCoinSquare(x, y);
                        break;
                    case Board::blue_coin_square:
                        cerr << "Location " << x << " " << y << " has a blue coin square\n";
                        addBlueCoinSquare(x, y);
                        break;
                    case Board::star_square:
                        addStarSquare(x, y);
                        cerr << "Location " << x << " " << y << " has a star square\n";
                        break;
                    case Board::event_square:
                        break;
                    case Board::bank_square:
                        break;
                    case Board::up_dir_square:
                        break;
                    case Board::left_dir_square:
                        break;
                    case Board::right_dir_square:
                        break;
                    case Board::down_dir_square:
                        break;
                    }
                }
            }
        }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    if (timeRemaining() < 0) {
        return GWSTATUS_PEACH_WON; //fix this if peach wins, do this else return yoshi wins, else return tie
    }
    m_peach->doSomething(); //tell peach to do something
    m_yoshi->doSomething();
    for (Actor* a : actors) { //all actors need to do there "something"
        a->doSomething();
    }
    return GWSTATUS_CONTINUE_GAME;
}

StudentWorld::~StudentWorld() {
    cleanUp(); //call cleanup to destroy studentworld
}

void StudentWorld::cleanUp()
{
    for (Actor* a : actors) {
        delete a; //delete all actors
    }
    actors.clear(); //clear the vector

    delete m_yoshi;//delete yoshi
    m_yoshi = nullptr;

    delete m_peach; //delete peach
    m_peach = nullptr; //declare m_peach to nullptr so we crash if follow it ever

    delete m_board;
    m_board = nullptr;
}

void StudentWorld::addPlayerActor(double x, double y) {
    m_peach = new PlayerActor(this,IID_PEACH, x, y, 1);
    m_yoshi = new PlayerActor(this, IID_YOSHI, x, y, 2);
    actors.push_back(new CoinSquare(this, IID_BLUE_COIN_SQUARE, x, y, true));
}

void StudentWorld::addBlueCoinSquare(double x, double y) {
    actors.push_back(new CoinSquare(this, IID_BLUE_COIN_SQUARE, x, y, true));
}

void StudentWorld::addRedCoinSquare(double x, double y) {
    actors.push_back(new CoinSquare(this, IID_RED_COIN_SQUARE, x, y, false));
}

void StudentWorld::addStarSquare(double x, double y) {
    actors.push_back(new StarSquare(this, x, y));
}

bool StudentWorld::canWalk(double x, double y) {
    Board::GridEntry ge = m_board->getContentsOf(x + 16, y + 16);
    if (ge == Board::GridEntry::empty) {
        return true; //fix
    }
    return false; ///fix
}

PlayerActor* StudentWorld::getPeach() {
    return m_peach;
}

PlayerActor* StudentWorld::getYoshi() {
    return m_yoshi;
}


bool StudentWorld::validPos(double x, double y) {
    Board::GridEntry grent = m_board->getContentsOf(int(x/16), int(y/16));
    if (grent == Board::GridEntry::empty) {
        return false;
    }
    //check for others
    else if ((x >= 0 && x <= VIEW_WIDTH - 1) && (y >= 0 && y <= VIEW_HEIGHT - 1)) {
        return true;
    }
    else {
        return true; //fix this
    }
}

bool StudentWorld::intersecting(double x1, double y1, double x2, double y2) {
    if (x1 + SPRITE_WIDTH > x2 && x1 < x2 + SPRITE_WIDTH) {
        if (y1 + SPRITE_HEIGHT > y2 && y1 < y2 + SPRITE_HEIGHT) {
            return true;
        }
    }
    return false;
}

bool StudentWorld::intersecting(Actor* a, Actor* b) {
    return intersecting(a->getX(), a->getY(), b->getX(), b->getY());
}

bool StudentWorld::overlap(double x1, double y1, double x2, double y2) {
    return abs(x1 - x2) < SPRITE_WIDTH && abs(y1 - y2) < SPRITE_HEIGHT; //check if valid
}

bool StudentWorld::overlap(Actor* a, Actor* b) {
    return overlap(a->getX(), a->getY(), b->getX(), b->getY());
}
