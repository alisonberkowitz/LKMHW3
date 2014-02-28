#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../src/Hashmap.h"
#include "../src/Node.h"


void testHashmap()
{
	Node dataNode = {.name="nathan"};
	Node dataNode2 = {.name="mikey"};
	int x = 1;
	int y;

	map_t map = hashmap_new();
	int error = hashmap_put(map, dataNode.name, &x);
	assert(error==MAP_OK);
	error = hashmap_put(map, dataNode2.name, &x);
	assert(error==MAP_OK);
	error = hashmap_get(map, dataNode2.name, (void**)(&y));
	if (error==MAP_OK)
	{
		printf("%s\n", "Key Found");
	}
	error = hashmap_get(map, "Michael Jordan", (void**)(&y));
	if (error == MAP_MISSING)
	{
		printf("%s\n", "Key Missing");
	}

}

int main()
{
	testHashmap();
	return 0;
}