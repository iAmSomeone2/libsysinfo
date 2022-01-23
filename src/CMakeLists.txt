# libsysinfo
#     Copyright (C) 2022 Brenden Davidson
#
#     This program is free software: you can redistribute it and/or modify
#     it under the terms of the GNU Lesser General Public License as published by
#     the Free Software Foundation, either version 3 of the License, or
#     (at your option) any later version.
#
#     This program is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#     GNU Lesser General Public License for more details.
#
#     You should have received a copy of the GNU Lesser General Public License
#     along with this program.  If not, see <https://www.gnu.org/licenses/>.

set(sysinfo_sources
    "osinfo/${os_dir}/osinfo.c"
)


add_library(sysinfo ${sysinfo_sources})
target_compile_features(sysinfo PUBLIC c_std_11)

if(LINUX)
    find_package(math REQUIRED)
    target_link_libraries(sysinfo math)
endif()