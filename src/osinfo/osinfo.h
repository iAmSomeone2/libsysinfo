// libsysinfo
//     Copyright (C) 2022 Brenden Davidson
//
//     This program is free software: you can redistribute it and/or modify
//     it under the terms of the GNU Lesser General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.
//
//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU Lesser General Public License for more details.
//
//     You should have received a copy of the GNU Lesser General Public License
//     along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef SYSINFO_OSINFO_H
#define SYSINFO_OSINFO_H

#include <errors.h>
#include <stddef.h>

// ====================
// Static Platform Info
// ====================
// Data determined at compile time.

/**
 * \brief Family to which an OS belongs
 * 
 * \details An OS's family is the general group to which an OS belongs. This would, for example,
 * group Windows 10 and 11 together or group Mac OS X, macOS 11, and macOS 12 together.
 * This is most useful for Linux distributions since the number of distros is constantly changing,
 * and not all distro names are related -- Ubuntu, Fedora, and Arch Linux, for example.
 */
enum os_family {
    /** Any Linux distribution */
    LINUX,
    /** Mac OS X or macOS 11 and up */
    MACOS,
    /** Windows 10 or 11*/
    WINDOWS,
    /** Unsupported OS */
    UNKNOWN
};

/**
 * \brief Compiled architecture of running OS.
 * 
 * \details May be different from native architecture of CPU.
 * For example, the OS is compiled for x86, but the CPU supports x86_64.
 */
enum os_arch {
    X86,
    X86_64,
    AARCH64
};

/**
 * \brief Compiled architecture of OS.
 * 
 * \details May be different from native architecture of CPU.
 * For example, the OS is compiled for x86, but the CPU supports x86_64.
 */
// static const char SYSINFO_OS_ARCH[] =
// #if (defined __amd64__) || (defined __x86_64__)
// "x86_64";
// #elif (defined __aarch64__) || (defined __arm64__)
// "AArch64";
// #endif

// ================
// OS-Agnostic Data
// ================
// Functions and data which may be used on any OS.

/**
 * Retrieve the name of the host OS.
 *
 * \param buff  pointer to character array to write result to
 * \param count  number of bytes allocated to buff
 *
 * \return number of bytes written to buff
 */
int sysinfo_get_os_name(char *buff, size_t count);

/**
 * Retrieve the version string of the host OS.
 *
 * \param buff  pointer to character array to write result to
 * \param count  number of bytes allocated to buff
 *
 * \return number of bytes written to buff
 */
int sysinfo_get_os_version(char *buff, size_t count);

// =================
// OS Info Structure
// =================
// Functions and data specific to each supported OS family.

/**
 * \brief Read-only information about the running operating system
 */
typedef struct osinfo {
    /**
     * \brief Family of current OS
     * \see os_family
     */
    const enum os_family family;

    /** Number of bytes allocated to name */
    const uint8_t name_len;
    /** Name of current OS */
    const char *name;

    /** Number of bytes allocated to version_str */
    const uint8_t version_str_len;
    /** OS's version string */
    const char *version_str;

    /** Number of bytes allocated to os_arch */
    const uint8_t os_arch_len;
    /**
     * \brief Compiled architecture of OS.
     * 
     * \details May be different from native architecture of CPU.
     * For example, the OS is compiled for x86, but the CPU supports x86_64.
     */
    const char *os_arch;
} osinfo_t;

// ========================= Instance Management ===========================

/**
 * \brief Creates a new instance of osinfo_t and returns a pointer to it.
 * 
 * \details The exact way osinfo_t is initialized is dependent on each OS.
 * 
 * \return an osinfo_t pointer
 */
osinfo_t *init_osinfo();

/**
 * \brief Cleans up resources used by the provided osinfo_t instance.
 * 
 * \param inst  pointer to the osinfo_t instance to free
 */
void free_osinfo(const osinfo_t * restrict inst);

// ================================ Getters =================================

/**
 * \brief Retrieves the OS Family enum value from the provided osinfo_t instance.
 * 
 * \param inst  pointer to the osinfo_t instance
 * \return the os_family for the current OS
 */
const enum os_family osinfo_get_family(const osinfo_t * restrict inst);

/**
 * \brief Gets the name of the current OS.
 * 
 * \details Caller does not need to, and should not, free the string data from the
 * returned pointer's location. The osinfo_t instance manages it.
 * 
 * \param inst  pointer to the osinfo_t instance
 * \return pointer to the managed name string
 */
const char *osinfo_get_name(const osinfo_t * restrict inst);

/**
 * \brief Gets the version name string of the current OS. For example, "Windows 10", "macOS Big Sur", etc.
 * 
 * \details Caller does not need to, and should not, free the string data from the
 * returned pointer's location. The osinfo_t instance manages it.
 * 
 * \param inst  pointer to the osinfo_t instance
 * \return pointer to the managed version name string
 */
const char *osinfo_get_version(const osinfo_t * restrict inst);

const char *osinfo_get_arch(const osinfo_t * restrict inst);

#if defined __linux__
// +++++++++++++++++++
// Linux-Only Features
// +++++++++++++++++++

#include <stddef.h>
#include <inttypes.h>

// -------
// OS Info
// -------

/**
 * \brief Characteristics of the running kernel.
 */
typedef struct kernel_info {
    /** Major version */
    uint8_t     major;
    /** Minor version */
    uint8_t     minor;
    /** Patch version */
    uint16_t     patch;
    /** Distro-specific patch version */
    uint16_t    distro_patch;
    /** Tag (ex. fc35, MANJARO, generic, etc.) */
    char        tag[25];
    /** Compiled architecture */
    char        arch[13];
} sysinfo_kernel_info_t;

/**
 * \brief (Linux-only) Retrieve the version string of the running kernel.
 * 
 * \param buff  pointer to character array to write result to
 * \param count  number of bytes allocated to buff
 * 
 * \return number of bytes written to buff
 */
sysinfo_kernel_info_t *sysinfo_get_kernel_info();

#elif (defined __APPLE__) && (defined __MACH__) // macOS-specific features

// +++++++++++++++++++
// macOS-Only Features
// +++++++++++++++++++

#else

// ++++++++++++++
// Unsupported OS
// ++++++++++++++

#endif
// End OS detection block

#endif // SYSINFO_OSINFO_H