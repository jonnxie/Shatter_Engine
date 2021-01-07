cmake_minimum_required(VERSION 3.17)
project(Shatter_engine)

set(CMAKE_CXX_STANDARD 20)

aux_source_directory(Shatter_Action/ DIR_ACTION_SRC)
aux_source_directory(Shatter_Action/*.cpp DIR_ACTION_INCLUDE)

aux_source_directory(Shatter_App/ DIR_APP_SRC)
aux_source_directory(Shatter_App/*.cpp DIR_APP_INCLUDE)

aux_source_directory(Shatter_Asset/ DIR_ASSET_SRC)
aux_source_directory(Shatter_Asset/*.cpp DIR_ASSET_INCLUDE)

aux_source_directory(Shatter_Buffer/ DIR_BUFFER_SRC)
aux_source_directory(Shatter_Buffer/*.cpp DIR_BUFFER_INCLUDE)

aux_source_directory(Shatter_Camera/ DIR_CAMERA_SRC)
aux_source_directory(Shatter_Camera/*.cpp DIR_CAMERA_INCLUDE)

aux_source_directory(Shatter_Drawable/ DIR_DRAWABLE_SRC)
aux_source_directory(Shatter_Drawable/*.cpp DIR_DRAWABLE_INCLUDE)

aux_source_directory(Shatter_Input/ DIR_INPUT_SRC)
aux_source_directory(Shatter_Input/*.cpp DIR_INPUT_INCLUDE)

aux_source_directory(Shatter_Item/ DIR_ITEM_SRC)
aux_source_directory(Shatter_Item/*.cpp DIR_ITEM_INCLUDE)

aux_source_directory(Shatter_Model/ DIR_MODEL_SRC)
aux_source_directory(Shatter_Model/*.cpp DIR_MODEL_INCLUDE)

aux_source_directory(Shatter_Pipeline/ DIR_PIPELINE_SRC)
aux_source_directory(Shatter_Pipeline/*.cpp DIR_PIPELINE_INCLUDE)

aux_source_directory(Shatter_Render/ DIR_RENDER_SRC)
aux_source_directory(Shatter_Render/*.cpp DIR_RENDER_INCLUDE)

aux_source_directory(Shatter_Scene/ DIR_SCENE_SRC)
aux_source_directory(Shatter_Scene/*.cpp DIR_SCENE_INCLUDE)

aux_source_directory(Shatter_Shader/ DIR_SHADER_SRC)
aux_source_directory(Shatter_Shader/*.cpp DIR_SHADER_INCLUDE)

aux_source_directory(Shatter_UI/ DIR_UI_SRC)
aux_source_directory(Shatter_UI/*.cpp DIR_UI_INCLUDE)


set(DIR_SRC
        ${DIR_ACTION_SRC}
        ${DIR_APP_SRC}
        ${DIR_ASSET_SRC}
        ${DIR_BUFFER_SRC}
        ${DIR_CAMERA_SRC}
        ${DIR_DRAWABLE_SRC}
        ${DIR_INPUT_SRC}
        ${DIR_ITEM_SRC}
        ${DIR_MODEL_SRC}
        ${DIR_PIPELINE_SRC}
        ${DIR_RENDER_SRC}
        ${DIR_SCENE_SRC}
        ${DIR_SHADER_SRC}
        ${DIR_UI_SRC}
        )
set(DIR_INCLUDE
        ${DIR_ACTION_INCLUDE}
        ${DIR_APP_INCLUDE}
        ${DIR_ASSET_INCLUDE}
        ${DIR_BUFFER_INCLUDE}
        ${DIR_CAMERA_INCLUDE}
        ${DIR_DRAWABLE_INCLUDE}
        ${DIR_INPUT_INCLUDE}
        ${DIR_ITEM_INCLUDE}
        ${DIR_MODEL_INCLUDE}
        ${DIR_PIPELINE_INCLUDE}
        ${DIR_RENDER_INCLUDE}
        ${DIR_SCENE_INCLUDE}
        ${DIR_SHADER_INCLUDE}
        ${DIR_UI_INCLUDE}
        )


add_executable(Shatter_engine ${DIR_INCLUDE} ${DIR_SRC} main.cpp)

## SDL
set(SDL2_PATH C:/Users/maybe/Desktop/third-part-library/SDL2-2.0.12/x86_64-w64-mingw32)
set(SDL2_LIBS_DIR ${SDL2_PATH}/lib)
set(SDL2_INCLUDE_DIR ${SDL2_PATH}/include)
set(SDL2_LIBRARIES -L${SDL2_LIBS_DIR} -lmingw32 -lSDL2main -lSDL2 -mwindows)

include_directories(${SDL2_INCLUDE_DIR})

target_link_libraries(Shatter_engine ${SDL2_LIBRARIES})

## STB
set(STB_INCLUDE_DIR C:/VulkanSDK/1.2.154.1/Third-Party/Include/stb/)

include_directories(${STB_INCLUDE_DIR})

## TINY_OBJ
set(TINY_OBJ_DIR C:/VulkanSDK/1.2.154.1/Third-Party/Include/tinyobjloader/)

include_directories(${TINY_OBJ_DIR})

## GLFW
set(GLFW_INCLUDE_DIRS C:/Users/maybe/Desktop/third-part-library/glfw-3.3.2.bin.WIN64/include/GLFW/)
set(GLFW_LIBRARIES C:/Users/maybe/Desktop/third-part-library/glfw-3.3.2.bin.WIN64/lib-mingw-w64/)
include_directories(${GLFW_INCLUDE_DIRS})
target_link_libraries(Shatter_engine ${GLFW_LIBRARIES})

target_link_libraries(Shatter_engine glfw3)

## GLM
set(GLM_INCLUDE_DIRS C:/VulkanSDK/1.2.154.1/Third-Party/Include/glm/)
include_directories(${GLM_INCLUDE_DIRS})

## VulKan
find_package(Vulkan REQUIRED)
target_include_directories(Shatter_engine PUBLIC ${Vulkan_INCLUDE_DIRS})
target_link_libraries(Shatter_engine ${Vulkan_LIBRARIES})





