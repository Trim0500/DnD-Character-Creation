#include "RawMapBuilder.h"

using RMP = RawMapBuilder::RawMapBuilder;

void RMP::buildRows(int rows) {
	m_map->setRows(rows);
}

void RMP::buildCols(int cols) {
	m_map->setCols(cols);
}

void RMP::buildEndCell() {
	m_map->setEndCell();
}

void RMP::buildGrid() {
	m_map->setGrid();
}

void RMP::buildEmpty(int row, int col) {
	m_map->setEmpty(row, col);
}

void RMP::buildSpecial(int row, int col) {
	m_map->setSpecial(row, col);
}