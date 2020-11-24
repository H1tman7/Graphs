
#include "Tree.h"

#define max(a,b) (((a) > (b)) ? (a) : (b))


struct __TreeNode {
	KeyType key;
	ValueType value;
	struct __TreeNode* left;
	struct __TreeNode* right;
};

static int COUNT = 0;


/*Private functions*/
static TreeNode* CreateAndInitTreeNode(KeyType key, ValueType value);
static bool InsertTreeNode(Tree* root, TreeNode* newNode);
static TreeNode* SearchTreeNode(Tree root, KeyType key);
static void PostOrderTraversal(Tree root, void (*action)(void*));
static void FreeTreeNode(void* root);
static Tree DeleteTreeNode(Tree root, KeyType key);
static TreeNode* LeftTreeNode(TreeNode* root);
static void DataTreeNodeCopy(TreeNode* dst, TreeNode* src);
static void IncrementCount(void* _);
static int HeightTree(Tree root);
static int DepthTreeNode(Tree root, KeyType key);


/*==================================
========= Public functions =========
==================================*/
Tree InitTree() {
	return (Tree)NULL;
}

bool InsertTreeValueByKey(Tree* root, KeyType key, ValueType value) {
	TreeNode* node = CreateAndInitTreeNode(key, value);
	return InsertTreeNode(root, node);
}

bool DeleteTreeNodeByKey(Tree* root, KeyType key) {
	Tree tree = *root;
	if (tree == (Tree)NULL) { return false; }

	if (tree->left == (TreeNode*)NULL && tree->right == (TreeNode*)NULL) {
		FreeTreeNode((void*)root);
		return true;
	}

	if (tree == DeleteTreeNode(tree, key)) { return false; }
	return true;
}

ValueType GetTreeValueByKey(Tree root, KeyType key) {
	if (root == (Tree)NULL) { return (ValueType)NULL; }

	TreeNode* node = SearchTreeNode(root, key);
	if (node == (TreeNode*)NULL) {
		return (ValueType)NULL;
	}
	else {
		return node->value;
	}
}

int GetLevelTreeNodeByKey(Tree root, KeyType key) {
	COUNT = -1;
	return HeightTree(root) - DepthTreeNode(root, key);
}

int GetDepthTreeNodeByKey(Tree root, KeyType key) {
	COUNT = -1;
	return DepthTreeNode(root, key);
}

int GetCountTreeNodes(Tree root) {
	if (root == (Tree)NULL) { return 0; }

	COUNT = 0;
	PostOrderTraversal(root, IncrementCount);

	int _count = COUNT;
	COUNT = 0;
	return _count;
}

int GetCountTreeLeafs(Tree root) {
	if (root == (Tree)NULL) { return 0; }

	if (root->left == (TreeNode*)NULL && root->right == (TreeNode*)NULL) {
		return 1;
	}

	return GetCountTreeLeafs(root->left) + GetCountTreeLeafs(root->right);
}

int GetHeightTree(Tree root) {
	COUNT = -1;
	int height = HeightTree(root);
	COUNT = 0;
	return height < 0 ? 0 : height;
}

bool CheckIsBTS(Tree root) {
	if (root == (Tree)NULL) { return true; }

	if (root->left != (TreeNode*)NULL) {
		if (strcmp(root->left->key, root->key) < 0) {
			return true & CheckIsBTS(root->left) & CheckIsBTS(root->right);
		}
		else {
			return false;
		}
	}

	if (root->right != (TreeNode*)NULL) {
		if (strcmp(root->right->key, root->key) > 0) {
			return true & CheckIsBTS(root->right) & CheckIsBTS(root->left);
		}
		else {
			return false;
		}
	}

	return true;
}

void ClearTree(Tree* root) {
	PostOrderTraversal(*root, FreeTreeNode);
	*root = (Tree)NULL;
	return;
}

void PrintTreeNode(Tree root, int c) {
	if (root == (Tree)NULL) { return; }

	PrintTreeNode(root->right, ++c);
	for (int i = 0; i < c; ++i) { printf(" "); }
	printf("%s:%s\n", root->key, root->value);
	PrintTreeNode(root->left, ++c);
	return;
}
/*=================================*/


/*==================================
========= Private functions ========
==================================*/
TreeNode* CreateAndInitTreeNode(KeyType key, ValueType value) {
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));

	size_t len = strlen(key) + 1;
	node->key = (KeyType)malloc(len);
	memcpy(node->key, key, len);

	len = strlen(value) + 1;
	node->value = (ValueType)malloc(len);
	memcpy(node->value, value, len);

	node->left = node->right = (TreeNode*)NULL;
	return node;
}

bool InsertTreeNode(Tree* root, TreeNode* newNode) {
	if (*root == (Tree)NULL) {
		*root = newNode;
		return true;
	}

	TreeNode* tmp = *root;
	while (tmp != (TreeNode*)NULL) {
		int cmp_value = strcmp(newNode->key, tmp->key);
		if (cmp_value > 0) {
			if (tmp->right == (TreeNode*)NULL) {
				tmp->right = newNode;
				tmp = (TreeNode*)NULL;
			}
			else {
				tmp = tmp->right;
			}
		}
		else if (cmp_value < 0) {
			if (tmp->left == (TreeNode*)NULL) {
				tmp->left = newNode;
				tmp = (TreeNode*)NULL;
			}
			else {
				tmp = tmp->left;
			}
		}
		else {
			return false;
		}
	}
	return true;
}

TreeNode* SearchTreeNode(Tree root, KeyType key) {
	TreeNode* tmp = root;
	while (tmp != (TreeNode*)NULL) {
		int cmp_value = strcmp(key, tmp->key);
		if (cmp_value > 0) {
			tmp = tmp->right;
		}
		else if (cmp_value < 0) {
			tmp = tmp->left;
		}
		else {
			return tmp;
		}
	}
	return (TreeNode*)NULL;
}

void PostOrderTraversal(Tree root, void (*action)(void*)) {
	if (root == (Tree)NULL) { return; }

	PostOrderTraversal(root->left, action);
	PostOrderTraversal(root->right, action);

	action((void*)&root);
	return;
}

void FreeTreeNode(void* root) {
	TreeNode* tree = *(Tree*)root;
	if (tree == (Tree)NULL) { return; }
	free(tree->key);
	free(tree->value);
	free(tree);
	*(Tree*)root = (Tree)NULL;
	return;
}

Tree DeleteTreeNode(Tree root, KeyType key) {
	if (root == (TreeNode*)NULL) { return (Tree)NULL; }

	int cmp_value = strcmp(key, root->key);
	if (cmp_value > 0) {
		root->right = DeleteTreeNode(root->right, key);
	}
	else if (cmp_value < 0) {
		root->left = DeleteTreeNode(root->left, key);
	}
	else if (root->left != (TreeNode*)NULL && root->right != (TreeNode*)NULL) {
		TreeNode* tmp = LeftTreeNode(root->right);
		DataTreeNodeCopy(root, tmp);
		root->right = DeleteTreeNode(root->right, root->key);
	}
	else {
		if (root->left != (TreeNode*)NULL) {
			TreeNode* tmp = root->left;
			FreeTreeNode((void*)&root);
			root = tmp;
		}
		else if (root->right != (TreeNode*)NULL) {
			TreeNode* tmp = root->right;
			FreeTreeNode((void*)&root);
			root = tmp;
		}
		else {
			FreeTreeNode((void*)&root);
		}
	}
	return root;
}

TreeNode* LeftTreeNode(TreeNode* root) {
	TreeNode* prev = root;
	while (root != (TreeNode*)NULL) {
		prev = root;
		root = root->left;
	}
	return prev;
}

void DataTreeNodeCopy(TreeNode* dst, TreeNode* src) {
	free(dst->key);
	size_t len = strlen(src->key) + 1;
	dst->key = (KeyType)malloc(len);
	memcpy(dst->key, src->key, len);

	free(dst->value);
	len = strlen(src->value) + 1;
	dst->value = (ValueType)malloc(len);
	memcpy(dst->value, src->value, len);
	return;
}

void IncrementCount(void* _) {
	++COUNT;
}

int HeightTree(Tree root) {
	++COUNT;
	if (root == (Tree)NULL) { return (--COUNT); }

	int left = HeightTree(root->left);
	int right = HeightTree(root->right);

	if (root->left == (TreeNode*)NULL && root->right == (TreeNode*)NULL) {
		return COUNT--;
	}

	--COUNT;
	return max(left, right);
}

int DepthTreeNode(Tree root, KeyType key) {
	++COUNT;
	if (root == (Tree)NULL) { return (--COUNT); }

	int cmp_value = strcmp(key, root->key);
	if (cmp_value > 0) {
		return DepthTreeNode(root->right, key);
	}
	else if (cmp_value < 0) {
		return DepthTreeNode(root->left, key);
	}
	else {
		int _count = COUNT;
		COUNT = 0;
		return _count;
	}
}
/*=================================*/
