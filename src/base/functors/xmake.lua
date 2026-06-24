target("mixr_base_functors")
    set_kind("shared")
    add_files("./**.cpp")
    
    add_includedirs(
        path.join(os.projectdir(), "include"), 
        {public = true}
    )

    add_packages("json", "eigen")
