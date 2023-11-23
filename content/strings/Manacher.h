/**
 * Author: Cristi
 * Description: wtf
 */
int odd[N], even[N];
/*
 * [i - odd[i], i + odd[i]] - longest palindrome with center in i
 * [i - even[i], i + even[i] - 1] - longest palindrome with center in (i-1, i)
 */

void manacher(const string &s) {
	int l = 0, r = -1, n = s.length();
	for(int i = 0; i < n; ++i) {
		odd[i] = (i > r ? 1 : min(odd[l + r - i], r - i));
		while(i - odd[i] >= 0 && i + odd[i] < n && s[i - odd[i]] == s[i + odd[i]]) ++odd[i];
		--odd[i];

		if(i + odd[i] > r) l = i - odd[i], r = i + odd[i];
	}

	l = 0; r = -1;
	for(int i = 0; i < n; ++i) {
		even[i] = (i > r ? 1 : min(even[l + r - i + 1], r - i));
		while(i - even[i] >= 0 && i + even[i] - 1 < n && s[i - even[i]] == s[i + even[i] - 1]) ++even[i];
		--even[i];

		if(i + even[i] - 1 > r) l = i - even[i], r = i + even[i] - 1;
	}
}

