#include "Map.h"
#include "Unit.h"
#include <string>
#include <sstream>

using namespace std;

Map::Map()
{
    Map::mapInitialise();
    Map::mapStatusInitialise();
    Map::backgroundInitialise();
}

void Map::backgroundInitialise( void )
{
    //create visual background map
    backgroundSetTop(0);
    for( int y = 1; y < Y_SIZEBACKGROUND; y+=4 )
    {
        for(int i = 0; i < 3; i++)
        {
            backgroundSetRow( y + i );
        }


        if(y > ( Y_SIZEBACKGROUND - 7 ) )
        {
            backgroundSetBottom(y+3);
        }
        else
        {
            backgroundSetFlat(y+3);
        }
    }

    //building Trumps wall
    mapBackground[(X_SIZEBACKGROUND)/2][0] = MAP_WALL_TOP;
    mapBackground[(X_SIZEBACKGROUND)/2][Y_SIZEBACKGROUND-1] = MAP_WALL_BOTTOM;
    for(int y = 1; y < Y_SIZEBACKGROUND - 1; y++ )
    {
        mapBackground[(X_SIZEBACKGROUND)/2][y] = MAP_WALL;
    }
}

void Map::mapInitialise( void )
{
    //Create empty map
    for( int y = 0; y < Y_SIZE; y++ )
    {
        for( int x = 0; x < X_SIZE; x++ )
        {
            map[x][y] = nullptr;
        }
    }
}

void Map::mapStatusInitialise( void )
{
    //Create empty map
    for( int y = 0; y < Y_SIZE; y++ )
    {
        for( int x = 0; x < X_SIZE; x++ )
        {
            mapStatus[x][y] = 0;
        }
    }
}

void Map::backgroundSetRow( int y )
{
    mapBackground[0][y] = MAP_STRAIGHT;

    for( int x = 1; x < X_SIZEBACKGROUND; x+=6 )
    {
        for(int i = 0; i < 5; i++)
        {
            mapBackground[x+i][y] = MAP_SPACE;
        }
        mapBackground[x+5][y] = MAP_STRAIGHT;

    }
}

void Map::backgroundSetFlat( int y )
{
    mapBackground[0][y] = MAP_RIGHT;

    for( int x = 1; x < X_SIZEBACKGROUND - 1; x+=6 )
    {
        for(int i = 0; i < 5; i++)
        {
            mapBackground[x+i][y] = MAP_FLAT;
        }
        mapBackground[x+5][y] = MAP_CROSS;

    }
    mapBackground[X_SIZEBACKGROUND - 1][y] = MAP_LEFT;
}

void Map::backgroundSetTop( int y )
{
    mapBackground[0][y] = MAP_CORNER_UP_LEFT;

    for( int x = 1; x < X_SIZEBACKGROUND - 1; x+=6 )
    {
        for(int i = 0; i < 5; i++)
        {
            mapBackground[x+i][y] = MAP_FLAT;
        }
        mapBackground[x+5][y] = MAP_TOP;

    }
    mapBackground[X_SIZEBACKGROUND - 1][y] = MAP_CORNER_UP_RIGHT;
}

void Map::backgroundSetBottom( int y )
{
    mapBackground[0][y] = MAP_CORNER_BOTTOM_LEFT;

    for( int x = 1; x < X_SIZEBACKGROUND - 1; x+=6 )
    {
        for(int i = 0; i < 5; i++)
        {
            mapBackground[x+i][y] = MAP_FLAT;
        }
        mapBackground[x+5][y] = MAP_BOTTOM;

    }
    mapBackground[X_SIZEBACKGROUND - 1][y] = MAP_CORNER_BOTTOM_RIGHT;
}

std::string Map::toString()
{
    Map::mapBuild();

    std::stringstream mapStringStream;

    for( int y = 0; y < Y_SIZEBACKGROUND; y++ )
    {
        for( int x = 0; x < X_SIZEBACKGROUND; x++ )
        {
            mapStringStream << mapBackground[x][y];
        }
        mapStringStream << std::endl;
    }
    return mapStringStream.str();
}

void Map::setStatus( int x, int y, int status )
{
    mapStatus[x][y] = status;
}


void Map::mapBuild( void )
{
    char status;

    Map::backgroundInitialise();

    for( int y = 0; y < Y_SIZE; y++ )
    {
        for( int x = 0; x < X_SIZE; x++ )
        {
            for(int a = 1; a < 4; a++)
            {
                for(int b =1; b < 6; b++)
                {
                    mapBackground[x*6+b][y*4+a] = Map::statusChar( mapStatus[x][y] );
                }
            }
            if( map[x][y] != nullptr ){mapBackground[x*6+3][y*4+2] = map[x][y]->getChar();}
        }
    }
}

char Map::statusChar( int status )
{
    char statusChar;

    switch( status )
        {
        case 0:     //no status
        statusChar = MAP_SPACE;
        break;
        case 1:     //selected
        statusChar = MAP_SELECTED;
        break;
        case 2:     //exploded
        statusChar = MAP_EFFECT;
        break;
        }
    return statusChar;
}

void Map::setUnit( int x, int y, Unit * unit )
{
    map[x][y] = unit;
}

Unit * Map::getUnit( int x, int y )
{
    return map[x][y];
}

int Map::getWall( void )
{
    return (X_SIZE / 2);
}

bool Map::getAlive( int player )
{
    bool alive = false;

    if(player == 1)
    {
        for( int y = 0; y < Y_SIZE; y++ )
        {
            for( int x = 0; x <= getWall()-1; x++ )
            {
                if(map[x][y] != nullptr){alive = true;}
            }
        }
    }

    else if(player == 2)
    {
        for( int y = 0; y < Y_SIZE; y++ )
        {
            for( int x = getWall(); x < X_SIZE; x++ )
            {
                if(map[x][y] != nullptr){alive = true;}
            }
        }
    }
    return alive;
}
