target("mixr_models")
    set_kind("shared")
    add_files("./*.cpp")
    
    add_includedirs(
        path.join(os.projectdir(), "include"), 
        {public = true}
    )
