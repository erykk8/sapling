target_sources(Scanner
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/AlphaToken.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/BraceToken.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/EqualsToken.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/OperatorToken.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/ValueToken.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Predicates.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/IO.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Scanner.cpp"
    PUBLIC
        "${CMAKE_CURRENT_LIST_DIR}/IO.h"
        "${CMAKE_CURRENT_LIST_DIR}/Scanner.h"
)

target_link_libraries(Scanner PUBLIC Token)