/***************************************************************************
 *              test_GXml.hpp  -   test xml class                          *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2012 by Jean-Baptiste Cayrou                             *
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

#ifndef TEST_GXML_HPP
#define TEST_GXML_HPP

/* __ Includes ___________________________________________________________ */
#include "GammaLib.hpp"
#include <iostream>                           // cout, cerr

class TestGXml : public GTestSuite
{
    public:
        // Constructors and destructors
        TestGXml(void) : GTestSuite(){ return; }
        virtual ~TestGXml(void){ return; }

        // Methods
        virtual void set(void);
        void test_GXml_attributes(void);
        void test_GXml_elements();
        void test_GXml_construct();
        void test_GXml_load();
        void test_GXml_access();

    // Private members
    private:
        std::string m_xml_file;
};

#endif /* TEST_GXML_HPP */
