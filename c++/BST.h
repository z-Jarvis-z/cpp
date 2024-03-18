#pragma once

#include "tree.h"
template<typename T>
class BSTNode : public TreeNode<T>
{
public:
    T getval() { return val; }
    TreeNode<T>* getleft() { return left; }
    TreeNode<T>* getright() { return right; }

    void setval(T val) { this->val = val; }
    void setleft(TreeNode<T>* left) { this->left = (BSTNode<T>*)left; }
    void setright(TreeNode<T>* right) { this->right = (BSTNode<T>*)right; }

    BSTNode(T val):val(val),left(nullptr),right(nullptr){}
private:
    T val;
    BSTNode<T>* left, * right;
};
template<typename T>
class BST : public Tree<T>
{
private:
    TreeNode<T>* m_root;
public:
    BST() : m_root(nullptr) {};

    TreeNode<T>* getroot()
    {
        return m_root;
    }
    void insert(T value)
    {

        if (m_root == nullptr)
        {
            m_root = new BSTNode<T>(value);
            return;
        }
        TreeNode<T>* node = find(value);
        if (node != nullptr)
            return;
        TreeNode<T>* tnode = m_root, * pretnode = nullptr;
        while (tnode != nullptr)
        {
            if (value == tnode->getval())
                return;
            pretnode = tnode;
            tnode = (value < tnode->getval()) ? tnode->getleft() : tnode->getright();
        }
        if (value < pretnode->getval())
            pretnode->setleft(new BSTNode<T>(value));
        else
            pretnode->setright(new BSTNode<T>(value));
    }
    void remove(T value)
    {
        TreeNode<T>* tnode = find(value);
        if (tnode == nullptr)
            return;

        if (tnode->getleft() != nullptr && tnode->getright() != nullptr)
        {
            removeLR(tnode);
            return;
        }
        TreeNode<T>* pretnode = findpre(value);

        if (tnode->getleft() == nullptr && tnode->getright() == nullptr)
        {
            remove_(tnode, pretnode);
            return;
        }

        if (tnode->getright() == nullptr && tnode->getleft() != nullptr)
        {
            removeL(tnode, pretnode);
            return;
        }

        if (tnode->getleft() == nullptr && tnode->getright() != nullptr)
        {
            removeR(tnode, pretnode);
            return;
        }

    }
    TreeNode<T>* find(T value)
    {
        TreeNode<T>* tnode = m_root;
        while (tnode != nullptr)
        {
            if (tnode->getval() == value)
                break;
            else
                tnode = (value < tnode->getval()) ? tnode->getleft() : tnode->getright();
        }
        return tnode;
    }
    ~BST()
    {
        removeall(m_root);
        m_root = nullptr;
    };

private:
    TreeNode<T>* findpre(T value)
    {
        TreeNode<T>* tnode = m_root, * pretnode = nullptr;
        while (tnode != nullptr)
        {
            if (value == tnode->getval())
                break;
            pretnode = tnode;
            tnode = (value < tnode->getval()) ? tnode->getleft() : tnode->getright();
        }
        return pretnode;
    }

    TreeNode<T>* findnext(TreeNode<T>* tnode)
    {
        tnode = tnode->getright();
        while (tnode->getleft() != nullptr)
        {
            tnode = tnode->getleft();
        }
        return tnode;
    }
    void remove_(TreeNode<T>* tnode, TreeNode<T>* pretnode)
    {
        if (pretnode == nullptr)
            m_root = nullptr;
        else
        {
            if (pretnode->getleft() == tnode)
                pretnode->setleft(nullptr);
            else
                pretnode->setright(nullptr);
        }
        delete(tnode);
    }

    void removeL(TreeNode<T>* tnode, TreeNode<T>* pretnode)
    {
        if (pretnode == nullptr)
            m_root = tnode->getleft();
        else
        {
            if (pretnode->getleft() == tnode)
                pretnode->setleft(tnode->getleft());
            else
                pretnode->setright(tnode->getleft());
        }
        delete(tnode);
    }

    void removeR(TreeNode<T>* tnode, TreeNode<T>* pretnode)
    {
        if (pretnode == nullptr)
            m_root = tnode->getright();
        else
        {
            if (pretnode->getleft() == tnode)
                pretnode->setleft(tnode->getright());
            else
                pretnode->setright(tnode->getright());
        }
        delete(tnode);
    }

    void removeLR(TreeNode<T>* tnode)
    {
        TreeNode<T>* nextnode = findnext(tnode);
        tnode->setval(nextnode->getval());

        if (nextnode->getleft() == nullptr && nextnode->getright() == nullptr)
        {
            remove_(nextnode, findpre(nextnode->getval()));
            return;
        }

        if (nextnode->getright() == nullptr && nextnode->getleft() != nullptr)
        {
            removeL(nextnode, findpre(nextnode->getval()));
            return;
        }

        if (nextnode->getleft() == nullptr && nextnode->getright() != nullptr)
        {
            removeR(nextnode, findpre(nextnode->getval()));
            return;
        }
    }

    void removeall(TreeNode<T>* tnode)
    {
        if (tnode == nullptr)
        {
            return;
        }
        removeall(tnode->getleft());
        removeall(tnode->getright());
        delete(tnode);
    }
};
