#include "StudentWorld.h"
#include "Actor.h"
#include "GameConstants.h"
#include <string>
#include <vector>
#include "Board.h"
using namespace std;


//bool StudentWorld::insertPeach(double x, double y) {
//    if (validPos(x, y)) {
//        m_peach = new Peach(this, x, y);
//        return true;
//    }
//}
//
//bool StudentWorld::insertBlueSquare(double x, double y) {
//    if (validPos(x, y)) {
//        actors.push_back(new CoinSquare(this, IID_BLUE_COIN_SQUARE, x, y, 0, 1));
//        return true;
//    }
//}
GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{   
    actors.clear(); //clear all actors
    m_board = new Board(); //update m_board to point at board

    m_peach = nullptr; //set the peach pointer to nullptr, she can be seperate from all actors
    
}

int StudentWorld::init()
{
      //  Board bd; //given code, reads in board
        startCountdownTimer(99);
        string board_file = assetPath() + "board01.txt"  /*to_string(getBoardNumber()) + ".txt"*/;
        Board::LoadResult result = m_board->loadBoard(board_file);
        if (result == Board::load_fail_file_not_found)
            cerr << "Could not find board01.txt data file\n";
        else if (result == Board::load_fail_bad_format)
            cerr << "Your board was improperly formatted\n";
        else if (result == Board::load_success) {
            cerr << "Successfully loaded board\n";
            //Board::GridEntry ge = bd.getContentsOf(5, 10); //x=5, y=10
            for (int x = 0; x < 16; x++) {
                for (int y = 0; y < 16; y++) {
                    Board::GridEntry ge = m_board->getContentsOf(x, y); //instead of 5, 10 get x, y
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
                        cerr << "Location " << x << " " << y << " has a player Yoshi and Peach\n";
                        //insertPeach(x, y);
                        addPeach(x, y);
                        break;
                    case Board::red_coin_square:
                        cerr << "Location " << x << " " << y << " has a red coin square\n";
                        break;
                    case Board::blue_coin_square:
                        cerr << "Location " << x << " " << y << " has a blue coin square\n";
                       // insertBlueSquare(x, y);
                        addBlueCoinSquare(x, y);
                        break;
                        // etc� //given implementation of board 
                    }
                }
            }
        }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit ESC.
    // Notice that the return value GWSTATUS_NOT_IMPLEMENTED will cause our framework to end the game.

    m_peach->doSomething(); //tell peach to do something
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

    delete m_peach; //delete peach
    m_peach = nullptr; //declare m_peach to nullptr so we crash if follow it ever

    delete m_board;
    m_board = nullptr;
}

void StudentWorld::addPeach(double x, double y) {
    m_peach = new Peach(this, x, y);
    actors.push_back(new CoinSquare(this, x, y));
}

void StudentWorld::addBlueCoinSquare(double x, double y) {
    actors.push_back(new CoinSquare(this, x, y));
}

bool StudentWorld::canWalk(double x, double y) {
    Board::GridEntry ge = m_board->getContentsOf(x + 16, y + 16);
    if (ge == Board::GridEntry::empty) {
        return true; //fix
    }
    return false; ///fix
}

bool StudentWorld::validPos(double x, double y) {
    Board::GridEntry grent = m_board->getContentsOf(int(x/16), int(y/16));
    if (grent == Board::GridEntry::empty()) {
        return false;
    }
    //check for others
    if ((x >= 0 && x <= VIEW_WIDTH - 1) && (y >= 0 && y <= VIEW_HEIGHT - 1)) {
        return true;
    }
    else {
        return false; //fix this
    }
}
