//
//  Title.h
//  KittehAdventure
//
//  Created by code on 2014/11/02.
//
//

#ifndef __KittehAdventure__Title__
#define __KittehAdventure__Title__

#include <stdio.h>
#include "cocos2d.h"
#include "Globals.h"
#include "Object.h"
#include "AnimeText.h"
#include "Intro.h"
#include "KittehStore.h"
//#include "../external/chipmunk/include/chipmunk/chipmunk.h"


USING_NS_CC;


class Title : public cocos2d::CCLayer
{
    public:
        bool fadeIn;
        float fadeAmount;

        CCLayerColor *faderLayer;
        Object* bird;
        Object* cloud;
        Object* cloud2;
        Object* cloud3;
        CCArray* spSeq;
        CCArray* spSeq2;
        AnimeText* kittehText;
        AnimeText* adventureText;
        Object* kitteh;
        Object* music_note;
        Object* kittehStore;
        CCLabelTTF* ttf2;
        bool music;
        CCDictionary* options;
    
        virtual bool init();
        static cocos2d::CCScene* scene();
        void Fader(float dt);
        void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
        void BirdAnimeDone();
        void CleanUp();
        ~Title();
    
        void update(float dt);
    
    CREATE_FUNC(Title);
};

#endif
