/**
 * Author: Cristi
 * Description: wtf
 */
const int N = 2000010;
const int A = 26;

int k, last;
int len[N], link[N];
int go[N][A];

void addLetter(int ch) {
	int p = last;
	last = k++;
	len[last] = len[p] + 1;

	while(!go[p][ch]) go[p][ch] = last, p = link[p];
	if(go[p][ch] == last) return void(link[last] = 0);

	int q = go[p][ch];
	if(len[q] == len[p] + 1) return void(link[last] = q);

	int cl = k++;
	memcpy(go[cl], go[q], sizeof go[q]);
	link[cl] = link[q];
	len[cl] = len[p] + 1;
	link[last] = link[q] = cl;

	while(go[p][ch] == q) go[p][ch] = cl, p = link[p];
}

