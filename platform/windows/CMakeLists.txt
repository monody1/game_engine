add_executable(win32_gdi)

target_sources(
        win32_gdi
        PRIVATE
        hello_win32_gdi.cpp
)

add_executable(win32_d2d)

target_sources(
        win32_d2d
        PRIVATE
        hello_win32_d2d.cpp
)

target_link_libraries(
        win32_d2d
        PRIVATE
        ole32.lib d2d1.lib user32.lib
)

add_executable(win32_d3d)

target_sources(
        win32_d3d
        PRIVATE
        hello_win32_d3d.cpp
)

target_compile_options(
        win32_d3d
        PRIVATE
        -I ./DirectXMath/Inc
)

target_link_libraries(
        win32_d3d
        PRIVATE
        user32.lib d3d11.lib d3dcompiler.lib
)

