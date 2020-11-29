#include <stdafx.hpp>
#include <LTurtle.hpp>
#include <math.h>
#include "imgui_helper.hpp"

LTurtle::LTurtle(int win_w, int win_h, std::string win_title)
: step(0)
, angle(0)
{
  pos.pos.x = pos.pos.y = pos.dir = 0.0;
  initImgui(win_w, win_h, win_title);
  win_size.x = (float)win_w;
  win_size.y = (float)win_h;
}

LTurtle::~LTurtle() {
  termImgui();
}

void LTurtle::init(float _step, float _angle) {
  step = _step;
  angle = _angle;
}

void LTurtle::interpret(std::string condition, std::vector<char> constants) {

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
      if (std::find(constants.begin(), constants.end(), condition[i]) == constants.end())
        moveForward(step);
      break;
    }
  }
  
}

void LTurtle::draw(bool adjust) {

  if (adjust)
    this->adjust();

  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  int cnt = 0;
  while (!glfwWindowShouldClose(window)) {
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

    {
      ImDrawList* draw_list = ImGui::GetOverlayDrawList();
      int dc = 0;
      for (auto line : lines) {
        if (dc > cnt)
          break;
        draw_list->AddLine(
          ImVec2(line.start.x, line.start.y), 
          ImVec2(line.end.x, line.end.y), 
          ImGui::GetColorU32(ImVec4(1.0, 1.0, 1.0, 1.0)),
          3.0
          );
          dc++;
      }
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
    cnt++;
    cnt %= (lines.size() + 10);
  }
}

void LTurtle::adjust() {
  float max_x = lines.front().start.x;
  float max_y = lines.front().start.y;
  float min_x = lines.front().start.x;
  float min_y = lines.front().start.y;

  Vector2D s = lines.front().start;

  for (auto line : lines) {
    max_x = std::max(max_x, line.end.x);
    max_y = std::max(max_y, line.end.y);
    min_x = std::min(min_x, line.end.x);
    min_y = std::min(min_y, line.end.y);
  }

  float cur_w = max_x - min_x;
  float cur_h = max_y - min_y;
  float w_margin = 20.0;
  float h_margin = 20.0;

  float xscale = ((float)win_size.x - 2*w_margin ) / cur_w;
  float yscale = ((float)win_size.y - 2*h_margin ) / cur_h;

  float scale = std::min(xscale, yscale);
  
  float ofsx = (float)win_size.x / 2.0 - (max_x + min_x)*scale / 2.0;
  float ofsy = (float)win_size.y / 2.0 - (max_y + min_y)*scale / 2.0;

  std::list<Line> tmp_lines;
  for (auto line : lines)
  {
    Line l;
    l.start = {(line.start.x - s.x) * scale + ofsx, (line.start.y - s.y) * scale + ofsy};
    l.end   = {(line.end.x - s.x) * scale + ofsx, (line.end.y - s.y) * scale + ofsy};
    tmp_lines.push_back(l);
  }

  lines.assign(tmp_lines.begin(), tmp_lines.end());
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

