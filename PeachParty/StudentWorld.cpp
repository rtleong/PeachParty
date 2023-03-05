#include "StudentWorld.h"
#include "Actor.h"
#include "GameConstants.h"
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
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
    m_yoshi = nullptr; //set yoshi to nullptr
    m_peach = nullptr; //set the peach pointer to nullptr, she can be seperate from all actors
    
}

int StudentWorld::init()
{
   
        startCountdownTimer(99); //start countdown
        string board_file = assetPath() + "board0" + to_string(getBoardNumber()) + ".txt"; 
        Board::LoadResult result = m_board->loadBoard(board_file);
        if (result == Board::load_fail_file_not_found)
            cerr << "Could not find board01.txt data file\n";
        else if (result == Board::load_fail_bad_format)
            cerr << "Your board was improperly formatted\n";
        else if (result == Board::load_success) {
            cerr << "Successfully loaded board\n";
            for (int x = 0; x < 16; x++) { //loop through all board contents to load in types of objects
                for (int y = 0; y < 16; y++) {
                    Board::GridEntry ge = m_board->getContentsOf(x, y); 
                    switch (ge) {
                    case Board::empty:
                        cerr << "Location " << x << " " << y << " is empty.\n";
                        break;
                    case Board::boo:
                        addBoo(x, y);
                        cerr << "Location " << x << " " << y << " has a boo.\n";
                        break;
                    case Board::bowser:
                        addBowser(x, y);
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
                        addEventSquare(x, y);
                        cerr << "Location " << x << " " << y << " has a event square\n";
                        break;
                    case Board::bank_square:
                        addBankSquare(x, y);
                        cerr << "Location " << x << " " << y << " has a bank square\n";
                        break;
                    case Board::up_dir_square:
                        addDirectionalSquare(x, y, 90);
                        cerr << "Location " << x << " " << y << " has a up directional square\n";
                        break;
                    case Board::left_dir_square:
                        addDirectionalSquare(x, y, 180);
                        cerr << "Location " << x << " " << y << " has a left directional square\n";
                        break;
                    case Board::right_dir_square:
                        addDirectionalSquare(x, y, 0);
                        cerr << "Location " << x << " " << y << " has a right directional square\n";
                        break;
                    case Board::down_dir_square:
                        addDirectionalSquare(x, y, 270);
                        cerr << "Location " << x << " " << y << " has a down directional square\n";
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
        playSound(SOUND_GAME_FINISHED);
        if (getStars(m_peach) > getStars(m_yoshi)) {
            setFinalScore(getStars(m_peach), getCoins(m_peach));
            return GWSTATUS_PEACH_WON;
        }
        else if (getStars(m_yoshi) > getStars(m_peach)) {
            setFinalScore(getStars(m_yoshi), getCoins(m_yoshi));
            return GWSTATUS_YOSHI_WON;
        }
        else if (getStars(m_peach) == getStars(m_yoshi) && getCoins(m_peach) > getCoins(m_yoshi)) {
            setFinalScore(getStars(m_peach), getCoins(m_peach));
            return GWSTATUS_PEACH_WON;
        }
        else if (getStars(m_peach) == getStars(m_yoshi) && getCoins(m_peach) < getCoins(m_yoshi)) {
            setFinalScore(getStars(m_yoshi), getCoins(m_yoshi));
            return GWSTATUS_YOSHI_WON;
        }
        else {
            setFinalScore(getStars(m_peach), getCoins(m_peach));
            return GWSTATUS_PEACH_WON;
        }
    }
    m_peach->doSomething(); //tell peach to do something
    m_yoshi->doSomething(); //tell yoshi to do something
    for (Actor* a : actors) { //all actors need to do there "something"
        a->doSomething();
    }
    std::ostringstream oss; //may have to debug this
    oss << "P1 ";
    oss << "Roll: " << getTicks(m_peach) << " ";
    oss << setw(2) << "Stars: " << getStars(m_peach) << " ";
    oss << setw(2) << "$$: " << getCoins(m_peach) << " ";
    if (m_peach->checkIfHasVortex() == true) {
        oss << setw(2) << "VOR" << "  ";
    }
    oss << setw(2) << "| Time: " << timeRemaining() << " ";
    oss << setw(2) << "| Bank: " << getBankCoins() << " ";
    oss << setw(2) << "| P2 ";
    oss << setw(2) << "Roll: " << getTicks(m_yoshi) << " ";
    oss << setw(2) << "Stars: " << getStars(m_yoshi) << " ";
    oss << setw(2) << "$$: " << getCoins(m_yoshi) << " ";
    if (m_yoshi->checkIfHasVortex() == true) {
        oss << setw(2) << "VOR" << " ";
    }
    setGameStatText(oss.str());
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

    delete m_board; //delete board pointer
    m_board = nullptr;
}

void StudentWorld::addPlayerActor(double x, double y) {
    m_peach = new PlayerActor(this,IID_PEACH, x, y, 1); //add peach
    m_yoshi = new PlayerActor(this, IID_YOSHI, x, y, 2); //add yoshi
    actors.push_back(new CoinSquare(this, IID_BLUE_COIN_SQUARE, x, y, true)); //add blue square under both Actors
}

void StudentWorld::addBlueCoinSquare(double x, double y) {
    actors.push_back(new CoinSquare(this, IID_BLUE_COIN_SQUARE, x, y, true)); 
}

void StudentWorld::addRedCoinSquare(double x, double y) {
    actors.push_back(new CoinSquare(this, IID_RED_COIN_SQUARE, x, y, false));
}

void StudentWorld::addStarSquare(double x, double y) {
    actors.push_back(new StarSquare(this, IID_STAR_SQUARE, x, y));
}

void StudentWorld::addDirectionalSquare(double x, double y, int direction) {
    actors.push_back(new DirectionalSquare(this, IID_DIR_SQUARE, x, y, direction));
}

void StudentWorld::addBankSquare(double x, double y) {
    actors.push_back(new BankSquare(this, IID_BANK_SQUARE, x, y));
}

void StudentWorld::addEventSquare(double x, double y) {
    actors.push_back(new EventSquare(this, IID_EVENT_SQUARE, x, y));
}

void StudentWorld::addBowser(int x, int y) {
    actors.push_back(new Bowser(this, IID_BOWSER, x, y));
    actors.push_back(new CoinSquare(this, IID_BLUE_COIN_SQUARE, x, y, true));
}

void StudentWorld::addBoo(int x, int y) {
    actors.push_back(new Boo(this, IID_BOO, x, y));
    actors.push_back(new CoinSquare(this, IID_BLUE_COIN_SQUARE, x, y, true));
}

PlayerActor* StudentWorld::getPeach() { //returns peach pointer for functions
    return m_peach;
}

PlayerActor* StudentWorld::getYoshi() { //returns yoshi pointer for functions
    return m_yoshi;
}

int StudentWorld::getBankCoins() {
    return m_bankCoins;
}

int StudentWorld::getTicks(PlayerActor* a) {
    return a->checkTicks() / 8;
}

int StudentWorld::getStars(PlayerActor* a) {
    return a->checkStars();
}

int StudentWorld::getCoins(PlayerActor* a) {
    return a->checkCoins();
}

void StudentWorld::addCoinstoBank(int n) {
    m_bankCoins += n;
}

void StudentWorld::setBankBalanceToZero() {
    m_bankCoins = 0;
}

//Actor* StudentWorld::getRandomSquare(double x, double y) const {
//    //if (isThereASquareAtLocation(x, y) == true) {
//    //    return actors;
//    //}
//    return;
//}

bool StudentWorld::isThereASquareAtLocation(int x, int y) const {
    Board::GridEntry grent = m_board->getContentsOf(int(x), int(y));
    if (grent == Board::GridEntry::empty) {
        return false;
    }
    else
        return true;
}

bool StudentWorld::validPos(int x, int y) {
    Board::GridEntry grent = m_board->getContentsOf(int(x/16), int(y/16));
    if (grent == Board::GridEntry::empty) { //if next position on board is empty
        return false;   //only passing in x+16, y, or x, y-16, or other 4 directions
    }
    //check for others
    else if ((x >= 0 && x <= VIEW_WIDTH - 1) && (y >= 0 && y <= VIEW_HEIGHT - 1)) {
        return true; //if outside of screen retun false
    }
    else {
        return false; //check this if moving invalidly
    }
}

bool StudentWorld::intersecting(double x1, double y1, double x2, double y2) {
    if (x1 + SPRITE_WIDTH > x2 && x1 < x2 + SPRITE_WIDTH) { //if any part of sprite X1 hits sprite x2
        if (y1 + SPRITE_HEIGHT > y2 && y1 < y2 + SPRITE_HEIGHT) {
            return true; //and y is equal return true
        }
    }
    return false;
}

bool StudentWorld::intersecting(Actor* a, Actor* b) { //input two actors to get intersecting
    if (a->getX() == b->getX()) {
        if (a->getY() == b->getY()) {
            return true;
        }
    }
    return false;
}

bool StudentWorld::overlap(double x1, double y1, double x2, double y2) { //if fully overalapped
    return abs(x1 - x2) < SPRITE_WIDTH && abs(y1 - y2) < SPRITE_HEIGHT; //check if valid
}

bool StudentWorld::overlap(Actor* a, Actor* b) { //two actors to get overlapped
    if (((abs(a->getX() - b->getX())) == 0) && ((abs(a->getY() - b->getY())) < 16)) {
        return true;
    }
    if (((abs(a->getX() - b->getX())) < 16) && ((abs(a->getY() - b->getY())) == 0)) {
        return true;
    }
    return false;
}
