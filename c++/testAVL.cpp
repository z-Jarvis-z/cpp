#include"AVL.h"
#include<iostream>
#include"TraverseTreeh.h"
static void test()
{
	AVL<int> bst;
	for (int i = 1; i < 10; i++)
	{
		bst.insert(i);
		if (bst.find(i))
			std::cout << i << std::endl;
	}
	TraverseTree<int>::LDR(bst.getroot());
	AVLNode<int>* tnode_ = dynamic_cast<AVLNode<int>*>(bst.getroot());
	std::cout << tnode_->getheight() << "height" << std::endl;
	bst.remove(9);
	bst.remove(2);
	bst.remove(3);
	bst.remove(5);
	TraverseTree<int>::LDR(bst.getroot());
	tnode_ = dynamic_cast<AVLNode<int>*>(bst.getroot());
	std::cout << tnode_->getheight() <<"height"<< std::endl;
}
