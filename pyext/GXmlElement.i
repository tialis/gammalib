/***************************************************************************
 *             GXmlElement.i - XML element node class definition           *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2010 by Jurgen Knodlseder                                *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
/**
 * @file GXmlElement.i
 * @brief GXmlElement class python bindings
 * @author J. Knodlseder
 */
%{
/* Put headers and other declarations here that are needed for compilation */
#include "GXmlElement.hpp"
%}


/***********************************************************************//**
 * @class GXmlElement
 *
 * @brief XML element node class interface defintion.
 *
 * This class implements an XML element with it's associated attributes.
 ***************************************************************************/
class GXmlElement : public GXmlNode {
public:
    // Constructors and destructors
    GXmlElement(void);
    GXmlElement(const GXmlElement& node);
    GXmlElement(const std::string& segment);
    ~GXmlElement(void);

    // Implemented virtual methods
    void     clear(void);
    void     write(FILE* fptr, int indent = 0) const;
    //void     print(std::ostream& os, int indent = 0) const;
    NodeType type(void) const { return NT_ELEMENT; }

    // Methods
    std::string name(void) const { return m_name; }
    std::string attribute(const std::string& name) const;
    GXmlNode*   parent(void) const { return m_parent; }
    void        name(const std::string& name) { m_name=name; }
    void        parent(GXmlNode* node) { m_parent = node; }
    void        attribute(const std::string& name, const std::string& value);
};


/***********************************************************************//**
 * @brief GXmlElement class extension
 ***************************************************************************/
%extend GXmlElement {
//    char *__str__() {
//        static std::string result = self->print();
//        return ((char*)result.c_str());
//    }
};
