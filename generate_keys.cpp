#include <random>
#include <chrono>
#include "helpers.H"

std::mt19937 rng;

std::vector<std::int64_t> read_secret_phrase() {
	std::string buf;
	std::vector<std::int64_t> in;
	while( std::cin >> buf ) {
		std::transform( buf.begin(), buf.end(), std::back_inserter( in ), 
				[]( char c ) -> std::int64_t {
					assert( 'a' <= c && c <= 'z' );
					return c - 'a' + 1;
				}
		);
	}
	return in;
}

// 1,y
std::vector<std::int64_t> make_points( std::size_t n ) {
	std::uniform_int_distribution<std::int64_t> dist{ 0, MOD - 1 };
	std::vector<std::int64_t> points(n);
	for( auto& p : points ) {
		p = dist( rng );
	}
	return points;
}

int main() {
	
	rng.seed( std::chrono::system_clock::now().time_since_epoch().count() );
	auto secret_phrase = read_secret_phrase();
	const auto N = secret_phrase.size();
	auto random_points = make_points( N );

	std::vector<Point> shares[3];
	for( auto i = 0u; i < 3; ++i ) {
		shares[i].resize( N );
		std::uniform_int_distribution<std::int64_t> dist{ 0, MOD - 1 };
		for( auto j = 0u; j < N; ++j ) {
			auto& p = shares[i][j];
			p.x = dist( rng );
			p.y = ( ( ( random_points[j] - secret_phrase[j] ) * p.x + secret_phrase[j] ) % MOD + MOD) % MOD;
		}
		std::cout << "SHARE " << i + 1 << ":" << std::endl;
		for( auto p : shares[i] ) {
			std::cout << p << std::endl;
		}
	}
	
#ifdef TEST
	for( auto i = 0u; i < 3; ++i ) {
		for( auto j = 0u; j < i; ++j ) {
			std::cout << "CHECKING COMBINATION OF SHARES " << i+1 << " AND " << j+1 << std::endl;
			std::cout << recover( shares[i], shares[j] ) << std::endl;
		}
	}
#endif

	return 0;
}
