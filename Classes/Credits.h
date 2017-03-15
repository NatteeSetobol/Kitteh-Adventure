//
//  Credits.h
//  KittehAdventure
//
//  Created by code on 2014/12/23.
//
//

#ifndef __KittehAdventure__Credits__
#define __KittehAdventure__Credits__

#include <stdio.h>
#include "cocos2d.h"
#include "Intro.h"


class Credits: public cocos2d::CCLayer {
    public:
        CCLayerColor *faderLayer;
        static cocos2d::CCScene* scene();
        virtual bool init();
        void ShowLogo(float dt);
    CREATE_FUNC(Credits);

};


#endif /* defined(__KittehAdventure__Credits__) */
