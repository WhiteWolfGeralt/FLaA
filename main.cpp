#include <iostream>
#include "src/regular/re-tree/tree_creator.h"

int main() {
	TreeCreator treeCreator;
	treeCreator.init("*ma|b|(cd)*");
	treeCreator.create_tree();
	treeCreator.print_tree();
}
