set_project("mixr")
set_version("0.1.0")

set_languages("cxx26")

add_rules("plugin.compile_commands.autoupdate")

add_rules("mode.debug", "mode.release")

add_requires("conan::nlohmann_json/3.12.0", {alias = "json"})
add_requires("eigen", {alias = "eigen"})

includes("src")
includes("tests")
