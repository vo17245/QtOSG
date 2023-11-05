add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/execution-charset:gbk>")

# 设置ide中目录结构
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakePredefinedTargets")

function(FolderTraRCS_GetDir result rootdir)
	file(GLOB_RECURSE all LIST_DIRECTORIES true ${rootdir}/*)
	foreach(fileordir ${all})
		if (IS_DIRECTORY ${fileordir})    
			LIST(APPEND alldir ${fileordir})
		endif()
	endforeach()
	set(${result} ${alldir} PARENT_SCOPE)
endfunction()

function(FolderTra_GetCode result rootdir)
	file(GLOB allcode "${rootdir}/*.h" "${rootdir}/*.hpp" "${rootdir}/*.cpp" "${rootdir}/*.c" "${rootdir}/*.ui" "${rootdir}/*.qrc")
	set(${result} ${allcode} PARENT_SCOPE)
endfunction()

function(FolderTraRCS_GetCode result rootdir)
	file(GLOB_RECURSE allcode "${rootdir}/*.h" "${rootdir}/*.hpp" "${rootdir}/*.cpp" "${rootdir}/*.c" "${rootdir}/*.ui" "${rootdir}/*.qrc")
	set(${result} ${allcode} PARENT_SCOPE)
endfunction()

function(SrcCodeGroup rootdir)
	FolderTraRCS_GetDir(dirlist ${rootdir})
	LIST(APPEND dirlist ${rootdir})
	foreach(dir ${dirlist})
		
		FolderTra_GetCode(dircode ${dir})
		list(LENGTH dircode len)	
		
		if (NOT (${dir} STREQUAL ${rootdir}))  
			string(REPLACE "${rootdir}" "" groupname ${dir})
			#message("${groupname}     ${len}")
			if (${len} STRGREATER 0)  
				source_group(${groupname} FILES ${dircode})
			endif()
		else()
			#message("/     ${len}")
			if (${len} STRGREATER 0) 
				source_group("/" FILES ${dircode})
			endif()
		endif()
		
	endforeach()
endfunction()

SrcCodeGroup(${PROJECT_SOURCE_DIR})
FolderTraRCS_GetCode(allcode ${PROJECT_SOURCE_DIR})
