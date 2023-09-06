#pragma once

namespace math
{

class Math
{
public:
    Math() = default;
    Math(const Math&) = delete;
    Math(Math&&) = delete;
    Math& operator=(const Math&) = delete;
    Math&& operator=(Math&&) = delete;

public:
    int add(int i, int j);
    int sub(int i, int j);
    int mul(int i, int j);
    int div(int i, int j);
};

}  // namespace math