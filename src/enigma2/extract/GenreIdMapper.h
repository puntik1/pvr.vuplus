#pragma once
/*
 *      Copyright (C) 2005-2019 Team XBMC
 *      http://www.xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 51 Franklin Street, Fifth Floor, Boston,
 *  MA 02110-1335, USA.
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */

#include "IExtractor.h"

#include <map>
#include <string>

namespace enigma2
{
  namespace extract
  {
    class GenreIdMapper : public IExtractor
    {
    public:
      GenreIdMapper();
      ~GenreIdMapper();

      void ExtractFromEntry(enigma2::data::BaseEntry& entry);
      bool IsEnabled();

    private:
      static int GetGenreTypeFromCombined(int combinedGenreType);
      static int GetGenreSubTypeFromCombined(int combinedGenreType);

      int LookupGenreIdInMap(const int genreId);

      void LoadGenreIdMapFile();
      bool LoadIdToIdGenreFile(const std::string& xmlFile, std::map<int, int>& map);
      void CreateGenreAddonDataDirectories();

      std::map<int, int> m_genreIdToDvbIdMap;
    };
  } //namespace extract
} //namespace enigma2