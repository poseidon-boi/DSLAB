# Week 10

## binary_tree_ops.c

A menu driven program to perform the following basic operations on a binary tree:

1. Insert element
2. Print tree
3. Traverse inorder
4. Traverse postorder
5. Traverse preorder
6. Print parent of entered element
7. Print depth of tree
8. Print ancestors of entered element
9. Count number of leaf nodes
10. Exit

Build command for linux(with GCC):

```shell
gcc -O3 -o output_file_name.out binary_tree_ops.c
```

## binary_tree_ops.o

An object file of `binary_tree_ops.c` to compile the other programs in this folder. Has all of the functions except the main function, so that the other programs can use it.

## tree.h

Header file containing all of the tree operation functions in `binary_tree_ops.c` so that other programs can include and use those functions.  

## level_order.c

A menu driven program to perform the following operations on a binary tree:

1. Insert element
2. Print the tree
3. Traverse tree in level order
4. Exit

Build command for linux(with GCC):

```shell
gcc -O3 -o output_file_name.out level_order.c binary_tree_ops.o
```

## postfix_tree.c

A program that creates an expression tree from a postfix expression and evaluates the expression

Output example:

```

Enter postfix expression: 576+-
                6
        +
                7
-
        5
Result is -8

```

Build command for linux(with GCC):

```shell
gcc -O3 -o output_file_name.out postfix_tree.c binary_tree_ops.o
```

## tree_copy.c

A menu driven program that copies a given binary tree to a brand new binary tree. Has the following operations:

1. Insert element into original tree
2. Copy tree
3. Print original tree
4. Print copied tree
5. Exit

Build command for linux(with GCC):

```shell
gcc -O3 -o output_file_name.out tree_copy.c binary_tree_ops.o
```

## tree_equality.c

A menu driven program that compares two binary trees to check if they are equal. Has the following operations:

1. Insert element into tree 1
2. Insert element into tree 2
3. Print tree 1
4. Print tree 2
5. Check for equality
6. Exit

Build command for linux(with GCC):

```shell
gcc -O3 -o output_file_name.out tree_equality.c binary_tree_ops.o
```

## tree_mirror.c

A menu driven program that checks whether two binary trees are mirrors of each other. Has the following operations:

1. Insert element into tree
2. Insert element into tree 2
3. Print tree 1
4. Print tree 2
5. Check whether mirrored
6. Exit

Build command for linux(with GCC):

```shell
gcc -O3 -o output_file_name.out tree_mirror.c binary_tree_ops.o
```
