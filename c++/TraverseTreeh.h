#include"iostream"
#include"BST.h"
template<typename T>
class TraverseTree {
public:
	static void DLR(TreeNode<T>* tnode)
	{
		if (tnode == nullptr)
		{
			return;
		}
		std::cout << tnode->val << std::endl;
		DLR(tnode->left);
		DLR(tnode->right);
	}
	static void LDR(TreeNode<T>* tnode)
	{
		if (tnode == nullptr)
		{
			return;
		}
		LDR(tnode->left);
		std::cout << tnode->val << std::endl;
		LDR(tnode->right);
	}
	static void LRD(TreeNode<T>* tnode)
	{
		if (tnode == nullptr)
		{
			return;
		}
		LRD(tnode->left);
		LRD(tnode->right);
		std::cout << tnode->val << std::endl;
	}
};