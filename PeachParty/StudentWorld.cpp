#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <vector>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    m_peach = nullptr; //set the peach pointer to nullptr, she can be seperate from all actors
    actors.clear(); //clear all actors
}

int StudentWorld::init()
{
    {
        Board bd; //given code, reads in board
        string board_file = assetPath() + "board01.txt";
        Board::LoadResult result = bd.loadBoard(board_file);
        if (result == Board::load_fail_file_not_found)
            cerr << "Could not find board01.txt data file\n";
        else if (result == Board::load_fail_bad_format)
            cerr << "Your board was improperly formatted\n";
        else if (result == Board::load_success) {
            cerr << "Successfully loaded board\n";
            Board::GridEntry ge = bd.getContentsOf(5, 10); // x=5, y=10
            switch (ge) {
            case Board::empty:
                cerr << "Location 5,10 is empty\n";
                break;
            case Board::boo:
                cout << "Location 5,10 has a Boo and a blue coin square\n";
                break;
            case Board::bowser:
                    cerr << "Location 5,10 has a Bowser and a blue coin square\n";
                break;
            case Board::player:
                cerr << "Location 5,10 has Peach & Yoshi and a blue coin square\n";
                break;
            case Board::red_coin_square:
                cerr << "Location 5,10 has a red coin square\n";
                break;
                // etc… //given implementation of board 
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

}

bool StudentWorld::ValidMove(double x, double y) {
    for (auto a : actors) {
        if (x + SPRITE_WIDTH - 1 > a->getX() && x < a->getX() + SPRITE_WIDTH - 1) { //if x is out of bounds dont move or y is out of bounds dont move
            if (y + SPRITE_HEIGHT - 1 > a->getY() && y < a->getY() + SPRITE_HEIGHT - 1) { // or y is out of bounds dont move
                return false;
            }
        }
    }
    return true; //move
}
