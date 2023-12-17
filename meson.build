project(
  'redfish_event','cpp',
        version : '1.0',
        meson_version: '>=0.63.0',
        default_options: [
            'b_lto_mode=default',
            'b_lto_threads=0',
            'b_lto=true',
            'b_ndebug=if-release',
            'buildtype=debugoptimized',
            'cpp_rtti=false',
            'cpp_std=c++20',
            'warning_level=3',
            'werror=true',
           ])

redfish_event_sources = [
    'src/redfish_event.cpp'
]


REDFISH_EVENT_ARGS=['-DBOOST_URL_NO_SOURCE_LOCATION']
openssl_dep = dependency('openssl', version: '>=1.1.1')
boost_dep = dependency('boost',modules: ['coroutine','url'])
json_dep = dependency('nlohmann_json')
#bmcweb=subproject('bmcweb')
reactor=subproject('reactor')
core_includes = include_directories(['./include',
'./subprojects/bmcweb/http',
'./subprojects/bmcweb/include',
'./subprojects/bmcweb/config',
'./subprojects/bmcweb/redfish-core/include',
'./subprojects/nghttp2-1.54.0/lib/includes',
'./subprojects/bmcweb/plugin-ifaces'])

nghttp2 = dependency('libnghttp2', version: '>=1.52.0', required : false)
if not nghttp2.found()
  cmake = import('cmake')
  opt_var = cmake.subproject_options()
  opt_var.add_cmake_defines({
    'ENABLE_LIB_ONLY': true,
    'ENABLE_STATIC_LIB': true
  })
  nghttp2_ex = cmake.subproject('nghttp2', options: opt_var)
  nghttp2 = nghttp2_ex.dependency('nghttp2')
endif

redfish_event_dep = declare_dependency(
	include_directories : core_includes,
	dependencies : [dependency('threads'),openssl_dep,boost_dep,nghttp2]
)
redfish_event_deps = [
json_dep,boost_dep,openssl_dep
]



redfish_event = library('redfish_event', 
    sources : redfish_event_sources,
    include_directories : core_includes,
    dependencies : redfish_event_deps,
    cpp_args : REDFISH_EVENT_ARGS,
    link_with : [])
    


