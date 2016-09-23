/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include "ImagesLoader.h"
#include <DevIL/il.h>
#include <Vector2.h>
#include <Core/Texture/Image.h>
#include <Utilities/PixelUtils.h>
#include <algorithm>
#include <CommonDefines.h>
#include <Debug/New.h>


namespace Agmd
{
    ImagesLoader::ImagesLoader()
    {
        ilInit();

        ilOriginFunc(IL_ORIGIN_UPPER_LEFT);
        ilEnable(IL_ORIGIN_SET);

        ilEnable(IL_FILE_OVERWRITE);

        ilSetInteger(IL_FORMAT_MODE, IL_BGRA);
        ilEnable(IL_FORMAT_SET);
    }

    ImagesLoader::~ImagesLoader()
    {
        ilShutDown();
    }

    Image* ImagesLoader::LoadFromFile(const std::string& filename)
    {
        a_uint32 texture;
        ilGenImages(1, &texture);
        ilBindImage(texture);

        if (!ilLoadImage(const_cast<ILstring>(filename.c_str())))
            throw LoadingFailed(filename, "Erreur DevIL : l'appel à ilLoadImage a échoué");

        ivec2 Size(ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT));

        unsigned char* Pixels = reinterpret_cast<unsigned char*>(ilGetData());

        Image* image = new Image(Size, PXF_A8R8G8B8, Pixels);

        ilDeleteImages(1, &texture);

        image->Flip();

        return image;
    }

    void ImagesLoader::SaveToFile(const Image* object, const std::string& filename)
    {
        Image image(object->GetSize(), PXF_A8R8G8B8);
        image.CopyImage(*object);

        image.Flip();

        a_uint32 texture;
        ilGenImages(1, &texture);
        ilBindImage(texture);

        const ivec2& size = image.GetSize();


        if (!ilTexImage(size.x, size.y, 1, GetBytesPerPixel(image.GetFormat()), IL_BGRA, IL_UNSIGNED_BYTE, (void*)image.GetData()))
            throw LoadingFailed(filename, "Erreur DevIL : l'appel à ilTexImage a échoué");

        if (!ilSaveImage(const_cast<ILstring>(filename.c_str())))
            throw LoadingFailed(filename, "Erreur DevIL : l'appel à ilSaveImage a échoué");

        ilDeleteImages(1, &texture);
    }
} // namespace Agmd
