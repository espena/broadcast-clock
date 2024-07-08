idf_component_register( SRCS "app_main.cpp"
                             "components/application.cpp"
                             "components/clock_face.cpp"
                             "components/ambient_sensor.cpp"
                             "components/wifi.cpp"
                             "components/dial.cpp"
                             "components/dotmatrix.cpp"
                        INCLUDE_DIRS "." )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCRON_USE_LOCAL_TIME" )