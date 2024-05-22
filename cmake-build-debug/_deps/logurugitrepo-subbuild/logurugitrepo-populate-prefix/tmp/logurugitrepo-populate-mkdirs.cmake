# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/ye/CLionProjects/EXTRAME-PRACTICE/cmake-build-debug/_deps/logurugitrepo-src"
  "/home/ye/CLionProjects/EXTRAME-PRACTICE/cmake-build-debug/_deps/logurugitrepo-build"
  "/home/ye/CLionProjects/EXTRAME-PRACTICE/cmake-build-debug/_deps/logurugitrepo-subbuild/logurugitrepo-populate-prefix"
  "/home/ye/CLionProjects/EXTRAME-PRACTICE/cmake-build-debug/_deps/logurugitrepo-subbuild/logurugitrepo-populate-prefix/tmp"
  "/home/ye/CLionProjects/EXTRAME-PRACTICE/cmake-build-debug/_deps/logurugitrepo-subbuild/logurugitrepo-populate-prefix/src/logurugitrepo-populate-stamp"
  "/home/ye/CLionProjects/EXTRAME-PRACTICE/cmake-build-debug/_deps/logurugitrepo-subbuild/logurugitrepo-populate-prefix/src"
  "/home/ye/CLionProjects/EXTRAME-PRACTICE/cmake-build-debug/_deps/logurugitrepo-subbuild/logurugitrepo-populate-prefix/src/logurugitrepo-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/ye/CLionProjects/EXTRAME-PRACTICE/cmake-build-debug/_deps/logurugitrepo-subbuild/logurugitrepo-populate-prefix/src/logurugitrepo-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/ye/CLionProjects/EXTRAME-PRACTICE/cmake-build-debug/_deps/logurugitrepo-subbuild/logurugitrepo-populate-prefix/src/logurugitrepo-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
