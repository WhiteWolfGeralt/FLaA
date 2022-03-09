#include <iostream>
#include "src/regular/re-tree/tree_creator.h"

int main() {
	TreeCreator treeCreator;
	treeCreator.init("../tests/regular_brackets.txt");
	treeCreator.create_tree();
	treeCreator.print_tree();
}