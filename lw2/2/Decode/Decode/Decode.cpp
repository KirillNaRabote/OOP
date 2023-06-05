#include <iostream>
#include "HtmlDecode.h"

using namespace std;

int main()
{
	string str;
	map <string, string> wordsToDecode;

	FillWordsToDecode(wordsToDecode);

	while (getline(cin, str))
	{
		cout << HtmlDecode(str, wordsToDecode) << endl;
	}

	return 0;
}