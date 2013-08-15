#ifndef __MENU_LABEL_H__
#define __MENU_LABEL_H__

#include "cocos2d.h"

USING_NS_CC;

class MenuLabelLayer : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(MenuLabelLayer);

	Menu* menu;
	char* fontFile;

	void initWithLabel(char* chrLabel);
	void addMenuItem(char* chrLabel);
	void createMenu();

	void renameMenuItem(int itemIndex, char* chrLabel);
};

#endif
