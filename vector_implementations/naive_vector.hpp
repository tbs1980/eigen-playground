#pragma once

#include <cstddef>
#include <cassert>

template <typename Real>
class NaiveVector
{
public:
    inline NaiveVector(std::size_t size)
        : m_size(size), m_data(new Real[size])
    {
    }
    inline NaiveVector(std::size_t size, Real val)
        : m_size(size), m_data(new Real[size])
    {
        for (std::size_t i = 0; i < m_size; ++i)
        {
            m_data[i] = val;
        }
    }
    inline ~NaiveVector()
    {
        delete m_data;
    }

    inline std::size_t size() const
    {
        return m_size;
    }

    inline NaiveVector &operator=(NaiveVector const &other)
    {
        assert(m_size == other.m_size);
        return *this;
    }

    inline Real &operator[](std::size_t i)
    {
        assert(i < m_size);
        return m_data[i];
    }

    inline Real operator[](std::size_t i) const
    {
        assert(i < m_size);
        return m_data[i];
    }

    inline NaiveVector operator+(NaiveVector const &other)
    {
        assert(m_size == other.m_size);
        NaiveVector result(m_size);
        for (std::size_t i = 0; i < m_size; ++i)
        {
            result.m_data[i] = m_data[i] + other.m_data[i];
        }
        return result;
    }

    inline NaiveVector operator*(NaiveVector const &other)
    {
        assert(m_size == other.m_size);
        NaiveVector result(m_size);
        for (std::size_t i = 0; i < m_size; ++i)
        {
            result.m_data[i] = m_data[i] * other.m_data[i];
        }
        return result;
    }

private:
    std::size_t m_size;
    Real *m_data;
};