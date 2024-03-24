该仓库的源代码使用vcpkg进行包管理。

依赖的库有glfw3、glad、glm、imgui、assimp、freetype。

其中freetype在目前为止还没有使用，之后会加入字体绘制时会用到。

第一次使用CMake+Ninja这种方式管理项目生成，在一些操作上还不是很熟悉，如果直接克隆可能需要进行一定程度的修改才能构建。（主要是编译器吧，因为我使用的是Clang。）

如果在之后加入了PBR还有空闲时间的话，会考虑将绘制API更改为Vulkan以提高性能。