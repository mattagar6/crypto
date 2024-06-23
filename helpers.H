#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <cstdint>
#include <vector>
#include <cassert>

#define MOD 1000000007

struct Point {
	std::int64_t x, y;
};

std::ostream& operator<<( std::ostream& out, Point p ) {
	return out << p.x << " " << p.y;
}

std::istream& operator>>( std::istream& in, Point& p ) {
	return in >> p.x >> p.y;
}

std::int64_t inverse( std::int64_t x ) {
	auto M = MOD - 2;
	std::int64_t ans = 1, cur = x;
	while( M > 0 ) {
		if( M % 2 == 1 ) {
			ans = ans * cur % MOD;
		}
		cur = cur * cur % MOD;
		M /= 2;
	}
	return ans;
}

std::string recover( std::vector<Point> first, std::vector<Point> second ) {
	const auto N = first.size();
	assert( N == second.size() );
	std::string secret;
	for( auto i = 0u; i < N; ++i ) {
		const auto p1 = first[i], p2 = second[i];
		const auto m = ( ( p2.y - p1.y + MOD ) % MOD ) * inverse( ( p2.x - p1.x + MOD ) % MOD ) % MOD;
		const auto b = ( p1.y - p1.x * m % MOD + MOD ) % MOD;
		assert( 1 <= b && b <= 26 );
		secret.push_back( static_cast<char>(b - 1 + 'a') );
	}
	return secret;
}
