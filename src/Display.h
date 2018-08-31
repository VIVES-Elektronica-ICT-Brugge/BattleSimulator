#pragma once
#include <cstdlib>
#include <string>
#include <sstream>

#include "Map.h"

class Display
{
    private:

        Map * map;
        std::string message;
        int player;
        const static char PLAYER_SELECTED = 254;
        const static char PLAYER_NOT_SELECTED = 32;

    private:
        void windowInitialize( void );
        void logo( void );
        void playerLogo( int player );
        void winLogo( void );
        void emptyLines( int lines );


    public:

        Display( Map * map );
        void startScreen( void );
        void gameScreen( int player, std::string message );
        void buyScreen( int player, int credits, std::string message );
        void playerScreen( int player );
        void winScreen( int player );

};
