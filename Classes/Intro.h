//
//  Intro.h
//  KittehAdventure
//
//  Created by code on 2014/11/02.
//
//

#ifndef __KittehAdventure__Intro__
#define __KittehAdventure__Intro__

#include <stdio.h>
#include "cocos2d.h"
#include "Object.h"
#include "Player.h"
#include "Level.h"

USING_NS_CC;

enum { SCENE_0,SCENE_1,SCENE_2 };


class Intro: public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    Object* house;
    Object* dialog;
    Object* car;
    Object* capturer;
    Object* skipImage;

    
    void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void RunIntro(float dt);
    int Scene;
    float fadeAmount;
    CCLayerColor *bgColorLayer;
    Object* boy;
    Object* rock;
    CCLabelTTF* storyText1;
    CREATE_FUNC(Intro);
    void AnimeDone();
    void kitteh_run_done();
    void kitteh_run_done2();
    Player* player;
    int parts;
    void car_done();
    bool FadeOut();
    bool FadeIn();
    void CleanUp();
};


#endif /* defined(__KittehAdventure__Intro__) */
