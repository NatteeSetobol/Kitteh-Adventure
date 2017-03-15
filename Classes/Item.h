//
//  Item.h
//  KittehAdventure
//
//  Created by code on 2014/11/27.
//
//

#ifndef __KittehAdventure__Item__
#define __KittehAdventure__Item__

#include <stdio.h>

#include "LiveObject.h"

class Item : public LiveObject
{
    public:
        bool destoryOnCol;
        int type;
        Item();
};

#endif /* defined(__KittehAdventure__Item__) */
