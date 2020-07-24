#include <iostream>
#include <cstdio>

using namespace std;

void get_next_vector(string& pattern, int* next)
{
    int pattern_length = pattern.length();
    next[0] = -1;
    int j = 0, k = -1;
    while (j < pattern_length)
    {
        if (k == -1 || pattern.at(j) == pattern.at(k))
        {
            j++;
            k++;
            next[j] = k;
        }
        else
        {
            k = next[k];
        }
    }
}

int mykmp(string& target, string& pattern, int next[], int start)
{
    int len_t = target.length(), len_p = pattern.length();
    int current_base = start;
    int len_match = 0;
    while (current_base + len_p <= len_t)
    {
        while (len_match < len_p && target.at(current_base + len_match) == pattern.at(len_match))
        {
            ++len_match;
        }
        if (len_match == len_p)
        {
            return current_base;
        }
        else
        {
            current_base += len_match - next[len_match];
            len_match = max(next[len_match], 0);
        }
    }
    
    return -1;
}

int kmp(string& target, string& pattern, int next[], int start)
{
    int posP = 0, posT = start;
    int lengthP = pattern.length();
    int lengthT = target.length();
    while (posP < lengthP && posT < lengthT)
    {
        if (posP == -1 || pattern.at(posP) == target.at(posT))
        {
            posP++;
            posT++;
        }
        else
        {
            posP = next[posP];
        }
    }
    if (posP < lengthP) 
    {
        return -1;
    }
    return posT - lengthP;
}

int main()
{
    // string target = "acabaabaabcacaabc";
    // string pattern = "abaabcac";
    // int next[] = {-1,0,0,1,1,2,0,1};

    string target, pattern;
    cout << "请输入目标：\n";
    cin >> target;
    cout << "请输入模式：\n";
    cin >> pattern;
    int* next = new int[pattern.length()];

    get_next_vector(pattern, next);
    int pos = mykmp(target, pattern, next, 0);

    printf("匹配位置为：%d\n", pos);

    system("pause");
    return 0;
}