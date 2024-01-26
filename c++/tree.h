#pragma once

template<typename T>
struct TreeNode {
    T val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(T x) : val(x), left(nullptr), right(nullptr) {}
};

template<typename T>
class Tree
{   
public:
    virtual~Tree() {};
    virtual TreeNode<T>* getroot() = 0;
    virtual void insert(T value) = 0;
    virtual void remove(T value) = 0;
    virtual TreeNode<T>*  find(T value) = 0;
};


