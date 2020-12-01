file(GLOB src "*.c")
set(src_res )
if (WIN32)
if(MINGW)
  set(CMAKE_RC_COMPILER_INIT windres)
  ENABLE_LANGUAGE(RC)
  SET(CMAKE_RC_COMPILE_OBJECT
    "<CMAKE_RC_COMPILER> <FLAGS> -O coff <DEFINES> -i <SOURCE> -o <OBJECT>")
  file(GLOB src_res "*.rc")
endif(MINGW)
endif(WIN32)

add_executable(launch ${src} ${src_res})
target_link_libraries(launch icode)