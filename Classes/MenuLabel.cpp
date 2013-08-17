#include "MenuLabel.h"

bool MenuLabelLayer::init()
{
	fontFile = "fonts/Courier.fnt";

	return true;
}

void MenuLabelLayer::initWithLabel(char* chrLabel, float scaleVal)
{
	// Label Item (LabelBMFont)
    LabelBMFont* label = LabelBMFont::create(chrLabel, fontFile);
    MenuItemLabel* item = MenuItemLabel::create(label);
    item->setScale( scaleVal );
	item->setTag(0);

	// create menu
	menu = Menu::create( item, NULL);
}

void MenuLabelLayer::addMenuItem(char* chrLabel, float scaleVal)
{
	// Label Item (LabelBMFont)
    LabelBMFont* label = LabelBMFont::create(chrLabel, fontFile);
    MenuItemLabel* item = MenuItemLabel::create(label);
    item->setScale( scaleVal );

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
	addChild(menu);
}

void MenuLabelLayer::renameMenuItem(int itemIndex, char* chrLabel)
{
	MenuItemLabel* item = (MenuItemLabel*)menu->getChildByTag(itemIndex);
	item->setLabel(LabelBMFont::create(chrLabel, fontFile));
}