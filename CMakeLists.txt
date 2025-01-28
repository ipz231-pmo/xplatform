cmake_minimum_required (VERSION 3.16)
project ("XPlatform")

add_subdirectory("libs")
add_subdirectory("sfml")
add_subdirectory("glh")

#add_subdirectory("demo1")

add_subdirectory("BlockOutlining")
add_subdirectory("TestEventSystem")
add_subdirectory("native_grap")
add_subdirectory("Snake")


option(BUILD_WINAPIPROJECTS "Set true to add WINAPI Projects dir to build" ON)
if(BUILD_WINAPIPROJECTS)
	add_subdirectory("WINAPI")
endif(BUILD_WINAPIPROJECTS)
