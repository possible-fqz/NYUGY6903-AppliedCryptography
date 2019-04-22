project('CS6903-project2', 'cpp', default_options: ['cpp_std=c++14', 'warning_level=3'])

add_global_arguments('-I../src', language: 'cpp')

cxx = meson.get_compiler('cpp')
lib_ntl = cxx.find_library('ntl')

src = [
    'src/polyinvert.cpp',
    'src/main.cpp',
    'src/NTRU.cpp',
    'src/NTRUEncrypter.cpp',
    'src/util.cpp',
    'src/tests/test_NTRU.cpp',
    'src/tests/test_poly.cpp',
    'src/benchmark.cpp',
]

executable('out', src, dependencies: [lib_ntl])
