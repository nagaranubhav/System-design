#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

/*
=========================================================
ITERATOR DESIGN PATTERN IMPLEMENTATION
=========================================================

GOAL:
Different collections:
1) LinkedList
2) BinaryTree
3) Playlist

In tino ko SAME traversal interface dena:
- hasNext()
- next()

Client ko internal structure ka kuch nahi pata.

This is exactly Iterator Pattern.
*/


// =====================================================
// 1) GENERIC ITERATOR INTERFACE
// =====================================================
/*
Ye traversal contract define karta hai.

Any iterator MUST support:
1) hasNext() -> aur elements bache?
2) next()    -> next element do

Template<T> use kiya so same interface:
- int
- string
- Song
- custom objects
sab ke liye reusable ho gaya
*/
template<typename T>
class Iterator {
public:
    virtual bool hasNext() = 0;
    virtual T next() = 0;
};


/*
Iterable ka kaam:
client ko iterator provide karna.

Ye actual collection interface hai.
Har collection bolega:
"mai apna iterator bana ke de sakta hu"
*/
template<typename T>
class Iterable {
public:
    virtual Iterator<T>* getIterator() = 0;
};


// =====================================================
// 2) LINKED LIST COLLECTION
// =====================================================
/*
Ye collection bhi hai and node bhi.

Each node:
- data
- next

Since it inherits Iterable<int>,
ye client ko iterator de sakta hai.
*/
class LinkedList : public Iterable<int> {
public:
    int data;
    LinkedList* next;

    LinkedList(int value) {
        data = value;
        next = nullptr;
    }

    Iterator<int>* getIterator() override;
};


// =====================================================
// 3) BINARY TREE COLLECTION
// =====================================================
/*
Binary tree node structure.

Iterator yaha traversal complexity hide karega.

Important:
Client ko stack based inorder traversal nahi pata.
*/
class BinaryTree : public Iterable<int> {
public:
    int data;
    BinaryTree* left;
    BinaryTree* right;

    BinaryTree(int value) {
        data  = value;
        left  = nullptr;
        right = nullptr;
    }

    Iterator<int>* getIterator() override;
};


// =====================================================
// 4) DOMAIN OBJECT: SONG
// =====================================================
/*
Simple business object.

Playlist iterator custom objects bhi iterate kar sakta hai.
Ye batata hai pattern sirf primitives tak limited nahi.
*/
class Song {
public:
    string title;
    string artist;

    Song(const string& t, const string& a) {
        title  = t;
        artist = a;
    }
};


// =====================================================
// 5) PLAYLIST COLLECTION
// =====================================================
/*
Vector based collection.

Traversal hide karne ke liye iterator return karega.
*/
class Playlist : public Iterable<Song> {
public:
    vector<Song> songs;

    void addSong(const Song& s) {
        songs.push_back(s);
    }

    Iterator<Song>* getIterator() override;
};


// =====================================================
// 6) LINKED LIST ITERATOR
// =====================================================
/*
Traversal state:
current pointer

This is external iterator.
State iterator ke andar stored hai.
*/
class LinkedListIterator : public Iterator<int> {
private:
    LinkedList* current;

public:
    LinkedListIterator(LinkedList* head) {
        current = head;
    }

    /*
    Agar current valid node pe hai,
    means traversal continue kar sakte hain.
    */
    bool hasNext() override {
        return current != nullptr;
    }

    /*
    current node ka data return
    then pointer next pe move

    Example:
    1 -> 2 -> 3

    next():
    return 1
    move to 2
    */
    int next() override {
        int val = current->data;
        current = current->next;
        return val;
    }
};


// =====================================================
// 7) BINARY TREE INORDER ITERATOR
// =====================================================
/*
Sabse important iterator.

Tree traversal naturally recursive hota hai.
But iterator recursion expose nahi karega.

We simulate recursion using stack.

INORDER:
Left -> Root -> Right
*/
class BinaryTreeInorderIterator : public Iterator<int> {
private:
    stack<BinaryTree*> stk;
    BinaryTree* curr;

    /*
    Ye helper saare left nodes stack me push karta hai.

    Example tree:
          4
         /
        2
       /
      1

    stack top = 1
    */
    void pushLefts(BinaryTree* node) {
        while (node) {
            stk.push(node);
            node = node->left;
        }
    }

public:
    BinaryTreeInorderIterator(BinaryTree* root) {
        curr = root;
        pushLefts(curr);
    }

    bool hasNext() override {
        return !stk.empty();
    }

    /*
    Inorder logic:
    1) top node nikalo
    2) uska right subtree ho to uske lefts push karo
    */
    int next() override {
        BinaryTree* node = stk.top();
        stk.pop();

        int val = node->data;

        if (node->right) {
            pushLefts(node->right);
        }

        return val;
    }
};


// =====================================================
// 8) PLAYLIST ITERATOR
// =====================================================
/*
Simple index based iterator.

Traversal state:
index

Good interview point:
Same interface, different internal traversal logic.
*/
class PlaylistIterator : public Iterator<Song> {
private:
    vector<Song> vec;
    size_t index;

public:
    PlaylistIterator(vector<Song> v) {
        vec = v;
        index = 0;
    }

    bool hasNext() override {
        return index < vec.size();
    }

    Song next() override {
        return vec[index++];
    }
};


// =====================================================
// 9) ATTACHING ITERATORS TO COLLECTIONS
// =====================================================
/*
Factory style creation.

Each collection decides:
kaunsa iterator dena hai.
*/
Iterator<int>* LinkedList::getIterator() {
    return new LinkedListIterator(this);
}

Iterator<int>* BinaryTree::getIterator() {
    return new BinaryTreeInorderIterator(this);
}

Iterator<Song>* Playlist::getIterator() {
    return new PlaylistIterator(songs);
}


// =====================================================
// 10) CLIENT CODE
// =====================================================
/*
IMPORTANT:
Client ko koi traversal details nahi pata.

Same while loop:
while(iterator->hasNext())

Ye hi Iterator Pattern ka sabse bada power hai.
*/
int main() {

    // -------------------------------------------------
    // LINKED LIST
    // -------------------------------------------------
    LinkedList* list = new LinkedList(1);
    list->next = new LinkedList(2);
    list->next->next = new LinkedList(3);

    Iterator<int>* iterator1 = list->getIterator();

    cout << "LinkedList contents: ";

    while (iterator1->hasNext()) {
        cout << iterator1->next() << " ";
    }

    cout << "\n";


    // -------------------------------------------------
    // BINARY TREE
    // -------------------------------------------------
    /*
            2
           / \
          1   3

    inorder = 1 2 3
    */
    BinaryTree* root = new BinaryTree(2);
    root->left  = new BinaryTree(1);
    root->right = new BinaryTree(3);

    Iterator<int>* iterator2 = root->getIterator();

    cout << "BinaryTree inorder: ";

    while (iterator2->hasNext()) {
        cout << iterator2->next() << " ";
    }

    cout << "\n";


    // -------------------------------------------------
    // PLAYLIST
    // -------------------------------------------------
    Playlist playlist;
    playlist.addSong(Song("Admirin You", "Karan Aujla"));
    playlist.addSong(Song("Husn", "Anuv Jain"));

    Iterator<Song>* iterator3 = playlist.getIterator();

    cout << "Playlist songs:\n";

    while (iterator3->hasNext()) {
        Song s = iterator3->next();
        cout << "  " << s.title << " by " << s.artist << "\n";
    }


    // -------------------------------------------------
    // CLEANUP
    // -------------------------------------------------
    delete list->next->next;
    delete list->next;
    delete list;

    delete root->left;
    delete root->right;
    delete root;

    return 0;
}

/*
=========================================================
BIGGEST LEARNING FROM THIS CODE
=========================================================

SAME CLIENT CODE:
while(iterator->hasNext())

WORKS FOR:
- LinkedList
- BinaryTree
- Playlist

WITHOUT changing traversal logic.

That is the soul of Iterator Pattern.
=========================================================
*/