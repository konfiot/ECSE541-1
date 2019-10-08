#define max(a,b) ((a) &gt; (b) ? (a) : (b))
#define max3(a,b,c) (max((a), max((b),(c))))

#define NUM_BLOCKS 64
#define BLOCK_SIZE 64
#define INPUT1_ADDR 0
#define INPUT2_ADDR 16384
#define SAD_OUTPUT_ADDR 32768
#define MEM_SIZE NUM_BLOCKS*BLOCK_SIZE+ max3(SAD_OUTPUT_ADDR, INPUT1_ADDR, INPUT2_ADDR)
