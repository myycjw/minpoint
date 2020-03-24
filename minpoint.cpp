#include<map>
#include<stdlib.h>
#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn = 1e5 + 10;
#define ll long long
int i, j, k;
int n, m;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
struct point {
	double x, y;
}p[maxn];
double dis(point p1, point p2) {
	return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}
bool cmp1(point p1, point p2) {
	return p1.x < p2.x;
}
bool cmp2(point p1, point p2) {
	return p1.y < p2.y;
}
//蛮力法
double getmin(int n) {
	double minn = sqrt((p[0].x - p[1].x)*(p[0].x - p[1].x) + (p[0].y - p[1].y)*(p[0].y - p[1].y));
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			double t = sqrt((p[i].x - p[j].x)*(p[i].x - p[j].x) + (p[i].y - p[j].y)*(p[i].y - p[j].y));
			if (minn > t)
				minn = t;
		}
	}
	return minn;
}
//分治法
double getmin2(point p[], int L, int R) {
	int mid = (R + L) / 2, l = L, r = R;
	if (R - L == 1) {
		return dis(p[R], p[L]);
	}
	if (R - L == 2) {
		double d1 = dis(p[R], p[L]), d2 = dis(p[R], p[R + 1]), d3 = dis(p[R + 1], p[L]);
		return min(min(d1, d2), d3);
	}
	double d1 = getmin2(p, L, mid), d2 = getmin2(p, mid + 1, R);
	double d = min(d1, d2);
	while (p[l].x < p[mid].x - d && l <= R);
		l++;
	while (p[r].x > p[mid].x + d && r >= L)
		r++;
	sort(p + 1, p + r + 1, cmp2);
	double t;
	for (int i = l; i <= r; i++) {
		for (int j = i + 1; j <= r; j++) {
			if (p[j].y - p[i].y >= d) {
				break;
			}
			else {
				t = dis(p[i], p[j]);
				if (t < d)
					d = t;
			}
		}
	}
	return d;
}
int main() {
	cin >> n;
	for (i = 1; i <= n; i++) {
		cin >> p[i].x >> p[i].y;
	}
	sort(p + 1, p + n + 1, cmp1);
	for (i = 1; i <= n; i++) {
		cout << p[i].x << " " << p[i].y << endl;
	}
	if(n<=3)
		cout << getmin(n) << endl;
	else
		cout << getmin2(p, 1, n) << endl;
	return 0;
}
