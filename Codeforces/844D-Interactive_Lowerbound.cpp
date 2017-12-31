#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <map>
#include <deque>
#include <queue>
#include <climits>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define SORT(v) sort(v.begin(), v.end())
#define SORTFUNC(v, func) sort(v.begin(), v.end(), func)
#define PRINT(v) REP(i, v.size()) printf("%d ", v[i]); cout << endl
#define SCI(n) int (n); scanf("%d", &(n))
#define SCL(n) ll (n); scanf("%I64d", &(n))
#define IN(n) scanf("%d", &(n))

int queryamount;
int ecartmax = 50000;
bool seen[50000];
int n, start, x;

void ans(int n){
  printf("! %d\n", n);
  fflush(stdout);
  exit(0);
}

pii ask(int index){
  queryamount++;
  printf("? %d\n", index);
  fflush(stdout);
  int a, b;
  scanf("%d %d", &a, &b);
  seen[b] = true;
  if(queryamount >= 1999) ans(-1);
  return make_pair(a, b);
}

int main(){
  srand(time(0));
  memset(seen, false, sizeof(seen));
  queryamount = 0;
  pii res;
  scanf("%d %d %d", &n, &start, &x);
  int curans = 1e9;
  res = make_pair(0, start);
  seen[start] = true;
  if (n <= 1999){
    while(res.first < x){
      if (res.second == -1) ans(-1);
      res = ask(res.second);
    }
    ans(res.first);
  }
  else{
    pii cur = ask(start);
    if (cur.first >= x) ans(cur.first);
    while(queryamount < 1000){
      int num = 1+((double)rand()/RAND_MAX * n);
      while(seen[num]) num = 1 + (rand()%(n-1));
      res = ask(num);
      if(res.first > cur.first && res.first < x){
        cur = res;
      }
    }
    res = cur;
    while(res.first < x){
      if (res.second == -1) ans(-1);
      res = ask(res.second);
    }
    ans(res.first);
  }
  return 0;
}