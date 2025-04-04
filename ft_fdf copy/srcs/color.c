int   trgb_to_int(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

int	get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

int interpolate_color(int color1, int color2, double ratio)
{
    int red = ((color2 >> 16) & 0xFF) * ratio + ((color1 >> 16) & 0xFF) * (1 - ratio);
    int green = ((color2 >> 8) & 0xFF) * ratio + ((color1 >> 8) & 0xFF) * (1 - ratio);
    int blue = (color2 & 0xFF) * ratio + (color1 & 0xFF) * (1 - ratio);

    return (red << 16) | (green << 8) | blue;
}