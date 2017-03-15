//
//  KittehStore.cpp
//  KittehAdventure
//
//  Created by code on 2015/01/30.
//
//

#include "KittehStore.h"

CCScene* KittehStore::scene()
{
    CCScene *scene = CCScene::create();
    
    KittehStore *layer = KittehStore::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool KittehStore::init()
{
    CCString path;
    CCString writablePath;
    std::string str;
    CCDictionary* options;
    CCString* savedCoins=NULL;
    CCString* contextString ;
    CCLabelTTF* coinText=NULL;
    ccColor4B backgroundColor;
    ccColor3B itemCostTextColor;
    CCLayerColor *colorLayer=NULL;


    
    if ( !CCLayer::init() )
    {
        return false;
    }
    this->setTouchEnabled(true);
    
    backgroundColor = ccc4(153, 183, 231, 255);
    colorLayer = CCLayerColor::create(backgroundColor);
    this->addChild(colorLayer);
    
    Kitteh = new AnimeText((char*)"KITTEH");
    this->addChild(Kitteh);
    Kitteh->Animate(280, 480);
    

    Store = new AnimeText((char*) "STORE");
    this->addChild(Store);
    Store->Animate(310, 380);
    
    Object* KittehStoreIcon = new Object;
    KittehStoreIcon->SetSprite((char*)"kittehstore.png");
    KittehStoreIcon->GetSprite()->setPosition(ccp(250,480));
    KittehStoreIcon->GetSprite()->setScale(4.0);
    KittehStoreIcon->GetSprite()->setFlipX(true);
    this->addChild(KittehStoreIcon->GetSprite());
    


    
    path = CCFileUtils::sharedFileUtils()->fullPathForFilename("options");
    writablePath = CCFileUtils::sharedFileUtils()->getWritablePath();
    
    
    str = writablePath.getCString();
    str += "options";
    
    options = CCDictionary::createWithContentsOfFile(str.data());
    
    
    savedCoins = (CCString*) options->objectForKey("COINS");
    
    
    contextString = CCString::createWithFormat("Total Coins: %i", savedCoins->intValue());
    coinText = CCLabelTTF::create(contextString->getCString(), "Helvetica", 30,
                                  CCSizeMake(695, 150), kCCTextAlignmentCenter);
    
    
    coinText->setPosition(ccp(530, 350));
    this->addChild(coinText);
    
    
    
    box = new Object();
    box->SetSprite((char*)"box.png");
    box->GetSprite()->setPosition(ccp(300, 300));
    this->addChild(box->GetSprite());

    Object* must = new Object();
    must->SetSprite((char*) "mustache.png");
    must->GetSprite()->setPosition(ccp(box->GetSprite()->getPositionX(), 310));
    this->addChild(must->GetSprite(),4);
    
    Object* coin = new Object();
    coin->SetSprite((char*) "coin.png");
    coin->GetSprite()->setScale(0.5);
    coin->GetSprite()->setPosition(ccp(box->GetSprite()->getPositionX()-30,280));
    this->addChild(coin->GetSprite(),4);
    
    CCLabelTTF* itemCostText = CCLabelTTF::create("500", "Helvetica", 25,
                                              CCSizeMake(695, 150), kCCTextAlignmentCenter);
    itemCostTextColor = ccc3(0, 0, 0);

    itemCostText->setColor(itemCostTextColor);
    itemCostText->setPosition(ccp(box->GetSprite()->getPositionX()+10, 220));
    
    this->addChild(itemCostText);
    
    GoBackText = CCLabelTTF::create("Go Back", "Helvetica", 30,
                                  CCSizeMake(695, 150), kCCTextAlignmentCenter);
    GoBackText->setPosition(ccp(930, 50));
    
    this->addChild(GoBackText);


    

    
    
    return true;
}


void KittehStore::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    CCSetIterator iter = touches->begin();

    
    for (; iter != touches->end(); iter++)
    {
        CCTouch* pTouch = (CCTouch*)(*iter);
        
        CCPoint location = pTouch->getLocationInView();
        location =CCDirector::sharedDirector()->convertToGL(location);

        
        if (GoBackText->boundingBox().containsPoint(location))
        {
            this->unscheduleAllSelectors();
            CCScene *pScene = Title::scene();
            CCDirector::sharedDirector()->replaceScene(pScene);
            return ;
        }

        
    }
}