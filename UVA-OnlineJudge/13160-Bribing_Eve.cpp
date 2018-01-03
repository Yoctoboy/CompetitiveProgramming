/***********
PROBLEM : https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=871&page=show_problem&problem=5060
***********/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cfloat>
#include <cstdint>
using namespace std;

typedef int16_t smint; //small int

pair<smint, smint> scores[100000];
pair<smint, smint> maria;
pair<float, int> intersections[1000000]; // intersections[i] = pair < abscisse , battery index >
int N, nbinf, nbsup, bestpos, worstpos;
int passageplus, passagemoins;

void initialize() {
	bestpos = 0; worstpos = 0; nbinf = 0; nbsup = 0;
	smint x1, x2;
	scanf("%d%d", &x1, &x2);
	maria.first = x2; maria.second = x1 - x2;
	scores[0] = make_pair(x2, x1-x2);
	for (int i = 1; i < N; i++) {
		scanf("%d%d", &x1, &x2);
		scores[i] = make_pair(x2,x1-x2);
		if (x2 < maria.first) {
			nbinf++; //inferieur strict
		}
		else if (x2 > maria.first) {
			nbsup++; //supérieur strict
		}
	}
	bestpos = nbsup + 1;
	worstpos = N - nbinf;
}

void findintersections() {
	intersections[0] = make_pair(FLT_MAX, 0); // intersections de maria avec elle-même
	for (int i = 1; i < N; i++) {
		if (scores[i].second != maria.second) {
			intersections[i] = make_pair((float)(scores[i].first - maria.first) / (float)(maria.second - scores[i].second), i);
		}
		else {
			intersections[i] = make_pair(-1, i);
		}
	}
	sort(intersections, intersections+N);
}

void findall() {
	float w1;
	int index = 0;
	float w = intersections[index].first;	
	while (w < 0 && index < N) {
		index++;
		w = intersections[index].first;
	}
	if (w == 0 && index < N) {
		passageplus = 0;
		passagemoins = 0;
		w1 = intersections[index].first;
		do {
			if (scores[intersections[index].second].second > maria.second) {
				passageplus++;
			}
			if (scores[intersections[index].second].second < maria.second) {
				passagemoins++;
			}
			index++;
			w = intersections[index].first;
		} while (w == w1 && index < N);
		nbsup += passageplus; //on ne fait qu'ajouter car l'initialisation garde toutes les égalités
		nbinf += passagemoins;
	}
	while (w <= 1 && index < N) {
		passageplus = 0;
		passagemoins = 0;
		w1 = intersections[index].first;
		do {
			if (scores[intersections[index].second].second > maria.second) {
				passageplus++;
			}
			if (scores[intersections[index].second].second < maria.second) {
				passagemoins++;
			}
			index++;
			w = intersections[index].first;
		} while (w == w1 && index < N);
		nbsup -= passagemoins;
		nbinf -= passageplus;
		if (nbsup + 1 < bestpos) {
			bestpos = nbsup + 1;
		}
		if (N - nbinf > worstpos) {
			worstpos = N - nbinf;
		}
		nbsup += passageplus;
		nbinf += passagemoins;
	}
}

void solver() {
	initialize();
	findintersections();
	findall();
	cout << bestpos << " " << worstpos << endl;
}

int main()
{
	while (scanf("%d", &N) == 1) {
		solver();
	}
}