#include <stdafx.hpp>
#include <LTurtle.hpp>
#include <math.h>
#include "imgui_helper.hpp"

LTurtle::LTurtle()
: step(0)
, angle(0)
{
  pos.pos.x = pos.pos.y = pos.dir = 0.0;
  initImgui();
}

LTurtle::~LTurtle() {
  termImgui();
}

void LTurtle::init(float _step, float _angle) {
  step = _step;
  angle = _angle;
}

void LTurtle::interpret(std::string condition) {

  lines.clear();
  for (size_t i = 0; i < condition.size(); i++) {
    switch (condition[i])
    {
    case '+':
      turnRight(angle);
      break;
    case '-':
      turnLeft(angle);
      break;
    case '[':
      save();
      break;
    case ']':
      restore();
      break;
    default:
      moveForward(step);
      break;
    }
  }
  
}

void LTurtle::draw() {
    // Our state
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

}

void LTurtle::moveto(Vector2D to) {
  pos.pos = to;
}

void LTurtle::moveForward(float step) {

  Vector2D prev = pos.pos;
  pos.pos.x += step * cos(pos.dir);
  pos.pos.y += step * sin(pos.dir);

  lines.push_back({prev, pos.pos});
}

void LTurtle::turnRight(float angle) {
  pos.dir -= angle;
}

void LTurtle::turnLeft(float angle) {
  pos.dir += angle;
}

void LTurtle::save() {
  stack.push(pos);
}

void LTurtle::restore() {
  pos = stack.top();
  stack.pop();
}

