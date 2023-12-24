#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#ifdef _DEBUG
#include "utils/debug.h"
#else
#define debug(...)
#endif

/**
 * Author: Stanford
 * Source: Stanford Notebook
 * License: MIT
 * Description: Solves a general linear maximization problem: maximize $c^T x$ subject to $Ax \le b$, $x \ge 0$.
 * Returns -inf if there is no solution, inf if there are arbitrarily good solutions, or the maximum value of $c^T x$ otherwise.
 * The input vector is set to an optimal $x$ (or in the unbounded case, an arbitrary solution fulfilling the constraints).
 * Numerical stability is not guaranteed. For better performance, define variables such that $x = 0$ is viable.
 * Usage:
 * vvd A = {{1,-1}, {-1,1}, {-1,-2}};
 * vd b = {1,1,-4}, c = {-1,-1}, x;
 * T val = LPSolver(A, b, c).solve(x);
 * Time: O(NM * \#pivots), where a pivot may be e.g. an edge relaxation. O(2^n) in the general case.
 * Status: seems to work?
 */

#define rep(i, from, to) for (int i = from; i < (to); ++i)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

typedef __float128 T; // long double, Rational, double + mod<P>...
typedef vector<T> vd;
typedef vector<vd> vvd;

const T eps = 1e-8, inf = 1/.0;
#define MP make_pair
#define ltj(X) if(s == -1 || MP(X[j],N[j]) < MP(X[s],N[s])) s=j

struct LPSolver {
	int m, n;
	vi N, B;
	vvd D;

	LPSolver(const vvd& A, const vd& b, const vd& c) :
		m(sz(b)), n(sz(c)), N(n+1), B(m), D(m+2, vd(n+2)) {
			rep(i,0,m) rep(j,0,n) D[i][j] = A[i][j];
			rep(i,0,m) { B[i] = n+i; D[i][n] = -1; D[i][n+1] = b[i];}
			rep(j,0,n) { N[j] = j; D[m][j] = -c[j]; }
			N[n] = -1; D[m+1][n] = 1;
		}

	__float128 abs(__float128 x) {
		return x < 0 ? -x : x;
	}
	void pivot(int r, int s) {
		T *a = D[r].data(), inv = 1 / a[s];
		rep(i,0,m+2) if (i != r && abs(D[i][s]) > eps) {
			T *b = D[i].data(), inv2 = b[s] * inv;
			rep(j,0,n+2) b[j] -= a[j] * inv2;
			b[s] = a[s] * inv2;
		}
		rep(j,0,n+2) if (j != s) D[r][j] *= inv;
		rep(i,0,m+2) if (i != r) D[i][s] *= -inv;
		D[r][s] = inv;
		swap(B[r], N[s]);
	}

	bool simplex(int phase) {
		int x = m + phase - 1;
		for (;;) {
			int s = -1;
			rep(j,0,n+1) if (N[j] != -phase) ltj(D[x]);
			if (D[x][s] >= -eps) return true;
			int r = -1;
			rep(i,0,m) {
				if (D[i][s] <= eps) continue;
				if (r == -1 || MP(D[i][n+1] / D[i][s], B[i])
				             < MP(D[r][n+1] / D[r][s], B[r])) r = i;
			}
			if (r == -1) return false;
			pivot(r, s);
		}
	}

	T solve(vd &x) {
		int r = 0;
		rep(i,1,m) if (D[i][n+1] < D[r][n+1]) r = i;
		if (D[r][n+1] < -eps) {
			pivot(r, n);
			if (!simplex(2) || D[m+1][n+1] < -eps) return -inf;
			rep(i,0,m) if (B[i] == -1) {
				int s = 0;
				rep(j,1,n+1) ltj(D[i]);
				pivot(i, s);
			}
		}
		bool ok = simplex(1); x = vd(n);
		rep(i,0,m) if (B[i] < n) x[B[i]] = D[i][n+1];
		return ok ? D[m][n+1] : inf;
	}
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string line;
	struct Shard {
		double x, y, z;
		double dx, dy, dz;
	};
	vector<Shard> vec;
	while (getline(cin, line)) {
		istringstream iss(line);
		Shard s;
		char c;
		iss >> s.x >> c >> s.y >> c >> s.z >> c;
		iss >> s.dx >> c >> s.dy >> c >> s.dz;
		vec.push_back(s);
	}
	const T LO = 200000000000000;
	const T HI = 400000000000000;
	// const T LO = 7;
	// const T HI = 27;
	int N = vec.size();
	int ans = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = i+1; j < N; ++j) {
			auto [x1, y1, z1, dx1, dy1, dz1] = vec[i];
			auto [x2, y2, z2, dx2, dy2, dz2] = vec[j];
			vvd A = {
				{dx1, -dx2},
				{-dx1, dx2},
				{dy1, -dy2},
				{-dy1, dy2},
			};
			vd b = {
				{x2 - x1},
				{x1 - x2},
				{y2 - y1},
				{y1 - y2},
			};
			vd c = {0, 0};
			LPSolver simplex(A, b, c);
			vd x(2);
			auto ret = simplex.solve(x);
			// debug(ret);
			bool ok = ret != -inf;
			T px = x1 + dx1 * x[0];
			T py = y1 + dy1 * x[0];
			ok &= px >= LO && px <= HI;
			ok &= py >= LO && py <= HI;
			ans += ok;
		}
	}
	cout << ans << '\n';
}
