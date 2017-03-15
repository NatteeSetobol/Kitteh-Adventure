//
//  Intro.cpp
//  KittehAdventure
//
//  Created by code on 2014/11/02.
//
//

#include "Intro.h"

USING_NS_CC;

CCScene* Intro::scene()
{
    CCScene *scene = CCScene::create();
    
    Intro *layer = Intro::create();
    
    scene->addChild(layer);
    
    return scene;
}

// on "init" you need to initialize your instance
bool Intro::init()
{
    
    if ( !CCLayer::init() )
    {
        return false;
    }
    

    
    Scene = SCENE_0;
    
    this->setTouchEnabled(true);
    ccColor4B backgroundColor = ccc4(153, 183, 231, 255);
    CCLayerColor *colorLayer = CCLayerColor::create(backgroundColor);
    this->addChild(colorLayer);

    
    skipImage = new Object();
    skipImage->SetSprite((char*)"skip-button.png");
    skipImage->GetSprite()->setPosition(ccp(500, 580));
    skipImage->setTouchEnabled(true);
    skipImage->setTag(69);

    this->addChild(skipImage->GetSprite());
    
    this->schedule(schedule_selector(Intro::RunIntro),0.01f);

    //CCArray* tiles = CCArray::create();
    int tileX=80;

    
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
                                                   ((tileX)+ (tile->GetSprite()->getTextureRect().size.width                                                              )*(i)
                                                    ) ,15
                                                   )
                                               );
                
                this->addChild(tile->GetSprite());
                delete tile;
                tile=NULL;
            }
        }
    }
    
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

    
    storyText1 = CCLabelTTF::create("Mom! I'm going out!\nCan you close the door?\nSo the Cat can't won't get out?\n\n(Tap to continue!)", "Helvetica", 25,
                                          CCSizeMake(695, 150), kCCTextAlignmentCenter);
    storyText1->setColor(textColor);
    storyText1->setVisible(false);
    storyText1->setPosition(ccp(220, 440));
    this->addChild(storyText1);
    
    
    boy = new Object();
    boy->AddSprite((char*)"kid", 4);
    boy->GetSpriteFrom((char*)"kid")->setScale(1.5);
    boy->GetSpriteFrom((char*)"kid")->setPosition(ccp(580,90));
    boy->addChild((CCLayer*)boy->layers->objectAtIndex(0));
    boy->Run((char*)"kid", 1.5f);
    boy->setVisible(false);
    this->addChild(boy);
    
    fadeAmount=255;
    
    player = new Player();
    player->GetSpriteFrom((char*)"longkitteh")->setVisible(false);
    this->addChild(player);

    
    car = new Object();
    car->SetSprite((char*)"car.png");
    car->GetSprite()->setScale(1.5);
    car->GetSprite()->setVisible(false);
    this->addChild(car->GetSprite());
    
    capturer = new Object();
    capturer->AddSprite((char*)"catcher", 2);
    this->addChild((CCLayer*) capturer->layers->objectAtIndex(0));
    capturer->Run((char*)"catcher", 0.3);
    capturer->GetSpriteFrom((char*)"catcher")->setFlipX(true);
    capturer->GetSpriteFrom((char*)"catcher")->setScale(1.5);
    capturer->GetSpriteFrom((char*)"catcher")->setVisible(false);

    
    rock = new Object();
    rock->SetSprite((char*) "rock.png");
    rock->GetSprite()->setScale(1.5);
    this->addChild(rock->GetSprite());
    rock->GetSprite()->setVisible(true);
    
    
    ccColor4B backgroundLayer = ccc4(0, 0, 0, 255);
    bgColorLayer = CCLayerColor::create(backgroundLayer);
    this->addChild(bgColorLayer);
    

    

    

    parts=1;
     
    return true;
}



void Intro::ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{

    CCSetIterator iter = touches->begin();
    
    for (; iter != touches->end(); iter++)
    {
        CCTouch* pTouch = (CCTouch*)(*iter);
        
        CCPoint location = pTouch->getLocationInView();
        location =CCDirector::sharedDirector()->convertToGL(location);
        
        if (skipImage->GetSprite()->boundingBox().containsPoint(location))
        {
            parts = 29;
        }
        
    }
    

    
    if (touches->containsObject(skipImage))
    {
        CCLog("all");
    }
    switch (Scene) {
        case SCENE_0:
        {
            break;
        }
        case SCENE_1:
        {
            switch (parts)
            {
                case 1:
                {
                    break;
                }
                case 2:
                {
                    CCMoveBy* moveRight = CCMoveBy::create(7.1, ccp(-800,0));
                    
                    
                    CCArray* spSeq = new CCArray();
                    spSeq->addObject(moveRight);
                    
                    CCCallFunc* moveDone = CCCallFunc::create(this,callfunc_selector(Intro::AnimeDone));
                    spSeq->addObject(moveDone);
                    
                    CCSequence* seq = CCSequence::create(spSeq);
                    
                    
                    
                    boy->runAction(seq);
                    dialog->GetSprite()->setVisible(false);
                    storyText1->setVisible(false);
                    
                    parts=3;
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

                    player->show(true);
                    player->ChangeSprite((char*)"kitteh_idle");
                    player->setPosition(ccp(660,76));
                    storyText1->setString("Meow!!!!!\n\n(Tap to continue)");

                    parts = 6;
                    
                    break;
                }
                case 6:
                {
                    player->ChangeSprite((char*)"kitteh_run");
                    player->setPosition(ccp(660,76));

                    dialog->GetSprite()->setVisible(false);
                    storyText1->setVisible(false);
                    CCMoveBy* moveRight = CCMoveBy::create(7.1, ccp(-800,0));
                    
                    
                    CCArray* spSeq = new CCArray();
                    spSeq->addObject(moveRight);
                    
                    CCCallFunc* moveDone = CCCallFunc::create(this,callfunc_selector(Intro::kitteh_run_done));
                    spSeq->addObject(moveDone);
                    
                    CCSequence* seq = CCSequence::create(spSeq);
                    player->runAction(seq);
                        
                    
                    parts=7;
                    break;
                }
                case 7:
                {
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
                case 11:
                {
                    break;
                }
                case 12:
                {
                    break;
                }
                case 13:
                {
                    break;
                }
                case 14:
                {
                    break;
                }
                case 15:
                {
                    break;
                }
                case 16:
                {
                    dialog->GetSprite()->setVisible(true);
                    storyText1->setVisible(true);
                    storyText1->setString("I going to take him in!!\n\n(Tap to continue)");
                    parts=17;
                    break;
                }
                case 17:
                {
                    dialog->GetSprite()->setVisible(false);
                    storyText1->setVisible(false);
                    capturer->GetSpriteFrom((char*)"catcher")->setVisible(false);
                    player->setVisible(false);
                
                    
                    CCArray* spSeq = new CCArray();
                    CCMoveBy* moveRight = CCMoveBy::create(7.1, ccp(-660,0));
                    
                    spSeq->addObject(moveRight);
                    
                    CCCallFunc* moveDone = CCCallFunc::create(this,callfunc_selector(Intro::car_done));
                    spSeq->addObject(moveDone);
                    
                    CCSequence* seq = CCSequence::create(spSeq);
                    car->GetSprite()->runAction(seq);
                    parts=18;
                    break;
                }
                case 26:
                {
                    dialog->GetSprite()->setVisible(false);
                    storyText1->setVisible(false);
                    CCJumpBy* jump = CCJumpBy::create(1.0, ccp(-450,-100), 0, 1);
                    //firstSprite->runAction(jump);
                    CCSequence* walkSec;
                    CCArray* spSeq = new CCArray();
                    spSeq->addObject(jump);
                    
                    CCCallFunc* moveDone = CCCallFunc::create(this,callfunc_selector(Intro::car_done));
                    spSeq->addObject(moveDone);
                    
                    walkSec = CCSequence::create(spSeq);
                    
                    
                    car->GetSprite()->runAction(walkSec);
                    
                    
                    CCJumpBy* catDown = CCJumpBy::create(1.0, ccp(10,-220), 0, 1);
                    player->runAction(catDown);


                    parts = 27;
                    break;
                }
                case 27:
                {
                    break;
                }
                case 28:
                {
                    parts=29;
                    break;
                }
            }
            break;
        }
    }
    
}

void Intro::RunIntro(float dt)
{
    switch (Scene)
    {
        case SCENE_0:
        {
            bgColorLayer->setOpacity(fadeAmount);
            fadeAmount-=5;
            
            if (fadeAmount <= 0)
            {
                Scene = SCENE_1;
                break;
            }
            break;
        }
        case SCENE_1:
        {
            switch (parts) {
                case 1:
                {
                    dialog->GetSprite()->setVisible(true);
                    storyText1->setVisible(true);
                    boy->setVisible(true);
                    parts=2;
                    break;
                }
                case 2:
                {

                    break;
                }
                case 3:
                {
                    break;
                }
                case 4:
                {
                    
                    dialog->GetSprite()->setVisible(true);
                    storyText1->setVisible(true);
                    storyText1->setString("Meow?\n\n(Tap to continue)");
                    parts = 5;
                    break;
                }
                case 5:
                {
                    break;
                }
                case 6:
                {
                    break;
                }
                case 7:
                {
                    break;
                }
                case 8:
                {
                    
                    if (FadeOut())
                    {
                        house->GetSprite()->setVisible(false);
                        parts = 9;
                        break;
                    }
                    
                    
                    break;
                }
                case 9:
                {

                    if (FadeIn())
                    {

                        player->setPosition(ccp(1150,76));
                        player->ChangeSprite((char*) "kitteh_run");
                        player->GetSpriteFrom((char*)"kitteh_run")->setFlipX(true);
                        
                        CCArray* spSeq = new CCArray();
                        CCMoveBy* moveRight = CCMoveBy::create(7.1, ccp(-500,0));
                        
                        spSeq->addObject(moveRight);
                        
                        CCCallFunc* moveDone = CCCallFunc::create(this,callfunc_selector(Intro::kitteh_run_done2));
                        spSeq->addObject(moveDone);
                        
                        CCSequence* seq = CCSequence::create(spSeq);
                        player->runAction(seq);

                     
                        parts=10;
                    }
                    break;
                }
                case 10:
                {


                    break;
                }
                case 11:
                {
                    player->ChangeSprite((char*)"kitteh_idle");
                    parts=12;
                    break;
                }
                case 12:
                {
                    car->GetSprite()->setPosition(ccp(1150,105));
                    car->GetSprite()->setVisible(true);
                    CCArray* spSeq = new CCArray();
                    CCMoveBy* moveRight = CCMoveBy::create(7.1, ccp(-660,0));
                    
                    spSeq->addObject(moveRight);
                    
                    CCCallFunc* moveDone = CCCallFunc::create(this,callfunc_selector(Intro::car_done));
                    spSeq->addObject(moveDone);
                    
                    CCSequence* seq = CCSequence::create(spSeq);
                    car->GetSprite()->runAction(seq);
                    parts=13;
                    break;
                }
                case 13:
                {
                    break;
                }
                case 14:
                {
                    capturer->GetSpriteFrom((char*)"catcher")->setPosition(ccp(car->GetSprite()->getPositionX()-50,95));
                    capturer->GetSpriteFrom((char*)"catcher")->setVisible(true);
                    parts=15;
                    break;
                }
                case 15:
                {
                    dialog->GetSprite()->setVisible(true);
                    storyText1->setVisible(true);
                    storyText1->setString("This cat has no collar...\n\n(Tap to continue)");
                    parts=16;
                    break;
                }
                case 16:
                {
                    
                    break;
                }
                case 17:
                {

                    
                    break;
                }
                case 18:
                {
                    break;
                }
                case 19:
                {

                    if (FadeOut())
                    {
                        parts=20;
                    }
                    break;
                }
                case 20:
                {

                    if (FadeIn())
                    {
                        parts=21;
                    }
                    break;
                }
                case 21:
                {
                    rock->setVisible(true);
                    rock->GetSprite()->setPosition(ccp(130,60));
                    car->GetSprite()->setPosition(ccp(1150,105));
                    
                    CCArray* spSeq = new CCArray();
                    CCMoveBy* moveRight = CCMoveBy::create(7.1, ccp(-920,0));
                    
                    spSeq->addObject(moveRight);
                    
                    CCCallFunc* moveDone = CCCallFunc::create(this,callfunc_selector(Intro::car_done));
                    spSeq->addObject(moveDone);
                    
                    CCSequence* seq = CCSequence::create(spSeq);
                    car->GetSprite()->runAction(seq);
                    parts = 22;
                    break;
                }
                case 22:
                {
                    
                    break;
                }
                case 23:
                {
                    CCJumpBy* jump = CCJumpBy::create(1.0, ccp(100,100), 100, 1);
                    CCSequence* walkSec;
                    CCArray* spSeq = new CCArray();
                    spSeq->addObject(jump);
                    
                    CCCallFunc* moveDone = CCCallFunc::create(this,callfunc_selector(Intro::car_done));
                    spSeq->addObject(moveDone);
                    
                    walkSec = CCSequence::create(spSeq);
                    
                    
                    car->GetSprite()->runAction(walkSec);
                    
                    parts=24;
                    break;
                }
                case 24:
                {
                    break;
                }
                case 25:
                {
                    dialog->GetSprite()->setVisible(true);
                    storyText1->setVisible(true);
                    storyText1->setString("OOPS!!!...\n\n(Tap to continue)");
                    player->setVisible(true);
                    player->setPosition(ccp(car->GetSprite()->getPositionX()+100,car->GetSprite()->getPositionY()+100));
                    player->ChangeSprite((char*)"kitteh_scared");
                    player->GetSpriteFrom((char*)"kitteh_scared")->setRotation(50);
                    parts=26;
                    break;
                }
                case 26:
                {
                    break;
                }
                case 28:
                {
                    break;
                }
                case 29:
                {
                    if (FadeOut())
                    {
                       // this->unscheduleAllSelectors();

                        CCScene *level = Level::scene();
                        CCDirector::sharedDirector()->replaceScene(level);
                        parts=30;
                        break;
                    }
                    break;
                }
            }

            break;
        }
    }
}

void Intro::car_done()
{
    
    switch (parts)
    {
        case 13:
        {
            parts=14;
            break;
        }
        case 18:
        {
            parts=19;
            break;
        }
        case 22:
        {
            parts=23;
            break;
        }
        case 24:
        {
            parts=25;
            break;
        }
        case 25:
        {
            break;
        }
        case 27:
        {
            dialog->GetSprite()->setVisible(true);
            storyText1->setVisible(true);
            player->setPosition(ccp(player->getPositionX(), player->getPositionY()-20));
            player->ChangeSprite((char*)"kitteh_sad");
            storyText1->setString("Kitteh are lost!!\n\nHelp kitteh find his way home!\n\n(Tap to continue)");
            parts=28;
            break;
        }
    }
    
}

bool Intro::FadeOut()
{
    bgColorLayer->setOpacity(fadeAmount);
    
    fadeAmount+=5;
    if (fadeAmount >= 255)
    {
        fadeAmount=255;
        return true;
    }
    return false;
}

bool Intro::FadeIn()
{
    bgColorLayer->setOpacity(fadeAmount);
    
    fadeAmount-=5;
    if (fadeAmount <= 0)
    {
        fadeAmount=0;
        return true;
    }
    return false;
}


void Intro::CleanUp()
{
    
}

void Intro::AnimeDone()
{
    if (parts == 29 || parts == 30) return ;
    parts=4;
}

void Intro::kitteh_run_done()
{
    if (parts == 29 || parts == 30) return ;

    parts=8;
}

void Intro::kitteh_run_done2()
{
    if (parts == 29 || parts == 30) return ;
                                                                                                                                                                                                                                                                                                       
    parts=11;
}
