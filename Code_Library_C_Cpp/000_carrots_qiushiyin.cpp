#include<iostream>
using namespace std;
int carrots;
char c, c1;
void main()
{
shuru:cout << "How many carrots do you have?" << endl;
	fflush(stdin);		//������뻺��
	cin.clear();	//���cin����
//	scanf("%d",carrots);
	cin >> carrots;
	c = getchar();
	if (c == '\n')		//�������Ϊ����
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
		cout << "Please enter a integer.Do you try again?(only Y or N)" << endl;	//����Y/N
panduan:fflush(stdin);		//������뻺��
		cin.clear();	//���cin����
		c = getchar();
		if (c == 'Y' || c == 'y')		//�жϵ�����
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
