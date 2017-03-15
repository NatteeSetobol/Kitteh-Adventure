//
//  AnimeText.cpp
//  KittehAdventure
//
//  Created by code on 2014/11/04.
//
//

#include "AnimeText.h"

AnimeText::AnimeText(char* text, float x, float y)
{
    CCLayer:CCLayer();
    
    Letters=NULL;
    LetterObjects=NULL;
    newText=NULL;

    X=0;
    Y=0;
    fadeIn=0.0f;
    padding=0;
    
    Letters =  CCArray::create();
    LetterObjects =  new CCArray();
    newText = new char[strlen(text)+1];
    strcpy(newText, text);
    

    for (int i=0;i<strlen(text);i++)
    {
       
        Object* letter = new Object();
        char letterToAdd[5];
        sprintf(letterToAdd, "%c",text[i]);

        letter->AddSprite(letterToAdd, 8);
        letter->GetSpriteFrom(letterToAdd)->setPosition(ccp(x, y));
        Letters->addObject(letter->layers->objectAtIndex(0));
        LetterObjects->addObject(letter);
        
        this->addChild((CCLayer*) letter->layers->objectAtIndex(0));
        
        x+=70;
    }
    
    this->setPosition(ccp(x,y));
    
    
}

AnimeText::~AnimeText()
{
    //if (Letters)
   // {
       // delete Letters;
        //Letters=NULL;
    //}
    /*
    if (LetterObjects)
    {
        for (int i=0;i<LetterObjects->count();i++)
        {
            Object* tempLetter = (Object*) LetterObjects->objectAtIndex(i);
            tempLetter->GetSprite()->stopAllActions();
            tempLetter->stopAllActions();
            if (tempLetter)
            {
                delete tempLetter;
                tempLetter=NULL;
            }
        }
        
        delete LetterObjects;
        LetterObjects=NULL;
        
        CCLog("deleted Letter");
    }
    
    if (newText)
    {
        delete newText;
        newText=NULL;
    }
    CCLog("deleted");
     */
}

void AnimeText::SetOpacity(float opToSet)
{
    for (int i=0;i<strlen(newText);i++)
    {
        
        Object* letter = (Object*)LetterObjects->objectAtIndex(i);
        char letterToAdd[5];
        sprintf(letterToAdd, "%c",newText[i]);
        
        letter->GetSpriteFrom(letterToAdd)->setOpacity(opToSet);
        
    }
}

bool AnimeText::FadeIn()
{

    if (fadeIn < 255)
    {
        fadeIn+=3.0;
        SetOpacity(fadeIn);
        return true;
    }
    
    return false;
}


bool AnimeText::Animate(int x, int y)
{
    
    X=x;
    Y=y;
    
    int xPos=X;
    for (int i=0;i<strlen(newText);i++)
    {
        if (newText[i] != '~')
        {
            Object* letter = (Object*)LetterObjects->objectAtIndex(i);
            char letterToAdd[5];
            sprintf(letterToAdd, "%c",newText[i]);
            letter->Run(letterToAdd, 0.3f);
            xPos+=70;
        }
    }
    
    this->setPosition(ccp(x,y));

    
    return true;
}
