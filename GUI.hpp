#ifndef GUI_HPP
#define GUI_HPP
#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include "avizier.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>

class GUI
{
private:
    static void glfw_error_callback(int error, const char *description)
    {
        // printf(stderr, "GLFW Error %d: %s\n", error, description);
        std::cout << "error";
    }
    const int width = 1920, height = 1080;
    const int L = 900;
    const char *glsl_version = "#version 130";
    GLFWwindow *window;
    ImVec4 clear_color;
    bool show_welcome = true;
    bool show_game = false;

    void
    Game()
    {
        static float f = 0.0f;
        static int counter = 0;
        ImGui::SetNextWindowSize(ImVec2(L, L), ImGuiCond_FirstUseEver);                                 // Custom size
        ImGui::SetNextWindowPos(ImVec2(width / 4 - L / 2, height / 2 - L / 2), ImGuiCond_FirstUseEver); // Custom position
                                                                                                        // Begin a new ImGui window
        ImGui::Begin(" ");

        // Variables to control the size of the buttons inside the clusters
        // float button_sz = (L - ImGui::GetStyle().WindowPadding.x * 2 - ImGui::GetStyle().CellPadding.x * 2 * 3) / 9;
        float button_sz = L / 9 - 10;
        float cell_sz = button_sz * 3 + ImGui::GetStyle().CellPadding.x * 2 * 2; // 3 buttons and 2*2 padding

        int highlightedCluster = -1;                                                                          // Variable to track the highlighted cluster
        if (ImGui::BeginTable("Clusters", 3, ImGuiTableFlags_BordersInner | ImGuiTableFlags_SizingFixedSame)) // 3x3 matrix with fixed sizing
        {
            // Set column width to evenly divide the table into three
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, cell_sz);
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, cell_sz);
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, cell_sz);

            for (int row = 0; row < 3; ++row)
            {
                ImGui::TableNextRow();

                for (int col = 0; col < 3; ++col)
                {
                    ImGui::TableSetColumnIndex(col);

                    int clusterIndex = row * 3 + col;
                    if (clusterIndex == highlightedCluster)
                    {
                        // Highlight this cluster
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.5f, 0.0f, 1.0f)); // Orange for highlight
                        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.6f, 0.0f, 1.0f));
                        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.8f, 0.0f, 1.0f));
                    }

                    // Create a sub-table for each cluster to control inner spacing
                    if (ImGui::BeginTable("ClusterSubTable", 3, ImGuiTableFlags_SizingFixedSame))
                    {
                        for (int i = 0; i < 3; ++i)
                        {
                            ImGui::TableNextRow();
                            for (int j = 0; j < 3; ++j)
                            {
                                ImGui::TableSetColumnIndex(j);
                                ImGui::Button(("A" + std::to_string(i * 3 + j)).c_str(), ImVec2(button_sz, button_sz)); // Button size scaled according to 'L'
                            }
                        }
                        ImGui::EndTable();
                    }

                    if (clusterIndex == highlightedCluster)
                    {
                        ImGui::PopStyleColor(3); // Reset to previous style
                    }
                }
            }

            ImGui::EndTable();
        }

        // End the ImGui window
        ImGui::End();
    }

    void Welcome_screen()
    {
        static float f = 0.0f;
        static int counter = 0;
        ImGui::SetNextWindowSize(ImVec2(L, L), ImGuiCond_FirstUseEver);                                 // Custom size
        ImGui::SetNextWindowPos(ImVec2(width / 2 + width / 4 - L / 2, height / 2 - L / 2), ImGuiCond_FirstUseEver); // Custom position
        ImGui::Begin("Hello, world!");                                                                  // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text."); // Display some text (you can use a format strings too)
        if(ImGui::Button("Start Game"))
        {
            show_game = true;
            show_welcome = false;
        }

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);             // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float *)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Buton")) // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);
        ImGui::End();
    }


    void loop()
    {
        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();

            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            if(show_welcome)
                Welcome_screen();

            if (show_game)
                Game();


            // Rendering
            ImGui::Render();
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
        }
    }

public:
    int Run()
    {
        glfwSetErrorCallback(glfw_error_callback);
        if (!glfwInit())
            return 1;
        // GL 3.0 + GLSL 130
        // const char *glsl_version = "#version 130";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

        // Create window with graphics context
        window = glfwCreateWindow(width, height, "Ultimate Tic Tac Toe", nullptr, nullptr);
        if (window == nullptr)
            return 1;
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1); // Enable vsync

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        // ImGui::StyleColorsLight();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);

        ImGui_ImplOpenGL3_Init(glsl_version);

        bool show_another_window = false;
        clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        ImGui::GetIO().IniFilename = NULL;

        // main loop
        loop();

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(window);
        glfwTerminate();
        return 0;
    }
};
#endif
