#include "Painting.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* Painting::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Painting::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Painting::init()
{

	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("gambar/bgStage.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg);

	auto apel = Sprite::create("gambar/201.png");
	apel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	auto stencil = Sprite::create("gambar/201a.png");

	auto clip = ClippingNode::create();
	clip->setAnchorPoint(Vec2(0.5, 0.5));
	clip->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	clip->setAlphaThreshold(0.05f);
	clip->setStencil(stencil);

	//clip->addChild(stencil);
	this->addChild(clip);

	//stencil = Sprite::create("gambar/brush.png");
	//stencil->setScale(5);
	//stencil->setColor(Color3B(255, 0, 0));
	l = LayerColor::create(Color4B::WHITE);
	l->setPosition(- clip->getPosition());
	clip->addChild(l);

	_nodeStencil = Node::create();

	clipper = ClippingNode::create();
	clipper->setAnchorPoint(Vec2(0.5, 0.5));
	//clipper->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
	clipper->setAlphaThreshold(0.05f);
	clipper->setStencil(_nodeStencil);

	l->addChild(clipper);

	brush = Sprite::create("res/HelloWorld.png");
	brush->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	clipper->addChild(brush);

	/*target = RenderTexture::create(visibleSize.width, visibleSize.height, Texture2D::PixelFormat::RGBA8888, GL_DEPTH24_STENCIL8);
	target->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
	target->retain();

	this->addChild(target);*/

	auto bkuning = Button::create("pattern/paint_a.png");
	auto warnakuning = Sprite::create("pattern/paint_b.png");
	warnakuning->setColor(Color3B::ORANGE);
	warnakuning->setPosition(Vec2(bkuning->getContentSize().width / 2, bkuning->getContentSize().height / 2));
	bkuning->addChild(warnakuning);
	bkuning->setPosition(Vec2(1000, 100));
	bkuning->setTag(0);
	bkuning->addClickEventListener(CC_CALLBACK_1(Painting::bPatternClick, this));

	auto bbiru = Button::create("pattern/paint_a.png");
	auto warnabiru = Sprite::create("pattern/paint_b.png");
	warnabiru->setColor(Color3B::BLUE);
	warnabiru->setPosition(Vec2(bbiru->getContentSize().width / 2, bbiru->getContentSize().height / 2));
	bbiru->addChild(warnabiru);
	bbiru->setPosition(Vec2(1000, 300));
	bbiru->setTag(1);
	bbiru->addClickEventListener(CC_CALLBACK_1(Painting::bPatternClick, this));

	auto bmerah = Button::create("pattern/paint_a.png");
	auto warnamerah = Sprite::create("pattern/paint_b.png");
	warnamerah->setColor(Color3B::RED);
	warnamerah->setPosition(Vec2(bbiru->getContentSize().width / 2, bbiru->getContentSize().height / 2));
	bmerah->addChild(warnamerah);
	bmerah->setPosition(Vec2(1000, 500));
	bmerah->setTag(2);
	bmerah->addClickEventListener(CC_CALLBACK_1(Painting::bPatternClick, this));

	auto bhijau = Button::create("pattern/paint_a.png");
	auto warnahijau = Sprite::create("pattern/paint_b.png");
	warnahijau->setColor(Color3B::GREEN);
	warnahijau->setPosition(Vec2(bbiru->getContentSize().width / 2, bbiru->getContentSize().height / 2));
	bhijau->addChild(warnahijau);
	bhijau->setPosition(Vec2(1000, 700));
	bhijau->setTag(3);
	bhijau->addClickEventListener(CC_CALLBACK_1(Painting::bPatternClick, this));

	this->addChild(bkuning);
	this->addChild(bbiru);
	this->addChild(bmerah);
	this->addChild(bhijau);
	//this->addChild(clipper);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Painting::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Painting::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Painting::onTouchEnded, this);
	this->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void Painting::bPatternClick(cocos2d::Ref *ref)
{
	auto b = (Button*)ref;
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if (b->getTag() < 2) {
		_nodeStencil = Node::create();

		clipper = ClippingNode::create();
		clipper->setAnchorPoint(Vec2(0.5, 0.5));
		//clipper->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
		clipper->setAlphaThreshold(0.05f);
		clipper->setStencil(_nodeStencil);

		l->addChild(clipper);

		brush = Sprite::create("res/HelloWorld.png");
		brush->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		clipper->addChild(brush);

		if (b->getTag() == 0)
			brush->setTexture("pattern/3.png");
		else if (b->getTag() == 1)
			brush->setTexture("pattern/2.png");
		isPen = false;
	}
	else {
		isPen = true;
		if (b->getTag() == 2) penColor = Color3B::RED;
		else if (b->getTag() == 3) penColor = Color3B::GREEN;
	}
}

bool Painting::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *events)
{
	Vec2 start = touch->getLocation();
	Vec2 delta = start;

	cocos2d::log("touch x:%f, y:%f", start.x, start.y);
	cocos2d::log("delta x:%f, y:%f", delta.x, delta.y);

	//target->begin();
	//n->setPosition(start);
	//brush->setPosition(delta);
	//n->visit();

	//target->end();

	auto st = Sprite::create("gambar/brush.png");
	st->setPosition(start);
	if (!isPen) _nodeStencil->addChild(st);
	else {
		st->setColor(penColor);
		l->addChild(st);
	}

	return true;
}

void Painting::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *events)
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

	Vec2 start = touch->getPreviousLocation();
	Vec2 end = touch->getLocation();

	//target->begin();
	//n->setPosition(start);
	//brush->setPosition(delta);
	//n->visit();

	//target->end();

	auto st = Sprite::create("gambar/brush.png");
	st->setPosition(start);
	if (!isPen) _nodeStencil->addChild(st);
	else {
		st->setColor(penColor);
		l->addChild(st);
	}

	float distance = start.getDistance(end);
	if (distance > 1) {
		int d = (int)distance / 5;

		for (int i = 0; i < d; i++)
		{
			float difx = end.x - start.x;
			float dify = end.y - start.y;
			float delta = (float)(i * 5) / distance;

			auto st = Sprite::create("gambar/brush.png");
			st->setPosition(Vec2(start.x + (difx * delta), start.y + (dify * delta)));
			if (!isPen) _nodeStencil->addChild(st);
			else {
				st->setColor(penColor);
				l->addChild(st);
			}
		}
	}
}

void Painting::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *events)
{

}
