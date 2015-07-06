//----------------------------
// File:		cell.cpp
// Created:		2012/07/06
// Copyright:	Daniel Schenker
//----------------------------

#include "stdafx.h"
#include "cell.h"

cCell::cCell()
{
}

cCell::cCell(char _row, int _column, bool _isOccupied)
:	row(_row)
,	column(_column)
,	isOccupied(_isOccupied)
{
}

cCell::~cCell()
{
}