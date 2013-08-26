#ifndef __DIVE_FEET_H__
#define __DIVE_FEET_H__

#include "cocos2d.h"

USING_NS_CC;

class DiveFeetLayer : public Layer
{
private:
	int currentDivedFeet;
	int diveStep;
	int sceneDivedFeet;

	void initWithLabel();
	void incrementDiveFeet(float dt);

	void resetDiveStep(float dt);

public:
	virtual bool init();
	CREATE_FUNC(DiveFeetLayer);

	void startDive();
	void stopDive();
	void setDiveStepWithTime(int diveStepVal, float timeVal);
	void setDiveStep(int diveStepVal);
	int getDivedFeet();
	void setDivedFeet(int divedFeetValue);

	bool isMaxDivedFeetAtScene(int maxDivedFeet);
};

#endif