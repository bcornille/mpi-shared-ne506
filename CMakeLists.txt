# Setup the project name and required cmake version.
cmake_minimum_required (VERSION 2.8.12.2)
project (ShMemMC)
set (ShMemMC_VERSION_MAJOR 0)
set (ShMemMC_VERSION_MINOR 1)

# Add subdirectories
add_subdirectory (src)
#add_subdirectory (test)

# Create documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
	add_custom_target(docs
		${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating API documentation with Doxygen" VERBATIM
		)
	set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${CMAKE_CURRENT_BINARY_DIR}/docs)
endif(DOXYGEN_FOUND)
