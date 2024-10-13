#ifndef __GET_QUERY_FIELD__
#define __GET_QUERY_FIELD__

#include <string>

namespace espena::utils {

  inline std::string
  get_query_field( const std::string query, const std::string field ) {

    std::string key;
    std::string value;
    bool is_key = true;
    for( auto c : query ) {
      if( c == '?' ) {
        is_key = true;
        key = "";
        value = "";
        continue;
      }
      if( c == '&' ) {
        if( key == field ) {
          break;
        }
        is_key = true;
        key = "";
        value = "";
        continue;
      }
      if( c == '=' ) {
        is_key = false;
        continue;
      }
      if( is_key ) {
        key += c;
      }
      else {
        value += c;
      }
    }
    return field == key ? value : "";
  
  } // get_query_field

} // namespace espena::utils

#endif // __GET_QUERY_FIELD__

