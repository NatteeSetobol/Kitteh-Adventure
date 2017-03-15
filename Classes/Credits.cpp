//
//  Credits.cpp
//  KittehAdventure
//
//  Created by code on 2014/12/23.
//
//

#include "Credits.h"

USING_NS_CC;


CCScene* Credits::scene()
{
    CCScene *scene = CCScene::create();
    
    Credits *layer =  Credits::create();
    
    scene->addChild(layer);
    
    return scene;
}

// on "init" you need to initialize your instance
bool Credits::init()
{
    
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCLabelTTF* credits = CCLabelTTF::create("Kitteh Adventure\n\nProgrammed by: Nattee Setobol\n\nMusic:\nDire Dire Docks Memoria, Unnatural Selection and Jungle Vibes - Matt Porter\nSnow Ball Game Music - Zildy\nSpookytownz - Akulu\nBusy Port Town - DJFibuko\n\nAll sprites by Maple Story", "Helvetica", 40,
                                          CCSizeMake(695, 1000), kCCTextAlignmentCenter);
    credits->setPosition(ccp(560, -500));
    this->addChild(credits);
    
    CCMoveBy* moveLeft = CCMoveBy::create(30.1, ccp(0,1300));
    //credits->runAction(moveLeft);
    
    
    CCCallFunc* moveDone = CCCallFunc::create(this, callfunc_selector(Credits::ShowLogo));

    CCArray* seqsOfCommands = CCArray::create();
    seqsOfCommands->addObject(moveLeft);
    seqsOfCommands->addObject(moveDone);
    
    CCSequence* runSeq = CCSequence::create(seqsOfCommands);
    
    credits->runAction(runSeq);
    
    
    //cocos2d::ccColor4B backgroundColor = cocos2d::ccc4(0, 0, 0, 255);
   // cocos2d::CCLayerColor *colorLayer = cocos2d::CCLayerColor::create(backgroundColor);
    //this->addChild(colorLayer);
    
    return true;
}

void Credits::ShowLogo(float dt)
{
    CCScene *pScene = Title::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}