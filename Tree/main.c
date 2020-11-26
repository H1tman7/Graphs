
#include "main.h"


int main() {
	Tree tree = InitTree();

	printf("Binary Tree Search\n");

	while (1) {
		char* str = (char*)NULL;
		char** split = (char**)NULL;
		ValueType value = (ValueType)NULL;
		bool check = false;

		printf("\n");
		printf("1. Add node\n");
		printf("2. Delete node\n");
		printf("3. Get value by key\n");
		printf("4. Get depth node by key\n");
		printf("5. Get level node by key\n");
		printf("6. Count nodes\n");
		printf("7. Count leafs\n");
		printf("8. Height tree\n");
		printf("9. Check is BTS\n");
		printf("10. Clear tree\n");
		printf("11. Print tree\n");
		printf("0. Exit\n");

		switch (read_digit()) {
		case 1:
			printf("Enter: [ key : value ]\n");
			str = readline();
			if (!strlen(str)) { free(str); break; }
			if (count_split(str, 2)) {
				split = split_string(str);
				check = InsertTreeValueByKey(&tree, (KeyType)split[0], (ValueType)split[1]);
			}
			else {
				split = split_string(str);
				check = InsertTreeValueByKey(&tree, (KeyType)split[0], (ValueType)"");
			}
			free(str);
			free(split);
			if (check) {
				printf("Node successful added\n");
			}
			else {
				printf("Node with this key is already in tree\n");
			}
			break;

		case 2:
			printf("Enter: [ key ]\n");
			str = readline();
			if (!strlen(str)) { free(str); break; }
			if (DeleteTreeNodeByKey(&tree, str)) {
				printf("Node with this key removed\n");
			}
			else {
				printf("Node with this key not found\n");
			}
			free(str);
			break;

		case 3:
			printf("Enter: [ key ]\n");
			str = readline();
			if (!strlen(str)) { free(str); break; }
			value = GetTreeValueByKey(tree, str);
			if (value == (ValueType)NULL) {
				printf("Node with this key not found\n");
			}
			else {
				printf("[ key : value ]\n");
				printf("[ %s : %s ]\n", str, (char*)value);
			}
			free(str);
			break;

		case 4:
			printf("Enter: [ key ]\n");
			str = readline();
			if (!strlen(str)) { free(str); break; }
			printf("Depth: %d\n", GetDepthTreeNodeByKey(tree, str));
			free(str);
			break;

		case 5:
			printf("Enter: [ key ]\n");
			str = readline();
			if (!strlen(str)) { free(str); break; }
			printf("Level: %d\n", GetLevelTreeNodeByKey(tree, str));
			free(str);
			break;

		case 6:
			printf("Count nodes: %d\n", GetCountTreeNodes(tree));
			break;

		case 7:
			printf("Count leafs: %d\n", GetCountTreeLeafs(tree));
			break;

		case 8:
			printf("Height tree: %d\n", GetHeightTree(tree));
			break;

		case 9:
			if (CheckIsBTS(tree)) {
				printf("Is BTS: Yes\n");
			}
			else {
				printf("Is BTS: No\n");
			}
			break;

		case 10:
			ClearTree(&tree);
			printf("Tree cleared successful\n");
			break;

		case 11:
			printf("\n");
			PrintTreeNode(tree, 0);
			break;

		case 0:
			ClearTree(&tree);
			return 0;

		default:
			printf("Wrong option\n");
			break;
		}
	}

	return 0;
}
