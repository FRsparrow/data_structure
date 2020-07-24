#include <memory.h>
#include "../myheaders/triple.h"

template<typename E>
class Sparse_matrix
{
private:
    int row_num;
    int col_num;
    int ele_num;
    
public:
    Triple<E>* elements;

    Sparse_matrix(Sparse_matrix<E>& matrix_t);
    Sparse_matrix(int rn, int cn, int en);
    ~Sparse_matrix();

    int get_row_num(){ return row_num; }
    int get_col_num(){ return col_num; }
    int get_ele_num(){ return ele_num; }
    void transpose(Sparse_matrix& b);
};

template<typename E>
Sparse_matrix<E>::Sparse_matrix(int rn, int cn, int en)
{
    row_num = rn;
    col_num = cn;
    ele_num = en;
    elements = new Triple<E>[ele_num];
}

template<typename E>
Sparse_matrix<E>::~Sparse_matrix()
{
    delete elements;
}

// 快速转置
template<typename E>
void Sparse_matrix<E>::transpose(Sparse_matrix& B)
{
    int* b_row_size = new int[col_num];     // 转置矩阵B每行的元素个数
    int* b_row_start = new int[col_num];    // 转置矩阵B每行元素在三元组数组中的起始位置

    memset(b_row_size, 0, col_num * sizeof(int));

    for (int i = 0; i < ele_num; i++)
    {
        ++b_row_size[elements[i].col];
    }

    b_row_start[0] = 0;
    for (int i = 1; i < col_num; i++)
    {
        b_row_start[i] = b_row_start[i-1] + b_row_size[i-1];
    }
    
    // cout << "数组：\n";
    // for (int i = 0; i < col_num; i++)
    // {
    //     cout << b_row_size[i] << "," << b_row_start[i] << endl;
    // }
    

    for (int i = 0; i < ele_num; i++)
    {
        int index = b_row_start[elements[i].col];
        B.elements[index].row = elements[i].col;
        B.elements[index].col = elements[i].row;
        B.elements[index].value = elements[i].value;
        ++b_row_start[elements[i].col];
        // cout << "第" << i << "行:" << B.elements[index];
    }
    
    delete b_row_size;
    delete b_row_start;
}

template<typename E>
Sparse_matrix<E>::Sparse_matrix(Sparse_matrix<E>& matrix_t)
{
    row_num = matrix_t.get_col_num();
    col_num = matrix_t.get_row_num();
    ele_num = matrix_t.get_ele_num();
    elements = new Triple<E>[ele_num];
    matrix_t.transpose(*this);
}