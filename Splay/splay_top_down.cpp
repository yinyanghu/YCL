#include <cstdio>
#include <cstring>
#define limitsize 10000
#define infinity 1000000000
typedef int Data;
struct TreeNode
{
	int left, right;
	int count;
	Data key;
};

struct Tsplay
{
	int root, top;
	TreeNode tree[limitsize];
	
	void clear()
	{
		root = top = 0;
		memset(tree, 0, sizeof(tree));
	}
	
	inline void update(int x)
	{
		
	}
	
	void splay(Data key, int x)
	{
		if (x == 0) return;
		TreeNode Splay_left, Splay_right;
		int Cur_left, Cur_right;
		
		Splay_left.left = Splay_left.right = Splay_right.left = Splay_right.right = 0;
		Cur_left = Cur_right = 0;
		
		for (;;)
		{
			if (key < tree[x].key)
			{
				if (tree[x].left == 0) break;
				if (key < tree[tree[x].left].key)
				{
					int y = tree[x].left; tree[x].left = tree[y].right; tree[y].right = x; x = y;
					if (tree[x].left == 0) break;
				}
				Splay_right.left = x;
				Cur_right = x;
				x = tree[x].left;
			}
			else if (key > tree[x].key)
			{
				if (tree[x].right == 0) break;
				if (key > tree[tree[x].right].key)
				{
					int y = tree[x].right; tree[x].right = tree[y].left; tree[y].left = x; x = y;
					if (tree[x].right == 0) break;
				}
				Splay_left.right = x;
				Cur_left = x;
				x = tree[x].right;
			}
			else break;
		}
		
	}
	
};


int main()
{
	
	return 0;
}

