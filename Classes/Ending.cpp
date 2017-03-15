//
//  Ending.cpp
//  KittehAdventure
//
//  Created by code on 2014/12/19.
//
//

#include "Ending.h"

CCScene* Ending::scene()
{
    CCScene *scene = CCScene::create();
    
    Ending *layer =  Ending::create();
    
    scene->addChild(layer);
    
    return scene;
}

// on "init" you need to initialize your instance
bool Ending::init()
{
    int tileX=80;
    
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    ccColor4B backgroundColor = ccc4(153, 183, 231, 255);
    CCLayerColor *colorLayer = CCLayerColor::create(backgroundColor);
    this->addChild(colorLayer);
    
    
    for (int i=0;i<14;i++)
    {
        Object* tile = new Object();
        tile->SetSprite((char*) jungleTitle1);
        
        if (tile)
        {
            if (tile->GetSprite())
            {
                tile->GetSprite()->setScale(1.8f);
                tile->GetSprite()->setPosition(
                                               ccp(
                                                   ((tileX)+ (tile->GetSprite()->getTextureRect().size.width
                                                              )*(i)
                                                    ) ,15
                                                   )
                                               );
                
                this->addChild(tile->GetSprite());
                delete tile;
                tile=NULL;
            }
        }
    }

    this->setTouchEnabled(true);
    
    kitteh = new Player();
    kitteh->ChangeSprite("kitteh_run");
    kitteh->GetSpriteFrom("kitteh_run")->setFlipX(false);
    kitteh->setPosition(ccp(0, 80));
    kitteh->Running(300, 5);
    this->addChild(kitteh,2);
    
    
    house = new Object();
    house->SetSprite((char*)"houses.png");
    house->GetSprite()->setScale(0.8);
    house->GetSprite()->setPosition(ccp(800, 250));
    this->addChild(house->GetSprite());
    
    dialog = new Object();
    dialog ->SetSprite((char*)"storyboard.png");
    dialog->GetSprite()->setScale(1.8);
    dialog->GetSprite()->setPosition(ccp(250, 440));
    dialog->GetSprite()->setVisible(false);
    this->addChild(dialog->GetSprite());
    
    ccColor3B textColor = ccc3(0, 0, 0);

    dialogText = CCLabelTTF::create("KITTEH!!! I MISS YOU!!?\n\n(Tap to continue!)", "Helvetica", 25,
                                    CCSizeMake(695, 150), kCCTextAlignmentCenter);
    dialogText->setColor(textColor);
    dialogText->setVisible(false);
    dialogText->setPosition(ccp(220, 440));
    this->addChild(dialogText);
    
    boy = new Object();
    boy->AddSprite((char*)"kid", 4);
    boy->GetSpriteFrom((char*)"kid")->setScale(1.5);
    boy->GetSpriteFrom((char*)"kid")->setPosition(ccp(580,90));
    boy->addChild((CCLayer*)boy->layers->objectAtIndex(0));
    boy->Run((char*)"kid", 1.5f);
    boy->setVisible(false);
    this->addChild(boy,1);
    
    
    congratsText = new AnimeText((char*)"CONGRATULATIONS");
    this->addChild(congratsText);
    congratsText->Animate(10,380);
    congratsText->setVisible(false);
    
    state = 0;
    this->schedule(schedule_selector(Ending::Update),0.01f);

    fadeAmount = 0.0f;
    ccColor4B backgroundColor2 = ccc4(0, 0, 0, 0);
    faderLayer = CCLayerColor::create(backgroundColor2);
    faderLayer->setVisible(false);
    this->addChild(faderLayer,100);
    
    return true;
}


void Ending::Update()
{
    switch (state)
    {
        case 0:
        {
            if (kitteh->getPositionX() >= 300)
            {
                kitteh->ChangeSprite("kitteh_idle");
                kitteh->GetSpriteFrom("kitteh_idle")->setFlipX(true);
                state = 1;
            }
            break;
        }
        case 1:
        {
            dialogText->setVisible(true);
            dialog->GetSprite()->setVisible(true);
            boy->setVisible(true);
            state = 2;
            break;
        }
        case 2:
        {
            break;
        }
        case 3:
        {
            dialogText->setVisible(false);
            dialog->GetSprite()->setVisible(false);
            kitteh->ChangeSprite("kitteh_run");
            CCJumpBy* catDown;
            catDown= CCJumpBy::create(1.5, ccp(255,25), -10, 1);
            kitteh->runAction(catDown);
            state = 4;
            break;
        }
        case 4:
        {
            if (kitteh->getPositionX() >= 555 && kitteh->getPositionY() >= 105)
            {
                dialogText->setVisible(true);
                dialog->GetSprite()->setVisible(true);
                dialogText->setString("Meow!!!! <3 <3\n\n(Tap to continue)");
                kitteh->ChangeSprite("kitteh_idle");
                state = 5;
            }
            break;
        }
        case 5:
        {
            
            break;
        }
        case 6:
        {
            //dialogText->setVisible(true);
            dialog->GetSprite()->setVisible(false);
            dialogText->setPosition(ccp(280, 120));
            dialogText->setString("(Tap to exit!)");
            congratsText->setVisible(true);
            state = 7;
            break;
        }
        case 7:
        {

            break;
        }
        case 8:
        {
            faderLayer->setVisible(true);
            fadeIn=false;
            this->schedule(schedule_selector(Ending::Fader),0.01f);
            state=9;
            break;
        }
        case 9:
        {
            if (fadeAmount >= 255)
            {
                state = 10;
            }
            break;
        }
        case 10:
        {
            this->removeAllChildren();
            level=1;
            CCScene *pScene = Credits::scene();
            level=0;
            CCDirector::sharedDirector()->replaceScene(pScene);
            state = 11;
            break;
        }
    }
}

void Ending::ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    switch (state)
    {
        case 0:
        {

            break;
        }
        case 1:
        {

            break;
        }
        case 2:
        {
            state = 3;
            break;
        }
        case 3:
        {
            break;
        }
        case 4:
        {
            
            break;
        }
        case 5:
        {
            state = 6;
            break;
        }
        case 6:
        {
            break;
        }
        case 7:
        {
            state = 8;
            break;
        }
        case 8:
        {
            break;
            
        }
        case 9:
        {
            break;
        }
        case 10:
        {
            break;
        }
    }
}

void Ending::Fader(float dt)
{
    
    if (fadeIn)
    {
        if (fadeAmount >= 0)
        {
            faderLayer->setOpacity(fadeAmount);
            
            fadeAmount-= 4.0f;
        } else {
            if (this->isTouchEnabled() == false)
            {
                this->setTouchEnabled(true);
            }
        }
    } else {
        if (fadeAmount <= 255)
        {
            faderLayer->setOpacity(fadeAmount);
            fadeAmount += 4.0f;
        } else {

            
            
        }
    }
}