includes("./colors")
includes("./functors")

target("test_base_object")
    set_kind("binary")

    add_files("./test_object.cpp")

    add_packages("catch2")
    add_packages("json")

    add_deps("mixr_base")

target("test_base_parser")
    set_kind("binary")

    add_files("./test_parser.cpp")

    add_packages("catch2")
    add_packages("json")

    add_deps("mixr_base")

target("tests_base")
    set_kind("binary")

    add_files("./*.cpp")

    add_packages("catch2")
    add_packages("json")

    add_deps("mixr_base")
