#include "ip_filter.h"

int main(int /* argc */, const char** /* argv[] */)
{
    try
    {
        IpPool pool(std::cin);

        //reverse lexicographically sort
        pool.reverseSort();
        pool.print();

        //filter by first byte and output
        IpPool sortedPool;
        sortedPool = pool.filter(1);
        sortedPool.print();

        //filter by first and second bytes and output
        sortedPool = pool.filter(46, 70);
        sortedPool.print();

        //filter by any byte and output
        sortedPool = pool.filterAny(46);
        sortedPool.print();
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
