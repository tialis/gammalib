/***************************************************************************
 *      GFitsImage.i  - FITS image abstract base class SWIG interface      *
 * ----------------------------------------------------------------------- *
 *  copyright : (C) 2008-2010 by Jurgen Knodlseder                         *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
/**
 * @file GFitsImage.i
 * @brief GFitsImage class SWIG file.
 * @author J. Knodlseder
 */
%{
/* Put headers and other declarations here that are needed for compilation */
#include "GFitsImage.hpp"
%}

/***********************************************************************//**
 * @class GFitsImage
 *
 * @brief Abstract SWIG interface for the FITS image classes.
 ***************************************************************************/
class GFitsImage : public GFitsHDU {
public:
    // Constructors and destructors
    GFitsImage(void);
    GFitsImage(int bitpix, int naxis, const int* naxes);
    GFitsImage(const GFitsImage& image);
    virtual ~GFitsImage(void);

    // Pure virtual methods
    virtual void*       pixels(void) = 0;
    virtual double      pixel(const int& ix) const = 0;
    virtual double      pixel(const int& ix, const int& iy) const = 0;
    virtual double      pixel(const int& ix, const int& iy, const int& iz) const = 0;
    virtual double      pixel(const int& ix, const int& iy, const int& iz, const int& it) const = 0;
    virtual GFitsImage* clone(void) const = 0;

    // Implemented pure virtual methods
    HDUType exttype(void) const { return HT_IMAGE; }

    // Methods
    int  size(void) const;
    int  bitpix(void) const;
    int  naxis(void) const;
    int  naxes(int axis) const;
    int  anynul(void) const;
    void nulval(const void* value);
};
