target("mixr_base_colors")
    set_kind("shared")
    add_files("./Color.cpp")

    add_includedirs(
        path.join(os.projectdir(), "include"),
        {public = true}
    )

    add_deps("mixr_base")
