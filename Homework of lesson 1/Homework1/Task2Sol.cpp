int nulls_count(int x)
{
	if (!x)
		return 32;
	int ans = 0, y = 1 << (sizeof(int) << 3) - 2;
	while (y && !(x & y)) {
		y >>= 1;
		++ans;
	}
	return ans;
}
