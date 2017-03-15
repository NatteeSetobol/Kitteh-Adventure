//
//  Level.cpp
//  KittehAdventure
//
//  Created by code on 2014/11/02.
//
//
//TODO LIST: 
//1. Make Level Longer
//2. Add a Store where people can buy items with their coins collected


#include "Level.h"

USING_NS_CC;


CCScene* Level::scene()
{
    CCScene *scene = CCScene::create();
    
    Level *layer = Level::create();
    
    scene->addChild(layer);
    
    return scene;
}


bool Level::init()
{

    if ( !CCLayer::init() )
    {
        return false;
    }
    
    
    
    kitteh=NULL;
    coinDisplay=NULL;
    tiles=NULL;
    enimes=NULL;
    items=NULL;
    shroom=NULL;
    theText=NULL;
    levelTitle=NULL;
    GameoverText=NULL;
    coinIcon=NULL;
    loadingScreenLayer=NULL;
    walkSec=NULL;
    backgrounds=NULL;
    levelBackgroundMusic=NULL;
    display=NULL;
    newState=-1;
    state=0;
    gravity = true;
    titleFade=255;
    pauseAmount=0;
    pauseCount=1.0;
    titleState=0;
    tilePadding=0;
    levelEnd=0;
    kittehSpeed=0.1;
    gameOverStatus=false;
    isLoading=false;
    musicVolume=1.0;
    
    if (level == 0)
    {
        totalCoins=0;
        totalKittehSave=0;
    }
    
    level++;
    pauseAmount=0.0f;
    pauseCount=0.0f;
    gravity=false;
    this->setTouchEnabled(true);
    titleFade=0.0f;
    
    tiles = new CCArray();
    
    if (tiles == NULL)
    {

        //TODO ERROR HANDLING
    }
    
    enimes = new CCArray();
    
    if (enimes == NULL)
    {

        //TODO ERROR HANDLING
    }
    
    items= new CCArray();
    if (items == NULL)
    {

        //TODO ERROR HANDLING
    }
    
    backgrounds = new CCArray();
    
    if (backgrounds == NULL)
    {

        //TODO ERROR HANDLING
    }
    
    walkSec=NULL;

    kitteh=NULL;
    coinIcon=NULL;

    state = LOAD;
    
    loadingScreenLayer = new LoadLevel();
    this->addChild(loadingScreenLayer,5);

    const char* fileName = "options";
    CCString path = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);
    CCString writablePath = CCFileUtils::sharedFileUtils()->getWritablePath();
    
    std::string str = writablePath.getCString();
    str += fileName;
    
    CCDictionary *options2 = CCDictionary::createWithContentsOfFile(str.data());
    
    
    CCString* musicOption  = (CCString*)options2->objectForKey("MUSIC");
    
    
    if (musicOption->compare("yes") == 0)
    {
        music = true;
    } else {
        music = false;
        
    }
    
    
    this->schedule(schedule_selector(Level::Update),0.01f);

    coinDisplay =  CCLabelTTF::create("x 0", "Helvetica", 35,
                                      CCSizeMake(695, 150), kCCTextAlignmentCenter);
    
    this->addChild(coinDisplay,2);

#ifdef DEBUG
    box = new Object();
    box->SetSprite((char*)"marker.png");
    this->addChild(box->GetSprite(),5);
#endif

    return true;
}


void Level::LoadingScreen(float dt)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("pickup_coin.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("enemyhit.wav");
    
    display = new Object();
    display->SetSprite((char*)"display.png");
    display->GetSprite()->setScale(1.5);
    display->GetSprite()->setPosition(ccp(levelEnd-500, 150));
    display->GetSprite()->setVisible(false);
    this->addChild(display->GetSprite(),5);
    
    
    //Load Player
    kitteh = new Player();
    kitteh->ChangeSprite((char*)"kitteh_idle");
    kitteh->GetSpriteFrom((char*)"kitteh_idle")->setFlipX(true);
    kitteh->setPosition(CCDirector::sharedDirector()->getWinSize().width/2, 65);
    this->addChild(kitteh, 3);

    if (level > totalLevels)
    {
        level = 1;
    }
    //Open Level information
    CCString* spriteName = CCString::createWithFormat("Level%i.plist",level);
    
    CCDictionary* dictionary;
    dictionary = CCDictionary::createWithContentsOfFile(spriteName->getCString());
    if (dictionary == NULL)
    {
        CCLog("Error can not load %s", spriteName->getCString());
    }
    CCDictionary* info = (CCDictionary*)dictionary->objectForKey("INFO");
    
    CCString* bgmusic = (CCString*)  info->objectForKey("BACKGROUND_MUSIC");
    
    if (bgmusic)
    {
        levelBackgroundMusic = CCString::create(bgmusic->getCString());
    } else {
        levelBackgroundMusic=NULL;
    }
    
    
    CCString* levelBackground = (CCString*)  info->objectForKey("LEVEL_BACKGROUND");
    CCDictionary* bgcolors = (CCDictionary*) info->objectForKey("BACKGROUND_COLOR");
    CCDictionary* kitteh_feet = (CCDictionary*) info->objectForKey("KITTEH_FEET");

    
    kitteh->setFeetCollusion(kitteh_feet->valueForKey("X")->floatValue(), kitteh_feet->valueForKey("Y")->floatValue(), kitteh_feet->valueForKey("WIDTH")->floatValue(), kitteh_feet->valueForKey("HEIGHT")->floatValue());

    
    int background_repeat = info->valueForKey("BACKGROUND_REPEAT")->intValue();
    
    int backgroundStartX = 550;
    
    for (int m=0;m< background_repeat;m++)
    {
        Object* levelBackgroundObject = new Object();
        levelBackgroundObject->SetSprite((char*) levelBackground->getCString());
        levelBackgroundObject->GetSprite()->setScale(1.0);
        levelBackgroundObject->GetSprite()->setPosition(ccp(backgroundStartX,320));
        this->addChild(levelBackgroundObject->GetSprite(),1);
        backgrounds->addObject(levelBackgroundObject);
        
        backgroundStartX += levelBackgroundObject->GetSprite()->getContentSize().width;
    }
    
    
    CCString* leveltile = (CCString*) info->objectForKey("NAME");
    kittehSpeed = info->valueForKey("SPEED")->floatValue();
    levelEnd = (float) info->valueForKey("END")->floatValue();
    
    char the[4] = "THE";
    theText = new AnimeText((char*)the);
    
    
    this->addChild(theText,2);
    
    theText->SetOpacity(0.00f);
    
    theText->Animate(80, 480);
    
    coinIcon = new Object();
    coinIcon->SetSprite((char*)"coin.png");
    coinIcon->setScale(1.8f);
    this->addChild(coinIcon->GetSprite(),2);
    
    levelTitle = new AnimeText((char*)leveltile->getCString());
    
    this->addChild(levelTitle,2);
    levelTitle->SetOpacity(0.00f);
    levelTitle->Animate(180,380);
    
    ccColor4B backgroundColor = ccc4(bgcolors->valueForKey("r")->floatValue(), bgcolors->valueForKey("g")->floatValue(), bgcolors->valueForKey("b")->floatValue(), 255);
    CCLayerColor *colorLayer = CCLayerColor::create(backgroundColor,levelEnd, 3000);
    
    this->addChild(colorLayer,0);
    
    int totalTiles=0;
    
    //Load all Objects
    CCDictionary* levelObjects = (CCDictionary*)dictionary->objectForKey("OBJECTS");
    CCArray* enemies = (CCArray*) dictionary->objectForKey("ENEMIES");
    
    if (levelObjects)
    {
        CCObject* pElement;
        CCArray* allKeys = levelObjects->allKeys();
        
        CCARRAY_FOREACH(allKeys, pElement)
        {
            CCString* key = (CCString*)pElement;
            CCDictionary* objdic = (CCDictionary*)levelObjects->objectForKey(key->getCString());
            
            if (objdic)
            {
                if (strcmp(key->getCString(), "ITEMS") == 0)
                {
                    
                    CCArray* itemArray = (CCArray*)levelObjects->objectForKey(key->getCString());
                    
                    
                    
                    for (int m=0;m<itemArray->count();m++)
                    {
                        Item* newItem = new Item();
                        CCDictionary* itemProperties = (CCDictionary*) itemArray->objectAtIndex(m);
                        
                        CCString* spriteName = (CCString*) itemProperties->objectForKey("SpriteName");
                        
                        CCString* spriteImage = CCString::createWithFormat("%s.png",spriteName->getCString());
                        
                        
                        newItem->SetSprite((char*) spriteImage->getCString());
                        
         
                        newItem->destoryOnCol =  itemProperties->valueForKey("Destory")->boolValue();
                        newItem->type = itemProperties->valueForKey("Type")->intValue();
                        newItem->GetSprite()->setScale(itemProperties->valueForKey("Scale")->floatValue());
                        float enemyX=itemProperties->valueForKey("X")->floatValue();
                        float enemyY=itemProperties->valueForKey("Y")->floatValue();
                        newItem->GetSprite()->setPosition(ccp(enemyX,enemyY));
                        
                        
                        this->addChild(newItem->GetSprite(),2);
                        items->addObject(newItem);
                        
                    }
                    
                } else {
                    
                    CCString* sprite = (CCString*)objdic->objectForKey((char*) "SPRITE_NAME");
                    
                    tilePadding = (int) objdic->valueForKey("PADDING")->floatValue();
                    
                    CCArray* positions = (CCArray*) objdic->objectForKey((char*) "POSITIONS");
                    if (positions)
                    {
                        for (int i = 0; i < positions->count();i++)
                        {
                            CCDictionary* pDictionary = (CCDictionary*) positions->objectAtIndex(i);
                            if (pDictionary)
                            {
                                CCDictionary* xDictionary = (CCDictionary*) pDictionary->objectForKey("X");
                                CCDictionary* yDictionary = (CCDictionary*) pDictionary->objectForKey("Y");
                                
                                
                                float tileXStart=0;
                                float tileYStart=0;
                                float tileXPadding=0;
                                float tileYPadding=0;
                                
                                bool xHasRange;
                                bool yHasRange;
                                
                                float xTimes=0;
                                float yTimes=0;
                                
                                float incX=0;
                                
                                if (xDictionary)
                                {
                                    
                                    tileXStart = xDictionary->valueForKey("START")->floatValue();
                                    tileXPadding = xDictionary->valueForKey("PADDING")->floatValue();
                                    xTimes = xDictionary->valueForKey("TIMES")->intValue();
                                    xHasRange = xDictionary->valueForKey("HAS_RANGE");
                                    
                                    
                                    incX = tileXStart;
                                    
                                    totalTiles+= xTimes;
                                    
                                } else {

                   		    //TODO ERROR HANDLING
                                }
                                
                                if (yDictionary)
                                {
                                    tileYStart = yDictionary->valueForKey("START")->floatValue();
                                    tileYPadding = yDictionary->valueForKey("PADDING")->floatValue();
                                    yTimes = xDictionary->valueForKey("TIMES")->intValue();
                                    yHasRange = xDictionary->valueForKey("HAS_RANGE");
                                    
                                    
                                } else {
					//TODO Error Handing

                                }
                                
                                
                                CCString* spriteImage = CCString::createWithFormat("%s.png", sprite->getCString());
                                
                                
                                
                                for (int j=0;j<xTimes;j++)
                                {
                                    Object* object;
                                    object = new Object();
                                    if (object == NULL)
                                    {
					//TODO Error Handing
                                    }
                                    object->SetSprite((char*)spriteImage->getCString());
                                    
                                    CCSprite* tsprite = object->GetSprite();
                                    
                                    if (tsprite)
                                    {
                                        tsprite->setScale(1.5);
                                        tsprite->setPosition(ccp(incX, tileYStart));
                                        
                                        this->addChild(object->GetSprite(),1);
                                        
                                        incX+=tsprite->getContentSize().width +tileXPadding;
                                    } else {
					//TODO Error Handing
                                    }
                                    
                                    if (strcmp( key->getCString() , "PLATFORM") == 0)
                                    {
                                        tiles->addObject(object);
                                    }
                                    
                                    
                                }
                                
                            } else {
                                
				//TODO Error Handing
                                    
                            }
                        }
                    }
                }
            } else {

		//TODO Error Handing
            }
        }
    }
    //LOAD ENEMIES FROM PLIST
    if (enemies)
    {
        for (int k=0;k<enemies->count();k++)
        {
            CCDictionary* enemy = (CCDictionary*)  enemies->objectAtIndex(k);
            
            if (enemy)
            {
                //Get Users Information
                CCDictionary* enemyLocation = (CCDictionary*) enemy->objectForKey("LOCATION");
                CCDictionary* enemyMove = (CCDictionary*) enemy->objectForKey("MOVE");
                CCDictionary* enemyProjection = (CCDictionary*) enemy->objectForKey("PROJECTION");
                CCDictionary* enemyFeet = (CCDictionary*) enemy->objectForKey("FEET");
                CCArray* enemyAction = (CCArray*) enemy->objectForKey("ACTIONS");
                float enemyScale;
                
                if (enemy->objectForKey("SCALE"))
                {
                    enemyScale = enemy->valueForKey("SCALE")->floatValue();
                } else {
                    enemyScale = 1.8f;
                }
                
                bool usedGravity = enemy->valueForKey("GRAVITY")->boolValue();
                
                float enemyHeight;
                float enemyWidth;
                float enemyX;
                float enemyY;
                float enemyLocationX;
                float enemyLocationY;
                
                Enemy* newEnemy = new Enemy();
                
                newEnemy->hasGravity = usedGravity;
                
                if (newEnemy)
                {
                } else {
                    
                   //TODO ERROR HANDLING
                }
                
                
                
                if (enemyMove)
                {
                    newEnemy->triggerOnPosition = enemyMove->valueForKey("TriggerOnPosition")->boolValue();
                    newEnemy->direction = enemyMove->valueForKey("Direction")->intValue();
                    newEnemy->forward = enemyMove->valueForKey("Forward")->boolValue();
                    newEnemy->speed= enemyMove->valueForKey("Speed")->floatValue();
                    newEnemy->gravty = enemyMove->valueForKey("Gravity")->boolValue();
                    //Eneimes doesn't have to have move
                    newEnemy->hitGround = false;
                }
                
            
                
                if (enemyLocation)
                {
                    enemyLocationX = (float) enemyLocation->valueForKey("X")->floatValue();
                    enemyLocationY = (float) enemyLocation->valueForKey("Y")->floatValue();
                    
                } else {
                   //TODO ERROR HANDLING
                }
                
                
                if (enemyFeet)
                {
                    enemyHeight = (float) enemyFeet->valueForKey("HEIGHT")->floatValue();
                    enemyWidth = (float) enemyFeet->valueForKey("WIDTH")->floatValue();
                    enemyX = (float) enemyFeet->valueForKey("X")->floatValue();
                    enemyY = (float) enemyFeet->valueForKey("Y")->floatValue();
                } else {
                   //TODO ERROR HANDLING

                }
                
                
                
                if (enemyAction)
                {
                    
                    for (int l=0;l<enemyAction->count();l++)
                    {
                        CCString* actionName = (CCString*)enemyAction->objectAtIndex(l);
                        if (actionName)
                        {
                            newEnemy->AddSprite((char*)actionName->getCString());
                            
                            if (l==0)
                            {
                                //Set the first sprite as the default sprite
                                newEnemy->ChangeSprite((char*)actionName->getCString());
                                newEnemy->GetSpriteFrom((char*)actionName->getCString())->setScale(enemyScale);
                            }
                        } else {
                            //TODO ERROR HANDLING
                        }
                    }
                    
                }
                
                newEnemy->setFeetCollusion(enemyX, enemyY, enemyWidth, enemyHeight);
                newEnemy->setPosition(enemyLocationX, enemyLocationY);
                
                this->addChild(newEnemy,2);
                enimes->addObject(newEnemy);
                
                if (enemyProjection)
                {
                    //Get Projection. If enemy Projection is NULL then it has not and doesn't
                    //produce an error.
                    
                    CCString* projectionSprite = (CCString*) enemyProjection->objectForKey((char*)"SPRITE");
                    CCString* projectionDirection = (CCString*) enemyProjection->objectForKey((char*)"DIRECTION");
                    float projectionSpeed = enemyProjection->valueForKey("SPEED")->floatValue();
                    float projectDelay = enemyProjection->valueForKey("DELAY")->floatValue();

                    bool isRepeated=false;
                    
                    if (enemyProjection->valueForKey("REPEAT"))
                    {
                        
                        if (enemyProjection->valueForKey("REPEAT")->boolValue() == true)
                        {
                            isRepeated=true;
                        } else {
                            isRepeated=false;
                        }
                        
                    } else {
                        isRepeated=false;
                    }
                    
                    newEnemy->repeatProjections = isRepeated;
                    
                    if (newEnemy->repeatProjections == false)
                    {
                        newEnemy->projection = new LiveObject();
                        if (projectionSprite)
                        {
                            newEnemy->projection->SetSprite((char*)projectionSprite->getCString());
                            newEnemy->projection->GetSprite()->setPosition(ccp(enemyLocationX,enemyLocationY-10));
                            newEnemy->projection_speed = projectionSpeed;
                            
                            newEnemy->projection->GetSprite()->setVisible(false);
                            newEnemy->projection_direction = new CCString();
                            newEnemy->projection_direction->initWithFormat("%s", projectionDirection->getCString());
                            newEnemy->projection_delay = projectDelay;
                            this->addChild(newEnemy->projection->GetSprite(),2);
                            
                            
                        }
                    } else {
                        newEnemy->projectionSpriteName = new CCString();
                        newEnemy->projectionSpriteName->initWithFormat("%s", projectionSprite->getCString());
                        newEnemy->projection_direction = new CCString();
                        newEnemy->projection_direction->initWithFormat("%s", projectionDirection->getCString());
                        newEnemy->projection_delay = projectDelay;
                        newEnemy->projection_speed = projectionSpeed;

                    }
                    
                }
                
            }
        }
    } else {
	//TODO ERROR HANDLING
    }
    this->removeChild(loadingScreenLayer);
    
    
    state = INTRO;
    isLoading=false;
    titleState = TITLE_FADEIN;
    musicVolume = 1.0;
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(musicVolume);
    
    
    if (levelBackgroundMusic)
    {
        
        if (music== true)
        {
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
                                                                levelBackgroundMusic->getCString() , true);
        }
    }
}

void Level::Update(float dt)
{
    bool hit=false;
    

    if (coinIcon && kitteh)
    {
        
        CCSize s = CCDirector::sharedDirector()->getWinSize();
        
        float screenWidth = s.width;
        float kitteh_x = kitteh->getPositionX();
        
#ifdef DEBUG
        float kittehRealX = (kitteh->getPositionX()-(kitteh->realWidth + kitteh->scale));
        float kittehRealY = (kitteh->getPositionY()-(kitteh->realHeight + kitteh->scale));
#endif

        
//        float kittehRealY=(kitteh->getPositionY()-(kitteh->realHeight + kitteh->GetRunningSprite()->getScale());
        
#ifdef DEBUG
        box->GetSprite()->setPosition(ccp(kittehRealX, kittehRealY));
#endif
 
        
        
        if (kitteh_x + (screenWidth/2)-20 < levelEnd)
        {
            coinDisplay->setPosition(ccp(    (kitteh_x - (screenWidth / 2)) + 100 , s.height-100) );
            
            CCString* coins = CCString::createWithFormat(" x %i", totalCoins);
            coinDisplay->setString(coins->getCString());
            
            
            coinIcon->GetSprite()->setPosition(ccp(    (kitteh_x - (screenWidth / 2)) + 50 , s.height-50) );
        }
        
    }
    switch (state)
    {
        case LOAD:
        {
            
            isLoading=true;
            this->scheduleOnce(schedule_selector(Level::LoadingScreen),2.00f);
            state = WAIT;
            break;
        }
        case INTRO:
        {

            switch (titleState)
            {
                case TITLE_FADEIN:
                {
                    if (!theText->FadeIn() && !levelTitle->FadeIn())
                    {
                        
                        pauseCount=0.0f;
                        pauseAmount=1.5f;
                        titleState = TITLE_DONE;
                        newState = INTRO;
                        state = PAUSE;
                         
                    }
                    break;
                }
                case TITLE_DONE:
                {
                    this->removeChild(theText);
                    this->removeChild(levelTitle);
                    kitteh->ChangeSprite((char*)"kitteh_run");
                    kitteh->GetSpriteFrom((char*)"kitteh_run")->setFlipX(false);

                    kitteh->Running(levelEnd,kittehSpeed);
                    kitteh->gravty=true;

                    CCFollow* followKitteh = CCFollow::create(kitteh,CCRectMake(0, 0, levelEnd, 1000));
                    this->runAction(followKitteh);
                    gravity=true;

                    


                    state = PLAYMODE;
                    break;
                }
            }
            break;
        }
        case PLAYMODE:
        {

            if (newState == PLAYMODE)
            {
                kitteh->ChangeSprite((char*)"kitteh_run");
                kitteh->Running(levelEnd, kittehSpeed);
                newState=-1;
                
            }
            
            if (gravity)
            {
                //Collusion Detection for player tiles
                for (int i=0;i< tiles->count();i++)
                {
                    Object* theTile = (Object*)tiles->objectAtIndex(i);
                    
                    if ( (kitteh->CollidedWithTile(theTile->GetSprite()->getPositionX(), theTile->GetSprite()->getPositionY(), theTile->GetSprite()->getContentSize().width, theTile->GetSprite()->getContentSize().height+tilePadding, theTile->GetSprite()->getScale())
                          )
                        &&
                        kitteh->isJumping == false
                        )
                    {
                        hit = true;
                    }
                    
                    
                }
                
                if (hit )
                {
                    kitteh->hitGround=true;
                    kitteh->isFalling=false;
                    kitteh->Reset();
                    
                } else {
                    kitteh->hitGround=false;
                    kitteh->Fall();
                    kitteh->isFalling=true;
                    
                }
                
                
                //Colussion Detection for enemies tiles
                
                for (int j=0;j< tiles->count();j++)
                {
                    Object* theTile = (Object*)tiles->objectAtIndex(j);
                    
                    for (int k=0;k<enimes->count();k++)
                    {
                        Enemy* enemyFromArray = (Enemy*) enimes->objectAtIndex(k);
                        if ( (enemyFromArray->CollidedWithTile(theTile->GetSprite()->getPositionX(), theTile->GetSprite()->getPositionY(), theTile->GetSprite()->getContentSize().width, theTile->GetSprite()->getContentSize().height, theTile->GetSprite()->getScale())
                              )
                            
                            )
                        {
                            enemyFromArray->hitTile = true;
                        }
                    }
                }
                
                //Enemies Gravity
                for (int l=0;l<enimes->count();l++)
                {
                    Enemy* enemyFromArray = (Enemy*) enimes->objectAtIndex(l);
                    if (enemyFromArray)
                    {
                        if (enemyFromArray->hasGravity)
                        {
                            if (enemyFromArray->hitTile)
                            {
                                enemyFromArray->hitGround=true;
                                enemyFromArray->isFalling=false;
                                enemyFromArray->Reset();
                                
                            } else {
                                enemyFromArray->hitGround=false;
                                enemyFromArray->Fall();
                                enemyFromArray->isFalling=true;
                                
                            }
                            enemyFromArray->hitTile=false;
                        }
                        
                        //unpause all enemies
                        if (enemyFromArray->paused)
                        {
                            enemyFromArray->paused=false;
                            enemyFromArray->RunningLeft(enemyFromArray->speed);
                            
                            //unpause projection
                            if (enemyFromArray->projection)
                            {
                                if (enemyFromArray->projection->isRunning == false)
                                {
                                    enemyFromArray->projection_moveBy = CCMoveBy::create(enemyFromArray->projection_speed, ccp(enemyFromArray->ProjectionDirectionValueX,enemyFromArray->ProjectionDirectionValueY));
                                    enemyFromArray->projection->GetSprite()->runAction(enemyFromArray->projection_moveBy);
                                    enemyFromArray->projection->isRunning=true;
                                }
                            }
                        }
                        
                        //Collusion for the enemies
                        if (enemyFromArray->mainSprite)
                        {
                            if (kitteh->special)
                            {
                                if (kitteh->specialID == LONG_KITTEH)
                                {
                                    for (int o=0;o<kitteh->lasersParts->count();o++)
                                    {
                                        Object* lazer = (Object*)kitteh->lasersParts->objectAtIndex(o);
                                        if (enemyFromArray->Collided(kitteh->getPositionX()+lazer->GetSprite()->getPositionX(), kitteh->getPositionY()+lazer->GetSprite()->getPositionY(), lazer->GetSprite()->getContentSize().width, lazer->GetSprite()->getContentSize().height, lazer->GetSprite()->getScale()))
                                        {
                                            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("enemyhit.wav");

                                            CCJumpBy* jump = CCJumpBy::create(10.0, ccp(enemyFromArray->getPositionX()+1000,1000), 1000, 1);
                                            enemyFromArray->runAction(jump);
                                            enemyFromArray->canColide=false;
                                            enemyFromArray->runAction(CCRepeatForever::create(CCRotateBy::create(1.0, 360)));
                                            break;
                                        }
                                    }
                                }
                            }
                            if (enemyFromArray->projection && enemyFromArray->repeatProjections == false)
                            {
                                if (kitteh->Collided(enemyFromArray->projection->GetSprite()->getPositionX(), enemyFromArray->projection->GetSprite()->getPositionY(),enemyFromArray->projection->GetSprite()-> getContentSize().width, enemyFromArray->projection->GetSprite()->getContentSize().height, enemyFromArray->projection->GetSprite()->getScale()) && enemyFromArray->projection->canColide && kitteh->special == false)
                                {
                                    enemyFromArray->projection->canColide=false;
                                    
                                    
                                    PauseGame();

    
                                    kitteh->ChangeSprite((char*)"kitteh_scared");
                                    
                                    kitteh->JumpDone(1.0);
                                    
                                    pauseAmount=0.8f;
                                    newState = PLAYMODE;
                                    state = PAUSE;
                                    
                                    if (kitteh->kittens->count() != 0)
                                    {
                                        LiveObject* lastKitten =(LiveObject*) kitteh->kittens->objectAtIndex(kitteh->kittens->count()-1);
                                        
                                        CCJumpBy* catDown= CCJumpBy::create(8.5, ccp(0,-100), -100, 1);
                                        
                                        lastKitten->GetSprite()->runAction(catDown);
                                        
                                        
                                        kitteh->kittens->removeLastObject();
                                    } else {
                                        
                                        
                                        GameoverText = new AnimeText((char*)"GAMEOVER",kitteh->getPositionX()-400,300);
                                        GameoverText->SetOpacity(0.00f);
                                        
                                        this->addChild(GameoverText,2);
                                        
                                        GameoverText->Animate(100, 100);
                                        
                                        kitteh->ChangeSprite((char*)"kitteh_sad");
                                        kitteh->GetSpriteFrom((char*)"kitteh_sad")->setFlipX(true);
                                        pauseAmount=1.0f;
                                        newState = GAMEOVER;
                                        state = PAUSE;
                                        return ;
                                    }
                                }
                            } else
                            if (enemyFromArray->repeatProjections == true && enemyFromArray->projection == NULL)
                            {
                                //do collision for muliple projections
                                for (int p=0;enemyFromArray->projections->count();p++)
                                {
                                    if (p >= enemyFromArray->projections->count()) break;
                                    Object* projection = (Object*)enemyFromArray->projections->objectAtIndex(p);
                                    if (projection->mainSprite == NULL)
                                    {
                                        if (enemyFromArray->projectionSpriteName == NULL) break;
                                        projection->SetSprite((char*)enemyFromArray->projectionSpriteName->getCString());
                                        projection->GetSprite()->setPosition(ccp(enemyFromArray->getPositionX(), enemyFromArray->getPositionY()));
                                        this->addChild(projection->GetSprite(), 2);
                                        
                                        CCMoveBy *projection_moveBy = CCMoveBy::create(enemyFromArray->projection_speed, ccp(-2000,enemyFromArray->getPositionY()));
                                        projection->GetSprite()->runAction(projection_moveBy);
                                    } else {
                                        //Multi projection collusion detection
                                        if (
                                            kitteh->Collided(projection->GetSprite()->getPositionX(), projection->GetSprite()->getPositionY(), projection->GetSprite()->getContentSize().width, projection->GetSprite()->getContentSize().height+1.8, projection->GetSprite()->getScale() )
                                            && projection->canColide && kitteh->special == false
                                            )
                                        {
                                            projection->canColide=false;
                                            PauseGame();
                                            
                                            
                                            kitteh->ChangeSprite((char*)"kitteh_scared");
                                            
                                            kitteh->JumpDone(1.0);
                                            
                                            pauseAmount=0.8f;
                                            newState = PLAYMODE;
                                            state = PAUSE;
                                            
                                            if (kitteh->kittens->count() != 0)
                                            {
                                                LiveObject* lastKitten =(LiveObject*) kitteh->kittens->objectAtIndex(kitteh->kittens->count()-1);
                                                
                                                CCJumpBy* catDown= CCJumpBy::create(8.5, ccp(0,-100), -100, 1);
                                                
                                                lastKitten->GetSprite()->runAction(catDown);
                                                
                                                
                                                kitteh->kittens->removeLastObject();
                                            } else {
                                                
                                                
                                                GameoverText = new AnimeText((char*)"GAMEOVER",kitteh->getPositionX()-400,300);
                                                GameoverText->SetOpacity(0.00f);
                                                
                                                this->addChild(GameoverText,2);
                                                
                                                GameoverText->Animate(100, 100);
                                                
                                                kitteh->ChangeSprite((char*)"kitteh_sad");
                                                kitteh->GetSpriteFrom((char*)"kitteh_sad")->setFlipX(true);
                                                pauseAmount=1.0f;
                                                newState = GAMEOVER;
                                                state = PAUSE;
                                                return ;
                                            }
  
                                        }
                                    }
                                }
                            }
                            
                            if ((
                                kitteh->Collided(enemyFromArray->getPositionX(), enemyFromArray->getPositionY(), enemyFromArray->GetWidth(), enemyFromArray->GetHeight(), enemyFromArray->GetRunningSprite()->getScale())
                                && enemyFromArray->canColide==true
                                
                                )
                                ||
                                (kitteh->special && kitteh->specialID == BIG_KITTEH && kitteh->Collided2X(enemyFromArray->getPositionX(), enemyFromArray->getPositionY(), enemyFromArray->GetWidth(), enemyFromArray->GetHeight(), enemyFromArray->GetRunningSprite()->getScale()))
                                )

                            
                            {
 
                                
                                if (kitteh->special)
                                {
                                    switch (kitteh->specialID) {
                                        case BIG_KITTEH:
                                        {
                                            CCJumpBy* jump = CCJumpBy::create(10.0, ccp(enemyFromArray->getPositionX()+1000,1000), 1000, 1);
                                            enemyFromArray->runAction(jump);
                                            enemyFromArray->canColide=false;
                                            enemyFromArray->isDead=true;
                                            enemyFromArray->runAction(CCRepeatForever::create(CCRotateBy::create(1.0, 360)));
                                            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("enemyhit.wav");

                                            break;
                                        }
                                        case GRUMPY_KITTEH:
                                        {
                                            CCJumpBy* jump = CCJumpBy::create(10.0, ccp(enemyFromArray->getPositionX()+1000,1000), 1000, 1);
                                            enemyFromArray->runAction(jump);
                                            enemyFromArray->isDead=true;
                                            enemyFromArray->canColide=false;
                                            enemyFromArray->runAction(CCRepeatForever::create(CCRotateBy::create(1.0, 360)));
                                            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("enemyhit.wav");

                                            break;
                                        }
                                    }
                                } else {
                                    enemyFromArray->canColide=false;

                                    PauseGame();
                                    kitteh->ChangeSprite((char*)"kitteh_scared");
                                    
                                    kitteh->JumpDone(1.0);
                                
                                    pauseAmount=0.8f;
                                    newState = PLAYMODE;
                                    state = PAUSE;
                                    
                                    if (kitteh->kittens->count() != 0)
                                    {
                                        LiveObject* lastKitten =(LiveObject*) kitteh->kittens->objectAtIndex(kitteh->kittens->count()-1);
                                        
                                        CCJumpBy* catDown= CCJumpBy::create(8.5, ccp(0,-100), -100, 1);

                                        lastKitten->runAction(catDown);
                                        
                                    
                                        kitteh->kittens->removeLastObject();
                                    } else {

                                        
                                        GameoverText = new AnimeText((char*)"GAMEOVER",kitteh->getPositionX()-400,300);
                                        GameoverText->SetOpacity(0.00f);
                                        
                                        this->addChild(GameoverText,2);
                                        
                                        GameoverText->Animate(100, 100);
                                        
                                        kitteh->ChangeSprite((char*)"kitteh_sad");
                                        kitteh->GetSpriteFrom((char*)"kitteh_sad")->setFlipX(true);
                                        pauseAmount=1.0f;
                                        newState = GAMEOVER;
                                        state = PAUSE;
                                        return ;
                                    }
                                }
                            }
                        }
                        
                        float x1=kitteh->getPositionX();
                        float x2=enemyFromArray->getPositionX();
                        float distancesBetween = x2-x1;
                        
                        //Enemy trigger
                        if (enemyFromArray->triggerOnPosition && enemyFromArray->isDead == false)
                        {
                            if (enemyFromArray->forward)
                            {
                                if (distancesBetween < 800 )
                                {
                                    
                                    if (enemyFromArray->isRunning == false)
                                    {
                                        enemyFromArray->RunningLeft(enemyFromArray->speed);
                                    
                                    }
                                    if (enemyFromArray->projection)
                                    {
                                            //Do Projection here
                                        enemyFromArray->projection->GetSprite()->setVisible(true);
                                        
                                        if (enemyFromArray->projection_direction->compare("FORWARD") == 0 && enemyFromArray->canColide == true)
                                        {
                                            if (enemyFromArray->repeatProjections)
                                            {
                                  
                                            } else {
                                                CCSize s = CCDirector::sharedDirector()->getWinSize();
                                                float screenWidth = s.width;
                                                float kitteh_x = kitteh->getPositionX();
                                                enemyFromArray->ProjectionDirectionValueX = - ( (kitteh_x - (screenWidth / 2)) + 50);
                                                enemyFromArray->ProjectionDirectionValueY = 0;
                                            }
                                            enemyFromArray->makeProjection();
                                            
                                        }
                                    } else {
                                        if (enemyFromArray->repeatProjections && enemyFromArray->isDead==false)
                                        {
                                            if (distancesBetween < 800)
                                            {
                                                if (enemyFromArray->isMuliProjRunning == false)
                                                {
                                                    enemyFromArray->isMuliProjRunning = true;
                                                    enemyFromArray->makeProjection();
                                                }
                                            }
                                            
                                        }
                                    }
                                    
                                }
                            } else {
                                if (enemyFromArray->projection && enemyFromArray->isDead == false)
                                {
                                    //Do Projection here
                                    if (distancesBetween < 800)
                                    {
                                        
                                        if (enemyFromArray->projection)
                                        {
                                            //Do Projection here
                                            if (enemyFromArray->projection->isRunning == false)
                                            {
                                                enemyFromArray->projection->GetSprite()->setVisible(true);
                                                
                                                if (enemyFromArray->projection_direction->compare("FORWARD") == 0  && enemyFromArray->canColide == true)
                                                {
                                                    if (enemyFromArray->repeatProjections == false)
                                                    {
                                                        CCSize s = CCDirector::sharedDirector()->getWinSize();
                                                        float screenWidth = s.width;
                                                        float kitteh_x = kitteh->getPositionX();
                                                        enemyFromArray->ProjectionDirectionValueX = - ( (kitteh_x - (screenWidth / 2)) );
                                                        enemyFromArray->ProjectionDirectionValueY = 0;
                                                    }
                                                    enemyFromArray->makeProjection();

                                                }
                                            }
                                            
                                        }
                                    }
                                } else {
                                    if (enemyFromArray->repeatProjections == true && enemyFromArray->isDead == false)
                                    {
                                        if (distancesBetween < 800)
                                        {
                                            if (enemyFromArray->isMuliProjRunning == false)
                                            {
                                                enemyFromArray->isMuliProjRunning = true;
                                                enemyFromArray->makeProjection();
                                            }
                                        }
                                        
                                    }
                                }
                            }
                        } else {
                            if (enemyFromArray->forward)
                            {
                                if (enemyFromArray->isRunning == false)
                                {
                                    enemyFromArray->RunningLeft(enemyFromArray->speed);

                                }

                            }
                            if (enemyFromArray->projection && enemyFromArray->isDead == false)
                            {
                                //Do Projection here
                                if (distancesBetween < 800)
                                {
                                    if (enemyFromArray->isRunning == false)
                                    {
                                        enemyFromArray->projection->GetSprite()->setVisible(true);
                                        
                                        if (enemyFromArray->projection_direction->compare("FORWARD") == 0 &&  enemyFromArray->canColide == true)
                                        {
                                            if (enemyFromArray->repeatProjections == false)
                                            {
                                                CCSize s = CCDirector::sharedDirector()->getWinSize();
                                                float screenWidth = s.width;
                                                float kitteh_x = kitteh->getPositionX();
                                                
                                                enemyFromArray->ProjectionDirectionValueX = - ( (kitteh_x - (screenWidth / 2)) + 50);
                                                enemyFromArray->ProjectionDirectionValueY = 0;
                                            }
                                            enemyFromArray->makeProjection();
                                            

                                        }
                                    }
                                }
                            } else {
                                if (enemyFromArray->repeatProjections == true && enemyFromArray->isDead == false)
                                {
                                    if (distancesBetween < 800)
                                    {
                                        if (enemyFromArray->isMuliProjRunning == false)
                                        {
                                            enemyFromArray->isMuliProjRunning = true;
                                            enemyFromArray->makeProjection();
                                        }
                                    }
                                    
                                }
                            }
                        }
                    }
                }
            }
            //Item collusion
            for (int k=0;k < items->count();k++)
            {
                Item* item = (Item*)items->objectAtIndex(k);
                if (kitteh->Collided(item->GetSprite()->getPositionX(), item->GetSprite()->getPositionY(), item->GetSprite()->getContentSize().width, item->GetSprite()->getContentSize().height, item->GetSprite()->getScale()))
                {
                    if (item->destoryOnCol)
                    {
                        this->removeChild(item->GetSprite(), true);
                        items->removeObject(item);
                    }
                    
                    if (item->type == LIFE)
                    {
                        LiveObject* newKittehz = new LiveObject();
                        newKittehz->AddSprite((char*)"kitteh_run");
                        newKittehz->Run((char*)"kitteh_run", 0.5);
                        newKittehz->setPosition(kitteh->getPositionX()-(60.0f*kitteh->kittens->count()), kitteh->getPositionY()-16);
                        totalKittehSave++;
                        kitteh->kittens->addObject(newKittehz);
                        this->addChild(newKittehz,2);

                    }
                    
                    if (item->type == COIN)
                    {
                        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("pickup_coin.wav");
                        kitteh->coins++;
                        totalCoins++;
                    }
                    
                    if (item->type== POWERUP)
                    {

                        PauseGame();
                        kitteh->GetRunningSprite()->stopAction(kitteh->moveRight);
                        
                        kitteh->JumpDone(1.0);
                        newState = POWER_UP;
                        pauseAmount = 0.5f;
                        state = PAUSE;
                    }
                    
                }
            }
            
            //Mange the little kittehs
            for (int n=0;n<kitteh->kittens->count();n++)
            {
                LiveObject* currentNewKitteh = (LiveObject*) kitteh->kittens->objectAtIndex(n);
                currentNewKitteh->setPosition(kitteh->getPositionX()-(60.0f * (n+1)),kitteh->getPositionY()-16);
            }
            
            //if Kitteh Falls to it's death
            if (kitteh->getPositionY() < 1)
            {
                GameoverText = new AnimeText((char*)"GAMEOVER",kitteh->getPositionX()-400,300);
                GameoverText->SetOpacity(0.00f);
                
                this->addChild(GameoverText,2);
                kitteh->unscheduleAllSelectors();
                kitteh->currentRunningSprite->stopAction(kitteh->moveRight);
                kitteh->moveRight=NULL;
                kitteh->ChangeSprite((char*)"kitteh_run");

                GameoverText->Animate(100, 100);
                pauseAmount=1.0f;
                newState = GAMEOVER;
                state = PAUSE;
            }
            
            if (kitteh->getPositionX() >= levelEnd)
            {
                if (kitteh->special)
                {
                    kitteh->SpecialRunning(0);
                    if (kitteh->hitGround == false)
                    {
                        kitteh->Fall();
                    }
                }
                state = END_OF_LEVEL;
            }
            break;
        }
        case END_OF_LEVEL:
        {
            CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(musicVolume);
            
            if (musicVolume < 0)
            {
                state = SHOW_STATS;
            } else {
                musicVolume -= 0.01f;
            }
            //Mange the little kittehs
            if (kitteh)
            {
                if (kitteh->kittens)
                {
                    for (int n=0;n<kitteh->kittens->count();n++)
                    {
                        LiveObject* currentNewKitteh = (LiveObject*) kitteh->kittens->objectAtIndex(n);
                        currentNewKitteh->setPosition(kitteh->getPositionX()-(60.0f * (n+1)),kitteh->getPositionY()-16);
                    }
                }
            }

            break;
        }
        case POWER_UP:
        {
            int randSpecial = (arc4random() % 4);
            kitteh->DoSpecial(randSpecial);
            state = PLAYMODE;
            break;
        }
        
        case PAUSE:
        {
            pauseCount+= 0.01f;
            
            if (pauseCount >= pauseAmount)
            {
                pauseCount = 0.0f;
                state = newState;
                break;
            }
            break;
        }
        
        case DIED:
        {
            break;
        }
        case GAMEOVER:
        {
            CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(musicVolume);
            if (GameoverText->FadeIn() == false)
            {
                CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
                pauseCount = 0.0;
                pauseAmount=1.5f;
                newState = CLEAN_UP;
                state = PAUSE;
            }
            musicVolume-= 0.1f;
            break;
        }
        case CLEAN_UP:
        {
            
            CleanUp();
            CCScene *pScene = Title::scene();
            level=0;
            CCDirector::sharedDirector()->replaceScene(pScene);
            state = DONE;
            break;
        }
        case SHOW_STATS:
        {
            display->GetSprite()->setPosition(ccp(coinIcon->GetSprite()->getPositionX()+500, 300));
            display->GetSprite()->setVisible(true);
            int kittens = kitteh->kittens->count();
            CCString* totalKittens =  CCString::createWithFormat("Kittens saved: %i", kittens  );
            
            CCLabelTTF* ttf1 = CCLabelTTF::create(totalKittens->getCString(), "Helvetica", 30,
                                                  CCSizeMake(695, 150), kCCTextAlignmentCenter);
            ccColor3B color;
            color.b=0;
            color.r=0;
            color.g=0;
            ttf1->setColor(color);
            ttf1->setPosition(ccp(levelEnd-550, 280));
            this->addChild(ttf1,5);
            
            
            CCString* totalcoinz =  CCString::createWithFormat("Coins Collected: %i", kitteh->coins  );
            
            CCLabelTTF* ttf2 = CCLabelTTF::create(totalcoinz->getCString(), "Helvetica", 30,
                                                  CCSizeMake(695, 150), kCCTextAlignmentCenter);
            ccColor3B color2;
            color2.b=0;
            color2.r=0;
            color2.g=0;
            ttf2->setColor(color);
            ttf2->setPosition(ccp(levelEnd-580, 240));
            this->addChild(ttf2,5);
            if (kitteh)
            {
                if (kitteh->kittens)
                {
                    totalKittehSave += kitteh->kittens->count();
                }
            }
            pauseCount = 0.0;
            pauseAmount=3.0f;
            newState = RESET;
            state = PAUSE;
            
            break;
        }
        case RESET:
        {
            CleanUp();
            if (level == totalLevels)
            {
                CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
                CCScene *ending = Ending::scene();
                CCDirector::sharedDirector()->replaceScene(ending);
                //TODO save coins into file

                const char* fileName = "options";
                CCString path = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);
                CCString writablePath = CCFileUtils::sharedFileUtils()->getWritablePath();

                std::string str = writablePath.getCString();
                str += fileName;

                CCDictionary* options = CCDictionary::createWithContentsOfFile(str.data());
                CCString* savedCoins = (CCString*) options->valueForKey("COINS");

                int newCoinValue = savedCoins->intValue() + totalCoins;
                
                CCString* coinValue = CCString::createWithFormat("%i", newCoinValue);
                options->removeObjectForKey("COINS");
            
                options->setObject(coinValue, "COINS");
                options->writeToFile(str.data());
		
            } else {
                CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
                CCScene *level = Level::scene();
                CCDirector::sharedDirector()->replaceScene(level);
            }
            state=DONE;
            break;
        }
        case ERROR:
        {
            break;
        }
        case WAIT:
        {
            break;
        }
        case DONE:
        {
            break;
        }
    }
    
    
}



void Level::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    switch (state)
    {
        case LOAD:
        {
            break;
        }
        case INTRO:
        {
            break;
        }
        case PLAYMODE:
        {

            kitteh->Jump();
            break;
        }
        case END_OF_LEVEL:
        {
            break;
        }
        case POWER_UP:
        {
            break;
        }
            
        case PAUSE:
        {
            break;
        }
            
        case DIED:
        {
            break;
        }
        case GAMEOVER:
        {
            break;
        }
        case CLEAN_UP:
        {
            break;
        }
        case SHOW_STATS:
        {
            break;
        }
        case RESET:
        {
            break;
        }
        case ERROR:
        {
            break;
        }
    }
}

void Level::PauseGame()
{
    for (int m=0;m<enimes->count();m++)
    {
        Enemy* runningEnemies = (Enemy*) enimes->objectAtIndex(m);
        if (runningEnemies)
        {
            if (runningEnemies->moveLeft)
            {
                runningEnemies->GetRunningSprite()->stopAction(runningEnemies->moveLeft);
                runningEnemies->paused = true;
                runningEnemies->moveLeft=NULL;
                
                //stop enemies projection if it's running
                if (runningEnemies->projection)
                {
                    runningEnemies->projection->stopAction(runningEnemies->projection_moveBy);
                    runningEnemies->projection->isRunning=false;
                    runningEnemies->projection_moveBy=NULL;
                }
            }
        }
    }
    kitteh->GetRunningSprite()->stopAction(kitteh->moveRight);
}

void Level::CleanUp()
{
    
    this->stopAllActions();
    this->unscheduleAllSelectors();
    this->removeAllChildrenWithCleanup(false);    
}



