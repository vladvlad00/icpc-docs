/**
 * Author: Cristi
 * Description: wtf
 */
 const int SIGMA = 26;

struct Node {
	int cnt;
	Node *suff, *next[SIGMA];

	Node(int cnt = 0) : cnt(cnt) {
		suff = nullptr;
		for(int i = 0; i < SIGMA; ++i) next[i] = nullptr;
	}
};
using PNode = Node*;

void insert(PNode root, const string &s) {
	for(auto ch : s) {
		if(!root->next[ch - 'a']) root->next[ch - 'a'] = new Node;
		root = root->next[ch - 'a'];
	}
	++root->cnt;
}

void buildSuffLinks(PNode root) {
	queue<PNode> q;

	root->suff = root;
	for(int i = 0; i < SIGMA; ++i) {
		if(!root->next[i]) root->next[i] = root;
		else q.push(root->next[i]);

		root->next[i]->suff = root;
	}

	for(; !q.empty(); q.pop()) {
		PNode node = q.front();
		node->cnt += node->suff->cnt;

		for(int i = 0; i < SIGMA; ++i)
			if(node->next[i]) node->next[i]->suff = node->suff->next[i], q.push(node->next[i]);
			else node->next[i] = node->suff->next[i];
	}
}
