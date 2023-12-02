///de testat
#include <bits/stdc++.h>

using namespace std;

struct pct
{
    long long x, y;

    pct()
    {
        x = y = 0;
    }

    pct(long long x, long long y)
    {
        this->x = x;
        this->y = y;
    }

    pct operator-(pct b)
    {
        pct ans = pct(x - b.x, y - b.y);
        return ans;
    }
};

long long det(pct a, pct b, pct c)
{
    long long ans = a.x * b.y + b.x * c.y + c.x * a.y;
    ans -= a.x * c.y + b.x * a.y + c.x * b.y;
    return ans;
}

bool compPolar(pair<pct, int> a, pair<pct, int> b)
{
    pct pctA = a.first;
    pct pctB = b.first;

    return det(pct(0, 0), pctA, pctB) > 0;
}

vector<pct> convexHull(vector<pct> v)
{
    int leftPoint = 0;
    for(int i=1; i<(int)v.size(); i++)
    {
        if(v[i].x < v[leftPoint].x)
            leftPoint = i;

        if(v[i].x == v[leftPoint].x && v[i].y < v[leftPoint].y)
            leftPoint = i;
    }

    //cout<<"left point is ";
    //cout<<v[leftPoint].x<<' '<<v[leftPoint].y<<'\n';

    vector<pair<pct, int>> aux;

    for(int i=0;i<(int)v.size();i++)
    {
        if(i == leftPoint)
            continue;

        aux.push_back({v[i]-v[leftPoint], i});
    }

    sort(aux.begin(), aux.end(), compPolar);

    /*
    cout<<"ord is\n";
    for(auto it : aux)
        cout<<v[it.second].x<<' '<<v[it.second].y<<'\n';
    */

    vector<pct> ans;
    ans.push_back(v[leftPoint]);

    for(auto it : aux)
    {
        auto newPct = v[it.second];

        while((int)ans.size() >= 2)
        {
            if(det(ans[ans.size()-2], ans.back(), newPct) < 0)
                ans.pop_back();
            else
                break;
        }

        ans.push_back(newPct);
    }

    return ans;
}
