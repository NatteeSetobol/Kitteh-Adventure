//
//  Nomication.cpp
//  KittehAdventure
//
//  Created by code on 2015/01/07.
//
//

#include "Nomication.h"

CCScene* Nomication::scene()
{
    CCScene *scene = CCScene::create();
    
    Nomication *layer =  Nomication::create();
    
    scene->addChild(layer);
    
    return scene;
}

// on "init" you need to initialize your instance
bool Nomication::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    ccColor4B backgroundColor = ccc4(255, 255, 255, 255);
    CCLayerColor *colorLayer = CCLayerColor::create(backgroundColor);
    this->addChild(colorLayer);
    
    Object* logo = new Object();
    
    logo->SetSprite((char*)"logo.png");
    logo->GetSprite()->setPosition(ccp(600,300));
    this->addChild(logo->GetSprite());
    fadeIn=true;
    fadeAmount = 255;
    pause = 1.0;
    ccColor4B backgroundColor2 = ccc4(0, 0, 0, 255);
    faderLayer = CCLayerColor::create(backgroundColor2);
    this->addChild(faderLayer);
    this->schedule(schedule_selector(Nomication::Fader),0.01f);

    return true;
}

void Nomication::Fader(float dt)
{
    
    if (fadeIn)
    {
        if (fadeAmount >= 0)
        {
            faderLayer->setOpacity(fadeAmount);
            
            fadeAmount-= 4.0f;
        } else {
            pause-=0.01;
            if (pause <= 0)
            {
                fadeIn=false;
            }
        }
    } else {
        if (fadeAmount <= 255)
        {
            faderLayer->setOpacity(fadeAmount);
            fadeAmount += 4.0f;
        } else {
            //switch scene
            CCScene *pScene = Title::scene();
            CCDirector::sharedDirector()->replaceScene(pScene);
            this->unscheduleAllSelectors();
            
            
        }
    }
}