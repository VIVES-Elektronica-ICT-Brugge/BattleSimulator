#pragma once
#include "Unit.h"
#include <string>


using namespace std;

class Map
{
    public:
        static const int X_SIZE = 20;
        static const int Y_SIZE = 8;

    private:
        static const int X_SIZEBACKGROUND = X_SIZE * 6 + 1;
        static const int Y_SIZEBACKGROUND = Y_SIZE * 4 + 1;

        Unit * map[X_SIZE][Y_SIZE];
        int mapStatus[X_SIZE][Y_SIZE];
        char mapBackground[X_SIZEBACKGROUND][Y_SIZEBACKGROUND];

        static const char MAP_CORNER_UP_RIGHT = 191;
        static const char MAP_CORNER_UP_LEFT = 218;
        static const char MAP_CORNER_BOTTOM_RIGHT = 217;
        static const char MAP_CORNER_BOTTOM_LEFT = 192;
        static const char MAP_TOP = 194;
        static const char MAP_BOTTOM = 193;
        static const char MAP_CROSS = 197;
        static const char MAP_FLAT = 196;
        static const char MAP_STRAIGHT = 179;
        static const char MAP_RIGHT = 195;
        static const char MAP_LEFT = 180;
        static const char MAP_SPACE = 32;
        static const char MAP_WALL = 219;
        static const char MAP_WALL_TOP = 220;
        static const char MAP_WALL_BOTTOM = 223;
        static const char MAP_SELECTED = 176;
        static const char MAP_EFFECT = 35;

        void backgroundSetRow( int y );
        void backgroundSetFlat( int y );
        void backgroundSetTop( int y );
        void backgroundSetBottom( int y );

        void mapInitialise( void );
        void mapStatusInitialise( void );
        void backgroundInitialise( void );
        void mapBuild( void );
        char statusChar( int status );

    public:
        Map();
        std::string toString(void);
        void setStatus( int x, int y, int status );
        void setUnit( int x, int y, Unit * unit );
        Unit * getUnit( int x, int y );
        int getWall( void );
        bool getAlive( int player );



};
