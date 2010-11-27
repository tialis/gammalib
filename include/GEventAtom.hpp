/***************************************************************************
 *              GEventAtom.hpp  -  Event atom abstract base class          *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2009-2010 by Jurgen Knodlseder                           *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
/**
 * @file GEventAtom.hpp
 * @brief GEventAtom abstract base class interface definition.
 * @author J. Knodlseder
 */

#ifndef GEVENTATOM_HPP
#define GEVENTATOM_HPP

/* __ Includes ___________________________________________________________ */
#include "GEvent.hpp"
#include "GInstDir.hpp"
#include "GEnergy.hpp"
#include "GTime.hpp"


/***********************************************************************//**
 * @class GEventAtom
 *
 * @brief Abstract interface for the event atom class.
 *
 * An event atom is a single event occuring in an instrument. Event atoms
 * are used for unbinned analysis.
 *
 * Each event has 3 attributes: energy, instrument direction and time.
 * These attributes can be accessed and changed through the energy(),
 * dir(), and time() methods.
 *
 * The counts() and error() methods return the number of counts and the
 * error in this number for each event. For event atoms the number of
 * counts is 1 and the error is 0.
 *
 * The size() method returns the size of an event bin ,which is the
 * quantity that has to be multiplied by the probability for an event to
 * occur to predict the number of events in a bin. For event atoms this
 * quantity is by definition 1.
 *
 * The GEventAtom class does not hold any data members. Data members are
 * stored in the derived classes.
 ***************************************************************************/
class GEventAtom : public GEvent {

    // Friend classes
    friend class GEvents;

public:
    // Constructors and destructors
    GEventAtom(void);
    GEventAtom(const GEventAtom& atom);
    virtual ~GEventAtom(void);

    // Operators
    virtual GEventAtom& operator= (const GEventAtom& atom);

    // Event access methods
    virtual const GInstDir& dir(void) const = 0;
    virtual const GEnergy&  energy(void) const = 0;
    virtual const GTime&    time(void) const = 0;
    double                  counts(void) const { return 1.0; }
    double                  error(void) const { return 0.0; }

    // Other methods
    virtual void        clear(void) = 0;
    virtual double      size(void) const { return 1.0; }
    virtual GEventAtom* clone(void) const = 0;
    virtual bool        isatom(void) const { return true; }
    virtual bool        isbin(void) const { return false; }

protected:
    // Protected methods
    void init_members(void);
    void copy_members(const GEventAtom& atom);
    void free_members(void);
};

#endif /* GEVENTATOM_HPP */
