#include "Table.h"

Table::Table( int nr ): m_Nr(nr )
{
}

int Table::GetNumber( ) const
{
	return m_Nr;
}

std::ostream& operator<<( std::ostream& out, const Table& table )
{
	out << "Table " << table.m_Nr;
	return out;
}