from conan import ConanFile
from conan.tools.meson import Meson, MesonToolchain
from conan.tools.gnu import PkgConfigDeps


class Recipe(ConanFile):
    name = "mixr"
    version = "1.0.5"

    license = "LGPL-3.0"
    url = "https://github.com/ASA-Simulation/mixr"
    description = "A fork of MIXR focused on meson/conan integration."

    settings = "arch", "build_type", "compiler", "os"
    options = {"fPIC": [True, False]}
    default_options = {"fPIC": True}

    exports_sources = "meson.build*", "include/*", "scripts/*", "src/*", "subprojects/*"

    def requirements(self):
        self.requires("protobuf/3.21.12")
        self.requires("openrti/814a210978b7faafd65affbe70a2e25679921b23")
        self.requires("jsbsim/1.1.11", transitive_headers=True)

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def layout(self):
        self.folders.build = "build"
        self.folders.generators = "build"

    def generate(self):
        tc = PkgConfigDeps(self)
        tc.generate()

        tc = MesonToolchain(self)
        tc.generate()

    def build(self):
        meson = Meson(self)
        meson.configure()
        meson.build()

    def package(self):
        meson = Meson(self)
        meson.install()

    def package_info(self):
        self.cpp_info.components["base"].libs = ["mixr_base"]
        self.cpp_info.components["interop_common"].libs = ["mixr_interop_common"]
        self.cpp_info.components["interop_dis"].libs = ["mixr_interop_dis"]
        self.cpp_info.components["linearsystem"].libs = ["mixr_linearsystem"]
        self.cpp_info.components["linkage"].libs = ["mixr_linkage"]
        self.cpp_info.components["models"].libs = ["mixr_models"]
        self.cpp_info.components["recorder"].libs = ["mixr_recorder"]
        self.cpp_info.components["simulation"].libs = ["mixr_simulation"]
        self.cpp_info.components["terrain"].libs = ["mixr_terrain"]
