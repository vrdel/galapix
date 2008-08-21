/*
**  Griv - Grumbel's Image Viewer
**  Copyright (C) 2008 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_GRIV_HPP
#define HEADER_GRIV_HPP

class Griv
{
private:
public:
  Griv();
  ~Griv();

  void print_usage();
  int main(int argc, char** argv);

  void info(const std::vector<std::string>& filenames);
  void downscale(const std::vector<std::string>& filenames);
  void cleanup(const std::string& database);
  void check(const std::string& database);
  void list(const std::string& database);
  void thumbgen(const std::string& database, 
                const std::vector<std::string>& filenames);
  void filegen(const std::string& database, 
                const std::vector<std::string>& filenames);
  void generate_tiles(const std::string& database, 
                      const std::vector<std::string>& filenames);
  void view(const std::string& database, 
            const std::vector<std::string>& filenames);
};

#endif

/* EOF */