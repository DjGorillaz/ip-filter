#include "ip_filter.h"

auto IpPool::split(const std::string &str, char d)
{
    vecStr r;
    std::string::size_type start = 0, stop = 0;

    do
    {
        stop = str.find_first_of(d, start);
        r.push_back(str.substr(start, stop - start));
        start = stop + 1;
    }
    while(stop != std::string::npos);

    return r;
}

IpPool::IpPool(std::istream &stream)
{
    std::string line;
    while (std::getline(stream /*std::cin*/, line))
    {
        std::string ip = line.substr(0, line.find("\t"));
        pool.push_back(split(ip, '.'));
    }
}

IpPool& IpPool::operator=(std::vector<vecStr>&& vv) noexcept
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
    std::sort(pool.begin(), pool.end(),
              [](const vecStr& l, const vecStr& r)
    {
        auto vSize = l.size();
        for(uint i = 0; i < vSize; ++i)
        {
            int lNum = std::stoi(l.at(i));
            int rNum = std::stoi(r.at(i));
            if (lNum != rNum) return lNum > rNum;
        }
        return false;
    });
}

std::vector<vecStr> IpPool::filterAny(int byte)
{
    std::vector<vecStr> v;
    if (pool.empty())
        return v;

    auto sz = pool.at(0).size();

    for(const auto& ip : pool)
    {
        for(uint i = 0; i < sz; ++i)
        {
            if (byte == std::stoi(ip.at(i)))
            {
                v.push_back(ip);
                break;
            }
        }
    }
    return v;
}
