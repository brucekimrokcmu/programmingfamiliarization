execute_process(COMMAND "/home/brucekimrok/catkin_ws/src/message_ui/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/brucekimrok/catkin_ws/src/message_ui/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
