project('myproject', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++14'])

microhttp_dep = dependency('libmicrohttpd', required: true)

jsoncpp_dep = dependency('jsoncpp', required: true)

inc = include_directories('src')

sources = [
    'src/main.cpp',
    'src/Server.cpp',
    'src/HttpRequest.cpp',
    'src/HttpResponse.cpp',
    'src/Resource.cpp',
]

executable('myproject', sources,
  include_directories: inc,
  dependencies : [ microhttp_dep, jsoncpp_dep ],
  install : true)

