#include <iostream>
#include <string>
#include <vector>
#include <functional>

#include <mutex>
#include <future>


template<typename T>
class monitor {

    private:

		T t;
		/* mutable */ std::mutex mux;

    public:

		explicit monitor(T t = T{}) : t{ std::move(t) } {}

		template<typename F>
		auto operator()(F &&f) {
			std::lock_guard<std::mutex> _{ mux };			
			return std::invoke(std::forward<F>(f), t);
		}

		/////template<typename F>
		/////auto operator()(F &&f) const {
		/////	std::lock_guard<std::mutex> _{ mux };
		/////	return std::invoke(std::forward<F>(f), t);
		/////}
};



int main() {

	monitor<std::string> s{ "start\n" };
	std::vector<std::future<void>> v;

	for (int i = 0; i < 10; i++) {
		v.push_back(
			std::async(
				[&, i]() {					
					s([i](std::string& es) {
						es += std::to_string(i);
						std::this_thread::sleep_for(std::chrono::milliseconds(100));
						es += '\n';
					});					
				}
			)
		);
	}

	for (auto &f : v)
		f.wait();

	s([](const std::string &es) {
		std::cout << es << '\n';
	});

}
