target_sources(Parser
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/Function.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/IfBlock.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Instruction.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Parser.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Program.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/ValueExpression.cpp"
    PUBLIC
        "${CMAKE_CURRENT_LIST_DIR}/Parser.h"
)

target_link_libraries(Parser PUBLIC Token)
target_link_libraries(Parser PUBLIC AST)
target_link_libraries(Parser PUBLIC Scanner)