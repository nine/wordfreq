set(wordfreq_SOURCES
    wordfreq.cpp
    file_reader.cpp
)

add_executable(wordfreq)
target_sources(wordfreq PRIVATE
    ${wordfreq_SOURCES}
)
target_link_libraries(wordfreq PRIVATE
    bfg::lyra
    Threads::Threads)
if(TARGET lyra::lyra)
endif()
