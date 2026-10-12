#include"speechmanager.h"
#include<ctime>
int main()
{
	srand((unsigned int)time(NULL));
	speechmanager sm;
	while (true)
	{
		sm.show_menu();
		cout << "ÇëÊäÈëÄúµÄÑ¡Ôñ£º" << endl;
		int choice = 0;
		cin >> choice;
		switch (choice)
		{
		case 1:
			sm.startspeech();
			break;
		case 2:
			sm.showrecord();
			break;
		case 3:
			sm.clearrecord();
			break;
		case 0:
			sm.existsystem();
			break;
		default:
			system("cls");
			break;
		}
		system("pause");
		system("cls");
	}
	return 0;
}
