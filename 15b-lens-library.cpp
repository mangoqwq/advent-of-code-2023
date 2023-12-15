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
	int ans = 0;
	vector<vector<pair<string, int>>> boxes(256);
	while (getline(cin, line)) {
		istringstream iss(line);
		string cur;
		int hsh = 0;
		for (char c : line) {
			if (c == ',') {
				auto &box = boxes[hsh];
				if (cur.back() == '-') {
					string id = cur.substr(0, cur.size() - 1);
					for (int i = 0; i < box.size(); ++i) {
						if (box[i].first == id) {
							box.erase(box.begin() + i);
							break;
						}
					}
				}
				else {
					string id = cur.substr(0, cur.size() - 2);
					int val = cur.back() - '0';
					bool added = 0;
					for (auto &[s, value] : box) {
						if (s == id) value = val, added = 1;
					}
					if (!added) box.push_back({id, val});
				}

				hsh = 0;
				cur = "";
			}
			else {
				cur += c;
				if (!(c == '-' || c == '=' || isdigit(c))) {
					hsh = (hsh + c) * 17 % 256;
				}
			}
		}
	}
	for (int i = 0; i < 256; ++i) {
		for (int j = 0; j < boxes[i].size(); ++j) {
			ans += (i+1) * (j+1) * boxes[i][j].second;
		}
	}
	cout << ans << '\n';
}
