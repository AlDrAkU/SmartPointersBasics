#include <windows.h>
#include <iostream>
#include <memory>
#include <vector>
#include "Table.h"


void CreateSharedPointers( );
void CreateUniquePointers( );
void CreateWeakPointers( );
void UseSmartPointers( );
void TestRestrictions( );
void TestUniquePointersContainer( );

// Helper functions
std::shared_ptr<Table> CreateSharedTable( int nr );
std::unique_ptr<Table> CreateUniqueTable( int nr );
std::weak_ptr<Table> CreateWeakTable( int nr );

// Memory leak functions
void StartHeapControl( );
void DumpMemoryLeaks( );

int main( )
{
	StartHeapControl( );
	{
		CreateSharedPointers( );
		CreateUniquePointers( );
		CreateWeakPointers( );

		UseSmartPointers( );

		TestUniquePointersContainer( );

		TestRestrictions( );
	}
	DumpMemoryLeaks( );

	std::cout << "Push ENTER to stop the application\n";
	std::cin.get( );
}

void CreateSharedPointers( )
{

	// TODO: Create a shared_ptr using the make_shared function
	std::shared_ptr<Table> sp1{ std::make_shared<Table>(10) };
	// TODO: Create a shared_ptr using the copy constructor
	std::shared_ptr<Table> sp2{sp1 };
	// TODO: Create a shared_ptr using the copy assignment operator
	std::shared_ptr<Table> sp3 = sp2;
	// TODO: Create a shared_ptr using the move constructor (call CreateSharedTable)
	std::shared_ptr<Table>sp4{ CreateSharedTable(1) };
	// TODO: Create a shared_ptr using the move assignment operator (call CreateSharedTable)
	std::shared_ptr<Table>sp5 = CreateSharedTable(2);
}

void CreateUniquePointers( )
{
	// TODO: Create a unique_ptr using the make_unique function
	std::unique_ptr<Table>up0 = std::make_unique<Table>(1);
	// TODO: Create a unique_ptr using the copy constructor
	//std::unique_ptr<Table>up1  {up0};
	// TODO: Create a unique_ptr using the copy assignment
	//std::unique_ptr<Table>up2 = up1;
	

	// TODO: Create a unique_ptr using the move constructor (call CreateUniqueTable)
	std::unique_ptr<Table>up3{ CreateUniqueTable(3) };
	// TODO: Create a unique_ptr using the move assignment (call CreateUniqueTable)
	std::unique_ptr<Table>up4 = CreateUniqueTable(4) ;
}

void CreateWeakPointers( )
{
	std::shared_ptr<Table> psTable1{ std::make_shared<Table>( 1 ) };
	std::shared_ptr<Table> psTable2{ std::make_shared<Table>( 2 ) };

	// TODO: Create a weak_ptr using its constructor: weak_ptr<T>(std::shared_ptr<T>)
	std::weak_ptr<Table>& wp0(std::shared_ptr<Table>psTable1);

	// TODO: Create a weak_ptr assigning a shared_ptr to it
	//std::shared_ptr<Table>sp0{ std::make_shared<Table>(2) };
	std::weak_ptr<Table>wp1{ psTable2};
	// TODO: Create a weak_ptr using the copy constructor
	std::weak_ptr<Table>wp2{ wp1 };
	// TODO: Create a weak_ptr using the copy assignment
	std::weak_ptr<Table>wp3 = wp2;
	// TODO: Create a weak_ptr using the move constructor (call CreateWeakTable)
	std::weak_ptr<Table>wp4{ CreateWeakTable(4) };
	// TODO: Create a weak_ptr using the move assignment (call CreateWeakTable)
	std::weak_ptr<Table>wp5 = CreateWeakTable(5);


}

void UseSmartPointers( )
{
	// Create some smart pointers 
	std::shared_ptr<Table> psTable1{ std::make_shared<Table>( 1 ) };
	std::weak_ptr<Table> pwTable1{ psTable1 };
	std::unique_ptr<Table> puTable1{ std::make_unique<Table>( 1 ) };
	std::unique_ptr<Table> puTable2{ std::make_unique<Table>( 2 ) };
	std::shared_ptr<Table> psTable3{ std::make_shared<Table>( 3 ) };
	std::shared_ptr<Table> psNoTable{};
	std::weak_ptr<Table> pwNoTable{};

	// Access using the -> operator 
	// TODO: Verify which smart pointers have the -> operator
	//       Get the table's number and print it to the console wp doesn't 
	std::cout << "\nAccessing the managed objects using ->:\n";
	std::cout <<"psTable1 : "<<psTable1->GetNumber() << '\n';
	std::cout <<"psTable3 : " << psTable3->GetNumber() << '\n';
	//std::cout <<"pwTable1 : " << pwTable1->GetNumber() << '\n';
	std::cout << "puTable1 : " << puTable1->GetNumber() << '\n';
	std::cout << "puTable2 : " << puTable2->GetNumber() << '\n';
	if (!psNoTable) std::cout << "An empty shared pointer." <<'\n';
	else std::cout << "psNoTable : " << psNoTable->GetNumber() << '\n';
	//std::cout << "pwNoTable : " << pwNoTable->GetNumber() << '\n';
	std::shared_ptr<Table> psTemp = pwTable1.lock();
	std::cout <<"pwTable1 : " << psTemp->GetNumber() << '\n';
	
	
	// TODO: Find a way to get the table's number for the smart pointer that hasn't the -> operator

	// Access using the * operator 
	// TODO: Verify which smart pointers have the * operator (dereference)
	//       Show the Table info on the console using the Table's operator<<
	std::cout << "\nAccessing the managed objects using *:\n";
	std::cout << "psTable1 : " << psTable1.operator*().GetNumber() << '\n';
	std::cout << "psTable3 : " << psTable3.operator*().GetNumber() << '\n';
	//std::cout <<"pwTable1 : " << pwTable1.operator*().GetNumber() << '\n';
	std::shared_ptr<Table> psTemp1 = pwTable1.lock();
	std::cout << "pwTable1 : " << psTemp1.operator*().GetNumber() << '\n';
	std::cout << "puTable1 : " << puTable1.operator*().GetNumber() << '\n';
	std::cout << "puTable2 : " << puTable2.operator*().GetNumber() << '\n';
	if (!psNoTable) std::cout << "An empty shared pointer." << '\n';
	else std::cout << "psNoTable : " << psNoTable.operator*().GetNumber() << '\n';
	// TODO: Find a way to show the table for the smart pointer that hasn't the * operator
	
	// Use the bool operator to verify whether a smart pointer manages an existing object 
	// TODO: Verify which smart pointers have the bool operator defined
	std::cout << "\nTest existance of managed object using the bool operator:\n";
	std::cout << "psTable1 : " << psTable1.operator bool() << '\n';
	std::cout << "psTable3 : " << psTable3.operator bool() << '\n';
	//std::cout <<"pwTable1 : " << pwTable1.operator bool() << '\n';
	std::shared_ptr<Table> psTemp2 = pwTable1.lock();
	std::cout << "pwTable1 : " << psTemp2.operator bool() << '\n';
	std::cout << "puTable1 : " << puTable1.operator bool() << '\n';
	std::cout << "puTable2 : " << puTable2.operator bool() << '\n';
	if (!psNoTable) std::cout << "An empty shared pointer." << '\n';
	else std::cout << "psNoTable : " << psNoTable.operator bool() << '\n';
	// The operators ==, != to verify whether 2 smart pointers do (not) manage the same object 
	// TODO: Verify which smart pointers have this operator
	std::cout << "\nTest whether smart pointers manage the same object using == and !=:\n";


	//std::cout << "psTable1 : " << psTable1. << '\n';
	//std::cout << "psTable3 : " << psTable3.operator bool() << '\n';
	//std::cout <<"pwTable1 : " << pwTable1.operator bool() << '\n';
	//std::shared_ptr<Table> psTemp2 = pwTable1.lock();
	//std::cout << "pwTable1 : " << pwTable1.operator= << '\n';
	//std::cout << "puTable1 : " <<puTable1 << '\n';
	//std::cout << "puTable2 : " << puTable2.operator bool() << '\n';
	//if (!psNoTable) std::cout << "An empty shared pointer." << '\n';
	//else std::cout << "psNoTable : " << psNoTable.operator bool() << '\n';




}

void TestRestrictions( )
{
	// Don't create smart pointers for objects on the stack
	// TODO: Uncomment next code lines and see what happens
	Table table1{ 1 };
	std::shared_ptr<Table> pToTableOnStack1{ &table1 };
	Table table2{ 2 };
	std::unique_ptr<Table> pToTableOnStack2{ &table2 };

	// There should be only one manager for each managed heap object
	// Ensure that only one manager can be created by NOT using raw pointers
	// TODO: Uncomment the NOK code and see what happens
	Table* pTable3{ new Table( 3 ) }; // Don't use raw pointer
	std::shared_ptr<Table> p1Table3{ pTable3 }; // better create the object here => raw pointer can't get misused
	//std::shared_ptr<Table> p1Table3{ pTable3 }; // NOK

	// Don't delete a heap object, that is already managed by a smart pointer
	// TODO: Uncomment the NOK code and see what happens
	Table* pTable4{ new Table( 4 ) }; // Avoid using raw pointers when using smart pointers
	std::shared_ptr<Table> spTank{ pTable4 };
	//delete pTable4; // NOK
}

void TestUniquePointersContainer( )
{
	std::vector<std::unique_ptr<Table>> pTables;

	// Add 10 tables to the vector
	for ( int nr = 1; nr <= 10; ++nr )
	{
		// TODO: Uncomment next code lines and solve the error 
		std::unique_ptr<Table> pTable{ std::make_unique<Table>( nr ) };
		pTables.push_back( pTable );
	}

	// Print the tables to the console
	// TODO: Uncomment next code lines and solve the error 
	for ( std::unique_ptr<Table>& pTable : pTables )
	{
		std::cout << *pTable << " ";
	} 

	std::cout << '\n';

	// TODO: Explain why next code line results in a compilation error 
	//std::unique_ptr<Table> pCopyOfLastTable = pTables.back( );

	// TODO: Print first and last element of vector using the table's operator <<
	//std::unique_ptr<Table> pTables;
	
	std::cout << &pTables.begin();
	std::cout << &pTables.back();


	// Transfer ownership of last element
	//std::unique_ptr<Table> pLastTable = std::move( pTables.back( ) );

	// TODO: Again print first and last element of vector

}


std::shared_ptr<Table> CreateSharedTable( int nr )
{
	return std::make_shared<Table>( nr );
}

std::unique_ptr<Table> CreateUniqueTable( int nr )
{
	return std::make_unique<Table>( nr );
}

std::weak_ptr<Table> CreateWeakTable( int nr )
{
	return std::make_shared<Table>( nr );
}

void StartHeapControl( )
{
#if defined(DEBUG) | defined(_DEBUG)
	// Notify user if heap is corrupt
	HeapSetInformation( NULL, HeapEnableTerminationOnCorruption, NULL, 0 );

	// Report detected leaks when the program exits
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	// Set a breakpoint on the specified object allocation order number
	//_CrtSetBreakAlloc( 163 );
#endif
}

void DumpMemoryLeaks( )
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtDumpMemoryLeaks( );
#endif
}

