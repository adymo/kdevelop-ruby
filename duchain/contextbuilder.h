/*
* This file is part of KDevelop
*
* Copyright 2010 Niko Sams <niko.sams@gmail.com>
* Copyright 2010 Alexander Dymo <adymo@kdevelop.org>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU Library General Public License as
* published by the Free Software Foundation; either version 2 of the
* License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public
* License along with this program; if not, write to the
* Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/
#ifndef CONTEXTBUILDER_H
#define CONTEXTBUILDER_H

#include <language/duchain/builders/abstractcontextbuilder.h>

#include "parser/visitor.h"
#include "duchainexport.h"

namespace Ruby
{
class AST;
class ProgramAST;
class NameAST;
class ClassAST;
class EditorIntegrator;

typedef KDevelop::AbstractContextBuilder<AST, NameAST> ContextBuilderBase;

class KDEVRUBYDUCHAIN_EXPORT ContextBuilder: public ContextBuilderBase, Visitor {
public:
    ContextBuilder();
    virtual ~ContextBuilder();

    void setEditor(EditorIntegrator* editor);
    virtual KDevelop::ReferencedTopDUContext build(const KDevelop::IndexedString& url, AST* node,
        KDevelop::ReferencedTopDUContext updateContext = KDevelop::ReferencedTopDUContext());

protected:
    EditorIntegrator* editor() const;

    virtual KDevelop::TopDUContext* newTopContext(const KDevelop::RangeInRevision& range, KDevelop::ParsingEnvironmentFile* file = 0);

    virtual void startVisiting(AST* node);
    virtual void setContextOnNode(AST* node, KDevelop::DUContext* ctx);
    virtual KDevelop::DUContext* contextFromNode(AST* node);

    virtual KDevelop::RangeInRevision editorFindRange(AST* fromRange, AST* toRange);
    /// Find Cursor for start of a node, useful to limit findLocalDeclarations() searches.
    KDevelop::CursorInRevision startPos(AST* node);

    virtual KDevelop::QualifiedIdentifier identifierForNode(NameAST* id);

    virtual void visitClass(ClassAST* ast);
    virtual void visitFunction(FunctionAST* ast);
    virtual void visitFunctionArgument(FunctionArgumentAST* ast);

    bool m_reportErrors;
    EditorIntegrator* m_editor;
};

}

#endif
