#pragma once

typedef unsigned long long uint64;
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

typedef long long int64;
typedef int int32;
typedef short int16;
typedef char int8;

enum PieceType{
    blank = 0,
    barrier = 1,
    levelOne = 2,
    levelTwo = 3,
    levelThree = 4,
    levelFour = 5,
    levelFive = 6,
    levelHelper = 7,
    King = 8
};

enum side{
    red = 1,
    black = -1
};

const int ininGameBoard[256] = {
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,
        1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,
        1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,
        1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,
        1,1,1,King,0,0,0,0,0,0,0,0,-King,1,1,1,
        1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,
        1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,
        1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,
        1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};

const int initSide = red;

