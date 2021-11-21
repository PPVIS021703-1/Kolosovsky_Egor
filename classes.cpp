#include "long.h"

LongInt::LongInt() {}

LongInt::LongInt(std::string str)
{
    /* If string is emty, then number is zero */
    if (str.length() == 0) 
    {
        this->_is_negative = false;
    }
    else
    {
        if (str[0] == '-')
        {
            str = str.substr(1);  /* Get substring[indexes 1...n].Only number, no sign */
            this->_is_negative = true;
        }
        else 
        {
            this->_is_negative = false;
        }

        /* Make vector of ints from string */
        for (long long i = str.length(); i > 0; i -= 9)
        {
            if (i < 9) 
            {
                this->_digits.push_back(atoi(str.substr(0, i).c_str()));
            }
            else 
            {
                this->_digits.push_back(atoi(str.substr(i - 9, 9).c_str()));
            }
        }

        /* Delete leading zeros if exist*/
        this->_delete_leading_zeros();
    }
}

LongInt::LongInt(signed long long num)
{
    if (num < 0)
    {
        this->_is_negative = true;
        num = -num;
    }
    else
        this->_is_negative = false;

    /* Make vector of ints from number */
    while (num != 0)
    {
        this->_digits.push_back(num % LongInt::cell);
        num /= LongInt::cell;
    }
}

LongInt::LongInt(unsigned long long num)
{
    this->_is_negative = false;
    /* Make vector of ints from num */
    while (num != 0)
    {
        this->_digits.push_back(num % LongInt::cell);
        num /= LongInt::cell;
    }
}

void LongInt::_delete_leading_zeros()
{
    while (this->_digits.size() > 1 && this->_digits.back() == 0) 
    {
        this->_digits.pop_back();
    }

    /* Zeros can't be negative */
    if (this->_digits.size() == 1 && this->_digits[0] == 0) 
    {
        this->_is_negative = false;
    }
}

void LongInt::_shift_right() 
{
    if (this->_digits.size() == 0) 
    {
        this->_digits.push_back(0);
        return;
    }
    this->_digits.push_back(this->_digits[this->_digits.size() - 1]);

    /* Here the size of the array is at least two. 
    The search goes to the penultimate digit*/

    for (size_t i = this->_digits.size() - 2; i > 0; --i) this->_digits[i] = this->_digits[i - 1];
    this->_digits[0] = 0;
}

const LongInt LongInt::operator+() const
{
    return LongInt(*this);
}

const LongInt LongInt::operator-() const
{
    LongInt copy(*this);
    copy._is_negative = !copy._is_negative;
    return copy;
}

LongInt::operator std::string() const
{
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

std::ostream& operator<<(std::ostream& out, const LongInt& bi)
{
    if (bi._digits.empty()) 
    {
        out << 0;
    }
    else
    {
        if (bi._is_negative) 
        {
            out << '-';
        }
        out << bi._digits.back();

        char old_fill = out.fill('0');  /* Saving the current placeholder character */

        /* Print the following numbers in groups of 9 digits */
        for (long long i = static_cast<long long>(bi._digits.size()) - 2; i >= 0; --i) 
        {
            out << std::setw(9) << bi._digits[i];
        }

        out.fill(old_fill);  /* Restoring old placeholder character */
    }

    return out;
}


bool operator==(const LongInt& first, const LongInt& second)
{
    /* Numbers of different characters are not exactly equal */
    if (first._is_negative != second._is_negative) 
    {
        return false;
    }

    /* Have two representations of zero [0/empty] -> need to handle this in particular */
    if (first._digits.empty() || (first._digits.size() == 1 && first._digits[0] == 0))
    {
        if (second._digits.empty() || (second._digits.size() == 1 && second._digits[0] == 0)) 
        {
            return true;
        }
        else 
        {
            return false;
        }
    }

    if (second._digits.empty() || (second._digits.size() == 1 && second._digits[0] == 0))
    {
        if (first._digits.empty() || (first._digits.size() == 1 && first._digits[0] == 0)) 
        {
            return true;
        }
        else 
        {
            return false;
        }
    }

    /* Do not have leading zeros -> the numbers must have the same number of digits */
    if (first._digits.size() != second._digits.size()) 
    {
        return false;
    }

    /* Just compare each digit in numbers */
    for (size_t i = 0; i < first._digits.size(); i++)
    {
        if (first._digits[i] != second._digits[i]) 
        {
            return false;
        }
    }

    return true;
}

bool  operator<(const LongInt& first, const LongInt& second)
{
    if (first == second)
    {
        return false;
    }

    if (first._is_negative)
    {
        if (second._is_negative) 
        {
            return ((-second) < (-first));
        }
        else 
        {
            return true;
        }
    }
    else if (second._is_negative)
    {
        return false;
    }
    else
    {
        if (first._digits.size() != second._digits.size()) 
        {
            return (first._digits.size() < second._digits.size());
        }
        else
        {
            for (long long i = first._digits.size() - 1; i >= 0; --i)
            {
                if (first._digits[i] != second._digits[i]) 
                {
                    return (first._digits[i] < second._digits[i]);
                }
            }
            return false;
        }
    }

    return false;
}

bool operator!=(const LongInt& first, const LongInt& second)
{
    return !(first == second);
}

bool operator<=(const LongInt& first, const LongInt& second)
{
    return (first < second || first == second);;
}

bool  operator>(const LongInt& first, const LongInt& second)
{
    return !(first <= second);
}

bool operator>=(const LongInt& first, const LongInt& second)
{
    return !(first < second);
}


bool operator==(const LongInt& first, signed long long second)
{
    LongInt a(second);
    return (first == a);
}

bool  operator<(const LongInt& first, signed long long second)
{
    LongInt a(second);
    return (first < a);
}

bool operator!=(const LongInt& first, signed long long second)
{
    LongInt a(second);
    return (first != a);
}

bool operator<=(const LongInt& first, signed long long second)
{
    LongInt a(second);
    return (first <= a);
}

bool  operator>(const LongInt& first, signed long long second)
{
    LongInt a(second);
    return (first > a);
}

bool operator>=(const LongInt& first, signed long long second)
{
    LongInt a(second);
    return (first >= a);
}


const LongInt operator+(LongInt first, const LongInt& second) 
{
    /* Here is ONLY THE ADDITION of two positive numbers
    the rest is written by changing the sign and subtracting */
    if (first._is_negative)
    {
        if (second._is_negative) 
        {
            return -(-first + (-second));
        }
        else 
        {
            return second - (-first);
        }
    }
    else if (second._is_negative) 
    {
        return first - (-second);
    }

    int carry = 0;  /* Flag for transferring from the previous category */
    for (size_t i = 0; i < std::max(first._digits.size(), second._digits.size()) || carry != 0; i++)
    {
        if (i == first._digits.size()) 
        {
            first._digits.push_back(0);
        }
        first._digits[i] += carry + (i < second._digits.size() ? second._digits[i] : 0);
        carry = first._digits[i] >= LongInt::cell;
        if (carry != 0) 
        {
            first._digits[i] -= LongInt::cell;
        }
    }

    return first;
}

const LongInt operator-(LongInt first, const LongInt& second) 
{

    /* The same, only subtracting */
    if (second._is_negative) 
    {
        return first + (-second);
    }
    else if (first._is_negative) 
    {
        return -(-first + second);
    }
    /* Reverse if second bigger then first */
    else if (first < second) 
    {
        return -(second - first);
    }

    int carry = 0;
    for (size_t i = 0; i < second._digits.size() || carry != 0; ++i)
    {
        first._digits[i] -= carry + (i < second._digits.size() ? second._digits[i] : 0);
        carry = first._digits[i] < 0;
        if (carry != 0) 
        {
            first._digits[i] += LongInt::cell;
        }
    }

    first._delete_leading_zeros();
    return first;
}

const LongInt operator*(const LongInt& first, const LongInt& second)
{
    LongInt result;
    result._digits.resize(first._digits.size() + second._digits.size());
    for (size_t i = 0; i < first._digits.size(); i++)
    {
        int carry = 0;
        long long cur;
        for (size_t j = 0; j < second._digits.size() || carry != 0; ++j)
        {
            cur = result._digits[i + j] +
                first._digits[i] * 1LL * (j < second._digits.size() ? second._digits[j] : 0) + carry;
            result._digits[i + j] = static_cast<int>(cur % LongInt::cell);
            carry = static_cast<int>(cur / LongInt::cell);
        }
    }

    result._is_negative = first._is_negative != second._is_negative;
    result._delete_leading_zeros();
    return result;
}

const LongInt operator/(const LongInt& first, const LongInt& second)
{
    if (second == 0) throw LongInt::_divide_by_zero();
    LongInt b = second;
    b._is_negative = false;
    LongInt result, current;
    result._digits.resize(first._digits.size());
    for (long long i = static_cast<long long>(first._digits.size()) - 1; i >= 0; --i) 
    {
        current._shift_right();
        current._digits[0] = first._digits[i];
        current._delete_leading_zeros();
        int x = 0, l = 0, r = LongInt::cell;
        while (l <= r) 
        {
            int m = (l + r) / 2;
            LongInt t = b * m;
            if (t <= current) {
                x = m;
                l = m + 1;
            }
            else r = m - 1;
        }

        result._digits[i] = x;
        current = current - b * x;
    }

    result._is_negative = first._is_negative != second._is_negative;
    result._delete_leading_zeros();
    return result;
}

const LongInt operator%(const LongInt& first, const LongInt& second)
{
    LongInt result = first - (first / second) * second;
    if (result._is_negative) result += second;
    return result;
}

const LongInt operator+(const LongInt first, signed long long second)
{
    LongInt a(second);
    return (first + a);
}

const LongInt operator-(const LongInt first, signed long long second)
{
    LongInt a(second);
    return (first - a);
}

const LongInt operator*(const LongInt& first, signed long long second)
{
    LongInt a(second);
    return (first * a);
}

const LongInt operator/(const LongInt& first, signed long long second)
{
    LongInt a(second);
    return (first / a);
}

const LongInt operator%(const LongInt& first, signed long long second)
{
    LongInt a(second);
    return (first % a);
}


LongInt& LongInt::operator+=(const LongInt& value)
{
    return *this = (*this + value);
}

LongInt& LongInt::operator-=(const LongInt& value)
{
    return *this = (*this - value);
}

LongInt& LongInt::operator+=(const signed long long value)
{
    LongInt a(value);
    return *this = (*this + a);
}

LongInt& LongInt::operator-=(const signed long long value)
{
    LongInt a(value);
    return *this = (*this - a);
}


const LongInt LongInt::operator++() 
{
    LongInt a((unsigned long long)1);
    return (*this += a);
}

const LongInt LongInt::operator ++(int) 
{
    LongInt a((unsigned long long)1);
    *this += a;
    return *this - a;
}

const LongInt LongInt::operator --() 
{
    LongInt a((unsigned long long)1);
    return (*this -= a);
}

const LongInt LongInt::operator --(int) 
{
    LongInt a((unsigned long long)1);
    *this -= a;
    return *this + a;
}