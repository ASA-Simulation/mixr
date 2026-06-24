target("tests_base_colors")
    set_kind("binary")

    add_files("./*.cpp")

    add_packages("catch2")
    add_packages("json")

    add_deps("mixr_base", "mixr_base_colors")
