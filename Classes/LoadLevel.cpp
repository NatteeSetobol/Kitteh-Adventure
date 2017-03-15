//
//  LoadLevel.cpp
//  KittehAdventure
//
//  Created by code on 2014/12/08.
//
//

#include "LoadLevel.h"


LoadLevel::LoadLevel()
{
    kitteh = new LiveObject();
    kitteh->AddSprite((char*)"kitteh_sit");
    kitteh->ChangeSprite((char*)"kitteh_sit");
    kitteh->GetSpriteFrom((char*)"kitteh_sit")->setPosition(ccp(100, 100));
    kitteh->Run((char*)"kitteh_sit", 0.5);
    kitteh->GetSpriteFrom((char*) "kitteh_sit")->setFlipX(true);
    kitteh->GetSpriteFrom((char*)"kitteh_sit")->setScale(2);
    
    
    this->addChild(kitteh);
    
    CCLabelTTF* ttf1 = CCLabelTTF::create("Loading...Please Wait!", "Helvetica", 35,
                                          CCSizeMake(695, 150), kCCTextAlignmentCenter);
    ttf1->setPosition(ccp(370, 15));
    this->addChild(ttf1);
}