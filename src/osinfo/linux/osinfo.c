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

#include "../osinfo.h"
#include <sysinfo/errors.h>

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

static const char OS_RELEASE_PATH[] = "/etc/os-release";
static const char KERNEL_VERSION_PATH[] = "/proc/version";

/**
 * \brief (Linux-only) Retrieve a value from /etc/os-release given a key. The value of the first instance
 * of a key-value pair is used if the key is used more than once.
 *
 * \param key  key to find value for. Characters are read until a null character is encountered.
 * \param buff  pointer to character array to write result to
 * \param count  number of bytes allocated to buff. 128 is the maximum supported value. Larger values will be ignored.
 * 
 * \return sysinfo__error_code on failure
 */
sysinfo__error_code get_os_release_value(const char *key, char *buff, const size_t count)
{
    // Try to open file stream
    FILE *os_release_fd = fopen(OS_RELEASE_PATH, "r");
    if (os_release_fd == NULL)
    {
        perror("get_os_release_value");
        return MISSING_SYSTEM_FILE;
    }

    // Prepare line buffer
    const size_t line_len = 257;
    char line_buff[257];
    line_buff[256] = '\n';

    // Prep key-value buffers
    char key_buff[25];
    key_buff[24] = '\0';
    char val_buff[129];
    val_buff[128] = '\0';

    // Search for matching key
    bool key_found = false;
    size_t val_len = 0;
    do
    {
        if (fgets(line_buff, (int) (line_len), os_release_fd) == NULL)
        {
            break;
        }

        sscanf(line_buff, "%24[A-Z]%*[=]\"%128[^\"\n]\"", key_buff, val_buff); // Read key-value pair

        if (strcmp(key, key_buff) == 0)
        {
            // Keys match, so copy value to buff.
            val_len = strlen(val_buff);
            if (val_len >= count)
            {
                strncpy(buff, val_buff, count);
            }
            else
            {
                strcpy(buff, val_buff);
            }

            key_found = true;
        }
    } while (!key_found);

    // Clean up
    fclose(os_release_fd);

    if (key_found)
    {
        return SUCCESS;
    }
    return RELEASE_KEY_NOT_FOUND;
}

/**
 * \brief Retrieve the name of the host OS.
 *
 * \param buff  pointer to character array to write result to
 * \param count  number of bytes allocated to buff
 *
 * \return sysinfo__error_code on failure
 */
int sysinfo_get_os_name(char *buff, const size_t count)
{
    const char key[] = "NAME";
    return get_os_release_value(key, buff, count);
}

/**
 * \brief Retrieve the version string of the host OS.
 * 
 * \param buff  pointer to character array to write result to
 * \param count  number of bytes allocated to buff
 * 
 * \return sysinfo__error_code on failure
 */
int sysinfo_get_os_version(char *buff, const size_t count)
{
    const char key[] = "VERSION";
    return get_os_release_value(key, buff, count);
}

/**
 * \brief Retrieve info on the running kernel.
 * 
 * \return pointer to a new sysinfo_kernel_info_t struct on success or NULL on failure.
 */
sysinfo_kernel_info_t *sysinfo_get_kernel_info()
{
    sysinfo_kernel_info_t *k_info = (sysinfo_kernel_info_t *) (malloc(sizeof(sysinfo_kernel_info_t)));

    FILE *kernel_version_fd = fopen(KERNEL_VERSION_PATH, "r");
    if (kernel_version_fd == NULL)
    {
        perror("sysinfo_get_kernel_info");
        return NULL;
    }

    uint32_t major;
    uint32_t minor;
    uint32_t patch;
    uint32_t distro_patch;
    char tag[25];
    char arch[13];

    // Parse version string
    fscanf(kernel_version_fd, "%*[^0-9]%u%*[.]%u%*[.]%u-%u%*[.]%24[^.]%*[.]%12s",
           &major, &minor, &patch, &distro_patch, tag, arch);

    k_info->major = (uint8_t)(major);
    k_info->minor = (uint8_t)(minor);
    k_info->patch = (uint16_t)(patch);
    k_info->distro_patch = (uint16_t)(patch);
    strcpy(k_info->tag, tag);
    strcpy(k_info->arch, arch);

    fclose(kernel_version_fd);
    return k_info;
}
