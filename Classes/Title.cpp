//
//  Title.cpp
//  KittehAdventure
//
//  Created by code on 2014/11/02.
//
//

#include "Title.h"
USING_NS_CC;


CCScene* Title::scene()
{
    CCScene *scene = CCScene::create();
    
    Title *layer = Title::create();
    
    scene->addChild(layer);
    
    return scene;
}

// on "init" you need to initialize your instance
bool Title::init()
{
    int tileX=80;
    const char* fileName = "options";
    ccColor4B backgroundColor;
    CCLayerColor *colorLayer=NULL;
    CCMoveBy* moveRight=NULL;
    CCString path;
    CCString writablePath;
    std::string str;
    CCString *musicOpotion=NULL;
    CCCallFunc* moveDone;
    CCSequence* Cseq=NULL;
    CCLabelTTF* ttf1=NULL;
    CCString* contextString ;
    CCLabelTTF* coinText=NULL;
    CCLabelTTF* storyText=NULL;
    CCString* savedCoins=NULL;
    ccColor4B backgroundColor2;
 
   // tiles = NULL;
    bird = NULL;
    cloud=NULL;
    cloud2=NULL;
    cloud3=NULL;
    spSeq=NULL;
    spSeq2=NULL;
    kittehText=NULL;
    adventureText=NULL;
    kitteh=NULL;
    
    if ( !CCLayer::init() )
    {
        return false;
    }
 
    fadeIn=true;
    
  //  tiles = CCArray::create();
    
    backgroundColor = ccc4(153, 183, 231, 255);
    colorLayer = CCLayerColor::create(backgroundColor);
    this->addChild(colorLayer);
    
    /*NOTE: Draw tiles*/
        
    for (int i=0;i<14;i++)
    {
        Object* tile = new Object();
        tile->SetSprite((char*) "JungleTitleGround1.png");
        
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

            }
        }
    }
    
    /*Draw Images to the screen*/
    cloud = new Object();
    cloud->SetSprite( (char*)"GenericCloud.png");
    cloud->GetSprite()->setScale(.2);
    cloud->GetSprite()->setPosition(ccp(100, 500));
    this->addChild(cloud->GetSprite());
    
    
    cloud2 = new Object();
    cloud2->SetSprite((char*)"GenericCloud.png");
    cloud2->GetSprite()->setScale(.2);
    cloud2->GetSprite()->setPosition(ccp(1000, 400));
    this->addChild(cloud2->GetSprite());
    
    
    cloud3 = new Object();
    cloud3->SetSprite((char*)"GenericCloud.png");
    cloud3->GetSprite()->setScale(.2);
    cloud3->GetSprite()->setPosition(ccp(600, 580));
    this->addChild(cloud3->GetSprite());
    
    kittehText = new AnimeText((char*)"KITTEH");
    this->addChild(kittehText);
    kittehText->Animate(180,380);
    
    adventureText = new AnimeText((char*)"ADVENTURE");
    this->addChild(adventureText);
    adventureText->Animate(210,280);
    
    
    kitteh = new Object();
    kitteh->AddSprite((char*)"kitteh_sit", 3.5);
    kitteh->GetSpriteFrom((char*)"kitteh_sit")->setPosition(ccp(200, 80));
    kitteh->animeSpeed = 0.5f;

    this->addChild((CCLayer*) kitteh->layers->objectAtIndex(0));
    kitteh->GetSpriteFrom((char*)"kitteh_sit")->setFlipX(true);
    kitteh->GetSpriteFrom((char*)"kitteh_sit")->setScale(2.0f);
    kitteh->Run((char*)"kitteh_sit", 0.5);
    

    bird = new Object();
    bird->AddSprite((char*)"bird", 8);
    bird->GetSpriteFrom((char*)"bird")->setPosition(ccp(0,0));
    bird->GetSpriteFrom((char*) "bird")->setScale(1.5);
    bird->addChild((CCLayer*)bird->layers->objectAtIndex(0));
    bird->Run((char*)"bird", 0.1);
    bird->setPosition(1100,250);

    this->addChild(bird);
    
    moveRight = CCMoveBy::create(10.1, ccp(-1200,0));
    
    spSeq = new CCArray();
    spSeq->addObject(moveRight);
    
    moveDone = CCCallFunc::create(this,callfunc_selector(Title::BirdAnimeDone));
    spSeq->addObject(moveDone);
    
    Cseq = CCSequence::create(spSeq);
    bird->runAction(Cseq);
    
    ttf1 = CCLabelTTF::create("Tap Screen to Start!", "Helvetica", 40,
                                          CCSizeMake(695, 150), kCCTextAlignmentCenter);
    ttf1->setPosition(ccp(460, 100));
    this->addChild(ttf1);
    
    path = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);
    writablePath = CCFileUtils::sharedFileUtils()->getWritablePath();
    
    
    str = writablePath.getCString();
    str += fileName;
    
    options = CCDictionary::createWithContentsOfFile(str.data());
    

    /*NOTE Mini menu*/
    musicOpotion = (CCString*) options->objectForKey("MUSIC");
    savedCoins = (CCString*) options->objectForKey("COINS");
    
    if (musicOpotion->compare("yes") == 0)
    {
        music = true;
    } else {
        music=false;
    }

    if (music == true)
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0);
        
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
                                                                              "tilescreenmusic.mp3" , true);
    }
    

    music_note = new Object();
    music_note->SetSprite((char*)"music_note.png");
    music_note->GetSprite()->setScale(0.2);
    music_note->GetSprite()->setPosition(ccp(700,600));
    this->addChild(music_note->GetSprite());
    
    kittehStore = new Object();
    kittehStore->SetSprite((char*)"kittehstore.png");
    kittehStore->GetSprite()->setScale(2.0);
    kittehStore->GetSprite()->setPosition(ccp(780,600));
    this->addChild(kittehStore->GetSprite());
    
    storyText = CCLabelTTF::create("store", "Helvetica", 35,
                                               CCSizeMake(695, 180), kCCTextAlignmentCenter);
    
    storyText->setPosition(ccp(790, 480));
    this->addChild(storyText);
    
    
    if (music)
    {
        ttf2 = CCLabelTTF::create("on", "Helvetica", 35,
                                        CCSizeMake(695, 180), kCCTextAlignmentCenter);
    } else {
        ttf2 = CCLabelTTF::create("off", "Helvetica", 35,
                                  CCSizeMake(695, 180), kCCTextAlignmentCenter);
    }

    ttf2->setPosition(ccp(700, 480));
    this->addChild(ttf2);

    //TODO GET COIN FROM FILES

    contextString = CCString::createWithFormat("Total Coins: %i", savedCoins->intValue());
    coinText = CCLabelTTF::create(contextString->getCString(), "Helvetica", 30,
                                          CCSizeMake(695, 150), kCCTextAlignmentCenter);


    coinText->setPosition(ccp(130, 550));
    this->addChild(coinText);
    
    backgroundColor2 = ccc4(0, 0, 0, 255);
    faderLayer = CCLayerColor::create(backgroundColor2);
    this->addChild(faderLayer);

    this->schedule(schedule_selector(Title::Fader),0.01f);
    this->schedule(schedule_selector(Title::update),0.01f);

    fadeAmount = 255;
        
    return true;
}


void Title::Fader(float dt)
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
            CleanUp();
            
            CCScene *pScene = Intro::scene();
            CCDirector::sharedDirector()->replaceScene(pScene);
            this->unscheduleAllSelectors();
        }
    }
}

void Title::BirdAnimeDone()
{
    CCMoveBy* moveRight=NULL;
    CCCallFunc* moveDone=NULL;
    CCSequence* seq=NULL;

    spSeq2 = new CCArray();

    
    bird->setPosition(1200,250);
    moveRight = CCMoveBy::create(15.1, ccp(-1200,0));

    spSeq2->addObject(moveRight);
    
    moveDone = CCCallFunc::create(this,callfunc_selector(Title::BirdAnimeDone));
    spSeq2->addObject(moveDone);
    
    seq = CCSequence::create(spSeq2);
    bird->runAction(seq);
}

void Title::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    CCSetIterator iter = touches->begin();
    const char* fileName = "options";
    CCString path ;
    CCString writablePath;
    std::string str;
    CCDictionary *options2=NULL;
    
    for (; iter != touches->end(); iter++)
    {
        CCTouch* pTouch = (CCTouch*)(*iter);
        
        CCPoint location = pTouch->getLocationInView();
        location =CCDirector::sharedDirector()->convertToGL(location);
        
        if (music_note->GetSprite()->boundingBox().containsPoint(location))
        {

            if (music)
            {
                music=false;
            
                ttf2->setString("off");
                CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
            } else {
                music=true;
                ttf2->setString("on");
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
                                                                                      "tilescreenmusic.mp3" , true);
            }
             
            return ;
        }
        
        if (kittehStore->GetSprite()->boundingBox().containsPoint(location))
        {
            this->unscheduleAllSelectors();
            CCScene *pScene = KittehStore::scene();
            CCDirector::sharedDirector()->replaceScene(pScene);
            return ;
        }
        
    }
    
    
    
    path = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);
    writablePath = CCFileUtils::sharedFileUtils()->getWritablePath();
    
    str = writablePath.getCString();
    str += fileName;
    
    options2 = CCDictionary::createWithContentsOfFile(str.data());
    
    options2->removeObjectForKey("MUSIC");
    
    if (music)
    {
        options2->setObject(CCString::create("yes"), "MUSIC" );
        
    } else {
        options2->setObject(CCString::create("no"), "MUSIC" );

    }
    
    
    options2->writeToFile(str.data());
    
    
    fadeIn=false;
    fadeAmount = 0.0f;
    faderLayer->setOpacity(fadeAmount);

    this->setTouchEnabled(false);
    
}

void Title::CleanUp()
{
    this->unscheduleAllSelectors();
    this->getChildren()->removeAllObjects();
    this->removeAllChildrenWithCleanup(true);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();

}

Title::~Title()
{
}

void Title::update(float dt)
{
   // cpSpaceStep(space, dt);

}

