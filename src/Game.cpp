#include "Game.h"
#include "Map.h"
#include "Unit.h"

#include <string>
#include <sstream>
#include <conio.h>
#include <cmath>



Game::Game()
{
    map = new Map();
    display = new Display(  map );

    selectX = 0;
    selectY = 0;
}

void Game::start( void )
{
    alive = true;
    display->startScreen();
    Game::keyListener();
    Game::engine();
}

int Game::keyListener()
{
    int key = 0;
    key = getch();
    return key;
}

void Game::selector( int field )
{
    int wall;
    int key;

    wall = map->getWall();

    if( field == 1 && selectX > wall-1)
    {
        selectX = 0;
        selectY = 0;
    }
    else if( field == 2 && selectX < wall)
    {
        selectX = wall;
        selectY = 0;
    }

    while( key != KEY_SPACE && key != KEY_ENTER )
    {
        map->setStatus( selectX, selectY, 1 );
        display->gameScreen( 0, "" );
        key = Game::keyListener();
        map->setStatus( selectX, selectY, 0 );

        if( field == 1 )
        {
                switch( key ) {
            case KEY_UP:
                if(selectY > 0){selectY--;}
                break;
            case KEY_DOWN:
                if(selectY < map->Y_SIZE-1){selectY++;}
                break;
            case KEY_LEFT:
                if(selectX > 0){selectX--;}
                break;
            case KEY_RIGHT:
                if(selectX < wall-1){selectX++;}
                break;
            }
        }
        else if( field == 2 )
        {
                switch( key ) {
            case KEY_UP:
                if(selectY > 0){selectY--;}
                break;
            case KEY_DOWN:
                if(selectY < map->Y_SIZE-1){selectY++;}
                break;
            case KEY_LEFT:
                if(selectX > wall){selectX--;}
                break;
            case KEY_RIGHT:
                if(selectX < map->X_SIZE-1){selectX++;}
                break;
            }
        }
        else if( field == 0 )
        {
                switch( key ) {
            case KEY_UP:
                if(selectY > 0){selectY--;}
                break;
            case KEY_DOWN:
                if(selectY < map->Y_SIZE-1){selectY++;}
                break;
            case KEY_LEFT:
                if(selectX > 0){selectX--;}
                break;
            case KEY_RIGHT:
                if(selectX < map->X_SIZE-1){selectX++;}
                break;
            }
        }
    }
}

void Game::engine( void )
{
    //every one buys his units
    Game::buyMenu( 1, 2000 );
    Game::buyMenu( 2, 2000 );

    //actual fight
    while( alive )
    {
        if(alive){Game::playRound( 1 );}
        if(alive){Game::playRound( 2 );}
    }




}

void Game::buyMenu( int player, int credits )
{
    int oldCredits;
    Unit * unit;

    display->playerScreen( player );
    Game::keyListener();

    while( credits >= 100 )
    {
        display->buyScreen( player, credits, "Press the key of the unit you want to buy." );
        oldCredits = credits;
        while( oldCredits == credits )
        {
            switch ( Game::keyListener() )
            {
                case KEY_INFANTERY:
                    if( credits >= PRICE_INFANTERY)
                    {
                        credits = credits - PRICE_INFANTERY;
                        unit = new Unit('I', 10, 10, 5);
                    }else{display->buyScreen( player, credits, "You can't buy infantery with the money you own right now" );}
                break;
                case KEY_TANK:
                    if( credits >= PRICE_TANK)
                    {
                        credits = credits - PRICE_TANK;
                        unit = new Unit('T', 100, 100, 2);
                    }else{display->buyScreen( player, credits, "You can't buy a tank with the money you own right now" );}
                break;
                case KEY_SNIPER:
                    if( credits >= PRICE_SNIPER)
                    {
                        credits = credits - PRICE_SNIPER;
                        unit = new Unit('S', 20, 5, 0);
                    }else{display->buyScreen( player, credits, "You can't buy a sniper with the money you own right now" );}
                break;
                case KEY_RAMBO:
                    if( credits >= PRICE_RAMBO)
                    {
                        credits = credits - PRICE_RAMBO;
                        unit = new Unit('R', 200, 200, 10);
                    }else{display->buyScreen( player, credits, "You can't buy Ramno with the money you own right now" );}
                break;
            }
        }
        display->gameScreen( player, "Place your unit using the arrow keys, press 'space' to confirm." );
        Game::selectNoUnit( player );
        map->setUnit( selectX, selectY, unit );
    }
}

void Game::playRound( int player )
{
    display->playerScreen( player );
    Game::keyListener();
    display->gameScreen( player, "Select a unit you want to move or fire with" );

    Game::selectUnit( player );
    display->gameScreen( player, "What do you want to do with this unit? Press 'm' to move or 'f' to fire." );

    int key = 0;

    while( key != KEY_MOVE && key != KEY_FIRE)
    {
        key = Game::keyListener();
    }

    switch ( key )
        {
            case KEY_MOVE:
                Game::moveUnit( player );
            break;
            case KEY_FIRE:
                Game::fireUnit( player );
            break;
        }
}

void Game::selectUnit( int player )
{
    bool flag = true;
        while(flag)
        {
            Game::selector( player );
            if(map->getUnit(selectX, selectY) != nullptr)
            {
                flag = false;
            }
            else
            {
                display->gameScreen( player, "There is no unit on that field" );
            }
        }
}

void Game::selectNoUnit( int player )
{
    bool flag = true;
        while(flag)
        {
            Game::selector( player );
            if(map->getUnit(selectX, selectY) == nullptr)
            {
                flag = false;
            }
            else
            {
                display->gameScreen( player, "There is already a unit on that field" );
            }
        }
}

void Game::moveUnit( int player )
{
    Unit * unit;
    unit = map->getUnit(selectX, selectY);
    map->setUnit(selectX, selectY, nullptr);
    display->gameScreen( player, "Select the field where you want to move your unit to" );
    Game::selectNoUnit( player );
    map->setUnit(selectX, selectY, unit);
}

void Game::fireUnit( int player )
{
    Unit * unit = map->getUnit(this->selectX, this->selectY);
    int damage = unit->getDamage();
    float range = (float) unit->getRange()/100;
    int selectX = this->selectX;
    int selectY = this->selectY;

    if( player == 1 ){ player = 2; }
    else if( player == 2 ){ player = 1; }

    display->gameScreen( player, "Select enemy unit to shoot at" );
    Game::selectUnit( player );
    unit = map->getUnit(this->selectX, this->selectY);
    range = range * damage;
    range = range * (std::abs(selectX - this->selectX) + std::abs(selectY - this->selectY)+1);
    if(range > damage){range = damage;}
    damage = damage - range;
    unit->getAttacked(damage);

    if(unit->getHealth() <= 0)
    {
        map->setUnit(this->selectX, this->selectY, nullptr);
        map->setStatus(this->selectX, this->selectY, 2);
        display->gameScreen( player, "You destroyed the enemy unit" );
        if(map->getAlive( player ) == false)
        {
            alive = false;
            if( player == 1 ){ player = 2; }
            else if( player == 2 ){ player = 1; }
            Game::win( player );
        }
    }
    else
    {
        std::stringstream battleLog;
        battleLog << "You hit he enemy unit for " << damage << " health points!";
        display->gameScreen( 0, battleLog.str() );
    }
    Game::keyListener();

}

void Game::win( int player )
{
    display->winScreen( player );
    Game::keyListener();
}


















