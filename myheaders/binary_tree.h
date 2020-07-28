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
 ջ�г�ʼѹ���ָ����Ϊ����
1�����ʵ�ǰջ��ָ��p����Ϊ�ս���������
2��������data
3�����Һ��Ӳ�Ϊ�գ������ջ�к�������
4�������Ӳ�Ϊ�գ�������Ϊ�µĵ�ǰջ��ָ�룬��p=p->lchild��ת1
5����ջ��ȡָ�븳��p����p=stack.top();stack.pop()��ת1
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
 ջ�д�������Ѿ�������Ľ�㣬
 1��ջ��ָ�벻������ջ������������ȥ�������ӣ������ջ������������Һ��ӣ�ָ��ָ�����ӣ�ת1������ת2
 2��ջ��ָ�����Һ��ӣ����������Ȼ��ָ���Һ��ӣ�from_stack��false��ת1������ת3
 3������������ջ�ǿ���ջ��ָ��ȡջ����������from_stackΪtrue��ת1.�������
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
 ����˳������-�Һ���-���ӣ�����ǰ�������ջ�У��ٱ���ջ���෴˳������-�Һ���-����ĺ������
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

// �������ջ�Ľ�㶨��
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

// ��α���
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