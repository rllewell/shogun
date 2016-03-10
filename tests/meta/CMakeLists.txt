INCLUDE(PythonEnvironment)
GET_PYTHON_ENV()

# working directory of tester should be binary dir so link data folders
IF (NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/reference_results)
    EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_CURRENT_SOURCE_DIR}/reference_results" "${CMAKE_CURRENT_BINARY_DIR}/reference_results")
ENDIF()
IF (NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/generated_results)
    EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_CURRENT_SOURCE_DIR}/generated_results" "${CMAKE_CURRENT_BINARY_DIR}/generated_results")
ENDIF()
FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tester.py DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

FILE(GLOB META_INTEGRATION_REFERENCES reference_results/*/*.dat)
FOREACH(REFERENCE_FILE ${META_INTEGRATION_REFERENCES})
    # assume a structure <target_language>/<category>/result.dat
	STRING(REGEX REPLACE ".*/(.*).dat" "\\1" NAME ${REFERENCE_FILE})
	STRING(REGEX REPLACE ".*/(.*//.*).dat" "\\1" NAME_WITH_DIR ${REFERENCE_FILE})
	STRING(REGEX REPLACE "//" "_" NAME_WITH_DIR ${NAME_WITH_DIR})
    STRING(REGEX REPLACE ".*/(.*)//.*.dat" "\\1" REL_DIR ${REFERENCE_FILE})
	
	# cpp
	# TODO implement other languages tests
	# TODO tester.py should be written in c++ so that python_modular is not needed
	IF(PythonModular)
	    add_test(NAME integration_meta_cpp-${NAME_WITH_DIR}
		    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		    COMMAND ${PYTHON_EXECUTABLE} tester.py -r ${REL_DIR} -f ${NAME}.dat -t cpp -g generated_results -i reference_results
		    DEPENDS build_cpp_meta_examples)
        set_property(TEST integration_meta_cpp-${NAME_WITH_DIR} PROPERTY
			    ENVIRONMENT "${PYTHON_ENV_VARS}")
	ENDIF()
ENDFOREACH()
