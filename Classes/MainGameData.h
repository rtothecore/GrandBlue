#ifndef __MAINGAME_DATA_H__
#define __MAINGAME_DATA_H__

#include "cocos2d.h"
#include "Diver.h"
#include "DiveFeet.h"
#include "Fever.h"
#include "SpriteRepeater.h"

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

	static bool isSaveRocks;
	static void saveRocks(Rocks* rocks);
	static Rocks* loadRocks();
	static void resetRocks();

	// reset
	static void resetAllData();

	// for score
	static void saveAllGameResult(int DivedFeet, int ByeCount, int LovePoint, int FeverCount, int DiverLapCount);
	static int getDivedFeet();
	static int getByeCount();
	static int getLovePoint();
	static int getFeverCount();
	static int getDiverLapCount();
};

#endif