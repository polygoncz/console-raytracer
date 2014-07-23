#ifndef FILM_H
#define FILM_H

#include "core.h"

/*!
 * Třída Film reprezentuje film v kameře. Narozdíl od klasického filmu v reálném světě,
 * tento uchovává takové atributy, které jsou potom využitelné pro práci s počítačovou grafikou.
 */
class Film
{
public:
    Film(size_t w, size_t h, float size);
    ~Film();

    /*!
     * \brief Vrací celkový počet pixelů.
     * \return Celkový počet pixelů.
     */
    size_t pixelCount() const;

    /*!
     * \brief Vraci sirku obrazku v pixelech.
     * \return Sirka obrazku.
     */
    size_t width() const;

    /*!
     * \brief Vraci vysku obrazku v pixelech.
     * \return Vyska obrazku.
     */
    size_t height() const;

    /*!
     * \brief Velikost hrany jednoho pixelu ve scene.
     * \return velikost pixelu v jednotkach sceny.
     */
    float size() const;

    /*!
     * \brief Slouzi k ulozeni barvy na konkretni pixel v obrazku.
     * \param c barva
     * \param w poloha ve vodorovnem smeru
     * \param h poloha ve svislem smeru
     */
    void setPixelColor(const RGBColor& c, const size_t w, const size_t h);

    /*!
     * \brief Slouzi pro ziskani barvy pixelu v obrazku.
     * \param w poloha ve vodorovnem smeru
     * \param h poloha ve svislem smeru
     * \return barvu vysledneho pixelu
     */
    RGBColor getPixelColor(const size_t w, const size_t h) const;

private:
    /*!
     * \brief Index pixelu v jednorozmernem poli data.
     * \param x index v prvnim rozmeru
     * \param y index ve druhem rozmeru
     * \return index v jednorozmernem poli
     */
    inline size_t offset(const size_t x, const size_t y) const
    {
        return x * _width + y;
    }

private:
    size_t _width; ///< sirka
    size_t _height; ///< vyska
    size_t _pixelCount;
    float _size; ///< velikost pixelu
    RGBColor* data; ///< buffer na hodnoty pixelu
};

#endif // FILM_H
