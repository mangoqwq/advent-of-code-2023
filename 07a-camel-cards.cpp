#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#ifdef _DEBUG
#include "utils/debug.h"
#else
#define debug(...)
#endif

string ranks = {"AKQJT98765432"};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string line;
	ll ans = 0;
	struct Hand {
		int variety;
		vector<pair<char, int>> stuff;
		string hand;
		int bid;
	};
	auto ord = [&](char c) {
		return find(ranks.begin(), ranks.end(), c) - ranks.begin();
	};
	vector<Hand> hands;
	while (getline(cin, line)) {
		istringstream iss(line);
		string hand; int bid;
		iss >> hand >> bid;
		map<char, int> mp;
		for (char c : hand) mp[c]++;
		vector<pair<char, int>> vec;
		for (auto [c, i] : mp) {
			vec.push_back({c, i});
		}
		sort(vec.begin(), vec.end(), [&](pair<char, int> a, pair<char, int> b) { 
			auto orda = ord(a.first);
			auto ordb = ord(b.first);
			return tie(a.second, ordb) > tie(b.second, orda);
		});
		if (vec[0].second == 5) {
			hands.push_back(Hand{1, vec, hand, bid});
		}
		else if (vec[0].second == 4) {
			hands.push_back(Hand{2, vec, hand, bid});
		}
		else if (vec[0].second == 3 && vec[1].second == 2) {
			hands.push_back(Hand{3, vec, hand, bid});
		}
		else if (vec[0].second == 3 && vec[1].second == 1) {
			hands.push_back(Hand{4, vec, hand, bid});
		}
		else if (vec[0].second == 2 && vec[1].second == 2) {
			hands.push_back(Hand{5, vec, hand, bid});
		}
		else if (vec[0].second == 2) {
			hands.push_back(Hand{6, vec, hand, bid});
		}
		else hands.push_back(Hand{7, vec, hand, bid});
	}
	sort(hands.begin(), hands.end(), [&](Hand a, Hand b) {
		if (a.variety != b.variety) {
			return a.variety < b.variety;
		}
		vector<int> va;
		for (char c : a.hand) va.push_back(ord(c));
		vector<int> vb;
		for (char c : b.hand) vb.push_back(ord(c));
		return va < vb;
	});
	reverse(hands.begin(), hands.end());
	for (ll i = 0; i < hands.size(); ++i) {
		ans += (i+1) * hands[i].bid;
	}
	cout << ans << '\n';
}
