#include "pch.h"
#include "WorldCupInforManage.h"

//操作结果：定位场次
void WCIM::FindField()
{
	int inputField;  //用户输入的场次
	cout << "请输入场次:";
FIND:
	cin >> inputField;
	if (inputField < 1 || inputField > 64)
	{
		cout << "输入错误!!!请重新在1~64范围内输入正确的值:";
		goto FIND;
		
	}
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
//操作结果：显示所有场次信息
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

//操作结果：根据小组赛积分算出16强
void WCIM::GroupMatchSituation()
{
	//统计小组赛所有数据并显示=============
    //数据统计
	int AFlag = -1, BFlag = -1;  //队伍1在team中的位置，队伍2在team中的位置
	//将一条比赛记录matchRecord匹配队伍team，做好积分计算的工作
	//统计小组赛所有数据并显示
	for (int i = 0; i < 96; ++i)
	{
		//从一条比赛记录中找team1和team2
		for (int j = 0; j < teamCount; ++j)  //找match[i].team1在team[]中的位置
		{
			if (team[j].nameTeam == match[i].team1)
			{
				AFlag = j;
				break;
			}
		} 

		for (int j = 0; j < teamCount; ++j)  //找match[i].team2在team[]中的位置
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
			////new - 计算队伍小组赛总进球数
			//team[AFlag].goalsTotal += match[i].numGoal1; //队伍1小组赛的总进球数
			//team[BFlag].goalsTotal += match[i].numGoal2; //队伍2小组赛的总进球数

			//new - 增加小组赛净胜球规则
			team[AFlag].goalsDifference += match[i].numGoal1 - match[i].numGoal2; //队伍1的总净胜球
			team[BFlag].goalsDifference += match[i].numGoal2 - match[i].numGoal1;//队伍2的总净胜球

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

	//三级积分排序算法（先积分，再group，最后净胜球）
	//Test - 第一次乌拉圭净胜球数据有问题，但是n(n>=2)时数据就是正常
	//integral
	for (int i = 0; i < teamCount - 1; ++i)
	{
		for (int j = 0; j < teamCount - i - 1; ++j)
		{
			if (team[j].integral < team[j + 1].integral) //按积分排，从大到小
			{
				SwapTeamInfor(team[j], team[j + 1]);
			}
		}
	}

	//group
	for (int i = 0; i < teamCount - 1; ++i)
	{
		for (int j = 0; j < teamCount - i - 1; ++j)
		{
			if (team[j].group > team[j + 1].group) //group从小到大
			{
				SwapTeamInfor(team[j], team[j + 1]);
			}
		}
	}

	//goalsDifference
	for (int i = 0; i < teamCount - 1; ++i)
	{
		for (int j = 0; j < teamCount - i - 1; ++j)
		{
			//若是同一group,按净胜球从大到小排序
			if (team[j].group == team[j + 1].group) 
			{
				if (team[j].integral == team[j + 1].integral)
				{
					if (team[j].goalsDifference < team[j + 1].goalsDifference)
					{
						SwapTeamInfor(team[j], team[j + 1]);
					}
				}
			}
			if (team[j].group > team[j + 1].group) //group从小到大
			{
				SwapTeamInfor(team[j], team[j + 1]);
			}
		}
	}

	//显示积分榜
	cout << "===============小组赛最终的积分榜===============" << endl;
	cout << "组别" << "\t" << "国家" << "\t\t" << "积分" << "\t" << "胜" << "\t" << "平" << "\t" << "负" << "\t" << "净胜球" << endl;
	for (int i = 0; i < teamCount; ++i)
	{
		cout << team[i].group << "\t"
			<< team[i].nameTeam << "\t\t"
			<< team[i].integral << "\t"
			<< team[i].numWin << "\t"
			<< team[i].numFlat << "\t"
			<< team[i].numNegative << "\t"
			<< team[i].goalsDifference << endl;
	}

	//积分榜数据清零
	ClearZeroIntegral();
}

//操作结果：时间引导函数，通过输入的时间调用不同的函数
void WCIM::TimeGuide()
//操作结果：时间引导函数，通过输入的时间调用不同的函数
{
	string groupCloseTime = "06-29-04";  //最后一场小组赛的结束时刻
	string inputTime;
	cout << "请输入时间:";
	cin >> inputTime;

	//小组赛有积分榜，淘汰赛无积分榜，但是有射手榜
	if (inputTime <= groupCloseTime)  //小组赛进行中
	{
		//积分榜数据统计并显示
		Integral(inputTime);

		//射手榜数据统计并显示
		Shooters(inputTime);
	}
	else  //淘汰赛进行中
	{
		//显示小组赛结束时的积分榜
		//按照小组积分排序，为淘汰赛做准备
		GroupMatchSituation();  //小组赛最终结果展示
		InitializeKnockoutData();  //16强

		cout << "淘汰赛正在编写代码中" << endl;
		cout << "Wating..." << endl;
	}
}

//操作结果：积分榜数据统计并显示
void WCIM::Integral(string inputTime)
//操作结果：积分榜数据统计并显示
{
	//数据统计
	int nCount = 0;
	//计算时间节点在inputTime之前的比赛记录数目(包括inputTime)
	for (int i = 0; i < matchCount; ++i)
	{
		if (inputTime >= match[i].time)
		{
			nCount++;
		}
		else
		{
			break;
		}
	}
	int AFlag = -1, BFlag = -1;  //队伍1在team中的位置，队伍2在team中的位置
	//将一条比赛记录matchRecord匹配队伍team，做好积分计算的工作
	for (int i = 0; i < nCount; ++i)
	{
		//从一条比赛记录中找team1和team2
		for (int j = 0; j < teamCount; ++j)  //找match[i].team1在team[]中的位置
		{
			if (team[j].nameTeam == match[i].team1)
			{
				AFlag = j;
				break;
			}
		} 

		for (int j = 0; j < teamCount; ++j)  //找match[i].team2在team[]中的位置
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

	//结果显示
	//冒泡排序
	for (int i = 0; i < teamCount - 1; ++i)
	{
		for (int j = 0; j < teamCount - i - 1; ++j)
		{
			if (team[j].integral < team[j + 1].integral) //从大到小
			{
				SwapTeamInfor(team[j], team[j + 1]);
			}
		}
	}

	//显示积分榜
	cout << "===============" << inputTime << "的积分榜===============" << endl;
	cout << "组别" << "\t" << "国家" << "\t\t" << "积分" << "\t" << "胜" << "\t" << "平" << "\t" << "负" << endl;
	for (int i = 0; i < teamCount; ++i)
	{
		cout << team[i].group << "\t"
			<< team[i].nameTeam << "\t\t"
			<< team[i].integral << "\t"
			<< team[i].numWin << "\t"
			<< team[i].numFlat << "\t"
			<< team[i].numNegative << endl;
	}

	//积分榜数据清零
	ClearZeroIntegral();
}

//操作结果：射手榜数据统计并显示
void WCIM::Shooters(string inputTime)
//操作结果：射手榜数据统计并显示
{
	//数据统计
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

	//结果显示
	//冒泡排序
	for (int i = 0; i < playerCount - 1; ++i)
	//进球信息和球员信息匹配
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
	cout << "===============" << inputTime << "的射手榜" << "===============" << endl;
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

	//射手榜数据清零
	ClearZeroShooters();
}

//操作结果：积分榜清零
void WCIM::ClearZeroIntegral()
//操作结果：积分榜清零
{
	//积分、胜、平、负、净胜球清零
	for (int i = 0; i < teamCount; ++i)
	{
		team[i].integral = 0;
		team[i].numWin = 0;
		team[i].numFlat = 0;
		team[i].numNegative = 0;
		team[i].goalsDifference = 0;
	}
}

//操作结果：射手榜清零
void WCIM::ClearZeroShooters()
//操作结果：射手榜清零
{
	//球员进球数清零
	for (int i = 0; i < playerCount; ++i)
	{
		player[i].numGoal = 0;
	}
}

//操作结果：记录16强，并生成8强
void WCIM::InitializeKnockoutData()
//操作结果：记录16强，并生成8强
{
	int Count_16 = 0;

	//生成16强
	//按照A1,B2 \ C1,D2 \ E1,F2 \ G1,H2 || A2,B1 \ C2,D1 \ E2,F1 \ G2,H1s顺序读入16强
	knockkoutMatch[Count_16].team1 = team[0].nameTeam;  //A1
	knockkoutMatch[Count_16].team2 = team[5].nameTeam;  //B2
	Count_16++;
	knockkoutMatch[Count_16].team1 = team[8].nameTeam;  //C1
	knockkoutMatch[Count_16].team2 = team[13].nameTeam;  //D2
	Count_16++;
	knockkoutMatch[Count_16].team1 = team[16].nameTeam;  //E1
	knockkoutMatch[Count_16].team2 = team[21].nameTeam;  //F2
	Count_16++;
	knockkoutMatch[Count_16].team1 = team[24].nameTeam;  //G1
	knockkoutMatch[Count_16].team2 = team[29].nameTeam;  //H2
	Count_16++;
	knockkoutMatch[Count_16].team1 = team[1].nameTeam;  //A2
	knockkoutMatch[Count_16].team2 = team[4].nameTeam;  //B1
	Count_16++;
	knockkoutMatch[Count_16].team1 = team[9].nameTeam;  //C2
	knockkoutMatch[Count_16].team2 = team[12].nameTeam;  //D1
	Count_16++;
	knockkoutMatch[Count_16].team1 = team[17].nameTeam;  //E2
	knockkoutMatch[Count_16].team2 = team[20].nameTeam;  //F1
	Count_16++;
	knockkoutMatch[Count_16].team1 = team[25].nameTeam;  //G2
	knockkoutMatch[Count_16].team2 = team[28].nameTeam;  //H1
	Count_16++;

	//test - 输出结果看看
	cout << "16强" << endl;
	for (int i = 0; i < 8; ++i)
	{
		cout << knockkoutMatch[i].team1 << "    "
		     << knockkoutMatch[i].team2 << endl;
	}

	//生成8强
	for (int i = 0; i < 8; i++)  //通过遍历1/8比赛记录获得1/4比赛名单
	{
		string leftNameTeam;
		string rightNameTeam;
		if (i % 2 == 0)  //下标为偶数
		{
			if (knockkoutMatch[i].numGoal1 > knockkoutMatch[i].numGoal2)  //A1 > B2
			{
				 leftNameTeam = knockkoutMatch[i].team1;
			}
			else
			{
				leftNameTeam = knockkoutMatch[i].team2;
			}

			knockkoutMatch[Count_16].team1 = leftNameTeam;
		}
		else  //下标为奇数
		{
			if (knockkoutMatch[i].numGoal1 > knockkoutMatch[i].numGoal2)  //C1 > D2
			{
				rightNameTeam = knockkoutMatch[i].team1;
			}
			else
			{
				rightNameTeam = knockkoutMatch[i].team2;
			}

			knockkoutMatch[Count_16].team2 = rightNameTeam;
		    
			//奇数时淘汰赛比赛数才向后加1
			Count_16++;  //进入下一场比赛双发的记录
		}
	}

	//test - 输出8强看看结果
	cout << "8强" << endl;
	for (int i = 8; i < 12; ++i)
	{
		cout << knockkoutMatch[i].team1 << " "
			<< knockkoutMatch[i].team2 << endl;
	}

	//生成4强
	for (int i = 8; i < 12; ++i)  //通过遍历1/4比赛获得半决赛比赛名单
	{
		string leftNameTeam;
		string rightNameTeam;
		if (i % 2 == 0)  //下标为偶数
		{
			if (knockkoutMatch[i].numGoal1 > knockkoutMatch[i].numGoal2)  //A1 > B2
			{
				leftNameTeam = knockkoutMatch[i].team1;
			}
			else
			{
				leftNameTeam = knockkoutMatch[i].team2;
			}

			knockkoutMatch[Count_16].team1 = leftNameTeam;
		}
		else  //下标为奇数
		{
			if (knockkoutMatch[i].numGoal1 > knockkoutMatch[i].numGoal2)  //C1 > D2
			{
				rightNameTeam = knockkoutMatch[i].team1;
			}
			else
			{
				rightNameTeam = knockkoutMatch[i].team2;
			}

			knockkoutMatch[Count_16].team2 = rightNameTeam;

			//奇数时淘汰赛比赛数才向后加1
			Count_16++;  //进入下一场比赛双发的记录
		}
	}

	//test - 输出4强看看结果
	cout << "4强" << endl;
	for (int i = 12; i < 14; ++i)
	{
		cout << knockkoutMatch[i].team1 << " "
			<< knockkoutMatch[i].team2 << endl;
	}

	//生成半决赛和决赛名单
	for (int i = 12; i < 14; ++i)  //遍历1/4比赛获得半决赛和决赛名单
	{
		//三、四名争夺战比赛双方
		string leftSemifinalsNameTeam;
		string rightSemifinalsNameTeam;
		//一、二名争夺战比赛双方
		string leftFinalsNameTeam;
		string rightFinalsNameTeam;

		if (i % 2 == 0)  
		{
			if (knockkoutMatch[i].numGoal1 > knockkoutMatch[i].numGoal2)
			{
				leftFinalsNameTeam = knockkoutMatch[i].team1;
				leftSemifinalsNameTeam = knockkoutMatch[i].team2;
			}
			else
			{
				leftFinalsNameTeam = knockkoutMatch[i].team2;
				leftSemifinalsNameTeam = knockkoutMatch[i].team1;
			}

			knockkoutMatch[Count_16].team1 = leftSemifinalsNameTeam;
			knockkoutMatch[Count_16 + 1].team1 = leftFinalsNameTeam;
			Count_16++;  //分析一场比赛
		}
		else
		{
			if (knockkoutMatch[i].numGoal1 > knockkoutMatch[i].numGoal2)
			{
				rightFinalsNameTeam = knockkoutMatch[i].team1;
				rightSemifinalsNameTeam = knockkoutMatch[i].team2;
			}
			else
			{
				rightFinalsNameTeam = knockkoutMatch[i].team2;
				rightSemifinalsNameTeam = knockkoutMatch[i].team1;
			}

			knockkoutMatch[Count_16 - 1].team2 = rightSemifinalsNameTeam;
			knockkoutMatch[Count_16].team2 = rightFinalsNameTeam;

		}
	}

	//test - 输出半决赛
	cout << "半决赛" << endl;
	cout << knockkoutMatch[14].team1 << " "
		<< knockkoutMatch[14].team2 << endl;

	//test - 输出决赛
	cout << "决赛" << endl;
	cout << knockkoutMatch[15].team1 << " "
		<< knockkoutMatch[15].team2 << endl;

	//产生并输出三、四名
	if (knockkoutMatch[14].numGoal1 > knockkoutMatch[14].numGoal2)
	{
		cout << "第三名：" << knockkoutMatch[14].team1 << endl;
		cout << "第四名: " << knockkoutMatch[14].team2 << endl;
	}
	else
	{
		cout << "第三名：" << knockkoutMatch[14].team2 << endl;
		cout << "第四名：" << knockkoutMatch[14].team1 << endl;
	}

	//产生并输出一、二名
	if (knockkoutMatch[15].numGoal1 > knockkoutMatch[15].numGoal2)
	{
		cout << "第一名：" << knockkoutMatch[15].team1 << endl;
		cout << "第二名: " << knockkoutMatch[15].team2 << endl;
	}
	else
	{
		cout << "第一名：" << knockkoutMatch[15].team2 << endl;
		cout << "第二名：" << knockkoutMatch[15].team1 << endl;
	}
}

//操作结果：导入原始数据
WCIM::WCIM()
//操作结果：导入原始数据
{
	//new - 淘汰赛从文件中读入的记录数
	knockkoutMatchCount = 0;

	matchCount = 0;
	teamCount = 0;
	playerCount = 0;
	goalsCount = 0;
	fieldsCount = 0;

	//new - 初始化淘汰赛数据
	ifstream knockkoutMatchFile("knockkoutMatchRecord.txt", ios::in);
	if (!knockkoutMatchFile)
	{
		cerr << "open knockkoutMatchRecord.txt error" << endl;
		exit(1);
	}
	while (!knockkoutMatchFile.eof())
	{
		knockkoutMatchFile >> knockkoutMatch[knockkoutMatchCount].time  //时间
			>> knockkoutMatch[knockkoutMatchCount].numGoal1  //球队1进球数
			>> knockkoutMatch[knockkoutMatchCount].numGoal2;  //球队2进球数

		knockkoutMatchCount++;
	}

	//new - 初始化knockkoutMatch淘汰赛结构数据的数据
	for (int i = 0; i < 16; ++i)
	{
		knockkoutMatch[i].team1 = "";
		knockkoutMatch[i].team2 = "";
	}
	knockkoutMatchFile.close();

	ifstream fieldsFile("fieldsRecord.txt", ios::in);
	if (!fieldsFile)
	{
		cerr << "open fieldsRecord.txt error" << endl;
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
		cerr << "open matchRecord.txt error!" << endl;
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
		cerr << "open teamRecord.txt error!" << endl;
		exit(1);
	}
	while (!teamFile.eof())
	{
		teamFile >> team[teamCount].group
			>> team[teamCount].nameTeam;
		//队伍信息初始化
		team[teamCount].integral = 0;  //积分
		team[teamCount].numWin = 0;  //胜
		team[teamCount].numFlat = 0;  //平
		team[teamCount].numNegative = 0;  //负
		team[teamCount].goalsDifference = 0;  //净胜球
		++teamCount;
	}
	teamFile.close();

	ifstream playerFile("playerRecord.txt", ios::in); //以输入的方式打开文件
	if (!playerFile)   				//测试是否成功打开
	{
		cerr << "open playerRecord.txt error!" << endl;
		exit(1);
	}
	while (!playerFile.eof())
	{
		playerFile >> player[playerCount].nameTeam
			>> player[playerCount].name
			>> player[playerCount].number;
		player[playerCount].numGoal = 0;  //球员进球数

		++playerCount;
	}
	playerFile.close();

	ifstream goalsFile("goalsRecord.txt", ios::in);
	if (!goalsFile)
	{
		cerr << "open goalsRecord.txt error" << endl;
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

	//记录从文件中读入的数据条数
	cout << "matchCount:" << matchCount << endl;
	cout << "teamCount:" << teamCount << endl;
	cout << "playerCount:" << playerCount << endl;
	cout << "goalsCount:" << goalsCount << endl;
	cout << "fieldsCount:" << fieldsCount << endl;
	cout << "knockkoutMatchCount:" << knockkoutMatchCount << endl;
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
		//string time;
		switch (select)
		{
		case 1:
			DisplayMatchInforAll();
			break;
		case 2:
			DisplayPlayerInforAll();
			break;
		case 3:
			TimeGuide();
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
