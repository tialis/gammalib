/***************************************************************************
 *           GSPIEventCube.cpp  -  SPI event bin container class           *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2013 by Juergen Knoedlseder                              *
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
 * @file GSPIEventCube.cpp
 * @brief SPI event bin container class implementation
 * @author Juergen Knoedlseder
 */

/* __ Includes ___________________________________________________________ */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "GTools.hpp"
#include "GFits.hpp"
#include "GSPIException.hpp"
#include "GSPIEventCube.hpp"

/* __ Method name definitions ____________________________________________ */

/* __ Macros _____________________________________________________________ */

/* __ Coding definitions _________________________________________________ */

/* __ Debug definitions __________________________________________________ */



/*==========================================================================
 =                                                                         =
 =                        Constructors/destructors                         =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Void constructor
 *
 * Constructs an empty event cube.
 ***************************************************************************/
GSPIEventCube::GSPIEventCube(void) : GEventCube()
{
    // Initialise members
    init_members();

    // Return
    return;
}


/***********************************************************************//**
 * @brief Load constructor
 *
 * @param[in] filename Event cube FITS filename.
 *
 * Construct an event cube by loading information from a FITS file.
 ***************************************************************************/
GSPIEventCube::GSPIEventCube(const std::string& filename) : GEventCube()
{
    // Initialise members
    init_members();

    // Load event cube
    load(filename);

    // Return
    return;
}


/***********************************************************************//**
 * @brief Copy constructor
 *
 * @param[in] cube Event cube.
 ***************************************************************************/
GSPIEventCube::GSPIEventCube(const GSPIEventCube& cube) : GEventCube(cube)
{
    // Initialise members
    init_members();

    // Copy members
    copy_members(cube);

    // Return
    return;
}


/***********************************************************************//**
 * @brief Destructor
 ***************************************************************************/
GSPIEventCube::~GSPIEventCube(void)
{
    // Free members
    free_members();

    // Return
    return;
}


/*==========================================================================
 =                                                                         =
 =                               Operators                                 =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Assignment operator
 *
 * @param[in] cube Event cube.
 * @return Event cube.
 ***************************************************************************/
GSPIEventCube& GSPIEventCube::operator= (const GSPIEventCube& cube)
{
    // Execute only if object is not identical
    if (this != &cube) {

        // Copy base class members
        this->GEventCube::operator=(cube);

        // Free members
        free_members();

        // Initialise members
        init_members();

        // Copy members
        copy_members(cube);

    } // endif: object was not identical

    // Return this object
    return *this;
}


/***********************************************************************//**
 * @brief Event bin access operator
 *
 * @param[in] index Event index [0,...,size()-1].
 * @return Pointer to event bin.
 ***************************************************************************/
GSPIEventBin* GSPIEventCube::operator[](const int& index)
{
    // TODO: Implement method (dummy code only)
    GSPIEventBin* ptr;

    // Return pointer
    return ptr;
}


/***********************************************************************//**
 * @brief Event bin access operator (const version)
 *
 * @param[in] index Event index [0,...,size()-1].
 * @return Const pointer to event bin.
 ***************************************************************************/
const GSPIEventBin* GSPIEventCube::operator[](const int& index) const
{
    // TODO: Implement method (dummy code only)
    GSPIEventBin* ptr;

    // Return pointer
    return ptr;
}


/*==========================================================================
 =                                                                         =
 =                             Public methods                              =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Clear instance
 *
 * This method properly resets the object to an initial state.
 ***************************************************************************/
void GSPIEventCube::clear(void)
{
    // Free class members (base and derived classes, derived class first)
    free_members();
    this->GEventCube::free_members();
    this->GEvents::free_members();

    // Initialise members
    this->GEvents::init_members();
    this->GEventCube::init_members();
    init_members();

    // Return
    return;
}


/***********************************************************************//**
 * @brief Clone instance
 *
 * @return Pointer to deep copy of event cube.
 ***************************************************************************/
GSPIEventCube* GSPIEventCube::clone(void) const
{
    return new GSPIEventCube(*this);
}


/***********************************************************************//**
 * @brief Return number of bins in event cube
 *
 * @return Number of bins in event cube.
 ***************************************************************************/
int GSPIEventCube::size(void) const
{
    // TODO: Implement method

    // Return number of bins
    return 0;
}


/***********************************************************************//**
 * @brief Return dimension of event cube
 *
 * @return Number of dimensions in event cube.
 ***************************************************************************/
int GSPIEventCube::dim(void) const
{
    // TODO: Implement method

    // Return dimension
    return 0;
}


/***********************************************************************//**
 * @brief Return number of bins in axis
 *
 * @param[in] axis Axis.
 * @return Number of bins in axis.
 *
 * Returns the number of bins along a given event cube axis.
 ***************************************************************************/
int GSPIEventCube::naxis(int axis) const
{
    // TODO: Implement method

    // Return result
    return 0;
}


/***********************************************************************//**
 * @brief Load SPI event cube from FITS file
 *
 * @param[in] filename FITS filename.
 *
 * The method clears the object before loading, thus any events residing in
 * the object before loading will be lost.
 ***************************************************************************/
void GSPIEventCube::load(const std::string& filename)
{
    // Clear object
    clear();

    // Open FITS file
    GFits file(filename);

    // Load cube
    read(file);

    // Close FITS file
    file.close();

    // Return
    return;
}


/***********************************************************************//**
 * @brief Save SPI event cube into FITS file
 *
 * @param[in] filename FITS filename.
 * @param[in] clobber Overwrite existing FITS file (default=false).
 *
 * Save the SPI event cube into FITS file.
 ***************************************************************************/
void GSPIEventCube::save(const std::string& filename, bool clobber) const
{
    // Create empty FITS file
    GFits fits;

    // Write event cube
    write(fits);
    
    // Save FITS file
    fits.saveto(filename, clobber);

    // Return
    return;
}


/***********************************************************************//**
 * @brief Read SPI event cube from FITS file
 *
 * @param[in] file FITS file.
 ***************************************************************************/
void GSPIEventCube::read(const GFits& file)
{
    // Clear object
    clear();

    // TODO: Implement method

    // Return
    return;
}


/***********************************************************************//**
 * @brief Write SPIPTEL event cube into FITS file.
 *
 * @param[in] file FITS file.
 ***************************************************************************/
void GSPIEventCube::write(GFits& file) const
{
    // TODO: Implement method

    // Return
    return;
}


/***********************************************************************//**
 * @brief Return number of events in cube
 *
 * @return Number of events in event cube.
 *
 * This method returns the number of events in the event cube rounded to the
 * nearest integer.
 ***************************************************************************/
int GSPIEventCube::number(void) const
{
    // TODO: Implement method

    // Return
    return 0;
}


/***********************************************************************//**
 * @brief Print event cube information
 *
 * @return String containing event cube information.
 ***************************************************************************/
std::string GSPIEventCube::print(void) const
{
    // Initialise result string
    std::string result;

    // Append header
    result.append("=== GSPIEventCube ===");

    // Append cube information
    result.append("\n"+parformat("Number of events")+str(number()));
    result.append("\n"+parformat("Number of elements")+str(size()));

    // TODO: Add any further relevant information

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
void GSPIEventCube::init_members(void)
{
    // TODO: Initialise all class members

    // Return
    return;
}


/***********************************************************************//**
 * @brief Copy class members
 *
 * @param[in] cube Event cube.
 ***************************************************************************/
void GSPIEventCube::copy_members(const GSPIEventCube& cube)
{
    // TODO: Copy all class members

    // Return
    return;
}


/***********************************************************************//**
 * @brief Delete class members
 ***************************************************************************/
void GSPIEventCube::free_members(void)
{
    // TODO: Free all memory allocated by the object (not needed if no
    // memory has been allocated)

    // Return
    return;
}


/***********************************************************************//**
 * @brief Set log mean energy and energy width of event cube
 ***************************************************************************/
void GSPIEventCube::set_energies(void)
{
    // TODO: Implement method

    // Return
    return;
}


/***********************************************************************//**
 * @brief Set mean event time and ontime of event cube
 *
 * Computes the mean time of the event cube by taking the mean between start
 * and stop time. Computes also the ontime by summing up of all good time
 * intervals.
 ***************************************************************************/
void GSPIEventCube::set_times(void)
{
    // TODO: Implement method

    // Return
    return;
}
