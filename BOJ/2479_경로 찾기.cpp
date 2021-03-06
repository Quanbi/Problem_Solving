#include <iostream>
#include <functional>
#include <fstream>
#include <string>
#include <string.h>
#include <queue>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <limits.h>

typedef long long ll;
using namespace std;

int n, m;

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif
	cin >> n >> m;
	vector<string> vertex(n);
	vector<vector<int> > graph(n);
	for (int i = 0; i < n; i++)
		cin >> vertex[i];
	for (int i = 0; i < n; i++){
		for (int j = i + 1; j < n; j++){
			int flag = 0;;
			for (int k = 0; k < m; k++){
				if (vertex[i][k] != vertex[j][k])
					flag ++;
			}
			if (flag == 1){
				graph[i].push_back(j);
				graph[j].push_back(i);
			}
		}
	}
	int begin, end;
	cin >> begin >> end;
	begin -= 1,	end -= 1;
	vector<int> dis(n, INT_MAX);
	vector<int> track(n, -1);

	priority_queue < pair<int, int>, vector<pair<int, int> >, greater<pair<int, int > > > pq;
	pq.push(make_pair(0, begin));
	dis[begin] = 0;

	vector<int> res;
	while (!pq.empty()){
		int here = pq.top().second;
		int here_dis = pq.top().first;
		pq.pop();
		if (dis[here] < here_dis)
			continue;
		for (int i = 0; i < graph[here].size(); i++){
			int there = graph[here][i];
			if (dis[there] > here_dis + 1){
				dis[there] = here_dis + 1;
				pq.push(make_pair(here_dis + 1, there));
				track[there] = here;
			}
		}
	}
	if (dis[end] == INT_MAX){
		cout << "-1" << endl;
		return 0;
	}
	while(track[end] != -1){
		res.push_back(end);
		end = track[end];
	}
	res.push_back(begin);
	reverse(res.begin(), res.end());
	for (int i = 0; i < res.size(); i++){
		cout << res[i]  + 1<< " ";
	}
	cout << endl;
}