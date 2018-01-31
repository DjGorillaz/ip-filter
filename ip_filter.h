#ifndef IP_FILTER_H
#define IP_FILTER_H

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using vecInt = std::vector<int>;

class IpPool
{
public:
    IpPool() = default;
    IpPool(std::istream& stream);
    IpPool& operator=(std::vector<vecInt>&& vv) noexcept;
    void print();
    void reverseSort();
    template <typename... Args>
    auto filter(Args... args);
    std::vector<vecInt> filterAny(const int &inByte);

private:
    auto split(const std::string &str, char d);
    std::vector<vecInt> pool;
};

template <typename... Args>
auto IpPool::filter(Args... args)
{
    std::vector<vecInt> v;
    if (pool.empty())
        return v;

    if (sizeof...(args) > pool.at(0).size())
            throw std::invalid_argument("Too much args");

    vecInt inIp = {(args)...};

    std::copy_if(pool.begin(), pool.end(), std::back_inserter(v), [&inIp](const vecInt& ip)
    {
        return std::equal(inIp.begin(), inIp.end(), ip.begin());
    });

    return v;
}

#endif // IP_FILTER_H
