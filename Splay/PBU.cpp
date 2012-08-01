#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef int					Data;
typedef struct TNode		TreeNode;	

struct TNode
{
	TreeNode *left, *right, *father;
	int count;
	Data key;
};

struct Tsplay
{
	TreeNode *Root;

	void clear()
	{
		Root = NULL;
	}

	/*
	void left_rotate(TreeNode *x)
	{
		TreeNode *y = x -> father;
		TreeNode *z = x -> left;
		if (y == y -> father -> left)
			y -> father -> left = x;
		else
			y -> father -> right = x;

		x -> father = y -> father;
		x -> left = y;
		y -> right = z;
		y -> father = x;
		z -> father = y;
	}

	void right_rotate(TreeNode *x)
	{
		TreeNode *y = x -> father;
		TreeNode *z = x -> right;
		if (y == y -> father -> left)
			y -> father -> left = x;
		else
			y -> father -> right = x;

		x -> father = y -> father;
		x -> right = y;
		y -> left = z;
		y -> father = x;
		z -> father = y;
	}
	*/

	TreeNode * splay(TreeNode *x)
	{
		if (x == NULL) return NULL;
		while (x -> father != NULL)
		{
			TreeNode *y = x -> father;
			TreeNode *z = y -> father;
			if (z == NULL)
			{
				if (x == y -> left)
				{
					x -> father = NULL;	
					if (x -> right != NULL)
						x -> right -> father = y;
					y -> father = x;

					y -> left = x -> right;
					x -> right = y;
					//right_rotate(x);
				}
				else
				{
					x -> father = NULL;
					if (x -> left != NULL)
						x -> left -> father = y;
					y -> father = x;

					y -> right = x -> left;
					x -> left = y;
					//left_rotate(x);
				}
			}
			else
			{
				if (x == y -> left)
				{
					if (y == z -> left)
					{
						if (z -> father != NULL)
						{
							if (z == z -> father -> left)
								z -> father -> left = x;
							else
								z -> father -> right = x;
						}
						x -> father = z -> father;
						y -> father = x;
						z -> father = y;
						if (x -> right != NULL)
							x -> right -> father = y;
						if (y -> right != NULL)
							y -> right -> father = z;

						y -> left = x -> right;
						z -> left = y -> right;
						x -> right = y;
						y -> right = z;

						//right_rotate(y);
						//right_rotate(x);
					}
					else
					{
						if (z -> father != NULL)
						{
							if (z == z -> father -> left)
								z -> father -> left = x;
							else
								z -> father -> right = x;
						}
						x -> father = z -> father;
						y -> father = z -> father = x;
						if (x -> right != NULL)
							x -> right -> father = y;
						if (x -> left != NULL)
							x -> left -> father = z;

						y -> left = x -> right;
						z -> right = x -> left;
						x -> left = z;
						x -> right = y;

						//right_rotate(x);
						//left_rotate(x);
					}
				}
				else
				{
					if (y == z -> left)
					{
						if (z -> father != NULL)
						{
							if (z == z -> father -> left)
								z -> father -> left = x;
							else
								z -> father -> right = x;
						}
						x -> father = z -> father;
						y -> father = z -> father = x;
						if (x -> left != NULL)
							x -> left -> father = y;
						if (x -> right != NULL)
							x -> right -> father = z;

						y -> right = x -> left;
						z -> left = x -> right;
						x -> left = y;
						x -> right = z;

						//left_rotate(x);
						//right_rotate(x);
					}
					else
					{
						if (z -> father != NULL)
						{
							if (z == z -> father -> left)
								z -> father -> left = x;
							else
								z -> father -> right = x;
						}
						x -> father = z -> father;
						y -> father = x;
						z -> father = y;
						if (x -> left != NULL)
							x -> left -> father = y;
						if (y -> left != NULL)
							y -> left -> father = z;

						y -> right = x -> left;
						z -> right = y -> left;
						x -> left = y;
						y -> left = z;

						//left_rotate(y);
						//left_rotate(x);
					}
				}
			}
		}
		return x;
	}

	TreeNode * find(TreeNode *x, Data key)
	{
		if (x == NULL) return NULL;
		while (x -> key != key)
			if (key < x -> key)
			{
				if (x -> left == NULL) break;
				x = x -> left;
			}
			else
			{
				if (x -> right == NULL) break;
				x = x -> right;
			}
		return x;
	}

	bool exist(Data key)
	{
		if (Root == NULL) return false;
		TreeNode *x = find(Root, key);
		Root = splay(x);
		return (x -> key == key);
	}

	TreeNode * maximum(TreeNode *x)
	{
		if (x == NULL) return NULL;
		while (x -> right != NULL)
			x = x -> right;
		Root = splay(x);
		return Root;
	}

	TreeNode * minimum(TreeNode *x)
	{
		if (x == NULL) return NULL;
		while (x -> left != NULL)
			x = x -> left;
		Root = splay(x);
		return Root;
	}

	TreeNode * join(TreeNode *x1, TreeNode *x2)
	{
		if (x1 == NULL) return x2;
		if (x2 == NULL) return x1;
		TreeNode *x = maximum(x1);
		x -> right = x2;
		x2 -> father = x;
		return x;
	}

	void split(TreeNode *x, TreeNode * &left, TreeNode * &right)
	{
		left = Root = splay(x);
		right = Root -> right;
		right -> father = NULL;
		Root -> right = NULL;
	}

	void insert(Data key)
	{
		if (exist(key))
		{
			++ (Root -> count);
			return;
		}
		TreeNode *New = (TreeNode *)malloc(sizeof(TreeNode));
		New -> key = key; New -> count = 1;
		New -> left = New -> right = New -> father = NULL;

		if (Root == NULL)
		{
			Root = New;
			return;
		}
		if (key < Root -> key)
		{
			New -> left = Root -> left;
			if (New -> left != NULL)
				New -> left -> father = New;
			Root -> left = NULL;
			New -> right = Root;
		}
		else
		{
			New -> right = Root -> right;
			if (New -> right != NULL)
				New -> right -> father = New;
			Root -> right = NULL;
			New -> left = Root;
		}
		Root -> father = New;
		Root = New;
	}

	void remove(Data key)
	{
		if (!exist(key)) return;

		if (Root -> count > 1)
		{
			-- (Root -> count);
			return;
		}

		TreeNode *left = Root -> left;
		TreeNode *right = Root -> right;

		if (left != NULL)
			left -> father = NULL;
		if (right != NULL)
			right -> father = NULL;
		free(Root);

		Root = join(left, right);
	}

	TreeNode * prev(TreeNode *x)
	{
		Root = splay(x);
		for (x = x -> left; x != NULL; x = x -> right);
		return x;
	}


	TreeNode * succ(TreeNode *x)
	{
		Root = splay(x);
		for (x = x -> right; x != NULL; x = x -> left);
		return x;
	}

	bool empty()
	{
		return (Root == NULL);
	}

	/*
	void dfs(TreeNode *x)
	{
		if (x == NULL) return;
		printf("key = %d, left = %d, right %d\n", x -> key, (x -> left == NULL) ? 0 : x -> left -> key, (x -> right == NULL) ? 0 : x -> right -> key);
		dfs(x -> left);
		dfs(x -> right);
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
				printf("%d\n", set.maximum(set.Root) -> key);
		}
		else if (operation == 4)
		{
			if (set.empty())
				printf("NULL\n");
			else
				printf("%d\n", set.minimum(set.Root) -> key);
		}
	}
	return 0;
}

