/*******************************************************************************
** @file unique_ptr.test.cpp
** @author August Lounibos
** @date 6.5.18
** @brief unique_ptr test file 
*******************************************************************************/

#include <diy/unique_ptr.hpp>
#include <catch.hpp>
#include <utility>

TEST_CASE("unique_ptr", "[diy]") {
    static int leaks = 0;
    struct data {
        int n;
        explicit data(int i = 0) : n(i) { leaks++; } 
        ~data() { leaks--; }
    };
    SECTION("ctors") {
        {
            diy::unique_ptr<data> a;                // default
            diy::unique_ptr<data> b(new data(2));   // new ptr
            diy::unique_ptr<data> c(std::move(b));  // move 
            auto d = diy::make_unique<data>(3);     // move + factory
            a = std::move(d);                       // move=
        }
        REQUIRE(leaks == 0);
    }
    SECTION("accessors") {
        auto ptr = diy::make_unique<int>(2);
        auto zero_ptr = diy::make_unique<int>();
        auto data_ptr = diy::make_unique<data>(2);
        diy::unique_ptr<int> null_ptr{};

        REQUIRE(*(ptr.get()) == 2);                 // get
        REQUIRE(        *ptr == 2);                 // operator *
        REQUIRE( data_ptr->n == 2);                 // operator ->

        REQUIRE(ptr);                               // operator bool
        REQUIRE(zero_ptr);                          // operator bool
        REQUIRE_FALSE(null_ptr); // operator bool
    }
    SECTION("mutators") {
        {
            auto a = diy::make_unique<data>(2);
            auto b = diy::make_unique<data>(3);

            diy::swap(a, b);
            REQUIRE(a->n == 3);
            REQUIRE(b->n == 2);

            a.reset();
            REQUIRE_FALSE(a);
            
            data * raw = b.release();
            REQUIRE_FALSE(b);
            REQUIRE(raw->n == 2);

            a.reset(raw);
            REQUIRE(a);
            REQUIRE(a->n == 2);
        }
    }
}
