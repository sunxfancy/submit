from conans import ConanFile, CMake, tools

class submitConan(ConanFile):
    name = "submit"
    version = "0.3.0"
    license = "MIT"
    url = "https://github.com/sunxfancy/submit"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = "shared=False", "gtest:shared=False"
    generators = "cmake"
    build_policy = "missing"
    requires = 'gtest/1.8.0@lasote/stable'
    exports = "*"
    
    def build(self):
        cmake = CMake(self)
        self.run('cmake ../.. %s' % cmake.command_line)
        self.run("cmake --build . %s" % cmake.build_config)

    def package(self):
        self.copy("*.h", dst="include", src="include")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)
        self.copy("LICENSE", dst=".", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = [self.name]
