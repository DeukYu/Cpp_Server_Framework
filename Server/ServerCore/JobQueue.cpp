#include "pch.h"
#include "JobQueue.h"
#include "GlobalQueue.h"

void JobQueue::Push(JobRef job, bool pushOnly)
{
	const int32 prevCount = _jobCount.fetch_add(1);
	_jobs.Push(job);

	if (0 == prevCount)
	{
		if (nullptr == LCurrentJobQueue && false == pushOnly)
		{
			Execute();
		}
		else
		{
			// ���� �ִ� �ٸ� �����尡 �����ϵ��� GLobalQueue�� �ѱ��.
			GGlobalQueue->Push(shared_from_this());
		}
	}
}

void JobQueue::Execute()
{
	LCurrentJobQueue = this;

	while (true)
	{
		Vector<JobRef>	jobs;
		_jobs.PopAll(OUT jobs);

		const int32 jobCount = static_cast<int32>(jobs.size());
		for (int32 i = 0; i < jobCount; ++i)
			jobs[i]->Execute();

		// ���� �ϰ��� 0����� ����
		if (jobCount == _jobCount.fetch_sub(jobCount))
		{
			LCurrentJobQueue = nullptr;
			return;
		}

		const uint64 now = ::GetTickCount64();
		if (now >= LEndTickCount)
		{
			LCurrentJobQueue = nullptr;
			// ���� �ִ� �ٸ� �����尡 �����ϵ��� GLobalQueue�� �ѱ��.
			GGlobalQueue->Push(shared_from_this());
			break;
		}
	}
}
