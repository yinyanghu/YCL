#include <cstdio>
#include <cstring>
#include <cstdlib>

#define infinity 1000000000


typedef int					Data;
typedef struct TNode		TreeNode;

struct TNode
{
	TreeNode *left, *right;
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
	
	TreeNode * splay(TreeNode *x, Data key)
	{
		if (x == NULL) return NULL;

		//TreeNode Splay_left, Splay_right;
		TreeNode Split;
		TreeNode *Cur_left, *Cur_right;
		
		//Splay_left.left = Splay_left.right = Splay_right.left = Splay_right.right = 0;
		Split.left = Split.right = NULL;
		/*
		Cur_left = Split.left;
		Cur_right = Split.right;
		*/
		Cur_left = Cur_right = &Split;
		
		for (;;)
		{
			if (key < x -> key)
			{
				if (x -> left == NULL) break;
				if (key < x -> left -> key)		/* rotate right */
				{
					TreeNode *y = x -> left;
					x -> left = y -> right;
					y -> right = x;
					x = y;
					if (x -> left == NULL) break;
				}

				/* link right */
				Cur_right -> left = x;
				Cur_right = x;
				x = x -> left;
			}
			else if (key > x -> key)
			{
				if (x -> right == NULL) break;
				if (key > x -> right -> key)		/* rotate left */
				{
					TreeNode *y = x -> right;
					x -> right = y -> left;
					y -> left = x;
					x = y;
					if (x -> right == NULL) break;
				}
				
				/* link left */
				Cur_left -> right = x;
				Cur_left = x;
				x = x -> right;
			}
			else break;
		}

		/* assemble */
		Cur_left -> right = x -> left;
		Cur_right -> left = x -> right;
		x -> left = Split.right;				//inverse
		x -> right = Split.left;
		return x;
	}

	/* return 0, if the tree is empty */
	TreeNode * find(TreeNode *x, Data key)
	{
		Root = splay(x, key);
		return Root;
	}

	TreeNode * maximum(TreeNode *x)
	{
		if (x == NULL) return NULL;
		Root = splay(x, infinity);
		return Root;
	}

	TreeNode * minimum(TreeNode *x)
	{
		if (x == NULL) return NULL;
		Root = splay(x, -infinity);
		return Root;
	}

	TreeNode * join(TreeNode *x1, TreeNode *x2)
	{
		if (x1 == NULL) return x2;
		if (x2 == NULL) return x1;
		TreeNode *x = maximum(x1);
		x -> right = x2;
		return x;
	}

	void split(TreeNode *x, TreeNode * &left, TreeNode * &right)
	{
		left = Root = splay(Root, x -> key);
		right = Root -> right;
		Root -> right = NULL;
	}

	bool exist(Data key)
	{
		if (Root == NULL) return false;
		Root = splay(Root, key);
		return (Root -> key == key);
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
		New -> left = New -> right = NULL;

		if (Root == NULL)
		{
			Root = New;
			return;
		}

		if (key < Root -> key)
		{
			New -> left = Root -> left;
			Root -> left = NULL;
			New -> right = Root;
		}
		else
		{
			New -> right = Root -> right;
			Root -> right = NULL;
			New -> left = Root;
		}

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

		free(Root);

		Root = join(left, right);
	}


	bool empty()
	{
		return (Root == 0);
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

