#include "Background.h"
#include "Resource.h"
#include "UtilFunc.h"

//------------------------------------------------------------------
//
// EffectAction
//
//----------------------------------------------------------------

class Shaky3DDemo : public Shaky3D 
{
public:
    static ActionInterval* create(float t)
    {
        return Shaky3D::create(t, Size(15,10), 5, false);
    }
};

class LiquidDemo : public Liquid
{
public:
    static ActionInterval* create(float t)
    {
        return Liquid::create(t, Size(16,12), 4, 20);
    }
};

ActionInterval* createEffect(int nIndex, float t)
{
    Director::getInstance()->setDepthTest(false);

    switch(nIndex)
    {
        case 0: return Shaky3DDemo::create(t);
       /* case 1: return Waves3DDemo::create(t);
        case 2: return FlipX3DDemo::create(t);
        case 3: return FlipY3DDemo::create(t);
        case 4: return Lens3DDemo::create(t);
        case 5: return Ripple3DDemo::create(t);*/
        case 6: return LiquidDemo::create(t);
        /*case 7: return WavesDemo::create(t);
        case 8: return TwirlDemo::create(t);
        case 9: return ShakyTiles3DDemo::create(t);
        case 10: return ShatteredTiles3DDemo::create(t);
        case 11: return ShuffleTilesDemo::create(t);
        case 12: return FadeOutTRTilesDemo::create(t);
        case 13: return FadeOutBLTilesDemo::create(t);
        case 14: return FadeOutUpTilesDemo::create(t);
        case 15: return FadeOutDownTilesDemo::create(t);
        case 16: return TurnOffTilesDemo::create(t);
        case 17: return WavesTiles3DDemo::create(t);
        case 18: return JumpTiles3DDemo::create(t);
        case 19: return SplitRowsDemo::create(t);
        case 20: return SplitColsDemo::create(t);
        case 21: return PageTurn3DDemo::create(t);*/
    }

    return NULL;
}

ActionInterval* getAction()
{
    ActionInterval* pEffect = createEffect(6, 3);

    return pEffect;
}

//------------------------------------------------------------------
//
// BackgroundLayer
//
//----------------------------------------------------------------
bool BackgroundLayer::init()
{
	initWithSprite(s_UnderSea);
	return true;
}

void BackgroundLayer::onEnter()
{
    Layer::onEnter();
}

void BackgroundLayer::onExit()
{
    Layer::onExit();
}

void BackgroundLayer::initWithSprite(const char* chrSprt)
{
	// Effect
	effectNode = Node::create();
    addChild(effectNode, 0, 1);

	// Sprite
	Sprite* sprt = Sprite::create(chrSprt);
	sprt->setPosition(Point(UtilFunc::getWinSize().width / 2, UtilFunc::getWinSize().height / 2));
	effectNode->addChild(sprt);
}

void BackgroundLayer::runEffect()
{
	ActionInterval* effect = getAction();
	//effectNode->runAction(effect);
	auto repEffect = RepeatForever::create(effect);

	effectNode->runAction(repEffect);	
}