################################################################################################
# Project CAP/Identity
################################################################################################
ROOT_GENERATE_DICTIONARY(G__Identity LineShape.hpp LINKDEF IdentityLinkDef.h)

################################################################################################
# Create a shared library with geneated dictionary
################################################################################################
add_compile_options(-Wall -Wextra -pedantic)
add_library(Identity SHARED LineShape.cpp G__Identity.cxx)

target_link_libraries(Identity Base ${ROOT_LIBRARIES} ${EXTRA_LIBS} )
target_include_directories(Identity  PUBLIC Identity Base ${EXTRA_INCLUDES} )

install(FILES  "${CMAKE_CURRENT_BINARY_DIR}/libIdentity.rootmap" "${CMAKE_CURRENT_BINARY_DIR}/libIdentity_rdict.pcm" DESTINATION "$ENV{CAP_LIB}")
install(TARGETS Identity  LIBRARY DESTINATION "$ENV{CAP_LIB}")

