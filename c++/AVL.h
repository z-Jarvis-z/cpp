#pragma once

#include "tree.h"
template<typename T>
class AVLNode : public TreeNode<T>
{
public:
    T getval() { return val; }
    TreeNode<T>* getleft() { return left; }
    TreeNode<T>* getright() { return right; }

    void setval(T val) { this->val = val; }
    void setleft(TreeNode<T>* left) { this->left = (AVLNode<T>*)left; }
    void setright(TreeNode<T>* right) { this->right = (AVLNode<T>*)right; }

    void setheight(int height) { this->height = height; }
    int getheight() { return this->height; }

    AVLNode(T val) :val(val), left(nullptr), right(nullptr),height(1){}
private:
    T val;
    AVLNode<T>* left, * right;
    unsigned int height;
};
template<typename T>
class AVL: public Tree<T>
{
private:
    TreeNode<T>* m_root;
public:
    AVL() : m_root(nullptr) {};

    TreeNode<T>* getroot()
    {
        return (TreeNode<T>*)m_root;
    }
    void insert(T value)
    {
        TreeNode<T>* node = find(value);
        if (node != nullptr)
            return;
        m_root = insert_(m_root, value);
    }
    void remove(T value)
    {
        TreeNode<T>* tnode = find(value);
        if (tnode == nullptr)
            return;

        m_root = remove_val(m_root, value);

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
    ~AVL()
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

    TreeNode<T>* remove_val(TreeNode<T>* tnode,T value)
    {
        if (tnode->getval() > value)
        {
            tnode->setleft(remove_val(tnode->getleft(), value));
        }
        else if(tnode->getval() < value)
        {
            tnode->setright(remove_val(tnode->getright(), value));
        }
        else if (tnode->getval() == value)
        {
            if (tnode->getleft() != nullptr && tnode->getright() != nullptr)
            {
                TreeNode<T>* nextnode = findnext(tnode);
                tnode->setval(nextnode->getval());
                tnode->setright(remove_val(tnode->getright(), tnode->getval()));
            }
            else if (tnode->getleft() == nullptr && tnode->getright() == nullptr)
            {
                delete tnode;
                tnode = nullptr;
            }
            else if (tnode->getright() == nullptr && tnode->getleft() != nullptr)
            {
                TreeNode<T>* node = tnode;
                tnode = tnode->getleft();
                delete node;
            }
            else if (tnode->getleft() == nullptr && tnode->getright() != nullptr)
            {
                TreeNode<T>* node = tnode;
                tnode = tnode->getright();
                delete node;
            }
        }
        if (tnode == nullptr)
            return nullptr;
        update_height(tnode);
        return keep_balance(tnode);
    }


    TreeNode<T>* remove_node(TreeNode<T>* tnode)
    {
        

        return tnode;
    }

    TreeNode<T>* insert_(TreeNode<T>* tnode, T value)
    {
        if (tnode == nullptr)
        {
            tnode = new AVLNode<T>(value);
            return tnode;
        }
       
        if (value < tnode->getval())
        {
            tnode->setleft(insert_(tnode->getright(), value));
        }
        else
        {
            tnode->setright(insert_(tnode->getright(), value));
        }
        update_height(tnode);

        return keep_balance(tnode);
    }

    TreeNode<T>* keep_balance(TreeNode<T>* tnode)
    {
        int factor = getbalance_factor(tnode);


        if (factor > 1)
        {
            int factor_l = getbalance_factor(tnode->getleft());
            if (factor_l > 0)
            {
                return rotate_LL(tnode);
            }
            if (factor_l < 0)
            {
                return rotate_LR(tnode);
            }
        }
        if (factor < -1)
        {
            int factor_r = getbalance_factor(tnode->getright());
            if (factor_r < 0)
            {
                return rotate_RR(tnode);
            }
            if (factor_r < 0)
            {
                return rotate_RL(tnode);
            }
        }
        return tnode;
    }

    TreeNode<T>* rotate_LL(TreeNode<T>* tnode)
    {
        TreeNode<T>* new_tnode = tnode->getleft();
        tnode->setleft(new_tnode->getright());
        new_tnode->setright(tnode);
        update_height(tnode);
        update_height(new_tnode);
        return new_tnode;
    } 
    
    TreeNode<T>* rotate_LR(TreeNode<T>* tnode)
    {
        TreeNode<T>* new_tnode = tnode->getleft()->getright();
        TreeNode<T>* new_left = tnode->getleft();
        tnode->setleft(new_tnode->getright());
        new_left->setright(new_tnode->getleft());
        new_tnode->setleft(new_left);
        new_tnode->setright(tnode);
        update_height(tnode);
        update_height(new_left);
        update_height(new_tnode);
        return new_tnode;
    }

    TreeNode<T>* rotate_RR(TreeNode<T>* tnode)
    {
        TreeNode<T>* new_tnode = tnode->getright();
        tnode->setright(new_tnode->getleft());
        new_tnode->setleft(tnode);
        update_height(tnode);
        update_height(new_tnode);
        return new_tnode;
    }
    
    TreeNode<T>* rotate_RL(TreeNode<T>* tnode)
    {
        TreeNode<T>* new_tnode = tnode->getright()->getleft();
        TreeNode<T>* new_right = tnode->getright();
        tnode->setright(new_tnode->getleft());
        new_right->setleft(tnode->getright());
        new_tnode->setleft(tnode);
        new_tnode->setright(new_right);
        update_height(tnode);
        update_height(new_right);
        update_height(new_tnode);
        return new_tnode;
    }

    void update_height(TreeNode<T>* tnode)
    {
        AVLNode<T>* node = dynamic_cast<AVLNode<T>*>(tnode);
        auto max = [](int a, int b)->int {return a > b ? a : b; };
        node->setheight(1 + max(get_height(tnode->getleft()), get_height(tnode->getright())));
    }

    int get_height(TreeNode<T>* tnode)
    {
        AVLNode<T>* tnode_ = dynamic_cast<AVLNode<T>*>(tnode);
        if (tnode_ == nullptr)
            return 0;
        return tnode_->getheight();
    }

    int getbalance_factor(TreeNode<T>* tnode)
    {
        
        AVLNode<T>* left = dynamic_cast<AVLNode<T>*>(tnode->getleft());
        AVLNode<T>* right = dynamic_cast<AVLNode<T>*>(tnode->getright());

        if (right == nullptr && left == nullptr)
            return 0;
        if (right == nullptr && left != nullptr)
            return left->getheight();
        if (right != nullptr && left == nullptr)
            return -right->getheight();
        return left->getheight() - right->getheight();
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
