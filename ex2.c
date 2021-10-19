#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#define PASCALS_MAX_ROW (18)
static uint64_t pascals_array[] =
{
    1, 
    1, 1, 
    1, 2, 1, 
    1, 3, 3, 1, 
    1, 4, 6, 4, 1, 
    1, 5, 10, 10, 5, 1, 
    1, 6, 15, 20, 15, 6, 1, 
    1, 7, 21, 35, 35, 21, 7, 1, 
    1, 8, 28, 56, 70, 56, 28, 8, 1, 
    1, 9, 36, 84, 126, 126, 84, 36, 9, 1, 
    1, 10, 45, 120, 210, 252, 210, 120, 45, 10, 1, 
    1, 11, 55, 165, 330, 462, 462, 330, 165, 55, 11, 1, 
    1, 12, 66, 220, 495, 792, 924, 792, 495, 220, 66, 12, 1, 
    1, 13, 78, 286, 715, 1287, 1716, 1716, 1287, 715, 286, 78, 13, 1, 
    1, 14, 91, 364, 1001, 2002, 3003, 3432, 3003, 2002, 1001, 364, 91, 14, 1, 
    1, 15, 105, 455, 1365, 3003, 5005, 6435, 6435, 5005, 3003, 1365, 455, 105, 15, 1, 
    1, 16, 120, 560, 1820, 4368, 8008, 11440, 12870, 11440, 8008, 4368, 1820, 560, 120, 16, 1, 
    1, 17, 136, 680, 2380, 6188, 12376, 19448, 24310, 24310, 19448, 12376, 6188, 2380, 680, 136, 17, 1, 
};

static uint64_t nck(unsigned n, unsigned k)
{
    assert(n < PASCALS_MAX_ROW);
    if (n < k) return 0;
    return pascals_array[n*(n+1)/2 + k];
}

static unsigned seq_weight_w_index(unsigned n, unsigned len, unsigned weight)
{
    unsigned idx = 0;
    unsigned k;
    for (k = 1; k <= len; k++)
    {
        unsigned rem_bits = weight;

        if (k > 0)
            rem_bits -= __builtin_popcount(n & ((1 << (k-1)) - 1));

        if (n & (1 << (k-1)))
        {
            idx += nck(len - k, rem_bits);
        }
    }
    return idx;
}

static char *binary_str(unsigned n, unsigned len)
{
    static char str[33];
    unsigned i;
    for (i = 0; i < len; i++)
    {
        if (n & (1 << i))
        {
            str[i] = '1';
        }
        else
        {
            str[i] = '0';
        }
    }
    str[len] = '\0';
    return str;
}

int main(int argc, char *argv[])
{
    unsigned n;
    unsigned length;
    unsigned weight;

    if (argc != 3) return 0;

    length = strtoul(argv[1], NULL, 0);
    weight = strtoul(argv[2], NULL, 0);

    assert(weight <= length);

    for (n = 0; n < (1 << length); n++)
    {
        unsigned pc = __builtin_popcount(n);

        if (pc == weight)
        {
            unsigned idx = seq_weight_w_index(n, length, weight);
            printf("%4u %4x %10s has index %4u\n",
                   n, n, binary_str(n, length), idx);
        }
    }
    return 0;
}
