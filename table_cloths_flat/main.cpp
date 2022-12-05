// Source: https://codegolf.stackexchange.com/questions/35569/tweetable-mathematical-art

#include <iostream>
#include <cmath>

#define DIM 1024
#define DM1 (DIM-1)
#define _sq(x) ((x)*(x))                           // square
#define _cb(x) abs((x)*(x)*(x))                    // absolute value of cube
#define _cr(x) (unsigned short)(pow((x),1.0/3.0))  // cube root

unsigned char GR(int, int);
unsigned char BL(int, int);

void pixel_write(int, int);
FILE* fp;

unsigned char RD(int i, int j) {
	float s = 3. / (j + 99);
	float y = (j + sin((i * i + _sq(j - 700) * 5) / 100. / DIM) * 35) * s;
	return (int((i + DIM) * s + y) % 2 + int((DIM * 2 - i) * s + y) % 2) * 127;
}
unsigned char GR(int i, int j) {
	float s = 3. / (j + 99);
	float y = (j + sin((i * i + _sq(j - 700) * 5) / 100. / DIM) * 35) * s;
	return (int(5 * ((i + DIM) * s + y)) % 2 + int(5 * ((DIM * 2 - i) * s + y)) % 2) * 127;
}
unsigned char BL(int i, int j) {
	float s = 3. / (j + 99);
	float y = (j + sin((i * i + _sq(j - 700) * 5) / 100. / DIM) * 35) * s;
	return (int(29 * ((i + DIM) * s + y)) % 2 + int(29 * ((DIM * 2 - i) * s + y)) % 2) * 127;
}

int main() {
	errno_t err;

	err = fopen_s(&fp, "MathPic.ppm", "wb");

	if (err == 0) {
		printf("The file 'MathPic.ppm' was opened\n");

		fprintf(fp, "P6\n%d %d\n1023\n", DIM, DIM);

		for (int j = 0; j < DIM; j++)
			for (int i = 0; i < DIM; i++)
				pixel_write(i, j);

		fclose(fp);
	}
	else {
		printf("The file 'MathPic.ppm' was not opened\n");
	}

	return 0;
}

void pixel_write(int i, int j) {
	static unsigned short color[3];

	color[0] = RD(i, j) & DM1;
	color[1] = GR(i, j) & DM1;
	color[2] = BL(i, j) & DM1;

	fwrite(color, 2, 3, fp);
}