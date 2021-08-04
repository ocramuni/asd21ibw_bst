# Albero binario semplice
add_executable(bst bst.c)
# Albero binario di tipo AVL
add_executable(avl avl.c)
# Albero binario di tipo Red-Black
add_executable(rbt rbt.c)
# Calcolo tempi
add_executable(binaryTreeTime binaryTreeTime.c)
target_link_libraries(binaryTreeTime m)