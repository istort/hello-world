/*
  牛牛新买了一本算法书，算法书一共有n页，页码从1到n。牛牛于是想了一个算法题目：在这本算法书页码中0~9每个数字分别出现了多少次？
  */
  
# include <bits/stdc++.h>
using namespace std;
int Count(int n, int x)
{
    int res = 0, j;
    for(int i = 1; j = n / i; i *= 10)
    {
        int high = j / 10;
        if(x == 0) // 0 是特别的
        {
            if(high)
                high--;
            else
                break;
        }
        res += high * i;
        int tem = j % 10;
        if(tem > x)
            res += i;
        else if(tem == x)
            res += n - j * i + 1;
    }
    return res;
}

int main()
{
    int n;
    cin >> n;
    cout << Count(n, 0);
    for (int i = 1; i <= 9; i++)
        cout << " " << Count(n, i);
    return 0;
}
