#ifndef __MAINGAME_DATA_H__
#define __MAINGAME_DATA_H__

#include "cocos2d.h"
#include "Diver.h"
#include "DiveFeet.h"
#include "Fever.h"

USING_NS_CC;

class MainGameDataLayer : public Layer
{
public:
	CREATE_FUNC(MainGameDataLayer);
	virtual bool init();

	static bool isSaveDiver;
	static void saveDiver(DiverLayer* diverL);
	static DiverLayer* loadDiver();
	static void resetDiver();

	static bool isSaveDivedFeet;
	static void saveDivedFeet(DiveFeetLayer* diveFeetL);
	static DiveFeetLayer* loadDivedFeet();
	static void resetDivedFeet();

	static bool isSaveFever;
	static void saveFever(FeverLayer* feverL);
	static FeverLayer* loadFever();
	static void resetFever();

	//reset
	static void resetAllData();
};

#endif