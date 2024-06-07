#ifndef _SCHEDULER_HPP_
#define _SCHEDULER_HPP_

enum class WriteType {
	HOST,
	GC,
};

class Scheduler {
private:
	bool running;
	int hwrite_token;
	int gwrite_token;
	int hwrite_ratio;
	int gwrite_ratio;

	bool schedule_hwrite(void);
	bool schedule_gwrite(void);

	/* Statistics */
	unsigned long hwrite_stat;
	unsigned long gwrite_stat;

public:

	Scheduler(void);

	void off(void);
	void on(int ratio);
	bool schedule(WriteType wtype);
	void report(void);
};

#endif
