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

	void initWithLabel(char* chrLabel, float scaleVal);
	void addMenuItem(const char* chrLabel, float scaleVal);
	void createMenu();

	void renameMenuItem(int itemIndex, const char* chrLabel);
};

#endif
