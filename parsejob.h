/*
* This file is part of KDevelop
*
* Copyright 2008-2010 Alexander Dymo <adymo@kdevelop.org>
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
#ifndef RUBY_SIMPLEPARSEJOB_H
#define RUBY_SIMPLEPARSEJOB_H

#include <kurl.h>
#include <language/backgroundparser/parsejob.h>

class RubyLanguageSupport;

namespace Ruby
{

class Parser;

class SimpleParseJob : public KDevelop::ParseJob
{
    Q_OBJECT

public:
    enum {
        Resheduled = KDevelop::TopDUContext::LastFeature
    };

    SimpleParseJob( const KDevelop::IndexedString &url, RubyLanguageSupport* parent );

    virtual ~SimpleParseJob();

    RubyLanguageSupport* ruby() const;

    bool wasReadFromDisk() const;

protected:
    virtual void run();

private:
    void parse(const QString &c);

    Parser *m_parser;
    bool m_readFromDisk;
};

} // end of namespace ruby

#endif
