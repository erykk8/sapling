target_sources(AST
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/Expression.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Function.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/IfBlock.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Program.cpp"
    PUBLIC
        "${CMAKE_CURRENT_LIST_DIR}/Program.h"
        "${CMAKE_CURRENT_LIST_DIR}/Function.h"
        "${CMAKE_CURRENT_LIST_DIR}/Expression.h"
        "${CMAKE_CURRENT_LIST_DIR}/Parameter.h"
        "${CMAKE_CURRENT_LIST_DIR}/IfBlock.h"
)

target_link_libraries(AST PUBLIC Token)