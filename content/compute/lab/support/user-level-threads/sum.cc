// SPDX-License-Identifier: BSD-3-Clause

#include <vector>

#include <boost/fiber/all.hpp>

#define NUM_FIBERS 5000

static int sum;

void add_1(void)
{
	sum += 1;
}

int main(void)
{
	std::vector<boost::fibers::fiber *> fibers;

	for (int i = 0; i < NUM_FIBERS; i++)
		fibers.push_back(new boost::fibers::fiber(add_1));

	for (auto fiber : fibers)
		fiber->join();

	std::cout << "Sum is: " << sum << std::endl;

	return 0;
}
