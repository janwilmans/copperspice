/***********************************************************************
*
* Copyright (c) 2012-2020 Barbara Geller
* Copyright (c) 2012-2020 Ansel Sermersheim
*
* Copyright (c) 2015 The Qt Company Ltd.
* Copyright (c) 2012-2016 Digia Plc and/or its subsidiary(-ies).
* Copyright (c) 2008-2012 Nokia Corporation and/or its subsidiary(-ies).
*
* This file is part of CopperSpice.
*
* CopperSpice is free software. You can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public License
* version 2.1 as published by the Free Software Foundation.
*
* CopperSpice is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* https://www.gnu.org/licenses/
*
***********************************************************************/

#include <qdatastream.h>
#include <qdatastream_p.h>

#include <qbuffer.h>
#include <qstring.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <qendian.h>

#undef  CHECK_STREAM_PRECOND

#ifndef QT_NO_DEBUG
#define CHECK_STREAM_PRECOND(retVal) \
   if (! dev) { \
      qWarning("QDataStream: No device"); \
      return retVal; \
   }
#else

#define CHECK_STREAM_PRECOND(retVal) \
   if (! dev) { \
      return retVal; \
   }
#endif

#define CHECK_STREAM_WRITE_PRECOND(retVal) \
   CHECK_STREAM_PRECOND(retVal) \
   if (q_status != Ok) \
      return retVal;

// when streaming invalid QVariants,just the type should be written, no "data" after it

QDataStream::QDataStream()
{
   dev       = nullptr;
   owndev    = false;
   byteorder = BigEndian;
   ver       = CS_DefaultStreamVersion;
   noswap    = (QSysInfo::ByteOrder == QSysInfo::BigEndian);
   q_status  = Ok;
}

QDataStream::QDataStream(QIODevice *d)
{
   dev       = d;                                  // set device
   owndev    = false;
   byteorder = BigEndian;                         // default byte order
   ver       = CS_DefaultStreamVersion;
   noswap    = (QSysInfo::ByteOrder == QSysInfo::BigEndian);
   q_status = Ok;
}

QDataStream::QDataStream(QByteArray *a, QIODevice::OpenMode flags)
{
   QBuffer *buf = new QBuffer(a);

   buf->blockSignals(true);
   buf->open(flags);
   dev       = buf;
   owndev    = true;
   byteorder = BigEndian;
   ver       = CS_DefaultStreamVersion;
   noswap    = QSysInfo::ByteOrder == QSysInfo::BigEndian;
   q_status  = Ok;
}

QDataStream::QDataStream(const QByteArray &a)
{
   QBuffer *buf = new QBuffer;

   buf->blockSignals(true);
   buf->setData(a);
   buf->open(QIODevice::ReadOnly);
   dev       = buf;
   owndev    = true;
   byteorder = BigEndian;
   ver       = CS_DefaultStreamVersion;
   noswap    = QSysInfo::ByteOrder == QSysInfo::BigEndian;
   q_status  = Ok;
}

QDataStream::~QDataStream()
{
   if (owndev) {
      delete dev;
   }
}

void QDataStream::setDevice(QIODevice *d)
{
   if (owndev) {
      delete dev;
      owndev = false;
   }

   dev = d;
}

bool QDataStream::atEnd() const
{
   return dev ? dev->atEnd() : true;
}

QDataStream::FloatingPointPrecision QDataStream::floatingPointPrecision() const
{
   return d == nullptr ? QDataStream::DoublePrecision : d->floatingPointPrecision;
}

void QDataStream::setFloatingPointPrecision(QDataStream::FloatingPointPrecision precision)
{
   if (d == nullptr) {
      d.reset(new QDataStreamPrivate());
   }

   d->floatingPointPrecision = precision;
}

QDataStream::Status QDataStream::status() const
{
   return q_status;
}

void QDataStream::resetStatus()
{
   q_status = Ok;
}

void QDataStream::setStatus(Status status)
{
   if (q_status == Ok) {
      q_status = status;
   }
}

void QDataStream::setByteOrder(ByteOrder bo)
{
   byteorder = bo;

   if (QSysInfo::ByteOrder == QSysInfo::BigEndian) {
      noswap = (byteorder == BigEndian);
   } else {
      noswap = (byteorder == LittleEndian);
   }
}

QDataStream &QDataStream::operator>>(qint8 &i)
{
   i = 0;
   CHECK_STREAM_PRECOND(*this)
   char c;

   if (!dev->getChar(&c)) {
      setStatus(ReadPastEnd);
   } else {
      i = qint8(c);
   }

   return *this;
}

QDataStream &QDataStream::operator>>(qint16 &i)
{
   i = 0;
   CHECK_STREAM_PRECOND(*this)

   if (dev->read((char *)&i, 2) != 2) {
      i = 0;
      setStatus(ReadPastEnd);
   } else {
      if (!noswap) {
         i = qbswap(i);
      }
   }

   return *this;
}

QDataStream &QDataStream::operator>>(qint32 &i)
{
   i = 0;

   CHECK_STREAM_PRECOND(*this)

   if (dev->read((char *)&i, 4) != 4) {
      i = 0;
      setStatus(ReadPastEnd);
   } else {
      if (!noswap) {
         i = qbswap(i);
      }
   }

   return *this;
}

QDataStream &QDataStream::operator>>(qint64 &i)
{
   i = qint64(0);

   CHECK_STREAM_PRECOND(*this)

   if (version() < 6) {
      quint32 i1, i2;
      *this >> i2 >> i1;
      i = ((quint64)i1 << 32) + i2;

   } else {
      if (dev->read((char *)&i, 8) != 8) {
         i = qint64(0);
         setStatus(ReadPastEnd);
      } else {
         if (!noswap) {
            i = qbswap(i);
         }
      }
   }

   return *this;
}

QDataStream &QDataStream::operator>>(bool &i)
{
   qint8 v;

   *this >> v;
   i = (v != 0);

   return *this;
}

QDataStream &QDataStream::operator>>(float &f)
{
   if (floatingPointPrecision() == QDataStream::DoublePrecision) {
      double d;
      *this >> d;
      f = d;

      return *this;
   }

   f = 0.0f;
   CHECK_STREAM_PRECOND(*this)

   if (dev->read((char *)&f, 4) != 4) {
      f = 0.0f;
      setStatus(ReadPastEnd);

   } else {
      if (!noswap) {
         union {
            float val1;
            quint32 val2;
         } x;

         x.val2 = qbswap(*reinterpret_cast<quint32 *>(&f));
         f = x.val1;
      }
   }

   return *this;
}

#if defined(Q_DOUBLE_FORMAT)
#define Q_DF(x) Q_DOUBLE_FORMAT[(x)] - '0'
#endif

QDataStream &QDataStream::operator>>(double &f)
{
   if (floatingPointPrecision() == QDataStream::SinglePrecision) {
      float d;
      *this >> d;
      f = d;

      return *this;
   }

   f = 0.0;
   CHECK_STREAM_PRECOND(*this)

#ifndef Q_DOUBLE_FORMAT
   if (dev->read((char *)&f, 8) != 8) {
      f = 0.0;
      setStatus(ReadPastEnd);

   } else {
      if (!noswap) {
         union {
            double val1;
            quint64 val2;
         } x;
         x.val2 = qbswap(*reinterpret_cast<quint64 *>(&f));
         f = x.val1;
      }
   }
#else
   //non-standard floating point format
   union {
      double val1;
      char val2[8];
   } x;
   char *p = x.val2;
   char b[8];
   if (dev->read(b, 8) == 8) {
      if (noswap) {
         *p++ = b[Q_DF(0)];
         *p++ = b[Q_DF(1)];
         *p++ = b[Q_DF(2)];
         *p++ = b[Q_DF(3)];
         *p++ = b[Q_DF(4)];
         *p++ = b[Q_DF(5)];
         *p++ = b[Q_DF(6)];
         *p = b[Q_DF(7)];
      } else {
         *p++ = b[Q_DF(7)];
         *p++ = b[Q_DF(6)];
         *p++ = b[Q_DF(5)];
         *p++ = b[Q_DF(4)];
         *p++ = b[Q_DF(3)];
         *p++ = b[Q_DF(2)];
         *p++ = b[Q_DF(1)];
         *p = b[Q_DF(0)];
      }
      f = x.val1;
   } else {
      setStatus(ReadPastEnd);
   }

#endif
   return *this;
}

QDataStream &QDataStream::operator>>(long &i)
{
   qint64 tmp;

   *this >> tmp;
   i = tmp;

   return *this;
}

QDataStream &QDataStream::operator>>(unsigned long &i)
{
   quint64 tmp;

   *this >> tmp;
   i = tmp;

   return *this;
}

QDataStream &QDataStream::operator>>(char *&s)
{
   uint len = 0;
   return readBytes(s, len);
}

QDataStream &QDataStream::readBytes(char *&s, uint &l)
{
   s = nullptr;
   l = 0;
   CHECK_STREAM_PRECOND(*this)

   quint32 len;
   *this >> len;
   if (len == 0) {
      return *this;
   }

   const quint32 Step = 1024 * 1024;
   quint32 allocated = 0;
   char *prevBuf = nullptr;
   char *curBuf  = nullptr;

   do {
      int blockSize = qMin(Step, len - allocated);
      prevBuf = curBuf;
      curBuf  = new char[allocated + blockSize + 1];

      if (prevBuf) {
         memcpy(curBuf, prevBuf, allocated);
         delete [] prevBuf;
      }

      if (dev->read(curBuf + allocated, blockSize) != blockSize) {
         delete [] curBuf;
         setStatus(ReadPastEnd);
         return *this;
      }

      allocated += blockSize;

   } while (allocated < len);

   s      = curBuf;
   s[len] = '\0';
   l      = (uint)len;

   return *this;
}

int QDataStream::readRawData(char *s, int len)
{
   CHECK_STREAM_PRECOND(-1)
   return dev->read(s, len);
}

QDataStream &QDataStream::operator<<(qint8 i)
{
   CHECK_STREAM_WRITE_PRECOND(*this)

   if (! dev->putChar(i)) {
      q_status = WriteFailed;
   }

   return *this;
}

QDataStream &QDataStream::operator<<(qint16 i)
{
   CHECK_STREAM_WRITE_PRECOND(*this)

   if (! noswap) {
      i = qbswap(i);
   }

   if (dev->write((char *)&i, sizeof(qint16)) != sizeof(qint16)) {
      q_status = WriteFailed;
   }

   return *this;
}

QDataStream &QDataStream::operator<<(qint32 i)
{
   CHECK_STREAM_WRITE_PRECOND(*this)

   if (! noswap) {
      i = qbswap(i);
   }

   if (dev->write((char *)&i, sizeof(qint32)) != sizeof(qint32)) {
      q_status = WriteFailed;
   }

   return *this;
}

QDataStream &QDataStream::operator<<(qint64 i)
{
   CHECK_STREAM_WRITE_PRECOND(*this)

   if (version() < 6) {
      quint32 i1 = i & 0xffffffff;
      quint32 i2 = i >> 32;
      *this << i2 << i1;

   } else {
      if (!noswap) {
         i = qbswap(i);
      }

      if (dev->write((char *)&i, sizeof(qint64)) != sizeof(qint64)) {
         q_status = WriteFailed;
      }
   }

   return *this;
}

QDataStream &QDataStream::operator<<(bool i)
{
   CHECK_STREAM_WRITE_PRECOND(*this)

   if (! dev->putChar(qint8(i))) {
      q_status = WriteFailed;
   }

   return *this;
}

QDataStream &QDataStream::operator<<(float f)
{
   if (floatingPointPrecision() == QDataStream::DoublePrecision) {
      *this << double(f);
      return *this;
   }

   CHECK_STREAM_WRITE_PRECOND(*this)
   float g = f;                                // fixes float-on-stack problem
   if (!noswap) {
      union {
         float val1;
         quint32 val2;
      } x;
      x.val1 = g;
      x.val2 = qbswap(x.val2);

      if (dev->write((char *)&x.val2, sizeof(float)) != sizeof(float)) {
         q_status = WriteFailed;
      }
      return *this;
   }

   if (dev->write((char *)&g, sizeof(float)) != sizeof(float)) {
      q_status = WriteFailed;
   }

   return *this;
}

QDataStream &QDataStream::operator<<(double f)
{
   if (floatingPointPrecision() == QDataStream::SinglePrecision) {
      *this << float(f);
      return *this;
   }

   CHECK_STREAM_WRITE_PRECOND(*this)
#ifndef Q_DOUBLE_FORMAT
   if (noswap) {
      if (dev->write((char *)&f, sizeof(double)) != sizeof(double)) {
         q_status = WriteFailed;
      }
   } else {
      union {
         double val1;
         quint64 val2;
      } x;
      x.val1 = f;
      x.val2 = qbswap(x.val2);
      if (dev->write((char *)&x.val2, sizeof(double)) != sizeof(double)) {
         q_status = WriteFailed;
      }
   }
#else
   union {
      double val1;
      char val2[8];
   } x;
   x.val1 = f;
   char *p = x.val2;
   char b[8];
   if (noswap) {
      b[Q_DF(0)] = *p++;
      b[Q_DF(1)] = *p++;
      b[Q_DF(2)] = *p++;
      b[Q_DF(3)] = *p++;
      b[Q_DF(4)] = *p++;
      b[Q_DF(5)] = *p++;
      b[Q_DF(6)] = *p++;
      b[Q_DF(7)] = *p;
   } else {
      b[Q_DF(7)] = *p++;
      b[Q_DF(6)] = *p++;
      b[Q_DF(5)] = *p++;
      b[Q_DF(4)] = *p++;
      b[Q_DF(3)] = *p++;
      b[Q_DF(2)] = *p++;
      b[Q_DF(1)] = *p++;
      b[Q_DF(0)] = *p;
   }
   if (dev->write(b, 8) != 8) {
      q_status = WriteFailed;
   }

#endif
   return *this;
}

QDataStream &QDataStream::operator<<(long i)
{
   *this << static_cast<qint64>(i);
   return *this;
}

QDataStream &QDataStream::operator<<(unsigned long i)
{
   *this << static_cast<quint64>(i);
   return *this;
}

QDataStream &QDataStream::operator<<(const char *s)
{
   if (!s) {
      *this << (quint32)0;
      return *this;
   }

   uint len = qstrlen(s) + 1;                    // also write null terminator
   *this << (quint32)len;                        // write length specifier
   writeRawData(s, len);

   return *this;
}

QDataStream &QDataStream::writeBytes(const char *s, uint len)
{
   CHECK_STREAM_WRITE_PRECOND(*this)
   *this << (quint32)len;                        // write length specifier

   if (len) {
      writeRawData(s, len);
   }

   return *this;
}

int QDataStream::writeRawData(const char *s, int len)
{
   CHECK_STREAM_WRITE_PRECOND(-1)
   int ret = dev->write(s, len);

   if (ret != len) {
      q_status = WriteFailed;
   }

   return ret;
}

int QDataStream::skipRawData(int len)
{
   CHECK_STREAM_PRECOND(-1)

   if (dev->isSequential()) {
      char buf[4096];
      int sumRead = 0;

      while (len > 0) {
         int blockSize = qMin(len, (int)sizeof(buf));
         int n = dev->read(buf, blockSize);

         if (n == -1) {
            return -1;
         }

         if (n == 0) {
            return sumRead;
         }

         sumRead += n;
         len -= blockSize;
      }

      return sumRead;

   } else {
      qint64 pos  = dev->pos();
      qint64 size = dev->size();

      if (pos + len > size) {
         len = size - pos;
      }

      if (!dev->seek(pos + len)) {
         return -1;
      }

      return len;
   }
}
