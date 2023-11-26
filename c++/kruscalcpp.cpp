// Kruskal 算法求最小生成树 
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 2e5 + 10;

struct node {
	int x, y, z;
}edge[maxn];

bool cmp(node a, node b) {
	return a.z < b.z;
}

int fa[maxn];

int n, m;

int u, v, w;

long long sum;

int get(int x) {
	return x == fa[x] ? x : fa[x] = get(fa[x]);
}

static int test(void) {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &edge[i].x, &edge[i].y, &edge[i].z);
	}
	for (int i = 0; i <= n; i++) {
		fa[i] = i;
	}
	sort(edge + 1, edge + 1 + m, cmp);
	// 每次加入一条最短的边
	for (int i = 1; i <= m; i++) {
		int x = get(edge[i].x);
		int y = get(edge[i].y);
		if (x == y) continue;
		fa[y] = x;
		sum += edge[i].z;
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (i == fa[i]) ans++;
	}
	if (ans > 1) puts("impossible");
	else printf("%lld\n", sum);
	return 0;
}
