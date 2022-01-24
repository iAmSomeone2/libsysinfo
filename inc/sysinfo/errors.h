#ifndef SYSINFO_OSINFO_ERRORS_H
#define SYSINFO_OSINFO_ERRORS_H

typedef enum error_code {
    SUCCESS,
    /** A required system file is missing or inaccessible. */
    MISSING_SYSTEM_FILE,
#if defined __linux__ // Linux-only codes
    /** The specified key could not be located in /etc/os-release */
    RELEASE_KEY_NOT_FOUND
#endif
} sysinfo__error_code;

#endif // SYSINFO_OSINFO_ERRORS_H