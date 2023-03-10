
/* Buffer to store data */
struct buffer {
    struct packetHeader header; //Store header of buffer
    struct buffer * next; //Store next available buffer
    struct buffer *prev;
    int size;
    char data[0]; //Store data
};

#define STRUCTBUFFERSIZE sizeof(struct buffer)

/* Sentinel used for storing head of buffer blocks */
struct sentinel {
    int size;
    struct buffer *next;
    struct buffer *prev;
};

/* Stores a different size buffers at each index in ascending order (0 stores lowest) */
#define LEVELS 3
struct sentinel multiLevelStack[LEVELS]; 


/* Specifies the number of buffers for a specifc size and the size of data the buffer will hold */
#define BIGNUMBUFFERS 5
#define BIGMAXSIZEBUFFER 50

#define MEDNUMBUFFERS 7
#define MEDMAXSIZEBUFFER 35

#define SMALLNUMBUFFERS 10
#define SMALLMAXSIZEBUFFER 20

int initializeBuffers(void);

struct buffer * requestBuffer(int);

int inputBuffer(struct buffer *);

void printMultiLevelStack();

