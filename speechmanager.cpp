#include"speechmanager.h"
speechmanager::speechmanager()
{
	this->initspeech();
	this->createspeaker();
	this->loadrecord();
}
void speechmanager::show_menu()
{
	cout << "欢迎参加演讲比赛" << endl;
	cout << "1.开始演讲比赛" << endl;
	cout << "2.查看往届记录" << endl;
	cout << "3.清空比赛记录" << endl;
	cout << "0.退出比赛程序" << endl;
	cout << endl;
}
void speechmanager::existsystem()
{
	cout << "欢迎下次使用！" << endl;
	exit(0);
}
void speechmanager::initspeech()
{
	this->v1.clear();
	this->v2.clear();
	this->vic.clear();
	this->m_speaker.clear();
	this->index = 1;
	/*this->m_record.clear();*/

}
void speechmanager::createspeaker()
{
	string nameseed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameseed.size(); i++)
	{
		string name;
		name += nameseed[i];
		speaker sp;
		sp.m_name = name;
		for (int j = 0; j < 2; j++)
		{
			sp.m_score[j] = 0;
		}
		this->v1.push_back(i + 10001);
		this->m_speaker.insert(make_pair(i + 10001, sp));
	}
}
void speechmanager::startspeech()
{
	this->speechdraw();
	this->speechcontest();
	this->showscore();
	this->index++;
	this->speechdraw();
	this->speechcontest();
	this->showscore();
	this->saverecord();
	this->initspeech();
	this->createspeaker();
	this->loadrecord();
	cout << "比赛结束！" << endl;
}
void speechmanager::speechdraw()
{
	static default_random_engine e((unsigned int)time(0));
	cout << "第" << this->index << "轮比赛正在抽签" << endl;
	cout << "抽签后演讲顺序如下：" << endl;
	if (this->index == 1)
	{
		shuffle(v1.begin(), v1.end(),e);
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		shuffle(v2.begin(), v2.end(),e);
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	system("pause");
}
void speechmanager::speechcontest()
{
	cout << "第" << this->index << "轮比赛正式开始" << endl;
	multimap<double, int, greater<double>>groupscore;
	int num = 0;
	vector<int>v_src;
	if (this->index == 1)
	{
		v_src = v1;
	}
	else
	{
		v_src = v2;
	}
	deque<double>d;
	for (vector<int>::iterator it = v_src.begin(); it != v_src.end(); it++)
	{
		num++;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10;
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();
		d.pop_back();
		double sum = accumulate(d.begin(), d.end(),0.0f);
		double avg = sum / d.size();
		this->m_speaker[*it].m_score[this->index - 1] = avg;
		groupscore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "轮小组比赛名次：" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupscore.begin(); it != groupscore.end(); it++)
			{
				cout << "编号：" << it->second << "姓名：" << this->m_speaker[it ->second].m_name << "成绩："
					<< this->m_speaker[it->second].m_score[this->index - 1] << endl;
			}
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupscore.begin(); it != groupscore.end() && count < 3; it++, count++)
			{
				if (this->index == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					vic.push_back((*it).second);
				}
			}
			groupscore.clear();
			cout << endl;
		}
	}
	cout << "第" << this->index << "轮比赛完毕！" << endl;
	system("pause");
}
void speechmanager::showscore()
{
	cout << "第" << this->index << "轮晋级选手信息如下：" << endl;
	vector<int>v;
	if (this->index == 1)
	{
		v = v2;
	}
	else
	{
		v = vic;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "选手编号：" << *it << "姓名：" << m_speaker[*it].m_name << "得分：" << m_speaker[*it].m_score[this->index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_menu();
}
void speechmanager::saverecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	for (vector<int>::iterator it = vic.begin(); it != vic.end(); it++)
	{
		ofs << *it << "," << m_speaker[*it].m_score[1] ;
	}
	ofs << endl;
	ofs.close();
	cout << "记录已保存" << endl;
	this->fileisempty = false;
}
void speechmanager::loadrecord()
{
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open())
	{
		this->fileisempty = true;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->fileisempty = true;
		ifs.close();
		return;
	}
	this->fileisempty = false;
	ifs.putback(ch);
	string data;
	int index = 0;
	while (ifs >> data)
	{
		vector<string>v;
		int pos = -1;
		int start = 0;
		// 替换你原来的内层 while(true) 部分
		while (true)
		{
			pos = data.find(",", start);
			// 情况1：找不到逗号，说明到最后一个字段了
			if (pos == -1)
			{
				// 把最后一段内容取出来
				string last = data.substr(start);
				v.push_back(last);
				break; // 退出分割循环，不要 return！
			}
			// 情况2：找到逗号，正常截取
			string temp = data.substr(start, pos - start);
			v.push_back(temp);
			start = pos + 1;
		}
		this->m_record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
}
void speechmanager::showrecord()
{
	if (this->fileisempty)
	{
		cout << "文件不存在或为空！" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_record.size(); i++)
		{
			cout << "第" << i + 1 << "届"
				<< "冠军编号：" << this->m_record[i][0] << "得分：" << this->m_record[i][1] << " "
				<< "亚军编号：" << this->m_record[i][2] << "得分：" << this->m_record[i][3] << " "
				<< "季军编号：" << this->m_record[i][4] << "得分：" << this->m_record[i][5] << endl;
		}
	}
}
void speechmanager::clearrecord()
{
	cout << "是否确认清空？" << endl;
	cout << "1.是" << endl;
	cout << "2.否" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		this->initspeech();
		this->createspeaker();
		this->loadrecord();
		cout << "清空成功！" << endl;
	}
}
speechmanager::~speechmanager()
{

}