/**
 * Author: Cristi
 * Description: wtf
 */
const int NMAX = 101;
const int INF = 2000000001;
 
ifstream fin("mergeheap.in");
ofstream fout("mergeheap.out");
 
struct Node{
    int key;
    Node *child, *sibling;
 
    Node( int x ) : key( x ), child( NULL ), sibling( NULL ) {}
};
 
class PairingHeap{
 
    Node *root;
 
    Node* merge_heap( Node* H1, Node* H2 ){
 
        if( H1 == NULL ){
            H1 = H2;
            return H1;
        }
        if( H2 == NULL ) return H1;
 
        if( H1 -> key < H2 -> key )
            swap( H1, H2 );
 
        H2 -> sibling = H1 -> child;
        H1 -> child = H2;
 
        return H1;
    }
 
    Node* two_pass_merge( Node *_Node ){
 
        if( _Node == NULL || _Node -> sibling == NULL )
            return _Node;
 
        Node *heap_1, *heap_2, *next_pair;
 
        heap_1 = _Node;
        heap_2 = _Node -> sibling;
        next_pair = _Node -> sibling -> sibling;
 
        heap_1 -> sibling = heap_2 -> sibling = NULL;
 
        return merge_heap( merge_heap( heap_1, heap_2 ), two_pass_merge( next_pair ) );
    }
public:
 
    PairingHeap() : root( NULL ) {}
 
    PairingHeap( int _key ){
        root = new Node( _key );
    }
 
    PairingHeap( Node* _Node ) : root( _Node ) {}
 
    int top(){
        return root -> key;
    }
 
    void merge_heap( PairingHeap H ){
 
        if( root == NULL ){
            root = H.root;
            return;
        }
        if( H.root == NULL ) return;
 
        if( root -> key < H.root -> key )
            swap( root, H.root );
 
        H.root -> sibling = root -> child;
        root -> child = H.root;
        H.root = NULL;
    }
 
    void push( int _key ){
        merge_heap( PairingHeap( _key ) );
    }
 
    void pop(){
 
        Node* temp = root;
        root = two_pass_merge( root -> child );
 
        delete temp;
    }
 
    void heap_union( PairingHeap &H ){
        merge_heap( H );
        H.root = NULL;
    }
};
 
int N, M;
 
PairingHeap Heap[NMAX];
 
int main()
{
 
    fin >> N >> M;
 
    int task, h, x, h1, h2;
    for( int i = 1; i <= M; ++i ){
 
        fin >> task;
 
        if( task == 1 ){
            fin >> h >> x;
 
            Heap[h].push( x );
        }
        if( task == 2 ){
            fin >> h;
 
            fout << Heap[h].top() << '\n';
            Heap[h].pop();
        }
        if( task == 3 ){
            fin >> h1 >> h2;
 
            Heap[h1].heap_union( Heap[h2] );
        }
    }
 
    return 0;
}
