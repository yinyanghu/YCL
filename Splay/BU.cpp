#include <cstdio>
#include <cstring>
#define infinity 1000000000
#define limitsize 5000000
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
	
	/*
	void left_rotate(int x)
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
	}
	
	void right_rotate(int x)
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
	}
	*/
	
	void splay(int x)
	{
		if (x == 0) return;
		while (tree[x].father != 0)
		{
			int y = tree[x].father, z = tree[y].father;
			if (z == 0)
			{
				if (x == tree[y].left)
				{
					tree[x].father = 0;	
					if (tree[x].right != 0)
						tree[tree[x].right].father = y;
					tree[y].father = x;

					tree[y].left = tree[x].right;
					tree[x].right = y;

					//right_rotate(x);
				}
				else
				{
					tree[x].father = 0;
					if (tree[x].left != 0)
						tree[tree[x].left].father = y;
					tree[y].father = x;

					tree[y].right = tree[x].left;
					tree[x].left = y;

					//left_rotate(x);
				}
			}
			else
			{
				if (x == tree[y].left)
				{
					if (y == tree[z].left)
					{
						if (z == tree[tree[z].father].left)
							tree[tree[z].father].left = x;
						else
							tree[tree[z].father].right = x;

						tree[x].father = tree[z].father;
						tree[y].father = x;
						tree[z].father = y;

						if (tree[x].right != 0)
							tree[tree[x].right].father = y;

						if (tree[y].right != 0)
							tree[tree[y].right].father = z;

						tree[y].left = tree[x].right;
						tree[z].left = tree[y].right;
						tree[x].right = y;
						tree[y].right = z;

						//right_rotate(y);
						//right_rotate(x);
					}
					else
					{
						if (z == tree[tree[z].father].left)
							tree[tree[z].father].left = x;
						else
							tree[tree[z].father].right = x;

						tree[x].father = tree[z].father;
						tree[y].father = tree[z].father = x;

						if (tree[x].right != 0)
							tree[tree[x].right].father = y;
						if (tree[x].left != 0)
							tree[tree[x].left].father = z;

						tree[y].left = tree[x].right;
						tree[z].right=  tree[x].left;
						tree[x].left = z;
						tree[x].right = y;

						//right_rotate(x);
						//left_rotate(x);
					}
				}
				else
				{
					if (y == tree[z].left)
					{
						if (z == tree[tree[z].father].left)
							tree[tree[z].father].left = x;
						else
							tree[tree[z].father].right = x;

						tree[x].father = tree[z].father;
						tree[y].father = tree[z].father = x;

						if (tree[x].left != 0)
							tree[tree[x].left].father = y;
						if (tree[x].right != 0)
							tree[tree[x].right].father = z;

						tree[y].right = tree[x].left;
						tree[z].left = tree[x].right;
						tree[x].left = y;
						tree[x].right = z;
						//left_rotate(x);
						//right_rotate(x);
					}
					else
					{
						if (z == tree[tree[z].father].left)
							tree[tree[z].father].left = x;
						else
							tree[tree[z].father].right = x;

						tree[x].father = tree[z].father;
						tree[y].father= x;
						tree[z].father = y;
						if (tree[x].left != 0)
							tree[tree[x].left].father = y;
						if (tree[y].left != 0)
							tree[tree[y].left].father = z;

						tree[y].right = tree[x].left;
						tree[z].right = tree[y].left;
						tree[x].left = y;
						tree[y].left = z;
						//left_rotate(y);
						//left_rotate(x);
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

	bool exist(Data key)
	{
		if (root == 0) return false;
		int x = find(root, key);
		//if (x == 0) return false;
		splay(x);
		return (tree[x].key == key);
	}

	int maximum(int x)
	{
		//splay(find(x, infinity));
		if (x == 0) return 0;
		while (tree[x].right != 0)
			x = tree[x].right;
		splay(x);
		return root;
	}
	
	int minimum(int x)
	{
		//splay(find(x, -infinity));
		if (x == 0) return 0;
		while (tree[x].left != 0)
			x = tree[x].left;
		splay(x);
		return root;
	}
	
	/* return the root of the joined tree */
	int join(int x1, int x2)
	{
		if (x1 == 0) return x2;
		if (x2 == 0) return x1;
		int x = maximum(x1);
		tree[x].right = x2; tree[x2].father = x;
		return x;
	}	


	/* subtree x1: <= x, subtree x2: > x */
	void split(int x, int &x1, int &x2)					
	{
		splay(x);
		x1 = root;
		tree[x2 = tree[root].right].father = 0; tree[root].right = 0;
	}

	/* delete the root, and split two subtrees */
	/*
	void split_with_delete(int x, int &x1, int &x2)			
	{
		splay(x);
		tree[x1 = tree[x].left].father = 0; tree[root].left = 0;
		tree[x2 = tree[x].right].father = 0; tree[root].right = 0;
	}
	*/
	
	void insert(Data key)
	{
		if (exist(key))
		{
			++ tree[root].count;
			return;
		}
		tree[++ top].key = key; tree[top].count = 1;
		tree[top].left = tree[top].right = tree[top].father = 0;
		if (root == 0)
		{
			root = top;
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
		root = top;
	}
	
	
	void remove(Data key)
	{

		if (!exist(key)) return;

		if (tree[root].count > 1)
		{
			-- tree[root].count;
			return;
		}		

		/* split and join */
		int x1 = tree[root].left;
		int x2 = tree[root].right;

		tree[x1].father = tree[x2].father = 0;
		tree[root].left = tree[root].right = 0;

		root = join(x1, x2);

		/*
			Search for the node containing key. Let this node be x and let its parent be y.
			Replace x as a child of y by the join of the left and right subtrees of x, and then splay at y.
			Special Case: x is root or x is the only node in the tree.
		*/

		/*
		int x = find(root, key);
		if (x == 0 || tree[x].key != key) return;
		
		if (tree[x].count > 1)
		{
			-- tree[x].count;
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
			splay(y);
		}
		*/

	}

	int prev(int x)
	{
		splay(x);
		for (x = tree[x].left; x != 0; x = tree[x].right);
		return x;
		//if (tree[x].left == 0) return 0;
		//return maximum(tree[x].left);
	}
	
	int succ(int x)
	{
		splay(x);
		for (x = tree[x].right; x != 0; x = tree[x].left);
		return x;
		//if (tree[x].right == 0) return 0;
		//return minimum(tree[x].right);
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
			return;
		}

		int s1, s2;
		split_with_delete(x, s1, s2);
		root = join(s1, s2);
	}
	*/
