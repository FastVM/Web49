#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define N 16

typedef struct tree_t tree_t;

struct tree_t {
    ptrdiff_t n;
    tree_t *pair;
};

tree_t make_tree(ptrdiff_t item, ptrdiff_t depth) {
    if (depth != 0) {
        tree_t *pair = malloc(sizeof(tree_t) * 2);
        pair[0] = make_tree(item * 2 - 1, depth - 1);
        pair[1] = make_tree(item * 2, depth - 1);
        return (tree_t){
            .n = item,
            .pair = pair,
        };
    } else {
        return (tree_t){
            .n = item,
        };
    }
}

ptrdiff_t item_check(tree_t tree) {
    if (tree.pair != NULL) {
        return tree.n + item_check(tree.pair[0]) - item_check(tree.pair[1]);
    } else {
        return tree.n;
    }
}

void del_tree(tree_t tree) {
    if (tree.pair != NULL) {
        del_tree(tree.pair[0]);
        del_tree(tree.pair[1]);
        free(tree.pair);
    }
}

int main() {
    ptrdiff_t min = 4;
    ptrdiff_t max = min - 2;
    if (max < N) {
        max = N;
    }

    tree_t str = make_tree(0, max + 1);
    printf("%zi\n", item_check(str));
    del_tree(str);

    tree_t tree = make_tree(0, max);

    for (ptrdiff_t depth = min; depth < max; depth += 2) {
        ptrdiff_t iters = 1 << (max - depth + min);
        ptrdiff_t check = 0;
        for (size_t i = 0; i < iters; i++) {
            tree_t ta = make_tree(1, depth);
            check += item_check(ta);
            del_tree(ta);
            tree_t tb = make_tree(-1, depth);
            check += item_check(tb);
            del_tree(tb);
        }
        printf("%zi\n", check);
    }

    printf("%zi\n", item_check(tree));
    del_tree(tree);
}
