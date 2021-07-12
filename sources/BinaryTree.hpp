#pragma once
#include <iostream>
#include <queue>
#include <stdexcept>
using namespace std;
namespace ariel{
template < class T> 

class BinaryTree{

struct Node{
    T value;
    Node *left;
    Node *right;
    Node(T x): value(x), left(nullptr), right(nullptr){};
};

Node* root;

Node* isfind(Node* root, const T& val)
    {

    if (root==nullptr){
    return nullptr;
    }

    if (root->value==val){
    return root;
    }

    Node* left = (isfind (root->left, val));
    if (left){
    return left;
    }

    Node* right = (isfind (root->right, val));//left?
    if (right){ 
    return right;
    }

    return nullptr;
}
public:
BinaryTree(){
    root=nullptr;
}
~BinaryTree(){
    deleteAll(root);
}
void deleteAll(Node* node){

    if (node==nullptr){
    return;
    }
    if (node->left){
    deleteAll(node->left);
    }
    if (node->right){
    deleteAll(node->right);
    }
    delete node;
}

BinaryTree<T>& add_root (T val){
   
    if (root==nullptr)
    {
    root=new Node(val);
    }
    else
    {
    root->value = val;
    }
    return *this;
}
BinaryTree<T>& add_left(const T& parent, const T& childLeft){

    Node* temp = isfind(root, parent);

    if (temp->left == 0)
    {

    temp->left = new Node(childLeft);

    }
    else {

    temp->left->value = childLeft;

    }
    return *this;
}
BinaryTree<T>& add_right(const T& parent,const T& childRight){

    Node* temp = isfind(root, parent);

    if (temp->right == 0)
    {
    temp->right = new Node(childRight);
    }
    else
    {
    temp->right->value=childRight;
    }
    return *this;
}


class iterator
 {
    protected:
        queue<Node*> q;
        Node* nodeiterator;
    public:
        iterator(){
            nodeiterator = nullptr; 
             }
        virtual void order(Node* node) = 0;
        bool operator!=(const iterator& it) const
        {
            return nodeiterator !=it.nodeiterator;
            }

        bool operator==(const iterator& it) const
        {
            return nodeiterator ==it.nodeiterator;
             }
        T& operator*() const{
            return nodeiterator->value;
        }
         T* operator->() const{
            return &(nodeiterator->value);
        }
        iterator& operator++()//prefix
        {
        if (q.empty())
            {
             nodeiterator = nullptr;
            }
        else{
                nodeiterator = q.front();
                q.pop();
            }
        return *this;
        }

/*
      iterator operator++(int){
     iterator temp= *this;
     ++(*this);
     return temp;
}*/
};
class preorder: public iterator{
    public:
    preorder (Node* node)
    {
    order(node);
    ++(*this);
    }
    void order(Node* node){
    
    if(node ==nullptr){
        return;}
    this->q.push(node);

    if (node->left){
        order (node->left);}


    if (node->right){
        order (node->right);}

    }
    };

    preorder begin_preorder(){
    return preorder(root);
    }
    preorder end_preorder(){
    return preorder(nullptr);
}
class inorder: public iterator{
    public:
    inorder (Node* node)
    {
    order(node);
    ++(*this);
    }

    void order(Node* node){
    if (node == nullptr){
        return;}

    if(node->left){
        order (node->left);}

    this->q.push(node);

    if (node->right){
        order (node->right);}
    }
    };

    inorder begin_inorder(){
    return inorder (root);
    }
    inorder end_inorder(){
    return inorder(nullptr);
}
class postorder: public iterator{
    public:
    postorder (Node* node)
    {
    order(node);
    ++(*this);

    }
    void order(Node* node){
    
    if (node ==nullptr){
    return;}
    if(node->left){
    order (node->left);
    }
    if (node->right){
    order (node->right);
    }
    this->q.push(node);
    }
    }; 
    postorder begin_postorder(){
    return postorder(root);
    }
    postorder end_postorder(){
    return postorder(nullptr);
}
inorder begin(){
    return inorder (root);
}
inorder end(){
    return inorder (nullptr);
}
friend ostream& operator<<(ostream& os,BinaryTree<T> &tree){

    os << "tree\n";
    for(auto it=tree.begin_postorder(); it!=tree.end_postorder(); ++it){
        os<< (*it) <<" ";
    }
    return os;
}

};
};