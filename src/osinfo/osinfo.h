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

#include "./errors.h"

#include <stddef.h>

// ====================
// Static Platform Info
// ====================
// Data determined at compile time. 

/**
 * \brief Compiled architecture of OS.
 * 
 * \details May be different from native architecture of CPU.
 * For example, the OS is compiled for x86, but the CPU supports x86_64.
 */
static const char SYSINFO_OS_ARCH[] =
#if (defined __amd64__) || (defined __x86_64__)
"x86_64";
#elif (defined __aarch64__) || (defined __arm64__)
"AArch64";
#endif

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

// ================
// OS-Specific Data
// ================
// Functions and data specific to each supported OS family.

#if (defined __unix__) && (defined __linux__)
// +++++++++++++++++++
// Linux-Only Features
// +++++++++++++++++++

#include <stddef.h>
#include <inttypes.h>

/**
 * Family of running OS.
 */
static const char SYSINFO_OS_FAMILY[] = "Linux";

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

#elif (defined __unix__) && (defined __darwin__) // macOS-specific features

// +++++++++++++++++++
// macOS-Only Features
// +++++++++++++++++++

static const char SYSINFO_OS_FAMILY[] = "macOS";
#else

// ++++++++++++++
// Unsupported OS
// ++++++++++++++

static const char SYSINFO_OS_FAMILY[] = "unknown";
#endif
// End OS detection block

#endif // SYSINFO_OSINFO_H