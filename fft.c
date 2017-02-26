#include "fftw3.h"

fftwf_complex *fft(int N, fftwf_complex *in)
{
	fftwf_complex *out;
	fftwf_plan p;
	int i;

	out = (fftwf_complex*)(fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * N);
	p = fftwf_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	
	for (i = 0; i < N; i++){
		in[i][0] = in[i][0];
		in[i][1] = in[i][1];
	}
	fftwf_execute(p);
	fftwf_destroy_plan(p);
	return out;
	
}

fftwf_complex *ifft(int N, fftwf_complex *in)
{
	fftwf_complex *out;
	fftwf_plan p;
	int i;

	out = (fftwf_complex*)(fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * N);
	p = fftwf_plan_dft_1d(N, in, out, FFTW_BACKWARD, FFTW_ESTIMATE);

	for (i = 0; i < N; i++) {
		in[i][0] = in[i][0];
		in[i][1] = in[i][1];
	}

	fftwf_execute(p);

	for (i = 0; i < N; i++) {
		out[i][0] /= N;
		out[i][1] /= N;
	}

	fftwf_destroy_plan(p);
	return out;

}

