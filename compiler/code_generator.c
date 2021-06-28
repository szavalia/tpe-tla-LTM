#include "reduce_node.h"
#include <unistd.h>

char * generate_code(node_t * root , char ** buffer){
    char * code = handle_reduction(root);
    printf("%s\n" , code);
    *buffer = code;
    return code;
}
