#include <stdlib.h>
#include <stdio.h>

#include "../src/Node.h"

void nodeTest(){
	Node *node1 = new_Node();
	node1->name = "nathan";
	node1->type = "actor";
	Node *node2 = new_Node();
	node2->name = "curious george";
	node2->type = "actor";
	addChild(node1, "mikey");
	addChild(node1, "berko");
	addToPath(node1, "skurp");
	addToPath(node1, "alert");
	buildChildPath(node2, node1);
	printf("node name: %s, node type: %s child1 %s child2 %s path %s path2 %s \n", node1->name, node1->type, node1->children[0], node1->children[1], node1->path[0], node1->path[1]);
	printf("node name: %s path %s path2 %s path3 %s \n", node2->name, node2->path[0], node2->path[1], node2->path[2]);
}

int main(){
	nodeTest();
	return 0;
}
