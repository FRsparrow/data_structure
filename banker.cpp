#include <iostream>
#include <cwchar>
#include <string.h>

using namespace std;

const int rn = 3, pn = 5;

//系统可用（剩余）资源
int available[rn]={3,3,2};
//进程的最大需求
int max_request[pn][rn]={{7,5,3},
                         {3,2,2},
                         {9,0,2},
                         {2,2,2},
                         {4,3,3}};
//进程已经占有（分配）资源
int allocation[pn][rn]={{0,1,0},
                        {2,0,0},
                        {3,0,2},
                        {2,1,1},
                        {0,0,2}};
//进程还需要资源
int need[pn][rn]={{7,4,3},
                  {1,2,2},
                  {6,0,0},
                  {0,1,1},
                  {4,3,1}};
//是否安全
bool finish[pn];
//安全序列号
int safe_series[pn]={0,0,0,0,0};
//进程请求资源量
int request[rn];

int pid;

bool check_request()
{
    for (int i = 0; i < rn; i++)
    {
        if (request[i] > need[pid][i])
        {
            return false;
        }
    }
    return true;
}

bool check_available()
{
    for (int i = 0; i < rn; i++)
    {
        if (request[i] > available[i])
        {
            return false;
        }
    }
    return true;
}

bool check_satisfiable(int p_id, int *temp_available)
{
    for (int i = 0; i < rn; i++)
    {
        if (need[p_id][i] > temp_available[i])
        {
            return false;
        }
    }
    return true;
}

bool check_safe()
{
    int temp_available[rn];

    memcpy(temp_available, available, rn*sizeof(int));
    memset(finish, false, pn*sizeof(bool));

    for (int i = 0; i < rn; i++)
    {
        temp_available[i] -= request[i];
        allocation[pid][i] += request[i];
        need[pid][i] -= request[i];
    }

    int count = 0;
    int safe_sequence[pn];
    while (true)
    {
        bool one_satisfied = false;
        int i = pid;
        do
        {
            if (!finish[i] && check_satisfiable(i, temp_available))
            {
                for (int j = 0; j < rn; j++)
                {
                    temp_available[j] += allocation[i][j];
                }
                finish[i] = true;
                safe_sequence[count++] = i;
                one_satisfied = true;
            }
            i = (i + 1) % pn;
        } while (i != pid);
        if (count == pn)
        {
            cout << "safe, the safe sequence is: ";
            for (int j = 0; j < count; j++)
            {
                cout << safe_sequence[j] << " ";
            }
            cout << endl;
            return true;
        }
        if (!one_satisfied)
        {
            return false;
        }
    }
}

bool banker_algorithm()
{
    if (!check_request())
    {
        cout << "process " << pid << " requests too many resources!\n";
        return false;
    }
    if (!check_available())
    {
        cout << "there are not enough avaible resources!\n";
        return false;
    }
    if (!check_safe())
    {
        for (int i = 0; i < rn; i++)
        {
            available[i] += request[i];
            allocation[pid][i] -= request[i];
            need[pid][i] += request[i];
        }
        cout << "the request may cause danger, please wait.\n";
        return false;
    }
    else
    {
        cout << "allocate resources successfully!\n";
        return true;
    }
}

void set()
{
    pid = 4;
    request[0] = 4;
    request[1] = 3;
    request[2] = 1;
}

int main()
{
    set();
    banker_algorithm();

    system("pause");
    return 0;
}