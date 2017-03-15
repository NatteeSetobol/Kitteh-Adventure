//
//  Enemy.h
//  KittehAdventure
//
//  Created by code on 2014/11/19.
//
//

#ifndef __KittehAdventure__Enemy__
#define __KittehAdventure__Enemy__

#include <stdio.h>
#include "LiveObject.h"
#include "cocos2d.h"


class Enemy : public LiveObject
{
    public:
        Enemy();
        void Update(float dt);
    
        bool move;
        bool triggerOnPosition;
        int direction;
        bool forward;
        float speed;
        bool hasGravity;
        bool hitTile;
    
        bool isDead;
    
    
        LiveObject* projection;
        CCArray* projections;
        CCString* projection_direction;
        CCMoveBy* projection_moveBy;
        CCString* projectionSpriteName;

    
    
        bool repeatProjections;
        bool isMuliProjRunning;
    
        float projection_speed;
        float projection_delay;
    
    
        float ProjectionDirectionValueX;
        float ProjectionDirectionValueY;
    

        void makeProjection();
        void ProjectionDone();
};

#endif /* defined(__KittehAdventure__Enemy__) */
