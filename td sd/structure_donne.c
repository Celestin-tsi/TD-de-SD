#include <stdio.h>
#include <stdlib.h>
"""tableau"""
void delet_a(int array[],int size,int index){
    for(int i=index;i<=size;i++){
        array[i]=array[i+1];
    }
    size+=(-1);
}
void add_a(int array[],int size,int index,int value){
    for (int i=size-1;i>=index;i+=(-1)){
        array[i+1]=array[i];
    }
    array[index]=value;
    size+=1;
}
"""liste"""
struct cell{
    float head;
    struct cell*tail;
};
typedef struct cell* list;
list add_l(float a, list b, int index){
    list new_cell = malloc(sizeof(struct cell));
    if (new_cell == NULL) return b;
    new_cell->head = a;
    if (index == 0 || b == NULL) {
        new_cell->tail = b;
        return new_cell;
    }
    list current = b;
    for (int i = 0; current->tail != NULL && i < index - 1; i++) {
        current = current->tail;
    }
    new_cell->tail = current->tail;
    current->tail = new_cell;
    return b;
}
list delete_l(list b, int index) {
    if (b == NULL) return NULL;
    list temp;
    if (index == 0) {
        temp = b->tail;
        free(b);
        return temp;
    }
    list current = b;
    for (int i = 0; current->tail != NULL && i < index - 1; i++) {
        current = current->tail;
    }
    if (current->tail != NULL) {
        temp = current->tail;
        current->tail = current->tail->tail;
        free(temp);
    }
    return b;
}
void print_l(list l){
    printf("(");
    while (l->tail!=NULL){
        printf("%.2f ,",l->head);
        l=l->tail;
    }
    printf("%.2f )",l->head);
}
list range_l(int n,float pas){
    list l=NULL;int index=0;
    for (float i=0;i>n;i=i+pas){
    l=add(i,l,index);
    index++;
    }
return(l);
}
"""stack"""
struct stack{
    int tab[100];
    int last;
};
typedef struct stack* stack;
stack new_stack(){
    stack new_stack=malloc(sizeof(stack));
    new_stack->last=0;
    return(new_stack);
}
void push(stack s,int a){
    s->last=s->last+1;
    s->tab[s->last]=a;
}
void pop(stack s){
    s->last=s->last-1;
}
int top(stack s){
    return(s->tab[s->last]);
}
"""queue"""
struct queue {
    int tab[100];
    int head;
    int tail;
};
typedef struct queue* queue;
queue new_queue() {
    queue q = malloc(sizeof(struct queue));
    if (q != NULL) {
        q->head = 0;
        q->tail = 0;
    }
    return q;
}
void append(queue q, int a) {
    if (q->tail < 100) { 
        q->tab[q->tail] = a;
        q->tail = q->tail + 1;
    } else {
        printf("Erreur : La file est pleine.\n");
    }
}

void remove_q(queue q) {
    if (q->head < q->tail) {
        q->head = q->head + 1;
    } else {
        printf("Erreur : La file est vide.\n");
    }
}
int front(queue q) {
    return q->tab[q->head];
}
"""hash table"""
struct hash_node {
    int key;
    int value;
    struct hash_node* next;
};
struct hash_table {
    struct hash_node** buckets;
    int size;
    int count;
};
typedef struct hash_table* hash_table;
void resize_table(hash_table ht);
int hash_function(int key, int size) {
    int index = key % size;
    if (index < 0) index += size;
    return index;
}
hash_table new_hash_table() {
    hash_table ht = malloc(sizeof(struct hash_table));
    if (ht == NULL) return NULL;
    ht->size = 8;
    ht->count = 0;
    ht->buckets = malloc(ht->size * sizeof(struct hash_node*));
    if (ht->buckets == NULL) {
        free(ht);
        return NULL;
    }
    for (int i = 0; i < ht->size; i++) {
        ht->buckets[i] = NULL;
    }
    return ht;
}
void append_h(hash_table ht, int key, int value) {
    if (ht == NULL) return;
    if ((float)ht->count / ht->size >= 0.75) {
        resize_table(ht);
    }
    int index = hash_function(key, ht->size);
    struct hash_node* current = ht->buckets[index];
    while (current != NULL) {
        if (current->key == key) {
            current->value = value;
            return;
        }
        current = current->next;
    }
    struct hash_node* new_node = malloc(sizeof(struct hash_node));
    if (new_node == NULL) return;
    new_node->key = key;
    new_node->value = value;
    new_node->next = ht->buckets[index];
    ht->buckets[index] = new_node;
    ht->count++;
}
void resize_table(hash_table ht) {
    int old_size = ht->size;
    int new_size = old_size * 2;
    struct hash_node** new_buckets = malloc(new_size * sizeof(struct hash_node*));
    if (new_buckets == NULL) return;
    for (int i = 0; i < new_size; i++) {
        new_buckets[i] = NULL;
    }
    for (int i = 0; i < old_size; i++) {
        struct hash_node* current = ht->buckets[i];
        while (current != NULL) {
            struct hash_node* next_node = current->next;
            int new_index = hash_function(current->key, new_size);
            current->next = new_buckets[new_index];
            new_buckets[new_index] = current;

            current = next_node;
        }
    }
    free(ht->buckets);
    ht->buckets = new_buckets;
    ht->size = new_size;
}
void remove_h(hash_table ht, int key) {
    if (ht == NULL || ht->count == 0) return;
    int index = hash_function(key, ht->size);
    struct hash_node* current = ht->buckets[index];
    struct hash_node* prev = NULL;
    while (current != NULL) {
        if (current->key == key) {
            if (prev == NULL) {
                ht->buckets[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            ht->count--;
            return;
        }
        prev = current;
        current = current->next;
    }
}
int get_h(hash_table ht, int key, int default_value) {
    if (ht == NULL) return default_value;
    int index = hash_function(key, ht->size);
    struct hash_node* current = ht->buckets[index];
    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return default_value;
}