project(
    'tictactoe',
    'cpp',
    default_options : ['cpp_std=c++20']
)

dependencies = [
    dependency('raylib'),
    dependency('nlohmann_json')
]

subdir('src')

executable('tictactoe', sources, dependencies: dependencies)
