#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 210;
const int INF = 0x7fffffff;
int sum[N];
int a[N];
int maxx[N][N];
int minn[N][N];
int main()
{
    int n;
    cin >> n;
    memset(maxx, INF, sizeof(maxx));
    memset(minn, -INF, sizeof(minn));
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        a[i + n] = a[i]; //循环的需要
    }
    //前缀和
    for (int i = 1; i <= 2 * n; i++)
    {
        maxx[i][i] = 0;
        minn[i][i] = 0; //到自身的距离为0
        sum[i] = sum[i - 1] + a[i];
    }
    //核心代码
    for (int len = 2; len <= n; len++) //长度的选择，如果长度为1的话，就是它自己，所以不需要合并
    {
        for (int i = 1; i + len - 1 <= 2 * n; i++) //左端点起点的所以可能
        {
            int j = i + len - 1; // len长度右端点
            for (int k = i; k < j; k++)
            {
                //找到分别最优解，不断叠加前一状态
                minn[i][j] = min(minn[i][j], minn[i][k] + minn[k + 1][j] + sum[j] - sum[i - 1]);
                maxx[i][j] = max(maxx[i][j], maxx[i][k] + maxx[k + 1][j] + sum[j] - sum[i - 1]);
            }
        }
    }
    int ma = -INF;
    int mn = INF;
    for (int i = 1; i <= 2 * n; i++) //找到长度为n的最大值
    {
        ma = max(ma, maxx[i][i + n - 1]);
        mn = min(mn, minn[i][i + n - 1]);
    }
    cout << mn << endl;
    cout << ma << endl;
    return 0;
}
// INF为0x3f3f3f3f莫名算不出最大值，就很神奇，可能是卡了数据带点，必须得要0x7fffffff来表示int里面的最大值
//环状区间dp首先看成2倍长度，化曲为直。找到中间状态点k以及左右端点，分析端点以及状态表示