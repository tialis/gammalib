/***************************************************************************
 *     GModelSpatialShell.hpp  -  Spatial shell source model class         *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2011 by Christoph Deil                                   *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
/**
 * @file GModelSpatialShell.hpp
 * @brief Spatial shell model class interface definition
 * @author C. Deil
 */

#ifndef GMODELSPATIALSHELL_HPP
#define GMODELSPATIALSHELL_HPP

/* __ Includes ___________________________________________________________ */
#include <string>
#include "GModelSpatial.hpp"
#include "GModelPar.hpp"
#include "GSkyDir.hpp"
#include "GXmlElement.hpp"


/**************************************************************************
 * @class GModelSpatialShell
 *
 * @brief Shell source model class
 *
 * This class implements the spatial component of the factorised source
 * model for a shell source (can be used e.g. as a toy supernova remnant model).
 * The shell is simply the volume between an inner and outer radius
 * (a large sphere with a smaller sphere cut out) with constant
 * volume emissivity and no absorption.
 * To get the surface brightness distribution on the sky, this sphere is
 * integrated along parallel lines of sight.
 ***************************************************************************/
class GModelSpatialShell : public GModelSpatial {

public:
    // Constructors and destructors
    GModelSpatialShell(void);
    explicit GModelSpatialShell(const GSkyDir& dir,
                                const double& theta, const double& width);
    explicit GModelSpatialShell(const GXmlElement& xml);
    GModelSpatialShell(const GModelSpatialShell& model);
    virtual ~GModelSpatialShell(void);

    // Operators
    virtual GModelSpatialShell& operator=(const GModelSpatialShell& model);

    // Implemented pure virtual methods
    virtual void                clear(void);
    virtual GModelSpatialShell* clone(void) const;
    virtual std::string         type(void) const { return "ShellFunction"; }
    virtual double              eval(const GSkyDir& srcDir) const;
    virtual double              eval_gradients(const GSkyDir& srcDir) const;
    virtual GSkyDir             mc(GRan& ran) const;
    virtual void                read(const GXmlElement& xml);
    virtual void                write(GXmlElement& xml) const;
    virtual std::string         print(void) const;

    // Other methods
    double  ra(void) const { return m_ra.real_value(); }
    double  dec(void) const { return m_dec.real_value(); }
    double  radius(void) const { return m_radius.real_value(); }
    double  width(void) const { return m_width.real_value(); }
    GSkyDir dir(void) const;
    void    dir(const GSkyDir& dir);
    void    radius(const double& radius) { m_radius.real_value(radius); }
    void    width(const double& width) { m_width.real_value(width); }

protected:
    // Protected methods
    void init_members(void);
    void copy_members(const GModelSpatialShell& model);
    void free_members(void);

    // Protected members
    GModelPar m_ra;        //!< Right Ascension of shell centre (deg)
    GModelPar m_dec;       //!< Declination of shell centre (deg)
    GModelPar m_radius;    //!< Inner shell radius (deg)
    GModelPar m_width;     //!< Shell thickness (deg)
};

#endif /* GMODELSPATIALSHELL_HPP */
