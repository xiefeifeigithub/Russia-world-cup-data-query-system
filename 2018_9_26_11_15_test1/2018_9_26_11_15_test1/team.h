#pragma once

//球队信息记录结构
struct TeamInfor
{
	char nameTeam[20];  //球队名称
	int numWin;  //胜的场数
	int numFlat;  //平的场数
	int numNegative;  //负的场数
	int numGoal;  //净胜球
	int integral;  //积分 -- 晋级依据/积分榜依据
};

const int NTEAM = 32;  //一共32场比赛

//队伍信息管理类
class TeamInforManage
{
private:
	//队伍信息类的数据成员
	TeamInfor team[NTEAM];  //队伍信息结构数组
	int teamCount;  //从文件中读入的球队数目 - 方便test
public:
	//辅助函数
	void Display(const TeamInfor &teamInfor);  //显示记录
	void DisplayALL();  //显示所有球队记录
	void LeagueTable();  //根据队伍积分生成积分榜并显示 - 小组赛程
	void SwapTeamInfor(TeamInfor &a, TeamInfor &b);  //交换两个队伍在数组中的位置
	//公有函数
	TeamInforManage();  //无参构造函数
//	virtual ~TeamInforManage();  //析构函数
};