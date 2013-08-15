#ifndef __FEVER_H__
#define __FEVER_H__

#include "cocos2d.h"

USING_NS_CC;

class FeverLayer : public Layer
{
private:
	// Touch Fever
	bool bFeverMode;

	static const int st_touchComboForFever = 5;
	static const int st_touchDamage = 1;
	static const int st_touchDamageFever = 3;
	static const int st_feverTime = 10;

	int iTouchCombo;

	// ProgressBar
	void initProgressBar();
	void refreshProgressBar();

	// Fever
	void checkFever();
	void intoTheFever();
	void endFever(float dt);

public:
	virtual bool init();
	CREATE_FUNC(FeverLayer);

	int getTouchDamage();
	bool isFever();
	int getTouchComboForFever();
	int getTouchCombo();

	// Touch Combo 
	void increaseTouchCombo();
	void resetTouchCombo();
};

#endif