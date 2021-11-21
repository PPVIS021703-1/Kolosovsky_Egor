#pragma once
#ifndef long_H
#define long_H

#include <vector>
#include <string>
#include <sstream>  /* streamstring */
#include <iomanip>  /* setw */


class LongInt 
{
	private:
		/* Basis size of the cell in numver */
		static const int cell = 1e9;

		/* Number itself */
		std::vector<int> _digits;

		/* Sign (+/-) */
		bool _is_negative;

		/**/
		void _delete_leading_zeros();
		void _shift_right();

		class _divide_by_zero : public std::exception {};

	public:
		/* Constructors */
		LongInt();
		LongInt(std::string str);
		LongInt(signed long long l);
		LongInt(unsigned long long l);

		/**/
		/* Conversion operator */
		/* Allows [explicitly/implicitly] cast an object to std::string. */
		const LongInt operator -() const;
		const LongInt operator +() const;
		operator std::string() const;

		/* The friendly function [friend] is not a member of the class, */
		/* But has access to private fields */
		friend std::ostream& operator << (std::ostream& os, const LongInt& bi);

		friend bool operator==(const LongInt& first, const LongInt& second);
		friend bool  operator<(const LongInt& first, const LongInt& second);
		friend bool operator!=(const LongInt& first, const LongInt& second);
		friend bool operator<=(const LongInt& first, const LongInt& second);
		friend bool  operator>(const LongInt& first, const LongInt& second);
		friend bool operator>=(const LongInt& first, const LongInt& second);
		friend bool operator==(const LongInt& first, signed long long second);
		friend bool  operator<(const LongInt& first, signed long long second);
		friend bool operator!=(const LongInt& first, signed long long second);
		friend bool operator<=(const LongInt& first, signed long long second);
		friend bool  operator>(const LongInt& first, signed long long second);
		friend bool operator>=(const LongInt& first, signed long long second);

		friend const LongInt operator+(const LongInt first, const LongInt& second);
		friend const LongInt operator-(const LongInt first, const LongInt& second);
		friend const LongInt operator*(const LongInt& first, const LongInt& second);
		friend const LongInt operator/(const LongInt& first, const LongInt& second);
		friend const LongInt operator%(const LongInt& first, const LongInt& second);
		friend const LongInt operator+(const LongInt first, signed long long second);
		friend const LongInt operator-(const LongInt first, signed long long second);
		friend const LongInt operator*(const LongInt& first, signed long long second);
		friend const LongInt operator/(const LongInt& first, signed long long second);
		friend const LongInt operator%(const LongInt& first, signed long long second);

		/* Operations are performed directly only on the object itself */
		LongInt& operator+=(const LongInt& value);
		LongInt& operator-=(const LongInt& value);
		LongInt& operator+=(const signed long long value);
		LongInt& operator-=(const signed long long value);

		const LongInt operator++();
		const LongInt operator--();
		const LongInt operator++(int);
		const LongInt operator--(int);
	};

#endif // !1#pragma once