#include "pch.h"
#include "player.h"

void PlayerInforManage::Display(const PlayerInfor & playerInfor)
//操作结果：显示指定球员信息
{
	cout << playerInfor.name << "\t"
		<< playerInfor.nameTeam << "\t"
		<< playerInfor.number << "\t"
		<< playerInfor.numGoal << endl;
}

void PlayerInforManage::DisplayALL()
//操作结果：显示所有球员信息
{
	cout << "姓名" << "\t" << "球队" << "\t"
		<< "编号" << "\t" << "进球数" << endl;

	for (int i = 0; i < playerCount; ++i)
	{
		Display(player[i]);
	}
}

void PlayerInforManage::ShooterList()
//根据球员信息生成射手榜并显示
{
	PlayerInfor playerCopy[NPLAYER];  //私有成员player结构数组的拷贝

	//将player[NPLAYER]中的内容拷贝到playerCopy[NPLAYER]
	for (int i = 0; i < 4; ++i)
	{
		strcpy(playerCopy[i].name, player[i].name);
		strcpy(playerCopy[i].nameTeam, player[i].nameTeam);
		playerCopy[i].number = player[i].number;
		playerCopy[i].numGoal = player[i].numGoal;
	}

	//根据numGoal冒泡排序 - 生成射手榜 -- Waiting...


	//射手榜生成 - 冒泡排序
	


}

PlayerInforManage::PlayerInforManage()
//操作结果：初始化球员信息
{
	playerCount = 0;

	//下面从playerRecord.txt文件中读取数据到结构体数组中
	ifstream infile("F:\\VS2017\\2018_9_26_11_15_test1\\2018_9_26_11_15_test1\\playerRecord.txt", ios::in); //以输入的方式打开文件

	if (!infile)  //测试是否打开成功
	{
		cerr << "open playerRecord.txt error" << endl;
		exit(1);  //结束程序
	}

	int i = 0;  //临时计数变量
	while (!infile.eof())
	{
		infile >> player[i].name  //球员姓名
			>> player[i].nameTeam  //所属队伍
			>> player[i].number  //球员编号
			>> player[i].numGoal;  //进球数

		++playerCount;
		++i;
	}

	infile.close();
}
