double exchange(int Performance)
{
	if (Performance >= 90 && Performance <= 100)
		return 4.0;
	else if (Performance == 89 || Performance == 88 || Performance == 87)
		return 3.9;
	else if (Performance == 86 || Performance == 85)
		return 3.8;
	else if (Performance == 84 || Performance == 83)
		return 3.7;
	else if (Performance == 82)
		return 3.6;
	else if (Performance == 81 || Performance == 80)
		return 3.5;
	else if (Performance == 79 || Performance == 78)
		return 3.4;
	else if (Performance == 77 || Performance == 76)
		return 3.3;
	else if (Performance == 75)
		return 3.2;
	else if (Performance == 74)
		return 3.1;
	else if (Performance == 73)
		return 3.0;
	else if (Performance == 72)
		return 2.9;
	else if (Performance == 71)
		return 2.8;
	else if (Performance == 70 || Performance == 69)
		return 2.7;
	else if (Performance == 68)
		return 2.6;
	else if (Performance == 67)
		return 2.5;
	else if (Performance == 66)
		return 2.4;
	else if (Performance == 65 || Performance == 64)
		return 2.3;
	else if (Performance == 63)
		return 2.2;
	else if (Performance == 62)
		return 2.1;
	else if (Performance == 61)
		return 1.8;
	else if (Performance == 60)
		return 1.6;
	else if (Performance == 600) // 补考合格
		return 1.0;
	else if (Performance == 6000) // 两级制的通过
		return -1.0;
	else
		return 0;
}
