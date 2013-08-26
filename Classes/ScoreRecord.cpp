#include "ScoreRecord.h"
#include "Resource.h"
#include "UtilFunc.h"

bool ScoreRecordLayer::init()
{
	return true;
}

bool ScoreRecordLayer::is1stScore(int newScore)
{
	int oldScore = readScoreFromPlist();

	if(oldScore < newScore)
	{
		writeScoreToPlist(newScore);
		return true;
	}

	return 0;
}

void ScoreRecordLayer::writeScoreToPlist(int score)
{
    Dictionary *root = Dictionary::create();
	String *strScore = String::createWithFormat("%d", score);
	//Integer* iScore = Integer::create(score);	//----WARNING--- Dictionary can't write Integer Object
	
	root->setObject(strScore, k_1stScore);

    // end with /
	std::string writablePath = FileUtils::getInstance()->getWritablePath();
	std::string fullPath = writablePath + p_Score;

    if(root->writeToFile(fullPath.c_str()))
        log("see the plist file at %s", fullPath.c_str());
    else
        log("write plist file failed");
}

int ScoreRecordLayer::readScoreFromPlist()
{
	std::string writablePath = FileUtils::getInstance()->getWritablePath();
	std::string fullPath = writablePath + p_Score;
	
	if( FileUtils::getInstance()->isFileExist(fullPath.c_str()) )
	{
		Dictionary *root = Dictionary::createWithContentsOfFile(fullPath.c_str());
		String* score = (String*)(root->objectForKey(k_1stScore));
		
		return score->intValue();
	}

	return 0;
}

void ScoreRecordLayer::addHighScoreLabel(Layer* lyr, Color3B color)
{
	Size winSize = UtilFunc::getWinSize();

	// 1st Score
	Size blockSizeForScore = Size(winSize.width, 100);
    float fontSizeForScore = 12;
	String* str1stScore = String::createWithFormat("HIGH SCORE : %d", ScoreRecordLayer::readScoreFromPlist());

	LabelTTF *label1stScore = LabelTTF::create(str1stScore->getCString(), FONT_TITLE_FILE, fontSizeForScore, 
										blockSizeForScore, Label::HAlignment::CENTER, Label::VAlignment::TOP);
	label1stScore->setColor(color);
	label1stScore->setZOrder(1);
	label1stScore->setPosition( Point(winSize.width/2, winSize.height - (label1stScore->getContentSize().height/2)) );
	lyr->addChild(label1stScore);
}