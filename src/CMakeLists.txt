add_executable(fusselig
  forward_concept.cpp
  forward_object.cpp
  main.cpp
)

target_compile_features(fusselig
  PUBLIC
    cxx_std_20
)
