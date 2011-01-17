/***************************************************************************
 *            GXmlDocument.i - XML document node class definition          *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2010-2011 by Jurgen Knodlseder                           *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
/**
 * @file GXmlDocument.i
 * @brief GXmlDocument class python bindings
 * @author J. Knodlseder
 */
%{
/* Put headers and other declarations here that are needed for compilation */
#include "GXmlDocument.hpp"
#include "GTools.hpp"
%}


/***********************************************************************//**
 * @class GXmlDocument
 *
 * @brief XML document node class interface defintion.
 *
 * This class implements the root node of an XML document. It contains the
 * three special attributes 'version', 'encoding', and 'standalone'.
 ***************************************************************************/
class GXmlDocument : public GXmlNode {

public:
    // Constructors and destructors
    GXmlDocument(void);
    GXmlDocument(const GXmlDocument& node);
    ~GXmlDocument(void);

    // Implemented virtual methods
    void     clear(void);
    void     write(FILE* fptr, int indent = 0) const;
    //void     print(std::ostream& os, int indent = 0) const;
    NodeType type(void) const { return NT_DOCUMENT; }

    // Methods
    std::string version(void) const { return m_version.value(); }
    std::string encoding(void) const { return m_encoding.value(); }
    std::string standalone(void) const { return m_standalone.value(); }
    void        version(const std::string& version) { m_version.value(version); }
    void        encoding(const std::string& encoding) { m_encoding.value(encoding); }
    void        standalone(const std::string& standalone) { m_standalone.value(standalone); }
};


/***********************************************************************//**
 * @brief GXmlDocument class extension
 ***************************************************************************/
%extend GXmlDocument {
//    char *__str__() {
//        return tochar(self->print());
//    }
};


/***********************************************************************//**
 * @brief GXmlDocument type casts
 ***************************************************************************/
%inline %{
    GXmlDocument* cast_GXmlDocument(GXmlNode* node) {
        if (node->type() != GXmlNode::NT_DOCUMENT)
            throw GException::xml_bad_node_type("cast_GXmlDocument(GXmlNode*)",
                                                "",
                                                "Expecting GXmlDocument node.");
        return dynamic_cast<GXmlDocument*>(node);
    }
%};
