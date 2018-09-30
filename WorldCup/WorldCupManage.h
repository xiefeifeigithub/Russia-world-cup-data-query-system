#pragma once

#pragma once
#include "pch.h"

//比赛信息记录结构
struct MatchInfor
{
	string natureCompetition;  //比赛性质，每个汉字占两个字符
	string time; //06-01-05 表示6月1号凌晨5点
	string team1;  //队伍1名称
	string team2;  //队伍2名称
	int numGoal1;  //队伍1进球数
	int numGoal2;  //队伍2进球数
	string key;  //场次
};

//球队信息记录结构
struct TeamInfor
{
	string nameTeam;  //球队名称
	int numWin;  //胜的场数
	int numFlat;  //平的场数
	int numNegative;  //负的场数
	int numGoal;  //净胜球
	int integral;  //积分 -- 晋级依据/积分榜依据
};

//球员信息记录

struct PlayerInfor
{
	string name;  //球员姓名
	string nameTeam;  //所属球队名称
	int number;  //编号
//	string time;  //进球时间
	int numGoal;  //进球数 -- 射手榜排序依据
};

//进球信息记录
struct GoalsInfor
{
	string time;
	string name;
};

class WorldCupManage
{
public:
	//比赛信息类的数据成员
	MatchInfor match[70];  //比赛信息结构体数组
	int matchCount; //从文件读入的比赛场数

	//队伍信息类的数据成员
	TeamInfor team[40];  //队伍信息结构数组
	int teamCount;  //从文件中读入的球队数目 - 方便test

	//球员信息类的数据成员
	PlayerInfor player[500];  //球员信息结构数组
	int playerCount;  //从文件中读入的球员信息条数

	//进球信息类的数据成员
	GoalsInfor goals[100];  //进球信息结构数组
	int goalsCount;  //从文件中读入的进球信息条数

	//辅助函数
	string  IntegralAndShooterStatistics();  //积分榜和射手榜数据统计
	void IntegralAndShooterTable(string time);  //积分榜和射手榜排序输出
	void SwapTeamInfor(TeamInfor &a, TeamInfor &b);  //交换两个队伍在数组中的位置

	void SwapPlayerInfor(PlayerInfor &a, PlayerInfor &b);  //交换两个球员在数组中的位置

	void DisplayMatchInforAll();  //显示所有比赛记录
	void DisplayMatchInfor(const MatchInfor &matchInfor);  //显示一条比赛记录

	void DisplayPlayerInforAll();  //显示所有球员信息
	void DisplayPlayerInfor(const PlayerInfor &playerInfor);  //显示一条球员记录

	void RecordIntegralAndShooter();

	WorldCupManage();
	//	~WorldCupManage();
	void Run();  //模拟查询系统
};