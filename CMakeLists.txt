cmake_minimum_required(VERSION 3.10.2)
project(Digital_Photo_Frame C)

set(CMAKE_C_STANDARD 90)

add_executable(Digital_Photo_Frame main.c Debug/debug_manager.c Debug/debug_manager.c Debug/debug_manager.c Debug/netprint.c Debug/stdout.c Display/disp_manager.c Display/fb.c Encoding/ascii.c Encoding/encoding_manager.c Encoding/utf-8.c Encoding/utf-16be.c Encoding/utf-16le.c Fonts/ascii.c Fonts/fonts_manager.c Fonts/freetype.c Fonts/gbk.c File/file.c include/config.h include/debug_manager.h include/disp_manager.h include/encoding_manager.h include/file.h include/fonts_manager.h include/input_manager.h include/page_manager.h include/pic_operation.h include/picfmt_manager.h include/render.h Input/input_manager.c Input/stdin.c Input/touchscreen.c Page/auto_page.c Page/browse_page.c Page/interval_page.c Page/main_page.c Page/manual_page.c Page/page_manager.c Page/setting_page.c Render/render.c Render/format/bmp.c Render/format/jpg.c Render/format/picfmt_manager.c Render/operation/merge.c Render/operation/zoom.c netprint_client.c Debug/debug_manager.c Debug/debug_manager.c Debug/debug_manager.c)
