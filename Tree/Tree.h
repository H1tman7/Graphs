
#ifndef _TREE_H
#define _TREE_H

#ifdef _MSC_VER
	#define _CRT_SECURE_NO_WARNINGS
#endif //_MSC_VER

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef char* KeyType;
typedef char* ValueType;
typedef struct __TreeNode TreeNode, * Tree;

/*Public functions*/
Tree InitTree();
bool InsertTreeValueByKey(Tree* root, KeyType key, ValueType value);
bool DeleteTreeNodeByKey(Tree* root, KeyType key);
ValueType GetTreeValueByKey(Tree root, KeyType key);
int GetDepthTreeNodeByKey(Tree root, KeyType key);
int GetLevelTreeNodeByKey(Tree root, KeyType key);
int GetCountTreeNodes(Tree root);
int GetCountTreeLeafs(Tree root);
int GetHeightTree(Tree root);
bool CheckIsBTS(Tree root);
void ClearTree(Tree* root);
void PrintTreeNode(Tree root, int c);

#endif //_TREE_H
