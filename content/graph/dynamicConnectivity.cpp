///trebuie schimbata ca functia de solve, pt dynamic connectivity normal

#include <bits/stdc++.h>
 
using namespace std;
 
struct stack_dsu
{
    int par[100005];
    int sz[100005];
 
    stack< pair<int, int> > upd;
 
    void init(int n)
    {
        for(int i=0;i<n;i++)
        {
            par[i] = i;
            sz[i] = 1;
        }
    }
 
    int anc(int p)
    {
        if(par[p] == p)
            return p;
        return anc(par[p]);
    }
 
    void fmerge(int x, int y)
    {
        x = anc(x);
        y = anc(y);
 
        if(sz[x] < sz[y])
            swap(x, y);
 
        upd.push({x, y});
 
        if(x != y)
        {
            par[y] = x;
            sz[x] += sz[y];
        }
    }
 
    void pop()
    {
        int x = upd.top().first;
        int y = upd.top().second;
        upd.pop();
 
        if(x == y)
            return;
 
        par[y] = y;
        sz[x] -= sz[y];
    }
};
 
struct edge
{
    int x, y, val;
 
    edge(int x, int y, int val)
    {
        this->x = x;
        this->y = y;
        this->val = val;
    }
};
 
int n, q;
 
map< pair<int, int>, pair<int, int> > m;
 
stack_dsu dsu[12];
vector< vector<edge> > seg;
 
pair<int, int> qv[100005];
int ans[100005];
 
 
void upd(int stt, int drt, int st, int dr, int p, edge val)
{
    //cout<<st<<' '<<dr<<'\n';
 
    if(stt == st && drt == dr)
    {
        seg[p].push_back(val);
        return;
    }
 
    int mij = (st+dr)/2;
 
    if(drt <= mij)
        upd(stt, drt, st, mij, 2*p, val);
 
    else if(stt > mij)
        upd(stt, drt, mij+1, dr, 2*p+1, val);
 
    else
    {
        upd(stt, mij, st, mij, 2*p, val);
        upd(mij+1, drt, mij+1, dr, 2*p+1, val);
    }
}
 
void solve(int st, int dr, int p)
{
    for(auto it : seg[p])
    {
        for(int i=it.val; i<10; i++)
            dsu[i].fmerge(it.x, it.y);
    }
 
    if(st == dr)
    {
        if(qv[st] != make_pair(0, 0))
        {
            int x = qv[st].first;
            int y = qv[st].second;
 
            for(int i=0; i<10; i++)
            {
                if(dsu[i].anc(x) == dsu[i].anc(y))
                {
                    ans[st] = i;
                    break;
                }
            }
        }
    }
    else
    {
        int mij = (st+dr)/2;
 
        solve(st, mij, 2*p);
        solve(mij+1, dr, 2*p+1);
    }
 
    for(auto it : seg[p])
    {
        for(int i=it.val; i<10; i++)
            dsu[i].pop();
    }
}
