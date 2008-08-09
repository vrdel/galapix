/*  $Id$
**   __      __ __             ___        __   __ __   __
**  /  \    /  \__| ____    __| _/_______/  |_|__|  | |  |   ____
**  \   \/\/   /  |/    \  / __ |/  ___/\   __\  |  | |  | _/ __ \
**   \        /|  |   |  \/ /_/ |\___ \  |  | |  |  |_|  |_\  ___/
**    \__/\  / |__|___|  /\____ /____  > |__| |__|____/____/\___  >
**         \/          \/      \/    \/                         \/
**  Copyright (C) 2007 Ingo Ruhnke <grumbel@gmx.de>
**
**  This program is free software; you can redistribute it and/or
**  modify it under the terms of the GNU General Public License
**  as published by the Free Software Foundation; either version 2
**  of the License, or (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
** 
**  You should have received a copy of the GNU General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
**  02111-1307, USA.
*/

#include <iostream>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include "SDL_syswm.h"
#include "math/rect.hpp"
#include "framebuffer.hpp"

SDL_SysWMinfo syswm;
SDL_Surface* Framebuffer::screen = 0;
Uint32 Framebuffer::flags = 0;

void
Framebuffer::init()
{
  //XInitThreads();
 
  std::cout << "Framebuffer::init()" << std::endl;
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
      std::cout << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
      exit(1);
    }
  atexit(SDL_Quit); 
  
  flags = SDL_RESIZABLE | SDL_OPENGL;
  screen = SDL_SetVideoMode(800, 600, 0, flags);

  if (screen == NULL) 
    {
      std::cout << "Unable to set video mode: " << SDL_GetError() << std::endl;
      exit(1);
    }

  SDL_WM_SetCaption("Griv 0.0.2", 0 /* icon */);
  SDL_EnableUNICODE(1);

  glViewport(0, 0, screen->w, screen->h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, screen->w, screen->h, 0.0, 1000.0, -1000.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  //static const float cl_pixelcenter_constant = 0.375;
  //glTranslated(cl_pixelcenter_constant, cl_pixelcenter_constant, 0.0);
  
  SDL_VERSION(&syswm.version); // this is important!
  if (SDL_GetWMInfo(&syswm) == -1)
    {
      std::cout << "Couldn't get WM info " << std::endl;
    }
}

void
Framebuffer::deinit()
{
  
}

void
Framebuffer::toggle_fullscreen()
{
  flags |= SDL_OPENGL;
  if (flags & SDL_FULLSCREEN)
    flags &= ~SDL_FULLSCREEN;
  else
    flags |= SDL_FULLSCREEN;
 
  // Should use desktop resolution for this instead, but how?
  screen = SDL_SetVideoMode(1152, 864, 0, flags); 
  glViewport(0, 0, screen->w, screen->h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, screen->w, screen->h, 0.0, 1000.0, -1000.0);
}

void
Framebuffer::resize(int w, int h)
{
  screen = SDL_SetVideoMode(w, h, 0, SDL_OPENGL | SDL_RESIZABLE);
  glViewport(0, 0, screen->w, screen->h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, screen->w, screen->h, 0.0, 1000.0, -1000.0);
}

void
Framebuffer::flip()
{
  //SDL_Flip(screen);
  SDL_GL_SwapBuffers();
}

void
Framebuffer::clear()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //SDL_FillRect(Framebuffer::get_screen(), NULL, SDL_MapRGB(Framebuffer::get_screen()->format, 0, 0, 0));
}

void
Framebuffer::draw_rect(const Rectf& rect)
{
  glEnable(GL_BLEND);
  glDisable(GL_TEXTURE_2D);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        

  if (0)
    {
      glColor4f(1.0f, 0.0f, 1.0f, 0.25f);
      glBegin(GL_QUADS);
      glVertex2f(rect.left,  rect.top);
      glVertex2f(rect.right, rect.top);
      glVertex2f(rect.right, rect.bottom);
      glVertex2f(rect.left,  rect.bottom);
      glEnd();
    }

  glColor4f(1.0f, 1.0f, 1.0f, 0.5f);

  glBegin(GL_LINE_LOOP);
  glVertex2f(rect.left,  rect.top);
  glVertex2f(rect.right, rect.top);
  glVertex2f(rect.right, rect.bottom);
  glVertex2f(rect.left,  rect.bottom);
  glEnd();

  glDisable(GL_BLEND);
}

/* EOF */