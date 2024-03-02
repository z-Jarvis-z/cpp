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
		std::cout << tnode->getval() << std::endl;
		DLR(tnode->getleft());
		DLR(tnode->getright());
	}
	static void LDR(TreeNode<T>* tnode)
	{
		if (tnode == nullptr)
		{
			return;
		}
		LDR(tnode->getleft());
		std::cout << tnode->getval() << std::endl;
		LDR(tnode->getright());
	}
	static void LRD(TreeNode<T>* tnode)
	{
		if (tnode == nullptr)
		{
			return;
		}
		LRD(tnode->getleft());
		LRD(tnode->getright());
		std::cout << tnode->getval() << std::endl;
	}
};