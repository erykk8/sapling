target_sources(Grammar
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/Token.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Productions.cpp"
    PUBLIC
        "${CMAKE_CURRENT_LIST_DIR}/Token.h"
        "${CMAKE_CURRENT_LIST_DIR}/Productions.h"
)