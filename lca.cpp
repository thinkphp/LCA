#include <vector>
#include <cstdio>
using namespace std;
#define MAX_N 100005
#define MAX_L 20
int k, n, m;
int l[MAX_N << 1], h[MAX_N << 1],lg[MAX_N << 1], f[MAX_N];
int rmq[MAX_L][MAX_N << 2];
bool viz[MAX_N];
vector <int> g[MAX_N];
void citire()
{
	freopen("lca.in","r",stdin);
	freopen("lca.out","w",stdout);
	scanf("%d%d",&n,&m);
	int x;
	for(int i = 2; i <= n; ++i)
	{
		scanf("%d",&x);
		g[x].push_back(i);
	}
}

void df(int nod, int lev)
{
	h[++k]=nod;
	l[k]=lev; 
	viz[nod]=true;
	f[nod]=k; 
	size_t g1=g[nod].size();
	for (size_t i=0; i<g1; ++i)
	{
		if (viz[g[nod][i]])
			continue;
		df(g[nod][i],lev+1);
		h[++k]=nod;
		l[k]=lev;
	}
}

void rmq1()
{
	for(int i=2; i<=k; ++i)
		lg[i]=lg[i>>1]+1;
	for(int i=1; i<=k; ++i)
		rmq[0][i]=i;
	
	for(int i=1; (1<<i)<k; ++i)
		for(int j=1; j<=k-(1<<i); ++j)
		{
			int l1=1<<(i - 1);
			rmq[i][j]=rmq[i-1][j];
			if(l[rmq[i-1][j+l1]]<l[rmq[i][j]])
				rmq[i][j]=rmq[i-1][j+l1];
		}
}

int lca(int x, int y)
{
	int diff,l1,sol,sh;
	int a=f[x],b=f[y];
	if(a>b) swap(a,b);
	diff=b-a+1;
	l1=lg[diff];
	sol=rmq[l1][a];
	sh=diff-(1<<l1);
	if(l[sol]>l[rmq[l1][a+sh]])
		sol=rmq[l1][a+sh];
	return h[sol];
}

int main()
{
	citire();
	df(1,0);
	rmq1();
	int x,y;
	while(m--)
	{
		scanf("%d%d",&x,&y);
		printf("%d\n",lca(x,y));
	}
}
