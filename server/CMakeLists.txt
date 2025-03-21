cmake_minimum_required(VERSION 3.20)

add_executable(server 
	main.cpp
	connection.cpp
)
add_library(engine
	engine/engine.cpp
)

find_package(OpenSSL REQUIRED)
target_compile_features(server PRIVATE cxx_std_17) 
target_include_directories(server PRIVATE 
	${Boost_INCLUDE_DIRS}
)

target_link_libraries(server PUBLIC 
	engine
	pqxx
	OpenSSL::SSL
	${Boost_LIBRARIES}
)
