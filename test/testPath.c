#include <stdlib.h>
#include <stdio.h>
#include "../src/Path.h"

void testPath()
{
	Path p = {.length = 0};
	append(&p, "nathan");
	append(&p, "mikey");
	append(&p, "allison");
	printPath(&p);
}

int main()
{
	testPath();
	return 0;
}