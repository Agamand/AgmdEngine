#ifndef GRAPHICSTRING_H
#define GRAPHICSTRING_H

#include <Config/Export.h>
#include <Config/Fwd.h>
#include <Utilities/Color.h>
#include <Utilities/Singleton.h>
#include <Core/Buffer.h>
#include <Maths/Vector2.h>
#include <Maths/Rectangle.h>
#include <map>
#include <string>


namespace Agmd
{
    class AGMD_EXPORT GraphicString
    {
    public :

        GraphicString(const ivec2 & StringPosition = ivec2(0), const std::string& StringText = "", const Color& StringColor = Color::white, const std::string& StringFont = "Arial", int StringSize = 16);

        void Draw() const;

        ivec2 GetPixelSize() const;

        //----------------------------------------------------------
        // Modifie l'alignement du texte
        //----------------------------------------------------------
		void Align(unsigned long Mode, const Rectangle& Rect);

        //----------------------------------------------------------
        // Donn�es membres
        //----------------------------------------------------------
        ivec2   Position; ///< Position du texte � l'�cran
        std::string Text;     ///< Cha�ne de caract�res
        Color      color;    ///< Couleur du texte
        std::string Font;     ///< Police de caract�res
        int         Size;     ///< Taille du texte
    };

} // namespace Yes


#endif // GRAPHICSTRING_H
