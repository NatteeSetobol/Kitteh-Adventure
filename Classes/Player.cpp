//
//  Player.cpp
//  KittehAdventure
//
//  Created by code on 2014/11/10.
//
//

#include "Player.h"

USING_NS_CC;

Player::Player():LiveObject()
{
    init();
}

Player::~Player()
{
    
    if (kittens)
    {
        
        for (int i=0;i<kittens->count();i++)
        {
            LiveObject* littleKitten = (LiveObject*)kittens->objectAtIndex(i);
            
            if (littleKitten)
            {
                delete littleKitten;
                littleKitten=NULL;
            }
        }
        
        
        //delete kittens;
        //kittens=NULL;
    }
}

bool Player::init()
{
    if (!LiveObject::init())
    {
        CCLog("error");
        return false;
    }
    
    kittens=NULL;
    lasersParts=NULL;
    
    AddSprite((char*)"kitteh_idle");
    AddSprite((char*)"kitteh_run");
    AddSprite((char*) "kitteh_scared");
    AddSprite((char*) "kitteh_sad");
    AddSprite((char*) "longkitteh");
    AddSprite((char*) "meow_kitteh");
    AddSprite((char*) "grumpy_kitteh");

    /*
    must = new Object();
    must->SetSprite("mustache.png");
   // must->GetSprite()->setScale(1.8);
    must->GetSprite()->setPosition(ccp(20, -2));
    this->addChild(must->GetSprite(),3);
    */
    lasersParts = new CCArray();
    
    

    this->GetSpriteFrom((char*)"kitteh_idle")->setScale(1.8);
    this->GetSpriteFrom((char*)"kitteh_idle")->setPosition(ccp(0, 0));
    
    this->GetSpriteFrom((char*)"kitteh_run")->setScale(1.8);
    this->GetSpriteFrom((char*)"kitteh_run")->setFlipX(true);
    this->GetSpriteFrom((char*)"kitteh_run")->setPosition(ccp(0, 0));
    
    this->GetSpriteFrom((char*)"kitteh_scared")->setScale(1.8);
    this->GetSpriteFrom((char*)"kitteh_scared")->setPosition(ccp(0,0));
    this->GetSpriteFrom((char*)"kitteh_scared")->setFlipX(true);
    this->GetSpriteFrom((char*)"kitteh_sad")->setScale(1.8);
    
    this->GetSpriteFrom((char*) "longkitteh")->setScale(5.0);
    this->GetSpriteFrom((char*) "longkitteh")->setPosition(ccp(0,0));
    this->GetSpriteFrom((char*) "longkitteh")->setFlipX(true);
    
    this->GetSpriteFrom((char*) "meow_kitteh")->setScale(1.8);
    this->GetSpriteFrom((char*) "meow_kitteh")->setPosition(ccp(0,0));
    this->GetSpriteFrom((char*) "meow_kitteh")->setFlipX(true);
    
    this->GetSpriteFrom((char*) "grumpy_kitteh")->setScale(1.8);
    this->GetSpriteFrom((char*) "grumpy_kitteh")->setPosition(ccp(0,0));
    this->GetSpriteFrom((char*) "grumpy_kitteh")->setFlipX(true);
    /*
    CCSize newSize;
    newSize.width =this->GetSpriteFrom((char*)"kitteh_idle")->getContentSize().width;
    newSize.height = this->GetSpriteFrom((char*)"kitteh_idle")->getContentSize().height;
    this->setContentSize(newSize);
    */
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Laser.wav");
    
    coins=0;
    this->schedule(schedule_selector(Player::Update),0.01f);

    
    kittens = new CCArray();
    
    special=false;
    /*
    box = new Object();
    box->SetSprite((char*)"marker.png");
    this->addChild(box->GetSprite());
    */
    return true;
}

void Player::Update(float dt)
{
    LiveObject::Update(dt);
    
    if (GetRunningSpriteName()->compare("kitteh_idle") == 0)
    {
        
    }
    
   // float kittehRealX = getPositionX()+round(GetWidth()- realWidth);
   // float kittehRealY = getPositionY()+round(realHeight-GetHeight());
    

}

void Player::DoSpecial(int specialID)
{
    this->specialID = specialID;

    switch (specialID)
    {
        /*
         TODO: ADD CEILING CAT AND MORE MEMES
         */
        case GRUMPY_KITTEH:
        {
            ChangeSprite((char*)"grumpy_kitteh");
            
            Running(oldDistances, oldSpeed-40);
            this->scheduleOnce(schedule_selector(Player::SpecialRunning),5.00f);
            break;
        }
        case MEOW_KITTEH:
        {
            /*TODO: ADD DETAILS AND THE ABILITY TO MOVE THE KITTEH UP AND DOWN*/
            ChangeSprite((char*)"meow_kitteh");
            Running(oldDistances, oldSpeed-30);
            gravty=false;
            canJump=false;
            JumpDone(0.0);
            setPosition(getPositionX(), 395);
            this->scheduleOnce(schedule_selector(Player::SpecialRunning),5.00f);
            break;
        }
        case BIG_KITTEH:
        {
            GetSpriteFrom((char*)"kitteh_run")->setScale(5.0f);
            this->scale=5.0f;
            Running(oldDistances, oldSpeed+30.0f);
            setFeetCollusion(40, -20, 23, 13);
            this->scheduleOnce(schedule_selector(Player::SpecialRunning),10.00f);
            break;
        }
        case LONG_KITTEH:
        {
            ChangeSprite((char*)"longkitteh");

            int spX=35;
            int spY=175;
            int sp2X=88;
            int sp2Y=175;
            
            for (int i=0;i<86;i++)
            {
                Object* lazerz2 = new Object();
                lazerz2->SetSprite((char*) "lazer.png");
                lazerz2->GetSprite()->setRotation(-40);
                lazerz2->GetSprite()->setPosition(ccp(spX,spY));
                this->addChild(lazerz2->GetSprite());
                
                Object* lazerz = new Object();
                lazerz->SetSprite((char*) "lazer.png");
                lazerz->GetSprite()->setRotation(-40);
                lazerz->GetSprite()->setPosition(ccp(sp2X,sp2Y));
                this->addChild(lazerz->GetSprite());
                
                
                
                lasersParts->addObject(lazerz2);
                lasersParts->addObject(lazerz);

                
                
                spX+=5;
                spY-=5;
                
                
                sp2X+=5;
                sp2Y-=5;
            }
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Laser.wav");

            Running(oldDistances, oldSpeed);

            gravty=false;
            canJump=false;
            JumpDone(0.0);
            setPosition(getPositionX(), 295);
            this->scheduleOnce(schedule_selector(Player::SpecialRunning),4.00f);
            break;
        }
    }
    
    special = true;
}

void Player::SpecialRunning(float dt)
{
    switch (specialID)
    {
        case BIG_KITTEH:
        {
            GetSpriteFrom((char*)"kitteh_run")->setScale(1.8f);
            scale=1.8f;
            currentRunningSprite->stopAction(moveRight);
            moveRight=NULL;
            Running(oldDistances, oldSpeed-30.0);
            setFeetCollusion(40, 0, 23, 13);
            break;
        }
        case LONG_KITTEH:
        {
            ChangeSprite((char*)"kitteh_run");
            gravty=true;
            canJump=true;
            for (int i=0;i<lasersParts->count();i++)
            {
                Object* spriteToRemove = (Object*)lasersParts->objectAtIndex(i);
                this->removeChild(spriteToRemove->GetSprite());
            }
            
            lasersParts->removeAllObjects();
            break;
        }
        case MEOW_KITTEH:
        {
            ChangeSprite((char*)"kitteh_run");
            currentRunningSprite->stopAction(moveRight);
            moveRight=NULL;
            gravty=true;
            canJump=true;
            Running(oldDistances, oldSpeed+30.0);
            setFeetCollusion(40, 0, 23, 13);
            break;
        }
        case GRUMPY_KITTEH:
        {
            ChangeSprite((char*)"kitteh_run");
            currentRunningSprite->stopAction(moveRight);
            moveRight=NULL;
            Running(oldDistances, oldSpeed+40.0);
            setFeetCollusion(40, 0, 23, 13);
            break;
        }
    }
    
    special = false;

}
