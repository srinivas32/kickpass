#
# Copyright (c) 2015 Paul Fariello <paul@fariello.eu>
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#

find_package(Check)

if (CHECK_FOUND)
	macro(TEST_UNIT)
		set(oneValueArgs NAME FILE)
		set(multiValueArgs LIBS)
		cmake_parse_arguments(TEST_UNIT "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

		add_executable(test-${TEST_UNIT_NAME} ${TEST_UNIT_FILE})
		target_link_libraries(test-${TEST_UNIT_NAME} ${CHECK_LIBRARIES})
		target_link_libraries(test-${TEST_UNIT_NAME} ${TEST_UNIT_LIBS})
		set_property(TARGET test-${TEST_UNIT_NAME} APPEND PROPERTY INCLUDE_DIRECTORIES ${CHECK_INCLUDE_DIRS})
		add_test(NAME test-${TEST_UNIT_NAME}
			COMMAND test-${TEST_UNIT_NAME})
	endmacro(TEST_UNIT)
else()
	message(WARNING "Check not found. Skipping tests !")
	macro(TEST_UNIT)
	endmacro(TEST_UNIT)
endif()
