PROJECT(AgmdNetwork)

INCLUDE_DIRECTORIES(
	${AGMDENGINE_SOURCE_DIR}/src/AgmdNetwork
	${AGMDENGINE_SOURCE_DIR}/src/
	${AGMDENGINE_SOURCE_DIR}/dep
	)

FILE(
	GLOB_RECURSE
	source_files
	*.cpp
	*.h
	*.inl
	)
	
add_library(
	AgmdNetwork
	STATIC
	${source_files}
)
	
	