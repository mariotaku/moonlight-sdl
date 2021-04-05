cmake_minimum_required (VERSION 3.6)

unset(CMAKE_LIBRARY_OUTPUT_DIRECTORY)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/assets/lib)

pkg_check_modules(UMEDIA_API REQUIRED umedia_api_c)
pkg_check_modules(GLIB REQUIRED glib-2.0)
pkg_check_modules(MEDIARESCALC REQUIRED media-resource-calculator)

set(COMMON_SRC
    dile_platform.c
    dile_video.c
    lunasynccall.c
    utils.c
)

add_library(moonlight-dile SHARED ${COMMON_SRC} current/services_current.c current/VideoOutputService.c)

target_include_directories(moonlight-dile PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/app/stream/video
    ${CMAKE_SOURCE_DIR}/app
)
target_link_libraries(moonlight-dile moonlight-common-c dile_vdec_direct helpers
    ${GLIB_LIBRARIES} ${PBNJSON_LIBRARIES} ${LUNA_SERVICE_LIBRARIES} resource_mgr_client_c ${MEDIARESCALC_LIBRARIES})
target_include_directories(moonlight-dile SYSTEM PRIVATE
    ${GLIB_INCLUDE_DIRS} ${PBNJSON_INCLUDE_DIRS} ${LUNA_SERVICE_INCLUDE_DIRS} ${UMEDIA_API_INCLUDE_DIRS} ${MEDIARESCALC_INCLUDE_DIRS})

target_compile_definitions(moonlight-dile PUBLIC HAVE_DILE PRIVATE DECODER_PLATFORM_NAME=dile)

# DILE for webOS 4.x and below

add_library(moonlight-dile-legacy SHARED ${COMMON_SRC}
    legacy/services_legacy.c
    legacy/VideoSinkManagerService.c
    legacy/AcbService.c
    legacy/TVService.c
)

target_include_directories(moonlight-dile-legacy PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/app/stream/video
    ${CMAKE_SOURCE_DIR}/app
)

target_link_libraries(moonlight-dile-legacy moonlight-common-c dile_vdec_direct helpers AcbAPI
    ${GLIB_LIBRARIES} ${PBNJSON_LIBRARIES} ${LUNA_SERVICE_LIBRARIES} resource_mgr_client_c ${MEDIARESCALC_LIBRARIES})
target_include_directories(moonlight-dile-legacy SYSTEM PRIVATE
    ${GLIB_INCLUDE_DIRS} ${PBNJSON_INCLUDE_DIRS} ${LUNA_SERVICE_INCLUDE_DIRS} ${UMEDIA_API_INCLUDE_DIRS} ${MEDIARESCALC_INCLUDE_DIRS})

target_compile_definitions(moonlight-dile-legacy PUBLIC HAVE_DILE_LEGACY PRIVATE DECODER_PLATFORM_NAME=dile_legacy)