#####
# 'RobotArm' Deployment:
#
# This registers the 'RobotArm' deployment to the build system. 
# Custom components that have not been added at the project-level should be added to 
# the list below.
#
#####

###
# Topology and Components
###
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Top/")

# Add custom components to this specific deployment here
# add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/MyComponent/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/ServoPort")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/ArmDemo")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/PcaServo")


set(SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/Main.cpp")
set(MOD_DEPS ${FPRIME_CURRENT_MODULE}/Top)

register_fprime_deployment()
