#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QException>

class Exception : public QException
{
public:
    Exception(const QString &);
    virtual ~Exception() _GLIBCXX_USE_NOEXCEPT;

    void raise() const Q_DECL_OVERRIDE;
    Exception *clone() const Q_DECL_OVERRIDE;
    virtual const QString what() const _GLIBCXX_USE_NOEXCEPT;
private:
    QString message;
};

#endif // EXCEPTION_H
