#include <fstream>
#include <iterator>
#include "helpers.H"

int main() {
	std::ifstream first_share("first.txt"), second_share("second.txt");
	std::vector<Point> first, second;
	std::copy( std::istream_iterator<Point>( first_share ),
			   std::istream_iterator<Point>(),
			   std::back_inserter( first ) );
	std::copy( std::istream_iterator<Point>( second_share ),
			   std::istream_iterator<Point>(),
			   std::back_inserter( second ) );
	std::cout << recover( first, second ) << std::endl;
}
