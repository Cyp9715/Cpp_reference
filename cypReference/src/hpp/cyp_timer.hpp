#pragma once

#include "cyp_common.hpp"
#include <math.h>
#include <chrono>
#include <future>
#include <functional>


namespace cyp
{
	namespace timer
	{
		class Timer
		{
		private:
			std::chrono::system_clock::time_point _start;
			std::chrono::system_clock::time_point _current;

		public:
			void Start();

			template<typename T>
			long long getTime();
		};

		class FpsCounter
		{
		private:
			const float MILISECOND = 1000.0;

			int _tempFps = 0;
			int _loopFps = 0;
			float _fps = 0;

			std::chrono::system_clock::time_point _loopStart;

			std::chrono::system_clock::time_point _start;
			std::chrono::system_clock::time_point _end;

		public:
			// The return criterion is how many loop statements were executed per second.
			// i.e, only use in loop.
			int LoopCounting();

			// The Return criteria, number of times a second is divided by running time.
			// i.e, can measure FPS indirectly even if not loop
			void StartTimeCounting();
			float EndTimeCounting();
		};

		// It is not possible to build a general - purpose library of that callback timer.
		// This is a limitation of the C++ language.
		// recommended to modify and use the prototype as needed.
		class CallbackTimer
		{
		private:
			int currentThreadCount = 0;
			bool isRunningTimer = false;
			std::mutex _m;

		public:
			void Regist(int miliseconds, std::function<void()>& func);
			// An infinite loop thread that is already running can be stopped using the isLoop reference variable.
			// next func start after end before func.
			void Regist_loop(int miliseconds, std::function<void()>& func, bool &isLoop);

			// the next func will be executed, even if the previous func has not finished executing.
			// multiple func can coexist. if before func is not end next func is run.
			// The number of Threads can be set with the maxThreadCount variable.
			// If you specify too large a number, CPU usage may increase rapidly, so use it with caution.
			void Regist_loop_thread(int& miliseconds, std::function<void()>& func, bool& isLoop, int& maxThreadCount);
			
			void Regist_loop_thread(int&& miliseconds, std::function<void()>& func, bool& isLoop, int&& maxThreadCount);

		};
	}
}