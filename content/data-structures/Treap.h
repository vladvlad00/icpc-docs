/**
 * Author: Cristi
 * Description: wtf
 */
struct Treap {
	int key, pri, cnt, mn, mx, s;
	Treap *l, *r;

	Treap(int key) : key(key), pri(rand()) {
		cnt = s = 1;
		mn = mx = key;
		l = r = nullptr;
	}
};
using PTreap = Treap*;

void update(PTreap node) {
	// TODO: update node considering children are correct
}

void split(PTreap node, int key, PTreap &l, PTreap &r) {
	if(!node) return void(l = r = nullptr);

	if(key < node->key) split(node->l, key, l, node->l), r = node;
	else split(node->r, key, node->r, r), l = node;

	update(node);
}

void merge(PTreap &node, PTreap l, PTreap r) {
	if(!l || !r) return void(node = (l ? l : r));

	if(l->pri < r->pri) merge(r->l, l, r->l), node = r;
	else merge(l->r, l->r, r), node = l;

	update(node);
}

bool addIfExists(PTreap node, int key) {
	if(!node) return false;
	if(node->key == key) return ++node->cnt, update(node), true;

	auto res = addIfExists(key < node->key ? node->l : node->r, key);
	update(node);
	return res;
}

void add(PTreap &node, PTreap item) {
	if(!node) return void(node = item);

	if(item->pri > node->pri) split(node, item->key, item->l, item->r), node = item;
	else add(item->key < node->key ? node->l : node->r, item);

	update(node);
}

void erase(PTreap &node, int key) {
	if(!node) return;

	if(node->key == key) {
		--node->cnt;
		if(!node->cnt) merge(node, node->l, node->r);
	} else erase(key < node->key ? node->l : node->r, key);

	if(node) update(node);
}

void print(PTreap node, string indent = "") {
	if(!node) return;
	cout << indent << ' ' << node->key << ' ' << node->cnt << '\n';
	print(node->l, indent + " ");
	print(node->r, indent + " ");
}


