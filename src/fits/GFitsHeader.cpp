/***************************************************************************
 *               GFitsHeader.cpp  - FITS header handling class             *
 * ----------------------------------------------------------------------- *
 *  copyright            : (C) 2008 by Jurgen Knodlseder                   *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 * ----------------------------------------------------------------------- *
 ***************************************************************************/

/* __ Includes ___________________________________________________________ */
#include <iostream>
#include "GException.hpp"
#include "GFitsHeader.hpp"

/* __ Namespaces _________________________________________________________ */

/* __ Method name definitions ____________________________________________ */
#define G_OPEN "GFitsHeader::open(int)"

/* __ Macros _____________________________________________________________ */

/* __ Coding definitions _________________________________________________ */

/* __ Debug definitions __________________________________________________ */



/*==========================================================================
 =                                                                         =
 =                    GFitsHeader constructors/destructors                 =
 =                                                                         =
 ==========================================================================*/

/***************************************************************************
 *                                Constructor                              *
 * ----------------------------------------------------------------------- *
 ***************************************************************************/
GFitsHeader::GFitsHeader()
{
    // Initialise class members for clean destruction
    init_members();

    // Return
    return;
}


/***************************************************************************
 *                              Copy constructor                           *
 * ----------------------------------------------------------------------- *
 ***************************************************************************/
GFitsHeader::GFitsHeader(const GFitsHeader& header)
{
    // Initialise class members for clean destruction
    init_members();

    // Copy members
    copy_members(header);

    // Return
    return;
}


/***************************************************************************
 *                               Destructor                                *
 * ----------------------------------------------------------------------- *
 ***************************************************************************/
GFitsHeader::~GFitsHeader()
{
    // Free members
    free_members();

    // Return
    return;
}


/*==========================================================================
 =                                                                         =
 =                          GFitsHeader operators                          =
 =                                                                         =
 ==========================================================================*/

/***************************************************************************
 *                            Assignment operator                          *
 * ----------------------------------------------------------------------- *
 ***************************************************************************/
GFitsHeader& GFitsHeader::operator= (const GFitsHeader& header)
{
    // Execute only if object is not identical
    if (this != &header) {

        // Free members
        free_members();

        // Initialise private members for clean destruction
        init_members();

        // Copy members
        copy_members(header);

    } // endif: object was not identical

    // Return this object
    return *this;
}


/*==========================================================================
 =                                                                         =
 =                        GFitsHeader public methods                       =
 =                                                                         =
 ==========================================================================*/

/***************************************************************************
 *                                Open Header                              *
 * ----------------------------------------------------------------------- *
 ***************************************************************************/
void GFitsHeader::open(__fitsfile* fptr)
{
    // Move to HDU
    int status = 0;
    status     = __ffmahd(fptr, (fptr->HDUposition)+1, NULL, &status);
    if (status != 0)
        throw GException::fits_error(G_OPEN, status);

    // Determine number of cards in header
    status = __ffghsp(fptr, &m_num_cards, NULL, &status);
    if (status != 0)
        throw GException::fits_error(G_OPEN, status);

    // Drop any old cards
    if (m_card != NULL) delete [] m_card;

    // Allocate memory for new cards
    m_card = new GFitsHeaderCard[m_num_cards];

    // Read all cards
    for (int i = 0; i < m_num_cards; ++i)
        m_card[i].read(fptr, i+1);

    // Return
    return;
}


/***************************************************************************
 *                              Close Header                               *
 * ----------------------------------------------------------------------- *
 ***************************************************************************/
void GFitsHeader::close(void)
{
    // Free members
    free_members();

    // Initialise members
    init_members();

    // Return
    return;
}


/***********************************************************************//**
 * @brief Update card in header                                            
 * This method updates one header card. Updating means replacing any       
 * existing card with the specified one or appending a new card to the     
 * list of existing cards.                                                 
 ***************************************************************************/
void GFitsHeader::update(const GFitsHeaderCard& card)
{
    // If card exists then update existing values
    GFitsHeaderCard* ptr = this->card(card.keyname());
    if (ptr != NULL)
        *ptr = card;

    // ... otherwise append a new card
    else {
    
        // Create memory to hold cards
        GFitsHeaderCard* tmp = new GFitsHeaderCard[m_num_cards+1];
        if (tmp != NULL) {
        
            // Copy over existing cards and remove old ones
            if (m_card != NULL) {
                for (int i = 0; i < m_num_cards; ++i)
                    tmp[i] = m_card[i];
                delete [] m_card;
            }

            // Connect the new memory to the card pointer
            m_card = tmp;

            // Append new card to list
            m_card[m_num_cards] = card;

        } // endif: new memory was valid
    } // endif: card appending was required

    // Return
    return;
}


/***************************************************************************
 *                 Get specified header card value as string               *
 * ----------------------------------------------------------------------- *
 ***************************************************************************/
std::string GFitsHeader::string(const std::string& keyname)
{
    // Get card pointer
    GFitsHeaderCard* ptr = GFitsHeader::card(keyname);

    // Get string value
    std::string value = (ptr != NULL) ? ptr->string() : "";

    // Return string
    return value;
}


/***************************************************************************
 *                 Get specified header card value as string               *
 * ----------------------------------------------------------------------- *
 ***************************************************************************/
std::string GFitsHeader::string(const int& cardno)
{
    // Get card pointer
    GFitsHeaderCard* ptr = GFitsHeader::card(cardno);

    // Get string value
    std::string value = (ptr != NULL) ? ptr->string() : "";

    // Return string
    return value;
}


/***************************************************************************
 *                 Get specified header card value as double               *
 * ----------------------------------------------------------------------- *
 ***************************************************************************/
double GFitsHeader::real(const std::string& keyname)
{
    // Get card pointer
    GFitsHeaderCard* ptr = GFitsHeader::card(keyname);

    // Get string value
    double value = (ptr != NULL) ? ptr->real() : 0.0;

    // Return double
    return value;
}


/***************************************************************************
 *                 Get specified header card value as double               *
 * ----------------------------------------------------------------------- *
 ***************************************************************************/
double GFitsHeader::real(const int& cardno)
{
    // Get card pointer
    GFitsHeaderCard* ptr = GFitsHeader::card(cardno);

    // Get string value
    double value = (ptr != NULL) ? ptr->real() : 0.0;

    // Return double
    return value;
}


/***************************************************************************
 *                  Get specified header card value as int                 *
 * ----------------------------------------------------------------------- *
 ***************************************************************************/
int GFitsHeader::integer(const std::string& keyname)
{
    // Get card pointer
    GFitsHeaderCard* ptr = GFitsHeader::card(keyname);

    // Get string value
    int value = (ptr != NULL) ? ptr->integer() : 0;

    // Return double
    return value;
}


/***************************************************************************
 *                  Get specified header card value as int                 *
 * ----------------------------------------------------------------------- *
 ***************************************************************************/
int GFitsHeader::integer(const int& cardno)
{
    // Get card pointer
    GFitsHeaderCard* ptr = GFitsHeader::card(cardno);

    // Get string value
    int value = (ptr != NULL) ? ptr->integer() : 0;

    // Return double
    return value;
}


/*==========================================================================
 =                                                                         =
 =                         GFitsHeader private methods                     =
 =                                                                         =
 ==========================================================================*/

/***************************************************************************
 *                         Initialise class members                        *
 * ----------------------------------------------------------------------- *
 ***************************************************************************/
void GFitsHeader::init_members(void)
{
    // Initialise members
    m_num_cards = 0;
    m_card      = NULL;

    // Return
    return;
}


/***************************************************************************
 *                            Copy class members                           *
 * ----------------------------------------------------------------------- *
 ***************************************************************************/
void GFitsHeader::copy_members(const GFitsHeader& header)
{
    // Copy attributes

    // Copy cards
    if (header.m_card != NULL && header.m_num_cards > 0) {
        m_num_cards = header.m_num_cards;
        m_card      = new GFitsHeaderCard[m_num_cards];
        for (int i = 0; i < m_num_cards; ++i)
            m_card[i] = header.m_card[i];
    }

    // Return
    return;
}


/***************************************************************************
 *                           Delete class members                          *
 * ----------------------------------------------------------------------- *
 ***************************************************************************/
void GFitsHeader::free_members(void)
{
    // Free memory
    if (m_card != NULL) delete [] m_card;

    // Properly mark as free
    m_card = NULL;

    // Return
    return;
}


/***************************************************************************
 *                             Get card pointer                            *
 * ----------------------------------------------------------------------- *
 ***************************************************************************/
GFitsHeaderCard* GFitsHeader::card_ptr(const std::string keyname)
{

    // Set card pointer to NULL (default)
    GFitsHeaderCard* ptr = NULL;

    // Search keyname in list
    for (int i = 0; i < m_num_cards; ++i) {
        if (m_card[i].keyname() == keyname) {
            ptr = &(m_card[i]);
            break;
        }
    }

    // Return pointer
    return ptr;
}


/*==========================================================================
 =                                                                         =
 =                            GFitsHeader friends                          =
 =                                                                         =
 ==========================================================================*/

/***************************************************************************
 *                             Output operator                             *
 * ----------------------------------------------------------------------- *
 ***************************************************************************/
ostream& operator<< (ostream& os, const GFitsHeader& header)
{
    // Put header in stream
    os << "=== GFitsHeader ===" << endl;
    os << " Number of cards ...........: " << header.m_num_cards << endl;
    for (int i = 0; i < header.m_num_cards; ++i)
        os << " " << header.m_card[i];

    // Return output stream
    return os;
}


/*==========================================================================
 =                                                                         =
 =                    Other functions used by GFitsHeader                  =
 =                                                                         =
 ==========================================================================*/
