#include<iostream>
#include<algorithm>
#include"RBT.h"
#include"TraverseTreeh.h"
template<typename T>
static int getheight(TreeNode<T>* tnode)
{
	if (tnode == nullptr)
		return 0;
	int lh = getheight(tnode->getleft());
	int rh = getheight(tnode->getright());
	return std::max(lh, rh) + 1;
}
static void test()
{
	RBT<int> rbtree;
	for (int i = 1; i < 200; i++)
	{
		rbtree.insert(i);
		/*if (rbtree.find(i))
			std::cout << i<< std::endl;*/

	}
	std::cout << getheight(rbtree.getroot()) <<"height"<< std::endl;
	//TraverseTree<int>::LDR(rbtree.getroot());
	for (int i = 1; i < 100; i++)
	{
		rbtree.remove(i);
		std::cout <<i<<std::endl;
		std::cout << getheight(rbtree.getroot()->getleft()) << "zuo" << std::endl;
		std::cout << getheight(rbtree.getroot()->getright()) << "yuo" << std::endl;
		std::cout <<std::endl;
	
	}
	//TraverseTree<int>::LDR(rbtree.getroot());
}

int main() {
	test();
	return 0;
}