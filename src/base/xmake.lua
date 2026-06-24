includes("functors")

includes("colors")

target("mixr_base")
    set_kind("shared")
    add_files({
        "factory.cpp",
        "MetaObject.cpp",
        "Object.cpp",
        "SlotTable.cpp",
    })

    add_includedirs(
        path.join(os.projectdir(), "include"),
        {public = true}
    )

    add_packages("json")
