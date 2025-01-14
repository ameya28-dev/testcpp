#include <stdlib.h>

int main() {
	char *s = (char *)malloc(5 * sizeof(char));
	free(s);

	return 0;
}