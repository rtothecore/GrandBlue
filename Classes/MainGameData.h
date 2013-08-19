#ifndef __MAINGAME_DATA_H__
#define __MAINGAME_DATA_H__

#include "cocos2d.h"
#include "Diver.h"

USING_NS_CC;

class MainGameDataLayer : public Layer
{
public:
	CREATE_FUNC(MainGameDataLayer);
	virtual bool init();

	static bool isSaveDiver;
	static void saveDiver(DiverLayer* diverL);
	static DiverLayer* loadDiver();

	//void saveAttachedMarinelife();
	//void saveFeet();
};

#endif