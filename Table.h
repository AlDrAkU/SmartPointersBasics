#pragma once
#include <iostream>
class Table
{
public:
	Table(int nr );
	int GetNumber( ) const;
	friend std::ostream& operator<<( std::ostream& out, const Table& table );
private:
	int m_Nr;
};

