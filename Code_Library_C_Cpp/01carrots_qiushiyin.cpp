#include<iostream>
using namespace std;
int carrots;
char c, c1;
void main()
{
shuru:cout << "How many carrots do you have?" << endl;
	fflush(stdin);		//清空输入缓存
	cin.clear();	//清空cin缓存
//	scanf("%d",carrots);
	cin >> carrots;
	c = getchar();
	if (c == '\n')		//如果输入为数字
	{

		cout << "I have " << carrots << " carrots." << endl;
		carrots--;
		for (; carrots >= 1; carrots--)
		{
			cout << "Crunch,crunch.Now I have " << carrots << " carrots." << endl;
		}
		cout << "Crunch,crunch.Now I have no carrots." << endl;
	}
	else
	{
		fflush(stdin);
		cout << "Please enter a integer.Do you try again?(only Y or N)" << endl;	//输入Y/N
panduan:fflush(stdin);		//清空输入缓存
		cin.clear();	//清空cin缓存
		c = getchar();
		if (c == 'Y' || c == 'y')		//判断第三层
		{
			c1 = getchar();
			if (c1 == '\n')
			{
				fflush(stdin);
				goto shuru;
			}
			else
			{
				goto baocuo;
			}
		}
		else 
		{
			if (c == 'N' || c == 'n')
			{
				c1 = getchar();
				if (c1 == '\n')
				{
				}
				else
				{
					goto baocuo;
				}
			}
			else
			{
baocuo:			cout<<"Please enter Y or N!"<<endl;
				goto panduan;
			}
		}
	}
}
