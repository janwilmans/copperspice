/***********************************************************************
*
* Copyright (c) 2012-2021 Barbara Geller
* Copyright (c) 2012-2021 Ansel Sermersheim
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

#include <qsharedpointer.h>

#include <cs_catch2.h>

TEST_CASE("QSharedPointer copy", "[qsharedpointer]")
{
   QSharedPointer<int> ptr1;
   int *rawPointer = nullptr;

   {
      QSharedPointer<int> ptr2 = QMakeShared<int>();
      rawPointer = ptr2.data();
      ptr1 = ptr2;
   }

   REQUIRE(rawPointer == ptr1.data());
}

TEST_CASE("QSharedPointer custom_deleter", "[qsharedpointer]")
{
   bool deleterExecuted = false;

   {
      QSharedPointer<int> ptr(new int, [&deleterExecuted] (int *obj)
         {
            deleterExecuted = true;
            delete obj;
         }
      );

      REQUIRE(deleterExecuted == false);
   }

   REQUIRE(deleterExecuted == true);
}

TEST_CASE("QSharedPointer empty", "[qsharedpointer]")
{
   QSharedPointer<int> ptr;

   REQUIRE(ptr == nullptr);
   REQUIRE(ptr.isNull() == true);
}

TEST_CASE("QSharedPointer move_a", "[qsharedpointer]")
{
   QSharedPointer<int> ptr1 = QMakeShared<int>();
   QSharedPointer<int> ptr2(std::move(ptr1));

   REQUIRE(ptr2.isNull() == false);
}

TEST_CASE("QSharedPointer move_b", "[qsharedpointer]")
{
   QSharedPointer<int> ptr1 = QMakeShared<int>();
   QSharedPointer<int> ptr2 = QMakeShared<int>();

   int *rawPointer = ptr2.data();

   ptr1 = std::move(ptr2);

   REQUIRE(ptr1.data() == rawPointer);
}

TEST_CASE("QSharedPointer reset", "[qsharedpointer]")
{
   QSharedPointer<int> ptr = QMakeShared<int>();
   ptr.reset();

   REQUIRE(ptr == nullptr);
   REQUIRE(ptr.isNull() == true);
}
