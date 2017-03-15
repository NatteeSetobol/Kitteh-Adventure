//
//  KittehStore.h
//  KittehAdventure
//
//  Created by code on 2015/01/30.
//
//

#ifndef __KittehAdventure__KittehStore__
#define __KittehAdventure__KittehStore__

#include <stdio.h>
#include "cocos2d.h"
#include "AnimeText.h"
#include "Title.h"
USING_NS_CC;

class KittehStore: public cocos2d::CCLayer
{
    private:
    

    public:
        virtual bool init();
        static cocos2d::CCScene* scene();
        AnimeText* Kitteh;
        AnimeText* Store;
        Object* box;
        CCLabelTTF* GoBackText=NULL;

        void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);


    CREATE_FUNC(KittehStore);


};

#endif /* defined(__KittehAdventure__KittehStore__) */
