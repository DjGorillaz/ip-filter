#ifndef IP_FILTER_H
#define IP_FILTER_H

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using vecStr = std::vector<std::string>;

class IpPool
{
public:
    IpPool() = default;
    IpPool(std::istream& stream);
    IpPool& operator=(std::vector<vecStr>&& vv) noexcept;
    void print();
    void reverseSort();
    template <typename... Args>
    auto filter(Args... args);
    std::vector<vecStr> filterAny(int byte);

private:
    auto split(const std::string &str, char d);
    std::vector<vecStr> pool;
};

template <typename... Args>
auto IpPool::filter(Args... args)
{
    std::vector<vecStr> v;
    if (pool.empty())
        return v;

    auto sz = sizeof...(args);
    if (sz > pool.at(0).size())
            throw std::invalid_argument("Too much args");

    int inIp[sizeof...(args)] = {(args)...};
    for(const auto& ip : pool)
    {
        uint i = 0;
        for(; i < sz; ++i)
        {
            if (inIp[i] != std::stoi(ip.at(i)))
                break;
        }
        if (i == sz) v.push_back(ip);
    }
    return v;
}

#endif // IP_FILTER_H
