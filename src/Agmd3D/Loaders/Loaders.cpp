//==========================================================
// Agmd::Engine - Free C++ 3D engine
//
// Copyright (C) 2004-2005 Laurent Gomila
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc.,
// 59 Temple Place - Suite 330,
// Boston, MA  02111-1307, USA.
//
// E-mail : laurent.gom@gmail.com
//==========================================================
#include <Loaders/Loaders.h>
#include <Loaders/ImagesLoader.h>
#include <Loaders/ShadersLoader.h>
#include <Loaders/ShaderProgramsLoader.h>
#include <Loaders/ObjLoader.h>
#include <Loaders/TxtLoader.h>
#include <Core/MediaManager.h>
#include <Debug/New.h>


namespace Agmd
{

	void RegisterLoaders()
	{
		MediaManager& mediaManager = MediaManager::Instance();

		mediaManager.RegisterLoader(new ImagesLoader, "bmp, dds, jpg, pcx, png, pnm, raw, sgi, tga, tif");
		mediaManager.RegisterLoader(new ShadersLoader(SHADER_VERTEX), "vert");
		mediaManager.RegisterLoader(new ShadersLoader(SHADER_PIXEL),  "frag");
		mediaManager.RegisterLoader(new ShadersLoader(SHADER_GEOMETRY),  "geom");
		mediaManager.RegisterLoader(new ShadersLoader(SHADER_TESS_CONTROL),  "tessc");
		mediaManager.RegisterLoader(new ShadersLoader(SHADER_TESS_EVALUATION),  "tesse");
		mediaManager.RegisterLoader(new ShaderProgramsLoader(), "glsl");
		//mediaManager.RegisterLoader(new TxtLoader(),"txt");
		mediaManager.RegisterLoader(new ObjLoader(), "obj");
	}

} // namespace Agmd
