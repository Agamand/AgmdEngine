PROJECT(GLRender)

INCLUDE_DIRECTORIES(
	${AGMDENGINE_SOURCE_DIR}/src/Agmd3D
	${AGMDENGINE_SOURCE_DIR}/src/AgmdMaths
	${AGMDENGINE_SOURCE_DIR}/src/AgmdUtilities
	${AGMDENGINE_SOURCE_DIR}/src/Renderer/OpenGL
	${AGMDENGINE_SOURCE_DIR}/src
	${AGMDENGINE_SOURCE_DIR}/dep
	)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DOPENGL_EXPORTS")

FILE(
	GLOB_RECURSE
	source_files
	*.cpp
	*.h
	*.inl
	)
	
add_library(
	GLRender
	SHARED
	${source_files}
)
target_link_libraries(
	GLRender
	Agmd3D
	opengl32.lib
	${AGMDENGINE_SOURCE_DIR}/lib/Cg/cgGL.lib
	${AGMDENGINE_SOURCE_DIR}/lib/Cg/cg.lib
	${AGMDENGINE_SOURCE_DIR}/lib/GLU/glu32.lib
	)