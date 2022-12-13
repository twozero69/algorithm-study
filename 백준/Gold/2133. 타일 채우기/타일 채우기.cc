#include <stdio.h>

int tile_size;
int tile_array[31];

int tiling(int size) {
	if (size == 0)			//size==4일 때 for문에서 tiling(0)을 위해서
		return 1;
	if (size == 1)
		return 0;
	else if (size == 2)
		return 3;

	if (tile_array[size] != 0)
		return tile_array[size];

	int result = tiling(size - 2) * 3;

	for (int i = 4; i <= size; i++) {
		if (i % 2 == 0)
			result += 2 * tiling(size - i);
	}

	return tile_array[size] = result;
}

int main() {
	scanf("%d", &tile_size);
	printf("%d", tiling(tile_size));
}