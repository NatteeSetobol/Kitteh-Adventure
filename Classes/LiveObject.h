//
//  LiveObject.h
//  KittehAdventure
//
//  Created by code on 2014/11/18.
//
//

#ifndef __KittehAdventure__LiveObject__
#define __KittehAdventure__LiveObject__

#include <stdio.h>
#include "cocos2d.h"
#include "Object.h"
#include "../CocosDenshion/include/SimpleAudioEngine.h"


USING_NS_CC;

class LiveObject:  public Object
{
    public:
        LiveObject();
        ~LiveObject();
        CCArray* seqArray;
        CCMoveBy* moveRight;
        CCMoveBy* moveLeft;
        CCArray* spSeq;
        CCSequence* jumpSeq;
        CCSprite* currentRunningSprite;
        CCRect* feetCollusionRect;

    
        bool isFalling;

        virtual bool init();
        void Update(float dt);
        int state;
        void show(bool vis);

        bool ChangeSprite(char* sprite);
        bool CollidedWithTile(float objectX, float objectY, float objectWidth, float objectHeight, float objectScale );
        bool Collided(float objectX, float objectY, float objectWidth, float objectHeight, float objectScale );
        bool Collided2X(float objectX, float objectY, float objectWidth, float objectHeight, float objectScale );
        int x;
        int y;
        bool isJumping;
        bool hitGround;
        bool canJump;
        bool Jump();
        void JumpDone(float dt);

        bool Fall();
        void Stop();
        void Falling(float dt);
    
        bool isRunning;

        bool Running(float distances, float speed);
        void RunningDone(float dt);
    
        bool RunningLeft();
        bool RunningLeftDone(float dt);
    
        void Reset();
        bool paused;
        bool gravty;

        float GetWidth();
        float GetHeight();
        float GetScale();


        CCSprite* GetRunningSprite();

        virtual bool AddSprite(char* spriteName);
    
    
        float feetCollusionX;
        float feetCollusionY;
        float feetCollusionWidth;
        float feetCollusionHeight;
        float oldSpeed;
        float oldDistances;
        bool RunningLeft(float speed);

        void setFeetCollusion(float feetx,float feety, float feetwidth, float feetheight);
    
        CCString* GetRunningSpriteName();
};

#endif /* defined(__KittehAdventure__LiveObject__) */
