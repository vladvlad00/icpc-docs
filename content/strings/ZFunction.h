/**
 * Author: Cristi
 * Description: z[i] is the length of the longest string that is, at the same time, a prefix of s and a prefix of the suffix of s starting at i
 */
int z[N];

void computeZFunction(const string &s) {
	int n = s.length();
  for(int i = 0; i < n; ++i) {
    int l = -1, r = -1;
    for(int j = i + 1; j < n; ++j) {
      int k = (j > r ? 0 : min(z[j - l + i], r - j + 1));
      while(j + k < n && s[i + k] == s[j + k]) ++k;
      z[j] = k;
      if(j + k - 1 > r) l = j, r = j + k - 1;
    }
  }
}

