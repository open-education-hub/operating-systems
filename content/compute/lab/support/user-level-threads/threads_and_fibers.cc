// SPDX-License-Identifier: BSD-3-Clause

#include <vector>
#include <thread>

#include <boost/fiber/all.hpp>
#include <boost/fiber/detail/thread_barrier.hpp>

#define NUM_FIBERS 10
#define NUM_THREADS 3

static boost::fibers::fiber_specific_ptr<int> fiber_id;
static thread_local int thread_id;

static std::mutex print_mutex{};
static std::size_t fiber_count{ 0 };
static std::mutex count_mutex{};
static boost::fibers::condition_variable_any cnd_count{};

static boost::fibers::detail::thread_barrier thread_barrier(NUM_THREADS);

void fiber_work(int id)
{
	fiber_id.reset(new int(id));

	for (int i = 0; i < 10; i++) {
		print_mutex.lock();
		std::cout << "Fiber " << *fiber_id << ", on thread " << thread_id << ", yields" << std::endl;
		print_mutex.unlock();

		boost::this_fiber::yield();
	}

	count_mutex.lock();
	if (0 == --fiber_count) {
		count_mutex.unlock();
		cnd_count.notify_all();
	}
	count_mutex.unlock();
}

void thread_work(int id)
{
	thread_id = id;

	print_mutex.lock();
	std::cout << "thread " << thread_id << " started" << std::endl;
	print_mutex.unlock();

	// TODO: use the `work_stealing` scheduler
	boost::fibers::use_scheduling_algorithm<boost::fibers::algo::shared_work>();

	thread_barrier.wait();

	count_mutex.lock();
	cnd_count.wait( count_mutex, [](){ return 0 == fiber_count; } );
	count_mutex.unlock();
}

int main(void)
{
	std::vector<boost::fibers::fiber *> fibers;
	std::vector<std::thread *> threads;

	for (int i = 0; i < NUM_FIBERS; i++) {
		fibers.push_back(new boost::fibers::fiber(fiber_work, i));
		fibers[i]->detach();
		++fiber_count;
	}

	for (int i = 0; i < NUM_THREADS - 1; i++)
		threads.push_back(new std::thread(thread_work, i + 1));

	boost::fibers::use_scheduling_algorithm< boost::fibers::algo::shared_work>();

	thread_barrier.wait();

	count_mutex.lock();
	cnd_count.wait( count_mutex, [](){ return 0 == fiber_count; } );
	count_mutex.unlock();

	for (auto thread : threads)
		thread->join();

	return 0;
}
