#include <stdio.h>

int tile_size;

int tile_array[1001];

int tiling(int size) {
	if (size == 1)
		return 1;
	else if (size == 2)
		return 3;

	if (tile_array[size] != 0)
		return tile_array[size];

	return tile_array[size] = (tiling(size - 1) + tiling(size - 2) * 2) % 10007;
}

int main() {
	scanf("%d", &tile_size);
	printf("%d", tiling(tile_size));
}