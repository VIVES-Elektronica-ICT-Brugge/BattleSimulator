#pragma once
#include <cstdlib>
#include <string>
#include <sstream>

#include "Map.h"
#include "Display.h"
#include "Unit.h"

class Game
{
    private:

        Map * map;
        Display * display;

        int selectX;
        int selectY;

        bool alive;

        static const char KEY_UP = 72;
        static const char KEY_DOWN = 80;
        static const char KEY_LEFT = 75;
        static const char KEY_RIGHT = 77;
        static const char KEY_ENTER = 13;
        static const char KEY_SPACE = 32;
        static const char KEY_BACKSPACE = 8;
        static const char KEY_MOVE = 109;
        static const char KEY_FIRE = 102;

        static const char KEY_TANK = 116;
        static const char KEY_INFANTERY = 105;
        static const char KEY_SNIPER = 115;
        static const char KEY_RAMBO = 114;

        static const int PRICE_TANK = 1000;
        static const int PRICE_INFANTERY = 100;
        static const int PRICE_SNIPER = 150;
        static const int PRICE_RAMBO = 2000;

    private:
        int keyListener( void );
        void engine( void );
        void selector( int field );
        void buyMenu( int playerint, int credits );
        void playRound( int player );
        void selectUnit( int player );
        void selectNoUnit( int player );
        void moveUnit( int player );
        void fireUnit( int player );
        void win( int player );

    public:

        Game();
        void start( void );

};
