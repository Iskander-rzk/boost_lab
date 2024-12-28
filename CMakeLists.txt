cmake_minimum_required(VERSION 3.10)

# Настройка версии с использованием переменной GITHUB_RUN_NUMBER
if(DEFINED ENV{GITHUB_RUN_NUMBER})
    set(PATCH_VERSION $ENV{GITHUB_RUN_NUMBER})
else()
    set(PATCH_VERSION "1")
endif()

set(PROJECT_VERSION "0.0.${PATCH_VERSION}")
project(helloworld VERSION ${PROJECT_VERSION})

# Найти Boost для тестирования
find_package(Boost REQUIRED COMPONENTS unit_test_framework)

# Генерация version.h из version.h.in
configure_file(version.h.in version.h)

# Добавление исполняемых файлов и библиотек
add_executable(helloworld_cli main.cpp)
add_library(helloworld lib.cpp)
add_executable(test_version test_version.cpp)

# Настройки стандартов C++
set_target_properties(helloworld_cli helloworld test_version PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

# Установка директории для заголовочных файлов
target_include_directories(helloworld
    PRIVATE "${CMAKE_BINARY_DIR}"
)

# Настройки для тестов
target_include_directories(test_version
    PRIVATE ${Boost_INCLUDE_DIR}
)
target_link_libraries(test_version
    PRIVATE ${Boost_LIBRARIES}
    helloworld
)

# Линковка helloworld_cli с helloworld
target_link_libraries(helloworld_cli PRIVATE helloworld)

# Настройки компилятора в зависимости от платформы
if (MSVC)
    target_compile_options(helloworld_cli PRIVATE /W4)
    target_compile_options(helloworld PRIVATE /W4)
    target_compile_options(test_version PRIVATE /W4)
else ()
    target_compile_options(helloworld_cli PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(helloworld PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(test_version PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# Установка для macOS и Linux
if (APPLE)
    set(CPACK_GENERATOR "Bundle")
    set(CPACK_PACKAGE_NAME "helloworld")
    set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
    set(CPACK_PACKAGE_FILE_NAME "helloworld-${PROJECT_VERSION}-${CMAKE_SYSTEM_NAME}")
    set(CPACK_BUNDLE_NAME "helloworld")
    set(CPACK_BUNDLE_PLIST "${CMAKE_SOURCE_DIR}/Info.plist")
    set(CPACK_BUNDLE_ICON "${CMAKE_SOURCE_DIR}/AppIcon.icns")
elseif (UNIX)
    set(CPACK_GENERATOR "DEB")
    set(CPACK_PACKAGE_NAME "helloworld")
    set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
    set(CPACK_PACKAGE_FILE_NAME "helloworld-${PROJECT_VERSION}-Linux")
endif()

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

# Настройка тестов
enable_testing()
add_test(NAME test_version COMMAND test_version)

message("Configured PATCH_VERSION: ${PATCH_VERSION}")
message("Configured PROJECT_VERSION: ${PROJECT_VERSION}")