idf_component_register(INCLUDE_DIRS .)

add_prebuilt_library(forte "lib/${CONFIG_IDF_TARGET}/src/libforte-static.a"
             PRIV_REQUIRES 
                 log 
                 button
                 led_strip
                 forte_main
                 lua
                 nvs_flash)

target_link_libraries(${COMPONENT_LIB} INTERFACE forte)
