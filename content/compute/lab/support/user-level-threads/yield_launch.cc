// SPDX-License-Identifier: BSD-3-Clause

#include <vector>

#include <boost/fiber/all.hpp>

#define NUM_FIBERS 5

void yielding_work(int id)
{
	std::cout << "Fiber " << id << " before yielding" << std::endl;

	boost::this_fiber::yield();

	std::cout << "Fiber " << id << " after yielding once" << std::endl;

	boost::this_fiber::yield();

	std::cout << "Fiber " << id << " after yielding twice" << std::endl;
}

int main(void)
{
	std::vector<boost::fibers::fiber *> fibers;

	for (int i = 0; i < NUM_FIBERS; i++) {
		std::cout << "Creating fiber " << i << std::endl;
		// TODO: modify the launch parameter
		fibers.push_back(new boost::fibers::fiber(boost::fibers::launch::dispatch, yielding_work, i));
	}

	for (auto fiber : fibers)
		fiber->join();

	return 0;
}
