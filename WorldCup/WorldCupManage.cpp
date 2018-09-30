#include "pch.h"
#include "WorldCupManage.h"


string WorldCupManage::IntegralAndShooterStatistics()
//操作结果：积分榜and射手榜数据统计
{
	string inputTime;
	cout << "请输入时间:";
	cin >> inputTime;
	int nFlag = 0;
	while (match[nFlag].time < inputTime) nFlag++;

	//积分榜
	int AFlag, BFlag;
	for (int i = 0; i < nFlag; ++i)
	{
		for (int j = 0; j < teamCount; ++j)
		{
			if (team[j].nameTeam == match[i].team1)
			{
				AFlag = j;
				continue;
			}
			else if (team[j].nameTeam == match[i].team2)
			{
				BFlag = j;
				continue;
			}
		}//找一条比赛中对应的队伍在team结构数组中的位置

		//计算比分
		if (match[i].numGoal1 > match[i].numGoal2)
		{
			team[AFlag].integral += 3;
		}
		if (match[i].numGoal1 < match[i].numGoal2)
		{
			team[BFlag].integral += 3;
		}
		else if (match[i].numGoal1 == match[i].numGoal2)
		{
			team[AFlag].integral += 1;
			team[BFlag].integral += 1;
		}
	}

	//射手榜
	int nCount = 0;
	while (goals[nCount].time < inputTime) nCount++;
	int aFlag = -1;
	for (int i = 0; i < nCount; ++i)
	{
		for (int j = 0; j < playerCount; ++j)
		{
			if (player[j].name == goals[i].name)
			{
				aFlag = j;  //记录球员在player中的位置
				break;
			}
		}

		if (aFlag != -1) player[aFlag].numGoal++;
	}

	return inputTime;
}

void WorldCupManage::IntegralAndShooterTable(string time)
//操作结果：积分榜And射手榜排序并显示
{
	//拷贝team[teamCount]
	//保护从文件中读出的原始数据

	//积分榜
	TeamInfor teamCopy[100];
	for (int i = 0; i < teamCount; ++i)
	{
		teamCopy[i].nameTeam = team[i].nameTeam;
		teamCopy[i].integral = team[i].integral;
	}

	//冒泡排序
	for (int i = 0; i < teamCount - 1; ++i)
	{
		for (int j = 0; j < teamCount - i - 1; ++j)
		{
			if (teamCopy[j].integral < teamCopy[j + 1].integral) //从大到小
			{
				SwapTeamInfor(teamCopy[j], teamCopy[j + 1]);
			}
		}
	}

	//显示积分榜
	cout << "===============" << time << "之前的积分榜===============" << endl;
	cout << "国家" << "\t\t" << "积分" << endl;
	for (int i = 0; i < teamCount; ++i)
	{
		cout << teamCopy[i].nameTeam << "\t\t"
			<< teamCopy[i].integral << endl;
	}

	//射手榜
	PlayerInfor playerCopy[100];
	for (int i = 0; i < playerCount; ++i)
	{
		playerCopy[i].name = player[i].name;
		playerCopy[i].numGoal = player[i].numGoal;
	}

	//冒泡排序
	for (int i = 0; i < playerCount - 1; ++i)
	{
		for (int j = 0; j < playerCount - i - 1; ++j)
		{
			if (playerCopy[j].numGoal < playerCopy[j + 1].numGoal) //从大到小
			{
				SwapPlayerInfor(playerCopy[j], playerCopy[j + 1]);  //交换球员位置
			}
		}
	}

	cout << "===============" << time << "之前的射手榜" << "===============" << endl;
	cout << "球员" << "\t\t" << "进球数" << endl;
	for (int i = 0; i < playerCount; i++)
	{
		cout << playerCopy[i].name << "\t\t"
			<< playerCopy[i].numGoal << endl;
	}

	//积分和球员进球数清零
	RecordIntegralAndShooter();
}

void WorldCupManage::SwapTeamInfor(TeamInfor & a, TeamInfor & b)
//操作结果：交换队伍位置
{
	TeamInfor temp;
	temp.nameTeam = a.nameTeam;
	temp.numWin = a.numWin;
	temp.numFlat = a.numFlat;
	temp.numNegative = a.numNegative;
	temp.numGoal = a.numGoal;
	temp.integral = a.integral;

	a.nameTeam = b.nameTeam;
	a.numWin = b.numWin;
	a.numFlat = b.numFlat;
	a.numNegative = b.numNegative;
	a.numGoal = b.numGoal;
	a.integral = b.integral;

	b.nameTeam = temp.nameTeam;
	b.numWin = temp.numWin;
	b.numFlat = temp.numFlat;
	b.numNegative = temp.numNegative;
	b.numGoal = temp.numGoal;
	b.integral = temp.integral;
}

void WorldCupManage::SwapPlayerInfor(PlayerInfor &a, PlayerInfor &b)
//操作结果：交换两个球员在数组中的位置
{
	PlayerInfor temp;

	temp.name = a.name;
	temp.nameTeam = a.nameTeam;
	temp.number = a.number;
	temp.numGoal = a.numGoal;

	a.name = b.name;
	a.nameTeam = b.nameTeam;
	a.number = b.number;
	a.numGoal = b.numGoal;

	b.name = temp.name;
	b.nameTeam = temp.nameTeam;
	b.number = temp.number;
	b.numGoal = temp.numGoal;
}

void WorldCupManage::DisplayMatchInforAll()
//操作结果：显示所有比赛记录
{
	cout << "场次" << "\t\t" << "比赛性质" << "\t"
		<< "时间" << "\t\t" << "主场" << "\t"
		<< "客场" << "\t" << "Num1" << "\t\t"
		<< "Num2" << endl;

	for (int i = 0; i < matchCount; ++i)
	{
		DisplayMatchInfor(match[i]);
	}
}

void WorldCupManage::DisplayMatchInfor(const MatchInfor & matchInfor)
//操作结果：显示一条比赛记录
{
	cout << matchInfor.key << "\t" << matchInfor.natureCompetition << "\t\t"
		<< matchInfor.time << "\t" << matchInfor.team1 << "\t"
		<< matchInfor.team2 << "\t" << matchInfor.numGoal1 << "\t\t"
		<< matchInfor.numGoal2 << endl;
}

void WorldCupManage::DisplayPlayerInforAll()
//操作结果：显示所有球员信息
{
	cout << "姓名" << "\t\t"
		<< "国籍" << endl;

	for (int i = 0; i < playerCount; ++i)
	{
		DisplayPlayerInfor(player[i]);
	}
}

void WorldCupManage::DisplayPlayerInfor(const PlayerInfor & playerInfor)
//操作结果：显示一条球员记录
{
	cout << playerInfor.name << "\t\t"
		<< playerInfor.nameTeam << endl;
}

void WorldCupManage::RecordIntegralAndShooter()
//操作结果：将积分和球员进球数清零
{
	//积分清零
	for (int i = 0; i < teamCount; ++i)
	{
		team[i].integral = 0;
	}

	//球员进球数清零
	for (int i = 0; i < playerCount; ++i)
	{
		player[i].numGoal = 0;
	}
}

WorldCupManage::WorldCupManage()
//操作结果：导入原始数据
{
	matchCount = 0;
	teamCount = 0;
	playerCount = 0;
	goalsCount = 0;

	ifstream matchFile("matchRecord.txt", ios::in); 	//以输入的方式打开文件

	if (!matchFile)   				//测试是否成功打开
	{
		cerr << "open matchFile error!" << endl;
		exit(1);
	}
	while (!matchFile.eof())
	{
		matchFile >> match[matchCount].key
			>> match[matchCount].natureCompetition
			>> match[matchCount].time
			>> match[matchCount].team1
			>> match[matchCount].team2
			>> match[matchCount].numGoal1
			>> match[matchCount].numGoal2;

		++matchCount;
	}
	matchFile.close();

	ifstream teamFile("teamRecord.txt", ios::in);  //以输入的方式打开文件
	if (!teamFile)   				//测试是否成功打开
	{
		cerr << "open teamFile error!" << endl;
		exit(1);
	}
	while (!teamFile.eof())
	{
		teamFile >> team[teamCount].nameTeam;
		team[teamCount].integral = 0;

		++teamCount;
	}
	teamFile.close();

	ifstream playerFile("playerRecord.txt", ios::in); //以输入的方式打开文件
	if (!playerFile)   				//测试是否成功打开
	{
		cerr << "open playerFile error!" << endl;
		exit(1);
	}
	while (!playerFile.eof())
	{
		playerFile >> player[playerCount].name
			>> player[playerCount].nameTeam;
		player[playerCount].numGoal = 0;  //球员进球数

		++playerCount;
	}
	playerFile.close();

	ifstream goalsFile("goalsRecord.txt", ios::in);
	if (!goalsFile)
	{
		cerr << "open goalsFile error" << endl;
		exit(1);
	}
	while (!goalsFile.eof())
	{
		goalsFile >> goals[goalsCount].time
			>> goals[goalsCount].name;
		++goalsCount;
	}
	goalsFile.close();
}

void WorldCupManage::Run()
//操作结果：模拟查询系统
{
	cout << "==============2018俄罗斯世界杯数据中心|赛程|积分榜|射手榜==============" << endl;
	int select;  //临时变量
	do
	{
		cout << "** 1--显示历史比赛数据         **" << endl;
		cout << "** 2--显示历史进球数据         **" << endl;
		cout << "** 3--输入时刻，看到结果和预告 **" << endl;
		cout << "*** 4--查询场次，显示详细信息   **" << endl;

		cout << "输入选择";  //输入选择
		cin >> select;  //输入选择
		while (getchar() != '\n');  //跳过当前行的其他字符
		switch (select)
		{
		case 1:
			DisplayMatchInforAll();
			break;
		case 2:
			DisplayPlayerInforAll();
			break;
		case 3:
			string time = IntegralAndShooterStatistics();
			IntegralAndShooterTable(time);
			break;
			//case 4:
			//	
			//	break;
			//case 5:
			//	DisplayALL();  //显示所有记录
			//	break;
		}
	} while (select != 0);
}
