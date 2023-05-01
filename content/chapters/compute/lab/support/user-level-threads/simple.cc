// SPDX-License-Identifier: BSD-3-Clause

#include <vector>

#include <boost/fiber/all.hpp>

#define NUM_FIBERS 5

void hello(void)
{
	std::cout << "Hello World" << std::endl;
}

int main(void)
{
	std::vector<boost::fibers::fiber *> fibers;

	// TODO: add a fiber that calls sleep(5)
	for (int i = 0; i < NUM_FIBERS; i++)
		fibers.push_back(new boost::fibers::fiber(hello));

	for (auto fiber : fibers)
		fiber->join();

	return 0;
}
