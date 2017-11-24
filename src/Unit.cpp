#include "Unit.h"

Unit::Unit( char symbol, int damage, int health, int range )
{
    this->symbol = symbol;
    this->damage = damage;
    this->health = health;
    this->range = range;
}

char Unit::getChar( void )
{
    return this->symbol;
}

int Unit::getDamage( void )
{
    return this->damage;
}

int Unit::getHealth( void )
{
    return this->health;
}

int Unit::getRange( void )
{
    return this->range;
}

void Unit::getAttacked( int damage )
{
    this->health = this->health - damage;
}

