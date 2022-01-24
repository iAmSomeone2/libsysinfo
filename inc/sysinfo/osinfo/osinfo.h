#ifndef SYSINFO_OSINFO_H
#define SYSINFO_OSINFO_H

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

#endif // SYSINFO_OSINFO_H