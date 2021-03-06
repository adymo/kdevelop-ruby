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
#include "contextbuilder.h"

#include <language/duchain/duchain.h>
#include <language/duchain/topducontext.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/declaration.h>
#include <language/duchain/classdeclaration.h>

#include <interfaces/icore.h>
#include <interfaces/ilanguagecontroller.h>
#include <interfaces/icompletionsettings.h>

#include <klocalizedstring.h>

#include "parser/rubyast.h"
#include "editorintegrator.h"

namespace Ruby
{

ContextBuilder::ContextBuilder() : m_reportErrors(true)
{
}

ContextBuilder::~ContextBuilder()
{
}

KDevelop::ReferencedTopDUContext ContextBuilder::build(const KDevelop::IndexedString& url, AST* node,
    KDevelop::ReferencedTopDUContext updateContext)
{
    if ( KDevelop::ICore::self() ) {
        m_reportErrors = KDevelop::ICore::self()->languageController()->completionSettings()->highlightSemanticProblems();
    }
    return ContextBuilderBase::build(url, node, updateContext);
}

void ContextBuilder::setEditor(EditorIntegrator* editor)
{
    m_editor = editor;
}

void ContextBuilder::startVisiting(AST* node)
{
    ProgramAST *ast = static_cast<ProgramAST*>(node);
    visitProgram(ast);
}

void ContextBuilder::visitClass(ClassAST* ast)
{
    openContext(ast, editorFindRange(ast, ast), KDevelop::DUContext::Class, ast->name);
    Visitor::visitClass(ast);
    closeContext();
}

void ContextBuilder::visitFunction(FunctionAST* ast)
{
    openContext(ast, editorFindRange(ast, ast), KDevelop::DUContext::Function, ast->name);
    Visitor::visitFunction(ast);
    closeContext();
}

void ContextBuilder::visitFunctionArgument(FunctionArgumentAST* ast)
{
    Visitor::visitFunctionArgument(ast);
}

KDevelop::TopDUContext* ContextBuilder::newTopContext(const KDevelop::RangeInRevision& range, KDevelop::ParsingEnvironmentFile* file)
{
    if (!file) {
        file = new KDevelop::ParsingEnvironmentFile(KDevelop::IndexedString(m_editor->url()));
        file->setLanguage(KDevelop::IndexedString("Ruby"));
    }
    return new KDevelop::TopDUContext(KDevelop::IndexedString(m_editor->url()), range, file);
}

void ContextBuilder::setContextOnNode(AST* /*node*/, KDevelop::DUContext* /*ctx*/)
{
}

KDevelop::DUContext* ContextBuilder::contextFromNode(AST* /*node*/)
{
    return 0;
}

EditorIntegrator* ContextBuilder::editor() const
{
    return m_editor;
}

KDevelop::RangeInRevision ContextBuilder::editorFindRange(AST* fromRange, AST* toRange)
{
    return m_editor->findRange(fromRange, toRange);
}

KDevelop::CursorInRevision ContextBuilder::startPos(AST* node)
{
    return m_editor->findPosition(node, EditorIntegrator::FrontEdge);
}

KDevelop::QualifiedIdentifier ContextBuilder::identifierForNode(NameAST* id)
{
    if (!id)
        return KDevelop::QualifiedIdentifier();
    return KDevelop::QualifiedIdentifier(id->name);
}

}
