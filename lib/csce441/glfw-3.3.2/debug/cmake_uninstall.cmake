
if (NOT EXISTS "/Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/install_manifest.txt")
  message(FATAL_ERROR "Cannot find install manifest: \"/Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/install_manifest.txt\"")
endif()

file(READ "/Users/wangyingjian/desktop/main/lib/csce441/glfw-3.3.2/debug/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")

foreach (file ${files})
  message(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
  if (EXISTS "$ENV{DESTDIR}${file}")
    exec_program("/private/var/folders/x5/y108qr5n6vq19tf9hqbty_1r0000gn/T/AppTranslocation/1260E3F6-2FFE-4E1B-BE09-64548FCF2234/d/CMake.app/Contents/bin/cmake" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
                 OUTPUT_VARIABLE rm_out
                 RETURN_VALUE rm_retval)
    if (NOT "${rm_retval}" STREQUAL 0)
      MESSAGE(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    endif()
  elseif (IS_SYMLINK "$ENV{DESTDIR}${file}")
    EXEC_PROGRAM("/private/var/folders/x5/y108qr5n6vq19tf9hqbty_1r0000gn/T/AppTranslocation/1260E3F6-2FFE-4E1B-BE09-64548FCF2234/d/CMake.app/Contents/bin/cmake" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
                 OUTPUT_VARIABLE rm_out
                 RETURN_VALUE rm_retval)
    if (NOT "${rm_retval}" STREQUAL 0)
      message(FATAL_ERROR "Problem when removing symlink \"$ENV{DESTDIR}${file}\"")
    endif()
  else()
    message(STATUS "File \"$ENV{DESTDIR}${file}\" does not exist.")
  endif()
endforeach()

