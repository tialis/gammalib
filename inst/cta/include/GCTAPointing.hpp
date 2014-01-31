/***************************************************************************
 *                  GCTAPointing.hpp - CTA pointing class                  *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2010-2013 by Juergen Knoedlseder                         *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 *  This program is free software: you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, either version 3 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.  *
 *                                                                         *
 ***************************************************************************/
/**
 * @file GCTAPointing.hpp
 * @brief CTA pointing class interface definition
 * @author Juergen Knoedlseder
 */

#ifndef GCTAPOINTING_HPP
#define GCTAPOINTING_HPP

/* __ Includes ___________________________________________________________ */
#include <string>
#include "GSkyDir.hpp"
#include "GTime.hpp"
#include "GMatrix.hpp"
#include "GNodeArray.hpp"
#include "GHorizDir.hpp"

/***********************************************************************//**
 * @class GCTAPointing
 *
 * @brief CTA pointing class.
 *
 * This class implements a CTA pointing. For the time being it is assumed
 * that the pointing direction is time-independent.
 *
 * @todo No transformation from sky coordinates to geographic coordinates
 *       has so far been implemented. The azimuth and zenith angle are not
 *       meaningful.
 ***************************************************************************/
class GCTAPointing : public GBase {

public:
    // Constructors and destructors
    GCTAPointing(void);
    explicit GCTAPointing(const GSkyDir& dir);
    GCTAPointing(const GCTAPointing& pnt);
    virtual ~GCTAPointing(void);

    // Operators
    virtual GCTAPointing& operator=(const GCTAPointing& pnt);

    // Implemented pure virtual methods
    virtual void           clear(void);
    virtual GCTAPointing*  clone(void) const;
    virtual const GSkyDir& dir(void) const;
    virtual std::string    print(const GChatter& chatter = NORMAL) const;

    // Other methods
    void           dir(const GSkyDir& dir);
    const GMatrix& rot(void) const;
    const double&  zenith(void) const;
    const double&  azimuth(void) const;
    const GHorizDir dir_horiz( const GTime &time ) const;


    void           load_pointing_table(std::string filename);

protected:
    // Protected methods
    void init_members(void);
    void copy_members(const GCTAPointing& pnt);
    void free_members(void);
    void update(void) const;



    // Protected members
    GSkyDir         m_dir;        //!< Pointing direction in sky coordinates
    double          m_zenith;     //!< Pointing zenith angle
    double          m_azimuth;    //!< Pointing azimuth angle


    bool                m_has_table; //!< table is loaded
    GNodeArray          m_table_nodes;
    std::vector<double> m_table_az; //!< table of azimuths (rad)
    std::vector<double> m_table_alt; //!< table of altitudes (rad)
    GTime               m_table_tmin; //!< min time bound in table
    GTime               m_table_tmax; //!<max time bound in table

    // Cached members
    mutable bool    m_has_cache;  //!< Has transformation cache
    mutable GMatrix m_Rback;      //!< Rotation matrix
};


/***********************************************************************//**
 * @brief Return pointing sky direction
 *
 * @return Pointing sky direction.
 ***************************************************************************/
inline
const GSkyDir& GCTAPointing::dir(void) const
{
    return m_dir;
}


/***********************************************************************//**
 * @brief Return pointing zenith angle
 *
 * @return Pointing zenith angle.
 ***************************************************************************/
inline
const double& GCTAPointing::zenith(void) const
{
    return m_zenith;
}


/***********************************************************************//**
 * @brief Return pointing azimuth angle
 *
 * @return Pointing zenith angle.
 ***************************************************************************/
inline
const double& GCTAPointing::azimuth(void) const
{
    return m_azimuth;
}

#endif /* GCTAPOINTING_HPP */
