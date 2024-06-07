#include <cassert>
#include <iostream>

#include "scheduler.hpp"

Scheduler::Scheduler(void)
		: running(false), hwrite_token(100000), gwrite_token(100000), hwrite_stat(0), gwrite_stat(0)
{
}

void Scheduler::off(void)
{
	running = false;
}

void Scheduler::on(int ratio)
{
	running = true;
	hwrite_token = 100000;
	gwrite_token = 100000;
	hwrite_ratio = ratio;
	gwrite_ratio = 1000 - hwrite_ratio;
}

bool Scheduler::schedule_hwrite(void)
{
	if (running) {
		if (hwrite_token < gwrite_token)
			return false;
		hwrite_token -= gwrite_ratio;
	}

	hwrite_stat++;
	return true;
}

bool Scheduler::schedule_gwrite(void)
{
	if (running) {
		if (gwrite_token < hwrite_token)
			return false;
		gwrite_token -= hwrite_ratio;
	}

	gwrite_stat++;
	return true;
}

bool Scheduler::schedule(WriteType wtype)
{
	if (hwrite_token < 1000 || gwrite_token < 1000) {
		hwrite_token += 100000;
		gwrite_token += 100000;
	}

	switch (wtype) {
	case WriteType::HOST:
		return schedule_hwrite();
	case WriteType::GC:
		return schedule_gwrite();
	default:
		assert(false);
	}
}

void Scheduler::report(void)
{
	std::cout << "hwrite: " << hwrite_stat << std::endl;
	std::cout << "gwrite: " << gwrite_stat << std::endl;
	std::cout << "   waf: " << 1 + (static_cast<double>(gwrite_stat) / hwrite_stat) << std::endl;
}
