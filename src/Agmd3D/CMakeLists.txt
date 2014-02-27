PROJECT(Agmd3D)

INCLUDE_DIRECTORIES(
	${AGMDENGINE_SOURCE_DIR}/src/Agmd3D
	${AGMDENGINE_SOURCE_DIR}/src/AgmdMaths
	${AGMDENGINE_SOURCE_DIR}/src/AgmdUtilities
	${AGMDENGINE_SOURCE_DIR}/src
	${AGMDENGINE_SOURCE_DIR}/dep
	)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DAGMD3D_EXPORTS")
	
FILE(
	GLOB_RECURSE
	source_files
	*.cpp
	*.h
	*.inl
	)

	
add_library(
	Agmd3D
	SHARED
	${source_files}
)
target_link_libraries(
	Agmd3D 
	AgmdMaths
	AgmdUtilities
	${AGMDENGINE_SOURCE_DIR}/lib/DevIL/DevIL.lib
	${AGMDENGINE_SOURCE_DIR}/lib/DevIL/ILU.lib
	${AGMDENGINE_SOURCE_DIR}/lib/DevIL/ILUT.lib
	)