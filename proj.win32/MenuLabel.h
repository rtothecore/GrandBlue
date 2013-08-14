#ifndef __MENU_LABEL_H__
#define __MENU_LABEL_H__

#include "cocos2d.h"

USING_NS_CC;

class MenuLabelLayer : public Layer
{
public:
	Menu* menu;
	char* fontFile;

	MenuLabelLayer(char* chrLabel);
	~MenuLabelLayer(void);

	void init(char* chrLabel);
	void addMenuItem(char* chrLabel);
	void createMenu();

	void renameMenuItem(int itemIndex, char* chrLabel);
};

#endif
