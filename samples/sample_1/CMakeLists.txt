PROJECT(sample_1)

INCLUDE_DIRECTORIES(
	${AGMDENGINE_SOURCE_DIR}/src/Agmd3D
	${AGMDENGINE_SOURCE_DIR}/src/AgmdMaths
	${AGMDENGINE_SOURCE_DIR}/src/AgmdUtilities
	${AGMDENGINE_SOURCE_DIR}/src/AgmdNetwork
	${AGMDENGINE_SOURCE_DIR}/src
	${AGMDENGINE_SOURCE_DIR}/dep
	${WXWIDGET_DIR}/include
	${WXWIDGET_DIR}/lib/vc_dll/mswud
	)

FILE(
	GLOB_RECURSE
	source_files
	*.cpp
	*.h
	*.inl
	)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DWXUSINGDLL")

add_executable(
	sample_1
	${source_files}
)

target_link_libraries(sample_1 optimized ${AGMDENGINE_SOURCE_DIR}/lib/Release/wxmsw30u_gl.lib debug ${AGMDENGINE_SOURCE_DIR}/lib/Debug/AgmdMaths.lib)
target_link_libraries(sample_1 optimized ${AGMDENGINE_SOURCE_DIR}/lib/Release/wxmsw30u_gl.lib debug ${AGMDENGINE_SOURCE_DIR}/lib/Debug/AgmdUtilities.lib)
target_link_libraries(sample_1 optimized ${AGMDENGINE_SOURCE_DIR}/lib/Release/wxmsw30u_gl.lib debug ${AGMDENGINE_SOURCE_DIR}/lib/Debug/Agmd3D.lib)
target_link_libraries(sample_1 optimized ${WXWIDGET_DIR}/lib/vc_dll/wxmsw30u_gl.lib debug ${WXWIDGET_DIR}/lib/vc_dll/wxmsw30ud_gl.lib)
target_link_libraries(sample_1 optimized ${WXWIDGET_DIR}/lib/vc_dll/wxmsw30u_core.lib debug ${WXWIDGET_DIR}/lib/vc_dll/wxmsw30ud_core.lib)
target_link_libraries(sample_1 optimized ${WXWIDGET_DIR}/lib/vc_dll/wxbase30u.lib debug ${WXWIDGET_DIR}/lib/vc_dll/wxbase30ud.lib)
target_link_libraries(sample_1 optimized ${WXWIDGET_DIR}/lib/vc_dll/wxtiff.lib debug ${WXWIDGET_DIR}/lib/vc_dll/wxtiffd.lib)
target_link_libraries(sample_1 optimized ${WXWIDGET_DIR}/lib/vc_dll/wxjpeg.lib debug ${WXWIDGET_DIR}/lib/vc_dll/wxjpegd.lib)
target_link_libraries(sample_1 optimized ${WXWIDGET_DIR}/lib/vc_dll/wxpng.lib debug ${WXWIDGET_DIR}/lib/vc_dll/wxpngd.lib)
target_link_libraries(sample_1 optimized ${WXWIDGET_DIR}/lib/vc_dll/wxzlib.lib debug ${WXWIDGET_DIR}/lib/vc_dll/wxzlibd.lib)
target_link_libraries(sample_1 optimized ${WXWIDGET_DIR}/lib/vc_dll/wxregexu.lib debug ${WXWIDGET_DIR}/lib/vc_dll/wxregexud.lib)
target_link_libraries(sample_1 optimized ${WXWIDGET_DIR}/lib/vc_dll/wxexpat.lib debug ${WXWIDGET_DIR}/lib/vc_dll/wxexpatd.lib)
