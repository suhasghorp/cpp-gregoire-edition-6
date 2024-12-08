#pragma once

#include "Employee.h"

namespace HR
{
	class Manager : public Employee
	{
	public:
		// Explicitly inherit Employee's constructors.
		using Employee::Employee;

		std::string toString() const override
		{
			return std::format("Manager is {}", Employee::toString());
		}
	};
}
