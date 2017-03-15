//
//  AnimeText.h
//  KittehAdventure
//
//  Created by code on 2014/11/04.
//
//

#ifndef __KittehAdventure__AnimeText__
#define __KittehAdventure__AnimeText__

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "cocos2d.h"
#include "Object.h"


class AnimeText : public Object
{
    public:
        CCArray* Letters;
        CCArray* LetterObjects;
        char* newText;
        float padding;
        int X;
        int Y;
        float fadeIn;

    
        AnimeText(char* text,float x=100, float y=100);
        ~AnimeText();
    
        bool Animate(int x, int y);
        bool FadeIn();
        void SetOpacity(float opToSet);
};


#endif /* defined(__KittehAdventure__AnimeText__) */
