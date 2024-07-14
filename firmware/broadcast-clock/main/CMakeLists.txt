idf_component_register( SRCS "app_main.cpp"
                             "components/application.cpp"
                             "components/configuration.cpp"
                             "components/clock_face.cpp"
                             "components/ambient_sensor.cpp"
                             "components/wifi.cpp"
                             "components/captive_portal_dns.cpp"
                             "components/captive_portal_http.cpp"
                             "components/dial.cpp"
                             "components/dotmatrix.cpp"
                INCLUDE_DIRS "."
              EMBED_TXTFILES "../resources/html/control_panel.html" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCRON_USE_LOCAL_TIME" )
