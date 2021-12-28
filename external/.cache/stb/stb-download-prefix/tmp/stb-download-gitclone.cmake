
if(NOT "C:/animation3/animation3/external/.cache/stb/stb-download-prefix/src/stb-download-stamp/stb-download-gitinfo.txt" IS_NEWER_THAN "C:/animation3/animation3/external/.cache/stb/stb-download-prefix/src/stb-download-stamp/stb-download-gitclone-lastrun.txt")
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: 'C:/animation3/animation3/external/.cache/stb/stb-download-prefix/src/stb-download-stamp/stb-download-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "C:/animation3/animation3/cmake/../external/stb"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: 'C:/animation3/animation3/cmake/../external/stb'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "C:/Program Files/Git/cmd/git.exe" -c http.sslVerify=false clone --no-checkout --config "advice.detachedHead=false" --config "advice.detachedHead=false" "https://github.com/libigl/libigl-stb.git" "stb"
    WORKING_DIRECTORY "C:/animation3/animation3/cmake/../external"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/libigl/libigl-stb.git'")
endif()

execute_process(
  COMMAND "C:/Program Files/Git/cmd/git.exe" -c http.sslVerify=false checkout cd0fa3fcd90325c83be4d697b00214e029f94ca3 --
  WORKING_DIRECTORY "C:/animation3/animation3/cmake/../external/stb"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'cd0fa3fcd90325c83be4d697b00214e029f94ca3'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "C:/Program Files/Git/cmd/git.exe" -c http.sslVerify=false submodule update --recursive --init 
    WORKING_DIRECTORY "C:/animation3/animation3/cmake/../external/stb"
    RESULT_VARIABLE error_code
    )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: 'C:/animation3/animation3/cmake/../external/stb'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "C:/animation3/animation3/external/.cache/stb/stb-download-prefix/src/stb-download-stamp/stb-download-gitinfo.txt"
    "C:/animation3/animation3/external/.cache/stb/stb-download-prefix/src/stb-download-stamp/stb-download-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: 'C:/animation3/animation3/external/.cache/stb/stb-download-prefix/src/stb-download-stamp/stb-download-gitclone-lastrun.txt'")
endif()

