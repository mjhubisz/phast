/* $Id: trees.h,v 1.3 2004-06-17 23:54:45 acs Exp $
   Written by Adam Siepel, 2002
   Copyright 2002, Adam Siepel, University of California */

#ifndef TREES_H
#define TREES_H

#define DEFAULT_WORDLEN 25
#define MAX_TREESTR_LEN 10000
#define MAX_LINE_LEN 10000

#include <stdio.h>
#include <lists.h>
#include <stringsplus.h>

typedef struct tree_node TreeNode;

/* TODO: starting to accumulate a lot of data about the entire tree at
   each node; perhaps time to adopt a less purely recursive structure,
   with a higher level struct describing the tree as a whole. */
struct tree_node {
  TreeNode *parent;
  TreeNode *lchild, *rchild;
  double dparent;
  char name [DEFAULT_WORDLEN];
  void *data;                   /* allows generic data to be 
                                   associated with tree node */ 
  int id;
  int nnodes;                   /* number of nodes in subtree defined
                                   by this node */
  int height;                   /* height of this node in the tree
                                   (maximum distance to a leaf, in
                                   terms of number of edges) */

  /* the following attributes are only guaranteed to be defined for
     the TreeNode at the root of a tree; 'nodes' is defined upon
     initialization, but the others are constructed on demand; they
     should be accessed only via the functions tr_preorder,
     tr_inorder, tr_postorder.  Note that most of these auxiliary
     attributes (nnodes, height, nodes, preorder, inorder) are not
     guaranteed to remain correct if the structure of a tree is
     altered after initialization */

  List *nodes;                  /* List of nodes: ith element is a
                                   pointer to the node with id = i */
  List *preorder;               /* List of nodes in the order of a
                                   preorder traversal from the root */
  List *inorder;                /* List of nodes in the order of an
                                   inorder traversal from the root */
  List *postorder;              /* List of nodes in the order of a
                                   postorder traversal from the
                                   root */
};

TreeNode *parse_nh_from_file(FILE *f);
TreeNode *parse_nh_from_string(char *s);
TreeNode *new_tree_node();
void addchild(TreeNode *parent, TreeNode *child);
void print_tree(FILE* f, TreeNode *root, int show_branch_lengths);
void print_tree_recur(FILE* f, TreeNode *n, int show_branch_lengths);
void print_tree_debug(FILE *f, TreeNode *n);
void free_tree(TreeNode *n);
void tr_set_nnodes(TreeNode *tree);
void tr_reset_id();
void tr_cpy(TreeNode *dest, TreeNode *src);
TreeNode *tr_create_copy(TreeNode *src);
void tr_node_cpy(TreeNode *dest, TreeNode *src);
void print_tree_alph(FILE* f, TreeNode *root, int show_branch_lengths);
void print_tree_ordered_recur(FILE* f, TreeNode *n, int *left_right,
                              int show_branch_lengths);
List *tr_preorder(TreeNode *tr);
List *tr_inorder(TreeNode *tr);
List *tr_postorder(TreeNode *tr);
void print_node_debug(FILE *f, TreeNode *n);
void tr_layout_xy(TreeNode *tree, int x0, int y0, int x1, int y1, 
                  int *x, int *y, int use_branch_lens, int horizontal);
void tr_print_ps(FILE *F, TreeNode *tree, int show_branch_lens,
                 int square_branches, int use_branch_lens, 
                 int horizontal_layout);
double tr_total_len(TreeNode *t);
TreeNode *tr_get_node(TreeNode *t, char *name);
void tr_number_leaves(TreeNode *t, char **names, int nnames);

#endif 
