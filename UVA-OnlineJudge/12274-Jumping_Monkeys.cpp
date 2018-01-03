/***********
PROBLEM : https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3426
***********/

#include <iostream>
#include <cstdint>
#include <vector>
#include <cmath>
#include <bitset>
#include <cstring>
#include <algorithm>

using namespace std;

//global
int n, m;
bool graph[21][21];
bool deg1[21]; //init
int fwtab[21][21];
bool treated[21];

void initialize() {
	int u, v;
	for (int i = 0; i < n; i++) memset(graph[i], 0, sizeof(graph[i]));
	memset(treated, 0, sizeof(treated));
	memset(deg1, 0, sizeof(deg1));
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &u, &v);
		graph[u][v] = 1;
		graph[v][u] = 1;
	}
	for (int i = 0; i < n; i++) {
		int nb = 0;
		for (int j = 0; j < n && nb<=1; j++) if (graph[i][j]) nb++;
		if (nb <= 1) deg1[i] = true;
	}
}

pair<int,int> getstarter() { //<index,distance>
	int maxdist = 0;
	int starter = 20;
	for (int i = 0; i < n; i++) {
		if (!deg1[i]) {
			for (int j = i+1; j < n; j++) {
				if (!deg1[j]) {
					if (fwtab[i][j] > maxdist) {
						maxdist = fwtab[i][j];
						starter = i;
					}
				}
			}
		}
	}
	if (maxdist == 0) {
		int index = 0;
		while (deg1[index]) index++;
		starter = index;
	}
	return make_pair(starter, maxdist);
}

void fw() {
	fill_n((int*)fwtab, 441, 100);
	for (int u = 0; u < n; u++) fwtab[u][u] = 0;
	for (int u = 0; u < n; u++) {
		for (int j = 0; j < n; j++) if (graph[u][j] == 1) fwtab[u][j] = 1;
	}
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) fwtab[i][j] = min(fwtab[i][j], fwtab[i][k] + fwtab[k][j]);
		}
	}
}

vector<int> parcours(int i) {
	treated[i] = 1;
	vector<int> path;
	path.push_back(i);
	bool leaf = true;
	for (int j = 0; j < n; j++) {
		if (!treated[j] && !deg1[j]) {
			if (graph[i][j]) {
				leaf = false;
				break;
			}
		}
	}
	if (leaf) return path;
	else {
		int longest = i;
		vector<int> possibles;
		for (int j = 0; j < n; j++) if (j != i && !deg1[j] && graph[i][j] && !treated[j]) possibles.push_back(j);
		vector<vector<int>> paths;
		for (int j : possibles) {
			vector<int> pathj = parcours(j);
			pathj.push_back(i);
			paths.push_back(pathj);
		}
		int maxpathindex = paths.size()-1;
		for (int i = paths.size() - 2; i >= 0; i--) if (paths[i].size() > paths[maxpathindex].size()) maxpathindex = i;
		for (int i = 0; i < paths.size(); i++) if (i != maxpathindex) path.insert(path.end(), paths[i].begin(), paths[i].end());
		path.insert(path.end(), paths[maxpathindex].begin(), paths[maxpathindex].end());	
		return path;
	}
}

bool checkparcours(vector<int> parc) {
	bool monkeys[21];
	bool nextmonkeys[21];
	memset(monkeys, true, sizeof(monkeys));
	memset(nextmonkeys, false, sizeof(nextmonkeys));
	for (int i = 0; i < parc.size(); i++) {
		int shoot = parc[i];
		for (int j = 0; j < n; j++) {
			if (monkeys[j] && shoot != j) {
				for (int k = 0; k < n; k++) {
					if (graph[j][k]) nextmonkeys[k] = true;
				}
			}
		}
		for (int j = 0; j < n; j++) {
			monkeys[j] = nextmonkeys[j];
			nextmonkeys[j] = false;
		}
	}
	for (int i = 0; i < n; i++) if (monkeys[i]) return false;
	return true;
}

void solver() {
	initialize();
	if (m >= n) puts("Impossible");
	else if (m == 0) puts("1: 0");
	else if (m == 1) puts("2: 0 0");
	else {
		fw();
		pair<int,int> onset = getstarter();
		int start = onset.first;
		vector<int> p = parcours(start);
		vector<int> premier(p.begin(), p.end() - onset.second); //tronquage nécessaire
		if (premier.size() % 2 != 0) {
			vector<int> premier2;
			premier2 = premier;
			premier.insert(premier.end(), premier2.begin(), premier2.end());
			if (checkparcours(premier)) {
				cout << premier.size() << ": ";
				for (int i = 0; i < premier.size() - 1; i++) cout << premier[i] << " ";
				cout << premier[premier.size() - 1] << endl;
			}
			else puts("Impossible");
		}
		else {
			int furthest = start;
			for (int i = 0; i < n; i++) {
				treated[i] = 0;
				if (!deg1[i] && (fwtab[start][i] > fwtab[start][furthest])) furthest = i;
			}
			vector<int> s = parcours(furthest);
			vector<int> second(s.begin(), s.end() - onset.second); //tronquage nécessaire
			premier.insert(premier.end(), second.begin(), second.end());
			if (checkparcours(premier)) {
				cout << premier.size() << ": ";
				for (int i = 0; i < premier.size() - 1; i++) cout << premier[i] << " ";
				cout << premier[premier.size() - 1] << endl;
			}
			else puts("Impossible");
		}
	}
}

int main() {
	cin >> n >> m;
	while (n != 0) {
		solver();
		cin >> n >> m;
	}
	return 0;
}
