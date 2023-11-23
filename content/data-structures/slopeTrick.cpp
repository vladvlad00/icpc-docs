/**
 * Author: Cristi
 * Description: Given an array a, on operation means increase or decrease an element by one
 * 	What is the minimum number of operations to make it strictly increasing?
 *  Remove line "a -= i" for non-decreasing
 */
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n, a;

	cin >> n;

	priority_queue<int> q;

	ll ans = 0;
	for(int i = 0; i < n; ++i) {
		cin >> a;
		a -= i;

		q.push(a);
		q.push(a);

		ans += q.top() - a;

		q.pop();
	}

	cout << ans << '\n';

	return 0;
}