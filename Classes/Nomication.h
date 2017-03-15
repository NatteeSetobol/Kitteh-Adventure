//
//  Nomication.h
//  KittehAdventure
//
//  Created by code on 2015/01/07.
//
//

#ifndef __KittehAdventure__Nomication__
#define __KittehAdventure__Nomication__

#include <stdio.h>
#include "cocos2d.h"
#include "Object.h"
#include "Title.h"

USING_NS_CC;

class Nomication : public cocos2d::CCLayer
{
    public:
    CCLayerColor *faderLayer;
    float fadeAmount;
    bool fadeIn;
    float pause;
    static cocos2d::CCScene* scene();
    virtual bool init();
    void Fader(float dt);
    CREATE_FUNC(Nomication);

};

#endif /* defined(__KittehAdventure__Nomication__) */
