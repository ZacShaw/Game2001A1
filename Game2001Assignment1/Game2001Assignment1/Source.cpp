#include "OrderedArray.h"
#include "UnorderedArray.h"

int main()
{
	OrderedArray<int> array(2, 2);

	array.push(4);
	array.printArray();
	array.push(64);
	array.printArray();
	array.push(8);
	array.printArray();
	array.push(16);
	array.printArray();
	array.push(32);
	array.printArray();
	array.push(2);
	array.printArray();
	array.push(64);

	std::cout << "\nSearching the array for a specific value (" << array[array.find(8)] << ")\n\n";

	std::cout << "Removing the latest value from the array...\n\n";
	array.pop();
	array.printArray();

	std::cout << "\nClearing the array...\n";
	array.erase();
	array.printArray();


	return 0;
}