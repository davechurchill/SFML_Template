#pragma once

#include <vector>
#include <algorithm>

template <class T>
class Grid
{
    size_t m_width = 0;
    size_t m_height = 0;

    std::vector<T> m_grid;

public:

    Grid() {}

    Grid(size_t width, size_t height, T val)
        : m_width(width)
        , m_height(height)
        , m_grid(width* height, val)
    {

    }

    void normalize()
    {
        T max = maxVal();
        if (max != 0)
        {
            for (T & val : m_grid)
            {
                val /= max;
            }
        }
    }

    T maxVal()
    {
        return *std::max_element(std::begin(m_grid), std::end(m_grid));
    }

    T minVal()
    {
        return *std::min_element(std::begin(m_grid), std::end(m_grid));
    }

    inline void refill(size_t width, size_t height, T val)
    {
        if (width == m_width && height == m_height)
        {
            std::fill(m_grid.begin(), m_grid.end(), val);
        }
        else
        {
            m_width = width;
            m_height = height;
            m_grid = std::vector<T>(width * height, val);
        }
    }

    inline T get(size_t index)
    {
        return m_grid[index];
    }

    inline void set(size_t index, T val)
    {
        m_grid[index] = val;
    }

    inline T get(size_t x, size_t y)
    {
        return m_grid[y * m_width + x];
    }

    inline const T get(size_t x, size_t y) const
    {
        return m_grid[y * m_width + x];
    }

    inline void add(size_t x, size_t y, T val)
    {
        m_grid[y * m_width + x] += val;
    }

    inline void set(size_t x, size_t y, T val)
    {
        m_grid[y * m_width + x] = val;
    }

    inline size_t width() const
    {
        return m_width;
    }

    inline size_t height() const
    {
        return m_height;
    }
};