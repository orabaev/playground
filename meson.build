project(
      'playground'
    , 'cpp'
    , default_options : ['cpp_std=c++2a']
)

test_sources = [
       'src/main.t.cpp' 
     , 'src/mdim_container.t.cpp'
]

exec = executable(
      'playground'
    , test_sources
)

test('test' , exec)
