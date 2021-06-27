#include "reduce_node.h"

char * generate_code(node_t * root , char ** buffer){
    char * code = handle_reduction(root);
    printf("%ld\n" , code);
    printf("%s\n" , code);
    printf("%ld\n" , code);
    *buffer = code;
    return code;
}
