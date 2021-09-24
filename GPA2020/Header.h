/*
* GPA Calculator Version 1.01a
* Copyright (c) 2020 Marina Akitsuki. All rights reserved.
*
* Date modified: 2020/01/21
* Bad luck!
*/

#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cctype>

#ifndef LINUX
#define THEEND system("pause"); return 0
#else
#define THEEND return 0
#endif

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::ostream;
using std::ifstream;

double exchange(int Performance);

#include "Course.h"

#endif // !HEADER_H
