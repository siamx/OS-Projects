#include <stdio.h>
#include <pthread.h>

struct reaction {
    // FILL ME IN
    int H_cnt;
    pthread_cond_t H;
    pthread_cond_t reaction_done;
    pthread_mutex_t lock;
};

void reaction_init(struct reaction *reaction);

void reaction_h(struct reaction *reaction);

void reaction_o(struct reaction *reaction);
