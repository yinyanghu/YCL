#include <cstdio>
#include <set>
using namespace std;

multiset<int> tree;

int main()
{
	freopen("in", "r", stdin);
	freopen("std", "w", stdout);
	tree.clear();
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
			tree.clear();
		}
		*/
		else if (operation == 0)
		{
			int key;
			scanf("%d", &key);
			tree.insert(key);
		}
		else if (operation == 1)
		{
			int key;
			scanf("%d", &key);
			multiset<int>::iterator it = tree.find(key);
			if (it != tree.end())
			{
				tree.erase(it);
				printf("OK\n");
			}
			else
				printf("Delete Error\n");
		}
		else if (operation == 2)
		{
			int key;
			scanf("%d", &key);
			multiset<int>::iterator it = tree.find(key);
			if (it != tree.end())
				printf("Yes\n");
			else
				printf("No\n");
		}
		/*
		else if (operation == 4)
		{
			int key;
			scanf("%d", &key);
			multiset<int>::iterator it = tree.find(key);
			if (it != tree.end())
			{
				-- it;
				printf("%d\n", *it);
			}
			else
				printf("Prev Error!\n");
		}
		else if (operation == 5)
		{
			int key;
			scanf("%d", &key);
			multiset<int>::iterator it = tree.find(key);
			if (it != tree.end())
			{
				++ it;
				printf("%d\n", *it);
			}
			else
				printf("Succ Error!\n");
		}
		*/
		else if (operation == 3)
		{
			if (tree.empty())
				printf("NULL\n");
			else
			{
				multiset<int>::reverse_iterator it = tree.rbegin();
				printf("%d\n", *it);
			}
		}
		else if (operation == 4)
		{
			if (tree.empty())
				printf("NULL\n");
			else
			{
				multiset<int>::iterator it = tree.begin();
				printf("%d\n", *it);
			}
		}
	}
	return 0;
}
