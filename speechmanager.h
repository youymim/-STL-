#pragma once
#include<iostream>
#include<vector>
#include<map>
#include"speaker.h"
#include<algorithm>
#include<deque>
#include<functional>
#include<numeric>
#include<fstream>
#include<random>
using namespace std;
class speechmanager
{
public:
	speechmanager();
	void show_menu();
	void existsystem();
	void initspeech();
	void createspeaker();
	void startspeech();
	void speechdraw();
	void speechcontest();
	void showscore();
	void saverecord();
	void loadrecord();
	void showrecord();
	void clearrecord();
	~speechmanager();
	vector<int>v1;
	vector<int>v2;
	vector<int>vic;
	map<int, speaker>m_speaker;
	int index;
	bool fileisempty;
	map<int, vector<string>>m_record;
};