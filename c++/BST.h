#pragma once

#include"tree.h"

template<typename T>
class BST:public Tree<T>
{
private:
	TreeNode<T>* m_root;
public:
	BST():m_root(nullptr) {};

	TreeNode<T>* getroot()
	{
		return m_root;
	}
	void insert(T value){
		
		if (m_root == nullptr)
		{
			m_root = new TreeNode<T>(value);
			return;
		}
		TreeNode<T>* tnode = m_root,* pretnode = nullptr;
		while (tnode != nullptr)
		{
			if (value == tnode->val)
				return;
			pretnode = tnode;
			tnode = (value < tnode->val) ? tnode->left : tnode->right;
		}
		if(value < pretnode -> val)
			pretnode -> left = new TreeNode<T>(value);
		else
			pretnode -> right = new TreeNode<T>(value);
	}
	void remove(T value){
		TreeNode<T>* tnode = find(value);
		if (tnode == nullptr)
			return;

		if (tnode->left != nullptr && tnode->right != nullptr)
		{
			removeLR(tnode);
			return;
		}
		TreeNode<T>* pretnode = findpre(value);

		if (tnode->left == nullptr && tnode->right == nullptr)
		{
			remove_(tnode, pretnode);
			return;
		}

		if (tnode->right == nullptr && tnode->left != nullptr)
		{
			removeL(tnode, pretnode);
			return;
		}

		if (tnode->left == nullptr && tnode->right != nullptr)
		{
			removeR(tnode, pretnode);
			return;
		}
		
	}
	TreeNode<T>* find(T value){
		TreeNode<T>* tnode = m_root;
		while (tnode != nullptr)
		{
			if (tnode->val == value)
				break;
			else
				tnode = (value < tnode->val) ? tnode->left : tnode->right;
		}
		return tnode;
	}
	~BST() {
		removeall(m_root);
		m_root = nullptr;
	};

private:
	TreeNode<T>* findpre(T value) {
		TreeNode<T>* tnode = m_root, * pretnode = nullptr;
		while (tnode != nullptr)
		{
			if (value == tnode->val)
				break;
			pretnode = tnode;
			tnode = (value < tnode->val) ? tnode->left : tnode->right;
		}
		return pretnode;
	}

	TreeNode<T>* findnext(TreeNode<T>* tnode) {
		tnode = tnode->right;
		while (tnode->left != nullptr)
		{
			tnode = tnode->left;
		}
		return tnode;
	}
	void remove_(TreeNode<T>* tnode, TreeNode<T>* pretnode)
	{
		if (pretnode == nullptr)
			m_root = nullptr;
		else
		{
			if (pretnode->left == tnode)
				pretnode->left = nullptr;
			else
				pretnode->right = nullptr;
		}
		delete(tnode);
	}

	void removeL(TreeNode<T>* tnode, TreeNode<T>* pretnode)
	{
		if (pretnode == nullptr)
			m_root = tnode->left;
		else
		{
			if (pretnode->left == tnode)
				pretnode->left = tnode->left;
			else
				pretnode->right = tnode->left;
		}
		delete(tnode);
	}

	void removeR(TreeNode<T>* tnode, TreeNode<T>* pretnode)
	{
		if (pretnode == nullptr)
			m_root = tnode->right;
		else
		{
			if (pretnode->left == tnode)
				pretnode->left = tnode->right;
			else
				pretnode->right = tnode->right;
		}
		delete(tnode);
	}

	void removeLR(TreeNode<T>* tnode)
	{
		TreeNode<T>* nextnode = findnext(tnode);
		tnode->val = nextnode->val;

		if (nextnode->left == nullptr && nextnode->right == nullptr)
		{
			remove_(nextnode, findpre(nextnode->val));
			return;
		}

		if (nextnode->right == nullptr && nextnode->left != nullptr)
		{
			removeL(nextnode, findpre(nextnode->val));
			return;
		}

		if (nextnode->left == nullptr && nextnode->right != nullptr)
		{
			removeR(nextnode, findpre(nextnode->val));
			return;
		}
	}

	void removeall(TreeNode<T>* tnode)
	{
		if (tnode == nullptr)
		{
			return;
		}
		removeall(tnode->left);
		removeall(tnode->right);
		delete(tnode);
	}
};
