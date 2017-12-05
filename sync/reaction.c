#include <pthread.h>
#include "reaction.h"

// Forward declaration. This function is implemented in reaction-runner.c,
// but you needn't care what it does. Just be sure it's called when
// appropriate within reaction_o()/reaction_h().
void make_water();


void reaction_init(struct reaction *reaction) {
    // FILL ME IN
    reaction->H_cnt = 0;
    pthread_cond_init(&reaction->H, NULL);
    pthread_cond_init(&reaction->reaction_done, NULL);
    pthread_mutex_init(&reaction->lock, NULL);
}


void reaction_h(struct reaction *reaction) {
    // FILL ME IN
    pthread_mutex_lock(&reaction->lock);
    reaction->H_cnt++;
    pthread_cond_signal(&reaction->H);
    pthread_cond_wait(&reaction->reaction_done, &reaction->lock);
    pthread_mutex_unlock(&reaction->lock);
}


void reaction_o(struct reaction *reaction) {
    // FILL ME IN
    pthread_mutex_lock(&reaction->lock);
    while (reaction->H_cnt < 2)
        pthread_cond_wait(&reaction->H, &reaction->lock);

    make_water();

    reaction->H_cnt -= 2;
    pthread_cond_signal(&reaction->reaction_done);
    pthread_cond_signal(&reaction->reaction_done);
    pthread_mutex_unlock(&reaction->lock);
}
