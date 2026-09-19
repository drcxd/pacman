add_rules("mode.debug", "mode.release")

package("sdl3-local")
    add_deps("cmake")
    set_sourcedir(path.join(os.scriptdir(), "lib", "SDL"))
    on_install(function (package)
        local configs = {}
        table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:debug() and "Debug" or "Release"))
        table.insert(configs, "-DBUILD_SHARED_LIBS=" .. (package:config("shared") and "ON" or "OFF"))
        import("package.tools.cmake").install(package, configs) -- Build and Install with CMake
    end)
package_end()

package("sdl3_image-local")
    add_deps("cmake")
    add_deps("sdl3-local", {configs = {shared = true}})
    set_sourcedir(path.join(os.scriptdir(), "lib", "SDL_image"))
    on_install(function (package)
        local configs = {}
        local sdl3 = package:dep("sdl3-local")
        table.insert(configs, "-DSDL3_DIR=" .. path.join(sdl3:installdir(), "lib", "cmake", "SDL3"))
        table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:debug() and "Debug" or "Release"))
        table.insert(configs, "-DBUILD_SHARED_LIBS=" .. (package:config("shared") and "ON" or "OFF"))
        import("package.tools.cmake").install(package, configs) -- Build and Install with CMake
    end)
package_end()

package("sdl3_mixer-local")
    add_deps("cmake")
    add_deps("sdl3-local", {configs = {shared = true}})
    set_sourcedir(path.join(os.scriptdir(), "lib", "SDL_mixer"))
    on_install(function (package)
        local configs = {}
        local sdl3 = package:dep("sdl3-local")
        table.insert(configs, "-DSDL3_DIR=" .. path.join(sdl3:installdir(), "lib", "cmake", "SDL3"))
        table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:debug() and "Debug" or "Release"))
        table.insert(configs, "-DBUILD_SHARED_LIBS=" .. (package:config("shared") and "ON" or "OFF"))
        import("package.tools.cmake").install(package, configs) -- Build and Install with CMake
    end)
package_end()

package("sdl3_ttf-local")
    add_deps("cmake")
    add_deps("sdl3-local", {configs = {shared = true}})
    set_sourcedir(path.join(os.scriptdir(), "lib", "SDL_ttf"))
    on_install(function (package)
        local configs = {}
        local sdl3 = package:dep("sdl3-local")
        table.insert(configs, "-DSDL3_DIR=" .. path.join(sdl3:installdir(), "lib", "cmake", "SDL3"))
        table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:debug() and "Debug" or "Release"))
        table.insert(configs, "-DBUILD_SHARED_LIBS=" .. (package:config("shared") and "ON" or "OFF"))
        table.insert(configs, "-DSDLTTF_VENDORED=ON")
        import("package.tools.cmake").install(package, configs) -- Build and Install with CMake
    end)
package_end()

local packages = {"sdl3-local", "sdl3_image-local", "sdl3_mixer-local", "sdl3_ttf-local"}

for _, pkg in ipairs(packages) do
   add_requires(pkg, {configs = {shared = true}})
end

target("pacman")
    set_kind("binary")
    add_files("src/*.cpp")
    add_packages(table.unpack(packages))

    -- NOTE: On Linux, xmake prefers .a libraries. Our current build
    -- configuration produces SDL3.so, SDL3_test.so and
    -- SDL3_test.a. When xmake sees SDL3_test.a, it only links to this
    -- library and ignore the SDL3.so, so some symbols becomes
    -- undefined at link time.
    add_links("SDL3")

    set_rundir("$(projectdir)")

    -- Copy all libraries to the directory of the executable
    after_build(function (target)
          for _, name in ipairs(packages) do
             local pkg = target:pkg(name)
             os.cp(path.join(pkg:installdir(), "bin", "*"), target:targetdir())
          end
    end)
--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro definition
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

