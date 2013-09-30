
/*
 Name: Nhan Tran
 Date: 7/5/12
 Class: CST 136
 Assignment: 1
 File Name: flipit.cpp
 Implementation file for flipit.h 
*/

#include "flipit.h"
#include <iostream>


FlipIt::FlipIt(int nRows, int nCols, int gameNum, int complexity, Pattern pattern, bool wrap) :
		m_rows(nRows),
		m_cols(nCols),
		m_gameNum(gameNum),
		m_complexity(complexity),
		m_pattern(pattern),
		m_wrap(wrap),
		m_grid(nRows, nCols)
{
	srand(gameNum);		//gameNum is used as the seed for the random function, this allows for repeatablity of game setups 

	//set starting grid state
	for (int i = 0; i < complexity; i++)
	{
		int row, col;
		
		row = rand() % nRows;
		col = rand() % nCols;

		click(row, col);
	}
}

//Name: click()
//Desc: takes in a zero-based row and col value then depending on the pattern toggles surrounding cells using toggle()
void FlipIt::click( int  row, int  col )
{
	switch (m_pattern)
	{	
		case cross_:
			toggle(row, col);		//center
			toggle(row - 1, col);	//top
			toggle(row + 1, col);	//bottom
			toggle(row, col - 1);	//left
			toggle(row, col + 1);	//right
			break;
		case x_:
			toggle(row, col);			//center
			toggle(row - 1, col - 1);	//top left
			toggle(row - 1, col + 1);	//top right
			toggle(row + 1, col - 1);	//bottom left
			toggle(row + 1, col + 1);	//bottom right
			break;
		case square_:
			toggle(row, col);			//center
			toggle(row - 1, col - 1);	//top left
			toggle(row - 1, col);		//top mid
			toggle(row - 1, col + 1);	//top right
			toggle(row, col - 1);		//mid left
			toggle(row, col + 1);		//mid right
			toggle(row + 1, col - 1);	//bottom left
			toggle(row + 1, col);		//bottom mid
			toggle(row + 1, col + 1);	//bottom right
			break;
		case hollowSquare_:
			toggle(row - 1, col - 1);	//top left
			toggle(row - 1, col);		//top mid
			toggle(row - 1, col + 1);	//top right
			toggle(row, col - 1);		//mid left
			toggle(row, col + 1);		//mid right
			toggle(row + 1, col - 1);	//bottom left
			toggle(row + 1, col);		//bottom mid
			toggle(row + 1, col + 1);	//bottom right
			break;
		case corners_:
			toggle(row - 1, col - 1);	//top left
			toggle(row - 1, col + 1);	//top right
			toggle(row + 1, col - 1);	//bottom left
			toggle(row + 1, col + 1);	//bottom right
			break;
		default:
			cout << "Error, invalid pattern input." << endl;	//should never happen
	}

}

FlipIt::Color FlipIt::fetch(int row, int col) const
{
	Color c;

	if (m_grid.fetch(row, col))
		c = solid_;		//if fetch is true then color is solid
	else
		c = clear_;		//if fetch is false then color is clear

	return c;	
}

//Name: toggle()
//Desc: takes in zero-based row and col value and taking the wrap option in account, turns a grid cell to clear or solid
void FlipIt::toggle(int row, int col)
{
	Color	color;

	if(row >= m_rows || row < 0 || col >= m_cols || col < 0)	//if row or col is outside boundary
		if(m_wrap)												//if wrap is true then recalculate row and col with wrapCheck
			wrapCheck(row, col);
		else													//else exit function
			return;

	color = fetch(row, col);
	
	if (color)	//if true(solid) set to false(clear)
		m_grid.clear(row, col);
	else		//else set to true
		m_grid.set(row,col);
}


//Name: wrapCheck()
//Desc: changes invalid row or column values to valid ones
void FlipIt::wrapCheck(int &row, int &col)
{
	if (row >= m_rows)
		row = row - m_rows;
	else if (row < 0)
		row = row + m_rows;
	
	if (col >= m_cols)
		col = col - m_cols;
	else if (col < 0)
		col = col + m_cols;
}


int FlipIt::numRows()  const //return m_rows
{
	return m_rows;
}	
   

int FlipIt::numCols()  const	//return m_cols
{
	return m_cols;
}

bool FlipIt::done() const
{
	for (int r = 0; r < m_rows; r++) //for every row
	{
		for (int c = 0; c < m_cols; c++)	//for every column
		{
			Color cellColor;
			cellColor = fetch(r, c);
			if (cellColor == solid_)
				return false;	//a cell is solid. game not done
		}
	}

	return true;	//all cells are clear since it has made it through the for loop check
}