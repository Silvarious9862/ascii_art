#pragma once 
#include <iostream>
#include <vector>

class MatrixIterator
{
public:
	MatrixIterator(std::vector<std::vector<double>>& matrix, int quality) : 
		ptr_row(&matrix), ptr_col(*(ptr_row->begin())), beginX(0), beginY(0), step(11 - quality) {}

	MatrixIterator& operator++(int);

	int GetX() const { return currentX; }
	int GetY() const { return currentY; }
	int GetStep() const { return step; }

	bool CheckIsDone() const { return isDone; }
	bool CheckRowDone() const { return rowDone; }
	bool CheckFullDone() const { return fullDone; }

	void UnsetRowDone() { rowDone = false; }

	double CountAvg(std::vector<std::vector<double>>& matrix);


private:
	std::vector<std::vector<double>>* ptr_row;
	std::vector<double> ptr_col;
	int beginX{};
	int beginY{};
	int currentX{};
	int currentY{};
	int step{};
	bool fullDone = false;
	bool isDone = false;
	bool rowDone = false;
};