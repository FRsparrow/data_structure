#include <iostream>
#include "myheaders/binary_tree.h"

using namespace std;

template<class E>
void visit(Binary_Tree<E>* p)
{
    cout << p->data << " ";
}

int main()
{
    auto tree = new Binary_Tree<int>(1);
    tree->lchild = new Binary_Tree<int>(2);
    tree->rchild = new Binary_Tree<int>(3);
    tree->lchild->lchild = new Binary_Tree<int>(4);
    tree->lchild->rchild = new Binary_Tree<int>(5);
    tree->rchild->lchild = new Binary_Tree<int>(6);
    tree->rchild->rchild = new Binary_Tree<int>(7);
    tree->rchild->rchild->rchild = new Binary_Tree<int>(8);
    levelorder(visit, tree);
    cout << endl;

    system("pause");
    return 0;
}