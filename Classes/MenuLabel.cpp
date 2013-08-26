#include "MenuLabel.h"
#include "Resource.h"

bool MenuLabelLayer::init()
{
	fontFile = "fonts/Fixedsys.fnt";

	return true;
}

void MenuLabelLayer::initWithLabel(char* chrLabel, float scaleVal)
{
	// Label Item (LabelTTF)
	Size winSize = Director::getInstance()->getWinSize();
	Size blockSize = Size(winSize.width/2, winSize.height/20);
    float fontSize = 18;

	LabelTTF *label = LabelTTF::create(chrLabel, FONT_MENU_FILE, fontSize, 
										blockSize, Label::HAlignment::CENTER, Label::VAlignment::CENTER);
	MenuItemLabel* item = MenuItemLabel::create(label);
    //item->setScale( scaleVal );
	item->setTag(0);

	// create menu
	menu = Menu::create( item, NULL);
}

void MenuLabelLayer::addMenuItem(const char* chrLabel, float scaleVal)
{
	// Label Item (LabelTTF)
	Size winSize = Director::getInstance()->getWinSize();
	Size blockSize = Size(winSize.width/2, winSize.height/20);
    float fontSize = 18;

	LabelTTF *label = LabelTTF::create(chrLabel, FONT_MENU_FILE, fontSize, 
										blockSize, Label::HAlignment::CENTER, Label::VAlignment::CENTER);
	MenuItemLabel* item = MenuItemLabel::create(label);
    //item->setScale( scaleVal );

	menu->addChild(item, 0, menu->getChildrenCount());
}

void MenuLabelLayer::createMenu()
{
	menu->alignItemsVertically();

	Size s = Director::getInstance()->getWinSize();

	// elastic effect
	int i=0;
    Node* child;
    Array * pArray = menu->getChildren();
    Object* pObject = NULL;
    CCARRAY_FOREACH(pArray, pObject)
    {
        if(pObject == NULL)
            break;

        child = static_cast<Node*>(pObject);

        Point dstPoint = child->getPosition();
        int offset = (int) (s.width/2 + 50);
        if( i % 2 == 0)
            offset = -offset;
        
        child->setPosition( Point( dstPoint.x + offset, dstPoint.y) );
        child->runAction( EaseElasticOut::create(MoveBy::create(2, Point(dstPoint.x - offset,0)), 0.35f) );
        i++;
    }

	// add menu
	addChild(menu, 0, 0);
}

void MenuLabelLayer::renameMenuItem(int itemIndex, const char* chrLabel)
{
	MenuItemLabel* item = (MenuItemLabel*)menu->getChildByTag(itemIndex);

	Size winSize = Director::getInstance()->getWinSize();
	Size blockSize = Size(winSize.width/2, winSize.height/20);
    float fontSize = 18;

	item->setLabel(LabelTTF::create(chrLabel, FONT_MENU_FILE, fontSize, 
		                            blockSize, Label::HAlignment::CENTER, Label::VAlignment::CENTER));
}