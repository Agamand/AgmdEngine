PROJECT(AgmdUtilities)

INCLUDE_DIRECTORIES(
	${AGMDENGINE_SOURCE_DIR}/src/AgmdUtilities
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
	AgmdUtilities
	STATIC
	${source_files}
)
	
	