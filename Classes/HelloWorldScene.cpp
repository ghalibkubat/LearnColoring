#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto bg = Sprite::create("gambar/bgStage.png");
    bg->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    
    auto stencil = Sprite::create("gambar/201a.png");
    
    brush = Sprite::create("gambar/brush.png");
    brush->setColor(Color3B(255, 0, 0));
    brush->setScale(0.7);
    brush->retain();
    
    auto apel = Sprite::create("gambar/201.png");
    apel->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    
    auto clipper = ClippingNode::create();
    clipper->setAnchorPoint(Vec2(0.5, 0.5));
    clipper->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    clipper->setAlphaThreshold(0.05f);
    clipper->setStencil(stencil);
    
    target = RenderTexture::create(visibleSize.width, visibleSize.height, Texture2D::PixelFormat::RGBA8888);
    target->setPosition(Vec2(clipper->getContentSize().width/2, clipper->getContentSize().height/2));
    target->retain();
    
    clipper->addChild(stencil);
    clipper->addChild(target);
    
    //stencil->runAction(RepeatForever::create(RotateBy::create(1.0f, 90.0f)));
    
    this->addChild(bg);
    
    this->addChild(clipper);
    //this->addChild(target);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    this->getEventDispatcher()->
    addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *events)
{
    Vec2 start = touch->getLocation();
    
    target->begin();
    brush->setPosition(start);
    brush->retain();
    target->end();
    
    return true;
}

void HelloWorld::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *events)
{
    Vec2 end = touch->getLocation();
    Vec2 start = touch->getPreviousLocation();
    
    target->begin();
    
    int distance = (int)start.distance(end);
    
    for(int i=0;i<distance;i++){
        float difx = end.x - start.x;
        float dify = end.y - start.y;
        float delta = (float)i / distance;
        
        auto spriteframe = brush->getSpriteFrame();
        auto b = Sprite::createWithSpriteFrame(spriteframe);
        b->setColor(Color3B(255, 0, 0));
        b->setPosition(Vec2(start.x + (difx * delta), start.y + (dify * delta)));
        b->visit();
    }
    
    target->end();
}

void HelloWorld::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *events)
{

}
