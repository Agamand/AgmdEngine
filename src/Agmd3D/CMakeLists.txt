PROJECT(Agmd3D)

INCLUDE_DIRECTORIES(
	${AGMDENGINE_SOURCE_DIR}/src/Agmd3D
	${AGMDENGINE_SOURCE_DIR}/src/AgmdMaths
	${AGMDENGINE_SOURCE_DIR}/src/AgmdUtilities
	${AGMDENGINE_SOURCE_DIR}/src
	${WXWIDGET_DIR}/include
	${WXWIDGET_DIR}/lib/vc_dll/mswud
	${AGMDENGINE_SOURCE_DIR}/dep
	)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DAGMD3D_EXPORTS -DWXUSINGDLL")
	
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
target_link_libraries(Agmd3D AgmdMaths)
target_link_libraries(Agmd3D AgmdUtilities)
target_link_libraries(Agmd3D ${AGMDENGINE_SOURCE_DIR}/lib/DevIL/DevIL.lib)
target_link_libraries(Agmd3D ${AGMDENGINE_SOURCE_DIR}/lib/DevIL/ILU.lib)
target_link_libraries(Agmd3D ${AGMDENGINE_SOURCE_DIR}/lib/DevIL/ILUT.lib)
target_link_libraries(Agmd3D optimized ${WXWIDGET_DIR}/lib/vc_dll/wxmsw30u_gl.lib debug ${WXWIDGET_DIR}/lib/vc_dll/wxmsw30ud_gl.lib)
target_link_libraries(Agmd3D optimized ${WXWIDGET_DIR}/lib/vc_dll/wxmsw30u_core.lib debug ${WXWIDGET_DIR}/lib/vc_dll/wxmsw30ud_core.lib)
target_link_libraries(Agmd3D optimized ${WXWIDGET_DIR}/lib/vc_dll/wxbase30u.lib debug ${WXWIDGET_DIR}/lib/vc_dll/wxbase30ud.lib)
target_link_libraries(Agmd3D optimized ${WXWIDGET_DIR}/lib/vc_dll/wxtiff.lib debug ${WXWIDGET_DIR}/lib/vc_dll/wxtiffd.lib)
target_link_libraries(Agmd3D optimized ${WXWIDGET_DIR}/lib/vc_dll/wxjpeg.lib debug ${WXWIDGET_DIR}/lib/vc_dll/wxjpegd.lib)
target_link_libraries(Agmd3D optimized ${WXWIDGET_DIR}/lib/vc_dll/wxpng.lib debug ${WXWIDGET_DIR}/lib/vc_dll/wxpngd.lib)
target_link_libraries(Agmd3D optimized ${WXWIDGET_DIR}/lib/vc_dll/wxzlib.lib debug ${WXWIDGET_DIR}/lib/vc_dll/wxzlibd.lib)
target_link_libraries(Agmd3D optimized ${WXWIDGET_DIR}/lib/vc_dll/wxregexu.lib debug ${WXWIDGET_DIR}/lib/vc_dll/wxregexud.lib)
target_link_libraries(Agmd3D optimized ${WXWIDGET_DIR}/lib/vc_dll/wxexpat.lib debug ${WXWIDGET_DIR}/lib/vc_dll/wxexpatd.lib)

target_link_libraries(Agmd3D optimized ${WXWIDGET_DIR}/lib/vc_dll/wxmsw30u_propgrid.lib debug ${WXWIDGET_DIR}/lib/vc_dll/wxmsw30ud_propgrid.lib)
target_link_libraries(Agmd3D optimized ${WXWIDGET_DIR}/lib/vc_dll/wxmsw30u_aui.lib debug ${WXWIDGET_DIR}/lib/vc_dll/wxmsw30ud_aui.lib)


#target_link_libraries(Agmd3D ${WXWIDGET_DIR}/lib/vc_dll/winmm.lib)
#target_link_libraries(Agmd3D ${WXWIDGET_DIR}/lib/vc_dll/comctl32.lib)
#target_link_libraries(Agmd3D ${WXWIDGET_DIR}/lib/vc_dll/rpcrt4.lib)
#target_link_libraries(Agmd3D ${WXWIDGET_DIR}/lib/vc_dll/wsock32.lib)
#target_link_libraries(Agmd3D ${WXWIDGET_DIR}/lib/vc_dll/wininet.lib)

#opengl32.lib
#glu32.lib
