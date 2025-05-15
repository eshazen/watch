# Watch software

It would be nice to display an analog clock face.
This is complicated by the fact that the E-Ink display
is 200x200 and we don't have enough RAM (200x200/8=5000 bytes)
for a bitmap.

One solution is a partial bitmap (e.g. 64x128 = 1k), and
a bit of code which takes a display list and iterates
over it 8 times, clipping the lines into regions,
sending each to the display as it completes.

    /---- 200 ------\
    +----+----+----+----+ \
    | 64 | 64 | 64 | 64 | |
	|    |    |    |    | |
	|    |    |    |    | |
	|    |    |    |    | 200 
    +----+----+----+----+ |
	|    |    |    |    | |
	|    |    |    |    | |
	|    |    |    |    | /
	|    |    |    |    |
    +----+----+----+----+

