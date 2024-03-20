/**
 * Author: Matei
 * Description: When provided a B update (add B), we just push it to the top of S.
 * When provided an A
 * update: If S already had A on top, we just pop. Otherwise, we begin the following process (which I'll call "fixing"): 
 * pop from S and save all the elements we popped, until we popped an equal amount of A's and B's, 
 * or until no A's remain in the stack; empty stack 
 * or only B's remain (we can keep an index of this position in the stack, which will only increase). 
 * Then, push back all the elements we popped, where we first push all B's, 
 * then all A's (we use commutativity here).
 * Since the top of S had a B, and we were asked to pop an existing A, after fixing, 
 * the topmost element will be an A which we pop.
 */
struct stack_upd
{
    int x, y;
 
    stack_upd(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
};
 
struct stack_dsu
{
    stack<stack_upd> upd;
 
    vector<int> par;
    vector<int> sz;
 
    void init(int n)
    {
        par.resize(n+1);
        sz.resize(n+1);
 
        for(int i=1;i<=n;i++)
        {
            par[i] = i;
            sz[i] = 1;
        }
    }
 
    int anc(int x)
    {
        if(par[x] == x)
            return x;
        return anc(par[x]);
    }
 
    void fmerge(int x, int y)
    {
        x = anc(x);
        y = anc(y);
 
        if(sz[x] < sz[y])
            swap(x, y);
 
        upd.push( stack_upd(x, y) );
 
        if(x != y)
        {
            par[y] = x;
            sz[x] += sz[y];
        }
    }
 
    void pop()
    {
        int x = upd.top().x;
        int y = upd.top().y;
        upd.pop();
 
        if(x != y)
        {
            par[y] = y;
            sz[x] -= sz[y];
        }
    }
};
 
struct queue_upd
{
    char type; ///A sau B, A -> LIFO, B-> FIFO
    int x, y;
 
    queue_upd(int x, int y, char type = 'B')
    {
        this->type = type;
        this->x = x;
        this->y = y;
    }
};
 
struct queue_dsu
{
    int nrA, nrB;
    vector<queue_upd> upd;
    stack_dsu ds;
 
    void init(int n)
    {
        nrA = nrB = 0;
        ds.init(n);
    }
 
    void fmerge(int x, int y)
    {
        nrB++;
 
        upd.push_back(queue_upd(x, y));
        ds.fmerge(x, y);
    }
 
    void reverse_updates()
    {
        for(int i=0; i<(int)upd.size(); i++)
            ds.pop();
 
        reverse(upd.begin(), upd.end());
 
        for(auto &it : upd)
        {
            it.type = 'A';
            ds.fmerge(it.x, it.y);
        }
 
        nrA = (int)upd.size();
        nrB = 0;
    }
 
    void fix()
    {
        vector< queue_upd > auxA;
        vector< queue_upd > auxB;
 
        while( !upd.empty() )
        {
            queue_upd it = upd.back();
 
            ds.pop();
            upd.pop_back();
 
            if( it.type == 'A' )
                auxA.push_back(it);
            else
                auxB.push_back(it);
 
            if(!auxA.empty() && auxA.size() == auxB.size() )
                break;
 
            if( (int)auxA.size() == nrA )
                break;
        }
 
        reverse(auxA.begin(), auxA.end());
        reverse(auxB.begin(), auxB.end());
 
        for(auto it : auxB)
        {
            ds.fmerge(it.x, it.y);
            upd.push_back(it);
        }
 
        for(auto it : auxA)
        {
            ds.fmerge(it.x, it.y);
            upd.push_back(it);
        }
    }
 
    void pop()
    {
        if(upd.back().type != 'A')
        {
            if(nrA)
                fix();
            else
                reverse_updates();
        }
 
        ds.pop();
        upd.pop_back();
        nrA --;
    }
};
