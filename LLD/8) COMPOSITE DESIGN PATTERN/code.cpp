# 💻 COMPOSITE PATTERN — CODE WITH SUPER DETAILED COMMENTS

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

//////////////////////////////////////////////////////////////
// 🧩 1. COMPONENT (Base Interface)
//
// Ye sabse important part hai.
// Ye define karta hai ki File aur Folder dono me kya common hoga.
//
// Interview tip:
// "We define a common interface so client treats all uniformly"
//////////////////////////////////////////////////////////////
class FileSystemItem {
public:
virtual ~FileSystemItem() {}

```
// List items (like 'ls' command)
virtual void ls(int indent = 0) = 0;

// Recursively open everything
virtual void openAll(int indent = 0) = 0;

// Get size (important recursive case)
virtual int getSize() = 0;

// Navigate to child folder
virtual FileSystemItem* cd(const string& name) = 0;

// Metadata
virtual string getName() = 0;
virtual bool isFolder() = 0;
```

};

//////////////////////////////////////////////////////////////
// 🌿 2. LEAF NODE → FILE
//
// Important:
// - No children
// - Direct behavior
//////////////////////////////////////////////////////////////
class File : public FileSystemItem {
string name;
int size;

public:
File(const string& n, int s) {
name = n;
size = s;
}

```
// Just print itself
void ls(int indent = 0) override {
    cout << string(indent, ' ') << name << "\n";
}

// Same behavior
void openAll(int indent = 0) override {
    cout << string(indent, ' ') << name << "\n";
}

// Direct return (base case of recursion)
int getSize() override {
    return size;
}

// File ke andar cd nahi hota
FileSystemItem* cd(const string&) override {
    return nullptr;
}

string getName() override {
    return name;
}

bool isFolder() override {
    return false;
}
```

};

//////////////////////////////////////////////////////////////
// 🌳 3. COMPOSITE NODE → FOLDER
//
// Important:
// - Children store karta hai
// - Recursive operations yahi hoti hain
//////////////////////////////////////////////////////////////
class Folder : public FileSystemItem {
string name;

```
// Composite ka heart → list of children
vector<FileSystemItem*> children;
```

public:
Folder(const string& n) {
name = n;
}

```
// Destructor (VERY IMPORTANT — memory cleanup)
~Folder() {
    for (auto c : children) delete c;
}

// Add child (leaf ya composite dono ho sakte hain)
void add(FileSystemItem* item) {
    children.push_back(item);
}

//////////////////////////////////////////////////////////
// ls() → list current folder contents
//////////////////////////////////////////////////////////
void ls(int indent = 0) override {
    for (auto child : children) {
        if (child->isFolder()) {
            cout << string(indent, ' ') << "+ " << child->getName() << "\n";
        } else {
            cout << string(indent, ' ') << child->getName() << "\n";
        }
    }
}

//////////////////////////////////////////////////////////
// openAll() → RECURSIVE CALL (CORE LOGIC)
//////////////////////////////////////////////////////////
void openAll(int indent = 0) override {
    cout << string(indent, ' ') << "+ " << name << "\n";

    // 🔥 Recursive traversal
    for (auto child : children) {
        child->openAll(indent + 4);
    }
}

//////////////////////////////////////////////////////////
// getSize() → TREE SUM (classic recursion)
//////////////////////////////////////////////////////////
int getSize() override {
    int total = 0;

    for (auto child : children) {
        total += child->getSize();  // 🔥 recursion
    }

    return total;
}

//////////////////////////////////////////////////////////
// cd() → navigate to child folder
//////////////////////////////////////////////////////////
FileSystemItem* cd(const string& target) override {
    for (auto child : children) {
        if (child->isFolder() && child->getName() == target) {
            return child;
        }
    }
    return nullptr;
}

string getName() override {
    return name;
}

bool isFolder() override {
    return true;
}
```

};

//////////////////////////////////////////////////////////////
// 🚀 4. MAIN FUNCTION (Driver Code)
//////////////////////////////////////////////////////////////
int main() {

```
//////////////////////////////////////////////////////////
// 🌳 BUILD FILE SYSTEM TREE
//////////////////////////////////////////////////////////

Folder* root = new Folder("root");

// Files in root
root->add(new File("file1.txt", 1));
root->add(new File("file2.txt", 1));

// docs folder
Folder* docs = new Folder("docs");
docs->add(new File("resume.pdf", 1));
docs->add(new File("notes.txt", 1));
root->add(docs);

// images folder
Folder* images = new Folder("images");
images->add(new File("photo.jpg", 1));
root->add(images);

//////////////////////////////////////////////////////////
// 🧪 OPERATIONS
//////////////////////////////////////////////////////////

// List root contents
root->ls();

// List docs contents
docs->ls();

// Recursive print (IMPORTANT)
root->openAll();

// cd into docs
FileSystemItem* cwd = root->cd("docs");

if (cwd != nullptr) {
    cwd->ls();
} else {
    cout << "\n Could not cd into docs \n";
}

// Total size
cout << root->getSize();

//////////////////////////////////////////////////////////
// 🧹 CLEANUP
//////////////////////////////////////////////////////////
delete root;

return 0;
```

}

---

## 🧠 DRY RUN (Step-by-step)

Tree structure:

root
├── file1.txt (1)
├── file2.txt (1)
├── docs
│    ├── resume.pdf (1)
│    ├── notes.txt (1)
└── images
└── photo.jpg (1)

---

👉 root->ls()

file1.txt
file2.txt

* docs
* images

---

👉 root->openAll()

* root
  file1.txt
  file2.txt

  * docs
    resume.pdf
    notes.txt
  * images
    photo.jpg

---

👉 root->getSize()

= 1 + 1 + (1+1) + (1)
= 5

---

## ⏱️ COMPLEXITY

Time: O(N)
Space: O(H) recursion stack

---

## 🔥 FINAL INTERVIEW GOLD LINE

"This is a classic Composite Pattern where Folder acts as a composite node and File as a leaf node. Operations like getSize and openAll are implemented recursively, allowing uniform treatment of both files and folders."

---
