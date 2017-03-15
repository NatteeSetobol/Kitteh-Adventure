//
//  LoadLevel.h
//  KittehAdventure
//
//  Created by code on 2014/12/08.
//
//

#ifndef __KittehAdventure__LoadLevel__
#define __KittehAdventure__LoadLevel__

#include <stdio.h>
#include "cocos2d.h"
#include "LiveObject.h"


USING_NS_CC;


class LoadLevel : public cocos2d::CCLayer
{
    public:
    LoadLevel();
    LiveObject* kitteh;
};


#endif /* defined(__KittehAdventure__LoadLevel__) */
