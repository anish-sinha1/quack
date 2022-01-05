#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "vector/vector.h"

// implementing this as a random access queue because I don't want to make a whole separate repo for that,
// and I just want to move on

typedef struct GQueueEntity {
    struct GQueueEntity *prev;
    struct GQueueEntity *next;
    void *val;
} GQueueEntity;

typedef struct GQueue {
    unsigned int entity_count;
    unsigned int capacity;
    GQueueEntity *head;
    GQueueEntity *tail;
    Vector *index;
} GQueue;

void *get_entity_val(GQueueEntity *e) {
    return e->val;
}

bool q_empty(GQueue *q) {
    return q->entity_count == 0;
}

bool q_full(GQueue *q) {
    return q->entity_count == q->capacity;
}

static GQueueEntity *create_entity(void *val) {
    if (val == NULL) return NULL; // pass a null pointer in? fuck you, get a null pointer back
    GQueueEntity *new_entity = malloc(sizeof(GQueueEntity));
    new_entity->val = val;
    new_entity->prev = new_entity->next = NULL;
    return new_entity;
}

void enqueue(GQueue *q, void *val) {
    if (q_full(q)) return;
    GQueueEntity *new_entity = create_entity(val);
    if (q == NULL || val == NULL) return;
    if (q->entity_count == 0) {
        q->head = q->tail = new_entity;
        append(q->index, new_entity);
    } else {
        GQueueEntity *t = q->tail;
        new_entity->prev = t;
        t->next = new_entity;
        q->tail = new_entity;
        append(q->index, new_entity);
    }
    q->entity_count++;
}

void *dequeue(GQueue *q) {
    if (q_empty(q)) return NULL;
    if (q->entity_count == 1) {
        GQueueEntity *t = q->head;
        q->head = q->tail = NULL;
        q->entity_count = 0;
        return t;
    }
    GQueueEntity *t = q->head;
    q->head = t->next;
    t->next = NULL;
    q->head->prev = NULL;
    delete(q->index, 0);
    return t;
}

void *get_index(GQueue *q, unsigned int index) {
    if (index > q->capacity) {
        return NULL;
    }
    return get(q->index, index);
}

void *first(GQueue *q) {
    void *t = q->head->val;
    return t;
}

GQueue *new_queue() {
    GQueue *new_queue = malloc(sizeof(GQueue));
    new_queue->head = new_queue->tail = NULL;
    new_queue->entity_count = 0;
    new_queue->capacity = 50;
    new_queue->index = new_vector();
    return new_queue;
}

// I love you. I miss you. I'm sorry Autumn. I promise I'll honor you with every line of code I ever write
// as a way of penance. I hope you're doing okay. I'm writing this here because I know that no one will ever
// read it and even if they do they won't know what I'm talking about.