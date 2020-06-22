//
//  main.cpp
//  Binary Tree
//
//  Created by Ira Xavier Porchia on 5/23/20.
//  Copyright © 2020 Ira Xavier Porchia. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

const int MAX = 100;
class Binary;
class tree;

template <class T>
class Queue{
private:
    int _head;
    int _tail;
public:
    T _data[MAX];

    Queue():
    _head(0), _tail(0){}

    bool isEmpty(){
        return _tail == _head;
    }

    bool isFull(){
        return (_tail + 1) % MAX == _head;
    }

    T dequeue(){
        if (isEmpty()) {
            return 0;
        }
        T i = _data[_head];
        _head = (_head + 1) % MAX;
        return i;
    }

    void enqueue(tree* value){
        if (isFull()) {
            return;
        }
        _data[_tail] = value;
        _tail = (_tail + 1) % MAX;
    }

    T head(){
        return _data[_head];
    }

};

class Binary;

struct Trunk
{
    Trunk *prev;
    string str;

    Trunk(Trunk *prev, string str)
    {
        this->prev = prev;
        this->str = str;
    }
};

// Helper function to print branches of the binary tree
void showTrunks(Trunk *p)
{
    if (p == nullptr)
        return;

    showTrunks(p->prev);

    cout << p->str;
}

class tree{
    friend class Binary;
private:
    int _data;
    tree *_left;
    tree *_right;
public:
    tree(int data):
    _data(data), _left(nullptr), _right(nullptr){}

    void clear();

    void setRight(Binary &subTree);

    void setLeft(Binary &subTree);
    
    void remLeaves();
    
    void search(int data);
    
    void preOrder();
    
    void inOrder();
    
    void postOrder();
    
    void levelOrder(tree *root);

};

class Binary{
    friend class tree;
private:
    tree *_root;
public:
    Binary():
    _root(nullptr){}

    ~Binary(){
        clear();
    }

    void clear();
    
    bool isEmpty();

    void insertRoot(int data);

    void setRight(Binary &subTree);

    void setLeft(Binary &subTree);
    
    tree *root();
    
    void printTree(tree *root, Trunk *prev, bool isLeft);
    
    int remRoot();
    
    void remLeaves();
    
    void search(int data);
    
    void preOrder();
    
    void inOrder();
    
    void postOrder();
    
    void levelOrder(tree *root);

};
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    bool Binary::isEmpty(){
        return _root == nullptr;
    }
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    void Binary::insertRoot(int data){
           if(_root != nullptr){
               cout << "Error." << endl;
               return;
           }
           _root = new tree(data);
       }
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    void Binary::clear(){
        if(_root != nullptr){
            _root->clear();
            _root = nullptr;
        }
    }

void tree::clear(){
        if (_left != nullptr) {
            delete _left;
            _left = nullptr;
        }
        if (_right != nullptr) {
            delete _right;
            _right = nullptr;
        }
        delete this;
    }
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    void Binary::setRight(Binary &subTree){
        if (_root == nullptr) {
            cout << "Error." << endl;
            return;
        }
        _root->setRight(subTree);
    }

    void tree::setRight(Binary &subTree){
        if (_right != nullptr) {
            _right->clear();
        }
        _right = subTree._root;
        subTree._root = nullptr;
    }
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    void Binary::setLeft(Binary &subTree){
        if (_root == nullptr) {
            cout << "Error." << endl;
            return;
        }
        _root->setLeft(subTree);
    }

    void tree::setLeft(Binary &subTree){
        if (_left != nullptr) {
            _left->clear();
        }
        _left = subTree._root;
        subTree._root = nullptr;
    }
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
tree *Binary::root(){
    return _root;
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    void Binary::preOrder(){
        if(_root != nullptr){
        _root->preOrder();
        }
    }

    void tree::preOrder(){
        cout << _data << " ";
        if(_left != nullptr){
            _left->preOrder();
        }
        if(_right != nullptr){
            _right->preOrder();
        }
    }

    void Binary::inOrder(){
        if(_root != nullptr){
        _root->inOrder();
        }
    }

    void tree::inOrder(){
        if(_left != nullptr){
            _left->inOrder();
        }
        cout << _data << " ";
        if(_right != nullptr){
            _right->inOrder();
        }
    }

    void Binary::postOrder(){
        if(_root != nullptr){
        _root->postOrder();
        }
    }

    void tree::postOrder(){
        if(_left != nullptr){
            _left->postOrder();
        }
        if(_right != nullptr){
            _right->postOrder();
        }
        cout << _data << " ";
    }

    void Binary::levelOrder(tree *root){
        if(_root != nullptr){
            _root->levelOrder(_root);
        }
    }

    void tree::levelOrder(tree *root){
        Queue<tree*> queue;
        queue.enqueue(root);
        while(!queue.isEmpty()){
            tree *presentNode = queue.dequeue();
            cout << presentNode->_data << " ";
            if(presentNode->_left != nullptr){
                queue.enqueue(presentNode->_left);
            }
            if(presentNode->_right != nullptr){
                queue.enqueue(presentNode->_right);
            }
        }
    }

// Recursive function to print binary tree
// It uses inorder traversal
void Binary::printTree(tree *root, Trunk *prev, bool isLeft)
{
    if (root == nullptr)
        return;

    string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);

    printTree(root->_left, trunk, true);

    if (!prev)
        trunk->str = "---";
    else if (isLeft)
    {
        trunk->str = ".---";
        prev_str = "   |";
    }
    else
    {
        trunk->str = "`---";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    cout << root->_data << endl;

    if (prev)
        prev->str = prev_str;
    trunk->str = "   |";

    printTree(root->_right, trunk, false);
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
int Binary::remRoot(){
    int temp = _root->_data;
    if(_root == nullptr || (_root->_left != nullptr && _root->_right != nullptr)){
        cout << "Error" << endl;
        return -1;
    }
    if (_root->_left != nullptr) {
        _root = _root->_left;
    } else {
        _root = _root->_right;
    }
    return temp;
}

void Binary::remLeaves(){
    if (_root == nullptr){
           // do nothing
       }
       else if (_root->_left == nullptr && _root->_right == nullptr) {
           delete this;
           _root = nullptr;
       }
       else {
           _root->remLeaves();
       }
}

void tree::remLeaves(){
    if (_left != nullptr) {
        if (_left->_left == nullptr && _left->_right == nullptr) {
            delete _left;
            _left = nullptr;
        }
        else {
            _left->remLeaves();
            }
        }
    if (_right != nullptr) {
        if (_right->_left == nullptr && _right->_right == nullptr) {
            delete _right;
            _right = nullptr;
        }
        else {
            _right->remLeaves();
            }
        }
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void Binary::search(int data){
    if(_root == nullptr){
        cout << "Didn't find the value." << endl << endl;
        return;
    }
    
    return _root->search(data);
}

void tree::search(int data){
    if(_data == data){
        cout << "Found value: " << data << endl << endl;
        return;
    }
    if(_left != nullptr){
        _left->search(data);
    }
    if(_right != nullptr){
        _right->search(data);
    }
}

int main(int argc, const char * argv[]) {
    Binary tree1;
    Binary tree2;
    Binary tree3;
    Binary tree4;
    Binary tree5;
    Binary tree6;
    Binary tree7;
    tree1.insertRoot(10);
    tree2.insertRoot(20);
    tree3.insertRoot(30);
    tree2.setLeft(tree1);
    tree2.setRight(tree3);
    tree4.insertRoot(40);
    tree4.setRight(tree2);
    tree5.insertRoot(50);
    tree6.insertRoot(60);
    tree7.insertRoot(70);
    tree5.setLeft(tree6);
    tree5.setRight(tree7);
    tree4.setLeft(tree5);
    tree4.preOrder();
    cout << endl << endl;
    tree4.inOrder();
    cout << endl << endl;
    tree4.postOrder();
    cout << endl << endl;
    tree4.levelOrder(tree4.root());
     cout << endl << endl;
    tree4.printTree(tree4.root(), nullptr, false);
    cout << endl << endl;
    tree4.search(50);
    tree4.search(40);
    cout << endl << endl;
    tree4.remLeaves();
    tree4.printTree(tree4.root(), nullptr, false);
    tree4.search(50);
    tree4.search(100);
    return 0;
}

