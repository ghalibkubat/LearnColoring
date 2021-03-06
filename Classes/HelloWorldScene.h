#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "../cocos/ui/CocosGUI.h"

using namespace cocos2d::ui;
using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
private:
    
    RenderTexture* target;
    Sprite* brush;
    
    bool onTouchBegan(Touch* touch, Event* events);
    void onTouchMoved(Touch* touch, Event* events);
    void onTouchEnded(Touch* touch, Event* events);
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
