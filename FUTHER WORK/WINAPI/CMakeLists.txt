
option(BUILD_WINAPI_DEMO1 "Set true to add WINAPI demo1 proj to build" ON)
option(BUILD_WINAPI_DEMO2 "Set true to add WINAPI demo2 proj to build" ON) # Snake in console


if(BUILD_WINAPI_DEMO1)
	add_subdirectory("demo1")
endif(BUILD_WINAPI_DEMO1)

if(BUILD_WINAPI_DEMO2)
	add_subdirectory("demo2")
endif(BUILD_WINAPI_DEMO2)