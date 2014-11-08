/***********************************************************************
*
* Copyright (c) 2012-2014 Barbara Geller
* Copyright (c) 2012-2014 Ansel Sermersheim
* Copyright (c) 2012-2014 Digia Plc and/or its subsidiary(-ies).
* Copyright (c) 2008-2012 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
*
* This file is part of CopperSpice.
*
* CopperSpice is free software: you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public License
* version 2.1 as published by the Free Software Foundation.
*
* CopperSpice is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with CopperSpice.  If not, see
* <http://www.gnu.org/licenses/>.
*
***********************************************************************/

#include <qfsfileengine_iterator_p.h>
#include <qfileinfo_p.h>
#include <qvariant.h>

#ifndef QT_NO_FSFILEENGINE
#ifndef QT_NO_FILESYSTEMITERATOR

QT_BEGIN_NAMESPACE

QFSFileEngineIterator::QFSFileEngineIterator(QDir::Filters filters, const QStringList &filterNames)
   : QAbstractFileEngineIterator(filters, filterNames)
   , done(false)
{
}

QFSFileEngineIterator::~QFSFileEngineIterator()
{
}

bool QFSFileEngineIterator::hasNext() const
{
   if (!done && !nativeIterator) {
      nativeIterator.reset(new QFileSystemIterator(QFileSystemEntry(path()), filters(), nameFilters()));
      advance();
   }

   return !done;
}

QString QFSFileEngineIterator::next()
{
   if (!hasNext()) {
      return QString();
   }

   advance();
   return currentFilePath();
}

void QFSFileEngineIterator::advance() const
{
   currentInfo = nextInfo;

   QFileSystemEntry entry;
   QFileSystemMetaData data;
   if (nativeIterator->advance(entry, data)) {
      nextInfo = QFileInfo(new QFileInfoPrivate(entry, data));
   } else {
      done = true;
      nativeIterator.reset();
   }
}

QString QFSFileEngineIterator::currentFileName() const
{
   return currentInfo.fileName();
}

QFileInfo QFSFileEngineIterator::currentFileInfo() const
{
   return currentInfo;
}

QT_END_NAMESPACE

#endif // QT_NO_FILESYSTEMITERATOR
#endif // QT_NO_FSFILEENGINE
