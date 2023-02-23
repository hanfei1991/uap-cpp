set (YAML_LIBRARY_DIR "${PROJECT_SOURCE_DIR}/third-party/yaml-cpp")
set (YAML_SRCS
    ${YAML_LIBRARY_DIR}/src/binary.cpp
    ${YAML_LIBRARY_DIR}/src/emitterutils.cpp
    ${YAML_LIBRARY_DIR}/src/null.cpp
    ${YAML_LIBRARY_DIR}/src/scantoken.cpp
    ${YAML_LIBRARY_DIR}/src/convert.cpp
    ${YAML_LIBRARY_DIR}/src/exceptions.cpp
    ${YAML_LIBRARY_DIR}/src/ostream_wrapper.cpp
    ${YAML_LIBRARY_DIR}/src/simplekey.cpp
    ${YAML_LIBRARY_DIR}/src/depthguard.cpp
    ${YAML_LIBRARY_DIR}/src/exp.cpp
    ${YAML_LIBRARY_DIR}/src/parse.cpp
    ${YAML_LIBRARY_DIR}/src/singledocparser.cpp
    ${YAML_LIBRARY_DIR}/src/directives.cpp
    ${YAML_LIBRARY_DIR}/src/memory.cpp
    ${YAML_LIBRARY_DIR}/src/parser.cpp
    ${YAML_LIBRARY_DIR}/src/stream.cpp
    ${YAML_LIBRARY_DIR}/src/emit.cpp
    ${YAML_LIBRARY_DIR}/src/nodebuilder.cpp
    ${YAML_LIBRARY_DIR}/src/regex_yaml.cpp
    ${YAML_LIBRARY_DIR}/src/tag.cpp
    ${YAML_LIBRARY_DIR}/src/emitfromevents.cpp
    ${YAML_LIBRARY_DIR}/src/node.cpp
    ${YAML_LIBRARY_DIR}/src/scanner.cpp
    ${YAML_LIBRARY_DIR}/src/emitter.cpp
    ${YAML_LIBRARY_DIR}/src/node_data.cpp
    ${YAML_LIBRARY_DIR}/src/scanscalar.cpp
    ${YAML_LIBRARY_DIR}/src/emitterstate.cpp
    ${YAML_LIBRARY_DIR}/src/nodeevents.cpp
    ${YAML_LIBRARY_DIR}/src/scantag.cpp
)

add_library (yaml_cpp ${YAML_SRCS})
target_include_directories(yaml_cpp PRIVATE ${YAML_LIBRARY_DIR}/include/yaml-cpp)
target_include_directories(yaml_cpp SYSTEM BEFORE PUBLIC ${YAML_LIBRARY_DIR}/include)

set(SRC_DIR "${PROJECT_SOURCE_DIR}/third-party/re2")

set(RE2_SOURCES
    ${SRC_DIR}/re2/bitstate.cc
    ${SRC_DIR}/re2/compile.cc
    ${SRC_DIR}/re2/dfa.cc
    ${SRC_DIR}/re2/filtered_re2.cc
    ${SRC_DIR}/re2/mimics_pcre.cc
    ${SRC_DIR}/re2/nfa.cc
    ${SRC_DIR}/re2/onepass.cc
    ${SRC_DIR}/re2/parse.cc
    ${SRC_DIR}/re2/perl_groups.cc
    ${SRC_DIR}/re2/prefilter.cc
    ${SRC_DIR}/re2/prefilter_tree.cc
    ${SRC_DIR}/re2/prog.cc
    ${SRC_DIR}/re2/re2.cc
    ${SRC_DIR}/re2/regexp.cc
    ${SRC_DIR}/re2/set.cc
    ${SRC_DIR}/re2/simplify.cc
    ${SRC_DIR}/re2/stringpiece.cc
    ${SRC_DIR}/re2/tostring.cc
    ${SRC_DIR}/re2/unicode_casefold.cc
    ${SRC_DIR}/re2/unicode_groups.cc
    ${SRC_DIR}/util/rune.cc
    ${SRC_DIR}/util/strutil.cc
)

add_library(re2 STATIC ${RE2_SOURCES})
target_include_directories(re2 PUBLIC "${SRC_DIR}")
