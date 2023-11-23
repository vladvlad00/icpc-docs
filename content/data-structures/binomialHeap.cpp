/**
 * Author: Cristi
 * Description: wtf
 */
const int INF = 2000000001;
const int NMAX = 101;
 
struct Node {
    int key, degree;
    Node *child, *sibling, *parent;
};
 
Node* newNode( int val ){
    Node* temp = new Node;
    temp -> key = val;
    temp -> degree = 0;
    temp -> child = temp -> sibling = temp -> parent = NULL;
    return temp;
}
 
class BinomialHeap{
 
    list < Node* > H;
 
    list < Node* > :: iterator get_root(){
 
        list < Node* > :: iterator it, it_max;
        Node* vmax = newNode( -INF );
 
        for( it = H.begin(); it != H.end(); ++it )
            if( (*it) -> key > vmax -> key ){
                vmax = *it;
                it_max = it;
            }
 
        return it_max;
    }
 
    void delete_root( Node* tree, BinomialHeap& heap ){
 
        if( tree -> degree == 0 ){
            delete tree;
            return;
        }
 
        Node* temp = tree;
 
        tree -> child -> parent = NULL;
        heap.H.push_front( tree -> child );
 
        tree = tree -> child;
        while( tree -> sibling ){
            tree -> sibling -> parent = NULL;
            heap.H.push_front( tree -> sibling );
            tree = tree -> sibling;
        }
        delete temp;
    }
 
    void merge_tree( Node* tree1, Node* tree2 ){
 
        if( tree1 -> key < tree2 -> key )
            swap ( *tree1, *tree2 );
 
        tree2 -> sibling = tree1 -> child;
        tree2 -> parent = tree1;
        tree1 -> child = tree2;
        tree1 -> degree++;
 
    }
 
    void adjust(){
 
        if( H.size() <= 1 ) return;
 
        list < Node* > :: iterator prev;
        list < Node* > :: iterator curr;
        list < Node* > :: iterator next;
        list < Node* > :: iterator temp;
 
        prev = curr = H.begin();
        curr++;
        next = curr;
        next++;
 
        while( curr != H.end() ){
 
            while ( ( next == H.end() || (*next) -> degree > (*curr) -> degree ) && curr != H.end() && (*prev) -> degree == (*curr) -> degree ){
 
                merge_tree( *curr, *prev );
 
                temp = prev;
 
                if( prev == H.begin() ){
                    prev++;
                    curr++;
                    if( next != H.end() )
                        next++;
                }
                else prev--;
 
                H.erase( temp );
 
            }
 
            prev++;
            if( curr != H.end() ) curr++;
            if( next != H.end() ) next++;
        }
    }
public:
 
    int top(){
        return (*get_root()) -> key;
    }
 
    void push( int val ){
 
        Node *tree = newNode( val );
        H.push_front( tree );
        adjust();
    }
 
    void heap_union( BinomialHeap& heap2){
 
        list < Node* > :: iterator it1 = H.begin();
        list < Node* > :: iterator it2 = heap2.H.begin();
 
        list < Node* > new_heap;
 
        while( it1 != H.end() && it2 != heap2.H.end() ){
            if( (*it1) -> degree <= (*it2) -> degree ){
                new_heap.push_back( *it1 );
                it1++;
            }
            else{
                new_heap.push_back( *it2 );
                it2++;
            }
        }
 
        while( it1 != H.end() ){
            new_heap.push_back( *it1 );
            it1++;
        }
 
        while( it2 != heap2.H.end() ){
            new_heap.push_back( *it2 );
            it2++;
        }
 
        heap2.H.clear();
 
        H = new_heap;
        adjust();
    }
 
    void pop(){
 
        list < Node* > :: iterator root = get_root();
 
        BinomialHeap new_heap;
        delete_root( (*root), new_heap );
 
        H.erase( root );
 
        heap_union( new_heap );
 
    }
};
 
int N, M;
BinomialHeap Heap[NMAX];
 
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
