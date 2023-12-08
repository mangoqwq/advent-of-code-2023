#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#ifdef _DEBUG
#include "utils/debug.h"
#else
#define debug(...)
#endif

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string line;
	string dir;
	{
		getline(cin, dir);
	}
	int M = dir.size();
	debug(M);
	getline(cin, line);

	map<string, pair<string, string>> adj;
	while (getline(cin, line)) {
		istringstream iss(line);
		string rt, eq, ch1, ch2;
		iss >> rt >> eq >> ch1 >> ch2;
		ch1 = ch1.substr(1, 3);
		ch2 = ch2.substr(0, 3);
		adj[rt] = {ch1, ch2};
	}

	int ans = 0;
	string v = "AAA";
	while (v != "ZZZ") {
		char c = dir[ans % M];
		if (c == 'L') v = adj[v].first;
		else v = adj[v].second;
		ans++;
	}
	cout << ans << '\n';
}
