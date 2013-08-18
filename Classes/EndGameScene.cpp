#include "EndGameScene.h"
#include "Dolphin.h"
#include "Diver.h"

enum {
	kTagLayerDiver = 4,
	kTagLayerDolphin = 8,
};

bool EndGameScene::init()
{
	return true;
}

void EndGameScene::runLoveEvent()
{
	scheduleOnce( schedule_selector(EndGameScene::actionLove), 3);
}

void EndGameScene::actionLove(float dt)
{
	// dolphin love action
	Array *arrChildren = getChildren();
	Object* pObj = NULL;
	DolphinLayer* dolphinL;

	CCARRAY_FOREACH(arrChildren, pObj)
	{
		if( kTagLayerDolphin == ((Node*)pObj)->getTag() )
		{
			dolphinL = static_cast<DolphinLayer*>(pObj);

			if(dolphinL && dolphinL->isAttachedToDiver)
				dolphinL->runLoveAction();
		}
	}

	// diver love action
	DiverLayer* diverL = (DiverLayer*)getChildByTag(kTagLayerDiver);
	diverL->runLoveAction();
}