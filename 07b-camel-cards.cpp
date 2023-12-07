#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#ifdef _DEBUG
#include "utils/debug.h"
#else
#define debug(...)
#endif

string ranks = {"AKQT98765432J"};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string line;
	ll ans = 0;
	auto ord = [&](char c) {
		return find(ranks.begin(), ranks.end(), c) - ranks.begin();
	};
	struct Hand {
		int variety;
		vector<pair<char, int>> stuff;
		string hand;
		int bid;
		bool operator<(const Hand &other) const {
			auto ord = [&](char c) {
				return find(ranks.begin(), ranks.end(), c) - ranks.begin();
			};
			if (variety != other.variety) {
				return variety < other.variety;
			}
			vector<int> va;
			for (char c : hand) va.push_back(ord(c));
			vector<int> vb;
			for (char c : other.hand) vb.push_back(ord(c));
			return va < vb;
		}
	};
	vector<Hand> hands;
	while (getline(cin, line)) {
		istringstream iss(line);
		string hand; int bid;
		string hand_save;
		iss >> hand >> bid;
		hand_save = hand;
		auto create = [&](string new_hand) {
			map<char, int> mp;
			for (char c : new_hand) mp[c]++;
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
				return Hand{1, vec, hand, bid};
			}
			else if (vec[0].second == 4) {
				return Hand{2, vec, hand, bid};
			}
			else if (vec[0].second == 3 && vec[1].second == 2) {
				return Hand{3, vec, hand, bid};
			}
			else if (vec[0].second == 3 && vec[1].second == 1) {
				return Hand{4, vec, hand, bid};
			}
			else if (vec[0].second == 2 && vec[1].second == 2) {
				return Hand{5, vec, hand, bid};
			}
			else if (vec[0].second == 2) {
				return Hand{6, vec, hand, bid};
			}
			else return Hand{7, vec, hand, bid};
		};
		vector<int> idxs;
		for (int i = 0; i < 5; ++i) {
			if (hand[i] == 'J') idxs.push_back(i);
		}
		vector<Hand> possible;
		for (char repl : ranks) {
			if (repl == 'J') continue;
			for (int idx : idxs) {
				hand[idx] = repl;
			}
			possible.push_back(create(hand));
		}
		sort(possible.begin(), possible.end());
		possible.front().hand = hand_save;
		hands.push_back(possible.front());
	}
	sort(hands.begin(), hands.end());
	reverse(hands.begin(), hands.end());
	for (ll i = 0; i < hands.size(); ++i) {
		ans += (i+1) * hands[i].bid;
	}
	cout << ans << '\n';
}
