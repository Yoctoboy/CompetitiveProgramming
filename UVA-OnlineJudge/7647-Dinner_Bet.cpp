#define _CRT_SECURE_NO_WARNINGS
#define RMAX 800 #Maximum amount of rounds computed
#define eps 1e-6 #Used for early stopping
typedef unsigned long long LL;

#include <cstring>
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;
int N, D, C, S;
int list1[10];
double probas[RMAX][11][11][11]; // R,S,A,B
double pok[RMAX]; //probability to finish at round R

float max(float a, float b) {
	return a < b ? b : a;
}

long double parmi(int k, int n) {
	if (k > n) return 0;
	if (k * 2 > n) k = n - k;
	if (k == 0) return 1;

	long double result = n;
	for (int i = 2; i <= k; i++) {
		result *= (n - i + 1);
		result /= i;
	}
	return result;
}

double p(int N, int D, int A, int B, int S, int i, int j, int k) {
	return ((double)parmi(i, A + i) / (double)parmi(D, N))*(double)(parmi(j, B + j)*parmi(k, S + k))*parmi(D - i - j - k, N - (A + i) - (B + j) - (S + k));
}

void init() {
	int x;
	S = 0;
	for (int i = 0; i < C; i++) {
		cin >> x;
		list1[i] = x;
	}
	for (int i = 0; i < C; i++) {
		bool found = false;
		cin >> x;
		for (int j = 0; j < C; j++) {
			if (list1[j] == x) {
				S++;
			}
		}
	}
}

void solver() {
	//init
	memset(probas, 0, sizeof(probas[0][0][0][0]) * RMAX * 11 * 11 * 11);
	memset(pok, 0, sizeof(pok[0])*RMAX);
	probas[0][S][C-S][C-S] = 1.0;
	double sum = 0.0;
	int niter = 0;
	double pr;
	//algo
	for (int R = 1; R < RMAX && sum < 1-eps; R++) {
		niter++;
		for (int s = 0; s <= S; s++) {
			for (int a = 0; a <= C - S; a++) {
				for (int b = 0; b <= C - S; b++) {
					pr = 0.0;
					for (int i = 0; i <= D; i++) {
						for (int j = 0; j <= D - i; j++) {
							for (int k = 0; k <= D - i - j; k++) {
								if (s+k<=S && a+i<=C-S && b+j<=C-S) {
									pr += (double)p(N, D, a, b, s, i, j, k)*probas[R - 1][s + k][a + i][b + j];
								}
							}
						}
					}
					probas[R][s][a][b] = pr;
				}
			}
		}
		double pokR = 0.0;
		for (int a = 0; a <= C - S; a++) {
			pokR += probas[R][0][a][0];
		}
		for (int b = 1; b <= C - S; b++) {
			pokR += probas[R][0][0][b];
		}
		pokR -= sum;
		sum += pokR;
		pok[R] = pokR;
	}
	float res = 0.0;
	for (int R = 1; R <= niter; R++) {
		res += R*pok[R];
	}
	cout << setprecision(8) << res << endl;
}

int main()
{
	while (scanf("%d %d %d", &N, &D, &C) == 3) {
		init();
		if (N==D) {
			cout << 1 << endl;
		}
		else {
			solver();
		}
	}
	return 0;
}

