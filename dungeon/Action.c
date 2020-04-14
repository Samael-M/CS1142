#include <stdio.h>

#include "Action.h"

Action actionFromChar(char ch) 
{
    if(ch == 'a') {
        return ActionWest;
    } else if(ch == 'w') {
        return ActionNorth;
    } else if(ch == 'd'){
        return ActionEast;
    } else if(ch == 's') {
        return ActionSouth;
    } else if(ch == 'q') {
        return ActionQuit;
    } else return ActionInvalid;
}
