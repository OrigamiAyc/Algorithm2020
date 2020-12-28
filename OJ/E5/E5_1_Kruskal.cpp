#include <iostream>
#include <algorithm>
#include <cstring>

typedef long long ll;
using namespace std;

int n, m;	 //节点数，边数
int ans = 0; //最小生成树边权和
int tot = 0; //已经选取的边数
struct lq
{
	int x, y, z;
} f[1000000];
int pre[100010]; //并查集数组

bool cmp(lq a, lq b)
{
	return a.z < b.z;
}

int father(int x)
{ //查找根节点
	int root = x;
	while (pre[root] != -1)
	{
		root = pre[root];
	}
	return root;
}

bool un(int x, int y)
{
	int x_root = father(x);
	int y_root = father(y);
	if (x_root == y_root)
	{
		return 0;
	}
	else
	{
		pre[x_root] = y_root;
		return 1;
	}
}

int main()
{
	memset(pre, -1, sizeof(pre)); //数组清零
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> f[i].x >> f[i].y >> f[i].z;
	}					 //读入数据
	sort(f, f + m, cmp); //以z的大小为标准进行升序排序
	for (int i = 0; i < m; i++)
	{ //依次取出权值最小的边
		if (un(f[i].x, f[i].y))
		{				   //如果该边的两个结点不在一个集合中，即添加该边未产生回路
			ans += f[i].z; //加入边权值
			tot++;		   //边数加一
			if (tot == n - 1)
			{ //当边数为n-1时，输出权值和
				cout << ans << endl;
				return 0;
			}
		}
	}
	cout << "infinty" << endl; //出循环则tot<n-1，即该图不连通，输出inf
	return 0;
}
