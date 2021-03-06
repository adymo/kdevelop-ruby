/*
* This file is part of KDevelop
*
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
#ifndef RUBY_PARSER_H
#define RUBY_PARSER_H

#include <QString>
#include <QRegExp>

#include "rubyast.h"

namespace Ruby {

class KDEVRUBYPARSER_EXPORT Parser {
public:
    Parser();
    ProgramAST *parse(const QString &contents);

private:
    QRegExp classre;
    QRegExp methodre;
    QRegExp methodargsre;
    QRegExp accessre;
    QRegExp attr_accessorre;
    QRegExp symbolre;
    QRegExp line_contre;
    QRegExp slot_signalre;
    QRegExp memberre;
    QRegExp begin_commentre;
    QRegExp end_commentre;
    QRegExp variablere;
    QRegExp endre;
};

}

#endif
