#include "MatrixIterator.h"
#include <vector>

MatrixIterator& MatrixIterator::operator++(int)
{
	beginX += step;
	isDone = false;
	if (beginX > ptr_col.size()) {
		beginX = 0;
		beginY += step;
		rowDone = true;
	}
	if (beginY > ptr_row->size()) {
		beginX = NULL;
		beginY = NULL;
		fullDone = true;
	}
	return *this;
}

double MatrixIterator::CountAvg(std::vector<std::vector<double>>& matrix)
{
	double avg = 0;
	int count = 0;
	for (currentY = beginY; (currentY < beginY + step) && (currentY < ptr_row->size()); currentY++) {
		for (currentX = beginX; (currentX < beginX + step) && (currentX < ptr_col.size()); currentX++) {
			avg += matrix.at(currentY).at(currentX);
			count++;
		}
	}
	isDone = true;
	return avg / count;
}
