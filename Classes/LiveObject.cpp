//
//  LiveObject.cpp
//  KittehAdventure
//
//  Created by code on 2014/11/18.
//
//

#include "LiveObject.h"

USING_NS_CC;


LiveObject::LiveObject():Object()
{
    init();
}

LiveObject::~LiveObject()
{

}

bool LiveObject::init()
{
    if (!Object::init())
    {
        return false;
    }
    
    moveRight=NULL;
    moveLeft=NULL;
    spSeq=NULL;
    jumpSeq=NULL;
    currentRunningSprite=NULL;
    feetCollusionRect=NULL;
    
    
    gravty=false;
    paused=false;
    isJumping=false;
    isFalling=false;
    hitGround=true;
    canJump=true;
    isRunning=false;
    this->schedule(schedule_selector(LiveObject::Update),0.01f);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("jump.wav");
    return true;
}


void LiveObject::show(bool vis)
{
    if (this->GetSpriteFrom((char*) "kitteh_idle"))
    {
        CCLog("yes!");
    } else {
        CCLog("no!");
        
    }
}

void LiveObject::setFeetCollusion(float feetx,float feety, float feetwidth, float feetheight)
{
    feetCollusionX=feetx;
    feetCollusionY=feety;
    feetCollusionWidth=feetwidth;
    feetCollusionHeight=feetheight;
}


bool LiveObject::ChangeSprite(char* sprite)
{
    CCObject* pElement;
    CCArray* allKeys = Object::sprites->allKeys();
    
    CCARRAY_FOREACH(allKeys, pElement)
    {
        CCString* key = (CCString*)pElement;
        CCSprite* sprt = this->GetSpriteFrom((char*)key->getCString());
        
        if (sprt == NULL)
        {
        }
        
        if (strcmp(key->getCString(), sprite) == 0)
        {
            if (sprt)
            {
                sprt->setVisible(true);
                sprt->stopAllActions();
                
                this->Run((char*) key->getCString(), 0.3);
                currentRunningSprite = sprt;
                
            }
        } else {
            sprt->setVisible(false);
            sprt->stopAllActions();
        }
        
    };
    return true;
}

bool LiveObject::Collided2X(float objectX, float objectY, float objectWidth, float objectHeight, float objectScale )
{
    float kittehRealX = (getPositionX()-(realWidth + scale)*2);
    float kittehRealY = (getPositionY()-(realHeight + scale)*2);
    
    float objectRealX = objectX - objectWidth;
    float objectRealY = objectY - objectHeight;
    
    if (
        kittehRealX < objectRealX + ((objectWidth  ) )
        &&
        kittehRealX + (GetWidth())  > objectRealX
        &&
        kittehRealY < objectRealY+(objectHeight)
        &&
        (GetHeight())+kittehRealY > objectRealY && canColide
        )
    {
        return true;
    }
    
    return false;
}

/* TODO Fix Collusion Detection with scaling */
bool LiveObject::Collided(float objectX, float objectY, float objectWidth, float objectHeight, float objectScale )
{
    float kittehX = getPositionX();
    float kittehY = getPositionY();
    float kittehWidth = round(realWidth+GetRunningSprite()->getScale());
    float kittehHeight = round(realHeight+GetRunningSprite()->getScale());
    
    float kittehRealX = kittehX-GetWidth();
    float kittehRealY = kittehY-GetHeight();
    
    
    float objectRealX = objectX - objectWidth;
    float objectRealY = objectY - objectHeight;
    
    if (
        kittehRealX < objectRealX + ((objectWidth  ) )
        &&
        kittehRealX + (kittehWidth)  > objectRealX
        &&
        kittehRealY < objectRealY+(objectHeight)
        &&
        (kittehHeight)+kittehRealY > objectRealY && canColide
        )
    {
        return true;
    }
    
    
    return false;
}

float LiveObject::GetScale()
{
    return GetRunningSprite()->getScale();
}

float LiveObject::GetWidth()
{
    return GetRunningSprite()->getTextureRect().size.width;
}

float LiveObject::GetHeight()
{
    return GetRunningSprite()->getTextureRect().size.height;
}


bool LiveObject::CollidedWithTile(float objectX, float objectY, float objectWidth, float objectHeight, float objectScale )
{
    
   
    float kittehX = getPositionX()+feetCollusionX;
    float kittehY = getPositionY()+feetCollusionY;
    float kittehWidth = feetCollusionWidth;//23
    float kittehHeight = feetCollusionHeight;//13
    
    /*
    float kittehX = getPositionX();
    float kittehY = getPositionY();
    float kittehWidth = GetWidth();
    float kittehHeight = GetHeight();
    
    
    float kittehRealX = abs(kittehX-GetWidth());
    float kittehRealY = abs(kittehY-GetHeight());
    
    
    float objectRealX = abs(objectX - objectWidth);
    float objectRealY = abs(objectY - objectHeight);
    
    if (
        kittehRealX < objectRealX + objectWidth
        &&
        kittehRealX + (kittehWidth)  > objectRealX
        &&
        kittehRealY > objectRealY+(objectHeight)
        &&
        (kittehRealY) < (objectRealY+objectHeight)+10
        )
    {
        if (kittehRealY != objectRealY+objectHeight)
        {
            this->setPosition(ccp(kittehRealX,kittehRealY+objectHeight));
        }
        return true;
    }
*/

    if (
        kittehX <= objectX + ((objectWidth) * objectScale )
        &&
        kittehX + (kittehWidth  * currentRunningSprite->getScale())  >= objectX
        &&
        kittehY >= objectY + (objectHeight * objectScale)
        &&
        kittehY <= objectY + ((objectHeight * objectScale)) + ((kittehHeight) * currentRunningSprite->getScale())
        
        )
    {
/*
        if (kittehY != objectY+objectHeight)
        {
            this->setPosition(ccp(kittehX, objectY+objectHeight));
        }
 */
        return true;
    }
    

    
    
    
    return false;
}


CCString* LiveObject::GetRunningSpriteName()
{
    CCObject* pElement;
    CCArray* allKeys = Object::sprites->allKeys();
    
    CCARRAY_FOREACH(allKeys, pElement)
    {
        CCString* key = (CCString*)pElement;
        CCSprite* sprt = this->GetSpriteFrom((char*)key->getCString());
        
        if (sprt->isRunning())
        {
            return key;
        }
    }
    return NULL;
}

CCSprite* LiveObject::GetRunningSprite()
{
    CCObject* pElement;
    CCArray* allKeys = Object::sprites->allKeys();
    
    CCARRAY_FOREACH(allKeys, pElement)
    {
        CCString* key = (CCString*)pElement;
        CCSprite* sprt = this->GetSpriteFrom((char*)key->getCString());
        
        if (sprt->isRunning())
        {
            return sprt;
        }
    }
    return NULL;
}

void LiveObject::Stop()
{
    CCObject* pElement;
    CCArray* allKeys = Object::sprites->allKeys();
    
    CCARRAY_FOREACH(allKeys, pElement)
    {
        CCString* key = (CCString*)pElement;
        CCSprite* sprt = this->GetSpriteFrom((char*)key->getCString());
        
        if (sprt->isRunning())
        {
            sprt->unscheduleAllSelectors();
            sprt->unscheduleUpdate();
            sprt->stopAllActions();
        }
    }
    unscheduleAllSelectors();
    unscheduleUpdate();
    stopAllActions();

    
}

bool LiveObject::Jump()
{
    
    if (isJumping == false && isFalling == false && canJump)
    {
        CCJumpBy* jump = CCJumpBy::create(1.0, ccp(0,120), 120, 1);
        spSeq = CCArray::create();
        spSeq->addObject(jump);
        
        CCCallFunc* moveDone = CCCallFunc::create(this,callfunc_selector(LiveObject::JumpDone));
        spSeq->addObject(moveDone);
        hitGround=false;
        jumpSeq= CCSequence::create(spSeq);
        runAction(jumpSeq);
        isJumping=true;
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Jump.wav");

    }
    return true;
}

bool LiveObject::Fall()
{
    if (jumpSeq == NULL )
    {
        if (hitGround == false && gravty)
        {
            
            CCJumpBy* catDown=NULL;
            
            if (getPositionY() < 0)
            {
                catDown= CCJumpBy::create(0.5, ccp(0,-100), -100, 1);
            } else {
                catDown= CCJumpBy::create(0.5, ccp(0,-1*(getPositionY()+1)), -10, 1);
                
            }
            catDown->retain();
        
            CCCallFunc* moveDone = CCCallFunc::create(this, callfunc_selector(LiveObject::Falling));
            moveDone->retain();
            
            seqArray = CCArray::create(catDown,moveDone);
            //CCArray::create(catDown,moveDone)->retain();
            
            jumpSeq = CCSequence::create(seqArray);
            jumpSeq->retain();
            runAction(moveDone);
        }
    }
    return false;
}

void LiveObject::Reset()
{
    if (jumpSeq != NULL)
    {
        stopAction(jumpSeq);
        getActionManager()->removeAction(jumpSeq);

        jumpSeq=NULL;
    }
}

void LiveObject::Falling(float dt)
{
    
    Reset();
    if (hitGround == false)
    {
        Fall();
        
    }
     
}

bool LiveObject::Running(float distances, float speed)
{
    moveRight = CCMoveBy::create(speed, ccp(distances,0));
    runAction(moveRight);
    isRunning=true;
    oldDistances=distances;
    oldSpeed=speed;
    return true;
}

void LiveObject::RunningDone(float dt)
{
    CCMoveBy* moveRight = CCMoveBy::create(10.1, ccp(2000,0));
    runAction(moveRight);
}

bool LiveObject::RunningLeft()
{
    moveLeft = CCMoveBy::create(30.1, ccp(-2000,0));
    runAction(moveLeft);
    isRunning=true;
    return true;
}

bool LiveObject::RunningLeft(float speed)
{
    moveLeft = CCMoveBy::create(speed, ccp(-2000,0));
    runAction(moveLeft);
    isRunning=true;
    return true;
}


bool LiveObject::RunningLeftDone(float dt)
{
    return true;
}

void LiveObject::JumpDone(float dt)
{
    if (jumpSeq != NULL)
    {
        stopAction(jumpSeq);
        getActionManager()->removeAction(jumpSeq);

        jumpSeq=NULL;
    }
    isJumping=false;
}

void LiveObject::Update(float dt)
{
    
    
    
}

bool LiveObject::AddSprite(char* sprite_name)
{
    CCString* spriteName = CCString::createWithFormat("%s.plist",sprite_name);
    
    
    CCDictionary* dictionary;
    dictionary = CCDictionary::createWithContentsOfFile(spriteName->getCString());
    CCDictionary* info = (CCDictionary*)dictionary->objectForKey("frames");
    
    int numberOfSprites = info->count()-1;
    
    Object::AddSprite((char*)sprite_name, numberOfSprites);
    
    CCLayer* pyer = (CCLayer*)layers->objectAtIndex( layers->count()-1 );
    this->addChild(pyer);
    
    
    return true;
}
