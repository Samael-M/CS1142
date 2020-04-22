#include <stdio.h>
#include <stdlib.h>
#include "Map.h"

bool mapInit(Map *map, const char *filename)
{

    FILE *in = fopen(filename, "r");
    if (in == NULL)
    {
        printf("%s does not exist\n", filename);
        return 0;
    }
    fscanf(in, "%d", &map->rows);
    fscanf(in, "%d", &map->cols);
    fscanf(in, "%d", &map->avatarRow);
    fscanf(in, "%d", &map->avatarCol);
    
    map->tiles = malloc(sizeof(Tile *) * map->rows);
    for (int i = 0; i < map->rows; i++)
    {
        map->tiles[i] = malloc(sizeof(Tile) * map->cols);
    }
    
    int tile = 0;
    int i = 0;
    int j = 0;
    while ((tile = fgetc(in)) != EOF)
    {
        if (j > map->cols - 1)
        {
            j = 0;
            i++;
        } //else if(i > map->rows - 1) { break; }
        if (tile == 32 || tile == 10)
        {
        }
        else
        {
            map->tiles[i][j] = tileFromChar(tile);
            j++;
        }
    }
    fclose(in);
    in = NULL;
    return 1;
}

void mapUninit(Map *map)
{
    for (int i = 0; i < map->rows; i++)
    {
        free(map->tiles[i]);
        map->tiles[i] = NULL;
    }
    free(map->tiles);
    map->tiles = NULL;
}

void mapDisplay(const Map *map)
{
    for (int i = 0; i < map->rows; i++)
    {
        for (int j = 0; j < map->cols; j++)
        {
            if (i == map->avatarRow && j == map->avatarCol)
            {
                printf("@");
            } else tileDisplay(map->tiles[i][j]);
            
        }
        printf("\n");
    }
}

bool mapMoveAvatar(Map *map, Avatar *avatar, Action action)
{
    if (action == ActionNorth && map->avatarRow > 0)
    {
        if (map->tiles[map->avatarRow - 1][map->avatarCol] == TileWall ||
            (map->tiles[map->avatarRow - 1][map->avatarCol] == TileLockedDoor &&
             avatar->keys == 0))
        {
            return 0;
        }
        else if (map->tiles[map->avatarRow - 1][map->avatarCol] == TileKey)
        {
            avatarAddKey(avatar);
            map->tiles[map->avatarRow - 1][map->avatarCol] = TileEmpty;
            map->avatarRow--;
            return 1;
        }
        else if (map->tiles[map->avatarRow - 1][map->avatarCol] == TileGem)
        {
            avatarAddGem(avatar);
            map->tiles[map->avatarRow - 1][map->avatarCol] = TileEmpty;
            map->avatarRow--;
            return 1;
        }
        else if (map->tiles[map->avatarRow - 1][map->avatarCol] == TileLockedDoor &&
                 avatar->keys > 0)
        {
            avatarUseKey(avatar);
            map->tiles[map->avatarRow - 1][map->avatarCol] = TileDoor;
            map->avatarRow--;
            return 1;
        }
        else if (map->tiles[map->avatarRow - 1][map->avatarCol] == TileInvalid)
        {
            return 0;
        }
        else
        {
            map->avatarRow--;
            return 1;
        }
    }
    else if (action == ActionSouth && map->avatarRow < map->rows - 1)
    {
        if (map->tiles[map->avatarRow + 1][map->avatarCol] == TileWall ||
            (map->tiles[map->avatarRow + 1][map->avatarCol] == TileLockedDoor &&
             avatar->keys == 0))
        {
            return 0;
        }
        else if (map->tiles[map->avatarRow + 1][map->avatarCol] == TileKey)
        {
            avatar->keys++;
            map->tiles[map->avatarRow + 1][map->avatarCol] = TileEmpty;
            map->avatarRow++;
            return 1;
        }
        else if (map->tiles[map->avatarRow + 1][map->avatarCol] == TileGem)
        {
            avatar->gems++;
            map->tiles[map->avatarRow + 1][map->avatarCol] = TileEmpty;
            map->avatarRow++;
            return 1;
        }
        else if (map->tiles[map->avatarRow + 1][map->avatarCol] == TileLockedDoor &&
                 avatar->keys > 0)
        {
            avatar->keys++;
            map->tiles[map->avatarRow + 1][map->avatarCol] = TileDoor;
            map->avatarRow++;
            return 1;
        }
        else if (map->tiles[map->avatarRow + 1][map->avatarCol] == TileInvalid)
        {
            return 0;
        }
        else
        {
            map->avatarRow++;
            return 1;
        }
    }
    else if (action == ActionEast && map->avatarCol < map->cols - 1)
    {
        if (map->tiles[map->avatarRow][map->avatarCol + 1] == TileWall ||
            (map->tiles[map->avatarRow][map->avatarCol + 1] == TileLockedDoor &&
             avatar->keys == 0))
        {
            return 0;
        }
        else if (map->tiles[map->avatarRow][map->avatarCol + 1] == TileKey)
        {
            avatar->keys++;
            map->tiles[map->avatarRow][map->avatarCol + 1] = TileEmpty;
            map->avatarCol++;
            return 1;
        }
        else if (map->tiles[map->avatarRow][map->avatarCol + 1] == TileGem)
        {
            avatar->gems++;
            map->tiles[map->avatarRow][map->avatarCol + 1] = TileEmpty;
            map->avatarCol++;
            return 1;
        }
        else if (map->tiles[map->avatarRow][map->avatarCol + 1] == TileLockedDoor &&
                 avatar->keys > 0)
        {
            avatar->keys--;
            map->tiles[map->avatarRow][map->avatarCol + 1] = TileDoor;
            map->avatarCol++;
            return 1;
        }
        else if (map->tiles[map->avatarRow][map->avatarCol + 1] == TileInvalid)
        {
            return 0;
        }
        else
        {
            map->avatarCol++;
            return 1;
        }
    }
    else if (action == ActionWest && map->avatarCol > 0)
    {
        if (map->tiles[map->avatarRow][map->avatarCol - 1] == TileWall ||
            (map->tiles[map->avatarRow][map->avatarCol - 1] == TileLockedDoor &&
             avatar->keys == 0))
        {
            return 0;
        }
        else if (map->tiles[map->avatarRow][map->avatarCol - 1] == TileKey)
        {
            avatar->keys++;
            map->tiles[map->avatarRow][map->avatarCol - 1] = TileEmpty;
            map->avatarCol--;
            return 1;
        }
        else if (map->tiles[map->avatarRow][map->avatarCol - 1] == TileGem)
        {
            avatar->gems++;
            map->tiles[map->avatarRow][map->avatarCol - 1] = TileEmpty;
            map->avatarCol--;
            return 1;
        }
        else if (map->tiles[map->avatarRow][map->avatarCol - 1] == TileLockedDoor &&
                 avatar->keys > 0)
        {
            avatar->keys--;
            map->tiles[map->avatarRow][map->avatarCol - 1] = TileDoor;
            map->avatarCol--;
            return 1;
        }
        else if (map->tiles[map->avatarRow][map->avatarCol - 1] == TileInvalid)
        {
            return 0;
        }
        else
        {
            map->avatarCol--;
            return 1;
        }
    }
    else
        return 0;
}

int mapGemsRemaining(const Map *map)
{
    int gems = 0;
    for (int i = 0; i < map->cols; i++)
    {
        for (int j = 0; j < map->rows; j++)
        {
            if (map->tiles[j][i] == TileGem)
            {
                gems++;
            }
        }
    }
    return gems;
}
