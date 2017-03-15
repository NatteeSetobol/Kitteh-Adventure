//
//  Enemy.cpp
//  KittehAdventure
//
//  Created by code on 2014/11/19.
//
//

#include "Enemy.h"

Enemy::Enemy()
{
    
    this->schedule(schedule_selector(Enemy::Update),0.01f);

    
    projection=NULL;
    projections=NULL;
    projection_direction=NULL;
    projection_moveBy=NULL;
    projectionSpriteName=NULL;
    moveLeft=NULL;
    
    projections = new CCArray();
    isMuliProjRunning=false;
    projection_delay=0;
    projection_speed=0;
    
    repeatProjections=false;
    isMuliProjRunning=false;
    isDead=false;
}

void Enemy::Update(float dt)
{
    LiveObject::Update(dt);
    
}

void Enemy::makeProjection()
{

    if (repeatProjections)
    {

        if (isDead == false)
        {
            CCLog("Make projection");
            
            Object* newProject = new Object();
            

            projections->addObject(newProject);
            
           // projection->isRunning=true;

            
            this->schedule(schedule_selector(Enemy::makeProjection),projection_delay);
        }
    } else {
        CCArray* arry = CCArray::create();
        CCSequence* newSeq;

        //CCCallFunc* moveDone = CCCallFunc::create(this,callfunc_selector(Enemy::ProjectionDone));


        //projection->GetSprite()->setPosition(ccp(getPositionX(), getPositionY()/2));
        projection_moveBy = CCMoveBy::create(projection_speed, ccp(ProjectionDirectionValueX,ProjectionDirectionValueY));

        projection->isRunning=true;

        arry->addObject(projection_moveBy);

        newSeq = CCSequence::create(arry);
        projection->GetSprite()->runAction( newSeq);
    }
}

void Enemy::ProjectionDone()
{
    
    if (isDead == false)
    {
        projection->GetSprite()->setPosition(ccp(getPositionX(),getPositionY()));
        projection_moveBy=NULL;
        makeProjection();
    }
}
