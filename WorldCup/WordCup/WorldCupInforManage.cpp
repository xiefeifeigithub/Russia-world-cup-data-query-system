#include "pch.h"
#include "WorldCupInforManage.h"

//操作结果：定位场次
void WCIM::FindField()
{
	int inputField;  //用户输入的场次
	cout << "请输入场次:";
FIND:
	cin >> inputField;
	int fieldsIndex = -1;  //match[]结构数组中的下标
	int goalsEndIndex = -1;  //goals[]结构数组中的下标

	//二分查找 - 场次结构数组fields[]
	int left = 0, right = fieldsCount - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (inputField == fields[mid].field)
		{
			fieldsIndex = mid;
			break;
		}
		else if (inputField < fields[mid].field) right = mid - 1;
		else left = mid + 1;
	}

	if (fieldsIndex == -1)
	{
		cout << "不存在第" << inputField << "场次" << endl;
		cout << "请重新输入:";

		goto FIND;
	}
	else
	{
		DisplayFieldInfor(fieldsIndex);  //输出找到的场次信息
	}

	//查找inputField对应的进球信息
	int begin = -1, end = -1;
	//begin
	for (int i = 0; i < goalsCount; ++i)
	{
		if (inputField == goals[i].field)
		{
			begin = i;
			break;
		}
	}
	//end
	for (int i = begin; i < goalsCount; ++i)
	{
		if (inputField != goals[i].field)
		{
			end = i - 1;
			break;
		}
	}

	for (int i = begin; i <= end; ++i)
	{
		DisplayGoalsInfor(i);
	}

}

//操作结果：显示一条场次信息
void WCIM::DisplayFieldInfor(int position)
{
	cout << "场次" << "\t" << "比赛时间" << "\t" << "国家" << "\t" << "国家" << "\t" << "比分" << endl;
	int i = position;
	cout << fields[i].field << "\t"
		<< fields[i].time << "\t"
		<< fields[i].team1 << "\t"
		<< fields[i].team2 << "\t"
		<< fields[i].scores << endl;
}

//显示所有场次信息
void WCIM::DisplayFieldInforAll()
{
	for (int i = 0; i < fieldsCount; ++i)  //??? i<fieldsCount-1 != i<fieldsCount
	{
		DisplayFieldInfor(i);
	}
}

//显示一场比赛中的进球信息
void WCIM::DisplayGoalsInfor(int position)
{
	int i = position;
	cout << "进球时间" << "\t"
		<< "姓名" << "\t"
		<< "国家" << "\t"
		<< "球员编号" << "\t"
		<< "进球特征" << "\t" << endl;

	cout << goals[i].time << "\t"
		<< goals[i].name << "\t"
		<< goals[i].nameTeam << "\t"
		<< goals[i].numberPlayer << "\t"
		<< goals[i].GoalCharacteristics << endl;
}

//操作结果：积分榜and射手榜数据统计
string WCIM::IntegralAndShooterStatistics()
//操作结果：积分榜and射手榜数据统计
{
	string inputTime;
	cout << "请输入时间:";
	cin >> inputTime;


	//积分榜
	int nFlag = 0;
	//计算时间节点在inputTime之前的比赛记录数目(包括inputTime)
	for (int i = 0; i < matchCount; ++i)
	{
		if (inputTime >= match[i].time)
		{
			nFlag++;
		}
		else
		{
			break;
		}
	}
	int AFlag = -1, BFlag = -1;  //队伍1在team中的位置，队伍2在team中的位置
	//将一条比赛记录matchRecord匹配队伍team，做好积分计算的工作
	for (int i = 0; i < nFlag; ++i)
	{
		/*for (int j = 0; j < teamCount; ++j)
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
		}*/

		//new - 从一条比赛记录中找team1和team2
		for (int j = 0; j < teamCount; ++j)
		{
			if (team[j].nameTeam == match[i].team1)
			{
				AFlag = j;
				break;
			}
		}

		for (int j = 0; j < teamCount; ++j)
		{
			if (team[j].nameTeam == match[i].team2)
			{
				BFlag = j;
				break;
			}
		}

		//积分判定和胜平负判定
		if (i % 2 == 0)  //偶记录，不决定最终积分
		{
			if (match[i].numGoal1 > match[i].numGoal2)
			{
				team[AFlag].integral += 3;
				team[AFlag].numWin++;
				team[BFlag].numNegative++;
			}
			else if (match[i].numGoal1 < match[i].numGoal2)
			{
				team[BFlag].integral += 3;
				team[BFlag].numWin++;
				team[AFlag].numNegative++;
			}
			else //match[i].numGoal1 == match[i].numGoal2
			{
				team[AFlag].integral += 1;
				team[BFlag].integral += 1;
				team[AFlag].numFlat++;
				team[BFlag].numFlat++;
			}
		}
		else //i%2!=0, 奇记录，决定最终积分
		{
			if (match[i].numGoal1 > match[i].numGoal2)
			{
				if (match[i - 1].numGoal1 > match[i - 1].numGoal2)
				{
					//Do Nothing
				}
				else if (match[i - 1].numGoal1 < match[i - 1].numGoal2)
				{
					team[AFlag].integral += 3;
					team[BFlag].integral -= 3;
					team[AFlag].numNegative--;
					team[AFlag].numWin++;
					team[BFlag].numNegative++;
					team[BFlag].numWin--;
				}
				else //match[i-1].numGoal1 == match[i-1].numGoal2
				{
					team[AFlag].integral += 2;
					team[BFlag].integral -= 1;
					team[AFlag].numFlat--;
					team[BFlag].numFlat--;
					team[AFlag].numWin++;
					team[BFlag].numNegative++;
				}
			}
			else if (match[i].numGoal1 < match[i].numGoal2)
			{
				if (match[i - 1].numGoal1 > match[i - 1].numGoal2)
				{
					team[AFlag].integral -= 3;
					team[BFlag].integral += 3;
					team[BFlag].numNegative--;
					team[BFlag].numWin++;
					team[AFlag].numWin--;
					team[AFlag].numNegative++;
				}
				else if (match[i - 1].numGoal1 < match[i - 1].numGoal2)
				{
					//Do Nothing
				}
				else
				{
					team[AFlag].integral -= 1;
					team[BFlag].integral += 2;
					team[AFlag].numFlat--;
					team[BFlag].numFlat--;
					team[BFlag].numWin++;
					team[AFlag].numNegative++;
				}
			}
			else  //match[i].numGoal1 == match[i].numGoal2
			{
				if (match[i - 1].numGoal1 > match[i - 1].numGoal2)
				{
					team[AFlag].integral = team[AFlag].integral - 3 + 1;
					team[BFlag].integral += 1;
					team[AFlag].numWin--;
					team[BFlag].numNegative--;
					team[AFlag].numFlat++;
					team[BFlag].numFlat++;
				}
				else if (match[i - 1].numGoal1 < match[i - 1].numGoal2)
				{
					team[BFlag].integral = team[BFlag].integral - 3 + 1;
					team[AFlag].integral += 1;
					team[BFlag].numWin--;
					team[AFlag].numNegative--;
					team[BFlag].numFlat++;
					team[AFlag].numFlat++;
				}
				else //match[i - 1].numGoal1 == match[i - 1].numGoal2
				{
					//Do Nothing
				}
			}
		}
	}

	//射手榜
	int nCount = 0;
	//查找时间节点在输入时刻之前(包括输入时刻)的所有进球记录个数
	for (int i = 0; i < goalsCount; ++i)
	{
		if (inputTime >= goals[i].time)
		{
			nCount++;
		}
		else
		{
			break;
		}
	}
	int aFlag = -1;
	//将时间节点在inputTime之前的进球记录与相应的player[]匹配，做好进球数记录工作
	for (int i = 0; i < nCount; ++i)
	{
		int j;
		for (j = 0; j < playerCount; ++j)
		{
			if (player[j].name == goals[i].name)
			{
				aFlag = j;  //记录球员在player中的位置
				break;
			}
		}

		if (aFlag != -1 && j != playerCount) player[aFlag].numGoal++;
	}


	return inputTime;
}

//操作结果：积分榜And射手榜排序并显示
void WCIM::IntegralAndShooterTable(string time)
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
		teamCopy[i].group = team[i].group;
		teamCopy[i].numWin = team[i].numWin;
		teamCopy[i].numFlat = team[i].numFlat;
		teamCopy[i].numNegative = team[i].numNegative;
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
	cout << "===============" << time << "的积分榜===============" << endl;
	cout << "组别" << "\t" << "国家" << "\t\t" << "积分" << "\t" << "胜" << "\t" << "平" << "\t" << "负" << endl;
	for (int i = 0; i < teamCount; ++i)
	{
		cout << teamCopy[i].group << "\t"
			<< teamCopy[i].nameTeam << "\t\t"
			<< teamCopy[i].integral << "\t"
			<< teamCopy[i].numWin << "\t"
			<< teamCopy[i].numFlat << "\t"
			<< teamCopy[i].numNegative << endl;
	}

	//射手榜
	//冒泡排序
	for (int i = 0; i < playerCount - 1; ++i)
	{
		for (int j = 0; j < playerCount - i - 1; ++j)
		{
			if (player[j].numGoal < player[j + 1].numGoal) //从大到小
			{
				SwapPlayerInfor(player[j], player[j + 1]);  //交换球员位置
			}
		}
	}
	//输出射手榜,将进球数不为0的射手信息输出
	cout << "===============" << time << "的射手榜" << "===============" << endl;
	cout << "球员" << "\t\t" << "进球数" << "\t" << "编号" << "\t" << "国家" << endl;
	for (int i = 0; i < playerCount; i++)
	{
		if (player[i].numGoal != 0)
		{
			cout << player[i].name << "\t\t"
				<< player[i].numGoal << "\t"
				<< player[i].number << "\t"
				<< player[i].nameTeam << endl;
		}
		else
		{
			break;
		}
	}

	//积分、胜、平、负、球员进球数清零
	ClearZeroISWFN();
}

//操作结果：交换队伍位置
void WCIM::SwapTeamInfor(TeamInfor & a, TeamInfor & b)
//操作结果：交换队伍位置
{
	TeamInfor temp;
	temp.group = a.group;
	temp.nameTeam = a.nameTeam;
	temp.numWin = a.numWin;
	temp.numFlat = a.numFlat;
	temp.numNegative = a.numNegative;
	temp.numGoal = a.numGoal;
	temp.integral = a.integral;

	a.group = b.group;
	a.nameTeam = b.nameTeam;
	a.numWin = b.numWin;
	a.numFlat = b.numFlat;
	a.numNegative = b.numNegative;
	a.numGoal = b.numGoal;
	a.integral = b.integral;

	b.group = temp.group;
	b.nameTeam = temp.nameTeam;
	b.numWin = temp.numWin;
	b.numFlat = temp.numFlat;
	b.numNegative = temp.numNegative;
	b.numGoal = temp.numGoal;
	b.integral = temp.integral;
}

//操作结果：交换两个球员在数组中的位置
void WCIM::SwapPlayerInfor(PlayerInfor &a, PlayerInfor &b)
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

//操作结果：显示所有比赛记录
void WCIM::DisplayMatchInforAll()
//操作结果：显示所有比赛记录
{
	cout << "比赛性质" << "\t"
		<< "时间" << "\t\t" << "主场" << "\t"
		<< "客场" << "\t" << "Num1" << "\t\t"
		<< "Num2" << endl;

	for (int i = 0; i < matchCount; ++i)
	{
		DisplayMatchInfor(match[i]);
	}
}

//操作结果：显示一条比赛记录
void WCIM::DisplayMatchInfor(const MatchInfor & matchInfor)
//操作结果：显示一条比赛记录
{
	cout << matchInfor.natureCompetition << "\t\t"
		<< matchInfor.time << "\t" << matchInfor.team1 << "\t"
		<< matchInfor.team2 << "\t" << matchInfor.numGoal1 << "\t\t"
		<< matchInfor.numGoal2 << endl;
}

//操作结果：显示所有球员信息
void WCIM::DisplayPlayerInforAll()
//操作结果：显示所有球员信息
{
	cout << "姓名" << "\t\t"
		<< "国籍" << endl;

	for (int i = 0; i < playerCount; ++i)
	{
		DisplayPlayerInfor(player[i]);
	}
}

//操作结果：显示一条球员记录
void WCIM::DisplayPlayerInfor(const PlayerInfor & playerInfor)
//操作结果：显示一条球员记录
{
	cout << playerInfor.name << "\t\t"
		<< playerInfor.nameTeam << endl;
}

//操作结果：积分、胜、平、负、球员进球数清零
void WCIM::ClearZeroISWFN()
//操作结果：将积分和球员进球数清零
{
	//积分、胜、平、负清零
	for (int i = 0; i < teamCount; ++i)
	{
		team[i].integral = 0;
		team[i].numWin = 0;
		team[i].numFlat = 0;
		team[i].numNegative = 0;
	}

	//球员进球数清零
	for (int i = 0; i < playerCount; ++i)
	{
		player[i].numGoal = 0;
	}
}

//操作结果：根据小组赛积分算出16强
void WCIM::Strong16()
{
	//分小组排序
	//将结构数组分段，一共8个小组
	//0~3,4~7, 8~11, 12~15, 16~19, 20~23, 24~27, 28~31
	TeamInfor teamCopy[100];
	for (int i = 0; i < teamCount; ++i)
	{
		teamCopy[i].nameTeam = team[i].nameTeam;
		teamCopy[i].integral = team[i].integral;
		teamCopy[i].group = team[i].group;
		teamCopy[i].numWin = team[i].numWin;
		teamCopy[i].numFlat = team[i].numFlat;
		teamCopy[i].numNegative = team[i].numNegative;
	}

	//A组，下标范围0~3
	for (int i = 0; i < 4 - 1; ++i)
	{
		for (int j = 0; j < 4 - i - 1; ++j)
		{
			if (teamCopy[j].integral < teamCopy[j + 1].integral) //从大到小
			{
				SwapTeamInfor(teamCopy[j], teamCopy[j + 1]);  //交换两个队伍位置在数组中的信息
			}
		}
	}

	//B组，下标范围4~7
	for (int i = 4; i < 8 - 1; ++i)
	{
		for (int j = 4; j < 8 - i - 1; ++j)
		{
			if (teamCopy[j].integral < teamCopy[j + 1].integral) //从大到小
			{
				SwapTeamInfor(teamCopy[j], teamCopy[j + 1]);  //交换两个队伍位置在数组中的信息
			}
		}
	}

	//C组，下标范围8~11
	for (int i = 8; i < 12 - 1; ++i)
	{
		for (int j = 8; j < 12 - i - 1; ++j)
		{
			if (teamCopy[j].integral < teamCopy[j + 1].integral) //从大到小
			{
				SwapTeamInfor(teamCopy[j], teamCopy[j + 1]);  //交换两个队伍位置在数组中的信息
			}
		}
	}

	//D组，下标范围12~15
	for (int i = 12; i < 16 - 1; ++i)
	{
		for (int j = 12; j < 16 - i - 1; ++j)
		{
			if (teamCopy[j].integral < teamCopy[j + 1].integral) //从大到小
			{
				SwapTeamInfor(teamCopy[j], teamCopy[j + 1]);  //交换两个队伍位置在数组中的信息
			}
		}
	}

	//E,下标范围16~19
	for (int i = 16; i < 20 - 1; ++i)
	{
		for (int j = 16; j < 20 - i - 1; ++j)
		{
			if (teamCopy[j].integral < teamCopy[j + 1].integral) //从大到小
			{
				SwapTeamInfor(teamCopy[j], teamCopy[j + 1]);  //交换两个队伍位置在数组中的信息
			}
		}
	}

	//F组，下标范围20~23
	for (int i = 20; i < 14 - 1; ++i)
	{
		for (int j = 20; j < 24 - i - 1; ++j)
		{
			if (teamCopy[j].integral < teamCopy[j + 1].integral) //从大到小
			{
				SwapTeamInfor(teamCopy[j], teamCopy[j + 1]);  //交换两个队伍位置在数组中的信息
			}
		}
	}

	//G组，下标范围24~27
	for (int i = 24; i < 28 - 1; ++i)
	{
		for (int j = 24; j < 28 - i - 1; ++j)
		{
			if (teamCopy[j].integral < teamCopy[j + 1].integral) //从大到小
			{
				SwapTeamInfor(teamCopy[j], teamCopy[j + 1]);  //交换两个队伍位置在数组中的信息
			}
		}
	}

	//H组，下标范围28~31
	for (int i = 28; i < 32 - 1; ++i)
	{
		for (int j = 28; j < 32 - i - 1; ++j)
		{
			if (teamCopy[j].integral < teamCopy[j + 1].integral) //从大到小
			{
				SwapTeamInfor(teamCopy[j], teamCopy[j + 1]);  //交换两个队伍位置在数组中的信息
			}
		}
	}

	for (int i = 0; i < teamCount; ++i)
	{
		cout << team[i].group << "\t"
			<< team[i].nameTeam << "\t\t"
			<< team[i].integral << endl;
	}
}

//操作结果：导入原始数据
WCIM::WCIM()
//操作结果：导入原始数据
{
	matchCount = 0;
	teamCount = 0;
	playerCount = 0;
	goalsCount = 0;
	fieldsCount = 0;

	ifstream fieldsFile("fieldsRecord.txt", ios::in);
	if (!fieldsFile)
	{
		cerr << "open fieldsFiel error" << endl;
		exit(1);
	}
	while (!fieldsFile.eof())
	{
		fieldsFile >> fields[fieldsCount].field
			>> fields[fieldsCount].time
			>> fields[fieldsCount].team1
			>> fields[fieldsCount].team2
			>> fields[fieldsCount].scores;

		++fieldsCount;
	}

	fieldsFile.close();

	ifstream matchFile("matchRecord.txt", ios::in); 	//以输入的方式打开文件

	if (!matchFile)   				//测试是否成功打开
	{
		cerr << "open matchFile error!" << endl;
		exit(1);
	}
	while (!matchFile.eof())
	{
		matchFile >> match[matchCount].natureCompetition
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
		teamFile >> team[teamCount].group
			>> team[teamCount].nameTeam;
		team[teamCount].integral = 0;  //队伍积分清0
		team[teamCount].numWin = 0;  //胜
		team[teamCount].numFlat = 0;  //平
		team[teamCount].numNegative = 0;  //负
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
			>> player[playerCount].nameTeam
			>> player[playerCount].number;
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
		goalsFile >> goals[goalsCount].field  //场次
			>> goals[goalsCount].time  //进球时间
			>> goals[goalsCount].name
			>> goals[goalsCount].nameTeam
			>> goals[goalsCount].numberPlayer  //编号
			>> goals[goalsCount].GoalCharacteristics;  //进球特征
		++goalsCount;
	}
	goalsFile.close();

	cout << "matchCount:" << matchCount << endl;
	cout << "teamCount:" << teamCount << endl;
	cout << "playerCount:" << playerCount << endl;
	cout << "goalsCount:" << goalsCount << endl;
	cout << "fieldsCount:" << fieldsCount << endl;
}

//操作结果：模拟查询系统
void WCIM::Run()
//操作结果：模拟查询系统
{
	cout << "==============2018俄罗斯世界杯数据中心|赛程|积分榜|射手榜==============" << endl;
	int select;  //临时变量
	do
	{
		cout << "** 1--显示历史比赛数据         **" << endl;
		cout << "** 2--显示历史进球数据         **" << endl;
		cout << "** 3--输入时刻，看到结果和预告 **" << endl;
		cout << "** 4--查询场次，显示详细信息   **" << endl;
		cout << "** 5--显示所有场次信息         **" << endl;

		cout << "输入选择";  //输入选择
		cin >> select;  //输入选择
		while (getchar() != '\n');  //跳过当前行的其他字符
		string time;
		switch (select)
		{
		case 1:
			DisplayMatchInforAll();
			break;
		case 2:
			DisplayPlayerInforAll();
			break;
		case 3:
			time = IntegralAndShooterStatistics();
			IntegralAndShooterTable(time);
			break;
		case 4:
			FindField();
			break;
		case 5:
			DisplayFieldInforAll();
			break;

			//case 5:
			//	DisplayALL();  //显示所有记录
			//	break;
		}
	} while (select != 0);
}
