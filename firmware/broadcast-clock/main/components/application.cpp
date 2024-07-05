#include "application.hpp"

using namespace espena::broadcast_clock;

application::
application() {
    
}

application::
~application() {

}

void application::
init() {
    m_clock_face.init();
}