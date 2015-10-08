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

int ans, cnt = 0;
vector<bool > isCut;

int dfs(vector<vector<int> > &graph, vector<int> &discovery, int here, bool isRoot) {

	discovery[here] = ++cnt;

	int ret = discovery[here];
	int children = 0;

	for (int i = 0; i < graph[here].size(); i++) {
		int there = graph[here][i];
		int mmin = discovery[there];
		//���� ������ ��Ʈ�� �ؼ� ������ ����Ʈ������ ���� ���� �� �� �ִ� ������ ��ȣ�� ã�Ƽ� �����Ѵ�
		//���� ���� ����Ʈ���� ����Ǿ��ִ� ���� ���ڰ� ���� ����(���� ����)�� ������ �������� ���ٸ� �̴� 
		//�������� Cutvertex�ΰ� �ǹ��Ѵ�.
		if (discovery[there] == 987654321) {
			children++;
			mmin = dfs(graph, discovery, there, false);
			if (mmin >= discovery[here] && !isRoot && isCut[here] == false) {
				isCut[here] = true;
				ans++;
			}
			ret = min(ret, mmin);
		}
		else
			ret = min(ret, discovery[there]);
	}

	//���� �� ������ ��Ʈ�̸� �������� ������ �ڽ��� �ΰ� �̻� ������ �Ѵ�. �̴� �׸��� �׷����� �ڸ���
	if ((isRoot && children >= 2)){
		isCut[here] = true;
		ans++;
	}

	return ret;
}


int main(){
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	int n;
	while (cin >> n){
		if (n == 0) exit(0);
		vector<vector<int> > graph(n + 1); //�׷��� 
		vector<int > discovery(n + 1, 987654321); //������ �з��� ���� �迭
		isCut = vector<bool>(n + 1, false);	 //������ ���������� �ƴ��� Ȯ���ϱ� ����

		string str;

		//�׷��� �𵨸�

		while (getline(cin, str)) {
			if (str.size() == 1 && str[0] == '0')
				break;
			else {
				int num = 0;
				bool ishere = false;
				int here;
				str.push_back(' ');
				for (int i = 0; i < str.size(); i++) {
					if (str[i] == ' ') {
						if (ishere) {
							graph[here].push_back(num);
							graph[num].push_back(here);
							num = 0;
						}
						else{
							here = num;
							num = 0;
							ishere = true;
						}
					}
					else {
						num *= 10;
						num += str[i] - '0';
					}
				}

			}
		}

		cnt = 0;
		ans = 0;
		for (int i = 1; i <= n; i++){
			if (discovery[i] == 987654321)
				dfs(graph, discovery, 1, true);
		}
		cout << ans << endl;
	}
}