#include <cstdio>
#include <cstring>
#define limitsize 1000000
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
	
	void update(int x)
	{
		
	}
	
	void splay(int x, Data key)
	{
		if (x == 0) return;
		//TreeNode Splay_left, Splay_right;
		TreeNode Split;
		int Cur_left, Cur_right;
		
		//Splay_left.left = Splay_left.right = Splay_right.left = Splay_right.right = 0;
		Cur_left = Cur_right = 0;
		Split.left = Split.right = 0;
		
		for (;;)
		{
			if (key < tree[x].key)
			{
				if (tree[x].left == 0) break;
				if (key < tree[tree[x].left].key)		/* rotate right */
				{
					int y = tree[x].left; tree[x].left = tree[y].right; tree[y].right = x; x = y;
					if (tree[x].left == 0) break;
				}

				/* link right */
				if (Cur_right == 0)
					Split.right = x;
				else
					tree[Cur_right].left = x;

				Cur_right = x;
				x = tree[x].left;
				/*
				Splay_right.left = x;
				Cur_right = x;
				x = tree[x].left;
				*/
			}
			else if (key > tree[x].key)
			{
				if (tree[x].right == 0) break;
				if (key > tree[tree[x].right].key)		/* rotate left */
				{
					int y = tree[x].right; tree[x].right = tree[y].left; tree[y].left = x; x = y;
					if (tree[x].right == 0) break;
				}
				
				/* link left */
				if (Cur_left == 0)
					Split.left = x;
				else
					tree[Cur_left].right = x;

				Cur_left = x;
				x = tree[x].right;
				/*
				Splay_left.right = x;
				Cur_left = x;
				x = tree[x].right;
				*/
			}
			else break;
		}

		/* assemble */
		if (Cur_left != 0)
		{
			tree[Cur_left].right = tree[x].left;
			tree[x].left = Split.left;
		}
		if (Cur_right != 0)
		{
			tree[Cur_right].left = tree[x].right;
			tree[x].right = Split.right;
		}
		root = x;
	}

	/* return 0, if the tree is empty */
	int find(int x, Data key)
	{
		splay(x, key);
		return root;
	}

	int maximum(int x)
	{
		if (x == 0) return 0;
		splay(x, infinity);
		return root;
	}

	int minimum(int x)
	{
		if (x == 0) return 0;
		splay(x, -infinity);
		return root;
	}

	int join(int x1, int x2)
	{
		if (x1 == 0) return x2;
		if (x2 == 0) return x1;
		int x = maximum(x1);
		tree[x].right = x2;
		update(x);
		return x;
	}

	void split(int x, int &x1, int &x2)
	{
		splay(root, tree[x].key);
		x1 = root;
		x2 = tree[root].right;
		tree[root].right = 0;
	}

	bool exist(Data key)
	{
		if (root == 0) return false;
		splay(root, key);
		return (tree[root].key == key);
	}


	void insert(Data key)
	{
		if (exist(key))
		{
			++ tree[root].count;
			update(root);
			return;
		}

		tree[++ top].key = key; tree[top].count = 1;
		tree[top].left = tree[top].right = 0;

		if (root == 0)
		{
			root = top;
			update(root);
			return;
		}

		if (key < tree[root].key)
		{
			tree[top].left = tree[root].left;
			tree[root].left = 0;
			tree[top].right = root;
		}
		else
		{
			tree[top].right = tree[root].right;
			tree[root].right = 0;
			tree[top].left = root;
		}

		update(root);
		root = top;
		update(root);

	}

	void remove(Data key)
	{
		if (!exist(key)) return;

		if (tree[root].count > 1)
		{
			-- tree[root].count;
			update(root);
			return;
		}

		int x1 = tree[root].left;
		int x2 = tree[root].right;

		tree[root].left = tree[root].right = 0;

		root = join(x1, x2);
	}


	bool empty()
	{
		return (root == 0);
	}

	/*
	int find(int x, Data key)
	{
		if (x == 0) return 0;
		while (tree[x].key != key)
			if (key < tree[x].key)
			{
				if (tree[x].left == 0) break;
				x = tree[x].left;
			}
			else
			{
				if (tree[x].right == 0) break;
				x = tree[x].right;
			}
		return x;
	}
	*/
	
};

Tsplay set;

int main()
{
	freopen("in", "r", stdin);
	freopen("me", "w", stdout);
	set.clear();
	while (1)
	{
		int operation;
		scanf("%d", &operation);
		if (operation == -1)
		{
			return 0;
		}
		/*
		else if (operation == 0)
		{
			set.clear();
		}
		*/
		else if (operation == 0)
		{
			int key;
			scanf("%d", &key);
			set.insert(key);
		}
		else if (operation == 1)
		{
			int key;
			scanf("%d", &key);
			if (set.exist(key))
			{
				set.remove(key);
				printf("OK\n");
			}
			else
				printf("Delete Error\n");
		}
		else if (operation == 2)
		{
			int key;
			scanf("%d", &key);
			if (set.exist(key))
				printf("Yes\n");
			else
				printf("No\n");
		}
		/*
		else if (operation == 4)
		{
			int key;
			scanf("%d", &key);
			int x = set.find(set.root, key);
			if (set.tree[x].key == key)
				printf("%d\n", set.tree[set.prev(x)].key);
			else
				printf("Prev Error!\n");
		}
		else if (operation == 5)
		{
			int key;
			scanf("%d", &key);
			int x = set.find(set.root, key);
			if (set.tree[x].key == key)
				printf("%d\n", set.tree[set.succ(x)].key);
			else
				printf("Succ Error!\n");
		}
		*/
		else if (operation == 3)
		{
			if (set.empty())
				printf("NULL\n");
			else
				printf("%d\n", set.tree[set.maximum(set.root)].key);
		}
		else if (operation == 4)
		{
			if (set.empty())
				printf("NULL\n");
			else
				printf("%d\n", set.tree[set.minimum(set.root)].key);
		}
	}
	return 0;
}

