#ifndef SYSINFO_OSINFO_H
#define SYSINFO_OSINFO_H

#include <string.h>

/**
 * \brief Family to which an OS belongs
 * 
 * \details An OS's family is the general group to which an OS belongs. This would, for example,
 * group Windows 10 and 11 together or group Mac OS X, macOS 11, and macOS 12 together.
 * This is most useful for Linux distributions since the number of distros is constantly changing,
 * and not all distro names are related -- Ubuntu, Fedora, and Arch Linux, for example.
 */
typedef enum os_family {
    /** Any Linux distribution */
    LINUX,
    /** Mac OS X or macOS 11 and up */
    MACOS,
    /** Windows 10 or 11*/
    WINDOWS,
    /** Unsupported OS */
    UNKNOWN
} sysinfo__os_family;

/**
 * \brief Information about the running operating system
 * 
 */
typedef struct osinfo {
    /**
     * \brief Family of current OS
     * \see sysinfo__os_family
     */
    const sysinfo__os_family family;

    /**
     * \brief Name of current OS
     */
    // const sysinfo__str name;
} sysinfo__osinfo_t;

#endif // SYSINFO_OSINFO_H