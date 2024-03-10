#pragma once

#include "MapBuilder.cpp"


namespace RawMapBuilder {

	class RawMapBuilder : public MapBuilder {

	public:

		virtual void buildRows(int rows);

		virtual void buildCols(int cols);

		virtual void buildEndCell();

		virtual void buildGrid();

		virtual void buildEmpty(int row, int col);

		virtual void buildWall(int row, int col);

		virtual void buildSpecial(int row, int col);

	};

}