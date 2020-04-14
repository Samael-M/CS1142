#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Avatar.h"

void avatarInit(Avatar* avatar, const char* name){
    avatar->name = malloc(strlen(name) + 1);
    strcpy(avatar->name, name);
    avatar->keys = 0;
    avatar->gems = 0;
}

void avatarUninit(Avatar* avatar){
    free(avatar->name);
    avatar->name = NULL;
}

bool avatarUseKey(Avatar* avatar){
    if(avatar->keys > 0) {
        avatar->keys--;
        return 1;
    } else return 0;
}

void avatarAddKey(Avatar* avatar){
    avatar->keys++;
}

void avatarAddGem(Avatar* avatar){
    avatar->gems++;
}

void avatarDisplay(const Avatar* avatar){
    printf("%s's inventory: gems %d, keys %d\n", avatar->name , avatar->gems, avatar->keys);
} 