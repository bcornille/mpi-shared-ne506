# Executable for the program
add_executable (ShMemMC_MPI ShMemMC_MPI.c comms.c geoms.c materials.c source.c tally.c trans.c)

# Find MPI
find_package (MPI REQUIRED)
include_directories (SYSTEM ${MPI_INCLUDE_PATH} /home/bcornille/usr/sprng/sprng5/include)
target_link_libraries (ShMemMC_MPI ${MPI_C_LIBRARIES} m sprng)
set_source_files_properties (ShMemMC_MPI.c comms.c geoms.c materials.c source.c tally.c trans.c PROPERTIES LANGUAGE CXX)
