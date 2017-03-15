//
//  Object.cpp
//  KittehAdventure
//
//  Created by code on 2014/11/02.
//
//

#include "Object.h"


Object::Object()
{
    init();
}

Object::~Object()
{

    this->removeAllChildren();
    
    if (AddedFrames)
    {
        delete AddedFrames;
        AddedFrames=NULL;
    }
    

    
    if (layers)
    {
        for (int i=0;i < layers->count();i++)
        {
            CCLayer* deletelayer = (CCLayer*) layers->objectAtIndex(i);
            if (deletelayer)
            {
                delete deletelayer;
                deletelayer=NULL;
            }
        }
        delete layers;
        layers=NULL;
    }
    
    if (sprites)
    {
        delete sprites;
        sprites=NULL;
    }
    /*
    if (mainLayer)
    {
        delete mainLayer;
        mainLayer=NULL;
    }*/

}

bool Object::init()
{
    
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    
    sprites = NULL;
    mainSprite=NULL;
    
    layers=NULL;
    mainLayer=NULL;
    AddedFrames=NULL;
    
    AddedFrames = new CCArray();
    bcount=0;
    canColide = true;
    layers = new CCArray();
    
    

    
    return true;
}



bool Object::AddSprite(char* nameOfSpriteName, int numberOfFrames)
{
    CCSpriteBatchNode* spriteBash;
    CCArray* walkFrames = new CCArray();
    CCSprite *firstSprite;
    CCString* pngName;
    CCString* plistName;
    CCString* realSpriteName;
    
    

    
    if (sprites == NULL)
    {
        sprites = new CCDictionary();
    }
    
    animeSpeed=0.10f;
    plistName = CCString::createWithFormat("%s.plist", nameOfSpriteName);

    pngName = CCString::createWithFormat("%s.png", nameOfSpriteName);
    
    
    realSpriteName = CCString::createWithFormat("%s", nameOfSpriteName); //new CCString();
    
    CCSpriteFrameCache::sharedSpriteFrameCache( )->addSpriteFramesWithFile(plistName->getCString());
    spriteBash = CCSpriteBatchNode::create(pngName->getCString());

    
    
    if (spriteBash == NULL)
    {
        CCLog("error loading sprites");
        return NULL;
    }
    

    
    for (int i=1;i<numberOfFrames;i++)
    {
        CCString* spriteName = CCString::createWithFormat("%s%i.png",nameOfSpriteName, i);
        
        if (spriteName)
        {
            
            CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache( )->spriteFrameByName(spriteName->getCString());
            
            if (spriteFrame)
            {
                bcount++;
                walkFrames->addObject( spriteFrame);
            }
        }
    }
    
    
    
    CCAnimation *walkAnim = CCAnimation::createWithSpriteFrames(walkFrames,animeSpeed);
    
    if (walkAnim == NULL)
    {
        CCLog("error");
        return false;
    }
    
    CCString* nameOfFirstSprite = CCString::createWithFormat("%s1.png", nameOfSpriteName);
    firstSprite = new CCSprite();
    

    
    firstSprite->initWithSpriteFrameName(nameOfFirstSprite->getCString());

    realWidth=firstSprite->getContentSize().width;
    realHeight=firstSprite->getContentSize().height;
    
    
    
    spriteBash->addChild(firstSprite);

    
    mainSprite = firstSprite;

    
    if (firstSprite == NULL)
    {
        CCLog("error");
        return false;
    }
    
    CCDictionary* info = new CCDictionary;
    
    info->setObject(spriteBash, "SpriteBash");
    info->setObject(walkFrames, "Frames");
    info->setObject(firstSprite, "Sprite");
    info->setObject(pngName, "png");
    info->setObject(realSpriteName, "SpriteName");

    info->setObject(plistName, "plist");
    
    sprites->setObject(info, nameOfSpriteName );
    
    CCLayer* newNode =  new CCLayer();
    newNode->addChild(spriteBash);
    layers->addObject(newNode);
    
    mainLayer = newNode;
    
    

    
/*
    if (pngName)
    {
        delete pngName;
        pngName=NULL;
    }
    /*
    if (realSpriteName)
    {
        delete realSpriteName;
        realSpriteName=NULL;
    }
 
    if (info)
    {
        delete info;
        info=NULL;
    }
 
    if (firstSprite)
    {
        delete firstSprite;
        firstSprite=NULL;
    }
 */
    return true;
}

void Object::update(float delta)
{

}

CCDictionary* Object::GetSpritesInfo(char* sInfo)
{
    CCDictionary* getSpriteFromDictionary = (CCDictionary*) sprites->objectForKey(sInfo);
    return getSpriteFromDictionary;
}

bool Object::Run(char* spriteToRun, float secs)
{

    CCDictionary* getSpriteFromDictionary = GetSpritesInfo(spriteToRun);
    
    if (getSpriteFromDictionary)
    {
        CCAction *walkAction;

        CCString* pngname = (CCString*)getSpriteFromDictionary->objectForKey("png");
        
        CCArray* spriteFrame = (CCArray*) getSpriteFromDictionary->objectForKey("Frames");
        
        CCSpriteBatchNode* bNode = (CCSpriteBatchNode*) getSpriteFromDictionary->objectForKey("SpriteBash");
        
        CCSprite *firstSprite = (CCSprite*) getSpriteFromDictionary->objectForKey("Sprite");

        
        CCAnimation *walkAnim;
        
        CCAnimate* walkAnimation;

        
        walkAnim = CCAnimation::createWithSpriteFrames(spriteFrame,secs);

        walkAnimation = CCAnimate::create(walkAnim);

        getSpriteFromDictionary->setObject(walkAnimation, "Animation");

        walkAction = CCRepeatForever::create(walkAnimation);


        getSpriteFromDictionary->setObject(walkAction, "Action");
        
        bool isDup=false;
    
        for (int i=0;i< AddedFrames->count();i++)
        {
            if ( AddedFrames->objectAtIndex(i) == pngname )
            {
                isDup = true;
       
                break;
            }
                
        }
        
        if (isDup == false)
        {
            if (pngname)
            {
                AddedFrames->addObject(pngname);
                
                bcount++;
            }
        }
        
        
        firstSprite->runAction(walkAction);
        
    } else {
        return false;
    }
    
    return true;
}

bool Object::SetSprite(char* filename)
{
    mainSprite = new CCSprite();
    mainSprite->initWithFile(filename);
    
    realWidth=mainSprite->getContentSize().width;
    realHeight=mainSprite->getContentSize().height;
    
    return true;
}


CCSprite* Object::GetSprite()
{
    return mainSprite;
}

CCSpriteBatchNode* Object::GetBatchNodeFromSprite(char* nsprite)
{
    CCDictionary* dic = GetSpritesInfo(nsprite);
    CCSpriteBatchNode* bNode;
    
    if (dic)
    {
        bNode = (CCSpriteBatchNode*) dic->objectForKey("SpriteBash");
    } else {
        return NULL;
    }
    return bNode;
}

CCSprite* Object::GetSpriteFrom(char* sName)
{
    CCDictionary* dic = GetSpritesInfo(sName);
    
    if (dic)
    {
    
        return (CCSprite*) dic->objectForKey("Sprite");
    }
    return NULL;
}

void Object::SetMainLayer(char* spritename)
{
  
    mainLayer = (CCLayer*)  layers->objectAtIndex(1);
    return ;
    CCSpriteBatchNode* bNode = GetBatchNodeFromSprite(spritename);
    
    for (int i;i<layers->count();i++)
    {
        CCLayer* layer = (CCLayer*) layers->objectAtIndex(i);
        
        for (int j=0;j<layer->getChildrenCount();i++)
        {
            CCSpriteBatchNode* bnode = (CCSpriteBatchNode*) layer->getChildren()->objectAtIndex(j);
            if (bnode == bNode)
            {
                mainLayer = layer;
                return ;
            }
        }
        
        

    }

}


