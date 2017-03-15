//
//  Ending.h
//  KittehAdventure
//
//  Created by code on 2014/12/19.
//
//

#ifndef __KittehAdventure__Ending__
#define __KittehAdventure__Ending__

#include <stdio.h>
#include "cocos2d.h"
#include "Object.h"
#include "Player.h"
#include "Credits.h"
#include "AnimeText.h"

class Ending: public cocos2d::CCLayer
{
    public:
        static cocos2d::CCScene* scene();
        virtual bool init();
        Player* kitteh;
        Object* house;
        Object* boy;
        Object* dialog;
        AnimeText* congratsText;
        int state;
        CCLabelTTF* dialogText;
        CCLayerColor *faderLayer;
        bool fadeIn;
        void Fader(float dt);
        void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
        float fadeAmount;
       // Ending();
   //     ~Ending();
    void Update();
    CREATE_FUNC(Ending);
};



#endif /* defined(__KittehAdventure__Ending__) */
