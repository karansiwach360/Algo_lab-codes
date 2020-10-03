#include<bits/stdc++.h>
using namespace std;
int z;

void dfs(vector< vector<int> > &g,vector<int> &vis,vector<int> &par,vector<int> &low,int c,vector<int> &ans,vector<int> &ch,vector<int> &temp)
{
    vis[c]=1;
    low[c]=z;
    temp[c]=z++;
    for (int i=0;i<g[c].size();i++)
    {
        if(par[c]==g[c][i]) continue;
        else if(!vis[g[c][i]])
        {
            ch[c]++;
            par[g[c][i]]=c;
            dfs(g,vis,par,low,g[c][i],ans,ch,temp);
            low[c]=min(low[c],low[g[c][i]]);
            if(low[g[c][i]]>=temp[c]) ans[c]=1;
        }
        else low[c]=min(low[c],temp[g[c][i]]);
    }
}
int main()
{
    int n,m;
    cout<<"Enter the number of vertexes in the graph: ";
    cin>>n;
    cout<<endl;
    cout<<"Enter the number of edges in the graph: ";
    cin>>m;
    cout<<endl;
    vector< vector<int> > g(n+1);
    for(int i=0;i<m;i++)
    {
        int x,y;
        cin>>x>>y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    vector<int> vis(n+1,0),par(n+1,0),low(n+1,0),ans(n+1,0),ch(n+1,0),temp(n+1,0);
    for (int i=0;i<n;i++)
    {
        if(!vis[i+1])
        {
            z=0;
            par[i+1]=-1;
            dfs(g,vis,par,low,i+1,ans,ch,temp);
            if(ch[i+1]>1) ans[i+1]=1;
            else ans[i+1]=0;
        }
    }
    for(int i=0;i<n;i++) if(ans[i+1]) cout<<i+1<<" ";
    return 0;
}
/*
8 9
0 1
0 2
1 2
2 3
3 4
4 5
4 6
5 6
5 7
*/
