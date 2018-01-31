#include "ip_filter.h"

auto IpPool::split(const std::string &str, char d)
{
    vecInt r;
    std::string::size_type start = 0, stop = 0;

    do
    {
        stop = str.find_first_of(d, start);
        r.push_back(std::stoi(str.substr(start, stop - start)));
        start = stop + 1;
    }
    while(stop != std::string::npos);

    return r;
}

IpPool::IpPool(std::istream& stream)
{
    std::string line;
    while (std::getline(stream, line))
    {
        std::string ip = line.substr(0, line.find("\t"));
        pool.push_back(split(ip, '.'));
    }
}

IpPool& IpPool::operator=(std::vector<vecInt>&& vv) noexcept
{
    std::swap(pool, vv);
    return *this;
}

void IpPool::print()
{
    std::string sep = "";
    for(const auto& ip : pool)
    {
        sep = "";
        for(const auto& ipPart : ip)
        {
            std::cout << sep << ipPart;
            sep = ".";
        }
        std::cout << std::endl;
    }
}

void IpPool::reverseSort()
{
    std::sort(pool.begin(), pool.end(), std::greater<>());
}

std::vector<vecInt> IpPool::filterAny(const int& inByte)
{
    std::vector<vecInt> v;
    if (pool.empty())
        return v;

    std::copy_if(pool.begin(), pool.end(), std::back_inserter(v), [&inByte](const vecInt& ip)
    {
        return std::any_of(ip.begin(), ip.end(), [&inByte](const int& byte)
        {
            return byte == inByte;
        });
    });

    return v;
}
