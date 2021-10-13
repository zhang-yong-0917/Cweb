cmake_minimum_required(VERSION 3.19)
project(jiexi)

set(CMAKE_CXX_STANDARD 14)

add_executable(jiexi cpp/main.cpp  cpp/MyAnalysisNew.cpp  head_h/MyAnalysisNew.h  cpp/threadpool.cpp head_h/threadpool.h   cpp/Analyse.cpp head_h/Analyse.h cpp/ServerSocket.cpp head_h/Socket.h cpp/File.cpp head_h/File.h head_h/epoll.h cpp/epoll.cpp cpp/ReadHtml.cpp head_h/ReadHtml.h cpp/spellresponse.cpp cpp/Analyse_two.cpp cpp/Time.cpp head_h/Time.h cpp/Config.cpp head_h/Config.h head_h/servlet.h head_h/do_servlet.h test/test.cpp  cpp/servlet/servlet.cpp head_h/spellresponse.h)


TARGET_LINK_LIBRARIES(jiexi pthread)