#include "ip_filter.h"
#define BOOST_TEST_MODULE test_sort

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>

BOOST_AUTO_TEST_CASE(ip_sorting)
{
    std::vector<vecInt> v{{1, 7, 234, 8},
                          {1, 1, 235, 8},
                          {2, 7, 235, 10},
                          {1, 1, 233, 7},
                          {2, 7, 234, 10}};
    IpPool pool;
    pool = std::move(v);
    pool.reverseSort();

    std::vector<vecInt> sorted{{1, 7, 234, 8},
                               {1, 1, 235, 8},
                               {1, 1, 233, 7}};
    std::vector<vecInt> res = pool.filter(1);
    BOOST_CHECK(res == sorted);


    sorted = {{1, 1, 235, 8},
              {1, 1, 233, 7}};
    res = pool.filter(1, 1);
    BOOST_CHECK(res == sorted);


    sorted = {{2, 7, 235, 10},
              {2, 7, 234, 10},
              {1, 7, 234, 8},
              {1, 1, 233, 7}};
    res = pool.filterAny(7);
    BOOST_CHECK(res == sorted);
}
