PROJECT(AgmdMaths)

INCLUDE_DIRECTORIES(
	${AGMDENGINE_SOURCE_DIR}/src/AgmdMaths
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
	AgmdMaths
	STATIC
	${source_files}
)
	
	