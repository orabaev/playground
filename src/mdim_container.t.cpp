#include "catch/catch.hpp"
#include <vector>
#include <iostream>

using namespace std;

class MDimContainer {
private:
    vector<int> dims;
    vector<int> data;
    vector<int> mult;

    int& get_at(const vector<int>& adims)
    {
        int offset = adims.back();
        for (int i = 0; i < dims.size()-1; ++i)
        {
            offset += adims[i] * mult[i];
        }
        return *(data.data()+offset);
    }
    
public:
    MDimContainer(vector<int> adims)
    : dims(move(adims))
    {
        size_t total_size = 1;
        for (auto v : dims) total_size *= v;
        data.resize(total_size);

        // pre-calculate multipliers
        mult.resize(dims.size());
        int m = 1;
        for (int i=dims.size()-1; i>0; --i)
        {
            m *= dims[i];
            mult[i-1] = m;
        }
    }

    void set(const vector<int>& adims, int v)
    {
        get_at(adims) = v;
    }

    int get(const vector<int>& adims)
    {
        return get_at(adims);
    }
};

TEST_CASE("MDimContainer")
{
    vector<int> dims = {3,4,2,13};
    MDimContainer mvec(dims);

    int v = 0;
    for (int i=0; i<3; ++i)
    {
        for (int j=0; j<4; ++j)
        {
            for (int k=0; k<2; ++k)
            {
                for (int l=0; l<13; ++l)
                {
                    vector<int> adims{i,j,k,l};
                    mvec.set(adims, v);
                    ++v;
                }
            }
        }
    }

    v = 0;
    for (int i=0; i<3; ++i)
    {
        for (int j=0; j<4; ++j)
        {
            for (int k=0; k<2; ++k)
            {
                for (int l=0; l<13; ++l)
                {
                    vector<int> adims{i,j,k,l};
                    REQUIRE( v == mvec.get(adims) );
                    ++v;
                }
            }
        }
    }
}