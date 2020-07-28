#include <stack>
#include <queue>

using namespace std;

template<class E>
class Binary_Tree
{
private:
    /* data */
public:
    E data;
    Binary_Tree* lchild;
    Binary_Tree* rchild;

    Binary_Tree(E e);
    ~Binary_Tree();
};

template<class E>
Binary_Tree<E>::Binary_Tree(E e)
{
    data = e;
    lchild = nullptr;
    rchild = nullptr;
}

template<class E>
Binary_Tree<E>::~Binary_Tree<E>()
{
}

/* 
 栈中初始压入空指针作为结束
1、访问当前栈外指针p，若为空结束，否则：
2、访问其data
3、若右孩子不为空，则放入栈中后续访问
4、若左孩子不为空，则左孩子为新的当前栈外指针，即p=p->lchild，转1
5、从栈中取指针赋给p，即p=stack.top();stack.pop()，转1
*/
template<class E>
void preorder(void(*visit)(Binary_Tree<E>* bt), Binary_Tree<E>* root)
{
    stack<Binary_Tree<E>*> s;
    Binary_Tree<E>* p = root;
    s.push(nullptr);
    
    while (p != nullptr)
    {
        visit(p);
        if(p->rchild != nullptr)
        {
            s.push(p->rchild);
        }
        if (p->lchild != nullptr)
        {
            p = p->lchild;
        }
        else
        {
            p = s.top();
            s.pop();
        }
    }
    
}

/*
 栈中存放左孩子已经访问完的结点，
 1、栈外指针不是来自栈中且有左孩子则去访问左孩子，自身进栈待访问自身和右孩子，指针指向左孩子，转1，否则转2
 2、栈外指针有右孩子，则访问自身，然后指向右孩子，from_stack置false，转1，否则转3
 3、访问自身，若栈非空则栈外指针取栈顶弹出，置from_stack为true，转1.否则结束
*/
template<class E>
void myinorder(void(*visit)(Binary_Tree<E>* bt), Binary_Tree<E>* root)
{
    stack<Binary_Tree<E>*> s;
    auto p = root;
    bool from_stack = false;
    while (true)
    {
        if (!from_stack && p->lchild)
        {
            s.push(p);
            p = p->lchild;
        }
        else if (p->rchild)
        {
            visit(p);
            p = p->rchild;
            from_stack = false;
        }
        else
        {
            visit(p);
            if (s.empty())
            {
                break;
            }
            else
            {
                p = s.top();
                s.pop();
                from_stack = true;
            }
        }
        
    }
}

template<class E>
void inorder(void(*visit)(Binary_Tree<E>* bt), Binary_Tree<E>* root)
{
    stack<Binary_Tree<E>*> s;
    Binary_Tree<E>* p = root;
    do
    {
        while (p)
        {
            s.push(p);
            p = p->lchild;
        }
        if (!s.empty())
        {
            p = s.top();
            s.pop();
            visit(p);
            p = p->rchild;
        }
        
    } while (p || !s.empty());
    
}

/*
 按照顺序：自身-右孩子-左孩子（类似前序）输出到栈中，再遍历栈按相反顺序左孩子-右孩子-自身的后序输出
*/
template<class E>
void mypostorder(void(*visit)(Binary_Tree<E>* bt), Binary_Tree<E>* root)
{
    stack<Binary_Tree<E>*> output;
    stack<Binary_Tree<E>*> s;
    Binary_Tree<E>* p = root;
    s.push(nullptr);
    while (p)
    {
        output.push(p);
        if (p->lchild)
        {
            s.push(p->lchild);
        }
        if (p->rchild)
        {
            p = p->rchild;
        }
        else
        {
            p = s.top();
            s.pop();
        }
    }
    while (!output.empty())
    {
        visit(output.top());
        output.pop();
    }
}

// 后序遍历栈的结点定义
template<class E>
struct stk_node 
{
    Binary_Tree<E>* ptr;
    bool tag;
    stk_node(Binary_Tree<E>* p = nullptr):ptr(p),tag(false){}
};

template<class E>
void postorder(void(*visit)(Binary_Tree<E>* bt), Binary_Tree<E>* root)
{
    stack<stk_node<E>> s;
    stk_node<E> w;
    Binary_Tree<E>* p = root;
    do
    {
        while (p)
        {
            w.ptr = p;
            w.tag = false;
            s.push(w);
            p = p->lchild;
        }
        bool continue1 = true;
        while (continue1 && !s.empty())
        {
            w = s.top();
            s.pop();
            p = w.ptr;
            if (w.tag)
            {
                visit(p);
            }
            else
            {
                w.tag = true;
                s.push(w);
                continue1 = false;
                p = p->rchild;
            }
        }
        
    } while (!s.empty());
}

// 层次遍历
template<class E>
void levelorder(void(*visit)(Binary_Tree<E>* bt), Binary_Tree<E>* root)
{
    if (!root)
    {
        return;
    }
    queue<Binary_Tree<E>*> q;
    Binary_Tree<E>* p = root;
    q.push(p);
    while (!q.empty())
    {
        p = q.front();
        q.pop();
        visit(p);
        if (p->lchild)
        {
            q.push(p->lchild);
        }
        if (p->rchild)
        {
            q.push(p->rchild);
        }
    }
}