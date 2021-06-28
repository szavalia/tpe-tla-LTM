#include "reduce_node.h"
#include <unistd.h>

char * generate_code(node_t * root , char ** buffer){
    dup2(STDERR_FILENO , STDOUT_FILENO);
    dup2(STDOUT_FILENO , STDERR_FILENO);
    char * code = handle_reduction(root);
    printf("%s\n" , code);
    *buffer = code;
    dup2(STDOUT_FILENO , STDERR_FILENO);
    dup2(STDERR_FILENO , STDOUT_FILENO);
    return code;
}
