/***************************************************************************
 *          GSkyDir.cpp  -  Class that implements a sky direction          *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2008-2011 by Jurgen Knodlseder                           *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
/**
 * @file GSkyDir.cpp
 * @brief GSkyDir class implementation.
 * @author J. Knodlseder
 */

/* __ Includes ___________________________________________________________ */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <cmath>
#include "GException.hpp"
#include "GTools.hpp"
#include "GSkyDir.hpp"
#include "GMatrix.hpp"
#include "GVector.hpp"

/* __ Method name definitions ____________________________________________ */

/* __ Macros _____________________________________________________________ */

/* __ Coding definitions _________________________________________________ */

/* __ Debug definitions __________________________________________________ */

/* __ Prototypes _________________________________________________________ */

/*==========================================================================
 =                                                                         =
 =                          Constructors/destructors                       =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Constructor
 ***************************************************************************/
GSkyDir::GSkyDir(void)
{
    // Initialise class members for clean destruction
    init_members();

    // Return
    return;
}


/***********************************************************************//**
 * @brief Copy constructor
 *
 * @param[in] dir Sky direction from which class should be instantiated.
 ***************************************************************************/
GSkyDir::GSkyDir(const GSkyDir& dir)
{
    // Initialise class members for clean destruction
    init_members();

    // Copy members
    copy_members(dir);

    // Return
    return;
}


/***********************************************************************//**
 * @brief Destructor
 ***************************************************************************/
GSkyDir::~GSkyDir(void)
{
    // Free members
    free_members();

    // Return
    return;
}


/*==========================================================================
 =                                                                         =
 =                                Operators                                =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Assignment operator
 *
 * @param[in] dir Sky direction to be assigned.
 ***************************************************************************/
GSkyDir& GSkyDir::operator= (const GSkyDir& dir)
{
    // Execute only if object is not identical
    if (this != &dir) {

        // Free members
        free_members();

        // Initialise private members
        init_members();

        // Copy members
        copy_members(dir);

    } // endif: object was not identical

    // Return this object
    return *this;
}


/*==========================================================================
 =                                                                         =
 =                              Public methods                             =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Clear sky direction
 ***************************************************************************/
void GSkyDir::clear(void)
{
    // Free members
    free_members();

    // Initialise private members
    init_members();

    // Return
    return;
}



/***********************************************************************//**
 * @brief Set equatorial sky direction (radians)
 *
 * @param[in] ra Right Ascension in radians.
 * @param[in] dec Declination in radians.
 ***************************************************************************/
void GSkyDir::radec(const double& ra, const double& dec)
{
    // Set attributes
    m_has_lb    = false;
    m_has_radec = true;

    // Set direction
    m_ra  = ra;
    m_dec = dec;

    // Return
    return;
}


/***********************************************************************//**
 * @brief Set equatorial sky direction (degrees)
 *
 * @param[in] ra Right Ascension in degrees.
 * @param[in] dec Declination in degrees.
 ***************************************************************************/
void GSkyDir::radec_deg(const double& ra, const double& dec)
{
    // Set attributes
    m_has_lb    = false;
    m_has_radec = true;

    // Set direction
    m_ra  = ra  * deg2rad;
    m_dec = dec * deg2rad;

    // Return
    return;
}


/***********************************************************************//**
 * @brief Set galactic sky direction (radians)
 *
 * @param[in] l Galactic longitude in radians.
 * @param[in] b Galactic latitude in radians.
 ***************************************************************************/
void GSkyDir::lb(const double& l, const double& b)
{
    // Set attributes
    m_has_lb    = true;
    m_has_radec = false;

    // Set direction
    m_l = l;
    m_b = b;

    // Return
    return;
}


/***********************************************************************//**
 * @brief Set galactic sky direction (degrees)
 *
 * @param[in] l Galactic longitude in degrees.
 * @param[in] b Galactic latitude in degrees.
 ***************************************************************************/
void GSkyDir::lb_deg(const double& l, const double& b)
{
    // Set attributes
    m_has_lb    = true;
    m_has_radec = false;

    // Set direction
    m_l = l * deg2rad;
    m_b = b * deg2rad;

    // Return
    return;
}


/***********************************************************************//**
 * @brief Set sky direction from 3D vector in celestial coordinates
 *
 * @param[in] vector 3D vector.
 ***************************************************************************/
void GSkyDir::celvector(const GVector& vector)
{
    // Set attributes
    m_has_lb    = false;
    m_has_radec = true;

    // Convert vector into sky position
    m_dec = asin(vector(2));
    m_ra  = atan2(vector(1), vector(0));

    // Return
    return;
}


/***********************************************************************//**
 * @brief Rotate sky direction by zenith and azimuth angle
 *
 * @param[in] phi Azimuth angle (deg).
 * @param[in] theta Zenith angle (deg).
 *
 * Rotate sky direction by a zenith and azimuth angle given in the system
 * of the sky direction and aligned in celestial coordinates. 
 * The azimuth angle is counted counter clockwise from celestial north
 * (this is identical to the astronomical definition of a position angle).
 ***************************************************************************/
void GSkyDir::rotate(const double& phi, const double& theta)
{
    // If we have no equatorial coordinates then get them now
    if (!m_has_radec && m_has_lb)
        gal2equ();

    // Allocate Euler and rotation matrices
    GMatrix Ry;
    GMatrix Rz;
    GMatrix Rback;
    GMatrix Rrot;

    // Set up rotation matrix to rotate into and back from the native
    // coordinate
    Ry.eulery(m_dec*rad2deg - 90.0);
    Rz.eulerz(-m_ra*rad2deg);
    Rback = transpose(Ry * Rz);

    // Set up rotation matrix for native coordinate vector
    Ry.eulery(-theta);
    Rz.eulerz(-phi);
    Rrot = Rz * Ry;

    // Set native coordinate vector (in z-direction by definition)
    GVector native(0.0, 0.0, 1.0);

    // Rotate native coordinate vector
    GVector rotnative = Rrot * native;

    // Rotate vector back into sky direction
    GVector dir = Rback * rotnative;

    // Set sky direction
    celvector(dir);

    // Return
    return;
}


/***********************************************************************//**
 * @brief Returns galactic longitude in radians
 ***************************************************************************/
double GSkyDir::l(void) const
{
    // If we have no galactic coordinates then get them now
    if (!m_has_lb && m_has_radec)
        equ2gal();

    // Return galactic longitude
    return m_l;
}


/***********************************************************************//**
 * @brief Returns galactic longitude in degrees
 ***************************************************************************/
double GSkyDir::l_deg(void) const
{
    // If we have no galactic coordinates then get them now
    if (!m_has_lb && m_has_radec)
        equ2gal();

    // Return galactic longitude
    return m_l * rad2deg;
}


/***********************************************************************//**
 * @brief Returns galactic latitude in radians
 ***************************************************************************/
double GSkyDir::b(void) const
{
    // If we have no galactic coordinates then get them now
    if (!m_has_lb && m_has_radec)
        equ2gal();

    // Return galactic latitude
    return m_b;
}


/***********************************************************************//**
 * @brief Returns galactic latitude in degrees
 ***************************************************************************/
double GSkyDir::b_deg(void) const
{
    // If we have no galactic coordinates then get them now
    if (!m_has_lb && m_has_radec)
        equ2gal();

    // Return galactic latitude
    return m_b * rad2deg;
}


/***********************************************************************//**
 * @brief Returns Right Ascension in radians
 ***************************************************************************/
double GSkyDir::ra(void) const
{
    // If we have no equatorial coordinates then get them now
    if (!m_has_radec && m_has_lb)
        gal2equ();

    // Return Right Ascension
    return m_ra;
}


/***********************************************************************//**
 * @brief Returns Right Ascension in degrees
 ***************************************************************************/
double GSkyDir::ra_deg(void) const
{
    // If we have no equatorial coordinates then get them now
    if (!m_has_radec && m_has_lb)
        gal2equ();

    // Return Right Ascension
    return m_ra * rad2deg;
}


/***********************************************************************//**
 * @brief Returns Declination in radians
 ***************************************************************************/
double GSkyDir::dec(void) const
{
    // If we have no equatorial coordinates then get them now
    if (!m_has_radec && m_has_lb)
        gal2equ();

    // Return Declination
    return m_dec;
}


/***********************************************************************//**
 * @brief Returns Declination in degrees
 ***************************************************************************/
double GSkyDir::dec_deg(void) const
{
    // If we have no equatorial coordinates then get them now
    if (!m_has_radec && m_has_lb)
        gal2equ();

    // Return Declination
    return m_dec * rad2deg;
}


/***********************************************************************//**
 * @brief Returns sky direction as 3D vector in celestial coordinates
 ***************************************************************************/
GVector GSkyDir::celvector(void) const
{
    // If we have no equatorial coordinates then get them now
    if (!m_has_radec && m_has_lb)
        gal2equ();

    // Compute 3D vector
    double  cosra  = cos(m_ra);
    double  sinra  = sin(m_ra);
    double  cosdec = cos(m_dec);
    double  sindec = sin(m_dec);
    GVector vector(cosdec*cosra, cosdec*sinra, sindec);

    // Return vector
    return vector;
}


/***********************************************************************//**
 * @brief Compute angular distance between sky directions in radians
 *
 * @param[in] dir Sky direction to which distance is to be computed.
 ***************************************************************************/
double GSkyDir::dist(const GSkyDir& dir) const
{
    // Initialise cosine of distance
    double cosdis;

    // Compute dependent on coordinate system availability. This speeds
    // up things by avoiding unnecessary coordinate transformations.
    if (m_has_lb && dir.m_has_lb) {
        cosdis = sin(m_b)*sin(dir.m_b) +
                 cos(m_b)*cos(dir.m_b) * cos(dir.m_l - m_l);
    }
    else if (m_has_radec && dir.m_has_radec) {
        cosdis = sin(m_dec)*sin(dir.m_dec) +
                 cos(m_dec)*cos(dir.m_dec) * cos(dir.m_ra - m_ra);
    }
    else if (m_has_lb) {
        cosdis = sin(m_b)*sin(dir.b()) +
                 cos(m_b)*cos(dir.b()) * cos(dir.l() - m_l);
    }
    else if (m_has_radec) {
        cosdis = sin(m_dec)*sin(dir.dec()) +
                 cos(m_dec)*cos(dir.dec()) * cos(dir.ra() - m_ra);
    }
    else {
        cosdis = sin(dec())*sin(dir.dec()) +
                 cos(dec())*cos(dir.dec()) * cos(dir.ra() - ra());
    }

    // Put cosine of distance in [-1,1]
    if (cosdis < -1.0) cosdis = -1.0;
    if (cosdis >  1.0) cosdis =  1.0;

    // Compute distance
    double dist = acos(cosdis);

    // Return distance
    return dist;
}


/***********************************************************************//**
 * @brief Compute angular distance between sky directions in degrees
 *
 * @param[in] dir Sky direction to which distance is to be computed.
 ***************************************************************************/
double GSkyDir::dist_deg(const GSkyDir& dir) const
{
    // Return distance in degrees
    return (dist(dir) * rad2deg);
}


/***********************************************************************//**
 * @brief Print vector information
 ***************************************************************************/
std::string GSkyDir::print(void) const
{
    // Initialise result string
    std::string result;

    // Put coordinates in string
    if (m_has_lb)
        result = "(l,b)=("+str(m_l*rad2deg)+","+str(m_b*rad2deg)+")";
    else if (m_has_radec)
        result = "(RA,Dec)=("+str(m_ra*rad2deg)+","+str(m_dec*rad2deg)+")";
    else
        result = "(RA,Dec)=(not initialised)";

    // Return result
    return result;
}


/*==========================================================================
 =                                                                         =
 =                             Private methods                             =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Initialise class members
 ***************************************************************************/
void GSkyDir::init_members(void)
{
    // Initialise members
    m_has_lb    = false;
    m_has_radec = false;
    m_l         = 0.0;
    m_b         = 0.0;
    m_ra        = 0.0;
    m_dec       = 0.0;

    // Return
    return;
}


/***********************************************************************//**
 * @brief Copy class members
 *
 * @param[in] dir Sky direction from which members should be copied
 ***************************************************************************/
void GSkyDir::copy_members(const GSkyDir& dir)
{
    // Copy attributes
    m_has_lb    = dir.m_has_lb;
    m_has_radec = dir.m_has_radec;
    m_l         = dir.m_l;
    m_b         = dir.m_b;
    m_ra        = dir.m_ra;
    m_dec       = dir.m_dec;

    // Return
    return;
}


/***********************************************************************//**
 * @brief Delete class members
 ***************************************************************************/
void GSkyDir::free_members(void)
{
    // Return
    return;
}


/***********************************************************************//**
 * @brief Convert equatorial to galactic coordinates
 ***************************************************************************/
void GSkyDir::equ2gal(void) const
{
    // Get non-const pointers to data members. This allows to circumvent
    // the const correctness and allows treating GSkyDir access methods
    // as const
    double* l = (double*)&m_l;
    double* b = (double*)&m_b;

    // Convert from equatorial to galactic
    euler(0, m_ra, m_dec, l, b);

    // Return
    return;
}


/***********************************************************************//**
 * @brief Convert galactic to equatorial coordinates
 ***************************************************************************/
void GSkyDir::gal2equ(void) const
{
    // Get non-const pointers to data members. This allows to circumvent
    // the const correctness and allows treating GSkyDir access methods
    // as const
    double* ra  = (double*)&m_ra;
    double* dec = (double*)&m_dec;

    // Convert from galactic to equatorial
    euler(1, m_l, m_b, ra, dec);

    // Return
    return;
}


/***********************************************************************//**
 * @brief General coordinate transformation routine for J2000
 *
 * @param[in] type Conversion type (0=equ2gal, 1=gal2equ)
 * @param[in] xin Input longitude (RA or GLON) in radians.
 * @param[in] yin Input latitude (Dec or GLAT) in radians.
 * @param[out] xout Output longitude in radians.
 * @param[out] yout Output latitude in radians.
 ***************************************************************************/
void GSkyDir::euler(const int& type, const double& xin, const double &yin, 
                    double* xout, double *yout) const
{
    // Set transformation constants
    const double psi[]    = {0.57477043300,  4.9368292465};
    const double stheta[] = {0.88998808748, -0.88998808748};
    const double ctheta[] = {0.45598377618,  0.45598377618};
    const double phi[]    = {4.9368292465,   0.57477043300};

    // Perform transformation
    double a    = xin - phi[type];
    double b    = yin;
    double sb   = sin(b);
    double cb   = cos(b);
    double cbsa = cb * sin(a);

    //
    a = atan2(ctheta[type] * cbsa + stheta[type] * sb, cb * cos(a));
    b = -stheta[type] * cbsa + ctheta[type] * sb;
    if (b > 1.0)
        b = 1.0;

    //
    *yout = asin(b);
    *xout = modulo((a+psi[type] + fourpi), twopi);

    // Return
    return;
}


/*==========================================================================
 =                                                                         =
 =                                 Friends                                 =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Output operator
 *
 * @param[in] os Output stream.
 * @param[in] dir Sky direction.
 ***************************************************************************/
std::ostream& operator<< (std::ostream& os, const GSkyDir& dir)
{
     // Write sky direction in output stream
    os << dir.print();

    // Return output stream
    return os;
}


/***********************************************************************//**
 * @brief Log operator
 *
 * @param[in] log Logger.
 * @param[in] dir Sky direction.
 ***************************************************************************/
GLog& operator<< (GLog& log, const GSkyDir& dir)
{
    // Write sky direction into logger
    log << dir.print();

    // Return logger
    return log;
}


