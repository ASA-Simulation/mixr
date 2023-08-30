from conan import ConanFile
from conan.tools.scm import Git
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout

class Recipe(ConanFile):
    # Mandatory metadata
    name = "jsbsim"
    version = "1.1.11"

    # Optional metadata
    license = "LGPL-2.1"
    url = "https://github.com/JSBSim-Team/jsbsim"
    description = "JSBSim is a multi-platform, general purpose object-oriented Flight Dynamics Model (FDM) written in C++."

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    generators = "CMakeDeps"

    def source(self):
        git = Git(self)
        git.clone(url="https://github.com/JSBSim-Team/jsbsim", target=".")
        git.checkout("v1.1.11")

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
        self.cpp_info.libs = ["JSBSim", "Aeromatic++"]
        self.cpp_info.includedirs = ["include", "include/JSBSim"]
