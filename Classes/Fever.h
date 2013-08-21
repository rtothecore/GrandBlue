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

	int iMarineLifeBye;
	int iTouchCombo;

	// ProgressBar
	void initProgressBar();

	// Fever
	void checkFever();
	void intoTheFever();
	void endFever(float dt);

	// label
	void addFeverLabel();

public:
	virtual bool init();
	CREATE_FUNC(FeverLayer);

	int getTouchDamage();
	bool isFever();

	int getTouchComboForFever();
	
	// Touch Combo 
	void increaseTouchCombo();
	void resetTouchCombo();
	int getTouchCombo();
	void setTouchCombo(int touchComboVal);

	// Marinelife bye
	void increaseMarinelifeBye();
	int getMarinelifeBye();
	void setMarinelifeBye(int mlByeVal);
	
	void refreshProgressBar();
};

#endif