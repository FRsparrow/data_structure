#include <iostream>
#include "myheaders/sparse_matrix.h"

// using namespace std;

Sparse_matrix<int>* read_maxtrix()
{
    int row_num, col_num, ele_num;
    Sparse_matrix<int>* matrix;
    
    cout << "请输入矩阵行数、列数和三元组个数：\n";
    cin >> row_num >> col_num >> ele_num;
    matrix = new Sparse_matrix<int>(row_num, col_num, ele_num);
    cout << "请输入矩阵非零元素三元组，按格式row col value，回车隔开:\n";
    
    for (int i = 0; i < ele_num; i++)
    {
        cin >> matrix->elements[i].row >> matrix->elements[i].col >> matrix->elements[i].value;
    }
    // cout << "矩阵非零元个数：" << matrix->ele_num << endl;

    return matrix;
}

void show_matrix(Sparse_matrix<int>* matrix)
{
    // cout << "矩阵非零元个数：" << matrix->get_ele_num() << endl;
    int ele_num = matrix->get_ele_num();
    int row_num = matrix->get_row_num();
    int col_num = matrix->get_col_num();

    int** m = new int*[row_num];
    for (int i = 0; i < row_num; i++)
    {
        m[i] = new int[col_num];
        memset(m[i], 0, col_num * sizeof(int));
    }
    
    for (int i = 0; i < ele_num; i++)
    {
        m[matrix->elements[i].row][matrix->elements[i].col] = matrix->elements[i].value;
    }
    
    for (int i = 0; i < row_num; i++)
    {
        for (int j = 0; j < col_num; j++)
        {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
    
}

int main()
{
    auto matrix = read_maxtrix();
    auto matrix_t = new Sparse_matrix<int>(*matrix);    // 根据原矩阵生成转置矩阵
    cout << "原矩阵：\n";
    show_matrix(matrix);
    cout << "转置矩阵：\n";
    show_matrix(matrix_t);
    system("pause");
    return 0;
}