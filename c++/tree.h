#pragma once

template<typename T>
class TreeNode {
public:
    virtual T getval()=0;
    virtual TreeNode* getleft()=0;
    virtual TreeNode* getright()=0;

    virtual void setval(T val) = 0;
    virtual void setleft(TreeNode* left) = 0;
    virtual void setright(TreeNode* riht) = 0;
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


