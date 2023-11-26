set(SOURCES
    charset.c
    tree.c
    tree-node.c
)

set (CMAKE_C_COMPILER gcc)

add_library (tree-node tree-node.c tree-node.h)
add_library (tree tree.c tree.h tree-node.h)
add_library (charset charset.c charset.h tree.h tree-node.h)
