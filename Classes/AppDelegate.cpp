#include "AppDelegate.h"
#include "Title.h"

USING_NS_CC;


static bool music=true;


AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    pEGLView->getFrameSize();
    
    
    const char* fileName = "options";
    CCString path = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);
    CCString writablePath = CCFileUtils::sharedFileUtils()->getWritablePath();
    
    std::string str = writablePath.getCString();
    str += fileName;
    
    
    
    if (CCFileUtils::sharedFileUtils()->isFileExist(str) == false)
    {
        CCLog("no options file found creating default!");
        CCDictionary* options = CCDictionary::create();
        
        CCString* sound = CCString::create("no");
        options->setObject(sound, "MUSIC");
        
        CCString* coins = CCString::create("0");
        
        options->setObject(coins, "COINS");
        
        options->writeToFile(str.data());
    }     
    //pDirector->setContentScaleFactor(pEGLView->getFrameSize().height/pEGLView->getDesignResolutionSize().height);
    //pEGLView->setDesignResolutionSize(pEGLView->getDesignResolutionSize().width,pEGLView->getDesignResolutionSize().height, kResolutionNoBorder);
#ifdef ANDROID
    //pEGLView->setDesignResolutionSize(2560,1440, kResolutionNoBorder);

    //For LG Tribute
    pEGLView->setDesignResolutionSize(1024,680, kResolutionNoBorder);
#endif

    
    
#ifdef ANDROID
    CCScene *pScene = Nomication::scene();
    pDirector->runWithScene(pScene);
#else
    
    
    
    // create a scene. it's an autorelease object
    CCScene *pScene = Title::scene();
    

    // run
    pDirector->runWithScene(pScene);
    
#endif
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
