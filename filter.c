void filter(int bLength, fftwf_complex *b, int xLength, fftwf_complex *x, fftwf_complex *y)
{
	int N = xLength + bLength - 1;
	int i;
	fftwf_complex *XK;
	fftwf_complex *HK;
	fftwf_complex *YK = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * N);
	fftwf_complex *yn;
	fftwf_complex *xIn = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * N);
	fftwf_complex *bIn = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * N);

	memset(xIn, 0, sizeof(fftwf_complex) * N);
	memset(bIn, 0, sizeof(fftwf_complex) * N);

	for (i = 0; i < xLength; i++) {
		xIn[i][0] = x[i][0];
		xIn[i][1] = x[i][1];
	}

	for (i = 0; i < bLength; i++) {
		bIn[i][0] = b[i][0];
		bIn[i][1] = b[i][1];
	}

	XK = fft(N, xIn);
	HK = fft(N, bIn);

	for (i = 0; i < N; i++) {
		complexMulti(1, XK + i, HK + i, YK + i);
	}

	yn = ifft(N, YK);

	for (i = 0; i < xLength; i++) {
		y[i][0] = yn[i][0];
		y[i][1] = yn[i][1];
	}

	fftwf_free(yn);
	fftwf_free(XK);
	fftwf_free(HK);
	fftwf_free(YK);
	fftwf_free(xIn);
	fftwf_free(bIn);
}