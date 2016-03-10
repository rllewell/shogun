INCLUDE(PythonEnvironment)
GET_PYTHON_ENV()

FILE(GLOB META_INTEGRATION_REFERENCES reference_results/*/*.dat)
FOREACH(REFERENCE_FILE ${META_INTEGRATION_REFERENCES})
    # assume a structure <target_language>/<category>/result.dat
	STRING(REGEX REPLACE ".*/(.*).dat" "\\1" NAME ${REFERENCE_FILE})
	STRING(REGEX REPLACE ".*/(.*//.*).dat" "\\1" NAME_WITH_DIR ${REFERENCE_FILE})
	STRING(REGEX REPLACE "//" "_" NAME_WITH_DIR ${NAME_WITH_DIR})
    STRING(REGEX REPLACE ".*/(.*)//.*.dat" "\\1" REL_DIR ${REFERENCE_FILE})
	
	# cpp only for now
	add_test(NAME integration_meta_cpp-${NAME_WITH_DIR}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		COMMAND ${PYTHON_EXECUTABLE} tester.py -r ${REL_DIR} -f ${NAME}.dat -t cpp -g ${CMAKE_CURRENT_SOURCE_DIR}/generated_results -i ${CMAKE_CURRENT_SOURCE_DIR}/reference_results
		DEPENDS build_cpp_meta_examples)
set_property(TEST integration_meta_cpp-${NAME_WITH_DIR} PROPERTY
			ENVIRONMENT "${PYTHON_ENV_VARS}")
ENDFOREACH()
