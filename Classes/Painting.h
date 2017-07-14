#ifndef __PAINTING_SCENE_H__
#define __PAINTING_SCENE_H__

#include "cocos2d.h"
#include "../cocos/ui/CocosGUI.h"

using namespace cocos2d::ui;
using namespace cocos2d;

class Painting : public cocos2d::Layer
{
private:
	Sprite* brush;
	ClippingNode* clipper;
	std::string texture = "res/HelloWorld.png";
	LayerColor* l;
	SpriteBatchNode* _nodeStencil;
	SpriteBatchNode* batch;
	bool isPen = true;
	Color3B penColor = Color3B::BLACK;

	bool isChange = false;
	int state = 0;
	
	void bPatternClick(Ref* ref);

	bool onTouchBegan(Touch* touch, Event* events);
	void onTouchMoved(Touch* touch, Event* events);
	void onTouchEnded(Touch* touch, Event* events);
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(Painting);
};

#endif // __HELLOWORLD_SCENE_H__
