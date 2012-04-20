#include <cstdio>
#include <cstring>
#define infinity 1000000000
#define limitsize 1000000
typedef int Data;
struct TreeNode
{
	int left, right, father;
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
		
	inline void left_rotate(int x)
	{
		int y = tree[x].father, z = tree[x].left;
		if (y == tree[tree[y].father].left)
			tree[tree[y].father].left = x;
		else
			tree[tree[y].father].right = x;
		tree[x].father = tree[y].father;
		tree[x].left = y;
		tree[y].right = z;
		tree[y].father = x;
		tree[z].father = y;
		
		update(y); update(x);
	}
	
	inline void right_rotate(int x)
	{
		int y = tree[x].father, z = tree[x].right;
		if (y == tree[tree[y].father].left)
			tree[tree[y].father].left = x;
		else
			tree[tree[y].father].right = x;
		tree[x].father = tree[y].father;
		tree[x].right = y;
		tree[y].left = z;
		tree[y].father = x;
		tree[z].father = y;
		
		update(y); update(x);
	}
	
	void splay(int x)
	{
		while (tree[x].father)
		{
			int y = tree[x].father, z = tree[y].father;
			if (z == 0)
			{
				if (x == tree[y].left)
					right_rotate(x);
				else
					left_rotate(x);
			}
			else
			{
				if (x == tree[y].left)
				{
					if (y == tree[z].left)
					{
						right_rotate(y);
						right_rotate(x);
					}
					else
					{
						right_rotate(x);
						left_rotate(x);
					}
				}
				else
				{
					if (y == tree[z].left)
					{
						left_rotate(x);
						right_rotate(x);
					}
					else
					{
						left_rotate(y);
						left_rotate(x);
					}
				}
			}
			
		}
		root = x;
	}
	
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

	int maximum(int x)
	{
		splay(find(x, infinity));
		return root;
	}
	
	int minimum(int x)
	{
		splay(find(x, -infinity));
		return root;
	}
	
	int join(int x1, int x2)
	{
		if (x1 == 0) return x2;
		if (x2 == 0) return x1;
		int x = maximum(x1);
		tree[x].right = x2; tree[x2].father = x;
		update(root);
		return root;
	}	

	void split(int x, int &x1, int &x2)					//subtree x1: <= x, subtree x2: > x
	{
		splay(x);
		x1 = x;
		tree[x2 = tree[x].right].father = 0; tree[root].right = 0;
	}
	
	void split_with_delete(int x, int &x1, int &x2)			//delete the root, and split two subtrees
	{
		splay(x);
		tree[x1 = tree[x].left].father = 0; tree[root].left = 0;
		tree[x2 = tree[x].right].father = 0; tree[root].right = 0;
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
		tree[top].left = tree[top].right = tree[top].father = 0;
		if (root == 0)
		{
			root = top;
			update(root);
			return;
		}
		if (key < tree[root].key)
		{
			tree[top].left = tree[root].left;
			if (tree[top].left != 0)
				tree[tree[top].left].father = top;
			tree[root].left = 0;
			tree[top].right = root;
		}
		else
		{
			tree[top].right = tree[root].right;
			if (tree[top].right != 0)
				tree[tree[top].right].father = top;
			tree[root].right = 0;
			tree[top].left = root;
		}
		tree[root].father = top;
		update(root);
		root = top;
		update(root);
	}
	
	
	void remove(Data key)
	{
		/*
			Search for the node containing key. Let this node be x and let its parent be y.
			Replace x as a child of y by the join of the left and right subtrees of x, and then splay at y
			Special Case: x is root or x is the only node in the tree
		*/
		int x = find(root, key);
		if (x == 0 || tree[x].key != key) return;
		if (tree[x].count > 1)
		{
			-- tree[x].count;
			update(x);
			splay(x);
			return;
		}		
		int y = tree[x].father;
		tree[tree[x].left].father = tree[tree[x].right].father = 0;
		int z = join(tree[x].left, tree[x].right);
		tree[z].father = y;
		if (y == 0)
		{
			root = z;
		}
		else
		{
			if (x == tree[y].left)
				tree[y].left = z;
			else
				tree[y].right = z;
			update(y);
			splay(y);
		}
		
	}

	int prev(int x)
	{
		splay(x);
		if (tree[x].left == 0) return x;
		return maximum(tree[x].left);
	}
	
	int succ(int x)
	{
		splay(x);
		if (tree[x].right == 0) return x;
		return minimum(tree[x].right);
	}
	
	bool exist(Data key)
	{
		int x = find(root, key);
		if (x == 0) return false;
		splay(x);
		return (tree[x].key == key);
	}
	
	bool empty()
	{
		return (root == 0);
	}
	
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

	/*


	*/

	/*
	void remove(Data key)						//remove: split and join
	{
		int x = find(root, key);
		if (key != tree[x].key) return;
		if (tree[x].count > 1)

		{
			-- tree[x].count;
			update(x);
			return;
		}

		int s1, s2;
		split_with_delete(x, s1, s2);
		root = join(s1, s2);
	}
	*/
