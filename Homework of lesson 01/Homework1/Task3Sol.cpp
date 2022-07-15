int clear_bits_through_i(int x, int i)
{
	return x & ~(-1 << i);
}
