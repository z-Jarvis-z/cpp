#pragma once
#include"tree.h"
enum class NodeColor
{
    RED,
    BLACK
};
template<typename T>
class RBTNode : public TreeNode<T>
{
public:
    T getval() { return val; }
    TreeNode<T>* getleft() { return left; }
    TreeNode<T>* getright() { return right; }

    void setval(T val) { this->val = val; }
    void setleft(TreeNode<T>* left) { this->left = (RBTNode<T>*)left; }
    void setright(TreeNode<T>* right) { this->right = (RBTNode<T>*)right; }

    void setcolor(NodeColor color) { this->m_color = color; }
    NodeColor getcolor() { return this->m_color; }

    RBTNode(T val, NodeColor color) :val(val), left(nullptr), right(nullptr), m_color(color) {}
private:
    T val;
    RBTNode<T>* left, * right;
    NodeColor m_color;
};
template<typename T>
class RBT:public Tree<T>
{
public:
    TreeNode<T>* m_root;
    RBT() :m_root(nullptr) {};
    ~RBT() {
        removeall(m_root);
        m_root = nullptr;
    }
    TreeNode<T>* getroot()
    {
        return m_root;
    }
    void insert(T value)
    {
        TreeNode<T>* node = find(value);
        if (node != nullptr)
            return;
        m_root = insert_(m_root,value);
        if (getcolor(m_root) == NodeColor::RED)
        {
            setcolor(m_root, NodeColor::BLACK);
        }
        return;
       
    }
    void remove(T value)
    {
        TreeNode<T>* tnode = find(value);
        if (tnode == nullptr)
            return;
        do_remove(tnode);
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
        if (tnode->getleft() == nullptr)
            return tnode->getleft();
        if (tnode->getright() == nullptr)
            return tnode->getleft();
        tnode = tnode->getright();
        while (tnode->getleft() != nullptr)
        {
            tnode = tnode->getleft();
        }
        return tnode;
    }
    TreeNode<T>* insert_(TreeNode<T>* tnode, T value)
    {
        if (tnode == nullptr)
        {
            tnode = new RBTNode<T>(value, NodeColor::RED);
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
        return fix_double_red(tnode);
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
    NodeColor getcolor(TreeNode<T>* tnode)
    {
        RBTNode<T>* node = dynamic_cast<RBTNode<T>*>(tnode);
        if (tnode == nullptr)
            return NodeColor::BLACK;
        return node->getcolor();
    }
    void setcolor(TreeNode<T>* tnode, NodeColor color)
    {
        RBTNode<T>* node = dynamic_cast<RBTNode<T>*>(tnode);
        if (node == nullptr)
            return;
        node->setcolor(color);
    }
    unsigned int check_insert(TreeNode<T>* tnode) {
        TreeNode<T>* l_child = tnode->getleft();
        TreeNode<T>* r_child = tnode->getright();
        if (getcolor(l_child) == NodeColor::RED)
        {
            unsigned int factor = 1 << 3;
            if (getcolor(r_child) == NodeColor::RED)
            {
                factor += (1 << 4);
            }
			if (getcolor(l_child->getleft()) == NodeColor::RED)
				return factor;
			else if (getcolor(l_child->getright()) == NodeColor::RED)
				return factor + (1 << 2);
        }
        if (getcolor(r_child) == NodeColor::RED)
        {
            unsigned int factor = 1 << 1;
            if (getcolor(l_child) == NodeColor::RED)
            {
                factor += (1 << 4);
            }
            if (getcolor(r_child->getleft()) == NodeColor::RED)
                return factor;
            else if (getcolor(r_child->getright()) == NodeColor::RED)
                return factor + 1;
        }
        return 0;
    }
    TreeNode<T>* fix_double_red(TreeNode<T>* tnode)
    {
        if (tnode == nullptr)
            return tnode;
        unsigned int banlance_factor = check_insert(tnode);
        if (banlance_factor == 0)
            return tnode;
        if (banlance_factor & 1 << 4) {
            setcolor(tnode, NodeColor::RED);
            setcolor(tnode->getleft(), NodeColor::BLACK);
            setcolor(tnode->getright(), NodeColor::BLACK);
            return tnode;
        }
        if (banlance_factor & 1 << 3) 
        {
            if (banlance_factor & 1 << 2)
            {
                return rotate_LR(tnode);
            }
            else 
            {
                return rotate_LL(tnode);
            }
        }
        if (banlance_factor & 1 << 1) {
            if (banlance_factor & 1)
            {
                return rotate_RR(tnode);
            }
            else
            {
                return rotate_RL(tnode);
            }
        }
        return tnode;

    }

    void fix_double_black(TreeNode<T>* tnode)
    {
        if (tnode == m_root)
            return;
        TreeNode<T>* p_node = findpre(tnode->getval());
        TreeNode<T>* b_node = p_node->getleft();
        if (b_node == tnode)
            b_node = p_node->getright();
        if (getcolor(b_node) == NodeColor::RED)
        {
            setcolor(p_node, NodeColor::RED);
            setcolor(b_node, NodeColor::BLACK);
            if (tnode == p_node->getleft())
            {
                L_rotate(p_node);
            }
            else 
            {
                R_rotate(p_node);
            }

            fix_double_black(tnode);
            return;
        }

		if (getcolor(b_node->getright()) == NodeColor::BLACK && getcolor(b_node->getleft()) == NodeColor::BLACK)
		{
			setcolor(b_node, NodeColor::RED);
			if (getcolor(p_node) == NodeColor::RED)
			{
				setcolor(p_node, NodeColor::BLACK);
			}
			else {
				fix_double_black(p_node);
			}
		}
		else {
			if (b_node == p_node->getleft())
			{
				if (getcolor(b_node->getleft()) == NodeColor::RED)
				{
					setcolor(b_node->getleft(), NodeColor::BLACK);
					setcolor(b_node, getcolor(p_node));
					R_rotate(p_node);
				}
				else if (getcolor(b_node->getright()) == NodeColor::RED)
				{
					setcolor(b_node->getright(), getcolor(p_node));
					L_rotate(b_node);
					R_rotate(p_node);
				}
			}
			else
			{
				if (getcolor(b_node->getleft()) == NodeColor::RED)
				{
					setcolor(b_node->getleft(), getcolor(p_node));
					R_rotate(b_node);
					L_rotate(p_node);
				}
				else if (getcolor(b_node->getright()) == NodeColor::RED)
				{
					setcolor(b_node->getright(), NodeColor::BLACK);
					setcolor(b_node, getcolor(p_node));
					L_rotate(p_node);
				}
			}
			setcolor(p_node, NodeColor::BLACK);
		}
    }

    void do_remove(TreeNode<T>* tnode)
    {
        TreeNode<T>* next = findnext(tnode);
        if (next == nullptr)
        {
            if (tnode == m_root)
            {
                m_root = nullptr;
            }
            else
            {
                if (getcolor(tnode) == NodeColor::BLACK)
                {
                    fix_double_black(tnode);
                }
                TreeNode<T>* p_node = findpre(tnode->getval());
                if (tnode == p_node->getleft())
                {
                    p_node->setleft(nullptr);
                }
                else {
                    p_node->setright(nullptr);
                }
            }
            delete tnode;
            return;
        }
        else if (tnode->getleft() == nullptr || tnode->getright() == nullptr)
        {
            if (tnode == m_root)
            {
                m_root = next;
                setcolor(m_root, NodeColor::BLACK);
            }
            else 
            {
                TreeNode<T>* p_node = findpre(tnode->getval());
                if (tnode == p_node->getleft())
                {
                    p_node->setleft(next);
                }
                else
                {
                    p_node->setright(next);
                }
                setcolor(next, NodeColor::BLACK);
            }
            return;
        }
        else 
        {
            tnode->setval(next->getval());
            do_remove(next);
        }
    }

    TreeNode<T>* rotate_LL(TreeNode<T>* tnode)
    {
        setcolor(tnode, NodeColor::RED);
        TreeNode<T>* new_tnode = tnode->getleft();
        setcolor(new_tnode, NodeColor::BLACK);
        tnode->setleft(new_tnode->getright());
        new_tnode->setright(tnode);
        return new_tnode;
    }

    TreeNode<T>* rotate_LR(TreeNode<T>* tnode)
    {
        setcolor(tnode, NodeColor::RED);
        TreeNode<T>* new_tnode = tnode->getleft()->getright();
        setcolor(new_tnode, NodeColor::BLACK);
        TreeNode<T>* new_left = tnode->getleft();
        tnode->setleft(new_tnode->getright());
        new_left->setright(new_tnode->getleft());
        new_tnode->setleft(new_left);
        new_tnode->setright(tnode);
        return new_tnode;
    }

    TreeNode<T>* rotate_RR(TreeNode<T>* tnode)
    {
        setcolor(tnode, NodeColor::RED);
        TreeNode<T>* new_tnode = tnode->getright();
        setcolor(new_tnode, NodeColor::BLACK);
        tnode->setright(new_tnode->getleft());
        new_tnode->setleft(tnode);
        return new_tnode;
    }

    TreeNode<T>* rotate_RL(TreeNode<T>* tnode)
    {
        setcolor(tnode, NodeColor::RED);
        TreeNode<T>* new_tnode = tnode->getright()->getleft();
        setcolor(new_tnode, NodeColor::BLACK);
        TreeNode<T>* new_right = tnode->getright();
        tnode->setright(new_tnode->getleft());
        new_right->setleft(tnode->getright());
        new_tnode->setleft(tnode);
        new_tnode->setright(new_right);
        return new_tnode;
    }

    void R_rotate(TreeNode<T>* tnode)
    {

        TreeNode<T>* p_node = findpre(tnode->getval());
        TreeNode<T>* new_tnode = tnode->getleft();
        tnode->setleft(new_tnode->getright());
        new_tnode->setright(tnode);
        if (p_node == nullptr)
            m_root = new_tnode;
        else if (p_node->getleft() == tnode)
            p_node->setleft(new_tnode);
        else
            p_node->setright(new_tnode);
    }

    void L_rotate(TreeNode<T>* tnode) {
        TreeNode<T>* p_node = findpre(tnode->getval());
        TreeNode<T>* new_tnode = tnode->getright();
        tnode->setright(new_tnode->getleft());
        new_tnode->setleft(tnode);
        if (p_node == nullptr)
            m_root = new_tnode;
        else if (p_node->getleft() == tnode)
            p_node->setleft(new_tnode);
        else
            p_node->setright(new_tnode);
    }

    //Î´¿¼ÂÇË«ºÚ
    TreeNode<T>* remove_val(TreeNode<T>* tnode, T value)
    {
        if (tnode->getval() > value)
        {
            tnode->setleft(remove_val(tnode->getleft(), value));
        }
        else if (tnode->getval() < value)
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
                if (getcolor(tnode) == NodeColor::RED || tnode == m_root)
                {
                    delete tnode;
                    tnode = nullptr;
                }
                else {
                    tnode = remeove_Blacknode_(tnode);
                }
            }
            else if (tnode->getright() == nullptr && tnode->getleft() != nullptr)
            {
                TreeNode<T>* node = tnode;
                setcolor(tnode->getleft(), getcolor(tnode));
                tnode = tnode->getleft();
                delete node;
            }
            else if (tnode->getleft() == nullptr && tnode->getright() != nullptr)
            {
                TreeNode<T>* node = tnode;
                setcolor(tnode->getleft(), getcolor(tnode));

                tnode = tnode->getright();
                delete node;
            }
        }
        
        return tnode;
    }

    TreeNode<T>* remeove_Blacknode_(TreeNode<T>* tnode)
    {
        TreeNode<T>* p_node = findpre(tnode->getval());
        TreeNode<T>* b_node = p_node->getleft();
        if (b_node == tnode)
        {
            b_node = p_node->getright();
            if (getcolor(b_node) == NodeColor::BLACK)
            {
                if (b_node->getleft() == nullptr && b_node->getright() == nullptr)
                {
                    delete tnode;
                    tnode = nullptr;
                    setcolor(p_node, NodeColor::BLACK);
                    setcolor(b_node, NodeColor::RED);
                    return tnode;
                }
                tnode->setval(p_node->getval());
                if (b_node->getright() != nullptr)
                {
                    p_node->setval(b_node->getval());
                    b_node->setval(b_node->getright()->getval());
                    delete b_node->getright();
                    b_node->setright(nullptr);
                    if (b_node->getleft() != nullptr)
                    {
                        tnode->setright(b_node->getleft());
                        b_node->setleft(nullptr);
                    }
                    return tnode;
                }
                else
                {
                    p_node->setval(b_node->getleft()->getval());
                    delete b_node->getleft();
                    b_node->setleft(nullptr);
                    return tnode;
                }

            }
            else {
                tnode->setval(p_node->getval());
                p_node->setval(b_node->getval());
                b_node->setval(b_node->getright()->getval());
                delete b_node->getright();
                b_node->setright(nullptr);
				tnode->setright(b_node->getleft());
				b_node->setleft(nullptr);
				setcolor(b_node, NodeColor::RED);
                return tnode;
            }
        }
        else
        {
            if (getcolor(b_node) == NodeColor::BLACK)
            {
                if (b_node->getleft() == nullptr && b_node->getright() == nullptr)
                {
                    delete tnode;
                    tnode = nullptr;
                    setcolor(p_node, NodeColor::BLACK);
                    setcolor(b_node, NodeColor::RED);
                    return tnode;
                }
                tnode->setval(p_node->getval());
                if (b_node->getleft() != nullptr)
                {
                    p_node->setval(b_node->getval());
                    b_node->setval(b_node->getleft()->getval());
                    delete b_node->getleft();
                    b_node->setleft(nullptr);
                    if (b_node->getright() != nullptr)
                    {
                        tnode->setleft(b_node->getright());
                        b_node->setright(nullptr);
                    }
                    return tnode;
                }
                else
                {
                    p_node->setval(b_node->getright()->getval());
                    delete b_node->getright();
                    b_node->setright(nullptr);
                    return tnode;
                }

            }
            else {
				tnode->setval(p_node->getval());
				p_node->setval(b_node->getval());
				b_node->setval(b_node->getleft()->getval());
				delete b_node->getleft();
				b_node->setleft(nullptr);
				tnode->setleft(b_node->getright());
				b_node->setright(nullptr);
                setcolor(b_node, NodeColor::RED);
				return tnode;
            }
        }
    }
};

