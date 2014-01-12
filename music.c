#include <math.h>
#include <float.h>

typedef struct {
    const char * name;
    const double val;
} note;

#define DEF_NOTE(n, v) {.name = n, .val = v}

note notes[] = {
    DEF_NOTE("A2  ",   27.5),
    DEF_NOTE("A2 #",   29.1352350949),
    DEF_NOTE("B2  ",   30.8677063285),
    DEF_NOTE("C1  ",   32.7031956626),
    DEF_NOTE("C1 #",   34.6478288721),
    DEF_NOTE("D1  ",   36.7080959897),
    DEF_NOTE("D1 #",   38.8908729653),
    DEF_NOTE("E1  ",   41.2034446141),
    DEF_NOTE("F1  ",   43.6535289291),
    DEF_NOTE("F1 #",   46.249302839),
    DEF_NOTE("G1  ",   48.9994294977),
    DEF_NOTE("G1 #",   51.9130871975),
    DEF_NOTE("A1  ",   55.0),
    DEF_NOTE("A1 #",   58.2704701898),
    DEF_NOTE("B1  ",   61.735412657),
    DEF_NOTE("C   ",   65.4063913251),
    DEF_NOTE("C # ",   69.2956577442),
    DEF_NOTE("D   ",   73.4161919794),
    DEF_NOTE("D # ",   77.7817459305),
    DEF_NOTE("E   ",   82.4068892282),
    DEF_NOTE("F   ",   87.3070578583),
    DEF_NOTE("F # ",   92.4986056779),
    DEF_NOTE("G   ",   97.9988589954),
    DEF_NOTE("G # ",   103.826174395),
    DEF_NOTE("A   ",   110.0),
    DEF_NOTE("A # ",   116.54094038),
    DEF_NOTE("B   ",   123.470825314),
    DEF_NOTE("c   ",   130.81278265),
    DEF_NOTE("c # ",   138.591315488),
    DEF_NOTE("d   ",   146.832383959),
    DEF_NOTE("d # ",   155.563491861),
    DEF_NOTE("e   ",   164.813778456),
    DEF_NOTE("f   ",   174.614115717),
    DEF_NOTE("f # ",   184.997211356),
    DEF_NOTE("g   ",   195.997717991),
    DEF_NOTE("g # ",   207.65234879),
    DEF_NOTE("a   ",   220.0),
    DEF_NOTE("a # ",   233.081880759),
    DEF_NOTE("b   ",   246.941650628),
    DEF_NOTE("c1  ",   261.625565301),
    DEF_NOTE("c1 #",   277.182630977),
    DEF_NOTE("d1  ",   293.664767917),
    DEF_NOTE("d1 #",   311.126983722),
    DEF_NOTE("e1  ",   329.627556913),
    DEF_NOTE("f1  ",   349.228231433),
    DEF_NOTE("f1 #",   369.994422712),
    DEF_NOTE("g1  ",   391.995435982),
    DEF_NOTE("g1# ",   415.30469758),
    DEF_NOTE("a1  ",   440.0),
    DEF_NOTE("a1 #",   466.163761518),
    DEF_NOTE("b1  ",   493.883301256),
    DEF_NOTE("c2  ",   523.251130601),
    DEF_NOTE("c2 #",   554.365261954),
    DEF_NOTE("d2  ",   587.329535835),
    DEF_NOTE("d2 #",   622.253967444),
    DEF_NOTE("e2  ",   659.255113826),
    DEF_NOTE("f2  ",   698.456462866),
    DEF_NOTE("f2 #",   739.988845423),
    DEF_NOTE("g2  ",   783.990871963),
    DEF_NOTE("g2 #",   830.60939516),
    DEF_NOTE("a2  ",   880.0),
    DEF_NOTE("a2 #",   932.327523036),
    DEF_NOTE("b2  ",   987.766602512),
    DEF_NOTE("c3  ",   1046.5022612),
    DEF_NOTE("c3 #",   1108.73052391),
    DEF_NOTE("d3  ",   1174.65907167),
    DEF_NOTE("d3 #",   1244.50793489),
    DEF_NOTE("e3  ",   1318.51022765),
    DEF_NOTE("f3  ",   1396.91292573),
    DEF_NOTE("f3 #",   1479.97769085),
    DEF_NOTE("g3  ",   1567.98174393),
    DEF_NOTE("g3 #",   1661.21879032),
    DEF_NOTE("a3  ",   1760.0),
    DEF_NOTE("a3 #",   1864.65504607),
    DEF_NOTE("b3  ",   1975.53320502),
    DEF_NOTE("c4  ",   2093.0045224),
    DEF_NOTE("c4 #",   2217.46104781),
    DEF_NOTE("d4  ",   2349.31814334),
    DEF_NOTE("d4 #",   2489.01586978),
    DEF_NOTE("e4  ",   2637.0204553),
    DEF_NOTE("f4  ",   2793.82585146),
    DEF_NOTE("f4 #",   2959.95538169),
    DEF_NOTE("g4  ",   3135.96348785),
    DEF_NOTE("g4 #",   3322.43758064),
    DEF_NOTE("a4  ",   3520.0),
    DEF_NOTE("a4 #",   3729.31009214),
    DEF_NOTE("b4  ",   3951.06641005),
    DEF_NOTE("c5  ",   4186.00904481)
};

const char * get_note(double freq)
{

    int start = 0;
    int stop = sizeof(notes)/sizeof(note)-1;

    int i = 0, i_min = 0, tmp = 0;
    double min = DBL_MAX;

    while (stop > start && stop - start > 1 ) {

        i = (stop + start) / 2;

        if (notes[i].val < freq ) {
            start = i;
        } else if (notes[i].val > freq) {
            stop = i;
        } else { // exact match!?
            return notes[i].name;
        }

    }

    if (stop < start) {
        tmp = start;
        start = stop;
        stop = tmp;
    }

    i = start;
    i_min=start;

    min = fabs(freq - notes[i].val);

    for ( ; i<=stop; ++i) {
        if (fabs(freq - notes[i].val) < min) {
            i_min = i;
            min = fabs(freq-notes[i].val);
        }
    }

    return notes[i_min].name;
}
