#include"BST.h"
#include<iostream>
#include"TraverseTreeh.h"
static void test()
{
	BST<int> bst;
	for (int i = 1; i < 10; i++)
	{
		bst.insert(i);
		if (bst.find(i))
			std::cout << i << std::endl;
	}
	bst.remove(1);
	TraverseTree<int>::LRD(bst.getroot());
}
