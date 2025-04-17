#pragma once
#include "rspl.hpp"
#include <cassert>

namespace rspl
{

class Downsampler2Flt
{
public:
    enum { NBR_COEFS = 7 };

    Downsampler2Flt()
    : _coef_arr()
    , _x_arr()
    , _y_arr()
    {
        _coef_arr[0] = static_cast<float>(CHK_COEFS_NOT_SET);
        clear_buffers();
    }

    ~Downsampler2Flt() = default;

    void set_coefs(const double coef_ptr[NBR_COEFS])
    {
        assert(coef_ptr != nullptr);
        for (int i = 0; i < NBR_COEFS; ++i)
        {
            float c = static_cast<float>(coef_ptr[i]);
            assert(c > 0.0f && c < 1.0f);
            _coef_arr[i] = c;
        }
    }

    void clear_buffers()
    {
        _x_arr[0] = 0.0f;
        _x_arr[1] = 0.0f;
        for (int i = 0; i < NBR_COEFS; ++i)
            _y_arr[i] = 0.0f;
    }

    void downsample_block(float dest_ptr[], const float src_ptr[], long nbr_spl)
    {
        assert(_coef_arr[0] != static_cast<float>(CHK_COEFS_NOT_SET));
        assert(dest_ptr != nullptr && src_ptr != nullptr);
        assert(nbr_spl > 0);

        long pos = 0;
        do
        {
            float p0 = src_ptr[pos*2 + 1];
            float p1 = src_ptr[pos*2];
            dest_ptr[pos] = process_sample(p0, p1);
            ++pos;
        }
        while (pos < nbr_spl);
    }

    void phase_block(float dest_ptr[], const float src_ptr[], long nbr_spl)
    {
        assert(_coef_arr[0] != static_cast<float>(CHK_COEFS_NOT_SET));
        assert(dest_ptr != nullptr && src_ptr != nullptr);
        assert(nbr_spl > 0);

        long pos = 0;
        do
        {
            float p1 = src_ptr[pos];
            dest_ptr[pos] = process_sample(0.0f, p1);
            ++pos;
        }
        while (pos < nbr_spl);

        // kill denormals on selected states
        float d = ANTI_DENORMAL_FLT;
        _y_arr[0] += d; _y_arr[2] += d; _y_arr[4] += d; _y_arr[6] += d;
        _y_arr[0] -= d; _y_arr[2] -= d; _y_arr[4] -= d; _y_arr[6] -= d;
    }

private:
    enum { CHK_COEFS_NOT_SET = 12345 };

    rspl_FORCEINLINE float process_sample(float path_0, float path_1)
    {
        float tmp0 = _x_arr[0];
        float tmp1 = _x_arr[1];
        _x_arr[0] = path_0;
        _x_arr[1] = path_1;

        path_0 = (path_0 - _y_arr[0]) * _coef_arr[0] + tmp0;
        path_1 = (path_1 - _y_arr[1]) * _coef_arr[1] + tmp1;
        tmp0    = _y_arr[0];
        tmp1    = _y_arr[1];
        _y_arr[0] = path_0;
        _y_arr[1] = path_1;

        path_0 = (path_0 - _y_arr[2]) * _coef_arr[2] + tmp0;
        path_1 = (path_1 - _y_arr[3]) * _coef_arr[3] + tmp1;
        tmp0    = _y_arr[2];
        tmp1    = _y_arr[3];
        _y_arr[2] = path_0;
        _y_arr[3] = path_1;

        path_0 = (path_0 - _y_arr[4]) * _coef_arr[4] + tmp0;
        path_1 = (path_1 - _y_arr[5]) * _coef_arr[5] + tmp1;
        tmp0    = _y_arr[4];
        _y_arr[4] = path_0;
        _y_arr[5] = path_1;

        path_0 = (path_0 - _y_arr[6]) * _coef_arr[6] + tmp0;
        _y_arr[6] = path_0;

        assert(NBR_COEFS == 7);
        return path_0 + path_1;
    }

    float _coef_arr[NBR_COEFS];
    float _x_arr[2];
    float _y_arr[NBR_COEFS];

    // disable copying and comparison
    Downsampler2Flt(const Downsampler2Flt&) = delete;
    Downsampler2Flt& operator=(const Downsampler2Flt&) = delete;
    bool operator==(const Downsampler2Flt&) const = delete;
    bool operator!=(const Downsampler2Flt&) const = delete;
};

} // namespace rspl
