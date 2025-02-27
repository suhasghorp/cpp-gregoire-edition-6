#pragma once

#include <string>
#include <format>
#include <utility>
#include <iostream>
#include <iomanip>

class Person
{
public:
	// Two-parameter constructor automatically creates initials.
	// 
	// Warning: delegating to the 3-parameter constructor as follows doesn't work:
	//		Person(std::string firstName, std::string lastName)
	//			: Person{ std::move(firstName), std::move(lastName),
	//			std::format("{}{}", firstName[0], lastName[0]) }
	// because then firstName and lastName could already have been moved into
	// temporary std::strings before firstName[O] and lastName[O] are used in
	// the call to std::format().
	explicit Person(std::string firstName, std::string lastName)
		: m_firstName{ std::move(firstName) }
		, m_lastName{ std::move(lastName) }
	{
		m_initials = std::format("{}{}", m_firstName[0], m_lastName[0]);
	}

	Person() = default;

	explicit Person(std::string firstName, std::string lastName, std::string initials)
		: m_firstName{ std::move(firstName) }
		, m_lastName{ std::move(lastName) }
		, m_initials{ std::move(initials) }
	{
	}

	const std::string& getFirstName() const { return m_firstName; }
	void setFirstName(std::string firstName) { m_firstName = std::move(firstName); }

	const std::string& getLastName() const { return m_lastName; }
	void setLastName(std::string lastName) { m_lastName = std::move(lastName); }

	const std::string& getInitials() const { return m_initials; }
	void setInitials(std::string initials) { m_initials = std::move(initials); }

	void output(std::ostream& output) const
	{
		std::println(output, "{} {} ({})", getFirstName(), getLastName(), getInitials());
	}

	// Only this single line of code is needed to add support
	// for all six comparison operators.
	[[nodiscard]] auto operator<=>(const Person&) const = default;

private:
	std::string m_firstName;
	std::string m_lastName;
	std::string m_initials;
};

inline std::ostream& operator<<(std::ostream& os, const Person& person)
{
	os << std::quoted(person.getFirstName())
		<< std::quoted(person.getLastName())
		<< std::quoted(person.getInitials());

	return os;
}

inline std::istream& operator>>(std::istream& is, Person& person)
{
	std::string firstName, lastName, initials;
	is >> std::quoted(firstName)
		>> std::quoted(lastName)
		>> std::quoted(initials);

	person.setFirstName(std::move(firstName));
	person.setLastName(std::move(lastName));
	person.setInitials(std::move(initials));

	return is;
}
