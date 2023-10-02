from conan import ConanFile
from conan.tools.scm import Git
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout

class Recipe(ConanFile):
    # Mandatory metadata
    name = "openrti"
    version = "814a210978b7faafd65affbe70a2e25679921b23"

    # Optional metadata
    license = "LGPL-3"
    url = "https://sourceforge.net/projects/openrti/"
    description = "An rti library with an rti1516, rti1516e as well as a RTI13 interface."

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    generators = "CMakeDeps"

    def requirements(self):
        self.requires("expat/2.5.0")

    def source(self):
        git = Git(self)
        git.clone(url="https://github.com/onox/OpenRTI", target=".")
        git.checkout("814a210978b7faafd65affbe70a2e25679921b23")

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["OPENRTI_ENABLE_PYTHON_BINDINGS"] = False
        tc.variables["OPENRTI_ENABLE_RTI13"] = True
        tc.variables["OPENRTI_ENABLE_RTI1516"] = False
        tc.variables["OPENRTI_ENABLE_RTI1516E"] = False
        tc.variables["OPENRTI_BUILD_SHARED"] = self.options.shared
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = [
            "FedTime", "OpenRTI", "RTI-NG"
        ]
