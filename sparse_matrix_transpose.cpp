#include <iostream>
#include "myheaders/sparse_matrix.h"

// using namespace std;

Sparse_matrix<int>* read_maxtrix()
{
    int row_num, col_num, ele_num;
    Sparse_matrix<int>* matrix;
    
    cout << "�����������������������Ԫ�������\n";
    cin >> row_num >> col_num >> ele_num;
    matrix = new Sparse_matrix<int>(row_num, col_num, ele_num);
    cout << "������������Ԫ����Ԫ�飬����ʽrow col value���س�����:\n";
    
    for (int i = 0; i < ele_num; i++)
    {
        cin >> matrix->elements[i].row >> matrix->elements[i].col >> matrix->elements[i].value;
    }
    // cout << "�������Ԫ������" << matrix->ele_num << endl;

    return matrix;
}

void show_matrix(Sparse_matrix<int>* matrix)
{
    // cout << "�������Ԫ������" << matrix->get_ele_num() << endl;
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
    auto matrix_t = new Sparse_matrix<int>(*matrix);    // ����ԭ��������ת�þ���
    cout << "ԭ����\n";
    show_matrix(matrix);
    cout << "ת�þ���\n";
    show_matrix(matrix_t);
    system("pause");
    return 0;
}