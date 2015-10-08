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

typedef long long ll;
using namespace std;

#define INF 987654321


int sccidx;
//SCC COMPONENT�� idx
int cnt;
//������ ������ �����ϱ� ���ؼ� ������ �߰� ������ �����Ѵ�. 

bool cmp(const vector<int> &a, const vector<int> &b) {
	//����� ���� ��Ʈ
	return a[0] < b[0];
}

int dfs(vector<vector<int> > &graph, vector<int> &dis, vector<int> &SCC, stack<int> &st, int u) {

	dis[u] = ++cnt;
	//������ ������ �˾Ƴ������ؼ� ������ �߰� ������ ����Ѵ�.
	int ret = dis[u];
	//�ڽ��� �ڽ� �߿��� �ڱ⺸�� �������� �� �� �ִ��� ����ϴ� �����̴�. �ʱⰪ�� �ڱ� �ڽ��� ��ȣ
	st.push(u);
	//u�� subtree�� ��� u���� ������ stack ���̰� �ȴ�.
	for (int i = 0; i < graph[u].size(); i++) {
		int v = graph[u][i];
		//there
		int mmin = INF;
		if (dis[v] == INF)
			mmin = dfs(graph, dis, SCC, st, v);
		//mmin�� ������  u -> v �� Ʈ�������� ���
		else if (SCC[v] == -1)
			mmin = dis[v];
		//Ȥ�� u -> v ���� �����϶� �ٸ� ���� �� ���������� �ٸ� ������Ʈ�� �������� ���� ��쿡�� ret�� �����ؾ��Ѵ�.
		//�ٸ� ������Ʈ�� ������ ��� 
		ret = min(ret, mmin);

	}


	if (ret == dis[u]) {

		while (true) {
			int t = st.top();
			SCC[st.top()] = sccidx;
			st.pop();
			if (t == u) break;
		}
		sccidx++;
	}

	return ret;
}

int main(){
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif
	int n, m;
	cin >> n >> m;

	vector < vector< int > >  graph(n + 1);
	vector <int> dis(n + 1, INF);
	//������ �߰� ������ ���
	vector <int> SCC(n + 1, -1);
	//i��° ������ ���° component���� ����Ѵ�.
	vector <vector< int > > ans;
	//�� ����� ���� �迭

	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		graph[u].push_back(v);
	}

	for (int i = 1; i <= n; i++) {
		stack<int> st;
		if (dis[i] == INF) //������ �ѹ��� �߰� ���� �ʾ��� ������ Ž���� �����Ѵ�.
			dfs(graph, dis, SCC, st, i);
	}

	ans.resize(sccidx);

	for (int i = 1; i <= n; i++) {
		int sccid = SCC[i];
		ans[sccid].push_back(i);
	}

	for (int i = 0; i < ans.size(); i++) {
		sort(ans[i].begin(), ans[i].end());
	}

	sort(ans.begin(), ans.end(), cmp);
	cout << ans.size() << endl;

	for (int i = 0; i < ans.size(); i++) {
		for (int j = 0; j < ans[i].size(); j++) {
			cout << ans[i][j] << " ";
		}
		cout << "-1\n";
	}
}

