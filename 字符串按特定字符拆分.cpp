

#include "bits/stdc++.h"
using namespace std;

int main()
{
    string s1;
    getline(cin, s1);
    vector<string> res;
    while (!s1.empty())
    {
        if (s1.find(" ") == string::npos)
        {
            res.push_back(s1);
            s1.clear();
            break;
        }
		int id = sample.find(" ");
		string temp = sample.substr(0, id);
		v.push_back(temp);
		sample.earse(0, id+1);
    }
    for (auto &a : res)
    {
        cout << a << endl;
    }
    return 0;
}

