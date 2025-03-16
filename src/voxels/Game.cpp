

#include "Game.h"
#include <iostream>

#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Shader.h"
#include "Definitions.h"
#include "Callbacks.h"
#include "World.h"
#include "Crosshair.h"

namespace Voxels
{
    
    Game::Game()
    {
        deltaTime = 0.0f;
        lastX = Definitions::SCREEN_HEIGHT / 2.0f;
        lastY = Definitions::SCREEN_HEIGHT / 2.0f;
        firstMouse = true;
        mFailure = false;
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		window = glfwCreateWindow(Voxels::Definitions::SCREEN_WIDTH, Voxels::Definitions::SCREEN_HEIGHT, "Hello!", nullptr, nullptr);
		if (window == nullptr)
		{
			std::cout << "Failed to create GLFW window\n";
			glfwTerminate();
			mFailure = true;
		}
    }

    bool Game::init()
    {
        if (mFailure)
            return false;

        glfwMakeContextCurrent(window);
        glfwSetKeyCallback(window, windowKeyCallback);
        glfwSetFramebufferSizeCallback(window, windowFramebufferSizeCallback);
        glfwSwapInterval(1);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD\n";
            return false;
        }
        if (const GLubyte* renderer = glGetString(GL_RENDERER))
        {
            mRenderer = reinterpret_cast<const char*>(renderer);
        }

        if (mRenderer.empty())
            mFailure = true;

        std::cout << mRenderer << '\n';
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
        ImGui_ImplOpenGL3_Init();
        if (mFailure)
            return false;

        _createShaders();

        return true;
    }

    void Game::run()
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CW);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        float lastFrame = 0.0f;
        World world(shaders);
        Crosshair crosshair;

        constexpr float red = 125.f / 255.f;
        constexpr float green = 206.f / 255.f;
        constexpr float blue = 235.f / 255.f;
        while (!glfwWindowShouldClose(window))
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            ImGui::Text("FPS: %.2f", ImGui::GetIO().Framerate);
            ImGui::SetWindowSize(ImVec2(120.f, 40.f));
            
            float currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            _processInput();
            _processMouse();
            glClearColor(red, green, blue, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            world.update(camera);
            world.render(camera);
            crosshair.draw(shaders);
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        for (auto& s : shaders)
        {
            s.second.destroy();
        }

        glfwTerminate();
    }

    void Game::_processInput()
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.move(1, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.move(3, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.move(2, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.move(4, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            camera.move(5, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            camera.move(6, deltaTime);


        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        {
            camera.toggleZoom(true, 180.f, deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE)
        {
            camera.toggleZoom(false, 180.f, deltaTime);
        }

        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        {
            camera.toggleBoost(true);
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
        {
            camera.toggleBoost(false);
        }

        


    }

    void Game::_processMouse()
    {
        if (const int inputMode = glfwGetInputMode(window, GLFW_CURSOR); inputMode == GLFW_CURSOR_NORMAL)
            return;
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        float xpos = static_cast<float>(mouseX);
        float ypos = static_cast<float>(mouseY);

        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }
        float xoffset = xpos - lastX;
        float yoffset = ypos - lastY;

        lastX = xpos;
        lastY = ypos;

        camera.processMouse(xoffset, yoffset);
    }

    void Game::_createShaders()
    {
        shaders.try_emplace(ChunkProgram, RESOURCE_PATH "shaders/main.vert", RESOURCE_PATH "shaders/main.frag");
        /*
         * 0.0625 is based on a 16x16 texture on a 256x256 atlas
         *
         * Since the atlas is always to be square, you can just divide the TextureX by the atlas' ResolutionX (16.f/256.f in this example)
         */

        shaders[ChunkProgram].use();
        shaders[ChunkProgram].setFloat("textureSingleColumn", 0.0625);
        shaders.try_emplace(CrosshairProgram, RESOURCE_PATH "shaders/crosshair.vert", RESOURCE_PATH "shaders/crosshair.frag");
    }
}
