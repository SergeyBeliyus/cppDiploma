cmake_minimum_required(VERSION 3.20)
	
add_executable(client
	main.cpp
)
add_library(indexer 
	indexer/indexer.cpp
)

add_library(parser 
	indexer/parser/parser.cpp
)

add_library(utils
	utils/utils.cpp
)

add_library(link_get 
	indexer/link_get/link_get.cpp
)

add_library(sql_database 
	indexer/sql_database/sql_database.cpp
)

target_include_directories(client PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

find_package(OpenSSL REQUIRED)
target_compile_features(client PRIVATE cxx_std_17) 
target_include_directories(client PRIVATE 
	${Boost_INCLUDE_DIRS}
)

target_link_libraries(client PUBLIC 
	indexer
	utils
	parser
	link_get
	sql_database
	pqxx
	OpenSSL::SSL
	${Boost_LIBRARIES}
)
