#pragma once

//球员信息记录
struct PlayerInfor
{
	char name[20];  //球员姓名
	char nameTeam[20];  //所属球队名称
	int number;  //编号
	int numGoal;  //进球数 -- 射手榜排序依据
};

const int NPLAYER = 150;  //本届世界杯一共有110人进球

//球员信息管理类
class PlayerInforManage
{
private:
	//球员信息类的数据成员
	PlayerInfor player[NPLAYER];  //球员信息结构数组
	int playerCount;  //从文件中读入的球员信息条数

public:
	//辅助函数
	void Display(const PlayerInfor &playerInfor);  //显示进球信息
	void DisplayALL();  //显示所有进球记录
	void ShooterList();  //根据球员信息生成射手榜并显示

	PlayerInforManage();  //无参构造函数 - 球员信息初始化
//	virtual ~PlayerInforManage();  //析构函数
};