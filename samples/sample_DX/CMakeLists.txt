PROJECT(Demo)

INCLUDE_DIRECTORIES(
	${AGMDENGINE_SOURCE_DIR}/src/Agmd3D
	${AGMDENGINE_SOURCE_DIR}/src/AgmdMaths
	${AGMDENGINE_SOURCE_DIR}/src/AgmdUtilities
	${AGMDENGINE_SOURCE_DIR}/src/AgmdNetwork
	${AGMDENGINE_SOURCE_DIR}/src
	${AGMDENGINE_SOURCE_DIR}/dep
	)

FILE(
	GLOB_RECURSE
	source_files
	*.cpp
	*.h
	*.inl
	)
	
add_executable(
	Demo
	${source_files}
)
target_link_libraries(
	Demo
	Agmd3D
	AgmdNetwork
	)