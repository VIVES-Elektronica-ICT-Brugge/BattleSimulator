#pragma once
#include <string>

class Unit
{
    private:

    char symbol;;
    int damage;
    int health;
    int range;


    private:


    public:

        Unit( char symbol, int damage, int health, int range );
        char getChar( void );
        int getDamage( void );
        int getHealth( void );
        int getRange( void );
        void getAttacked( int damage );
};
