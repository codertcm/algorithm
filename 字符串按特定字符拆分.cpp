

#include "bits/stdc++.h"
using namespace std;

void split(string &s1, vector<string> &res, char c){
    res.clear();
    while (!s1.empty())
    {
        if (s1.find(c) == string::npos)
        {
            res.push_back(s1);
            s1.clear();
            break;
        }
		int id = s1.find(c);
		string temp = s1.substr(0, id);
		res.push_back(temp);
		s1.erase(0, id+1);
    }
}


int main()
{
    string s1;
    getline(cin, s1);
    vector<string> res;
    split(s1, res, ':');
    for (auto &a : res)
    {
        cout << a << endl;
    }
    return 0;
}

