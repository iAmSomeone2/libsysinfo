#ifndef SYSINFO__STR_H
#define SYSINFO__STR_H

#include <stdint.h>

/**
 * \brief Basic managed string structure
 */
typedef struct str {
    /** Raw character data of string */
    char *data;
    /** Number of string characters in the data array not including the null-terminator */
    uint32_t length;
    /** Number of bytes currently allocated to the data array */
    uint32_t size;
} str_t;

/**
 * \brief SysInfo managed string object
 * 
 * \details Use sysinfo__init_str() and sysinfo__free_str() to initialize a new instance
 * and de-init, respectively.
 */
typedef str_t* sysinfo__str;

/**
 * \brief Initializes a new instance of sysinfo__str.
 * 
 * \param in_str  Pointer to string for the sysinfo__str instance to manage. If a NULL
 * pointer is used, the instance will contain and empty string with a length of 0.
 * 
 * \return sysinfo__str 
 */
sysinfo__str sysinfo__init_str(const char * restrict in_str);

/**
 * \brief Safely frees the resources used by the provided sysinfo__str.
 * 
 * \param inst  instance of sysinfo__str to free
 */
void sysinfo__free_str(const restrict sysinfo__str inst);

/**
 * @brief Sets the string in the sysinfo__str instance to the new provided string.
 * 
 * @param inst
 * @param new_str 
 */
void sysinfo__set_str(const restrict sysinfo__str inst, const char * restrict new_str);

/**
 * \brief Retrieves the length of string data in the provided sysinfo__str.
 * 
 * \param inst  sysinfo__str instance to check
 * \return length of stored string data
 */
uint32_t sysinfo__str_get_length(const restrict sysinfo__str inst);

#endif // SYSINFO__STR_H