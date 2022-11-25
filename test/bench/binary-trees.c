#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node {
  struct tree_node *left_Node, *right_Node;
} tree_node;

static tree_node *create_Tree(const uint32_t tree_Depth) {
  tree_node *const root_Node = malloc(sizeof(tree_node));
  if (root_Node == NULL) {
    printf("out of memory at %" PRIu32 ", memory:%" PRIu32 "\n", tree_Depth,
#ifdef __wasm__
           (uint32_t)__builtin_wasm_memory_size(0)
#else
           0
#endif
    );
    return root_Node;
  }

  if (tree_Depth > 0) {
    root_Node->left_Node = create_Tree(tree_Depth - 1);
    root_Node->right_Node = create_Tree(tree_Depth - 1);
  } else {
    root_Node->left_Node = root_Node->right_Node = NULL;
  }

  return root_Node;
}

static void delete_Tree(tree_node *root) {
  if (root) {
    delete_Tree(root->left_Node);
    delete_Tree(root->right_Node);
    free(root);
  }
}

static uint32_t compute_Tree_Checksum(const tree_node *const root_Node) {
  if (root_Node->left_Node && root_Node->right_Node)
    return compute_Tree_Checksum(root_Node->left_Node) +
           compute_Tree_Checksum(root_Node->right_Node) + 1;

  return 1;
}

int main(int argc, char *argv[]) {
  const uint32_t minimum_Tree_Depth = 4,
                 maximum_Tree_Depth = atoi(argv[1]) < minimum_Tree_Depth + 2
                                          ? minimum_Tree_Depth + 2
                                          : atoi(argv[1]);
  tree_node *stretch_Tree = create_Tree(maximum_Tree_Depth + 1);
  printf("stretch tree of depth %" PRIu32 "\t check: %" PRIu32 "\n",
         maximum_Tree_Depth + 1, compute_Tree_Checksum(stretch_Tree));
  delete_Tree(stretch_Tree);

  tree_node *long_Lived_Tree;

  uint32_t long_Lived_Tree_Checksum,
      tree_Checksums[(maximum_Tree_Depth - minimum_Tree_Depth + 2) / 2];
  {
    {
      long_Lived_Tree = create_Tree(maximum_Tree_Depth);
      long_Lived_Tree_Checksum = compute_Tree_Checksum(long_Lived_Tree);
    }

    for (uint32_t tree_Depth = minimum_Tree_Depth;
         tree_Depth <= maximum_Tree_Depth; tree_Depth += 2) {

      uint32_t total_Trees_Checksum = 0;
      for (uint32_t iterations =
               1 << (maximum_Tree_Depth - tree_Depth + minimum_Tree_Depth);
           iterations-- > 0;) {
        tree_node *temp_Tree = create_Tree(tree_Depth);
        total_Trees_Checksum += compute_Tree_Checksum(temp_Tree);
        delete_Tree(temp_Tree);
      }

      tree_Checksums[(tree_Depth - minimum_Tree_Depth) / 2] =
          total_Trees_Checksum;
    }

    delete_Tree(long_Lived_Tree);
  }

  for (uint32_t tree_Depth = minimum_Tree_Depth;
       tree_Depth <= maximum_Tree_Depth; tree_Depth += 2)
    printf("%" PRIu32 "\t trees of depth %" PRIu32 "\t check: %" PRIu32 "\n",
           1 << (maximum_Tree_Depth - tree_Depth + minimum_Tree_Depth),
           tree_Depth, tree_Checksums[(tree_Depth - minimum_Tree_Depth) / 2]);

  printf("long lived tree of depth %" PRIu32 " \t check: %" PRIu32 " \n",
         maximum_Tree_Depth, long_Lived_Tree_Checksum);

  return 0;
}
