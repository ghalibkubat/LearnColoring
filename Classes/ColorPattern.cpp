#include "ColorPattern.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* ColorPattern::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ColorPattern::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ColorPattern::init()
{
    
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto stencil = Sprite::create("gambar/brush.png");
    //stencil->setScale(5);
    //stencil->setColor(Color3B(255, 0, 0));
    
    n = Node::create();
    n->retain();
    
    clipper = ClippingNode::create();
    clipper->setAnchorPoint(Vec2(0.5, 0.5));
    //clipper->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    clipper->setAlphaThreshold(0.05f);
    clipper->setStencil(stencil);
    
    n->addChild(clipper);
    
    brush = Sprite::create("res/HelloWorld.png");
    brush->setPosition(Vec2(960/2, 640/2));
    clipper->addChild(brush);
    
    target = RenderTexture::create(visibleSize.width, visibleSize.height, Texture2D::PixelFormat::RGBA8888, GL_DEPTH24_STENCIL8);
    target->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    target->retain();
    
    this->addChild(target);
    
    auto bkuning = Button::create("pattern/paint_a.png");
    auto warnakuning = Sprite::create("pattern/paint_b.png");
    warnakuning->setColor(Color3B::ORANGE);
    warnakuning->setPosition(Vec2(bkuning->getContentSize().width/2, bkuning->getContentSize().height/2));
    bkuning->addChild(warnakuning);
    bkuning->setPosition(Vec2(1000, 100));
    bkuning->setTag(0);
    bkuning->addClickEventListener(CC_CALLBACK_1(ColorPattern::bPatternClick, this));
    
    auto bbiru = Button::create("pattern/paint_a.png");
    auto warnabiru = Sprite::create("pattern/paint_b.png");
    warnabiru->setColor(Color3B::BLUE);
    warnabiru->setPosition(Vec2(bbiru->getContentSize().width/2, bbiru->getContentSize().height/2));
    bbiru->addChild(warnabiru);
    bbiru->setPosition(Vec2(1000, 300));
    bbiru->setTag(1);
    bbiru->addClickEventListener(CC_CALLBACK_1(ColorPattern::bPatternClick, this));
    
    this->addChild(bkuning);
    this->addChild(bbiru);
    //this->addChild(clipper);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(ColorPattern::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(ColorPattern::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(ColorPattern::onTouchEnded, this);
    this->getEventDispatcher()->
    addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void ColorPattern::bPatternClick(cocos2d::Ref *ref)
{
    auto b = (Button*) ref;
    if(b->getTag() == 0)
        brush->setTexture("pattern/3.png");
    else if(b->getTag()==1)
        brush->setTexture("pattern/2.png");
}

bool ColorPattern::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *events)
{
    Vec2 start = touch->getLocation();
    Vec2 delta = Vec2(960/2, 640/2) - start;
    
    cocos2d::log("touch x:%f, y:%f", start.x, start.y);
    cocos2d::log("delta x:%f, y:%f", delta.x, delta.y);
    
    target->begin();
    n->setPosition(start);
    brush->setPosition(delta);
    n->visit();
    
    target->end();
    
    return true;
}

void ColorPattern::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *events)
{
    /*Vec2 end = touch->getLocation();
    Vec2 start = touch->getPreviousLocation();
    
    target->begin();
    
    int distance = (int)start.distance(end) / 2;
    
    for(int i=0;i<distance;i++){
        float difx = end.x - start.x;
        float dify = end.y - start.y;
        float delta = (float)i / distance;
        
        n->setPosition(Vec2(start.x + (difx * delta), start.y + (dify * delta)));
        
        Vec2 start2 = n->getPosition();
        Vec2 delta2 = Vec2(960/2, 640/2) - start2;
        
        brush->setPosition(delta2);
        
        n->visit();
    }
    
    target->end();*/
    
    Vec2 start = touch->getLocation();
    Vec2 delta = Vec2(960/2, 640/2) - start;
    
    cocos2d::log("touch x:%f, y:%f", start.x, start.y);
    cocos2d::log("delta x:%f, y:%f", delta.x, delta.y);
    
    target->begin();
    n->setPosition(start);
    brush->setPosition(delta);
    n->visit();
    
    target->end();
    
}

void ColorPattern::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *events)
{

}
