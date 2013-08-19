#include "EndGameScene.h"
#include "Diver.h"
#include "MarineLife.h"
#include "MainGameBase.h"
#include "Tags.h"

bool EndGameScene::init()
{
	return true;
}

void EndGameScene::initWithMarinelifeTag(int tagVal)
{
	iTagForMarinelife = tagVal;
}

void EndGameScene::runLoveEvent()
{
	scheduleOnce( schedule_selector(EndGameScene::actionLove), 3);
}

void EndGameScene::actionLove(float dt)
{
	// marinelife love action
	Array *arrChildren = getChildren();
	Object* pObj = NULL;
	MarineLifeLayer* marinelifeL;

	MainGameBaseLayer* parent = (MainGameBaseLayer*)getParent();

	CCARRAY_FOREACH(arrChildren, pObj)
	{
		if( iTagForMarinelife == ((Node*)pObj)->getTag() )
		{
			marinelifeL = static_cast<MarineLifeLayer*>(pObj);

			if(marinelifeL && marinelifeL->isAttachedToDiver)
				marinelifeL->runLoveAction();
		}
	}

	// diver love action
	DiverLayer* diverL = (DiverLayer*)getChildByTag(kTagLayerDiver);
	diverL->runLoveAction();
}