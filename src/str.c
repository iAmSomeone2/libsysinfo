#include "str.h"

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
// #include <math.h>

/**
 * \brief Initializes a new instance of sysinfo__str.
 * 
 * \param in_str  Pointer to string for the sysinfo__str instance to manage. If a NULL
 * pointer is used, the instance will contain and empty string with a length of 0.
 * 
 * \return sysinfo__str 
 */
sysinfo__str sysinfo__init_str(const char * restrict in_str) {
    sysinfo__str new_str = (sysinfo__str)(malloc(sizeof(str_t)));
    
    if (in_str != NULL) {
        new_str->length = strnlen(in_str, UINT32_MAX);
    } else {
        new_str->length = 0;
    }

    // TODO: Allocate 150% of in_str's length to new_str->data to avoid some reallocs
    // new_str->size = new_str->length + (new_str->length >> 1);
    new_str->size = new_str->length+1;
    new_str->data = (char*)(malloc(new_str->size * sizeof(char)));
    
    if (new_str->length > 0) {
        strcpy(new_str->data, in_str);
    } else {
        new_str->data[0] = '\0';
    }

    return new_str;
}

/**
 * \brief Safely frees the resources used by the provided sysinfo__str.
 * 
 * \param inst  instance of sysinfo__str to free
 */
void sysinfo__free_str(const restrict sysinfo__str inst) {
    free(inst->data);
    inst->length = 0;
    inst->size = 0;
}

/**
 * \brief Retrieves the length of string data in the provided sysinfo__str.
 * 
 * \param inst  sysinfo__str instance to check
 * \return length of stored string data
 */
inline uint32_t sysinfo__str_get_length(const restrict sysinfo__str inst) {
    return inst->length;
}

inline uint32_t sysinfo__str_get_size(const restrict sysinfo__str inst) {
    return inst->size;
}