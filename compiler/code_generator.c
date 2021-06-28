#include "reduce_node.h"

char * generate_code(node_t * root , char ** buffer){
    dup2(3 , 1);
    dup2(1 , 3);
    char * code = handle_reduction(root);
    printf("%ld\n" , code);
    printf("%s\n" , code);
    printf("%ld\n" , code);
    *buffer = code;
    dup2(1 , 3);
    dup2(3 , 1);
    return code;
}
