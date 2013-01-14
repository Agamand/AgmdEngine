PROJECT(DXRender)

INCLUDE_DIRECTORIES(
	${AGMDENGINE_SOURCE_DIR}/src/Agmd3D
	${AGMDENGINE_SOURCE_DIR}/src/AgmdMaths
	${AGMDENGINE_SOURCE_DIR}/src/AgmdUtilities
	${AGMDENGINE_SOURCE_DIR}/src/Renderer/DirectX
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
	
add_library(
	DXRender
	SHARED
	${source_files}
)
target_link_libraries(
	DXRender
	Agmd3D
	${AGMDENGINE_SOURCE_DIR}/lib/Cg/cgdx9.lib
	#${AGMDENGINE_SOURCE_DIR}/lib/Cg/cgdx10.lib
	#${AGMDENGINE_SOURCE_DIR}/lib/Cg/cgdx11.lib
	${AGMDENGINE_SOURCE_DIR}/lib/Cg/cg.lib
	${AGMDENGINE_SOURCE_DIR}/lib/GLU/glu32.lib
	)