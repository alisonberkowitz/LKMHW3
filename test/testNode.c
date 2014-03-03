#include <stdlib.h>
#include <stdio.h>

#include "../src/Node.h"

void nodeTest(){
	Node *node1 = new_Node();
	node1->name = "nathan";
	node1->type = "actor";
	addChild(node1, "mikey");
	addChild(node1, "berko");
	printf("node name: %s, node type: %s child1 %s child2 %s \n", node1->name, node1->type, node1->children[0], node1->children[1]);
}

int main(){
	nodeTest();
	return 0;
}
