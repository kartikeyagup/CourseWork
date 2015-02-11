// YOU DO NOT NEED TO MODIFY THIS INSTRUCTOR-PROVIDED FILE.
// Your code should work properly with an unmodified version of this file.

#include "misc.h"

void printAndExit(string message = "")
{
	perror(message.data());
	exit(1);
}
