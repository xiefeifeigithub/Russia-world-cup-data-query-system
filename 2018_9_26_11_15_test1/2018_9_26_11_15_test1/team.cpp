#include "pch.h"
#include "team.h"

void TeamInforManage::Display(const TeamInfor & teamInfor)
//操作结果：显示指定球队记录
{
	cout << teamInfor.nameTeam << "\t\t" << teamInfor.numWin << "\t"
		<< teamInfor.numFlat << "\t" << teamInfor.numNegative << "\t"
		<< teamInfor.numGoal << "\t" << teamInfor.integral << endl;
}

void TeamInforManage::DisplayALL()
//操作结果：显示所有球队记录
{
	cout << "球队名称" << "\t" << "胜" << "\t"
		<< "平" << "\t" << "负" << "\t" << "净胜球" << "\t"
		<< "积分" << endl;

	for (int i = 0; i < teamCount; ++i)
	{
		Display(team[i]);
	}
}

void TeamInforManage::LeagueTable()
//操作结果：根据队伍积分生成积分榜并显示 - 小组赛程
{
	TeamInfor teamCopy[NTEAM];  //私有成员team结构数组的拷贝
	//将team[NTEAM]中的内容拷贝到teamCopy[NTEAM]
	//将结构数组分段，一共8个小组
	//0~3,4~7, 8~11, 12~15, 16~19, 20~23, 24~27, 28~31

	//0~3
	for (int i = 0; i < 4; ++i)
	{
		strcpy(teamCopy[i].nameTeam, team[i].nameTeam);
		teamCopy[i].numWin = team[i].numWin;
		teamCopy[i].numFlat = team[i].numFlat;
		teamCopy[i].numNegative = team[i].numNegative;
		teamCopy[i].numGoal = team[i].numGoal;
		teamCopy[i].integral = team[i].integral;
	}

	//0~3按积分排序
	for (int i = 0; i < 4-1; ++i)
	{
		for (int j = 0; j < 4 - i - 1; ++j)
		{
			if (teamCopy[j].integral < teamCopy[j + 1].integral) //从大到小
			{
				SwapTeamInfor(teamCopy[j], teamCopy[j + 1]);  //交换两个队伍位置在数组中的信息
			}
		}
	}

	cout << "A组排名" << endl;
	for (int i = 0; i < 4; ++i)
	{
		Display(teamCopy[i]);
	}
}

void TeamInforManage::SwapTeamInfor(TeamInfor & a, TeamInfor & b)
//交换两个队伍在数组中的位置
{
	TeamInfor temp;
	strcpy(temp.nameTeam, a.nameTeam);
	temp.numWin = a.numWin;
	temp.numFlat = a.numFlat;
	temp.numNegative = a.numNegative;
	temp.numGoal = a.numGoal;
	temp.integral = a.integral;

	strcpy(a.nameTeam, b.nameTeam);
	a.numWin = b.numWin;
	a.numFlat = b.numFlat;
	a.numNegative = b.numNegative;
	a.numGoal = b.numGoal;
	a.integral = b.integral;

	strcpy(b.nameTeam, temp.nameTeam);
	b.numWin = temp.numWin;
	b.numFlat = temp.numFlat;
	b.numNegative = temp.numNegative;
	b.numGoal = temp.numGoal;
	b.integral = temp.integral;
}

TeamInforManage::TeamInforManage() 
//操作结果:初始化球队信息
{
	teamCount = 0;
	//下面从文件中读取数据到Team结构体数组中
	ifstream infile("F:\\VS2017\\2018_9_26_11_15_test1\\2018_9_26_11_15_test1\\teamRecord.txt", ios::in);  //以输入的方式打开文件

	if (!infile) //测试是否打开成功
	{
		cerr << "open teamRecord.txt error" << endl;
		exit(1);
	}

	int i = 0;
	while (!infile.eof())
	{
		infile >> team[i].nameTeam >> team[i].numWin
			>> team[i].numFlat >> team[i].numNegative
			>> team[i].numGoal >> team[i].integral;

		++teamCount;
		++i;
	}

	infile.close();
}
