코드
```cpp
int n, m;
vector<int> leaf = { 0 };
vector<int> tree[1 << 18];
const int sz = 1 << 17;

void add(int x, int v)
{
	x += sz; 
	tree[x].push_back(v);
}

void build()
{
	for (int i = 1; i <= n; i++)
	{
		add(i, leaf[i]);
	}
	for (int i = sz - 1; i; i--)
	{
		tree[i].resize(tree[i * 2].size() + tree[i * 2 + 1].size());
		merge(all(tree[i*2]), all(tree[i*2+1]), tree[i].begin());
	}
}

int query(int f, int s, int k)
{
	f += sz; s += sz;
	int ans = 0;
	while (f <= s)
	{
		if (f % 2 != 0)
		{
			ans += tree[f].end() - upper_bound(all(tree[f]), k);
			f++;
		}
		if (s % 2 == 0)
		{
			ans += tree[s].end() - upper_bound(all(tree[s]), k);
			s--;
		}
		f /= 2; s /= 2;
	}
	return ans;
}
```
n : 최초 수열의 개수  
m : 쿼리의 수   <br>
**tree의 size와 sz정하는 법**
(log base2 n)의 값을 올림한 수를 k라 하자.  
size는 1<<k (2의 k제곱)  
sz는 1<<k-1 (2의 k-1제곱)
<br><br>
**쿼리 작성법**  
root가 tree[1]  
leaf는 tree[sz+1] ~ tree[sz+n] 에 위치  
자식 node탐색 : tree[cur*2] tree[cur*2+1]  
부모 node탐색 : tree[cur/2]
