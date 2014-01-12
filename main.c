#include <stdio.h>
#include <stdlib.h>

#include <signal.h>

#include <fftw3.h>
#include <complex.h>
#include <math.h>

#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/soundcard.h>

#define SPECT_LOW (27)
#define SPECT_HIGH (4187)

#define SPECTRUM (SPECT_HIGH - SPECT_LOW)

#define N (2*SPECTRUM)

const char * audio_dev = "/dev/dsp";
int running = 1;

void interrupt_program(int n)
{
    running = 0;
}

int main(int argc, char ** argv)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int m = 0;

    double max = 0.0;
    int max_i = 0;

    int audio_fd = 0;
    unsigned char audio_buffer;

    int audio_format = AFMT_U8;
    int audio_stereo = 0; /* mono */
    int audio_speed = N;

    signal(SIGINT, interrupt_program);

    fftw_complex *in, *out;
    fftw_plan plan;

    if ( !fftw_init_threads() ) {
        printf ("Threads are not supported!\n");
        exit(1);
    }

    if ( (audio_fd = open(audio_dev, O_RDONLY, 0)) <= 0) {
        printf("Cannot open audio device: %s\n", audio_dev);
        perror(audio_dev);
        exit(1);
    }

    if ( ioctl(audio_fd, SNDCTL_DSP_SETFMT, &audio_format) == -1) {
        printf("Cannot select audio format.\n");
        perror(audio_dev);
        close(audio_fd);
        exit(1);
    }

    if ( ioctl(audio_fd, SNDCTL_DSP_STEREO, &audio_stereo) == -1) {
        printf("Mono recording not supported.\n");
        perror(audio_dev);
        close(audio_fd);
        exit(1);
    }

    if ( ioctl(audio_fd, SNDCTL_DSP_SPEED, &audio_speed) == -1) {
        printf("Cannot set speed on audio device.\n");
        perror(audio_dev);
        close(audio_fd);
        exit(1);
    }
    
    in = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * N);
    out = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * N);

    for ( j=0; j<N; ++j) {
        in[j][0] = 0.0;
        in[j][1] = 0.0;
    }

    fftw_plan_with_nthreads(2);

    plan = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    while (running) {

        if ( read(audio_fd, &audio_buffer, 1) == -1) {
            printf("Cannot read data from soundcard.\n");
        } else {
            in[m][0] = (double) (audio_buffer-127)/255.0;

            if (m < N-1) {
                ++m;
            } else {
                for ( j=1; j < N; ++j) {
                    in[j-1][0] = in[j][0]/1.000032;
                }
            }
            
            k = (k+1) % 4;
        }

        if (k==3) {
            fftw_execute(plan);
            max = 0;
            max_i = 0;
            for ( i=1; i<1+N/2; ++i ) {
                double val = (2* sqrt(out[i][0] * out[i][0] +
                                  out[i][1] * out[i][1]) / N);
                if (val > max) {
                    max = val;
                    max_i = i;
                }
            }
            fprintf(stderr, "\rnote: %s (%03.5f [Hz])", get_note( (double) (2*max_i-1) / N * SPECTRUM + SPECT_LOW), (double) (2*max_i-1) / N * SPECTRUM + SPECT_LOW);
       }

    }


    fftw_destroy_plan(plan);

    fprintf(stderr, "\nbase: %f\n", sqrt(out[0][0] * out[0][0] + 
out[0][1] 
* out[0][1]) /SPECTRUM );
/*
    for ( i=1; i<1+N/2; ++i ) {
        double val = (2* sqrt(out[i][0] * out[i][0] +
                                  out[i][1] * out[i][1]) / N);
        if (val > max) {
            max = val;
            max_i = i;
        }
        printf("%f %f\n", (double) (2*i-1) / N * SPECTRUM + SPECT_LOW,
                                 val );
    }
*/
    fprintf(stderr, "note: %s\n", get_note( (double) (2*max_i-1) / N * SPECTRUM + SPECT_LOW));
//    fprintf(stderr, "Max: %f [Hz] = %f\n", (double) (2*max_i-1) / N * SPECTRUM + SPECT_LOW, max);

    fftw_free(in);
    fftw_free(out);

    fftw_cleanup_threads();

    close(audio_fd);

    return 0;
}
