#include "components/application.hpp"

extern "C" void app_main() {
    espena::broadcast_clock::application the_app;
    the_app.init();
    while( true ) {
        vTaskDelay( 1 );
    }
}