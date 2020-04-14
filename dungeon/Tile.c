#include <stdio.h>

#include "Tile.h"

Tile tileFromChar(char ch) {
    if(ch == '.') {
        return TileEmpty;
    } else if(ch == '#') {
        return TileWall;
    } else if(ch == '+') {
        return TileKey;
    } else if(ch == '=') {
        return TileLockedDoor;
    } else if(ch == '-') {
        return TileDoor;
    } else if(ch == '*') {
        return TileGem;
    } else if(ch == 'S') {
        return TileSecretPassage;
    } else return TileInvalid;
}

void tileDisplay(Tile tile){
    if(tile == TileKey) {
        printf("+");
    } else if(tile == TileEmpty) {
        printf(" ");
    } else if(tile == TileWall) {
        printf("#");
    } else if(tile == TileDoor) {
        printf("-");
    } else if(tile == TileLockedDoor) {
        printf("=");
    } else if(tile == TileSecretPassage) {
        printf("#");
    } else if(tile == TileGem) {
        printf("*");
    }
}

bool tilePassable(Tile tile) {
    if(tile == TileKey) {
        return 1;
    } else if(tile == TileEmpty) {
        return 1;
    } else if(tile == TileWall) {
        return 0;
    } else if(tile == TileDoor) {
        return 1;
    } else if(tile == TileLockedDoor) {
        return 0;
    } else if(tile == TileSecretPassage) {
        return 1;
    } else if(tile == TileGem) {
        return 1;
    } else return 0;
}