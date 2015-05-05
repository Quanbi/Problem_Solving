#include <iostream>
#include <utility>
#include <limits.h>
#include <fstream>
#include <string>
#include <string.h>
#include <queue>
#include <stdio.h>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <stack>
#include <functional>

typedef long long ll;
using namespace std;

int t, n, m;
vector<vector<pair<int, int > > > graph;

//dijkstra�� ����ؼ� ������ Ǫ�µ�, �̶� ����Ÿ���  -1�� ���� �׷����� �����ش�.
//����Ŭ üũ�� �׷����� �ִ� limit(n * 1000 * -1) �� ������ infinity�� ����.
//�̶� ����Ŭ üũ�� �Ÿ� ���ٴ� �� ������ �󸶳� ���� �����ߴ��ķ� �˻����ָ� �� �� ȿ�����̴�.

int dijkstra(ll limit){
	vector<int> dis(n, INT_MAX);
	dis[0] = 0;
	priority_queue<pair<int, int >, vector<pair<int, int> >, greater<pair<int, int> > > pq;
	pq.push(make_pair(0, 0));
	while (!pq.empty()){
		int here = pq.top().second;
		int here_dis = pq.top().first;
		pq.pop();
		if (here_dis > dis[here]) continue;
		for (int i = 0; i < graph[here].size(); i++){
			int there = graph[here][i].first;
			int there_dis = graph[here][i].second + here_dis;
			if (there_dis < limit) 
				return INT_MIN;
			if (there_dis < dis[there]){
				dis[there] = there_dis;
				pq.push(make_pair(there_dis, there));
			}
		}
	}
	return dis[1];
}

int main(){
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w+", stdout);
#endif
	scanf("%d", &t);
	while (t--){
		scanf("%d %d", &n, &m);
		graph = vector<vector<pair <int, int > > >(n);
		for (int i = 0; i < m; i++){
			int here, there, weight;
			scanf("%d %d %d", &here, &there, &weight);
			graph[here].push_back(make_pair(there, weight));
		}

		ll a = dijkstra(abs(1000 * n) * -1);
		if (a == INT_MAX){
			cout << "UNREACHABLE" << endl;
			continue;
		}
		for (int i = 0; i < graph.size(); i++)
			for (int j = 0; j < graph[i].size(); j++)
				graph[i][j].second *= -1;
			
		ll b = dijkstra(abs(1000 * n) * -1);

		if (a != INT_MIN && b != INT_MIN)
			cout << a << " " << (b * -1) << endl;
		else if (a != INT_MIN && b == INT_MIN)
			cout << a << " INFINITY" << endl;
		else if (a == INT_MIN && b != INT_MIN)
			cout << "INFINITY " << b * -1<< endl;
		else
			cout << "INFINITY INFINITY" << endl;

	}
}