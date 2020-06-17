#pragma once

#include "MainView.h"
#include "ViewManager.h"

using namespace ui;

u32* buffer = nullptr;
u64 offset = 0;

MainView::MainView(ViewManager* gvm) : gvm(gvm)
{
  mouse = { -1, -1 };
}

void MainView::render()
{
  auto r = gvm->renderer();

  SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
  SDL_RenderClear(r);

  const int32_t spacing = 20;
  int32_t x = 12, y = 12;
  const int32_t lines = (HEIGHT - y) / spacing;

  if (!buffer)
  {
    FILE* in = fopen("F:/Misc/Roms/Nintendo - NES/Adventure Island 2.nes", "rb");
    buffer = new u32[lines * 4];
    fread(buffer, sizeof(u32), lines * 4, in);
    fclose(in);
  }

  for (int32_t i = 0; i < lines; ++i)
  {
    static char sbuffer[256];
    snprintf(sbuffer, 256, "%04x %08x %08x %08x", i * 4, buffer[i * 4], buffer[i * 4 + 1], buffer[i * 4 + 2], buffer[i * 4 + 3]);
    gvm->text(sbuffer, x, y + i * spacing, { 255, 255, 255 }, ui::TextAlign::LEFT, 2.0f);
  }

  if (mouse.x >= 0 && mouse.x < WIDTH && mouse.y >= 0 && mouse.y < HEIGHT)
  {
    gvm->fillRect(mouse.x - 2, mouse.y - 2, 5, 5, { 255, 0, 0, 0 });
  }
}

void MainView::handleKeyboardEvent(const SDL_Event& event)
{
  if (event.type == SDL_KEYDOWN)
  {
    switch (event.key.keysym.sym)
    {
    case SDLK_ESCAPE: gvm->exit(); break;
    }
  }
}

void MainView::handleMouseEvent(const SDL_Event& event)
{
  if (event.type == SDL_MOUSEMOTION)
  {
    mouse.x = event.motion.x;
    mouse.y = event.motion.y;
  }
}