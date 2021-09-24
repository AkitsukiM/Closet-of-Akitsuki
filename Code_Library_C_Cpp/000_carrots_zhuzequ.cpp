//
//test.cpp
//
//Created by 朱泽衢さん on 10/6/2017.
//Modified by 顾澈怡 on 10/6/2017.
//Copyright © 2017 朱泽衢さん. All rights reserved.
//
//Here goes the editor's appreciation:
//It's my honor to have access to your excellent work. Althrough there're some mistakes, it doesn't matter at all!
//Great talent can be seen in this masterpiece.
//While reading it, I was quite shocked and learned a lot. Thank you again for offering assistance to me.
//
//P.S. I have to express my sincere apologies for having changed some of your programming style when editing the code, if it is the truth.
//re P.S. I'm really appreciated if you could tell me any mistakes appearing in this revised draft.
//

#include <iostream>
#include <sstream>
#include <cstdlib>
using namespace std;

void a_msg(int n) {
	             cout << "I have ";
	if (n > 0) { cout << n;         }
	else       { cout << "no";      }
	             cout << " carrot";
	if (n > 1) { cout << "s";       }
	             cout << ".\n";
}

int main() {
	string str;
	bool err = true;
	while (err) {
	    cout << "How many carrots do you have?\n";                   // Move it to here for convenience.    
		getline(cin, str);
		err = (str.length() == 0);
		for (auto d: str) {
			err |= (d < '0' || d > '9');
		}
		if (err) {
			cout << "Only Arabic number symbols are allowed, retry? (y/n)\n"; // Here should be the first tip.
			string buf;
			getline(cin, buf);                                       // WARNING: At first the variate "buf" had no cin.
			while (buf != string("y") && buf != string("n") && getline(cin, buf).rdstate() == 0) {
				                                                     // There are two NEQ.
				cout << "Only y and n are allowed. Retry please.\n"; // Here is the second tip. The sentence is supposed be different here.
				//buf.clear();                                       // I'm not sure if it is necessary.
				getline(cin, buf);                                   // Input again and judge again.
			}
			if (buf == string("n") || getline(cin, buf).rdstate() > 0) {
				return 0;
			}
		}
	}
	int n;
	stringstream(str) >> n; // This is slow but lazy.
	a_msg(n);
	while (n > 0) {
		cout << "Crunch, crunch. Now ";
		a_msg(--n);
	}
	system("pause");                                                 // For me, I prefer to add this. We have added the contents of the cstdlib file to our program.
	return 0;
}
