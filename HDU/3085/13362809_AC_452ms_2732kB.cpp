#include <iostream>    
#include <algorithm>    
#include <cstdio>    
#include <cstring>    
#include <string>    
#include <queue>    
using namespace std;    
char str[880][880];    
int t, n, m, step;    
int f[4][2] = {1,0,-1,0,0,1,0,-1};    
struct node    
{    
    int x, y;    
}gg, mm, zz[2];    
queue<node>q[2], qt;    
bool isok(node t)    
{     
    if(t.x<1 || t.x>n || t.y<1 || t.y>m) return false;  
    for(int i=0; i<2; i++)    
    {    
        if(abs(t.x-zz[i].x)+abs(t.y-zz[i].y)<=2*step || str[t.x][t.y]=='X' || str[t.x][t.y]=='\0') return false;    
    }    
    return true;    
}    
bool bfs(int mark, int num, char start, char endd)    
{    
    node a, b;    
    qt=q[mark];    
    for(int i=0; i<num; i++)    
    {    
        while(!qt.empty())    
        {    
            a=qt.front(), qt.pop(), q[mark].pop();    
            if(!isok(a)) continue;//鬼先走，每增加一步，先判断鬼能不能把人吃掉     
            for(int i=0; i<4; i++)    
            {    
                b = a;    
                b.x+=f[i][0], b.y+=f[i][1];    
                if(!isok(b)||str[b.x][b.y]==start) continue;    
                if(str[b.x][b.y]==endd) return true;//其中一个人到达了另一个人曾经到达的地方，两人相遇了     
                str[b.x][b.y]=start;//标记已经走过的地方     
                q[mark].push(b);    
            }    
        }    
        qt=q[mark];    
    }    
    return false;    
}    
int solve()    
{    
    step=0;    
    while(!q[0].empty()) q[0].pop();    
    while(!q[1].empty()) q[1].pop();    
    while(!qt.empty()) qt.pop();    
    q[0].push(mm), q[1].push(gg);    
    while(!q[0].empty() && !q[1].empty())    
    {    
        step++;    
        bool flag1 = bfs(0,3,'M','G');    
        bool flag2 = bfs(1,1,'G','M');    
        if(flag1||flag2) return step;    
    }    
    return -1;    
}    
int main()    
{    
    scanf("%d", &t);    
    while(t--)    
    {    
        cin>>n>>m;    
        memset(str,'X',sizeof(str));    
        for(int k=0,i=1; i<=n; i++)    
        {    
            scanf("%s", str[i]+1);    
            for(int j=1; j<=m; j++)    
            {    
                if(str[i][j]=='M') mm.x=i, mm.y=j;    
                if(str[i][j]=='G') gg.x=i, gg.y=j;    
                if(str[i][j]=='Z') zz[k].x=i, zz[k].y=j, k++;    
            }    
        }    
        printf("%d\n", solve());    
    }    
    return 0;    
}     