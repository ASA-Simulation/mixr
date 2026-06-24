target("mixr_terrain")
    set_kind("shared")

    add_files(
        "./srtm/SrtmHgtFile.cpp",
        "./DataFile.cpp",
        "./factory.cpp",
        "./QuadMap.cpp",
        "./Terrain.cpp"
    )

    add_includedirs(
        path.join(os.projectdir(), "include"),
        {public = true}
    )
