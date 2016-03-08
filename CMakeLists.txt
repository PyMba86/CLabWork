# LabWork :: PyMba86
cmake_minimum_required(VERSION 3.3)

# Cmake :: Project Name
project(labWork)


# Cmake :: Flags
#FIXME CMAKE_CXX_FLAGS только для MinGW
if (MINGW)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -std=c++11 ")
endif()

set(win32_flags "-DWINVER=0x0500 -D_WIN32_IE=0x0500 -D_WIN32_WINNT=0x0500")
set(unicode_flags "-DUNICODE -D_UNICODE  -D__NO_INLINE__")


# Cmake :: Win32 libraries
set(win32_libs
        User32 Shell32 ComCtl32 ComDlg32 Gdi32 Msimg32
        WinMM AdvAPI32 Ole32 ShLwApi Vfw32 WinInet)

# Cmake :: Options
option(THEMES "Build project using Manifest" on)

# Cmake :: Module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# MinGW :: Compile resource using windres.exe
set(work_resource_rc ${CMAKE_CURRENT_SOURCE_DIR}/Resource.rc)

if (MINGW)
    set(work_resource_obj ${CMAKE_CURRENT_BINARY_DIR}/Resource.res.obj)
    set(windres_flags -O coff)
    if (THEMES)
        list(APPEND windres_flags -D RC_WITH_MANIFEST=1)
    endif()
    add_custom_command(OUTPUT ${work_resource_obj}
            COMMAND windres.exe ${windres_flags} -I. -i ${work_resource_rc} -o ${work_resource_obj}
            MAIN_DEPENDENCY ${work_resource_rc}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    set(RESOURCE ${work_resource_obj})
else()
    set(RESOURCE ${work_resource_rc})
endif()

# Cmake :: Vaca library found
find_package(Vaca REQUIRED)
include_directories(${VACA_INCLUDE_DIR})

# Cmake :: Function to add work
function(add_work name)
    # Source files of the target
        file(GLOB work_sources ${name}/*.cpp)
    # Header files of the target
        file(GLOB work_header ${name}/*.h)

    # Resource file to be used
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${name}/${name}.rc)
        set(work_resource_rc ${CMAKE_CURRENT_SOURCE_DIR}/${name}/${name}.rc)
        set(work_resource_obj ${CMAKE_CURRENT_BINARY_DIR}/${name}.res.obj)

    # Compile resource using windres.exe
        if(MINGW)
            add_custom_command(OUTPUT ${work_resource_obj}
                COMMAND windres.exe ${windres_flags} -I${name} -i ${work_resource_rc} -o ${work_resource_obj}
                MAIN_DEPENDENCY ${work_resource_rc}
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
        endif()
    else()
        set(work_resource_rc ${CMAKE_CURRENT_SOURCE_DIR}/Resource.rc)
        set(work_resource_obj ${CMAKE_CURRENT_BINARY_DIR}/Resource.res.obj)
    endif()

    if(MINGW)
        set(work_resource ${work_resource_obj})
    else()
        set(work_resource ${work_resource_rc})
    endif()

    # Add the Win32 target
    add_executable(${name} WIN32  ${work_header} ${work_sources} ${work_resource})

    # Setup after build flags
    set_target_properties(${name} PROPERTIES
        COMPILE_FLAGS "${win32_flags} ${unicode_flags}")

    # Dependencies with libraries
    target_link_libraries(${name}  ${VACA_LIBRARY}  ${win32_libs} )

# MSVC :: Compile manifest using mt.exe
if(THEMES AND MSVC)
    # TODO The following custom command fails with VC solutions
    #      because we have to known object-output directory for each
    #      example (e.g. "examples/Buttons.dir/Release" instead of "")
    add_custom_command(TARGET ${name}
            POST_BUILD
            COMMAND mt.exe
            -manifest "${CMAKE_CURRENT_SOURCE_DIR}\\Resource.manifest"
            -outputresource:$(ProjectDir)$(Configuration)\\$(TargetName)$(TargetExt);#1
            COMMENT "Adding manifest..."
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()
endfunction(add_work)

# LabWork :: Work
add_work(Work1)
add_work(Work2)

