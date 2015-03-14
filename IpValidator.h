#ifndef IP_VALIDATOR
#define IP_VALIDATOR

#include <QValidator>

class IpValidator : public QValidator {
public:
	IpValidator();

	void fixup(QString& input) const;

	State validate(QString& input, int& position) const;
};

#endif // IP_VALIDATOR
