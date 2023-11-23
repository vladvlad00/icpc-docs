/**
 * Author: Cristi
 * Description: wtf
 */
Min floww with lower bounds on edges:
Add two new vertices s', t'
Add edge from s' to v with capacity sum{u}(lower_bound(u->v))
Add edge from v to t' with capacity sum{w}(lower_bound(v->w))
Add edge from v to u with capacity cap(v->u) - lower_bound(v->u)
Add edge from s to t with capacity INF
After finding a feasible flow, run Dinic again to find a mximum feasible flow, ensuring the flow is feasible at every step
i.e. do not substract flow from an edge such that the new value is less than the lower bound
