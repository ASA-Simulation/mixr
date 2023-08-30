from conan import ConanFile
from conan.tools.scm import Git
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout


class Recipe(ConanFile):
    name = "mixr"
    version = "1.0.0"

    # Optional metadata
    license = "LGPL-3.0"
    url = "https://github.com/ASA-Simulation/mixr"
    description = "A fork of MIXR focused on CMAKE integration."

    # Binary configuration
    settings = "arch", "build_type", "compiler", "os"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    generators = "CMakeDeps"

    exports_sources = "cmake/*", "include/*", "src/*", "CMakeLists.txt", "Config.cmake.in"

    def requirements(self):
        # Conancenter
        self.requires("protobuf/3.21.12")
        # Gitlab
        self.requires("jsbsim/1.1.11")
        self.requires("openrti/814a210978b7faafd65affbe70a2e25679921b23")

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        lib_name_prefix = ""
        lib_name_suffix = "d" if self.settings.build_type == "Debug" else ""
        libs = [
            "mixr_base", "mixr_interop_dis", "mixr_interop_hla", "mixr_interop", "mixr_interop_rprfom", "mixr_linearsystem",
            "mixr_linkage", "mixr_models", "mixr_recorder", "mixr_recorder_proto", "mixr_simulation", "mixr_terrain"
        ]

        for name in libs:
            # changing component name: mixr_base => mixr::base
            self.cpp_info.components[name].set_property(
                "cmake_target_name", name.replace("mixr_", "mixr::")
            )

            # mounting the name of the binary on disk
            self.cpp_info.components[name].libs = [
                lib_name_prefix + name + lib_name_suffix
            ]

            # adding the requirement for mixr_base: all except itself
            if name != "mixr_base":
                self.cpp_info.components[name].requires = ["mixr_base"]

        self.cpp_info.components["mixr_interop_hla"].requires = [
            "openrti::openrti"
        ]
        self.cpp_info.components["mixr_interop_rprfom"].requires = [
            "openrti::openrti"
        ]
        self.cpp_info.components["mixr_models"].requires = [
            "jsbsim::jsbsim"
        ]
        self.cpp_info.components["mixr_recorder"].requires = [
            "protobuf::libprotobuf", "mixr_recorder_proto"
        ]
        self.cpp_info.components["mixr_recorder_proto"].requires = [
            "protobuf::libprotobuf"
        ]
