/**
 * LNUM: Abstract the natural numbers.
 * 
 * Let's try something abstract using simple codes. We defined an abstract number
 * called `lnum` (Lambda Number), and used linked-list to code the very basics of
 * this abstraction. 
 * 
 * Basically, every `lnum` is a linked list and could be mapped 
 * to a natural number. But let's just forget the natural number system for now
 * and "reinvent" them without using any natural numbers.
 * 
 * This would be helpful for beginners to understand the Functional Programming.
 */

#include <stdio.h>
#include <stdlib.h>

struct lnum { struct lnum *next; }; /* Let's call it "Lambda Number" */

/* Define the ZERO Object. Here we use NULL. 
 * But at the abstraction level, it could be any object. */
#define ZERO_OBJ (struct lnum *)NULL

/* Define a flag as the end of a Lambda Number. */
#define LNUM_END (struct lnum *)NULL

#define ZERO(p_step_func, zero_obj) zero_obj       
/* Generate and return next Lambda Number. */
#define NEXT(ptr_lnum, p_step_func, zero_obj) ({ \
        (p_step_func(ptr_lnum, zero_obj)) ? (p_step_func(ptr_lnum, zero_obj)) : (ptr_lnum); \
        })

/* Map a Lambda Number to a natural number (actually the length of a linked-list) */
#define LNUM_MAP_TO_NUM(ptr_lnum) ({ \
        size_t num = 0; struct lnum *tmp = ptr_lnum; \
        do { \
            (tmp == LNUM_END) ? ({break;}) : ({tmp = tmp->next; num++;}); \
        } while (1); num; \
        })

#define PRINT_MAPPED_NUM(ptr_lnum, lnum_var_name) \
        printf("lnum_var_name: %s\tnatural_number: %lu\n", lnum_var_name, LNUM_MAP_TO_NUM(ptr_lnum));

/* Define the step function. We need recursive programming because that's one of the 
 * essence of Functional Programming (FP). 
 */
struct lnum *step_func(struct lnum *ptr_lnum, struct lnum *zero) {
    if(ptr_lnum == ZERO(step_func, zero) || ptr_lnum->next == LNUM_END) {
        struct lnum *new_lnum = (struct lnum *)malloc(sizeof(struct lnum));
        new_lnum->next = LNUM_END;
        /* We *ASSERT* the allocatin is good. ONLY for demo. */
        if(ptr_lnum == ZERO(step_func, zero)) {
            return new_lnum; // Use the new pointer.
        }
        else {
            ptr_lnum->next = new_lnum;
            return LNUM_END; // Use the original pointer.
        }
    }
    step_func(ptr_lnum->next, zero);
}

struct lnum *add(struct lnum *ptr_a, struct lnum *ptr_b, \
                struct lnum *(p_step_func)(struct lnum *, struct lnum *), \
                struct lnum *zero) {
    if(ptr_b == ZERO_OBJ) {
        return ptr_a;
    }
    ptr_a = NEXT(ptr_a, p_step_func, zero);
    add(ptr_a, ptr_b->next, p_step_func, zero);
}

/* OK, Let's "reinvent" the natural numbers with the efforts above. 
 * Please notice: Almost everything is a function here. 
 */
int main(int argc, char **argv) {
    /* struct lnum *lnum_0 = ZERO(step_func, ZERO_OBJ);
    PRINT_MAPPED_NUM(lnum_0, "lnum_0");
    struct lnum *lnum_1 = NEXT(lnum_0, step_func, ZERO_OBJ);
    PRINT_MAPPED_NUM(lnum_1, "lnum_1");
    struct lnum *lnum_2 = NEXT(lnum_1, step_func, ZERO_OBJ);
    PRINT_MAPPED_NUM(lnum_2, "lnum_2");
    struct lnum *lnum_3 = NEXT(lnum_2, step_func, ZERO_OBJ);
    PRINT_MAPPED_NUM(lnum_3, "lnum_3");
    struct lnum *lnum_4 = NEXT(lnum_3, step_func, ZERO_OBJ);
    PRINT_MAPPED_NUM(lnum_4, "lnum_4");
    struct lnum *this_num = lnum_4, *next_num;*/
    struct lnum *lnum_0 = ZERO(step_func, ZERO_OBJ);
    struct lnum *lnum_this = lnum_0, *lnum_next = NULL;
    char lnum_var_name[16] = "";
    for(size_t i = 0; i < 100; i++) {
        lnum_next = NEXT(lnum_this, step_func, ZERO_OBJ);
        snprintf(lnum_var_name, 16, "lnum_%lu", i + 1);
        PRINT_MAPPED_NUM(lnum_next, lnum_var_name);
        lnum_this = lnum_next;
    }
    /* TODO: ... Free the memory, for demo purpose we omit it. */
}
