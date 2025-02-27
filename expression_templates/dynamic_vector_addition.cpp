#include <iostream>
#include <vector>

// Defining a simple Vector class to represent dynamic vectors
class Vector
{
public:
    // Constructor
    Vector(int size) : data(size) {}

    // Access elements
    double &operator()(int i) { return data[i]; }
    const double &operator()(int i) const { return data[i]; }

    // Get size
    int size() const { return static_cast<int>(data.size()); }

    // Print the vector
    void print() const
    {
        for (double val : data)
        {
            std::cout << val << std::endl;
        }
        std::cout << std::endl;
    }

    // To enable lazy evaluation, we’ll overload the assignment = operator
    template <typename Expr>
    Vector &operator=(const Expr &expr)
    {
        for (int i = 0; i < size(); ++i)
        {
            data[i] = expr(i);
        }
        return *this;
    }

private:
    std::vector<double> data;
};

// define an expression template for vector addition
template <typename Lhs, typename Rhs>
class VectorSum
{
public:
    // Constructor
    VectorSum(const Lhs &lhs, const Rhs &rhs) : lhs(lhs), rhs(rhs) {}

    // Access elements of the vector experssion
    double operator()(int i) const
    {
        return lhs(i) + rhs(i);
    }

    // Get the size of the expression
    int size() const
    {
        return lhs.size();
    }

private:
    const Lhs &lhs;
    const Rhs &rhs;
};

// overload the + operator
template <typename Lhs, typename Rhs>
VectorSum<Lhs, Rhs> operator+(const Lhs &lhs, const Rhs &rhs)
{
    return VectorSum<Lhs, Rhs>(lhs, rhs);
}

int main()
{
    Vector v(3), w(3), u(3), x(3);

    // Initialize vectors
    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 3.0;
    w(0) = 4.0;
    w(1) = 5.0;
    w(2) = 6.0;
    x(0) = 7.0;
    x(1) = 8.0;
    x(2) = 9.0;

    v.print();
    w.print();
    x.print();

    // Perform vector addition
    u = v + w + x;

    // Print the result
    std::cout << "u = v + w + x = " << std::endl;
    u.print();

    return 0;
}