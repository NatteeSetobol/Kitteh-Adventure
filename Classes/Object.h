//
//  Object.h
//  KittehAdventure
//
//  Created by code on 2014/11/02.
//
//

#ifndef __KittehAdventure__Object__
#define __KittehAdventure__Object__

#include <stdio.h>
#include <string.h>
#include "cocos2d.h"
#include "Globals.h"
//#include "../external/chipmunk/include/chipmunk/chipmunk.h"

USING_NS_CC;

class Object: public cocos2d::CCLayer
{
    public:
        Object();
        ~Object();
        CCDictionary *sprites;
        CCSprite* mainSprite;
        CCArray* layers;
        CCLayer* mainLayer;
        CCArray* AddedFrames;

        float realWidth;
        float realHeight;
        virtual bool init();

        bool SetSprite(char* filename);
        CCSprite* GetSprite();
        bool AddSprite(char* spriteName, int numberOfFrames);
        bool Run(char* spriteToRun, float secs);
        CCDictionary* GetSpritesInfo(char* sInfo);
        CCSpriteBatchNode* GetBatchNodeFromSprite(char* nsprite);
        CCSprite* GetSpriteFrom(char* sName);
        float animeSpeed;

        int bcount;
        void SetMainLayer(char* spritename);
        bool canColide;
        float scale;

        void update(float delta);
};


#endif /* defined(__KittehAdventure__Object__) */
