#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

//暴力+bfs

const int MAXN = 15;
const int INF = 0x3f3f3f3f;

char maze[MAXN][MAXN];
int dist[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
int t, n, m, k;
struct _Node{
	int x, y, time;
	_Node(){
	} 
	_Node(int _x, int _y, int _time){
		x = _x; y = _y; time = _time;
	}
}tmp[110];
int visit[MAXN][MAXN];

void INIT()
{
	for(int i = 0; i < MAXN; ++i)
		for(int j = 0; j < MAXN; ++j) maze[i][j] = '.';
}

bool isOk()
{
	int x,y;
    for(int i=0;i< k;i++)
    {
        x = tmp[i].x; y = tmp[i].y;
        if(!visit[x][y])
            return 0;
    }
    return 1;
}

int bfs(_Node n1, _Node n2)
{
	memset(visit, 0, sizeof(visit));
	queue<_Node> q1;
	q1.push(n1);
	q1.push(n2);
	visit[n1.x][n1.y] = 1; visit[n2.x][n2.y] = 1;
	int ans = 0;
	while(!q1.empty()) {
		
		_Node t = q1.front(); q1.pop();
		
		if(isOk()) return ans;
		 
		for(int i = 0; i < 4; ++i)
		{
			int dx1 = t.x + dist[i][0], dy1 = t.y + dist[i][1];
			if(maze[dx1][dy1] == '#' && !visit[dx1][dy1])
			{
				q1.push(_Node(dx1, dy1, t.time + 1));
				ans = max(ans, t.time + 1);			
				visit[dx1][dy1] = 1;
			}
		}
	}
	return INF;
}
int main()
{
	scanf("%d", &t);
	for(int cnt = 1; cnt <= t; ++cnt)
	{
		INIT();
		scanf("%d%d", &n, &m);
		int x = 0;
		getchar();
		k = 0;
		for(int i = 1; i <= n; ++i)
		{
			for(int j = 1; j <= m; ++j)
			{
				 scanf("%c", &maze[i][j]);
				 if(maze[i][j] == '#')
				 {
				 	tmp[k].x = i;
					 tmp[k].y = j;
					 tmp[k++].time = 0;
				 }
			}
			getchar();
		}
			
		int ans = INF;

		for(int i = 0; i < k; i++)
        {
            for(int j = i; j < k; j++)
            {
                ans=min(bfs(tmp[i] ,tmp[j]),ans);
            }
        }
		printf("Case %d: ", cnt);
        if(ans == INF)
            printf("-1\n");
        else
            printf("%d\n",ans);
    }
	return 0;
}